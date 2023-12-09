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

void	exec_pipes(t_data *data)
{
	t_cmd_list	*list;

	list = data->list;
	data->in = dup(0);
	data->out = dup(1);
	if (data->in < 0 || data->out < 0)
		exit_shell_no_mes(errno, data);
	if (list && !(list->next) && (ft_strcmp(list->value, "unset") == 0
			|| ft_strcmp(list->value, "export") == 0
			|| ft_strcmp(list->value, "cd") == 0
			|| ft_strcmp(list->value, "exit") == 0))
	{
		manage_redir(list, data);
		call_builtin_func(data, data->list);
		return_in_out(data);
		return ;
	}
	if (list && list->next)
		exec_pipe(data, list);
	else
		exec_last_cmd(data, list);
}
