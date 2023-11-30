/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlova <vkozlova@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 00:28:31 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/30 00:28:31 by vkozlova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *put_str_to_str(char *dest, char *src, t_data *data)
{
	int		dest_i;
	int		src_i;
	int		result_i;
	char	*result;

	dest_i = 0;
	src_i = 0;
	result_i = 0;
	result = malloc(ft_strlen(dest) + ft_strlen(src) - 1);
	if (!result)
		exit_shell("Error: malloc failed", errno, data);
	while (dest && dest[dest_i] && dest[dest_i] != '%')
		result[result_i++] = dest[dest_i++];
	dest_i += 2;
	while (src && src[src_i])
		result[result_i++] = src[src_i++];
	while (dest && dest[dest_i])
		result[result_i++] = dest[dest_i++];
	result[result_i] = '\0';
	return (result);
}