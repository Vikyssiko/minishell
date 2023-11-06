/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:45:36 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/04 20:46:03 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ingores all whitespaces before the first character
char	*ignore_spaces(char *input)
{
	while (*input == ' ' || (*input >= 9 && *input <= 13))
		input++;
	return (input);
}

// checks if the string contains only ascii characters
int	is_only_ascii(char *str)
{
	while (*str)
		if (!ft_isascii(*str++))
			return (0);
	return (1);
}

// duplicates a 2d array
char	**dup_2darray(char **array)
{
	int		i;
	char	**dup;

	i = 0;
	while (array[i] != NULL)
		i++;
	dup = (char **)malloc(sizeof(char *) * (i + 1));
	printf("dup_2darray malloc success\n");
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (array[i] != NULL)
	{
		dup[i] = ft_strdup(array[i]);
		if (dup[i] == NULL)
		{
			free_2darray(dup);
			return (NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

// counts the length of a 2d array
int	len_2darray(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

// turnes true if the character is in the string
int	is_char_in_str(char c, char *str)
{
	while (*str)
		if (*str++ == c)
			return (1);
	return (0);
}
