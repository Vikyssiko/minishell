/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:53:22 by vkozlova          #+#    #+#             */
/*   Updated: 2023/12/02 22:56:14 by alappas          ###   ########.fr       */
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
		if (handle_d(data, line))
			continue ;
		if (ft_strlen(line) > 0)
			add_history(line);
		data->input_line = trim_input(line);
		data->input_line = replace_dollars(data, data->input_line);
		ft_strdel(&line);
		if ((odd_quote(data->input_line)) || (special_chars(data->input_line))
			|| (lexical_analysis(data, data->input_line)))
			continue ;

		init_list_data(data);
		exec_pipes(data);
	}
}
