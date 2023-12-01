/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:35 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/28 22:58:12 by alappas          ###   ########.fr       */
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
	if (ft_strcmp(data->list->value, "env") != 0)
		return ;
	print_envir(data->env_list);
	// while (data->env_array[i])
	// {
	// 	printf("%s\n", data->env_array[i]);
	// 	i++;
	// }
}

void	pwd(void)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 1);
	printf("%s\n", cwd);
	free(cwd);
}

void exit_builtin(t_data *data, t_cmd_list *list)
{
	int		i;
	char	*str;

	i = 0;
	if (list->args_array[1])
	{
		while (list->args_array[1][i])
		{
			if (!ft_isdigit(list->args_array[1][i]))
			{
				str = put_str_to_str("exit\nminishell: exit: %s: numeric argument required\n",
									 list->args_array[1], data);
				exit_shell(str, 255, data);
			}
			i++;
		}
		if (list->args_array[2])
		{
			ft_putstr_fd("exit\nminishell: exit: too many arguments\n", STDERR_FILENO);
			data->exit_status = 1;
			return ;
		}
		exit_shell_no_free("exit\n", ft_atoi(list->args_array[1]), data);
	}
	exit_shell_no_free("exit\n", data->exit_status, data);
	// free!!!
}
