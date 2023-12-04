/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 20:58:01 by vkozlova          #+#    #+#             */
/*   Updated: 2023/12/04 15:42:33 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_cmd(t_data *data, t_cmd_list *list, int stdin, int stdout)
{
	manage_redir(list, data, stdin, stdout);
	if (is_builtin(list))
	{
		call_builtin_func(data, list);
		exit(0);
	}
	else if (find_command_path(data, list) == NULL
		&& access(list->args_array[0], X_OK) == -1)
		put_to_stderr_and_exit("%s: command not found\n",
			list->args_array[0], data, 126);
	if (execve(find_command_path(data, list),
		   list->args_array, new_env_array(data)) < 0)
		exit(1);
	return (0);
}

int	exec_pipe(t_data *data, t_cmd_list *list, int stdin, int stdout)
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
		exec_cmd(data, list, stdin, stdout);
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
		exec_pipe(data, list, stdin, stdout);
		list = list->next;
	}
	//errors
	int 	pid;
	// pid < 0
	pid = fork();
	if (pid == 0)
		exec_cmd(data, list, stdin, stdout);
	waitpid(pid, NULL, 0);
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	dup2(stdin, 0);
	dup2(stdout, 1);
	return (0);
}
