/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenising.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlova <vkozlova@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:36 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/06 22:08:05 by vkozlova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	find_token(t_data *data, char *str, int *i, t_token **head)
{
	if (is_chr_str(str[*i], " \t") && !in_quotes(str, *i))
	{
		add_token(head, create_token(data, *i));
		(*i)++;
		data->count = 0;
		return (0);
	}
	else if (is_chr_str(str[*i], "|<>") && !in_quotes(str, *i)
//		if (is_chr_str(str[*i], "|<>") && !in_quotes(str, *i)
		&& *i > 0 && !is_chr_str(str[*i - 1], "|<>"))
		add_token(head, create_token(data, *i));
	return (1);
}

// printing the tokens to debug
void	print_tokens(t_data *data)
{
	t_token	*tmp;

	tmp = data->token_list;
	while (tmp)
	{
		printf("\nword:%s:type:%d\n", tmp->word, tmp->type);
		tmp = tmp->next;
	}
}

t_token	*create_token(t_data *data, int i)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		exit_shell("Error: malloc failed\n", 1, data);
	new->word = ft_substr(data->input_line, i - data->count, data->count);
	new->type = T_WORD;
	data->count = 0;
	return (new);
}

t_token	*create_arg_token(t_data *data, char *word, enum e_token_type type)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		exit_shell("Error: malloc failed\n", 1, data);
	new->word = ft_strdup(word);
	new->type = type;
	return (new);
}
