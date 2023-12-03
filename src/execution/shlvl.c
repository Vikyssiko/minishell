/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:54:40 by alappas           #+#    #+#             */
/*   Updated: 2023/12/03 22:34:37 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	incr_shell_lvl(t_data *data)
{
    t_envir *env_shlvl;
    char    **shlvl_array;
	int		level;

	env_shlvl = find_env_node(data->env_list, "SHLVL");
    level = ft_atoi(env_shlvl->var_value);
    if (env_shlvl == NULL)
    {
        shlvl_array = malloc(sizeof(char *) * 2);
        ft_envadd_back((&data->env_list), ft_envnew(shlvl_array));
        free(shlvl_array);
    }
    else
    {
        level += 1;
        ft_strdel(&env_shlvl->var_value);
        env_shlvl->var_value = ft_itoa(level);
    }
	if (level == 1000)
    {
        free((env_shlvl)->var_value);
    }
}
// 	level = 0;
// 	shlvl = find_env_var(data, "SHLVL", ft_strlen("SHLVL"));
// 	if (shlvl)
// 	{
// 		level = ft_atoi(shlvl);
// 		level++;
// 		if (level <= 999)
// 			shlvl = ft_itoa(level);
// 		else if (level == 1000)
// 			shlvl = ft_strdup("\n");
// 		else
// 		{
// 			level = 1;
// 			shlvl = ft_strdup("1");
// 		}
// 	}
// 	free(shlvl);
// }
