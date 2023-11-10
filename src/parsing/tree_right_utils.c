/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_right_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlova <vkozlova@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:36 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/10 20:05:15 by vkozlova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_tree	*build_right_branch(t_token **start, t_token *current, t_tree *tree)
{
	int	arg_nums;
	int	i;

	tree = (t_tree *)malloc(sizeof(t_tree));
	if (!tree)
		return (NULL);
	tree->type = current->type;
	tree->value = current->word;
	tree->args_array = NULL;
	i = 0;
	arg_nums = arg_count_right(*start, current);
	tree->left = (t_tree *)malloc(sizeof(t_tree));
	if (!tree->left)
	{
		free(tree);
		return (NULL);
	}
	tree->left->args_array = (char **)malloc(sizeof(char *) * (arg_nums + 1));
	while (*start != current)
	{
		tree->left->args_array[i] = ft_strdup((*start)->word);
		*start = (*start)->next;
		i++;
	}
	// ???
	tree->left->args_array[i] = NULL;
	*start = (*start)->next;
	tree->right = NULL;
	return (tree);
}

t_tree	*build_tree_leaf_right(t_token **token, t_tree *tree)
{
	int	arg_nums;
	int	i;

	tree = (t_tree *)malloc(sizeof(t_tree));
	if (!tree)
		return (NULL);
	tree->type = (*token)->type;
	tree->value = (*token)->word;
	i = 0;
	arg_nums = arg_count_right(*token, NULL);
	if (arg_nums != 0)
		tree->args_array = (char **)malloc(sizeof(char *) * (arg_nums));
	while ((*token)->type != T_NEWLINE)
	{
		tree->args_array[i] = ft_strdup((*token)->word);
		*token = (*token)->next;
		i++;
	}
	tree->args_array[i] = NULL;
	tree->left = NULL;
	tree->right = NULL;
	return (tree);
}

int	arg_count_right(t_token *token, t_token *current)
{
	int	count;

	count = 0;
	while (token != current)
	{
		count++;
		token = token->next;
	}
	return (count);
}

