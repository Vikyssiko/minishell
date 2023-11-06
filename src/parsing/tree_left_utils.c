#include "minishell.h"

t_tree	*build_left_tree(t_data *data, t_token *address)

{
	t_tree	*tree;
	t_tree	*root;
	t_token	*head;
	int	delim;

	tree = NULL;
	head = NULL;
	delim = 0;
	data->token_list = address;
	while (address)
	{
		if (address->type == T_PIPE || address->type == T_RED_INP || address->type == T_RED_OUT || address->type == T_THREE_IN
			|| address->type == T_APPEND || address->type == T_DELIM || address->type == T_AND || address->type == T_OR)
		{
			if (tree == NULL)
			{
				tree = build_left_branch(&data->token_list, address, tree);
				root = tree;
				address = data->token_list;
			}
			else
			{
				tree->left = build_left_branch(&data->token_list, address, tree);
				tree = tree->left;
				address = data->token_list;
			}
			delim++;
		}
		if (address->type != T_PIPE && address->type != T_RED_INP && address->type != T_RED_OUT && address->type != T_THREE_IN
		 	&& address->type != T_APPEND &&  address->type != T_DELIM && address->type != T_AND && address->type != T_OR)
			address = address->prev;
	}
	if (delim == 0)
	{
		address = data->token_list;
		tree = build_tree_leaf_left(&data->token_list, tree);
		root = tree;
	}
	else
	{
		tree->left = build_tree_leaf_left(&data->token_list, tree);
		tree = tree->left;
	}
	data->token_list = head;
	return (root);
}

t_tree	*build_left_branch(t_token **token, t_token *address, t_tree *tree)
{
	int arg_nums;
	int i;

	tree = (t_tree *)malloc(sizeof(t_tree));
	if (!tree)
		return (NULL);
	tree->type = (address)->type;
	tree->value = address->word;
	tree->args_array = NULL;
	i = 0;
	arg_nums =	arg_count_left(*token, address);
	tree->right = (t_tree *)malloc(sizeof(t_tree));
	if (!tree)
	{
		free(tree);
		return (NULL);
	}
	tree->right->args_array = (char **)malloc(sizeof(char *) * (arg_nums + 1));
	while (*token != address)
	{
		tree->right->args_array[i] = ft_strdup((*token)->word);
		*token = (*token)->prev;
		i++;
	}
	tree->right->args_array[i] = NULL;
	*token = (*token)->prev;
	tree->left = NULL;
	return (tree);
}

t_tree	*build_tree_leaf_left(t_token **token, t_tree *tree)
{
	int arg_nums;
	int i;

	tree = (t_tree *)malloc(sizeof(t_tree));
	if (!tree)
		return (NULL);
	tree->type = (*token)->type;
	tree->value = (*token)->word;
	i = 0;
	arg_nums =	arg_count_left(*token, NULL);
	if (arg_nums != 0)
		tree->args_array = (char **)malloc(sizeof(char *) * (arg_nums + 1));
	while (*token != NULL)
	{
		tree->args_array[i] = ft_strdup((*token)->word);
		*token = (*token)->prev;
		i++;
	}
	tree->args_array[i] = NULL;
	tree->left = NULL;
	tree->right = NULL;
	return (tree);
}

int		arg_count_left(t_token *token, t_token *address)
{
	int count;

	count = 0;
	while (token != address)
	{
		count++;
		token = token->prev;
	}
	return (count);
}