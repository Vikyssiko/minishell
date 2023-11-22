/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:36 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/22 01:04:42 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	save_envir(t_data *data, char **env_str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env_str[j])
		j++;
	data->env_array = malloc(sizeof(char *) * (j + 1));
	while (env_str[i])
	{
		data->env_array[i] = ft_strdup(env_str[i]);
		i++;
	}
	data->env_array[i] = NULL;
}

t_envir	*create_env_list(char **envp)

{
	t_envir	*env_list;
	char	**envs;
	int		i;

	i = 1;
	while (envp[i])
	{
		envs = ft_split(envp[i], '=');
		if (i == 1)
			env_list = ft_envnew(envs);
		else
			ft_envadd_back(&env_list, ft_envnew(envs));
		free_2darray(envs);
		i++;
	}
	return (env_list);
}

// t_envir	*create_export_list(char **envp)

// {
// 	int ascii;

// 	ascii = 'A';
// 	while (ascii != '_')
// 	{
		
// 	}
// }
