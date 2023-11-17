/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlova <vkozlova@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 20:58:01 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/14 20:58:01 by vkozlova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*
void	redir_output(t_tree *tree, int write_fd)
{
	int	file;

	file = open(tree->redir_word, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file < 0 || dup2(file, STDOUT_FILENO) < 0)
		return (errno);
//	close(file);
}

void	redir_input(t_tree *tree, int read_fd)
{
	int	file;

	file = open(tree->redir_word, O_WRONLY | O_TRUNC, 0777);
	if (file < 0)
	{
		printf("minishell: %s: No such file or directory\n", tree->redir_word);
		return (errno);
	}
	if (dup2(file, STDIN_FILENO) < 0)
		return (errno);
	// bash: end: No such file or directory
//	close(file);
}

void	append(t_tree *tree)
{
	int	file;

	file = open(tree->redir_word, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (file < 0 || dup2(file, STDOUT_FILENO) < 0)
		return (errno);
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

int	count_pipes(t_tree *tree)
{
	int	pipes;

	pipes = 0;
	while (tree->type != T_WORD)
	{
		tree = tree->right;
		pipes++;
	}
	return (pipes);
}

int	exec_pipe(t_data *data, t_tree *left, t_tree *right)
{
	int fd[2];
	int	pid_out;
	int	pid_in;

	if (pipe(fd) < 0)
		return (1);
	pid_out = fork();
	if (pid_out < 0)
		return (2);
	if (pid_out == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(find_executable_path(data->path, left->value),
			   left->args_array, data->env_array);
	}

	pid_in = fork();
	if (pid_in < 0)
		return (3);
	if (pid_in == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		execve(find_executable_path(data->path, right->value),
			   right->args_array, data->env_array);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_out, NULL, 0);
	waitpid(pid_in, NULL, 0);
	return (0);
}
 */