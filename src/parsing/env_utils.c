/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 22:41:03 by alappas           #+#    #+#             */
/*   Updated: 2023/12/12 00:57:18 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*trim_input_env(char *input)
{
	char	*str;
	int		i;
	int		j;

	str = ft_calloc(1, ft_strlen(input) + 1);
	if (!str)
		exit_shell_no_mes(1, NULL);
	i = 0;
	j = 0;
	while ((input[i] == '\"' || input[i] == '\'') && input[i])
		i++;
	while (input[i])
	{
		while ((input[i] == '\"' || input[i] == '\''))
			(i)++;
		if (input[i])
			str[(j)++] = input[(i)++];
	}
	if (str[j] == '\"' || str[j] == '\'')
		str[j] = '\0';
	return (str);
}

t_envir	*ft_envnew(char **env_line)
{
	t_envir	*env_list;
	int		i;

	i = 0;
	env_list = malloc(sizeof(t_envir));
	if (!env_list)
		return (NULL);
	if (env_line[i])
		env_list->var_name = trim_input_env(env_line[i]);
	else
		env_list->var_name = NULL;
	i++;
	if (env_line[i])
		env_list->var_value = trim_input_env(env_line[i]);
	else
		env_list->var_value = NULL;
	env_list->next = NULL;
	env_list->prev = NULL;
	return (env_list);
}

void	ft_envadd_back(t_envir **env_list, t_envir *new)
{
	t_envir	*tmp;

	if (!env_list)
		return ;
	if (*env_list)
	{
		tmp = ft_envlast(*env_list);
		tmp->next = new;
		new->prev = tmp;
		return ;
	}
	*env_list = new;
}

t_envir	*ft_envdelone(t_envir *env_list)
{
	t_envir	*next_node;
	t_envir	*prev_node;

	if (!env_list)
		return (NULL);
	next_node = env_list->next;
	prev_node = env_list->prev;
	ft_strdel(&env_list->var_name);
	ft_strdel(&env_list->var_value);
	if (next_node != NULL && prev_node != NULL)
	{
		prev_node->next = next_node;
		next_node->prev = prev_node;
	}
	else if (prev_node && !next_node)
		prev_node->next = NULL;
	else if (next_node && !prev_node)
		next_node->prev = NULL;
	env_list->next = NULL;
	env_list->prev = NULL;
	free(env_list);
	if (prev_node)
		return (prev_node);
	return (next_node);
}

char	**new_env_array(t_data *data)
{
	t_envir	*env_list;
	char	**new_env_array;
	char	*dup;
	int		i;

	if (!data->env_list)
		return (NULL);
	env_list = data->env_list;
	if (data->new_env_array)
		free_2darray(data->new_env_array);
	new_env_array = (char **)malloc(sizeof(char *) * (ft_lilen(env_list) + 1));
	i = 0;
	env_list = data->env_list;
	while (env_list != NULL)
	{
		dup = ft_strjoin(env_list->var_name, "=");
		new_env_array[i] = ft_strjoin(dup, env_list->var_value);
		free(dup);
		env_list = env_list->next;
		i++;
	}
	new_env_array[i] = NULL;
	data->new_env_array = new_env_array;
	return (new_env_array);
}
