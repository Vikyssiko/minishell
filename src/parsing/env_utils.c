/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 22:41:03 by alappas           #+#    #+#             */
/*   Updated: 2023/12/04 15:42:23 by alappas          ###   ########.fr       */
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
		//free!!!
		exit_shell("Error: malloc failed\n", 1, NULL);
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

t_envir	*ft_envlast(t_envir *lst)
{
	t_envir	*node;

	node = lst;
	if (node == NULL)
		return (NULL);
	while (node->next != NULL)
		node = node->next;
	return (node);
}

t_envir	*ft_envfirst(t_envir *lst)
{
	t_envir	*node;

	node = lst;
	if (node != NULL)
	{
		while (node->prev != NULL)
			node = node->prev;
	}
	return (node);
}

void	print_envir(t_envir	*envir)
{
	while (envir)
	{
		printf("%s=%s\n", envir->var_name, envir->var_value);
		envir = envir->next;
	}
}

void	print_export(t_envir *envir)
{
	while (envir)
	{
		if (!envir->var_value)
			printf("declare -x %s\n", envir->var_name);
		// else if (envir->var_value && !odd_quote(envir->var_value))
		// 	printf("declare -x %s=%s\n", envir->var_name, envir->var_value);
		else
			printf("declare -x %s=\"%s\"\n", envir->var_name, envir->var_value);
		envir = envir->next;
	}
}

void	ft_envdelone(t_envir *env_list)
{
	t_envir	*next;
	t_envir	*prev;

	if (!env_list)
		return ;
	next = env_list->next;
	prev = env_list->prev;
	if (env_list->var_name)
		free(env_list->var_name);
	if (env_list->var_value)
		free(env_list->var_value);
	if (next != NULL && prev != NULL)
	{
		prev->next = next;
		next->prev = prev;
	}
	else if (prev)
		prev->next = NULL;
	else if (next)
		next->prev = NULL;
	env_list->next = NULL;
	env_list->prev = NULL;
	free(env_list);
}

char	**new_env_array(t_data *data)

{
	t_envir *env_list;
	char	**new_env_array;
	int		i;

	if (!data->env_list)
		return (NULL);
	env_list = data->env_list;
	i = 0;
	if (data->new_env_array)
		free_2darray(data->new_env_array);
	while (env_list != NULL)
	{
		i++;
		env_list = env_list->next;
	}
	new_env_array = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	env_list = data->env_list;
	while (env_list != NULL)
	{
		new_env_array[i] = ft_strjoin(env_list->var_name, "=");
		new_env_array[i] = ft_strjoin(new_env_array[i], env_list->var_value);
		env_list = env_list->next;
		i++;
	}
	new_env_array[i] = NULL;
	data->new_env_array = new_env_array;
	return (new_env_array);
}