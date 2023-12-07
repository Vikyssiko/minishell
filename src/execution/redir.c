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

void	redir_output(char *name, t_data *data)
{
	int	file;

	file = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file < 0 || dup2(file, STDOUT_FILENO) < 0 || close(file) < 0)
		exit_shell_no_mes(errno, data);
}

void	redir_input(char *name, t_data *data)
{
	int	file;

	file = open(name, O_RDONLY, 0777);
	if (file < 0)
		put_to_stderr_and_exit("minishell: %s: No such file or directory\n",
			name, data, errno);
	if (dup2(file, STDIN_FILENO) < 0 || close(file) < 0)
		exit_shell_no_mes(errno, data);
}

void	append(char *name, t_data *data)
{
	int	file;

	file = open(name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (file < 0 || dup2(file, STDOUT_FILENO) < 0 || close(file) < 0)
		exit_shell_no_mes(errno, data);
}

void	delim(char *name, t_data *data, int stdin, int stdout)
{
	int		pid;
	int		fd[2];
	int		status;

	if (pipe(fd) < 0)
		exit_shell_no_mes(errno, data);
	status = 0;
	pid = fork();
	if (pid < 0)
		exit_shell_no_mes(errno, data);
	if (pid == 0)
		read_input_delim(name, stdin, stdout, fd[1]);
	waitpid(pid, &status, 0);
	data->exit_status = WEXITSTATUS(status);
	if (dup2(fd[0], 0) < 0 || close(fd[0]) < 0 || close(fd[1]) < 0)
		exit_shell_no_mes(errno, data);
}

void	manage_redir(t_cmd_list *list, t_data *data, int stdin, int stdout)
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
			delim(redir_list->redir_word->word, data, stdin, stdout);
		redir_list = redir_list->next;
	}
}
