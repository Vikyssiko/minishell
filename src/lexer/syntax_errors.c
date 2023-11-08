/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlova <vkozlova@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:35 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/07 14:05:13 by vkozlova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	syntax_errors(t_token *token, t_data *data)
{
	char	*str;
	int		i;

	i = 0;
	while (token)
	{
		str = check_first_token(&data->input_line[i], &i);
		if (str == NULL)
			return (0);
		while (token->type == T_WORD)
			token = token->next;
		if (check_red(token) || check_pipe(token))
			return (1);
		token = token->next;
	}
	return (0);
}

char	*check_token(char *str, int *i)
{
	if (*str == '|')
		return (*i += 1, "|");
	if (*str == '<' && *(str + 1) == '>')
		return (*i += 2, "<>");
	if (*str == '>' && *(str + 1) == '>')
		return (*i += 2, ">>");
	if (*str == '>')
		return (*i += 1, ">");
	if (*str == '<' && *(str + 1) == '<' && *(str + 2) != '>')
		return (*i += 2, "<<");
	if (*str == '<')
		return (*i += 1, "<");
	return (NULL);
}

char	*check_first_token(char *str, int *i)
{
	char	*result;

	while (*str)
	{
		result = check_token(str, i);
		if (result != NULL)
			return (result);
		str++;
		(*i)++;
	}
	return (NULL);
}
