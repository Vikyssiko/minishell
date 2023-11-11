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

void	init_tree(t_data *data)
{
	t_token	*head;

	head = data->token_list;
	data->tree = create_simple_tree(data, data->token_list);
	print_right_tree(data->tree);
	data->token_list = head;
}

t_tree	*create_simple_tree(t_data *data, t_token *token)
{
	t_tree	*tree;
	t_tree	*root;

	tree = NULL;
	if (token->type != T_WORD && token->type != T_PIPE)
	{
		tree = build_first_tree_leaf_redir(&data->token_list, tree);
		root = tree;
		token = token->next->next;
	}
	if (token->type == T_NEWLINE)
		return (root);
	while (token)
	{
		if (token->type == T_PIPE || token->type == T_RED_INP
			|| token->type == T_RED_OUT || token->type == T_APPEND
			|| token->type == T_DELIM)
		{
			if (tree == NULL)
			{
					tree = build_right_branch(&data->token_list, token, tree);
					root = tree;
			}
			else
			{
				tree->right = build_right_branch(&data->token_list, token, tree);
				tree = tree->right;
			}
			token = data->token_list;
		}
		else
			token = token->next;
	}
	if (tree == NULL)
		return (build_tree_leaf_right(&data->token_list, tree));
	tree->right = build_tree_leaf_right(&data->token_list, tree);
	return (root);
}
