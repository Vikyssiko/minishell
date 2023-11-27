/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:07:25 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/24 19:05:41 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


// check cd when unset is ready, there is a comment above cd function
void	unset(t_envir **env_list, t_cmd_list *list, int value)

{
	int		i;
	t_envir	*address;
	t_envir	*tmp;

	i = 1;
	if (ft_strcmp(list->value, "unset") != 0)
		return ;
	if (!list->args_array[i])
		return ;
	if (ft_strcmp(list->value, "unset") == 0 && list->args_array[i])
	{
		while (list->args_array[i] != NULL)
		{
			if (!unset_helper(list->args_array[i], value))
			{
				while (((*env_list)) != NULL)
				{
					if ((*env_list)->next)
						address = (*env_list)->next;
					else if ((*env_list)->prev)
						address = (*env_list)->prev;
					tmp = (*env_list)->next;
					if (ft_strcmp((*env_list)->var_name, list->args_array[i]) == 0)
						ft_envdelone((*env_list));
					(*env_list) = tmp;
				}
				(*env_list) = ft_envfirst(address);
			}
			i++;
		}
	}
}

int	unset_helper(char *list_arg, int value)

{
	int	i;

	i = 0;
	while (list_arg[i])
	{
		if (((ft_isalnum(list_arg[i]) || list_arg[i] != '_') && ((!ft_isalpha(list_arg[0])) && list_arg[0] != '_')) || list_arg[i] == '=')
		{
			if (value == 0)
				return (printf("unset: `%s': not a valid identifier\n", list_arg), 1);
			else
				return (1);
		}
		i++;
	}
	return (0);
} 
