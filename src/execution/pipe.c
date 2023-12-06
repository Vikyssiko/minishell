/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 20:58:01 by vkozlova          #+#    #+#             */
/*   Updated: 2023/12/06 22:02:28 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_cmd(t_data *data, t_cmd_list *list, int stdin, int stdout)
{
	manage_redir(list, data, stdin, stdout);
	if (is_builtin(list))
	{
		call_builtin_func(data, list);
		exit_shell_no_mes(0, data);
	}
	else if (list->args_array[0] && find_command_path(data, list) == NULL
		&& access(list->args_array[0], X_OK) == -1)
		put_to_stderr_and_exit("%s: command not found\n",
			list->args_array[0], data, 127);
	else if (find_command_path(data, list) == NULL)
		execve(list->args_array[0], list->args_array,
			new_env_array(data));
	else if (execve(find_command_path(data, list),
			list->args_array, new_env_array(data)) < 0)
		exit_shell_no_mes(errno, data);
	exit_shell_no_mes(errno, data);
}

int	exec_pipe(t_data *data, t_cmd_list *list, int stdin, int stdout)
{
	int	pid;
	int	fd[2];
	int	status;

	if (pipe(fd) < 0)
		exit_shell_no_mes(errno, data);
	pid = fork();
	status = 0;
	if (pid < 0)
		exit_shell_no_mes(errno, data);
	if (pid == 0)
	{
		if (dup2(fd[1], 1) < 0 || close(fd[0]) < 0 || close(fd[1]) < 0)
			exit(errno);
		exec_cmd(data, list, stdin, stdout);
		exit_shell_no_mes(errno, data);
	}
	waitpid(pid, &status, 0);
	data->exit_status = WEXITSTATUS(status);
	if (dup2(fd[0], 0) < 0 || close(fd[0]) < 0 || close(fd[1]) < 0)
		exit_shell_no_mes(errno, data);
	return (0);
}

void	exec_last_cmd(t_data *data, t_cmd_list *list, int stdin, int stdout)
{
	int	pid;
	int	status;

	status = 0;
	pid = fork();
	if (pid < 0)
		exit_shell_no_mes(errno, data);
	if (pid == 0)
	{
		exec_cmd(data, list, stdin, stdout);
		exit_shell_no_mes(errno, data);
	}
	waitpid(pid, &status, 0);
	data->exit_status = WEXITSTATUS(status);
	if (close(STDOUT_FILENO) < 0 || close(STDIN_FILENO) < 0
		|| dup2(stdin, 0) < 0 || dup2(stdout, 1) < 0)
		exit_shell_no_mes(errno, data);
}

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
	while (list && list->next)
	{
		exec_pipe(data, list, stdin, stdout);
		list = list->next;
	}
	if (list && list->args_array && list->args_array[0])
		exec_last_cmd(data, list, stdin, stdout);
}
