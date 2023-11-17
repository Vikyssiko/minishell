/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlova <vkozlova@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:35 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/07 14:00:20 by vkozlova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_token(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!new || !head)
		return ;
	if (*head)
	{
		tmp = *head;
		while (tmp->next)
		{
			tmp->next->prev = tmp;
			tmp = tmp->next;
		}
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
	else
	{
		*head = new;
		new->prev = NULL;
		new->next = NULL;
	}
}

t_redir	*create_redir_token(t_token *redir_token, t_token *word)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	redir->redir_token = redir_token;
	redir->redir_word = word;
	return (redir);
}

void	add_redir_token(t_redir **head, t_redir *redir)
{
	t_redir *tmp;

	if (!redir || !head)
		return ;
	if (*head)
	{
		tmp = *head;
		while (tmp->next)
		{
//			tmp->next->prev = tmp;
			tmp = tmp->next;
		}
		tmp->next = redir;
//		redir->prev = tmp;
		redir->next = NULL;
	}
	else
	{
		*head = redir;
//		redir->prev = NULL;
		redir->next = NULL;
	}
//	redir_token->type = redir_token->type;
//	redir_token->word = word->word;
}
