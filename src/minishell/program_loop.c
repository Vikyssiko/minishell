/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:51:13 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/11 16:42:03 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	start_loop(t_data *data)
{
	char	*line;

	while (1)
	{
		reset_data(data);
		line = readline(data->input_minishell);
		// data->input_line = "(1 | 2)";
		if (handle_d(data, line))
			continue ;
		if (ft_strlen(line) > 0)
			add_history(line);
		data->input_line = trim_input(line);
		data->input_line = replace_dollars(data->input_line, data);
//		printf("%s\n", data->input_line);
		ft_strdel(&line);
		check_exit(data->input_line);
		if ((odd_quote(data->input_line)) || (special_chars(data->input_line))
			|| (lexical_analysis(data, data->input_line)))
			continue ;
		init_tree(data);
		echo(data->tree);
		env(data, data->tree);
		pwd(data->tree);
//		 print_tree(data->tree);
	}
}
// printf("token length: %d\n", token_len(data->token_list));
// free(data->input_line);
