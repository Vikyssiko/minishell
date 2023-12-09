/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlova <vkozlova@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 00:42:19 by vkozlova          #+#    #+#             */
/*   Updated: 2023/12/08 19:05:57 by vkozlova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	return_in_out(t_data *data)
{
	if (close(STDOUT_FILENO) < 0 || close(STDIN_FILENO) < 0
		|| dup2(data->in, 0) < 0 || dup2(data->out, 1) < 0
		|| close(data->in) < 0 || close(data->out) < 0)
		exit_shell_no_mes(errno, data);
}

void	exec_cmd(t_data *data, t_cmd_list *list)
{
	manage_redir(list, data);
	if (is_builtin(list))
	{
		call_builtin_func(data, list);
		exit_shell_no_mes(0, data);
	}
	else if (list->args_array[0] && find_command_path(data, list) == NULL
			 && access(list->args_array[0], X_OK) == -1)
		put_to_stderr_and_exit("%s: command not found\n",
							   list->args_array[0], data, 127);
	else if (find_command_path(data, list) == NULL
			 && find_env_node(data->env_list, "PATH"))
		execve(list->args_array[0], list->args_array,
			   new_env_array(data));
	else if (find_command_path(data, list) == NULL
			 && (!find_env_node(data->env_list, "PATH")
				 && ft_strcmp(list->args_array[0], "./minishell") == 0))
		exit_shell_no_free("minishell: minishell: No such file "
						   "or directory\n", 127, data);
	else if (execve(find_command_path(data, list),
					list->args_array, new_env_array(data)) < 0)
		exit_shell_no_mes(errno, data);
	exit_shell_no_mes(errno, data);
}

void	exec_last_cmd(t_data *data, t_cmd_list *list)
{
	int	pid;
	int	status;

	status = 0;
	pid = 0;
	if (list && ((list->args_array && list->args_array[0])
				 || list->redir_list->redir_token->type == T_DELIM))
	{
		pid = fork();
		if (pid < 0)
			exit_shell_no_mes(errno, data);
		if (pid == 0)
		{
			exec_cmd(data, list);
			exit_shell_no_mes(errno, data);
		}
		while (waitpid(-1, &status, 0) > 0);
		data->exit_status = WEXITSTATUS(status);
	}
	else
		manage_redir(list, data);
	waitpid(pid, &status, 0);
	data->exit_status = WEXITSTATUS(status);
	return_in_out(data);
}

int	count_pipes(t_cmd_list *list)
{
	int			pipes;
	t_cmd_list	*copy;

	copy = list;
	pipes = 0;
	while (copy && copy->next)
	{
		copy = copy->next;
		pipes++;
	}
	return (pipes);
}

t_pipe_list	*create_pipes(t_cmd_list *list)
{
	int			pipe_num;
	t_pipe_list	*pipe_list;
	t_pipe_list	*first_pipe;
	t_pipe_list	*new_pipe;

	pipe_num = count_pipes(list);
	pipe_list = NULL;
	first_pipe = NULL;
	new_pipe = NULL;
	while (pipe_num > 0)
	{
		if (!first_pipe)
		{
			first_pipe = malloc(sizeof(t_pipe_list));
			first_pipe->next = NULL;
			first_pipe->prev = NULL;
			pipe_list = first_pipe;
		}
		else
		{
			new_pipe = malloc(sizeof(t_pipe_list));
			new_pipe->next = NULL;
			pipe_list->next = new_pipe;
			new_pipe->prev = pipe_list;
			pipe_list = pipe_list->next;
		}
		pipe(pipe_list->fd);
		pipe_num--;
	}
	return (first_pipe);
}

void	close_fds(t_pipe_list **first_pipe, t_pipe_list *in, t_pipe_list *out)
{
	t_pipe_list	*copy;

	copy = *first_pipe;
	while (copy)
	{
		if (in && copy == in)
			close(copy->fd[1]);
		else if (out && copy == out)
			close(copy->fd[0]);
		else
		{
			close(copy->fd[1]);
			close(copy->fd[0]);
		}
		copy = copy->next;
	}
}

t_cmd_list	*get_last_cmd(t_cmd_list *list)
{
	while (list && list->next)
		list = list->next;
	return (list);
}

t_pipe_list 	*get_last_pipe(t_pipe_list *pipes)
{
	while (pipes && pipes->next)
		pipes = pipes->next;
	return (pipes);
}

void	redir_input_to_pipe(int fd, t_data *data)
{
	if (dup2(fd, 0) < 0 || close(fd) < 0)
		exit_shell_no_mes(errno, data);
}

void	redir_output_to_pipe(int fd, t_data *data)
{
	if (dup2(fd, 1) < 0 || close(fd) < 0)
		exit_shell_no_mes(errno, data);
}

void	exec_pipe(t_data *data, t_cmd_list *list)
{
	t_pipe_list	*pipes;
	t_pipe_list	*first_pipe;
	int			status;

	status = 0;
	first_pipe = create_pipes(list);
	pipes = first_pipe;
	list = get_last_cmd(list);
	pipes = get_last_pipe(pipes);
	if (list && list->prev && fork() == 0)
	{
		close_fds(&first_pipe, pipes, NULL);
		dup2(pipes->fd[0], 0);
		close(pipes->fd[0]);
		exec_cmd(data, list);
		exit_shell_no_mes(errno, data);
	}
	if (list && list->prev)
		list = list->prev;
	while (list && list->prev)
	{
		pipes = pipes->prev;
		if (fork() == 0)
		{
			close_fds(&first_pipe, pipes, pipes->next);
			dup2(pipes->fd[0], 0);
			close(pipes->fd[0]);
			dup2(pipes->next->fd[1], 1);
			close(pipes->next->fd[1]);
			exec_cmd(data, list);
			exit_shell_no_mes(errno, data);
		}
		list = list->prev;
	}
	if (fork() == 0)
	{
		close_fds(&first_pipe, NULL, pipes);
		dup2(pipes->fd[1], 1);
		close(pipes->fd[1]);
		exec_cmd(data, list);
		exit_shell_no_mes(errno, data);
	}
	close_fds(&first_pipe, NULL, NULL);
	while (wait(&status) > 0);
	data->exit_status = WEXITSTATUS(status);
	return_in_out(data);
}

int	check_not_child_exec_builtins(t_cmd_list *list, t_data *data)
{
	if (list && !(list->next) && (ft_strcmp(list->value, "unset") == 0
		|| ft_strcmp(list->value, "export") == 0
		|| ft_strcmp(list->value, "cd") == 0
		|| ft_strcmp(list->value, "exit") == 0))
	{
		manage_redir(list, data);
		call_builtin_func(data, data->list);
		return_in_out(data);
		return (1);
	}
	return (0);
}


void	exec_pipes(t_data *data)
{
	t_cmd_list	*list;

	list = data->list;
	data->in = dup(0);
	data->out = dup(1);
	if (data->in < 0 || data->out < 0)
		exit_shell_no_mes(errno, data);
	if (!check_not_child_exec_builtins(list, data) && list && list->next)
		exec_pipe(data, list);
	else
		exec_last_cmd(data, list);
}


/*

t_pipe	*create_pipes(t_cmd_list *list)
{
	int			pipe_num;
	t_pipe		*pipe_list;
	t_pipe		*first_pipe;
	t_pipe		*new_pipe;

	pipe_num = count_pipes(list);
	pipe_list = NULL;
	first_pipe = NULL;
	new_pipe = NULL;
	while (pipe_num > 0)
	{
		if (!first_pipe)
		{
			first_pipe = malloc(sizeof(t_pipe));
			first_pipe->next = NULL;
			first_pipe->prev = NULL;
			pipe_list = first_pipe;
		}
		else
		{
			new_pipe = malloc(sizeof(t_pipe));
			new_pipe->next = NULL;
			pipe_list->next = new_pipe;
			new_pipe->prev = pipe_list;
			pipe_list = pipe_list->next;
		}
		pipe(pipe_list->fd);
		pipe_num--;
	}
	return (first_pipe);
}

void	close_fds(t_pipe **first_pipe, t_pipe *in, t_pipe *out)
{
	t_pipe	*copy;

	copy = *first_pipe;
	while (copy)
	{
		if (in && copy == in)
			close(copy->fd[1]);
		else if (out && copy == out)
			close(copy->fd[0]);
		else
		{
			close(copy->fd[1]);
			close(copy->fd[0]);
		}
		copy = copy->next;
	}
}

t_cmd_list	*get_last_cmd(t_cmd_list *list)
{
	while (list && list->next)
		list = list->next;
	return (list);
}

t_pipe 	*get_last_pipe(t_pipe *pipes)
{
	while (pipes && pipes->next)
		pipes = pipes->next;
	return (pipes);
}

void	redir_input_to_pipe(int fd, t_data *data)
{
	if (dup2(fd, 0) < 0 || close(fd) < 0)
		exit_shell_no_mes(errno, data);
}

void	redir_output_to_pipe(int fd, t_data *data)
{
	if (dup2(fd, 1) < 0 || close(fd) < 0)
		exit_shell_no_mes(errno, data);
}

void	exec_pipe(t_data *data, t_cmd_list *list, int stdin, int stdout)
{
	t_pipe_list	*pipes;
	t_pipe_list	*first_pipe;
//	int pid[10];
//	int i = 0;

	first_pipe = create_pipes(list);
	pipes = first_pipe;
//	pid[0] = fork();
	while (list && list->next)
		list = list->next;
	printf("here\n");
	while (pipes && pipes->next)
//		printf("now here\n");
		pipes = pipes->next;
//	printf("now here\n");
	if (list && list->prev && fork() == 0)
	{
		close_fds(&first_pipe, pipes, NULL);
		dup2(pipes->fd[0], 0);
		close(pipes->fd[0]);
		exec_cmd(data, list, stdin, stdout);
		exit_shell_no_mes(errno, data);
//		pipes = pipes->next;
	}
//	i++;
	if (list && list->prev)
		list = list->prev;
	while (list && list->prev)
	{
		pipes = pipes->prev;
//		pid[i] = fork();
		if (fork() == 0)
		{
			close_fds(&first_pipe, pipes, pipes->next);
			dup2(pipes->fd[0], 0);
			close(pipes->fd[0]);
			dup2(pipes->next->fd[1], 1);
			close(pipes->next->fd[1]);
			exec_cmd(data, list, stdin, stdout);
			exit_shell_no_mes(errno, data);
		}
		list = list->prev;
//		i++;
//		if (pipes->next)
//			pipes = pipes->next;
	}
//	pid[i] = fork();
	if (fork() == 0)
	{
		close_fds(&first_pipe, NULL, pipes);
		dup2(pipes->fd[1], 1);
		close(pipes->fd[1]);
		exec_cmd(data, list, stdin, stdout);
		exit_shell_no_mes(errno, data);
	}
	close_fds(&first_pipe, NULL, NULL);
	while (wait(NULL) > 0);
//	while (i >= 0)
//	{
//		wait(NULL);
////		waitpid(pid[i], NULL, 0);
//		i--;
//	}
	if (close(STDOUT_FILENO) < 0 || close(STDIN_FILENO) < 0
		|| dup2(stdin, 0) < 0 || dup2(stdout, 1) < 0
		|| close(stdin) < 0 || close(stdout) < 0)
		exit_shell_no_mes(errno, data);
}

//void	exec_pipe(t_data *data, t_cmd_list *list, int stdin, int stdout)
//{
//	t_pipe	*pipes;
//	t_pipe	*first_pipe;
//	int		status;
//
//	first_pipe = create_pipes(list);
//	pipes = first_pipe;
//	while (list && list->next)
//		list = list->next;
//	while (pipes && pipes->next)
//		pipes = pipes->next;
////	list = get_last_cmd(list);
////	pipes = get_last_pipe(first_pipe);
//	status = 0;
//	if (list && list->prev && fork() == 0)
//	{
//		close_fds(&first_pipe, pipes, NULL);
//		dup2(pipes->fd[0], 0);
//		close(pipes->fd[0]);
////		redir_input_to_pipe(pipes->fd[0], data);
//		exec_cmd(data, list, stdin, stdout);
//	}
//	if (list && list->prev)
//		list = list->prev;
//	while (list && list->prev)
//	{
//		pipes = pipes->prev;
//		if (fork() == 0)
//		{
//			close_fds(&first_pipe, pipes, pipes->next);
//
////			redir_input_to_pipe(pipes->fd[0], data);
//			dup2(pipes->fd[0], 0);
//			close(pipes->fd[0]);
//			dup2(pipes->fd[1], 1);
//			close(pipes->fd[1]);
//			exec_cmd(data, list, stdin, stdout);
//		}
//		list = list->prev;
//	}
//	if (fork() == 0)
//	{
//		close_fds(&first_pipe, NULL, pipes);
//		dup2(pipes->fd[1], 1);
//		close(pipes->fd[1]);
//		exec_cmd(data, list, stdin, stdout);
//	}
//	close_fds(&first_pipe, NULL, NULL);
//	while (waitpid(-1, &status, 0) > 0);
//	data->exit_status = WEXITSTATUS(status);
//	return_in_out(stdin, stdout, data);
//}

int	check_not_child_exec_builtins(t_cmd_list *list)
{
	if (list && !(list->next) && (ft_strcmp(list->value, "unset") == 0
			|| ft_strcmp(list->value, "export") == 0
			|| ft_strcmp(list->value, "cd") == 0
			|| ft_strcmp(list->value, "exit") == 0))
		return (1);
	return (0);
}


void	exec_pipes(t_data *data)
{
	t_cmd_list	*list;
	int			stdin;
	int			stdout;

	list = data->list;
	stdin = dup(0);
	stdout = dup(1);
	if (stdin < 0 || stdout < 0)
		exit_shell_no_mes(errno, data);
	if (check_not_child_exec_builtins(list))
	{
		manage_redir(list, data, stdin, stdout);
		call_builtin_func(data, data->list);
		if (close(STDOUT_FILENO) < 0 || close(STDIN_FILENO) < 0
			|| dup2(stdin, 0) < 0 || dup2(stdout, 1) < 0)
			exit_shell_no_mes(errno, data);
		return ;
	}
	if (list && list->next)
		exec_pipe(data, list, stdin, stdout);
	else
		exec_last_cmd(data, list, stdin, stdout);
}
*/