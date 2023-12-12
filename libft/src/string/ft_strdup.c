/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlova <vkozlova@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:35 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/11 20:48:23 by vkozlova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strdup(const char *s1)
{
	int		index;
	char	*s2;
	char	*s1_ptr;

	s1_ptr = (char *)s1;
	index = 0;
	s2 = malloc(ft_strlen(s1_ptr) * sizeof(char) + 1);
	if (!s2)
		return (NULL);
	while (s1 && s1[index])
	{
		s2[index] = s1[index];
		index++;
	}
	s2[index] = '\0';
	return (s2);
}
