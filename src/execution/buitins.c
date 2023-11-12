/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:35 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/11 17:25:09 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_without_quotes(char *str)
{
	int		i;
	char	quote;
	int		closed;

	i = 0;
	closed = 1;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && closed)
		{
			quote = str[i++];
			closed = 0;
		}
		if (str[i] && str[i] != quote)
			printf("%c", str[i++]);
		if (str[i] == quote)
		{
			closed = 1;
			i++;
		}
	}
}

void	echo(t_tree *tree)
{
	int		i;
	int		newline;

	i = 1;
	newline = 1;
	if (ft_strcmp(tree->value, "echo") != 0)
		return ;
	if (tree->args_array[i] && ft_strcmp(tree->args_array[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (tree->args_array[i])
	{
		print_without_quotes(tree->args_array[i]);
		i++;
		if (tree->args_array[i])
			printf(" ");
	}
	if (newline)
		printf("\n");
}

void	env(t_data *data, t_tree *tree)
{
	int	i;

	i = 0;
	if (ft_strcmp(tree->value, "env") != 0)
		return ;
//	if (ft_strcmp(tree->value, "env") == 0)
//	{
		while (data->env_array[i])
		{
			printf("%s\n", data->env_array[i]);
			i++;
		}
//	}
}

void	pwd(t_tree *tree)
{
	char	*cwd;

	cwd = NULL;
	if (ft_strcmp(tree->value, "pwd") != 0)
		return ;
	// pwd: too many arguments
	// pwd: bad option: -h
	cwd = getcwd(cwd, 1);
	printf("%s\n", cwd);
	free(cwd);
//	printf("%s\n", getenv("pwd"));
}

// int	ft_is_builtin(char *cmd)
// {
// 	if (ft_strcmp(cmd, "echo") == 0)
// 		return (1);
// 	else if (ft_strcmp(cmd, "cd") == 0)
// 		return (1);
// 	else if (ft_strcmp(cmd, "pwd") == 0)
// 		return (1);
// 	else if (ft_strcmp(cmd, "export") == 0)
// 		return (1);
// 	else if (ft_strcmp(cmd, "unset") == 0)
// 		return (1);
// 	else if (ft_strcmp(cmd, "env") == 0)
// 		return (1);
// 	else if (ft_strcmp(cmd, "exit") == 0)
// 		return (1);
// 	return (0);
// }

// void	builtin_pwd(void)
// {
// 	char cwd[PATH_MAX];
// 	if (getcwd(cwd, sizeof(cwd)) != NULL)
// 		printf("%s\n", cwd);
// 	else
// 		perror("pwd");
// }

// void	builtin_unset(t_list **head, char *var_name)
// {
// 	t_list *curr = *head;
// 	t_list *prev = NULL;

// 	while (curr != NULL)
// 	{
// 		t_envir *env = (t_envir *)curr->content;
// 		if (ft_strcmp(env->var_name, var_name) == 0)
// 		{
// 			if (prev == NULL)
// 				*head = curr->next;
// 			else
// 				prev->next = curr->next;
// 			ft_lstdelone(curr, &free);
// 			return;
// 		}
// 		prev = curr;
// 		curr = curr->next;
// 	}
// }

// void	builtin_env(t_list *head)
// {
// 	t_envir *env;

// 	while (head != NULL)
// 	{
// 		env = (t_envir *)head->content;
// 		printf("%s=%s\n", env->var_name, env->var_value);
// 		printf("\n");
// 		head = head->next;
// 	}
// }

// void builtin_exit(t_data *data)
// {
// 	exit_shell("exit", 0, data);
// }

// void builtin_cd(t_data *data, char *path)
// {
// 	char *cwd;
// 	t_envir *pwd_env;

// 	if (!path) 
// 	{
// 		path = get_home_dir();
// 		if (!path)
// 		{
// 			printf("minishell: cd: HOME not set\n");
// 			return;
// 		}
// 	}
// 	if (chdir(path) != 0) {
// 		printf("minishell: cd: %s: No such file or directory\n", path);
// 		return;
// 	}
// 	cwd = get_curr_dir();
// 	if (!cwd) {
// 		printf("minishell: error getting current directory\n");
// 		return;
// 	}
// 	pwd_env = find_envir(data->env, "PWD");
// 	if (!pwd_env) {
// 		printf("minishell: PWD environment variable not found\n");
// 		free(cwd);
// 		return;
// 	}
// 	free(pwd_env->var_value);
// 	pwd_env->var_value = cwd;
// 	free(cwd);
// }

// char *get_curr_dir(void)
// {
// 	char *cwd;

// 	cwd = malloc(PATH_MAX);
// 	if (!cwd)
// 	{
// 		perror("minishell: cd: Cant get the current directory\n");
// 		return NULL;
// 	}
// 	if (!getcwd(cwd, PATH_MAX))
// 	{
// 		free(cwd);
// 		return NULL;
// 	}
// 	return cwd;
// }

// char *get_home_dir(void)
// {
// 	const char *home_dir = getenv("HOME");
// 	if (!home_dir) {
// 		perror("minishell: cd: HOME not set\n");
// 		return NULL;
// 	}
// 	return strdup(home_dir);
// }
