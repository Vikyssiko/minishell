/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:51:13 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/30 15:21:46 by alappas          ###   ########.fr       */
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
		// line = readline("");
		// data->input_line = "unset _";
		if (handle_d(data, line))
			continue ;
		if (ft_strlen(line) > 0)
			add_history(line);
		data->input_line = trim_input(line);
		data->input_line = replace_dollars(data->input_line, data);
		next_level(data);
		ft_strdel(&line);
//		check_exit(data->input_line);
		if ((odd_quote(data->input_line)) || (special_chars(data->input_line))
			|| (lexical_analysis(data, data->input_line)))
			continue ;

		init_tree(data);
//		exec_cmd(data, data->list);
		// manage_redir(data->list, data);
//		if (is_builtin(data->list))
//			call_builtin_func(data, data->list);
//		else
			exec_pipes(data);
	}
}

void	execute(t_data *data)
{
	t_cmd_list	*list;

	list = data->list;
	while (list)
	{
		list = list->next;
	}
}
// printf("token length: %d\n", token_len(data->token_list));
// free(data->input_line);
void	next_level(t_data *data)

{
	int	pid;
	
	if (!ft_strcmp(data->input_line, "minishell"))
	{
		printf("I entered here\n");
		pid = fork();
		if (pid < 0)
			exit (1);
		else if (pid == 0)
		{
			// printf("Entering a new 'minishell' level\n");
			incr_shell_lvl(data);
			start_loop(data);
		}
		waitpid(pid, NULL, 0);
	}
}