/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlova <vkozlova@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:35 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/06 21:37:22 by vkozlova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <termios.h>
# include <dirent.h> 
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <termcap.h>
# include <unistd.h>
# include <stdint.h>
# include <limits.h>
# include <errno.h>
# include "../libft/include/libft.h"

# define MAX_ENV_VARS 100
# define MAX_DOLLAR_VALUE_LEN 100
# define MAX_PATH_LEN 100
# define MAX_CMD_LEN 100

# define NEW_LINE_ERR	"syntax error near unexpected token `newline'"
# define SINGLE_PIPE_ERR		"syntax error near unexpected token `|'"
# define DOUBLE_PIPE_ERR		"syntax error near unexpected token `||'"
# define DEL_ERR			"syntax error near unexpected token `<<'"

typedef enum e_token_type {
	T_WORD = 1,
	T_NEWLINE,
	T_SPACE,
	T_DOLLAR,
	T_STAR,
	T_AMPER,
	T_RED_INP,
	T_RED_OUT,
	T_THREE_IN,
	T_THREE_OUT,
	T_IN_OUT,
	T_APPEND,
	T_PIPE,
	T_OR,
	T_AND,
	T_DELIM,
	T_PARENTHESES,
}	t_token_type;

typedef struct s_envir {
	char		**var_name;
	char		**var_value;
	int			count;
}				t_envir;

typedef struct s_tree {
	t_token_type	type;
	char			*value;
	char			**args_array;
	struct s_tree	*last_input;
	struct s_tree	*last_output;
	struct s_tree	*left;
	struct s_tree	*right;
}				t_tree;

typedef struct s_data {
	struct s_tree	*tree;
	struct s_token	*token_list;
	t_envir			*env_list;
	t_list			*sorted_env_list;
//	int				single_quote;
//	int				double_quote;
	long int		exit_status;
	int				cmd_nbrs;
	int				pid;
	int				count;
	int				arg_nums;
	int				parenthesis_scope;
	int				forked;
	char			*input_minishell;
	char			*input_line;
	char			*curr_dir;
	char			*exit_str;
	char			**env_array;
	char			**cmd_array;
	char			**path;
}				t_data;

typedef struct s_token
{
	t_token_type		type;
	char				*word;
	struct s_token		*next;
	struct s_token		*prev;
}					t_token;

// typedef	struct s_parenth
// {
// 	t_token	*token;
// 	int		valid;
// 	int		depth;
// 	struct s_parenth *address;
// }	t_parenth;

/* builtins.c */
void		builtin_echo(char **args);
void		builtin_pwd(void);
void		builtin_unset(t_list **head, char *var_name);
void		builtin_env(t_list *head);
void		builtin_cd(t_data *data, char *path);
void		builtin_exit(t_data *data);
char		*get_curr_dir(void);
char		*get_home_dir(void);
void		builtin_export(t_envir *env);
void		handle_builtins(t_data *data);
int			ft_is_builtin(char *cmd);

/* environment.c */
void		save_envir(t_data *data, char **env_str);
char		*find_envir_variable(t_data *data, char *var_name, int len);
void		print_env_node(void *env_node);
int			find_envir_line(t_envir *env, char *var_name);
void		free_envir_array(char **env_array);

/* exit.c */
void		exit_shell(char *message, int exit_code, t_data *data);

/* free.c */
void		free_data(t_data *data);
// void		free_flags(t_flags *flags);
// void		free_delimiter(t_delim *delimiter);
void		free_envir(t_envir *envir);
void		free_2darray(char **array);

/* handle_input.c */
void		check_exit(char *input);
void		print_parsed_input(char *command);
int			is_valid_env(char *str);
int			is_valid_env2(char *str);

/* init_data.c */
void		init_data(t_data **data, char **envp);
// t_flags			*init_flags(void);

/* parsing_commads.c */
int			lexical_analysis(t_data *data, char *input);
// int			find_command_path(t_data *data, t_cmdexe *cmd);
int			parse_command(t_data *data);
void		child(t_data *data);
// static char			*find_executable_path(char **paths, char *cmd);

/* reset.c */
void		reset_data(t_data *data);;
// void		reset_flags(t_flags *flags);

/* signals.c */
int			handle_d(t_data *data, char *line);
void		handle_c(int signo);
void		handle_signal(void);
void		start_loop(t_data *data);

/* shlvl.c */
void		incr_shell_lvl(t_data *data);
void		export(t_envir **env_list, char *var_name, char *var_value);

/* utils.c */
char		**dup_2darray(char **array);
//int			is_only_ascii(char *str);
int			len_2darray(char **array);
//int			ft_has_only_digit(char *str);
int			only_spaces_parenth(char *str);
char		*trim_input(char *input);
void		process_input(char *input, char *str, int *i, int *j);

/* Environment lists functions */
void		ft_envadd_back(t_envir **lst, t_envir *new);
void		ft_envadd_front(t_envir **lst, t_envir *new);
void		ft_envclear(t_envir **lst);
void		ft_envdelone(t_envir *lst, void (*del)(void *));
void		ft_enviter(t_envir *lst, void (*f)(void *));
t_envir		*ft_envlast(t_envir *lst);
t_envir		*ft_envnew(char *var_name, char *var_value);
int			ft_envsize(t_envir *lst);

/* quotes.c */
int			odd_quote(char *str);
int			special_chars(char *str);
int			is_escaped(char *s, int pos);
int			in_quotes(char *s, int pos);
int			last_pipe(char *str, int pos);//Comented for the moment to avoid warning

/* tokens */
int			ft_is_in_stri(char c, char *str);
int			is_chr_str(char c, char *str);
void		tokenise(t_data *data, char *str);
int			find_token2(int i, char *str, char *splt);
int			find_token(t_data *data, char *str, int *i, t_token **head);
void		free_tokens(t_token **begin, void (*del)(void *));
t_token		*create_token(t_data *data, int i);
t_token		*create_arg_token(t_data *data, char *word, enum e_token_type type);
t_token		*last_token(t_token *lst);
void		add_token(t_token **token, t_token *new);
int			set_token_type(t_data *data);
void		set_token_type2(t_token *token);
void		clean_null_tokens(t_token **head);
void		ft_listadd_back(t_token **lst, t_token *next);
t_token		*split_tokens_to_list(char **split, t_data *data);
void		token_to_cmd(t_data *data, t_token **tmp);
int			evaluate_tokens(t_data *data);
void		add_token_front(t_token **head, t_token *new);
int			tokens_len(t_token **head);
void		print_tokens(t_data *data);
void		fix_tokens(t_token **head);
void		find_ortokens(t_token **head);
void		find_andtokens(t_token **head);
void		find_append(t_token *current);
void		find_delim(t_token *current);
void		find_inout(t_token **head);
void		clean_space_tokens(t_token **head);
// void		clear_token(t_token **token, void (*del)(void*));


char		*find_executable_path(char **paths, char *cmd);

/* error check */
//int			check_threeout(t_token *token);
//int			check_threein(t_token *token);
int			check_delim(t_token *token);
int			check_first_half_delim(t_token *token);
int			check_second_half_delim(t_token *token);
int			check_append(t_token *token);
char		*check_first_token(char *str, int *i);
char		*check_first_half(char *str, int *i);
char		*check_second_half(char *str, int *i);
int			syntax_errors(t_token *token, t_data *data);
int			syntax_error_parenth(t_token **token);
int			check_prev_token(t_token **token);
int			check_next_token(t_token **token);
int			check_and(t_token *token, char *str);
int			check_red(t_token *token, char *str);
int			check_red_general(t_token *tmp);
int			check_first_half_general(t_token *tmp);
int			check_second_half_general(t_token *tmp);
int			check_red_in(t_token *token);
int			check_redin_first_half(t_token *token);
int			check_redin_second_half(t_token *token);
int			check_redin_last_part(t_token *token);
int			check_red_out(t_token *token);
int			check_first_half_out(t_token *token);
int			check_second_half_out(t_token *token);
int			check_last_part_out(t_token *token);
int			check_inout(t_token *token);
int			check_pipe_or(t_token *token);
int			check_first_half_pipe_or(t_token *tmp);
int			check_second_half_pipe_or(t_token *tmp);
int			check_numbers(t_token *tmp);

/* Command Parsing*/
int			token_len(t_token *token);

/* Parentheses */
t_token		*create_parenth_token(t_data *data, int i, char *input);
int			lexic_with_parenth(t_data *data);
void		tokenise_parenth(t_data *data, char *str);
void		tokenize_parenth2(t_data *data, char *str, int *i, t_token ***head);
int			find_parenth_token(t_data *data, char *str, int *i, t_token **head);
void		set_token_parenth2(t_token *token);
int			set_token_parenth(t_data *data);
int			only_parenth(char *str);
int			operand_error_parenth(int i);
int			find_token3(t_data *data, char *str, int *i, t_token **head);
int			find_parenthesis(char *str);
int			count_parenthesis(char *str, int *parenCount, int *parenth_total);
int			check_parenthesis(int parenCount, int parenth_total);

/*Binary Tree*/
t_tree		*build_right_branch(t_token **token, t_token *address, t_tree *tree);
t_tree		*build_right_tree(t_data *data, t_token *address);
t_tree		*build_left_tree(t_data *data, t_token *address);
t_tree		*build_left_branch(t_token **token, t_token *address, t_tree *tree);
void		print_right_tree(t_tree *tree);
void		print_left_tree(t_tree *tree);
void		init_tree(t_data *data);
int			arg_count_right(t_token *token, t_token *address);
int			arg_count_left(t_token *token, t_token *address);
t_tree		*build_tree_leaf_right(t_token **token, t_tree *tree);
t_tree		*build_tree_leaf_left(t_token **token, t_tree *tree);
void		free_tree(t_tree *tree);
t_token		*find_tree_root(t_token *token);
t_tree		*create_tree_root(t_token *token);
t_tree		*create_simple_tree(t_data *data, t_token *address);
void		build_full_tree(t_data *data, t_token *address);
t_tree		*init_parenth_tree(t_token *parenth_token);

void		last_input(t_tree *tree);
void		last_output(t_tree *tree);
#endif