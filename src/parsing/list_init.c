/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:24:48 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/29 19:57:37 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd_list	*create_list(t_data *data, t_token *token);

void	init_list_data(t_data *data)
{
	t_token	*head;

	head = data->token_list;
	data->list = create_list(data, data->token_list);
	data->token_list = head;
}

t_cmd_list	*create_node_go_to_next(t_cmd_list **root, t_cmd_list **list,
				t_data *data, t_token *token)
{
	if (*list == NULL)
	{
		*list = create_node(&data->token_list, token, *list);
		*root = *list;
	}
	else
	{
		(*list)->next = create_node(&data->token_list, token, *list);
		*list = (*list)->next;
	}
	return (*list);
}

t_cmd_list	*create_list(t_data *data, t_token *token)
{
	t_cmd_list	*list;
	t_cmd_list	*root;

	list = NULL;
	if (token->type == T_NEWLINE)
		return (NULL);
	while (token)
	{
		if (token->type == T_PIPE)
		{
			list = create_node_go_to_next(&root, &list, data, token);
			token = data->token_list;
		}
		else
			token = token->next;
	}
	if (list == NULL)
		return (create_last_node(&data->token_list, list));
	list->next = create_last_node(&data->token_list, list);
	return (root);
}
