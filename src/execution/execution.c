/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlova <vkozlova@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 20:10:16 by vkozlova          #+#    #+#             */
/*   Updated: 2023/12/09 20:10:16 by vkozlova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	return_in_out(t_data *data)
{
//	printf("I want to close data->in and data->out\n");
	if (close(STDOUT_FILENO) < 0 || close(STDIN_FILENO) < 0
		|| dup2(data->in, 0) < 0 || dup2(data->out, 1) < 0
		|| close(data->in) < 0 || close(data->out) < 0)
		exit_shell_no_mes(errno, data);
}

void	redir_input(t_cmd_list *list, t_data *data)
{
	int	file;

	if (list->fd_in != -1)
		file = list->fd_in;
	else
		file = open(list->in->redir_word->word, O_RDONLY, 0777);
	if (file < 0)
	{
		put_to_stderr_and_exit("minishell: %s: No such file or directory\n",
			list->in->redir_word->word, data, errno);
	}
	else if (dup2(file, STDIN_FILENO) < 0 || close(file) < 0)
		exit_shell_no_mes(errno, data);
}

void	redir_output(t_redir *redir, t_data *data)
{
	int	file;

	file = 0;
//	printf("I am in redir output\n");
	if (redir->redir_token->type == T_RED_OUT)
		file = open(redir->redir_word->word, O_WRONLY | O_TRUNC, 0777);
	else if (redir->redir_token->type == T_APPEND)
		file = open(redir->redir_word->word, O_WRONLY | O_APPEND, 0777);
	if (file < 0 || dup2(file, STDOUT_FILENO) < 0 || close(file) < 0)
		exit_shell_no_mes(errno, data);
}

void	exec_cmd(t_data *data, t_cmd_list *list)
{
//	manage_redir(list, data);
//	if (list && list->redir_status == -1)
//		return ;
//		exit(1);
//	printf("list out: %s\n", list->out->redir_word->word);
	if (list->in)
		redir_input(list, data);
	if (list->out)
		redir_output(list->out, data);
	if (gl_signal != SIGINT)
	{
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
}

void	exec_last_cmd(t_data *data, t_cmd_list *list)
{
	int	pid;
	int	status;

	status = 0;
	if (list && list->redir_status == -1)
		return ;
	if (gl_signal != SIGINT && list && ((list->args_array && list->args_array[0])))
//			|| list->redir_list->redir_token->type == T_DELIM))
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
//	else
//		manage_redir(list, data);
//	printf("I am here\n");
	return_in_out(data);
}

void	exec_pipes(t_data *data)
{
	t_cmd_list	*list;

	list = data->list;
//	printf("I am in exec pipes\n");
	data->in = dup(0);
	data->out = dup(1);
	if (data->in < 0 || data->out < 0)
		exit_shell_no_mes(errno, data);
	while (list)
	{
		manage_redir(list, data);
		list = list->next;
	}
//	printf("I am here\n");
	list = data->list;
	if (list && !(list->next) && (ft_strcmp(list->value, "unset") == 0
			|| ft_strcmp(list->value, "export") == 0
			|| ft_strcmp(list->value, "cd") == 0
			|| ft_strcmp(list->value, "exit") == 0))
	{
		if (list->in)
			redir_input(list, data);
		if (list->out)
			redir_output(list->out, data);
//		manage_redir(list, data);
		if (gl_signal != SIGINT)
			call_builtin_func(data, data->list);
		return_in_out(data);
		return ;
	}
	if (list && list->next && gl_signal != SIGINT)
		exec_pipe(data, list);
	else
		exec_last_cmd(data, list);
	while (wait(NULL) > 0);
}
