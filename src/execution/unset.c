/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:07:25 by vkozlova          #+#    #+#             */
/*   Updated: 2023/12/06 19:57:57 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	unset(t_envir **env_list, t_data *data, int value)
{
	int		i;
	t_envir	*tmp;

	i = 1;
	tmp = (*env_list);
	if (!data->list->args_array[i])
		return ;
	while (data->list && data->list->args_array && data->list->args_array[i])
	{
		if (!unset_helper(data->list->args_array[i], value, data))
		{
			while (((tmp)) != NULL)
			{
				if (ft_strcmp((tmp)->var_name, data->list->args_array[i]) == 0)
				{
					tmp = ft_envdelone((tmp));
					(*env_list) = ft_envfirst(tmp);
					tmp = (*env_list);
					break ;
				}
				tmp = tmp->next;
			}
		}
		i++;
	}
}

int	unset_helper(char *list_arg, int value, t_data *data)
{
	int		i;

	i = 0;
	while (list_arg[i])
	{
		if (((ft_isalnum(list_arg[i]) || list_arg[i] != '_')
				&& ((!ft_isalpha(list_arg[0])) && list_arg[0] != '_'))
			|| list_arg[i] == '=')
		{
			if (value == 0)
				put_to_stderr("unset: `%s': not a valid identifier\n",
					list_arg, data, 1);
			return (1);
		}
		i++;
	}
	return (0);
}
