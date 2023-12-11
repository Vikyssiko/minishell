/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlova <vkozlova@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 21:40:03 by vkozlova          #+#    #+#             */
/*   Updated: 2023/12/07 21:40:03 by vkozlova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd_list	*init_list(void)
{
	t_cmd_list	*list;

	list = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	if (!list)
		exit(1);
	list->args_array = NULL;
	list->in = NULL;
	list->out = NULL;
	list->fd_in = -1;
	list->redir_status = 1;
	list->value = NULL;
	list->prev = NULL;
	list->next = NULL;
	list->redir_list = NULL;
	return (list);
}

int	count_args(t_token *start, t_token *current)
{
	int	count;

	count = 0;
	while (start != current)
	{
		if (start->type == T_PIPE)
			break ;
		if (start->type == T_APPEND || start->type == T_DELIM
			|| start->type == T_RED_INP || start->type == T_RED_OUT)
		{
			start = start->next->next;
			continue ;
		}
		start = start->next;
		count++;
	}
	return (count);
}

int	find_list_value(t_token **start, t_cmd_list **list)
{
	int		arg_num;
	t_token	*start_copy;

	arg_num = count_args(*start, NULL);
	*list = init_list();
	start_copy = (*start);
	while (start_copy && start_copy->type != T_WORD
		&& start_copy->type != T_NEWLINE && start_copy->next)
		start_copy = start_copy->next->next;
	(*list)->value = start_copy->word;
	return (arg_num);
}

t_cmd_list	*create_node(t_token **start, t_token *current, t_cmd_list *list)
{
	int		arg_num;
	int		i;

	i = 0;
	arg_num = find_list_value(start, &list);
	list->args_array = (char **)malloc(sizeof(char *) * (arg_num + 1));
	if (!list->args_array)
		exit(1);
	while (*start != current)
	{
		if ((*start)->type == T_APPEND || (*start)->type == T_DELIM
			|| (*start)->type == T_RED_INP || (*start)->type == T_RED_OUT)
		{
			add_redir_token(&(list->redir_list),
				create_redir_token((*start), (*start)->next));
			(*start) = (*start)->next->next;
			continue ;
		}
		list->args_array[i] = ft_strdup((*start)->word);
		*start = (*start)->next;
		i++;
	}
	list->args_array[i] = NULL;
	*start = (*start)->next;
	return (list);
}

t_cmd_list	*create_last_node(t_token **start, t_cmd_list *list)
{
	int		arg_num;
	int		i;

	i = 0;
	arg_num = find_list_value(start, &list);
	if (arg_num != 0)
		list->args_array = (char **)malloc(sizeof(char *) * (arg_num));
	if (!list->args_array)
		exit(1);
	while ((*start)->type != T_NEWLINE)
	{
		if ((*start)->type == T_APPEND || (*start)->type == T_DELIM
			|| (*start)->type == T_RED_INP || (*start)->type == T_RED_OUT)
		{
			add_redir_token(&(list->redir_list),
				create_redir_token((*start), (*start)->next));
			(*start) = (*start)->next->next;
			continue ;
		}
		list->args_array[i] = ft_strdup((*start)->word);
		*start = (*start)->next;
		i++;
	}
	list->args_array[i] = NULL;
	return (list);
}
