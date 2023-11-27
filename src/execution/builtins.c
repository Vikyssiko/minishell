/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:35 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/27 22:53:49 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(t_cmd_list *list)
{
	if (list && list->value)
	{
		if (ft_strcmp(list->value, "echo") == 0)
			return (1);
		else if (ft_strcmp(list->value, "cd") == 0)
			return (1);
		else if (ft_strcmp(list->value, "pwd") == 0)
			return (1);
		else if (ft_strcmp(list->value, "export") == 0)
			return (1);
		else if (ft_strcmp(list->value, "unset") == 0)
			return (1);
		else if (ft_strcmp(list->value, "env") == 0)
			return (1);
		else if (ft_strcmp(list->value, "exit") == 0)
			return (1);
	}
 	return (0);
}

void	call_builtin_func(t_data *data, t_cmd_list *list)
{
	if (ft_strcmp(list->value, "echo") == 0)
		echo(list);
	else if (ft_strcmp(list->value, "cd") == 0)
		cd(data, list);
	else if (ft_strcmp(list->value, "pwd") == 0)
		pwd();
	else if (ft_strcmp(list->value, "export") == 0)
		export(&(data->env_list), &(data->export_list), list);
	else if (ft_strcmp(list->value, "unset") == 0)
	{
		unset(&(data->env_list), list, 0);
		unset(&(data->export_list), list, 1);
	}
	else if (ft_strcmp(list->value, "env") == 0)
		env(data);
	else if (ft_strcmp(list->value, "exit") == 0)
		exit_builtin(data, list);
}

void	env(t_data *data)
{
	int	i;

	i = 0;
	if (ft_strcmp(data->list->value, "env") != 0)
		return ;
	print_envir(data->env_list);
	// while (data->env_array[i])
	// {
	// 	printf("%s\n", data->env_array[i]);
	// 	i++;
	// }
}

// pwd: too many arguments
// pwd: bad option: -h
void	pwd(void)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 1);
	printf("%s\n", cwd);
	free(cwd);
}

// shouldn't change the directory if HOME variable is unset
// need to check when unset is ready
//
//If no directory operand is given and the HOME environment
//variable is empty or undefined, the default behavior is
//implementation-defined and no further steps shall be taken.
//
//function doesn't change PWD variable
void	cd(t_data *data, t_cmd_list *list)
{
//	if (ft_strcmp(tree->value, "cd") != 0)
//		return ;
	t_envir	*head_env;
	t_envir	*head_exp;
	
	head_env = data->env_list;
	head_exp = data->export_list;
	if (!(list->args_array[1]))
	{
		if (find_envir_node(data->env_list, "HOME") == NULL)
			printf("cd: HOME not set\n");
		else if (chdir((find_envir_node(data->env_list, "HOME"))->var_value) == -1)
		{
			printf("cd: %s: no such file or directory\n", find_envir_node(data->env_list, "HOME")->var_value);
			data->exit_status = errno;
		}
		else
		{
			cd_home(data, data->env_list);
			cd_home(data, data->export_list);
		}
	}
	else if (list->args_array[1] && chdir(list->args_array[1]) == -1)
	{
		printf("cd: no such file or directory: %s\n", list->args_array[1]);
		data->exit_status = errno;
	}
//		perror(ft_strjoin("cd: no such file or directory: ", tree->args_array[1]));
}

void	cd_home(t_data *data, t_envir *env_list)

{
	
	chdir(find_envir_variable(data, "HOME"));
	env_list = find_envir_node(env_list, "PWD");
	free(env_list->var_value);
	env_list->var_value = ft_strdup(find_envir_variable(data, "HOME"));
}

void exit_builtin(t_data *data, t_cmd_list *list)
{
	int i;

	i = 0;
	if (list->args_array[1])
	{
		while (list->args_array[1][i])
		{
			if (!ft_isdigit(list->args_array[1][i]))
			{
				printf("bash: exit: %s: numeric argument required\n", list->args_array[1]);
				exit_shell("exit", data->exit_status, data);
			}
			i++;
		}
		if (list->args_array[2])
		{
			printf("minishell: exit: too many arguments\n");
			return ;
		}
		exit_shell("exit", ft_atoi(list->args_array[1]), data);
	}
	exit_shell("exit", data->exit_status, data);
	// free!!!
}

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
