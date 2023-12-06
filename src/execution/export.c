/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:20:42 by alappas           #+#    #+#             */
/*   Updated: 2023/12/06 19:58:51 by alappas          ###   ########.fr       */
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
	if (list->args_array[i])
	{
		while (list->args_array[i] != NULL)
		{
			if (!export_helper(list->args_array[i], data))
			{
				arg = ft_singlesplit(list->args_array[i], '=');
				check_export(data, export_list, &head_export, arg);
				check_export_null(head_export, env_list, export_list, arg);
				check_env(data, env_list, arg);
				(*export_list) = head_export;
				free_2darray(arg);
			}
			i++;
		}
		(*export_list) = sort_export(export_list);
	}
	else
		print_export((*export_list));
}

void	check_export(t_data *data, t_envir **export_list,
		t_envir **head_export, char **arg)

{
	if (check_export_exist(data) == 0)
	{
		data->export_list = ft_envnew(arg);
		(*head_export) = data->export_list;
		if (check_env_exist(data) == 0 && arg[1] && ft_strcmp(arg[1], "") != 0)
			data->env_list = ft_envnew(arg);
		return ;
	}
	while ((*export_list) != NULL)
	{
		if (ft_strcmp((*export_list)->var_name, arg[0]) == 0)
		{
			if (arg[1])
			{
				free((*export_list)->var_value);
				(*export_list)->var_value = trim_input_env(arg[1]);
			}
			break ;
		}
		(*export_list) = (*export_list)->next;
	}
}

void	check_env(t_data *data, t_envir **env_list, char **arg)
{
	t_envir	*head;
	t_envir	*tmp;

	head = *env_list;
	tmp = *env_list;
	if (!arg[1])
		return ;
	if (check_env_exist(data) == 0 && arg[1] && ft_strcmp(arg[1], "") != 0)
	{
		data->env_list = ft_envnew(arg);
		return ;
	}
	while (tmp)
	{
		if (ft_strcmp((tmp)->var_name, arg[0]) == 0)
		{
			free((tmp)->var_value);
			(tmp)->var_value = trim_input_env(arg[1]);
			break ;
		}
		tmp = (tmp)->next;
	}
	if (tmp == NULL && arg[1] && ft_strcmp(arg[1], "") != 0)
		ft_envadd_back((env_list), ft_envnew(arg));
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
			put_to_stderr("minishell: export: `%s': "
				"not a valid identifier\n", list_arg, data, 1);
			return (1);
		}
		i++;
	}
	return (0);
}
