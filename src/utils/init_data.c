/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:36 by vkozlova          #+#    #+#             */
/*   Updated: 2023/12/05 22:35:15 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_data(t_data **data, char **envp)
{
	*data = malloc(sizeof(t_data));
	if (!*data)
		exit(EXIT_FAILURE);
	(*data)->path = NULL;
//	(*data)->stdin = 0;
//	(*data)->stdout = 0;
	(*data)->exit_status = 0;
	(*data)->list = NULL;
	(*data)->token_list = NULL;
	(*data)->input_line = NULL;
	(*data)->new_env_array = NULL;
	(*data)->input_minishell = "minishell>> ";
	(*data)->curr_dir = getcwd(NULL, 0);
	save_envir((*data), envp);
	(*data)->env_list = create_env_list((((*data)->env_array)));
	(*data)->export_list = create_export_list((*data)->env_array);
	incr_shell_lvl(*data);
}
