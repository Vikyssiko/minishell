/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:07:25 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/19 23:16:50 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


// check cd when unset is ready, there is a comment above cd function
void	unset(t_data *data, t_cmd_list *list)

{
	int		i;
	int		j;
	int		len;

	i = 1;
	if (ft_strcmp(list->value, "unset") != 0)
		return ;
	if (!list->args_array[i])
		return ;
	if (ft_strcmp(list->value, "unset") == 0 && list->args_array[i])
	{
		while (list->args_array[i] != NULL)
		{
			if (!unset_helper(list->args_array[i]))
			{
				j = 0;
				len = ft_strlen(list->args_array[i]);
				while (data->env_array[j] != NULL)
				{
					if (ft_strncmp(data->env_array[j], list->args_array[i], len) == 0
						&& data->env_array[j][len] == '=' && (data->env_array[j][0] != '_' && data->env_array[j][1] != '='))
					{
						free(data->env_array[j]);
						while (data->env_array[j + 1] != NULL)
						{
							data->env_array[j] = data->env_array[j + 1];
							j++;
						}
						data->env_array[j] = NULL;
					}
					j++;
				}
			}
			i++;
		}
	}
}

int	unset_helper(char *tree_arg)

{
	int	i;

	i = 0;
	while (tree_arg[i])
	{
		if (((ft_isalnum(tree_arg[i]) || tree_arg[i] != '_') && ((!ft_isalpha(tree_arg[0])) && tree_arg[0] != '_')) || tree_arg[i] == '=')
			return (printf("unset: `%s': not a valid identifier\n", tree_arg), 1);
		i++;
	}
	return (0);
}

