/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlova <vkozlova@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:36 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/07 13:58:39 by vkozlova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_data(t_data **data, char **envp)
{
	*data = malloc(sizeof(t_data));
	if (!*data)
		exit(EXIT_FAILURE);
	(*data)->env_list = NULL;
	(*data)->token_list = NULL;
	(*data)->input_line = NULL;
	(*data)->input_minishell = "minishell>> ";
	(*data)->pid = getpid();
	(*data)->curr_dir = getcwd(NULL, 0);
	save_envir((*data), envp);
	incr_shell_lvl(*data);
}
