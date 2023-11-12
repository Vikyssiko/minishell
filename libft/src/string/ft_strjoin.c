/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlova <vkozlova@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:35 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/11 21:03:31 by vkozlova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"
#include "../../../include/minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	s1_size;
	size_t	s2_size;
	int		index;

	index = 0;
	s1_size = ft_strlen((char *)s1);
	s2_size = ft_strlen((char *)s2);
	result = malloc(s1_size + s2_size + 1);
	if (result == NULL)
		return (NULL);
	while (s1 && *s1)
	{
		result[index++] = *s1;
		s1++;
	}
	while (s2 && *s2)
	{
		result[index++] = *s2;
		s2++;
	}
	result[index] = '\0';
	return (result);
}
