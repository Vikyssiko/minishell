/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlova <vkozlova@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:36 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/06 22:16:53 by vkozlova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// takes the input and trims the spaces and tabs of every 
// word outside the quotes
char	*trim_input(char *input)
{
	char	*str;
	int		i;
	int		j;

	if (!input || !*input)
		return (NULL);
	str = ft_calloc(1, ft_strlen(input) + 1);
	if (!(str))
		exit_shell("Error: malloc failed\n", 1, NULL);
	i = 0;
	j = 0;
	while ((input[i] == ' ' || input[i] == '\t') && input[i])
		i++;
	process_input(input, str, &i, &j);
	i = ft_strlen(str) - 1;
	while (str[i] == ' ' || str[i] == '\t')
		str[i--] = '\0';
	str[j] = '\0';
	return (str);
}

void	process_input(char *input, char *str, int *i, int *j)
{
	while (input[*i])
	{
		while ((input[*i] == ' ' || input[*i] == '\t')
			&& (input[*i + 1] == ' ' || input[*i + 1] == '\t'))
			(*i)++;
		while (in_quotes(input, *i) && input[*i])
			str[(*j)++] = input[(*i)++];
		str[(*j)++] = input[(*i)++];
	}
}

int	ft_is_in_stri(char c, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	is_chr_str(char c, char *str)
{
	if (ft_is_in_stri(c, str) >= 0)
		return (1);
	return (0);
}

int	ft_has_only_digit(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
