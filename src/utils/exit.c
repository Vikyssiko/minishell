/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlova <vkozlova@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:36 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/07 13:57:37 by vkozlova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_shell(char *message, int exit_code, t_data *data)
{
	free_data(data);
//	printf("exit\n");
//	perror(message);
	ft_putstr_fd(message, STDERR_FILENO);
	free(message);
//	ft_putstr_fd("\n", STDERR_FILENO);
//	printf("%i\n", exit_code);

	//static??
//	data->exit_status = exit_code;
	exit(exit_code);
}

void	exit_shell_no_free(char *message, int exit_code, t_data *data)
{
	free_data(data);
//	printf("exit\n");
//	perror(message);
	ft_putstr_fd(message, STDERR_FILENO);
//	free(message);
//	ft_putstr_fd("\n", STDERR_FILENO);
//	data->exit_status = exit_code;
//	printf("%i\n", exit_code);
	exit(exit_code);
}
