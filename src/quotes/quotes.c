/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlova <vkozlova@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:36 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/06 21:37:22 by vkozlova         ###   ########.fr       */
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
		if (str[i] == '\'' && double_quotes % 2 != 1)
			single_quotes++;
		if (str[i] == '\'' && single_quotes % 2 != 1)
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
		if (s[i] == '\"' && (i == 0 || !is_escaped(s, i - 1))
			&& single_quotes % 2 == 0)
			double_quotes++;
		if (s[i] == '\'' && (i == 0 || single_quotes % 2 != 0
				|| !is_escaped(s, i - 1))
			&& double_quotes % 2 == 0)
			single_quotes++;
		i++;
	}
	if (double_quotes % 2 != 0 || single_quotes % 2 != 0)
		return (1);
	return (0);
}

// int	last_pipe(char *str, int pos)
// {
// 	while (pos > 0 && (str[pos] == ' ' || str[pos] == '\n'))
// 		pos--;
// 	if (pos > 0 && str[pos] == '|' && !special_chars(str))
// 	{
// 		pos = 0;
// 		while (str[pos] && (str[pos] != ' ' || str[pos] == '\n'))
// 			pos++;
// 		if (str[pos] != '|')
// 		{
// 			while (str[pos] && (str[pos] != '|' || !special_chars(str) ||
// 				inside_paired_quotes(str, pos)))
// 				pos++;
// 			if (!str[pos] && str[pos + 1])
// 				return (1);
// 			else
// 				pos++;
// 			while (str[pos] && (str[pos] == ' ' || str[pos] == '\n'))
// 				pos++;
// 			if (str[pos] != '|')
// 				return (1);
// 		}
// 	}
// 	return (0);
// }
