/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:36 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/29 20:10:45 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_command_path(t_data *data, t_cmd_list *list)
{
 	char	*command_path;
	char	*path;

 	path = find_envir_var(data, "PATH");
 	if (!path)
 		return (NULL);
 	data->path = ft_split(path, ':');
 	if (!data->path)
 		return (NULL);
 	command_path = find_executable_path(data->path, list->value);
 	if (!command_path)
 	{
 		printf("minishell: %s: command not found\n", list->value);
 		return (NULL);
 	}
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

//two same functions!
char	*find_envir_var(t_data *data, char *var_name)
{
	t_envir *tmp;

	tmp = data->env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->var_name, var_name) == 0)
			return (tmp->var_value);
		tmp = tmp->next;
	}
	return (NULL);
}

t_envir	*find_envir_node(t_envir *env_list, char *var_name)
{
	t_envir *tmp;

	tmp = env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->var_name, var_name) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
