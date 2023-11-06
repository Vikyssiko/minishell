#include "minishell.h"

/*
The problem is probably caused by a non-existing address data->tree->right, as data->tree is missing during initial reset, but I may be wrong. Tried changing to **data, sending data->tree as an argument to the function, nothing worked.
As I mentioned before, the previous commit doesn't give this error and frees the nodes accordingly, therefore something may be changed in the main code.
*/

// void	free_tree(t_data *data)

// {
// 	int i;
// 	t_tree *right;

// 	i = 0;
// 	if (!data->tree)
// 		return ;
// 	while (data->tree)
// 	{
// 		// You basically can delete this line and iterate to the right node within the last line.
// 		right = data->tree->right;
// 		if (data->tree->left)
// 		{
// 			if (data->tree->left->args_array)
// 				free_2darray(data->tree->left->args_array);
// 			free(data->tree->left);
// 			data->tree->left = NULL;
// 		}
// 		free_2darray(data->tree->args_array);
// 		free(data->tree);
// 		// You can write here: data->tree = data->tree-right;
// 		data->tree = right;
// 	}
// }

void free_tree(t_tree *tree)
{
    if (tree == NULL)
        return ;

    if (tree->left)
        free_tree(tree->left);
    if (tree->right)
        free_tree(tree->right);
	if (tree->type == T_WORD)
    	free_2darray(tree->args_array);
    free(tree);
}

void print_right_tree(t_tree *tree)
{
	int i;

	i = 0;
	if (tree == NULL)
		return ;
	while (tree)
	{
		printf("HEAD tree->type: %d\n", tree->type);
		printf("HEAD tree->value: %s\n", tree->value);
		if (tree->args_array)
		{
			while (tree->args_array[i])
			{
				printf("HEAD tree->args_array[%d]: %s\n", i, tree->args_array[i]);
				i++;
			}
		}
		i = 0;
		if (tree->left)
		{
			while (tree->left->args_array[i])
			{
				printf("LEFT tree->args_array[%d]: %s\n", i, tree->left->args_array[i]);
				i++;
			}
		}
		i = 0;
		tree = tree->right;
	}
	printf("Completed printing the RIGHT tree\n\n");
}

void print_left_tree(t_tree *tree)
{
	int i;

	i = 0;
	if (tree == NULL)
		return ;
	while (tree)
	{
		printf("HEAD tree->type: %d\n", tree->type);
		printf("HEAD tree->value: %s\n", tree->value);
		if (tree->args_array)
		{
			while (tree->args_array[i])
			{
				printf("HEAD tree->args_array[%d]: %s\n", i, tree->args_array[i]);
				i++;
			}
		}
		i = 0;
		if (tree->right)
		{
			while (tree->right->args_array[i])
			{
				printf("RIGHT tree->args_array[%d]: %s\n", i, tree->right->args_array[i]);
				i++;
			}
		}
		i = 0;
		tree = tree->left;
	}
	printf("Completed printing the left tree\n\n");
}
// void print_tree_helper(t_tree *tree, int pos) {
//     int i;

//     i = -1;
//     while (++i < pos)
//         printf("\t");
//     if (tree) {
//         printf(
//             "<%d: %s (%p)>",
//             tree->type,
//             tree->value,
//             tree->left
//         );
//     } else {
//         printf(
//             "<%p %p>",
//             tree->left,
//             tree->right
//         );
//     }
//     printf("\n");
//     if (!tree || (!tree->left && !tree->right))
//         return;
//     if (tree) {
//         print_tree_helper(tree->left, pos - 1);
//         if (tree->left)
//             printf("\n");
//         print_tree_helper(tree->right, pos + 1);
//     }
// }

// int tree_depth(t_tree *tree) {
//     int left;
//     int right;

//     if (!tree)
//         return 0;
//     if (!tree->left && !tree->right)
//         return 1;
//     left = tree_depth(tree->left);
//     right = tree_depth(tree->right);
//     if (left > right)
//         return left + 1;
//     return right + 1;
// }

// void print_tree(t_tree *tree) {
//     print_tree_helper(tree, tree_depth(tree));
// }