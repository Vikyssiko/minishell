/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlova <vkozlova@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:36 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/07 13:59:25 by vkozlova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
