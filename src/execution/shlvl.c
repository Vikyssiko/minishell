/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:54:40 by alappas           #+#    #+#             */
/*   Updated: 2023/12/06 20:01:45 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	incr_shell_lvl(t_data *data)
{
	t_envir	*env_shlvl;
	t_envir	*exp_shlvl;
	int		level;
	char	*str;

	env_shlvl = find_env_node(data->env_list, "SHLVL");
	exp_shlvl = find_env_node(data->export_list, "SHLVL");
	if (env_shlvl)
		level = ft_atoi(env_shlvl->var_value);
	else
		level = 0;
	if (level > 999)
	{
		str = ft_itoa(level);
		put_to_stderr("minishell: warning: shell level (%s) "
			"too high, resetting to 1\n", str, data, 0);
		free(str);
	}
	shlvl_helper(env_shlvl, level, data->env_list);
	shlvl_helper(exp_shlvl, level, data->export_list);
}

void	shlvl_helper(t_envir *env_list, int level, t_envir *head)

{
	char	**shlvl_array;

	if (env_list == NULL)
	{
		shlvl_array = malloc(sizeof(char *) * 2);
		shlvl_array[0] = ft_strdup("SHLVL");
		shlvl_array[1] = ft_strdup("1");
		ft_envadd_back(&head, ft_envnew(shlvl_array));
		free(shlvl_array[0]);
		free(shlvl_array[1]);
		free(shlvl_array);
	}
	else if (level >= 999 || ft_strcmp(env_list->var_value, "") == 0)
	{
		free(env_list->var_value);
		if (level == 999)
			env_list->var_value = ft_strdup("");
		else
			env_list->var_value = ft_strdup("1");
	}
	else
	{
		level += 1;
		ft_strdel(&env_list->var_value);
		env_list->var_value = ft_itoa(level);
	}
}
