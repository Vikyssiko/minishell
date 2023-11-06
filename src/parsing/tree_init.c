#include "minishell.h"

/*
1. saving the address = saving the head of the token list to have an argument in which I can freely iterate through the tokens
2. Through the find_tree_root function we're finding whether our input has || or &&.
3. If the || or && exist - we will make it the beginning of our tree. Else, we will build the tree from left to right starting with the first delimeter we find.
4. If we have a parenthesis in address->type, it means that the input was a single parenthesis, therefore we will tokenize it and parse it inside the tree until there are no brackets or the first delimeter inside is found.
5. If || or && exist = we will start building the tree to the left first, and then to the right. The left part will have all the commands on its right side, the right tree will have all the commands on the left side.
6. Don't forget the input/output.

Tasks to do:
A. Implement && and || tree building - the function must build the tree to the left and right sides.
B. When it meets parenthesis - the function must call itself to start building a new semi-tree, we have to check on which side the parenthesis occured too.
C. When the parenthesis is met = we have to create a new temporary data structure to save the new tokens, and immediately free it after the execution. We don't need it in main data structure anymore as we 
will work with the tree structure only.
D. Check the errors of tokenized parenthesis and free after parsing the parenthesis inside the tree itself.

The current idea = starting with line 39 I want to add conditions on how to build the trees to make the functions composed too. Therefore, there is a third condition (it root->type == T_PARENTH) which will be modified accordingly (it will just require initial tokenization).

What was done = The tree is being fully built, only the parenthesees case left to be done.


WARNING! The free_tree function was added in tree_utils.c as it was deleted, I have restored it from our previous version. The tree is being freed in the way it is created now (will be needed to improved to clean the left tree), 
but with sanitizer it started giving an error, which doesn't exist in the previous version, commit "Fixed last leaf" on November 1st. Reason is unknown, tried to fix it, but didn't work (tried double pointer, returning t_tree address, etc).
More thoughts on this problem in the mentioned file. Also, "/" doesn't work for some reason.

*/

void	init_tree(t_data *data)
{
	t_token	*head;
	t_token	*address;
    t_token *root;

	address = data->token_list;
	head = data->token_list;
    root = find_tree_root(data->token_list);
	if (root->type == T_PARENTHESES)
	{
		ft_strdel(&data->input_line);
		data->input_line = ft_strdup(root->word);
		free_tokens(&data->token_list, free);
		lexical_analysis(data, data->input_line);
		root = find_tree_root(data->token_list);
		// print_tokens(data);
	}
	printf("I segfault here\n");
    if (root->type == T_OR || root->type == T_AND)
    {
        data->tree = create_tree_root(root);
        address = root;
		build_full_tree(data, address);
    }
	else
	{
		data->tree = create_simple_tree(data, address);
		print_right_tree(data->tree);
	}
	data->token_list = head;
}

void	build_full_tree(t_data *data, t_token *address)

{
	t_tree *root;

	root = data->tree;
	printf("ROOT TYPE = %d, ROOT VALUE = %s\n\n", root->type, root->value);
	data->tree->left = build_left_tree(data, address->prev);
	print_left_tree(data->tree->left);
	data->tree = root;
	data->tree->right = build_right_tree(data, address->next);
	print_right_tree(data->tree->right);
}

t_token *find_tree_root(t_token *token_list)
{
	t_token *token;
	t_token *tmp;
	int 	count;

	count = 0;
	token = token_list;

	while (token->type != T_NEWLINE)
	{
		if (token->type == T_OR)
		{
			tmp = token;
			count++;
			break ;
		}
		else if (token->type == T_AND && count == 0)
		{
			tmp = token;
			count++;
		}
		token = token->next;
	}
	token = token_list;
	if (count == 0)
	{
		while (token->type != T_NEWLINE)
		{
			if (token->type == T_PIPE || token->type == T_RED_INP || token->type == T_RED_OUT || token->type == T_THREE_IN
 				|| token->type == T_APPEND || token->type == T_OR || token->type == T_AND || token->type == T_DELIM)
			{
				tmp = token;
				count++;
				break ;
			}
			token = token->next;
		}
	}
	if (count == 0)
		tmp = token_list;
	return (tmp);
}

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
			|| address->type == T_APPEND || address->type == T_DELIM || address->type == T_THREE_IN)
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
		 	&& address->type != T_APPEND &&  address->type != T_DELIM && address->type != T_THREE_IN)
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
