/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlova <vkozlova@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:36 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/07 13:58:59 by vkozlova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_c;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
//	sa.sa_flags = SA_SIGINFO;
//	sigemptyset(&sa.sa_mask);
	rl_catch_signals = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGCHLD, &sa, NULL);
}

void	handle_c(int signo)
{
	int sig;
//
//	sig = gl_signal;
//	printf("I got a signal\n");
	if (signo == SIGCHLD)
	{
		gl_signal = SIGCHLD;
	}
	else if (signo == SIGINT)
	{
		write(1, "\n", 1);
//		gl_signal = SIGINT;
		wait(NULL);
		sig = gl_signal;
		gl_signal = SIGINT;
		if (sig == SIGCHLD)
		{
//			write(1, "\n", 1);
			return ;
		}
//		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signo == SIGQUIT)
	{
//		printf("I got a SIGQUIT signal\n");
//		gl_signal = SIGQUIT;
		wait(NULL);
		if (gl_signal == SIGCHLD)
		{
			write(1, "Quit: 3\n", 8);
			return ;
		}
//		ft_putstr_fd("exit\n", STDERR_FILENO);
//		exit(0);
	}
//	else if (signo == SIGTSTP)
//	{
//		rl_replace_line("", 0);
//		rl_redisplay();
//	}
}

int	handle_d(t_data *data, char *line)
{
	if (line == NULL)
	{
//		rl_on_new_line();
//		rl_redisplay();
		exit_shell_no_free("exit\n", 0, data);
	}
	if (ft_strlen(line) == 0)
	{
		ft_strdel(&line);
		return (1);
	}
	return (0);
}
