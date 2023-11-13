/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlova <vkozlova@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:07:25 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/13 14:07:25 by vkozlova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


// check cd when unset is ready, there is a comment above cd function
void	unset(t_data *data, t_tree *tree)

{
	int		i;
	char	*s;

	i = 1;
//	if (ft_strcmp(tree->value, "unset") != 0)
//		return ;
	if (!tree->args_array[i])
		return ;
	if (unset_helper(tree->args_array[i]))
		return ;
	if (ft_strcmp(tree->value, "unset") == 0 && tree->args_array[i])
	{
		while (data->env_array[i])
		{
			if (ft_strncmp(data->env_array[i], tree->args_array[i], ft_strlen(tree->args_array[i])) == 0)
			{
				s = data->env_array[i + 1];
				free(data->env_array[i]);
				data->env_array[i] = NULL;
				data->env_array[i] = s;
				i++;
				while (data->env_array[i])
				{
					data->env_array[i] = data->env_array[i + 1];
					i++;
				}
			}
			i++;
		}
	}
}

int	unset_helper(char *tree_arg)

{
	int	i;
	// int	len;

	i = 0;
	while (tree_arg[i])
	{
		if ((ft_isalnum(tree_arg[i]) || tree_arg[i] != '_') && ((!ft_isalpha(tree_arg[0])) && tree_arg[0] != '_'))
			return (printf("unset: `%s': not a valid identifier\n", tree_arg), 1);
		i++;
	}
	// len = ft_strlen(tree_arg);
	// if (env[len + 1] != '=')
	// 	return (0);
	return (0);
}
