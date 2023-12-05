/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:49:40 by vkozlova          #+#    #+#             */
/*   Updated: 2023/12/05 22:55:12 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_str_part(char *str, int i, int start, char **result)
{
	char	*new_str;

	new_str = malloc(i - start + 1);
	ft_strlcpy(new_str, &str[start], i - start + 1);
	*result = ft_strjoin(*result, new_str);
	free(new_str);
}

void	join_result_with_exit(int exit_status, char **result)
{
	char	*exit;

	exit = ft_itoa(exit_status);
	*result = ft_strjoin(*result, exit);
	free(exit);
}

void	replace_variable(t_data *data, int *i, int *start, char **result)
{
	char	*new_str;
	char	*str;

	str = data->input_line;
	add_str_part(str, *i, *start, result);
	*start = ++(*i);
	while (str[*i] && (str[*i] == '_' || ft_isalnum(str[*i])))
		(*i)++;
	new_str = malloc(*i - *start + 1);
	ft_strlcpy(new_str, &str[*start], *i - *start + 1);
	*result = ft_strjoin(*result, find_env_var(data, new_str));
	free(new_str);
	*start = *i;
}

char	*replace_dollars(t_data *data, char *str)
{
	int		start;
	char	*result;
	int		i;

	start = 0;
	i = 0;
	result = NULL;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?' && !in_single_quotes(str, i))
		{
			add_str_part(str, i, start, &result);
			i += 2;
			join_result_with_exit(data->exit_status, &result);
			start = i;
		}
		else if (str[i] == '$' && str[i + 1] != ' '
			&& !in_single_quotes(str, i))
			replace_variable(data, &i, &start, &result);
		else
			i++;
	}
	add_str_part(str, i, start, &result);
	free(str);
	return (result);
}
