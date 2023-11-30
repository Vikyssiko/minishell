/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:54:40 by alappas           #+#    #+#             */
/*   Updated: 2023/11/30 15:45:55 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	incr_shell_lvl(t_data *data)
{
    t_envir *env_shlvl;
	int		level;

	level = 0;
	env_shlvl = find_envir_node(data->env_list, "SHLVL");
    level = ft_atoi(env_shlvl->var_value) + 1;
	if (level == 999)
    {
        free((env_shlvl)->var_value);
    }
}
