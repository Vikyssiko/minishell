/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 19:13:24 by alappas           #+#    #+#             */
/*   Updated: 2023/11/06 19:24:30 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	lexical_analysis(t_data *data, char *input)
{
	if (!input || !input[0])
		return (1);
	tokenise(data, input);
	if (token_analysis(data))
		return (1);
	return (0);
}

int	create_tokens(t_data *data, char *str, int *word_len)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_chr_str(str[i], "\"\' \t") && !in_quotes(str, i)
			&& *word_len == 0)
			i++;
		if (is_chr_str(str[i], "|>< \t") && !in_quotes(str, i)
			&& *word_len != 0)
		{
			add_token(&data->token_list, create_token(data, i, *word_len));
			*word_len = 0;
		}
		if ((ft_strstr(&str[i], ">>") == &str[i]
				|| ft_strstr(&str[i], "<<") == &str[i])
			&& !in_quotes(str, i))
			add_token(&data->token_list, create_token(data, ++i + 1, 2));
		else if (is_chr_str(str[i], "|<>") && !in_quotes(str, i))
			add_token(&data->token_list, create_token(data, i + 1, 1));
		else if (!is_chr_str(str[i], " \t") || in_quotes(str, i))
			(*word_len)++;
		i++;
	}
	return (i);
}

void	tokenise(t_data *data, char *str)
{
	int		i;
	int		word_len;

	word_len = 0;
	i = create_tokens(data, str, &word_len);
	if (i > 0)
	{
		if (word_len != 0)
			add_token(&data->token_list, create_token(data, i, word_len));
		add_token(&data->token_list,
			create_arg_token(data, "newline", T_NEWLINE));
	}
}

int	token_analysis(t_data *data)
{
	t_token	*head;

	head = data->token_list;
	while (data->token_list)
	{
		set_token_type(data->token_list);
		data->token_list = data->token_list->next;
	}
	data->token_list = head;
	find_redir(&data->token_list);
	if (syntax_errors(data->token_list, data))
		return (1);
	return (0);
}

void	set_token_type(t_token *token)
{
	if (!ft_strcmp(token->word, "<<"))
		token->type = T_DELIM;
	else if (!ft_strcmp(token->word, ">>"))
		token->type = T_APPEND;
	else if (!ft_strcmp(token->word, "<"))
		token->type = T_RED_INP;
	else if (!ft_strcmp(token->word, ">"))
		token->type = T_RED_OUT;
	else if (!ft_strcmp(token->word, "|"))
		token->type = T_PIPE;
	else if (token->type != T_NEWLINE)
		token->type = T_WORD;
}
