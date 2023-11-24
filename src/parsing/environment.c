/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:36 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/23 23:39:47 by alappas          ###   ########.fr       */
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

	i = 0;
	envs = NULL;
	while (envp[i])
	{
		envs = ft_singlesplit(envp[i], '=');
		if (i == 0)
			env_list = ft_envnew(envs);
		else
			ft_envadd_back(&env_list, ft_envnew(envs));
		free_2darray(envs);
		i++;
	}
	return (env_list);
}
t_envir	*sort_export(t_envir **export)

{
	t_envir	*head;

	head = (*export);
	while ((*export)->next != NULL)
	{
		if (strcmp((*export)->var_name, (*export)->next->var_name) > 0)
		{
			(*export) = swap_env((*export), (*export)->next);
			(*export) = ft_envfirst((*export));
		}
		else
			(*export) = (*export)->next;
	}
	return (head);
}

t_envir	*create_export_list(char **envp)

{
	t_envir *export;
	t_envir *head;

	export = create_env_list(envp);
	head = export;
	sort_export(&export);
	export = head;
	return (export);
}

t_envir *swap_env(t_envir *first, t_envir *second)

{
	char *name;
	char *value;

	name = first->var_name;
	value = first->var_value;
	first->var_name = first->next->var_name;
	first->var_value = first->next->var_value;
	first->next->var_name = name;
	first->next->var_value = value;
	first = second;
	return (first);
}