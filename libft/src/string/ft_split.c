/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:45:10 by alappas           #+#    #+#             */
/*   Updated: 2023/11/21 01:06:08 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_wordlen(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

int	ft_countwords(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			s += ft_wordlen(s, c);
		}
		else
			s++;
	}
	return (count);
}

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
	{
		free(strs[i]);
		strs[i] = NULL;
		i++;
	}
	free(strs);
}

int	fill_in_the_word(char const *s, char c, int i, char	**strs)
{
	strs[i] = ft_substr(s, 0, ft_wordlen(s, c));
	if (!strs[i])
	{
		free_strs(strs);
		return (0);
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		i;
	int		count;

	if (!s)
		return (NULL);
	count = ft_countwords(s, c);
	strs = malloc(sizeof(char *) * (count + 1));
	if (!strs)
		return (NULL);
	strs[count] = NULL;
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			if (fill_in_the_word(s, c, i, strs) == 0)
				return (NULL);
			s += ft_wordlen(s, c);
			i++;
		}
		else
			s++;
	}
	return (strs);
}
