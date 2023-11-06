#include "minishell.h"

t_tree	*init_parenth_tree(t_token *parenth_token)
{
    t_data  *temp_data;
	t_tree	*tree;
	t_token	*head;
	t_token	*address;
    t_token *root;

	tree = NULL;
    temp_data = malloc(sizeof(t_data));
    temp_data->input_line = trim_input(parenth_token->word);
	lexical_analysis(temp_data, temp_data->input_line);
	// printf("I segfault here\n");
	address = temp_data->token_list;
	head = temp_data->token_list;
    root = find_tree_root(temp_data->token_list);
    if (root->type == T_OR || root->type == T_AND)
    {
        tree = create_tree_root(root);
        address = root;
		build_full_tree(temp_data, address);
    }
	else if (root->type == T_PARENTHESES)
		init_parenth_tree(parenth_token);
	else
	{
		tree = create_simple_tree(temp_data, address);
		print_right_tree(tree);
	}
	temp_data->token_list = head;
    free_tokens(&temp_data->token_list, free);
    free(temp_data);
    return (tree);
}
