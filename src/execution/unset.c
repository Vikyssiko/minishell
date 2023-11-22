/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:07:25 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/21 20:39:28 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


// check cd when unset is ready, there is a comment above cd function
void	unset(t_envir **env_list, t_cmd_list *list)

{
	int		i;
	t_envir	*tail;
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
			if (!unset_export_helper(list->args_array[i]))
			{
				tail = ft_envlast((*env_list));
				while ((*env_list) != NULL)
				{
					tmp = (*env_list)->next;
					if (ft_strcmp((*env_list)->var_name, list->args_array[i]) == 0
						&& (ft_strcmp((*env_list)->var_name, "_") != 0))
						ft_envdelone((*env_list));
					(*env_list) = tmp;
				}
				(*env_list) = ft_envfirst(tail);
			}
			i++;
		}
	}
}

int	unset_export_helper(char *list_arg)

{
	int	i;

	i = 0;
	while (list_arg[i])
	{
		if (((ft_isalnum(list_arg[i]) || list_arg[i] != '_') && ((!ft_isalpha(list_arg[0])) && list_arg[0] != '_')) || list_arg[i] == '=')
			return (printf("unset: `%s': not a valid identifier\n", list_arg), 1);
		i++;
	}
	return (0);
} 

