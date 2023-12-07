/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:36 by vkozlova          #+#    #+#             */
/*   Updated: 2023/12/05 23:18:47 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_shell(char *message, int exit_code, t_data *data)
{
	ft_putstr_fd(message, STDERR_FILENO);
	free(message);
	free_data(data);
	exit(exit_code);
}

void	exit_shell_no_free(char *message, int exit_code, t_data *data)
{
	ft_putstr_fd(message, STDERR_FILENO);
	free_data(data);
	exit(exit_code);
}

void	exit_shell_no_mes(int exit_code, t_data *data)
{
	free_data(data);
	exit(exit_code);
}
