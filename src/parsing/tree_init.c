/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:24:48 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/11 23:23:55 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd_list	*create_list(t_data *data, t_token *token);

void	print_cmd_list(t_cmd_list *list)
{
	int	i;

//	i = 0;
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
//		while (list->redir_list)
//		{
//			printf("redir token: %s", list->redir_list->redir_token->word);
//			printf("redir word: %s", list->redir_list->redir_word->word);
//			list->redir_list = list->redir_list->next;
//		}
		list = list->next;
	}
}

t_cmd_list 	*init_list()
{
	t_cmd_list *list;

	list = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	list->args_array = NULL;
	list->value = NULL;
	return (list);
}

void	init_tree(t_data *data)
{
	t_token	*head;

	head = data->token_list;
	data->list = create_list(data, data->token_list);
//	print_cmd_list(data->list);
//	if (data)
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
//	printf("count: %i\n", count);
	return (count);
}

t_cmd_list	*create_node(t_token **start, t_token *current, t_cmd_list *list)
{
	int	arg_num;
	int	i;

	i = 0;
	arg_num = count_args(*start, current);
//	arg_num = 2;
	list = init_list();
	list->value = (*start)->word;
	list->args_array = (char **)malloc(sizeof(char *) * (arg_num + 1));
//	if (!list->args_array)

	while (*start != current)
	{
		if ((*start)->type == T_APPEND || (*start)->type == T_DELIM
			|| (*start)->type == T_RED_INP || (*start)->type == T_RED_OUT)
		{
			printf("redir_token: %s\n", (*start)->word);
			printf("redir_word: %s\n", (*start)->next->word);
//			create_redir_token((*start), (*start)->next);
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
//	printf("I finished create_node execution\n");
	return (list);
}

t_cmd_list	*create_last_node(t_token **token, t_cmd_list *list)
{
	int	arg_nums;
	int	i;

	list = init_list();
//	if (!list)
//		return (NULL);
//	list->type = (*token)->type;
	list->value = (*token)->word;
	i = 0;
	arg_nums = count_args(*token, NULL);
	if (arg_nums != 0)
		list->args_array = (char **)malloc(sizeof(char *) * (arg_nums));
	while ((*token)->type != T_NEWLINE)
	{
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








//void	init_tree(t_data *data)
//{
//	t_token	*head;
//
//	head = data->token_list;
//	data->tree = create_simple_tree(data, data->token_list);
//	print_right_tree(data->tree);
//	data->token_list = head;
//}
//
//t_tree	*create_simple_tree(t_data *data, t_token *token)
//{
//	t_tree	*tree;
//	t_tree	*root;
//
//	tree = NULL;
//	if (token->type != T_WORD && token->type != T_PIPE)
//	{
//		tree = build_first_tree_leaf_redir(&data->token_list, tree);
//		root = tree;
//		token = token->next->next;
//	}
//	if (token->type == T_NEWLINE)
//		return (root);
//	while (token)
//	{
//		if (token->type == T_PIPE || token->type == T_RED_INP
//			|| token->type == T_RED_OUT || token->type == T_APPEND
//			|| token->type == T_DELIM)
//		{
//			if (tree == NULL)
//			{
//					tree = build_right_branch(&data->token_list, token, tree);
//					root = tree;
//			}
//			else
//			{
//				tree->right = build_right_branch(&data->token_list, token, tree);
//				tree = tree->right;
//			}
//			token = data->token_list;
//		}
//		else
//			token = token->next;
//	}
//	if (tree == NULL)
//		return (build_tree_leaf_right(&data->token_list, tree));
//	tree->right = build_tree_leaf_right(&data->token_list, tree);
//	return (root);
//}
