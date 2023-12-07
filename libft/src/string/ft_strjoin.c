/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:35 by vkozlova          #+#    #+#             */
/*   Updated: 2023/12/05 22:38:30 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"
#include "../../../include/minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	int		index;
	int		i;

	if (!s1 && !s2)
		return (NULL);
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
	result[index] = '\0';
	return (result);
}
