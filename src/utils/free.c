/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:48:33 by alappas           #+#    #+#             */
/*   Updated: 2023/12/04 15:41:56 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_data(t_data *data)
{
	if (!data)
		return ;
	free_2darray(data->env_array);
	free_2darray(data->new_env_array);
	free_tokens(&data->token_list, free);
	ft_envclear(&data->env_list);
	ft_envclear(&data->export_list);
	free_list(&data->list);
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

void	ft_envclear(t_envir **env_list)

{
	t_envir	*head;

	while ((*env_list))
	{
		head = (*env_list)->next;
		if ((*env_list)->var_name)
		{
			free((*env_list)->var_name);
			(*env_list)->var_name = NULL;
		}
		if ((*env_list)->var_value)
		{
			free((*env_list)->var_value);
			(*env_list)->var_value = NULL;
		}
		free((*env_list));
		(*env_list) = NULL;
		(*env_list) = head;
	}
}

void	free_list(t_cmd_list **list)
{
	t_cmd_list *tmp;

	tmp = NULL;
	if (!(*list))
		return ;
	while ((*list))
	{
		tmp = (*list)->next;
		free_2darray((*list)->args_array);
//		if ((*list)->redir_list)
//		{
//			if ((*list)->redir_list->redir_token->word)
//				ft_strdel(&(*list)->redir_list->redir_token->word);
//			if ((*list)->redir_list->redir_word->word)
//				ft_strdel(&(*list)->redir_list->redir_word->word);
//		}
//		 if ((*list)->value)
////			 (*list)->value = NULL;
//		 	ft_strdel(&(*list)->value);
		free((*list));
		(*list) = tmp;
	}
}
