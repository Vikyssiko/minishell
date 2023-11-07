/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlova <vkozlova@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:35 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/07 14:02:52 by vkozlova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	find_ortokens(t_token **head)
{
	t_token	*current;
	t_token	*tmp;
	t_token	*tmp2;

	current = *head;
	while (current != NULL)
	{
		tmp = current;
		if (tmp->type == T_PIPE && tmp->next->type == T_PIPE)
		{
			tmp->type = T_OR;
			ft_strdel(&tmp->word);
			tmp->word = ft_strdup("||");
			ft_strdel(&tmp->next->word);
			tmp2 = tmp->next;
			tmp->next = tmp->next->next;
			tmp->next->prev = tmp;
			free(tmp2);
		}
		current = current->next;
	}
}

void	find_andtokens(t_token **head)
{
	t_token	*current;
	t_token	*tmp;
	t_token	*tmp2;

	current = *head;
	while (current != NULL)
	{
		tmp = current;
		if (tmp->type == T_AMPER && tmp->next->type == T_AMPER)
		{
			tmp->type = T_AND;
			ft_strdel(&tmp->word);
			tmp->word = ft_strdup("&&");
			ft_strdel(&tmp->next->word);
			tmp2 = tmp->next;
			tmp->next = tmp->next->next;
			tmp->next->prev = tmp;
			free(tmp2);
		}
		current = current->next;
	}
}

void	find_delim(t_token *current)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = current;
	if (tmp->type == T_RED_INP && tmp->next->type == T_RED_INP)
	{
		tmp->type = T_DELIM;
		ft_strdel(&tmp->word);
		tmp->word = ft_strdup("<<");
		tmp2 = tmp->next;
		tmp->next = tmp->next->next;
		tmp->next->prev = tmp;
		ft_strdel(&tmp2->word);
		free(tmp2);
	}
}
