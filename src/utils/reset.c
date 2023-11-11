/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:32:51 by alappas           #+#    #+#             */
/*   Updated: 2023/11/11 22:20:17 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	reset_data(t_data *data)
{
	data->forked = 0;
	if (data->curr_dir)
		ft_strdel(&data->curr_dir);
	if (data->input_line && ft_strlen(data->input_line) > 0)
		ft_strdel(&data->input_line);
	free_tokens(&data->token_list, free);
	// free_tree(data);
}

