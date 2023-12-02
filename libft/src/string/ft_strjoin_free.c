/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlova <vkozlova@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:35 by vkozlova          #+#    #+#             */
/*   Updated: 2023/12/02 00:40:45 by vkozlova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;
	int		index;
	int		i;

	index = 0;
	i = 0;
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (result == NULL)
		return (NULL);
	while (s1 && s1[i])
		result[index++] = s1[i++];
	i = 0;
	while (s2 && s2[i])
		result[index++] = s2[i++];
//	if (s1)
//		free(s1);
//	if (s2)
//		free(s2);
	result[index] = '\0';
	return (result);
}
