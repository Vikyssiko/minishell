/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 20:58:01 by vkozlova          #+#    #+#             */
/*   Updated: 2023/12/03 22:51:52 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	redir_output(char *name, t_data *data)
{
	int	file;

	file = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file < 0 || dup2(file, STDOUT_FILENO) < 0)
		data->exit_status = errno;
	close(file);
//		return (errno);
}

void	redir_input(char *name, t_data *data)
{
	int	file;

	file = open(name, O_RDONLY, 0777);
	if (file < 0)
	{
		put_to_stderr_and_free("minishell: %s: No such file or directory\n",
			name, data, 1);
		exit(1);
//		return (errno);
	}
	if (dup2(file, STDIN_FILENO) < 0)
		data->exit_status = errno;
//		return (errno);
	close(file);
}

void	append(char *name, t_data *data)
{
	int	file;

	file = open(name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (file < 0 || dup2(file, STDOUT_FILENO) < 0)
		data->exit_status = errno;
//		return (errno);
	close(file);
}

void	delim(char *name, t_data *data)
{
	int 	pid;
	int		fd[2];
	char	*str;

	if (pipe(fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		data->exit_status = errno;
//	if (pid == -1)
//		exit(0);
	if (pid == 0)
	{
//		str = get_next_line(0);
		str = readline("> ");
		while (str && ft_strcmp(str, name) != 0)
		{
			write(fd[1], str, ft_strlen(str));
			write(fd[1], "\n", 1);
//			str = get_next_line(0);
			free(str);
			str = readline("> ");
		}
//		perror("ls");
		exit(1);
	}
//	sleep(1000);
	waitpid(pid, NULL, 0);
//	printf("child exec is over\n");
	dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
////	return (0);
}

void	manage_redir(t_cmd_list *list, t_data *data)
{
	t_redir	*redir_list;

	redir_list = list->redir_list;
	while (redir_list)
	{
		if (redir_list->redir_token->type == T_RED_OUT)
			redir_output(redir_list->redir_word->word, data);
		else if (redir_list->redir_token->type == T_RED_INP)
			redir_input(redir_list->redir_word->word, data);
		else if (redir_list->redir_token->type == T_APPEND)
			append(redir_list->redir_word->word, data);
		else if (redir_list->redir_token->type == T_DELIM)
			delim(redir_list->redir_word->word, data);
		redir_list = redir_list->next;
	}
}

int	count_pipes(t_cmd_list *list)
{
	int	pipes;

	pipes = 0;
	while (list)
	{
		list = list->next;
		pipes++;
	}
	return (pipes);
}

int	exec_cmd(t_data *data, t_cmd_list *list)
{
	manage_redir(list, data);
	if (is_builtin(list))
	{
		call_builtin_func(data, list);
		exit(0);
	}
	else if (find_command_path(data, list) == NULL)
	{
		if (access(list->args_array[0], X_OK) == -1)
			{
				printf("%s: command not found\n", list->args_array[0]);
				// perror("");
				exit(126);
			}
		else
			execve(list->args_array[0], list->args_array, data->env_array);
	}
	else if (execve(find_command_path(data, list),
		   list->args_array, data->env_array) < 0)
	{
		// printf("exec error\n");
		// printf("Do you enter here?\n");
		exit(1);
	}
	return (0);
}

int	exec_pipe(t_data *data, t_cmd_list *list)
{
	int 	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		exit(0);
	pid = fork();
//	if (pid == -1)
//		exit(0);
	if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		exec_cmd(data, list);
//		perror("ls");
//		exit(1);
	}
	waitpid(pid, NULL, 0);
	dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
	return (0);
}

int	exec_pipes(t_data *data)
{
	t_cmd_list	*list;
	int 		stdin;
	int 		stdout;

	list = data->list;
	if (list && !(list->next) && (ft_strcmp(list->value, "unset") == 0
		|| ft_strcmp(list->value, "export") == 0
		|| ft_strcmp(list->value, "cd") == 0
		|| ft_strcmp(list->value, "exit") == 0))
	{
		call_builtin_func(data, data->list);
		return (0);
	}
	stdin = dup(0);
	stdout = dup(1);
	while (list && list->next)
	{
		exec_pipe(data, list);
		list = list->next;
	}
	//errors
	int 	pid;
	// pid < 0
	pid = fork();
	if (pid == 0)
		exec_cmd(data, list);
	waitpid(pid, NULL, 0);
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	dup2(stdin, 0);
	dup2(stdout, 1);
	return (0);
}
