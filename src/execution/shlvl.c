/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:54:40 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/04 20:55:26 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// else
// 	export(&(*data).env_list, "SHLVL", "1");
void	incr_shell_lvl(t_data *data)
{
	char	*shlvl;
	int		level;

	level = 0;
	shlvl = find_envir_variable(data, "SHLVL", ft_strlen("SHLVL"));
	if (shlvl)
	{
		level = ft_atoi(shlvl);
		level++;
		if (level <= 999)
			shlvl = ft_itoa(level);
		else if (level == 1000)
			shlvl = ft_strdup("\n");
		else
		{
			level = 1;
			shlvl = ft_strdup("1");
		}
	}
	free(shlvl);
}

// void	export(t_data **data, char *var_name, char *var_value)
// {
// 	t_envir	*new_envir;

// 	new_envir = (t_envir *)malloc(sizeof(t_envir));
// 	if (!new_envir)
// 		return ;
// 	new_envir->var_name = ft_strdup(var_name);
// 	new_envir->var_value = ft_strdup(var_value);
// 	new_envir->count = ft_strlen(var_value);
// 	new_envir->next = NULL;
// 	new_envir->prev = NULL;
// 	if (*env_list)
// 	{
// 		t_envir *last_envir = *env_list;
// 		while (last_envir->next)
// 			last_envir = last_envir->next;
// 		last_envir->next = new_envir;
// 		new_envir->prev = last_envir;
// 	}
// 	else
// 		*env_list = new_envir;
// }