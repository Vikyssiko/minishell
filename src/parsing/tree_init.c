#include "minishell.h"

void	init_tree(t_data *data)
{
	t_token	*head;
	t_token	*address;
//    t_token *root;

	address = data->token_list;
	head = data->token_list;
//    root = find_tree_root(data->token_list);
	data->tree = create_simple_tree(data, address);
	print_right_tree(data->tree);
	data->token_list = head;
}

//t_token *find_tree_root(t_token *token_list)
//{
//	t_token *token;
//	t_token *tmp;
//	int 	count;
//
//	count = 0;
//	token = token_list;
//
//	while (token->type != T_NEWLINE)
//	{
//		if (token->type == T_OR)
//		{
//			tmp = token;
//			count++;
//			break ;
//		}
//		else if (token->type == T_AND && count == 0)
//		{
//			tmp = token;
//			count++;
//		}
//		token = token->next;
//	}
//	token = token_list;
//	if (count == 0)
//	{
//		while (token->type != T_NEWLINE)
//		{
//			if (token->type == T_PIPE || token->type == T_RED_INP || token->type == T_RED_OUT
// 				|| token->type == T_APPEND || token->type == T_DELIM)
//			{
//				tmp = token;
//				count++;
//				break ;
//			}
//			token = token->next;
//		}
//	}
//	if (count == 0)
//		tmp = token_list;
//	return (tmp);
//}

t_tree	*create_tree_root(t_token *token)
{
	t_tree *tree;
	t_token *tmp;

	if (!token)
		return (0);
	tmp = token;
	tree = malloc(sizeof(t_tree));
	tree->type = tmp->type;
	tree->value = tmp->word;
	tree->left = NULL;
	tree->right = NULL;
	return (tree);
}
t_tree	*create_simple_tree(t_data *data, t_token *address)

{
	t_tree	*tree;
	t_tree	*root;
	int	delim;

	tree = NULL;
	delim = 0;
	while (address)
	{
		if (address->type == T_PIPE || address->type == T_RED_INP || address->type == T_RED_OUT 
			|| address->type == T_APPEND || address->type == T_DELIM)
		{
			if (tree == NULL)
			{
				tree = build_right_branch(&data->token_list, address, tree);
				root = tree;
				address = data->token_list;
			}
			else
			{
				tree->right = build_right_branch(&data->token_list, address, tree);
				tree = tree->right;
				address = data->token_list;
			}
			delim++;
		}
		if (address->type != T_PIPE && address->type != T_RED_INP && address->type != T_RED_OUT 
		 	&& address->type != T_APPEND &&  address->type != T_DELIM)
			address = address->next;
	}
	if (delim == 0)
	{
		address = data->token_list;
		tree = build_tree_leaf_right(&data->token_list, tree);
		root = tree;
	}
	else
	{
		tree->right = build_tree_leaf_right(&data->token_list, tree);
		tree = tree->right;
	}
	return (root);
}
