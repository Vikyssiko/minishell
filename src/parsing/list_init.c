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

void	print_cmd_list(t_cmd_list *list)
{
	int	i;

	while (list)
	{
		i = 0;
		if (list->value)
			printf("value: %s\n", list->value);
		while (list->args_array && list->args_array[i])
		{
			if (list->args_array[i])
				printf("args_array[%i]: %s\n", i, list->args_array[i]);
			i++;
		}
		while (list->redir_list)
		{
			printf("redir token: %s\n", list->redir_list->redir_token->word);
			printf("redir word: %s\n", list->redir_list->redir_word->word);
			list->redir_list = list->redir_list->next;
		}
		list = list->next;
	}
}

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
	t_cmd_list	*new;

	if (*list == NULL)
	{
		*list = create_node(&data->token_list, token, *list);
		(*list)->prev = NULL;
		*root = *list;
	}
	else
	{
		new = create_node(&data->token_list, token, *list);
		(*list)->next = new;
		new->prev = *list;
		*list = (*list)->next;
	}
	return (*list);
}

t_cmd_list	*create_list(t_data *data, t_token *token)
{
	t_cmd_list	*list;
	t_cmd_list	*root;
	t_cmd_list	*new;

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
	new = create_last_node(&data->token_list, list);
	list->next = new;
	new->prev = list;
	return (root);
}
