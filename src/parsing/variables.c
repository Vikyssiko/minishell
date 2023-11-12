/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlova <vkozlova@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:49:40 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/11 16:49:40 by vkozlova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//t_tree	next_command(t_tree *tree)
//{
//	while (tree && tree->type != T_WORD)
//	{
//		if (tree->left && tree->left->type == T_WORD)
//			tree = tree->left;
//		else
//			tree = tree->right;
//	}
//	return (tree);
//}

char	*replace_dollars(char *str)
{
	int		start;
	char	*new_str;
	char	*result;
	int		i;
	char	*var;

	start = 0;
	i = 0;
	result = NULL;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != ' ' && !in_single_quotes(str, i))
		{
			new_str = malloc(i - start + 1);
			ft_strlcpy(new_str, &str[start], i - start + 1);
			result = ft_strjoin(result, new_str);
			free(new_str);
			start = ++i;
			while (str[i] && (str[i] == '_' || ft_isalnum(str[i])))
				i++;
			var = malloc(i - start + 1);
			ft_strlcpy(var, &str[start], i - start + 1);
			result = ft_strjoin(result, getenv(var));
			free(var);
			start = i;
			continue ;
		}
//		printf("%s\n", result);
		i++;
	}
	new_str = malloc(i - start + 1);
	ft_strlcpy(new_str, &str[start], i - start + 1);
	result = ft_strjoin(result, new_str);
	free(new_str);
//	free(str);
	return (result);
}
