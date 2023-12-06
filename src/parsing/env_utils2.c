/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:48:05 by alappas           #+#    #+#             */
/*   Updated: 2023/12/06 21:09:42 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

t_envir	*ft_envfirst(t_envir *lst)
{
	t_envir	*node;

	node = lst;
	if (node == NULL)
		return (NULL);
	while (node->prev != NULL)
		node = node->prev;
	return (node);
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

int	ft_lilen(t_envir *env_list)

{
	int		i;
	t_envir	*tmp;

	i = 0;
	tmp = env_list;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
