/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:32:51 by alappas           #+#    #+#             */
/*   Updated: 2023/12/04 15:43:50 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	reset_data(t_data *data)
{
	if (!data)
		return ;
	free_tokens(&data->token_list);
	free_list(&data->list);
	ft_strdel(&data->input_line);
	if (data->curr_dir)
		ft_strdel(&data->curr_dir);
}
