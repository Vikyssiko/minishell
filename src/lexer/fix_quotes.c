/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:44:25 by alappas           #+#    #+#             */
/*   Updated: 2024/01/23 02:48:45 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	in_quotes_token(char *s, int *start)
{
	int		double_quotes;
	int		single_quotes;
	bool	encounter;
	int		i;

	double_quotes = 0;
	single_quotes = 0;
	encounter = false;
	i = (*start);
	while (s[++i])
	{
		if (s[i] == '\"' && single_quotes % 2 == 0)
			double_quotes++;
		if (s[i] == '\'' && double_quotes % 2 == 0)
			single_quotes++;
		if ((s[i] == '\'' || s[i] == '\"') && !encounter)
		{
			encounter = true;
			(*start) = i;
		}
	}
	if ((double_quotes % 2 == 0 && double_quotes > 0)
		|| (single_quotes % 2 == 0 && single_quotes > 0))
		return (1);
	return (0);
}

void	trim_tokens_helper(bool *encounter, int *i, int **end)

{
	(**end) = (*i) - 2;
	(*i)++;
	(*encounter) = true;
}

char	*trim_tokens(char *input, int start, int *end)
{
	char	*str;
	char	quote;
	bool	encounter;
	int		i;
	int		j;

	str = ft_calloc(ft_strlen(input) + 1, 1);
	if (!str)
		exit_shell_no_mes(1, NULL);
	quote = input[start];
	encounter = false;
	i = 0;
	j = 0;
	while (i != start)
		str[(j)++] = input[(i)++];
	i++;
	while (input[i])
	{
		if (input[i] == quote && !encounter)
			trim_tokens_helper(&encounter, &i, &end);
		if (input[i])
			str[j++] = input[i++];
	}
	str[j] = '\0';
	return (str);
}

void	fix_quotes(t_data *data)
{
	t_token	*head;
	char	*tmp;
	int		start;
	int		end;

	head = data->token_list;
	tmp = NULL;
	while (data->token_list)
	{
		if (data->token_list->type == T_WORD)
		{
			start = -1;
			while (in_quotes_token(data->token_list->word, &start))
			{
				tmp = trim_tokens(data->token_list->word, start, &end);
				ft_strdel(&data->token_list->word);
				data->token_list->word = ft_strdup(tmp);
				ft_strdel(&tmp);
				start = end;
			}
		}
		data->token_list = data->token_list->next;
	}
	data->token_list = head;
}
