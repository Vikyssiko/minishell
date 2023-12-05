/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_singlesplit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:29:04 by alappas           #+#    #+#             */
/*   Updated: 2023/12/02 22:51:43 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_singlewordlen(char const *s, char c)
{
    int len;
    
    len = 0;
    while (*s && *s != c)
    {
        len++;
        s++;
    }
    return len;
}

int	ft_singlecountwords(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s == c)
		{
			count++;
            break ;
		}
		else
			s++;
	}
	return (count);
}

static void	*free_singlestrs(char **strs)
{
    int i;
    
    i = 0;
    while (strs[i])
    {
        free(strs[i]);
        strs[i] = NULL;
        i++;
    }
    free(strs);
    return NULL;
}

char    **ft_singlesplit(char const *s, char c)
{
    char	**strs;
	int		i;
	int		count;

    if (!s)
		return (NULL);
	count = ft_singlecountwords(s, c);
    strs = malloc(sizeof(char *) * (count + 2));
    if (!strs)
		return (NULL);
	i = 0;
    while (*s)
	{
		if (*s != c)
		{
			strs[i] = ft_substr(s, 0, ft_singlewordlen(s, c));
			if (!strs[i])
			{
				free_singlestrs(strs);
				return (NULL);
			}
			s += ft_singlewordlen(s, c) + 1;
			i++;
			strs[i] = ft_substr(s, 0, ft_strlen(s));
            break ;
		}
		else
			s++;
	}
	strs[count + 1] = NULL;
	return (strs);
}