/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:36 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/19 18:16:42 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

 char	*find_command_path(t_data *data, t_cmd_list *list)
 {
 	char	*path;
 	char	*command_path;
// 	int	i;
//
// 	i = 0;
 	path = find_envir_variable(data, "PATH=", 5);
 	if (!path)
 		return (NULL);
 	data->path = ft_split(path, ':');
 	if (!data->path)
 		return (NULL);
 	command_path = find_executable_path(data->path, list->value);
//	 printf("COMMAND PATH = %s\n", command_path);
 	if (!command_path)
 	{
 		printf("minishell: %s: command not found\n", list->value);
 		return (NULL);
 	}
// 	printf("Executable_path: %s\n", command_path);
 	// cmd->path = ft_strdup(command_path);
 	// if (paths)
 		// free_2darray(paths);
 	return (command_path);
 }

char	*find_executable_path(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

char	*find_envir_variable(t_data *data, char *var_name, int len)
{
	int	i;

	i = 0;
	while (data->env_array[i])
	{
		if (ft_strncmp(data->env_array[i], var_name, len) == 0)
			return (data->env_array[i] + len);
		i++;
	}
	return (NULL);
}

// void	child(t_data *data)
// {
//     data->pid = fork();
//     if (!data->pid)
//     {
// 		if (execve(data->cmd_list->path, data->cmd_list->args_array,
//		data->path) == -1)
// 			{
// 				perror("execve");
// 				exit(1);
// 			}
//     }
// 	else
// 		wait(NULL);
// }
