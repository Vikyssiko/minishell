/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:20:42 by alappas           #+#    #+#             */
/*   Updated: 2023/11/24 19:03:01 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	export(t_envir **env_list, t_envir **export_list,
			t_cmd_list *list, t_data *data)
{
	int		i;
	t_envir	*head_export;
	char	**arg;

	i = 1;
	head_export = (*export_list);
	if (ft_strcmp(list->value, "export") != 0)
		return ;
	if (ft_strcmp(list->value, "export") == 0 && list->args_array[i])
	{
		while (list->args_array[i] != NULL)
		{
			if (!export_helper(list->args_array[i], data))
			{
				arg = ft_singlesplit(list->args_array[i], '=');
				while ((*export_list) != NULL)
				{
					if (ft_strcmp((*export_list)->var_name, arg[0]) == 0)
					{
						if (ft_strcmp(arg[1], "") != 0)
						{
							free((*export_list)->var_value);
							(*export_list)->var_value = ft_strdup(arg[1]);
							check_env(env_list, arg);
						}
						break ;
					}
					(*export_list) = (*export_list)->next;
				}
				if (*export_list == NULL)
				{
					(*export_list) = head_export;
					ft_envadd_back((export_list), ft_envnew(arg));
					if (ft_strcmp(arg[1], "") != 0)
						ft_envadd_back((env_list), ft_envnew(arg));
				}
				(*export_list) = head_export;
				free_2darray(arg);
			}
			i++;
		}
		(*export_list) = sort_export(export_list);
	}
	else if (ft_strcmp(list->value, "export") == 0 && !list->args_array[i])
	{
		print_export((*export_list));
		return ;
	}
}

void	check_env(t_envir **env_list, char **arg)
{
	t_envir	*head;

	head = *env_list;
	while (*env_list)
	{
		if (ft_strcmp((*env_list)->var_name, arg[0]) == 0)
		{
			free((*env_list)->var_value);
			(*env_list)->var_value = ft_strdup(arg[1]);
			break ;
		}
		*env_list = (*env_list)->next;
	}
	if (*env_list == NULL)
	{
		(*env_list) = head;
		ft_envadd_back((env_list), ft_envnew(arg));
	}
	(*env_list) = head;
}

int	export_helper(char *list_arg, t_data *data)
{
	int		i;

	i = 0;
	while (list_arg[i])
	{
		if (((ft_isalnum(list_arg[i]) || list_arg[i] != '_')
				&& ((!ft_isalpha(list_arg[0])) && list_arg[0] != '_')))
		{
			put_to_stderr_and_free("export: `%s': not a valid identifier\n",
				list_arg, data, 1);
			return (1);
		}
		i++;
	}
	return (0);
}
