/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlova <vkozlova@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 20:58:01 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/19 14:21:31 by vkozlova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	redir_output(char *name, t_data *data)
{
	int	file;

	file = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file < 0 || dup2(file, STDOUT_FILENO) < 0)
		data->exit_status = errno;
	close(file);
//	printf("hello\n");
//	close(STDIN_FILENO);
//		return (errno);
}

void	redir_input(char *name, t_data *data)
{
	int	file;

	file = open(name, O_WRONLY | O_TRUNC, 0777);
	if (file < 0)
	{
		printf("minishell: %s: No such file or directory\n", name);
		data->exit_status = errno;
//		return (errno);
	}
	if (dup2(file, STDIN_FILENO) < 0)
		data->exit_status = errno;
//		return (errno);
	close(file);
	// bash: end: No such file or directory
//	close(file);
}

void	append(char *name, t_data *data)
{
	int	file;

	file = open(name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (file < 0 || dup2(file, STDOUT_FILENO) < 0)
		data->exit_status = errno;
//		return (errno);
	close(file);
//	int	pid;
//	int	file;
//
//	pid = fork();
//	if (pid < 0)
//		return (errno);
//	if (pid == 0)
//	{
//		// 0777 permission
//		file = open(tree->redir_word, O_WRONLY | O_CREAT | O_APPEND);
//		if (file < 0 || dup2(file, STDOUT_FILENO) < 0)
//			return (errno);
//		close(file);
//	}
//	waitpid(pid, NULL, 0);
}

// child process?
void	manage_redir(t_cmd_list *list, t_data *data)
{
	t_redir	*redir_list;

	redir_list = list->redir_list;
//	printf("I am in manage redir function\n");
	while (redir_list)
	{
//		printf("I am in manage redir loop\n");
		if (redir_list->redir_token->type == T_RED_OUT)
			redir_output(redir_list->redir_word->word, data);
		else if (redir_list->redir_token->type == T_RED_INP)
			redir_input(redir_list->redir_word->word, data);
		else if (redir_list->redir_token->type == T_APPEND)
			append(redir_list->redir_word->word, data);
//		else if (redir_list->redir_token->type == T_DELIM)
//			delim(redir_list->redir_word->word, data);
		redir_list = redir_list->next;
	}
//	call_builtin_func(data, data->list);
//	close(STDOUT_FILENO);
}

int	count_pipes(t_cmd_list *list)
{
	int	pipes;

	pipes = 0;
	while (list)
	{
		list = list->next;
		pipes++;
	}
	return (pipes);
}

//int	exec_pipe(t_data *data, t_cmd_list *list)
//{
//	int fd[2];
//	int	pid_out;
////	int	pid_in;
//
//
//	if (pipe(fd) < 0)
//		return (1);
//	pid_out = fork();
//	if (pid_out < 0)
//		return (2);
//	if (pid_out == 0)
//	{
//		dup2(fd[1], STDOUT_FILENO);
//		close(fd[0]);
//		close(fd[1]);
//		execve(find_executable_path(data->path, list->value),
//			   list->args_array, data->env_array);
//	}
//
////	pid_in = fork();
////	if (pid_in < 0)
////		return (3);
////	if (pid_in == 0)
////	{
////		dup2(fd[0], STDIN_FILENO);
////		close(fd[1]);
////		close(fd[0]);
////		execve(find_executable_path(data->path, right->value),
////			   right->args_array, data->env_array);
////	}
//	close(fd[0]);
//	close(fd[1]);
//	waitpid(pid_out, NULL, 0);
////	waitpid(pid_in, NULL, 0);
//	return (0);
//}

int	exec_cmd(t_data *data, t_cmd_list *list)
{
//	int	pid_out;
//	int stdin;
//	int stdout;
//
//	stdin = dup(0);
//	stdout = dup(1);
//
//	pid_out = fork();
//	if (pid_out < 0)
//		return (2);
//	if (pid_out == 0)
//	{
//		printf("HERE\n");
		manage_redir(list, data);
		if (is_builtin(list))
			call_builtin_func(data, list);
		else
			execve(find_executable_path(data->path, list->value),
			   list->args_array, data->env_array);
//	}
//	waitpid(pid_out, NULL, 0);
//	close(STDOUT_FILENO);
//	close(STDIN_FILENO);
//	dup2(stdin, 0);
//	dup2(stdout, 1);
	return (0);
}

int	exec_pipe(t_data *data, t_cmd_list *list)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) < 0)
		return (1);
	pid = fork();
	if (pid < 0)
		return (2);
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], 1) < 0)
			return (3);
		exec_cmd(data, list);
	}
	else
	{
		close(fd[1]);
		if (dup2(fd[0], 0) < 0)
			return (4);
	}
	return (0);
}

int	exec_pipes(t_data *data)
{
//	int			pipes;
	t_cmd_list	*list;
	int stdin;
	int stdout;

	list = data->list;
	stdin = dup(0);
	stdout = dup(1);
//	pipes = count_pipes(list);
//	printf("I am here");
	while (list)
	{
//		printf("I am here: %s\n", list->redir_list->redir_word->word);
		exec_cmd(data, list);
		list = list->next;
	}
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	dup2(stdin, 0);
	dup2(stdout, 1);
	return (0);
}
