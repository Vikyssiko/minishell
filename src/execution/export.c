/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:20:42 by alappas           #+#    #+#             */
/*   Updated: 2023/11/20 22:15:38 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "../../include/minishell.h"

void    export(t_data *data, t_cmd_list *list)

{
	int		i;
	int		j;
	int		len;

	i = 1;
	if (ft_strcmp(list->value, "export") != 0)
		return ;
	if (ft_strcmp(list->value, "export") == 0 && list->args_array[i])
	{
		while (list->args_array[i] != NULL)
		{
			if (!unset_export_helper(list->args_array[i]))
			{
				j = 0;
				len = ft_strlen(list->args_array[i]);
				while (data->env_array[j] != NULL)
				{
					if (ft_strncmp(data->env_array[j], list->args_array[i], len) == 0
						&& data->env_array[j][len] == '=' && (data->env_array[j][0] != '_' && data->env_array[j][1] != '='))
					{
						free(data->env_array[j]);
						data->env_array[j] = ft_strdup(list->args_array[i]);
						break ;
					}
					j++;
				}
				data->env_array[j] = ft_strdup(list->args_array[i]);
			}
			i++;
		}
	}
	else if (ft_strcmp(list->value, "export") == 0 && !list->args_array[i])
	{
		printf("Hey!\n");
		return ;
	}
}