/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:50:45 by alappas           #+#    #+#             */
/*   Updated: 2023/12/06 19:58:47 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_export_exist(t_data *data)

{
	int		i;
	t_envir	*export_list;

	i = 0;
	export_list = data->export_list;
	while (export_list)
	{
		export_list = export_list->next;
		i++;
	}
	return (i);
}

int	check_env_exist(t_data *data)

{
	int		i;
	t_envir	*env_list;

	i = 0;
	env_list = data->env_list;
	while (env_list)
	{
		env_list = env_list->next;
		i++;
	}
	return (i);
}

void	create_new_export(t_data *data, char **arg)

{
	data->export_list = ft_envnew(arg);
	if (check_env_exist(data) == 0 && arg[1] && ft_strcmp(arg[1], "") != 0)
		data->env_list = ft_envnew(arg);
}

void	check_export_null(t_envir *head_export, t_envir **env_list,
		t_envir **export_list, char **arg)

{
	if (*export_list == NULL)
	{
		(*export_list) = head_export;
		ft_envadd_back((export_list), ft_envnew(arg));
		if (arg[1] && ft_strcmp(arg[1], "") != 0)
			ft_envadd_back((env_list), ft_envnew(arg));
	}
}
