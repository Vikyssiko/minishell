/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:36 by vkozlova          #+#    #+#             */
/*   Updated: 2023/12/02 22:26:09 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_data(t_data **data, char **envp)
{
	*data = malloc(sizeof(t_data));
	if (!*data)
		exit(EXIT_FAILURE);
	(*data)->env_list = create_env_list((envp));
	(*data)->export_list = create_export_list((envp));
	(*data)->path = NULL;
	(*data)->list = NULL;
	(*data)->token_list = NULL;
	(*data)->input_line = NULL;
	(*data)->input_minishell = "minishell>> ";
//	(*data)->pid = getpid();
	(*data)->curr_dir = getcwd(NULL, 0);
	save_envir((*data), envp);
	// incr_shell_lvl(*data);
}
