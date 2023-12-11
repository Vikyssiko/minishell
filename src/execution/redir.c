/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlova <vkozlova@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:14:27 by vkozlova          #+#    #+#             */
/*   Updated: 2023/12/04 19:14:27 by vkozlova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	output(t_redir *redir, t_data *data, t_cmd_list *list)
{
	int	file;

	file = open(redir->redir_word->word, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	list->out = redir;
	if (file < 0)
		exit_shell_no_mes(errno, data);
	if (close(file) < 0)
		exit_shell_no_mes(errno, data);
//	if (file < 0 || dup2(file, STDOUT_FILENO) < 0 || close(file) < 0)
//		exit_shell_no_mes(errno, data);
}

int	input(t_redir *redir, t_data *data, t_cmd_list *list, int delim)
{
	int	file;

	file = open(redir->redir_word->word, O_RDONLY, 0777);
	if (file < 0)
	{
		put_to_stderr("minishell: %s: No such file or directory\n",
			redir->redir_word->word, data, errno);
		return (0);
	}
	else
	{
		list->in = redir;
		if (delim == 1)
			list->fd_in = -1;
		if (close(file) < 0)
			exit_shell_no_mes(errno, data);
	}
	return (1);
//	else if (dup2(file, STDIN_FILENO) < 0 || close(file) < 0)
//		exit_shell_no_mes(errno, data);
}

void	append(t_redir *redir, t_data *data, t_cmd_list *list)
{
	int	file;

	file = open(redir->redir_word->word, O_WRONLY | O_CREAT | O_APPEND, 0777);
	list->out = redir;
	if (file < 0 || close(file) < 0)
		exit_shell_no_mes(errno, data);
//	if (file < 0 || dup2(file, STDOUT_FILENO) < 0 || close(file) < 0)
//		exit_shell_no_mes(errno, data);
}

void	delim(char *name, t_data *data, t_cmd_list *list)
{
	int		pid;
	int		fd[2];
	int		status;

	if (pipe(fd) < 0)
		exit_shell_no_mes(errno, data);
//	if (list->fd_in && close(list->fd_in) < 0)
//		exit_shell_no_mes(errno, data);
	status = 0;
	pid = fork();
	if (pid < 0)
		exit_shell_no_mes(errno, data);
	if (pid == 0)
		read_input_delim(name, data->in, data->out, fd[1]);
	waitpid(pid, &status, 0);
	data->exit_status = WEXITSTATUS(status);
	list->fd_in = fd[0];
	if (close(fd[1]) < 0)
		exit_shell_no_mes(errno, data);
//	if (dup2(fd[0], 0) < 0 || close(fd[0]) < 0 || close(fd[1]) < 0)
//		exit_shell_no_mes(errno, data);
}

int	manage_redir(t_cmd_list *list, t_data *data)
{
	t_redir	*redir_list;
	int		del;

	del = 0;
	redir_list = list->redir_list;
	while (redir_list)
	{
		if (gl_signal == SIGINT)
			break ;
		else if (redir_list->redir_token->type == T_DELIM)
			delim(redir_list->redir_word->word, data, list);
		redir_list = redir_list->next;
	}
	redir_list = list->redir_list;
	while (redir_list)
	{
//		if (gl_signal == SIGINT)
//			break ;
		if (redir_list->redir_token->type == T_RED_OUT)
			output(redir_list, data, list);
		else if (redir_list->redir_token->type == T_RED_INP)
		{
			if (input(redir_list, data, list, del) == 0)
			{
				list->redir_status = -1;
				return (0);
			}
			del = 0;
		}
		else if (redir_list->redir_token->type == T_APPEND)
			append(redir_list, data, list);
		else if (redir_list->redir_token->type == T_DELIM)
			del = 1;
		redir_list = redir_list->next;
	}
	return (1);
}
