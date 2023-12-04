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
	if (file < 0 || dup2(file, STDOUT_FILENO) < 0)
		exit_shell_no_free("Error in output redirection\n", errno, data);
//		data->exit_status = errno;
	close(file);
//		return (errno);
}

void	redir_input(char *name, t_data *data)
{
	int	file;

	file = open(name, O_RDONLY, 0777);
	if (file < 0)
		put_to_stderr_and_exit("minishell: %s: No such file or directory\n",
							   name, data, errno);
	if (dup2(file, STDIN_FILENO) < 0)
		exit_shell_no_free("Error in input redirection\n", errno, data);
//		data->exit_status = errno;
//		return (errno);
	close(file);
}

void	append(char *name, t_data *data)
{
	int	file;

	file = open(name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (file < 0 || dup2(file, STDOUT_FILENO) < 0)
		exit_shell_no_free("Error append\n", errno, data);
//		data->exit_status = errno;
//		return (errno);
	close(file);
}

void	delim(char *name, t_data *data, int stdin, int stdout)
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
		write(stdout, "> ", 2);
		str = get_next_line(stdin);
		while (str && ft_strncmp(str, name, ft_strlen(str)  - 1) != 0)
		{
			write(fd[1], str, ft_strlen(str));
//			write(fd[1], "\n", 1);
			free(str);
			write(stdout, "> ", 2);
			str = get_next_line(stdin);
		}
//		perror("ls");
		exit(1);
	}
	waitpid(pid, NULL, 0);
	dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
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
