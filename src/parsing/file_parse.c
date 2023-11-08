/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 21:01:38 by alappas           #+#    #+#             */
/*   Updated: 2023/11/04 23:46:42 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//void	last_input(t_tree *tree)
//{
//	t_tree	*target_leaf;
//	t_tree	*head;
//
//	if (tree == NULL)
//		return ;
//	target_leaf = tree;
//	head = tree;
//	while (tree && tree->type != T_AND && tree->type != T_OR)
//	{
//		if (tree->type == T_RED_INP)
//			target_leaf = tree;
//		tree = tree->right;
//	}
//	head = tree;
//	while (tree && tree->type != T_AND && tree->type != T_OR)
//	{
//		tree->last_output = target_leaf->right->left;
//		tree = tree->right;
//	}
//	if (tree && (tree->type == T_AND || tree->type == T_OR))
//	{
//		printf("I have found && ||  INP\n");
//		last_input(tree->right);
//	}
//}
//
//void	last_output(t_tree *tree)
//{
//	t_tree	*target_leaf;
//	t_tree	*head;
//
//	if (tree == NULL)
//		return ;
//	target_leaf = tree;
//	head = tree;
//	while (tree && tree->type != T_AND && tree->type != T_OR)
//	{
//		if (tree->type == T_RED_OUT)
//			target_leaf = tree;
//		tree = tree->right;
//	}
//	head = tree;
//	while (tree && tree->type != T_AND && tree->type != T_OR)
//	{
//		tree->last_output = target_leaf->right->left;
//		tree = tree->right;
//	}
//	if (tree && (tree->type == T_AND || tree->type == T_OR))
//	{
//		printf("I have found && ||  OUT\n");
//		last_output(tree->right);
//	}
//}
