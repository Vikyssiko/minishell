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

void	exec_cmd(t_data *data, t_cmd_list *list)
{
	redir_input_output(list, data);
	if (g_signal != SIGINT)
	{
		if (call_builtin_func(data, list))
			exit_shell_no_mes(0, data);
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
	if (g_signal != SIGINT && list && list->redir_status > -1
		&& ((list->args_array && list->args_array[0])))
	{
		pid = fork();
		if (pid < 0)
			exit_shell_no_mes(errno, data);
		if (pid == 0)
		{
			exec_cmd(data, list);
			exit_shell_no_mes(errno, data);
		}
		while (waitpid(-1, &status, 0) > 0)
			continue ;
		data->exit_status = WEXITSTATUS(status);
	}
	if (list->fd_in != -1 && close(list->fd_in) < 0)
		exit_shell_no_mes(errno, data);
	return_in_out(data);
}

int	check_not_child_exec_builtins(t_cmd_list *list, t_data *data)
{
	if (list && !(list->next) && (ft_strcmp(list->value, "unset") == 0
			|| ft_strcmp(list->value, "export") == 0
			|| ft_strcmp(list->value, "cd") == 0
			|| ft_strcmp(list->value, "exit") == 0))
	{
		redir_input_output(list, data);
		if (g_signal != SIGINT)
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
	while (list)
	{
		manage_redir(list, data);
		list = list->next;
	}
	list = data->list;
	if (check_not_child_exec_builtins(list, data))
		return ;
	if (list && list->next && g_signal != SIGINT)
		exec_pipe(data, list);
	else
		exec_last_cmd(data, list);
	while (wait(NULL) > 0)
		continue ;
}
