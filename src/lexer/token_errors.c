/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlova <vkozlova@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:35 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/08 15:07:09 by vkozlova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_pipe(t_token *tmp)
{
	if (tmp->type == T_PIPE
		&& (tmp->next->type != T_WORD || !tmp->prev || tmp->prev->type != T_WORD))
		return (printf("minishell: syntax error near %s\n", \
		"unexpected token `|'"), 1);
	return (0);
}

int	check_red(t_token *token)
{
	if (token->type == T_RED_INP || token->type == T_RED_OUT
		|| token->type == T_APPEND || token->type == T_DELIM)
	{
		if (token->next->type != T_WORD
			|| !token->prev || token->prev->type != T_WORD)
		return (printf("minishell: syntax error near unexpected token `%s'\n",
					   token->word), 1);
	}
//	if (token->type == T_RED_INP && (token->next->type != T_WORD
//			|| (token->prev && token->prev->type != T_WORD)))
//		return (printf("minishell: syntax error near unexpected token `%s'\n",
//				token->word), 1);
//	if (token->type == T_RED_OUT
//		&& (token->next->type != T_WORD || token->prev->type != T_WORD))
//		return (printf("minishell: syntax error near unexpected token `%s'\n",
//				token->word), 1);
//	if (token->type == T_APPEND
//		&& (token->next->type != T_WORD || token->prev->type != T_WORD))
//		return (printf("minishell: syntax error near unexpected token `%s'\n",
//				token->word), 1);
//	if (token->type == T_DELIM && token->next->type != T_WORD)
//		return (printf("minishell: syntax error near unexpected token `%s'\n",
//				token->word), 1);
	return (0);
}
