/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:50:43 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/04 20:51:03 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	init_data(&(data), envp);
	handle_signal();
	start_loop(data);
	free_data(data);
	return (0);
}
//int fd;
// if (read(0, NULL, 0) == -1)
// 	return (0);
// if ((fd = dup(0)) == -1)
// 	return (0);
// close(fd);