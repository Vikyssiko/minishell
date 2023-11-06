/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 19:04:28 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/04 19:05:45 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	odd_quote(char *str, t_data *data)
{
	char	first_q;
	int		i;

	i = 0;
	first_q = first_quote(str);
	if (first_q == '\'' && closed_singlequotes(str))
		data->single_quote = 1;
	else if (first_q == '\"' && closed_doublequotes(str))
		data->double_quote = 1;
	else if (first_q == '\0')
		return (0);
	else
	{
		write(2, "We should not handle unclosed quotes\n", 37);
		return (1);
	}
	return (0);
}

int	closed_singlequotes(char *str)
{
	int	single_quote;

	single_quote = 0;
	while (*str)
	{
		if (*str == '\'')
			single_quote++;
		str++;
	}
	return (single_quote % 2 == 0);
}

int	closed_doublequotes(char *str)
{
	int	double_quote;

	double_quote = 0;
	while (*str)
	{
		if (*str == '\"')
			double_quote++;
		str++;
	}
	return (double_quote % 2 == 0);
}

int	in_quotes(char *s, int pos)
{
	int	quotes1;
	int	quotes2;
	int	i;

	quotes1 = 0;
	quotes2 = 0;
	i = 0;
	while (i <= pos)
	{
		if (s[i] == 34 && (i == 0 || !is_escaped(s, i - 1))
			&& quotes2 % 2 == 0)
			quotes1++;
		if (s[i] == 39 && (i == 0 || quotes2 % 2 != 0 || !is_escaped(s, i - 1))
			&& quotes1 % 2 == 0)
			quotes2++;
		i++;
	}
	if (quotes1 % 2 != 0 || quotes2 % 2 != 0)
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
