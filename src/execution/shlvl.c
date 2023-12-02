/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:54:40 by alappas           #+#    #+#             */
/*   Updated: 2023/12/02 22:21:12 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	incr_shell_lvl(t_data *data)
{
    t_envir *env_shlvl;
    char    **shlvl_array;
	int		level;

	level = 0;
	env_shlvl = find_envir_node(data->env_list, "SHLVL");
    if (env_shlvl == NULL)
    {
        shlvl_array = malloc(sizeof(char *) * 2);
        ft_envadd_back((&data->env_list), ft_envnew(shlvl_array));
        free(shlvl_array);
    }
    level = ft_atoi(env_shlvl->var_value) + 1;
	if (level == 1000)
    {
        free((env_shlvl)->var_value);
    }
}
