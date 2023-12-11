/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_singlesplit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:29:04 by alappas           #+#    #+#             */
/*   Updated: 2023/12/06 20:33:50 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_singlewordlen(char const *str, char c)
{
	int	len;

	len = 0;
	while (*str && *str != c)
	{
		len++;
		str++;
	}
	return (len);
}

int	ft_singlecountwords(char const *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == c)
		{
			count++;
			break ;
		}
		str++;
	}
	return (count);
}

void	*free_singlestrs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		strs[i] = NULL;
		i++;
	}
	free(strs);
	return (NULL);
}

void	iterate_str(char const **str, int count, char c)

{
	if (count == 0)
		(*str) += ft_singlewordlen((*str), c);
	else
		(*str) += ft_singlewordlen((*str), c) + 1;
}

char	**ft_singlesplit(char const *str, char c)
{
	char	**strs;
	int		i;
	int		count;

	if (!str)
		return (NULL);
	count = ft_singlecountwords(str, c);
	strs = malloc(sizeof(char *) * (count + 2));
	if (!strs)
		return (NULL);
	i = 0;
	strs[i] = ft_substr(str, 0, ft_singlewordlen(str, c));
	if (!strs[i])
		return (free_singlestrs(strs));
	iterate_str(&str, count, c);
	if (count == 1)
		strs[++i] = ft_substr(str, 0, ft_strlen(str));
	strs[count + 1] = NULL;
	return (strs);
}
