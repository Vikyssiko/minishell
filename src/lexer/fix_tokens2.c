/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_tokens2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlova <vkozlova@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:35 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/07 14:03:05 by vkozlova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	fix_tokens(t_token **head)
{
	find_ortokens(head);
	find_andtokens(head);
	find_inout(head);
}

void	find_append(t_token *current)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = current;
	if (tmp->type == T_RED_OUT && tmp->next->type == T_RED_OUT)
	{
		tmp->type = T_APPEND;
		ft_strdel(&tmp->word);
		tmp->word = ft_strdup(">>");
		tmp2 = tmp->next;
		tmp->next = tmp->next->next;
		tmp->next->prev = tmp;
		ft_strdel(&tmp2->word);
		free(tmp2);
	}
}

void	find_inout(t_token **head)
{
	t_token	*current;
	t_token	*tmp;
	t_token	*tmp2;

	current = *head;
	while (current != NULL)
	{
		tmp = current;
		if (tmp->type == T_RED_INP && tmp->next->type == T_RED_OUT)
		{
			tmp->type = T_IN_OUT;
			ft_strdel(&tmp->word);
			tmp->word = ft_strdup("<>");
			ft_strdel(&tmp->next->word);
			tmp2 = tmp->next;
			tmp->next = tmp->next->next;
			tmp->next->prev = tmp;
			free(tmp2);
		}
		current = current->next;
	}
}

void	clean_null_tokens(t_token **head)
{
	t_token	*current;
	t_token	*tmp;

	current = *head;
	while (current != NULL)
	{
		tmp = current;
		if (ft_strlen(tmp->word) == 0 && tmp->type != T_PARENTHESES)
		{
			if (tmp->prev != NULL)
				tmp->prev->next = tmp->next;
			else
				*head = tmp->next;
			if (tmp->next != NULL)
				tmp->next->prev = tmp->prev;
			current = tmp->next;
			ft_strdel(&tmp->word);
			free(tmp);
		}
		else
			current = current->next;
	}
}
