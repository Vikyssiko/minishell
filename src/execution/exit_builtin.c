/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 21:29:06 by vkozlova          #+#    #+#             */
/*   Updated: 2023/12/05 23:31:36 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_arg_is_num(t_data *data, t_cmd_list *list)
{
	int		i;
	char	*str;

	i = 0;
	while (list->args_array[1][i])
	{
		if (!ft_isdigit(list->args_array[1][i]))
		{
			str = put_str_to_str("exit\nminishell: exit: "
					"%s: numeric argument required\n",
					list->args_array[1], data);
			exit_shell(str, 255, data);
		}
		i++;
	}
}

void	exit_builtin(t_data *data, t_cmd_list *list)
{
	if (list->args_array[1])
	{
		check_arg_is_num(data, list);
		if (list->args_array[2])
		{
			ft_putstr_fd("exit\nminishell: exit: too many arguments\n",
				STDERR_FILENO);
			data->exit_status = 1;
			return ;
		}
		exit_shell_no_free("exit\n", ft_atoi(list->args_array[1]), data);
	}
	exit_shell_no_free("exit\n", data->exit_status, data);
	//free
}
