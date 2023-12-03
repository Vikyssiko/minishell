/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:36 by vkozlova          #+#    #+#             */
/*   Updated: 2023/12/02 23:13:46 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_shell(char *message, int exit_code, t_data *data)
{
//	free_data(data);
//	printf("exit\n");
//	perror(message);
	ft_putstr_fd(message, STDERR_FILENO);
	free(message);
//	ft_putstr_fd("\n", STDERR_FILENO);
//	printf("%i\n", data->exit_status);

	//static??
//	data->exit_status = exit_code;
	if (data && data->list)
		free_list(data->list);
	free_data(data);
	exit(exit_code);
}

void	exit_shell_no_free(char *message, int exit_code, t_data *data)
{
//	printf("%i\n", data->exit_status);

//	printf("exit\n");
//	perror(message);
	ft_putstr_fd(message, STDERR_FILENO);
//	free(message);
//	ft_putstr_fd("\n", STDERR_FILENO);
//	data->exit_status = exit_code;
//	printf("%i\n", exit_code);
	if (data && data->list)
		free_list(data->list);
	free_data(data);
	exit(exit_code);
}
