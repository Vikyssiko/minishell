/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlova <vkozlova@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:06:29 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/13 14:06:29 by vkozlova         ###   ########.fr       */
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

void	echo(t_cmd_list *list)
{
	int		i;
	int		newline;

	i = 1;
	newline = 1;
//	if (ft_strcmp(tree->value, "echo") != 0)
//		return ;
	if (list->args_array[i] && ft_strcmp(list->args_array[i], "-n") == 0)
	{
		newline = 0;
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
