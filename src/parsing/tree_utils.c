/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:24:48 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/11 23:51:12 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
The problem is probably caused by a non-existing address data->tree->right, as data->tree is missing during initial reset, but I may be wrong. Tried changing to **data, sending data->tree as an argument to the function, nothing worked.
As I mentioned before, the previous commit doesn't give this error and frees the nodes accordingly, therefore something may be changed in the main code.
*/

 void	free_tree(t_tree **tree)

 {
 	int i;
 	t_tree *right;

 	i = 0;
	right = NULL;
 	if (!(*tree))
 		return ;
 	while ((*tree))
 	{
		if ((*tree)->right)
 			right = (*tree)->right;
 		if ((*tree)->left)
 		{
 			if ((*tree)->left->args_array)
 				free_2darray((*tree)->left->args_array);
 			free((*tree)->left);
 			(*tree)->left = NULL;
 		}
 		free_2darray((*tree)->args_array);
 		free((*tree));
		tree = NULL;
 		(*tree) = right;
 	}
 }

// void free_tree(t_tree *tree)
// {
//    if (tree == NULL)
//        return ;

//    if (tree->left)
//        free_tree(tree->left);
//    if (tree->right)
//        free_tree(tree->right);
// 	if (tree->type == T_WORD)
//    	free_2darray(tree->args_array);
//    free(tree);
// }

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
		if (tree->delim)
			printf("DELIM = %s\n", tree->delim);
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
