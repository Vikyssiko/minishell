/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlova <vkozlova@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 20:08:02 by vkozlova          #+#    #+#             */
/*   Updated: 2023/12/09 20:08:02 by vkozlova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd_list	*get_last_cmd(t_cmd_list *list)
{
	while (list && list->next)
		list = list->next;
	return (list);
}

t_pipe_list	*get_last_pipe(t_pipe_list *pipes)
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
