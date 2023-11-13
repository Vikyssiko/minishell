/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlova <vkozlova@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:36 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/07 13:58:21 by vkozlova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//void	check_exit(char *input)
//{
//	if (!ft_strncmp("exit", input, ft_strlen("exit")))
//	{
//		free(input);
//		exit(0);
//	}
//}

void	print_parsed_input(char *command)
{
	if (command != NULL)
		printf("Command: %s\n", command);
	else
		printf("Failed to parse the input.\n");
}

int	is_valid_env(char *str)
{
	int	i;
	int	eq_sign;

	i = 0;
	eq_sign = 0;
	while (str[i])
	{
		if (i == 0 && (ft_isdigit(str[i] || str[i] == '=')))
			return (0);
		if (!ft_isalnum(str[i] && str[i] != '_' && str[i] != '=')
			&& str[i] != '+' && str[i] != '\'' && str[i] != '\"')
			return (0);
		if ((str[i] == '\'' || str[i] == '\"') && eq_sign < 1)
			return (0);
		if (str[i] == '=')
			eq_sign++;
		i++;
	}
	if (eq_sign)
		return (1);
	return (0);
}

int	is_valid_env2(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i == 0 && ft_isdigit(str[i]))
			return (0);
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
