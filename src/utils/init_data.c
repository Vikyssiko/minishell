/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:36 by vkozlova          #+#    #+#             */
/*   Updated: 2024/02/16 21:25:19 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**create_envp(void)
{
	char	**envp;

	envp = (char **)malloc(sizeof(char *) * 3);
	envp[0] = ft_strdup(ft_strjoin("PWD=", getcwd(NULL, 0)));
	envp[1] = ft_strdup("SHLVL=1");
	envp[2] = ft_strdup("_=./minishell");
	envp[3] = NULL;
	return (envp);
}

void	init_data(t_data **data, char **envp)
{
	*data = malloc(sizeof(t_data));
	if (!*data)
		exit(EXIT_FAILURE);
	(*data)->path = NULL;
	(*data)->in = -1;
	(*data)->out = -1;
	(*data)->exit_status = 0;
	(*data)->list = NULL;
	(*data)->token_list = NULL;
	(*data)->input_line = NULL;
	(*data)->new_env_array = NULL;
	(*data)->input_minishell = "minishell>> ";
	if (*envp == NULL)
		envp = create_envp();
	save_envir((*data), envp);
	(*data)->env_list = create_env_list((((*data)->env_array)));
	(*data)->export_list = create_export_list((*data)->env_array);
	incr_shell_lvl(*data);
}
