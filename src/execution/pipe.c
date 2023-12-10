/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 00:42:19 by vkozlova          #+#    #+#             */
/*   Updated: 2023/12/09 20:43:28 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_first_cmd_in_pipe(t_data *data, t_cmd_list *list,
			t_pipe_list *first, t_pipe_list *pipes)
{
	int	pid;

	if (list && list->prev)
	{
		pid = fork();
		if (pid < 0)
			exit_shell_no_mes(errno, data);
		if (pid == 0)
		{
			close_fds(&first, pipes, NULL);
			redir_input_to_pipe(pipes->fd[0], data);
			exec_cmd(data, list);
			exit_shell_no_mes(errno, data);
		}
	}
}

void	exec_lst_cmd_in_pipe(t_data *data, t_cmd_list *list,
			t_pipe_list *first, t_pipe_list *pipes)
{
	int	pid;
	int	status;

	pid = fork();
	status = 0;
	if (pid < 0)
		exit_shell_no_mes(errno, data);
	if (pid == 0)
	{
		close_fds(&first, NULL, pipes);
		redir_output_to_pipe(pipes->fd[1], data);
		exec_cmd(data, list);
		exit_shell_no_mes(errno, data);
	}
	close_fds(&first, NULL, NULL);
	while (waitpid(pid, &status, 0) > 0);
	free_pipe(pipes);
	data->exit_status = WEXITSTATUS(status);
	return_in_out(data);
}

void	exec_pipe(t_data *data, t_cmd_list *list)
{
	t_pipe_list	*pipes;
	t_pipe_list	*first_pipe;

	first_pipe = create_pipes(list);
	pipes = first_pipe;
	list = get_last_cmd(list);
	pipes = get_last_pipe(pipes);
	exec_first_cmd_in_pipe(data, list, first_pipe, pipes);
	if (list && list->prev)
		list = list->prev;
	while (list && list->prev)
	{
		pipes = pipes->prev;
		if (fork() == 0)
		{
			close_fds(&first_pipe, pipes, pipes->next);
			redir_input_to_pipe(pipes->fd[0], data);
			redir_output_to_pipe(pipes->next->fd[1], data);
			exec_cmd(data, list);
			exit_shell_no_mes(errno, data);
		}
		list = list->prev;
	}
	exec_lst_cmd_in_pipe(data, list, first_pipe, pipes);
}
