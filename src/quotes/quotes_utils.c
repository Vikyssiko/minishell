/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 19:04:19 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/04 19:06:24 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_escaped(char *s, int pos)
{
	int	n;

	n = 0;
	while (pos >= 0 && s[pos] == '\\')
	{
		n++;
		pos--;
	}
	return (n % 2);
}

char	first_quote(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			return (*str);
		str++;
	}
	return (0);
}

int	special_chars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '\\' || str[i] == ';') && !in_quotes(str, i))
		{
			printf("minishell: we should not handle `%c'\n", str[i]);
			return (1);
		}
		i++;
	}
	return (0);
}
