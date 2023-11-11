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

//char	*ft_strjoin(char const *s1, char const *s2)
//{
//	char	*result;
//	size_t	len1;
//	size_t	len2;
//
//	if (!s1 || !s2)
//		return (NULL);
//	len1 = ft_strlen(s1);
//	len2 = ft_strlen(s2);
//	result = malloc(sizeof(char) * (len1 + len2 + 1));
//	if (!result)
//		return (NULL);
//	ft_memcpy(result, s1, len1);
//	ft_memcpy(result + len1, s2, len2 + 1);
//	return (result);
//}

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
