/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 22:41:03 by alappas           #+#    #+#             */
/*   Updated: 2023/11/21 20:37:22 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_envir	*ft_envnew(char **env_line)
{
	t_envir	*env_list;

	env_list = malloc(sizeof(t_envir));
	if (!env_list)
		return (NULL);
	if (env_line[0])
		env_list->var_name = ft_strdup(env_line[0]);
	else
		env_list->var_name = NULL;
	if (env_line[1])
		env_list->var_value = ft_strdup(env_line[1]);
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
	if (env_list)
	{
		if (*env_list)
		{
			tmp = ft_envlast(*env_list);
			tmp->next = new;
			new->prev = tmp;
			return ;
		}
	}
	*env_list = new;
}

t_envir	*ft_envlast(t_envir *lst)

{
	t_envir	*node;

	node = lst;
	if (node != NULL)
	{
		while (node->next != NULL)
			node = node->next;
	}
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

#include "libft.h"

void	ft_envdelone(t_envir *env_list)

{
	t_envir	*next;
	t_envir	*prev;

	next = NULL;
	prev = NULL;
	if (env_list->next)
		next = env_list->next;
	if (env_list->prev)
		prev = env_list->prev;
	if (env_list)
	{
		if (env_list->var_name)
			free(env_list->var_name);
		if (env_list->var_value)
			free(env_list->var_value);
		if (next && prev)
			prev->next = next;
		if (prev)
			next->prev = prev;
		else if (!prev)
			next->prev = NULL;
		free(env_list);
	}
}
