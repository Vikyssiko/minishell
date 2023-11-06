/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:48:33 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/06 19:19:42 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data(t_data *data)
{
	if (!data)
		return ;
	free_2darray(data->env_array);
	free_tokens(&data->token_list, free);
	free(data);
	data = NULL;
}

void	free_tokens(t_token **begin, void (*del)(void *))
{
	t_token	*tmp;
	t_token	*tmp2;

	if (!begin || !del)
		return ;
	tmp = *begin;
	while (tmp)
	{
		ft_strdel(&tmp->word);
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	*begin = NULL;
}

void	free_envir(t_envir *envir)
{
	t_envir	*tmp;

	if (!envir)
		return ;
	tmp = envir;
	if (tmp->var_name)
	{
		free(tmp->var_name);
		tmp->var_name = NULL;
	}
	if (tmp->var_value)
	{
		free(tmp->var_value);
		tmp->var_value = NULL;
	}
	free(tmp);
}

void	free_2darray(char **array)
{
	int	i;

	i = -1;
	if (!array)
		return ;
	while (array[++i])
		ft_strdel(&array[i]);
	free(array);
	array = NULL;
}

// void	free_tree(t_data *data)

// {
// 	int i;
// 	t_tree *right;

// 	i = 0;
// 	if (!data->tree)
// 		return ;
// 	while (data->tree)
// 	{
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
// 		data->tree = right;
// 	}
// }

// void	free_commands(t_cmdexe **head, void (*del)(void *))
// {
// 	t_cmdexe *tmp;
// 	t_cmdexe *tmp2;

// 	if (!head || !del)
// 		return ;
// 	tmp = *head;
// 	while (tmp)
// 	{
// 		printf("free_commands inside while \n");
// 		if (tmp->cmd)
// 			ft_strdel(&tmp->cmd);
// 		if (tmp->path)
// 			ft_strdel(&tmp->path);
// 		if (tmp->args_array)
// 			free_2darray(tmp->args_array);
// 		tmp2 = tmp->next;
// 		free(tmp);
// 		tmp = tmp2;
// 	}
// 	*head = NULL;
// }