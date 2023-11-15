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