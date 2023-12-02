/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 22:41:03 by alappas           #+#    #+#             */
/*   Updated: 2023/12/02 22:50:45 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_envir	*ft_envnew(char **env_line)
{
	t_envir	*env_list;
	int		i;

	i = 0;
	env_list = malloc(sizeof(t_envir));
	if (!env_list)
		return (NULL);
	if (env_line[i])
		env_list->var_name = ft_strdup(env_line[i]);
	else
		env_list->var_name = NULL;
	i++;
	if (env_line[i])
		env_list->var_value = ft_strdup(env_line[i]);
	else
		env_list->var_value = NULL;
	env_list->next = NULL;
	env_list->prev = NULL;
	return (env_list);
}

void	ft_envadd_back(t_envir **env_list, t_envir *new)
{
	t_envir	*tmp;
	
	if (!env_list)
		return ;
	if (*env_list)
	{
		tmp = ft_envlast(*env_list);
		tmp->next = new;
		new->prev = tmp;
		return ;
	}
	*env_list = new;
}

t_envir	*ft_envlast(t_envir *lst)
{
	t_envir	*node;

	node = lst;
	if (node == NULL)
		return (NULL);
	while (node->next != NULL)
		node = node->next;
	return (node);
}

t_envir	*ft_envfirst(t_envir *lst)
{
	t_envir	*node;

	node = lst;
	if (node != NULL)
	{
		while (node->prev != NULL)
			node = node->prev;
	}
	return (node);
}

void	print_envir(t_envir	*envir)
{
	while (envir)
	{
		printf("%s=%s\n", envir->var_name, envir->var_value);
		envir = envir->next;
	}
}

void	print_export(t_envir *envir)
{
	while (envir)
	{
		if (!envir->var_value)
			printf("declare -x %s\n", envir->var_name);
		else
			printf("declare -x %s=\"%s\"\n", envir->var_name, envir->var_value);
		envir = envir->next;
	}
}

void	ft_envdelone(t_envir *env_list)
{
	t_envir	*next;
	t_envir	*prev;

	if (!env_list)
		return ;
	next = env_list->next;
	prev = env_list->prev;
	if (env_list->var_name)
		free(env_list->var_name);
	if (env_list->var_value)
		free(env_list->var_value);
	if (next != NULL && prev != NULL)
	{
		prev->next = next;
		next->prev = prev;
	}
	else if (prev)
		prev->next = NULL;
	else if (next)
		next->prev = NULL;
	env_list->next = NULL;
	env_list->prev = NULL;
	free(env_list);
}
