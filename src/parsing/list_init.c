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

t_cmd_list 	*init_list()
{
	t_cmd_list *list;

	list = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	//malloc protect?
	list->args_array = NULL;
	list->value = NULL;
	list->next = NULL;
	list->redir_list = NULL;
	return (list);
}

void	init_list_data(t_data *data)
{
	t_token	*head;

	head = data->token_list;
	data->list = create_list(data, data->token_list);
//	print_cmd_list(data->list);
	data->token_list = head;
}

int	count_args(t_token *start, t_token *current)
{
	int	count;

	count = 0;
	while (start != current)
	{
		if (start->type == T_PIPE)
			break ;
		if (start->type == T_APPEND || start->type == T_DELIM
			|| start->type == T_RED_INP || start->type == T_RED_OUT)
		{
			start = start->next->next;
			continue ;
		}
		start = start->next;
		count++;
	}
	return (count);
}

t_cmd_list	*create_node(t_token **start, t_token *current, t_cmd_list *list)
{
	int		arg_num;
	int		i;
	t_token	*start_copy;

	i = 0;
	arg_num = count_args(*start, current);
	list = init_list();
	start_copy = (*start);
	while (start_copy && start_copy->type != T_WORD && start_copy->type != T_NEWLINE)
	{
		if (start_copy->next)
			start_copy = start_copy->next->next;
	}
	list->value = start_copy->word;
	list->args_array = (char **)malloc(sizeof(char *) * (arg_num + 1));
	if (!list->args_array)
		exit(1);
	while (*start != current)
	{
		if ((*start)->type == T_APPEND || (*start)->type == T_DELIM
			|| (*start)->type == T_RED_INP || (*start)->type == T_RED_OUT)
		{
			add_redir_token(&(list->redir_list), create_redir_token((*start), (*start)->next));
			(*start) = (*start)->next->next;
			continue ;
		}
		list->args_array[i] = ft_strdup((*start)->word);
		*start = (*start)->next;
		i++;
	}
	list->args_array[i] = NULL;
	*start = (*start)->next;
	return (list);
}

t_cmd_list	*create_last_node(t_token **token, t_cmd_list *list)
{
	int		arg_num;
	int		i;
	t_token	*token_copy;

	list = init_list();
//	if (!list)
//		return (NULL);
//	list->type = (*token)->type;
	token_copy = (*token);
	while (token_copy && token_copy->type != T_WORD && token_copy->type != T_NEWLINE)
	{
		if (token_copy->next)
			token_copy = token_copy->next->next;
	}
	list->value = token_copy->word;
	i = 0;
	arg_num = count_args(*token, NULL);
	if (arg_num != 0)
		list->args_array = (char **)malloc(sizeof(char *) * (arg_num));
	while ((*token)->type != T_NEWLINE)
	{
		if ((*token)->type == T_APPEND || (*token)->type == T_DELIM
			|| (*token)->type == T_RED_INP || (*token)->type == T_RED_OUT)
		{
			add_redir_token(&(list->redir_list), create_redir_token((*token), (*token)->next));
			(*token) = (*token)->next->next;
			continue ;
		}
		list->args_array[i] = ft_strdup((*token)->word);
		*token = (*token)->next;
		i++;
	}
	list->args_array[i] = NULL;
	return (list);
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
			if (list == NULL)
			{
				list = create_node(&data->token_list, token, list);
				root = list;
			}
			else
			{
				list->next = create_node(&data->token_list, token, list);
				list = list->next;
			}
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
