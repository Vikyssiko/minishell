/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:36 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/07 00:11:57 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	odd_quote(char *str)
{
	int	single_quotes;
	int	double_quotes;
	int	i;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' && double_quotes % 2 == 0)
			single_quotes++;
		if (str[i] == '\"' && single_quotes % 2 == 0)
			double_quotes++;
		i++;
	}
	if (double_quotes % 2 != 0 || single_quotes % 2 != 0)
	{
		write(2, "We should not handle unclosed quotes\n", 37);
		return (1);
	}
	return (0);
}

int	in_quotes(char *s, int pos)
{
	int	double_quotes;
	int	single_quotes;
	int	i;

	double_quotes = 0;
	single_quotes = 0;
	i = 0;
	while (i <= pos)
	{
		if (s[i] == '\"' && single_quotes % 2 == 0)
			double_quotes++;
		if (s[i] == '\'' && double_quotes % 2 == 0)
			single_quotes++;
		i++;
	}
	if (double_quotes % 2 != 0 || single_quotes % 2 != 0)
		return (1);
	return (0);
}

int	in_single_quotes(char *s, int pos)
{
	int	double_quotes;
	int	single_quotes;
	int	i;

	double_quotes = 0;
	single_quotes = 0;
	i = 0;
	while (i <= pos)
	{
		if (s[i] == '\"' && single_quotes % 2 == 0)
			double_quotes++;
		if (s[i] == '\'' && double_quotes % 2 == 0)
			single_quotes++;
		i++;
	}
	if (single_quotes % 2 != 0)
		return (1);
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
