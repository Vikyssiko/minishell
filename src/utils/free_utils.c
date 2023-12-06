/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:34:29 by alappas           #+#    #+#             */
/*   Updated: 2023/12/06 20:35:43 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_envir(t_envir *envir)
{
	t_envir	*tmp;

	if (!envir)
		return ;
	tmp = envir;
	if (tmp->var_name)
	{
		free(tmp->var_name);
		tmp->var_name = NULL;
	}
	if (tmp->var_value)
	{
		free(tmp->var_value);
		tmp->var_value = NULL;
	}
	free(tmp);
}

void	free_2darray(char **array)
{
	int	i;

	i = -1;
	if (!array)
		return ;
	while (array[++i])
		ft_strdel(&array[i]);
	free(array);
	array = NULL;
}

void	ft_envclear(t_envir **env_list)

{
	t_envir	*head;

	while ((*env_list))
	{
		head = (*env_list)->next;
		if ((*env_list)->var_name)
		{
			free((*env_list)->var_name);
			(*env_list)->var_name = NULL;
		}
		if ((*env_list)->var_value)
		{
			free((*env_list)->var_value);
			(*env_list)->var_value = NULL;
		}
		free((*env_list));
		(*env_list) = NULL;
		(*env_list) = head;
	}
}
