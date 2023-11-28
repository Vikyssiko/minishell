/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:06:29 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/28 01:12:20 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_without_quotes(char *str)
{
	int		i;
	char	quote;
	int		closed;

	i = 0;
	closed = 1;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && closed)
		{
			quote = str[i++];
			closed = 0;
		}
		if (str[i] && str[i] != quote)
			printf("%c", str[i++]);
		if (str[i] == quote)
		{
			closed = 1;
			i++;
		}
	}
}

// should it be in a different process?
void	echo(t_cmd_list *list)
{
	int		i;
	int		newline;

	i = 1;
	newline = 1;
//	if (ft_strcmp(tree->value, "echo") != 0)
//		return ;
	if (list->args_array[i] && ft_strncmp(list->args_array[i], "-n", 2) == 0)
	{
		newline = 0;
		while (ft_strncmp(list->args_array[i], "-n", 2) == 0)
			i++;
	}
	while (list->args_array[i])
	{
		print_without_quotes(list->args_array[i]);
		i++;
		if (list->args_array[i])
			printf(" ");
	}
	if (newline)
		printf("\n");
}
