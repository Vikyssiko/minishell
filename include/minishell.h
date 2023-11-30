/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:35 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/28 21:58:53 by alappas          ###   ########.fr       */
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
//	T_DOLLAR,
	T_RED_INP,
	T_RED_OUT,
	T_APPEND,
	T_PIPE,
	T_DELIM,
}	t_token_type;

typedef struct s_envir {
	char			*var_name;
	char			*var_value;
	int				equal;
	struct s_envir	*next;
	struct s_envir	*prev;
}				t_envir;



typedef struct s_token
{
	t_token_type		type;
	char				*word;
	struct s_token		*next;
	struct s_token		*prev;
}					t_token;

typedef struct s_redir {
	t_token 		*redir_token;
	t_token 		*redir_word;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd_list {
//	t_token_type		type;
	char				*value;
//	char				*delim;
	char				**args_array;
	t_redir 			*redir_list;
	struct s_cmd_list	*next;
//	struct s_tree	*prev;
}				t_cmd_list;

typedef struct s_tree {
	t_token_type	type;
	char			*value;
	char			*delim;
	char			**args_array;
	struct s_tree	*left;
	struct s_tree	*right;
}				t_tree;

typedef struct s_data {
	struct s_tree	*tree;
	struct s_token	*token_list;
	t_envir			*env_list;
	t_envir			*export_list;
	int				exit_status;
	int				pid;
	int				arg_nums;
	int				forked;
	char			*input_minishell;
	char			*input_line;
	char			*curr_dir;
	char			*exit_str;
	char			**env_array;
	char			**cmd_array;
	char			**path;

	t_cmd_list		*list;
}				t_data;

/* builtins.c */
void		builtin_unset(t_list **head, char *var_name);
void		builtin_env(t_list *head);

/* environment.c */
void		save_envir(t_data *data, char **env_str);
char		*find_envir_variable(t_data *data, char *var_name);
void		print_env_node(void *env_node);
int			find_envir_line(t_envir *env, char *var_name);
void		free_envir_array(char **env_array);

/* exit.c */
void		exit_shell(char *message, int exit_code, t_data *data);

/* free.c */
void		free_data(t_data *data);
void		free_envir(t_envir *envir);
void		free_2darray(char **array);
void		ft_envclear(t_envir **env_list);

/* handle_input.c */
//void		check_exit(char *input);
void		print_parsed_input(char *command);
int			is_valid_env(char *str);
int			is_valid_env2(char *str);
char		*replace_dollars(char *str, t_data *data);

/* init_data.c */
void		init_data(t_data **data, char **envp);

/* parsing_commads.c */
int			lexical_analysis(t_data *data, char *input);
char *		find_command_path(t_data *data, t_cmd_list *list);
int			parse_command(t_data *data);
void		child(t_data *data);
// static char			*cutable_path(char **paths, char *cmd);

/* reset.c */
void		reset_data(t_data *data);

/* signals.c */
int			handle_d(t_data *data, char *line);
void		handle_c(int signo);
void		handle_signal(void);
void		start_loop(t_data *data);

/* shlvl.c */
void		incr_shell_lvl(t_data *data);

/* utils.c */
char		*trim_input(char *input);
void		process_input(char *input, char *str, int *i, int *j);

/* Environment lists functions */
// void		ft_envadd_back(t_envir **lst, t_envir *new);
// void		ft_envadd_front(t_envir **lst, t_envir *new);
// void		ft_envclear(t_envir **lst);
// void		ft_envdelone(t_envir *lst, void (*del)(void *));
// void		ft_enviter(t_envir *lst, void (*f)(void *));
t_envir		*ft_envlast(t_envir *lst);
t_envir		*ft_envfirst(t_envir *lst);
t_envir		*ft_envnew(char **env_line);
void		ft_envadd_back(t_envir **env_list, t_envir *new);
t_envir		*create_env_list(char **envp);
void		print_envir(t_envir	*envir);
void		print_export(t_envir	*envir);
void		ft_envdelone(t_envir *env_list);
t_envir 	*swap_env(t_envir *first, t_envir *second);
t_envir		*create_export_list(char **envp);
char		**ft_singlesplit(char const *s, char c);
t_envir		*sort_export(t_envir **export);
t_envir		*find_envir_node(t_envir *env_list, char *var_name);
void		cd_home(t_data *data, t_envir *env_list);
void		cd_folder(t_data *data, t_envir *env_list, char *pwd);
// int			ft_envsize(t_envir *lst);

/* quotes.c */
int			odd_quote(char *str);
int			special_chars(char *str);
int			in_quotes(char *s, int pos);
int			in_single_quotes(char *s, int pos); // ??

/* tokens */
char		*ft_strstr(const char *haystack, const char *needle);
int			ft_is_in_stri(char c, char *str);
int			is_chr_str(char c, char *str);
void		tokenise(t_data *data, char *str);
void		free_tokens(t_token **begin, void (*del)(void *));
t_token		*create_token(t_data *data, int i, int len);
t_token		*create_arg_token(t_data *data, char *word, enum e_token_type type);
void		add_token(t_token **token, t_token *new);

void		add_redir_token(t_redir **head, t_redir *redir);
t_redir		*create_redir_token(t_token *redir_token, t_token *word);

int			token_analysis(t_data *data);
void		set_token_type(t_token *token);
void		print_tokens(t_data *data);
void		find_append(t_token *current);
void		find_delim(t_token *current);
void		find_redir(t_token **head);


char		*find_executable_path(char **paths, char *cmd);

/* error check */
int			check_delim(t_token *token);
int			check_append(t_token *token);
char		*check_first_token(char *str, int *i);
char		*check_token(char *str, int *i);
int			syntax_errors(t_token *token, t_data *data);
int			check_red(t_token *token);
int			check_pipe(t_token *token);

/*Binary Tree*/
t_tree		*build_right_branch(t_token **token, t_token *address, t_tree *tree);
void		print_right_tree(t_tree *tree);
void		init_tree(t_data *data);
int			arg_count_right(t_token *token, t_token *address);
t_tree		*build_tree_leaf_right(t_token **token, t_tree *tree);
// void		free_tree(t_data *data);
void		free_tree(t_tree **tree);
t_tree		*create_simple_tree(t_data *data, t_token *address);
t_tree		*build_first_tree_leaf_redir(t_token **token, t_tree *tree);
t_tree		*init_tree_data();

/* builtins */
int			is_builtin(t_cmd_list *list);
void		call_builtin_func(t_data *data, t_cmd_list *list);
void		echo(t_cmd_list *list);
void		env(t_data *data);
void		unset(t_envir **env_list, t_cmd_list *list, int value);
void		export(t_envir **env_list, t_envir **export_list, t_cmd_list *list);
void		check_env(t_envir **env_list, char **arg);
int			unset_helper(char *list_arg, int value);
int			export_helper(char *list_arg);
void		pwd(void);
void		cd(t_data *data, t_cmd_list *list);
void 		exit_builtin(t_data *data, t_cmd_list *list);

void		manage_redir(t_cmd_list *list, t_data *data);

int			exec_cmd(t_data *data, t_cmd_list *list);
int			exec_pipe(t_data *data, t_cmd_list *list);
int			exec_pipes(t_data *data);

char 		*put_str_to_str(char *dest, char *src, t_data *data);
void		exit_shell_no_free(char *message, int exit_code, t_data *data);

#endif