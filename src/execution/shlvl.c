/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:54:40 by alappas           #+#    #+#             */
/*   Updated: 2023/12/04 18:28:46 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	incr_shell_lvl(t_data *data)
{
	t_envir *env_shlvl;
	t_envir *exp_shlvl;
	t_envir	*env_head;
	t_envir	*export_head;
	// char    **shlvl_array;
	int		level;

	env_shlvl = find_env_node(data->env_list, "SHLVL");
	exp_shlvl = find_env_node(data->export_list, "SHLVL");
	env_head = data->env_list;
	export_head = data->export_list;
	if (env_shlvl)
		level = ft_atoi(env_shlvl->var_value);
	else
		level = 0;
	if (level > 999)
		printf("bash: warning: shell level (%d) too high, resetting to 1\n", level);
	shlvl_helper(env_shlvl, level, env_head);
	shlvl_helper(exp_shlvl, level, export_head);
}

void    shlvl_helper(t_envir *env_list, int level, t_envir *head)

{
	char	**shlvl_array;
	if (env_list == NULL)
	{
		shlvl_array = malloc(sizeof(char *) * 2);
		shlvl_array[0] = ft_strdup("SHLVL");
		shlvl_array[1] = ft_strdup("1");
		ft_envadd_back(&head, ft_envnew(shlvl_array));
		free(shlvl_array);
	}
	else if (level == 999)
	{
		free(env_list->var_value);
		env_list->var_value = ft_strdup("");
	}
	else if (ft_strcmp(env_list->var_value, "") == 0)
	{
		free(env_list->var_value);
		env_list->var_value = ft_strdup("1");
	}
	else if (level > 999)
	{
		free(env_list->var_value);
		env_list->var_value = ft_strdup("1");
	}
	else
	{
		level += 1;
		ft_strdel(&env_list->var_value);
		env_list->var_value = ft_itoa(level);
	}
}
