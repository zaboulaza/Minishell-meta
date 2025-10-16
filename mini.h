/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:14:12 by nsmail            #+#    #+#             */
/*   Updated: 2025/10/16 16:55:19 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include "libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <ncurses.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/resource.h>
# include <sys/types.h>
# include <sys/wait.h>

# define WORD 0
# define PIPE 1
# define OR 2
# define AND 3
# define OPEN_PAREN 4
# define CLOSE_PAREN 5
# define REDIR_IN 6
# define REDIR_OUT 7
# define REDIR_APPEND 8
# define HEREDOC 9

# define CMD 10
# define SUBSHELL 11

typedef struct s_node
{
	int							type;
	char						*content;
	int							id;
	struct s_node				*next;
}								t_node;

typedef struct s_satoi
{
	long double					val;
	int							err_code;
}								t_satoi;

typedef struct s_pwd
{
	char						*prev;
	char						*tmp;
	char						*new;
	int							exit_status;
}								t_pwd;

typedef struct s_env
{
	char						*key;
	char						*value;
	struct s_env				*next;
}								t_env;

typedef struct s_tmp
{
	char						*path;
	int							mode;
	char						**heredoc_content;
	struct s_tmp				*next;
}								t_tmp;

typedef struct s_files
{
	char						*path;
	int							mode;
	char						**heredoc_content;
	struct s_files				*next;
}								t_files;

typedef struct s_cmd
{
	int							type;
	char						**args;
	t_files						*files;
	struct s_cmd				*right;
	struct s_cmd				*left;
	struct s_cmd				*next;
}								t_cmd;

typedef struct s_general
{
	int							ac;
	char						**av;
	char						*one_line;
	char						**env;
	char						**path;
	int							status;
	int							signaled;
	struct s_node				*node;
	struct s_cmd				*cmd;
	struct s_tmp				*tmp;
	struct s_env				*envlst;
	struct s_pwd				*pwd;
}								t_general;

// Variables globales
extern volatile sig_atomic_t	g_signal_status;

// main.c
////////////////////////////////////////////////////////////////////////////
int								main(int ac, char **av, char **env);
void							creat_struct(t_general *g, int ac, char **av,
									char **env);
void							free_all(t_general *g);

// ##############################  parser.c  ##############################
int								parsing_general(t_general *g, t_tmp **tmp);

// ##############################  token_first.c  #########################
int								token_first(t_general *g);
// tokenizer_utils1.c
int								quote(t_general *g);
int								bracket(t_general *g, int i);
int								and_(t_general *g);

// ##############################  creat_list.c  ###########################
int								add_to_liste(t_node **node, char *line);
t_node							*new_node(char *line);
char							*next_step(char *line);
int								next_step_norm(char *line);
int								next_step_norm2(char *line);
// creat_list_urils1.c
int								find_type(char *line);
int								ispacce(char c);
char							*find_content(char *line);
int								find_content_norm(char *line);
int								list_size(t_node *node);
// creat_list_urils2.cPIPE
int								find_content_norm1(char *line);

// ##############################  token_second.c  ##########################
// parser la list
int								token_second(t_node **node);
int								team_redir(t_node *tmp);
int								team_and_or(t_node *tmp);
int								team_open_parent(t_node *tmp);
int								team_close_parent(t_node *tmp);
int								team_word(t_node *tmp);
int								token_second_norme(t_node *tmp);

// ##############################  token_third.c  ##########################

int								token_third(t_general *g, t_tmp **tmp);
int								add_to_cmd_liste(t_cmd **cmd, t_node *node,
									t_tmp **tmp);
t_cmd							*new_cmd(t_node *node, t_tmp **tmp);
t_node							*next_step_cmd(t_node *node);

// token_third_utils.c
t_node							*next_step_norm_cmd(t_node *node);
int								find_cmd_type(t_node *node);
char							**find_arg(t_cmd *cmd, t_node *node,
									t_tmp **tmp);
char							*ft_strjoin_(char *s1, char *s2);
char							**find_arg_norm_parent(t_node *node, t_cmd *cmd,
									t_tmp **tmp);

// token_third_utils2.c
void							free_all_(char **tab);
size_t							count_word_(char *s, char c);
char							*malloc_word_(char *str, char c);
char							**ft_split_(char *s, char c);
char							*quote_norm(char *line);
// token_third_utils3.c
int								add_to_files_liste(t_cmd *cmd, t_node *node,
									t_tmp **tmp);
t_files							*new_files(t_node *node);
char							**find_arg_norm(t_cmd *cmd, t_node *node,
									t_tmp **tmp);
int								add_to_tmp_liste(t_node *node, t_tmp **tmp);
t_tmp							*new_tmp(t_node *node);
// token_third_utils4.c
void							add_tmp_to_list(t_cmd *cmd, t_tmp **tmp);
void							remove_invalid_cmds(t_cmd **cmd_list);
int								find_arg_norm_parent2(t_node *node);
char							**heredoc_content(char *node);
char							*ft_strjoin__(char *s1, char const *s2);
// token_third_utils5.c
char							**cpy_char_tab(char **tab);
void							find_arg_norm3(t_cmd *cmd, t_tmp **tmp,
									t_tmp *cur);
void							handle_tmp_and_set_type(t_cmd *cmd,
									t_tmp **tmp);
t_node							*process_parent_content(t_node *node,
									char **arg, int count);
// token_third_utils6.c
char							*handle_heredoc_error(char *all_content,
									char *line, char *node);
char							*process_heredoc_line(char *all_content,
									char *line);
char							*read_all_heredoc_lines(char *node);
// last_verif_parent.c
int								last_verif_parent(t_cmd *cmd);
// ##############################  token_third.c  ##########################

// creat_ast.c
t_cmd							*init_ast(t_cmd *cmd, bool mini_ast_pipe);
int								priorite(t_cmd *operateur);
t_cmd							*creat_ast_exemple(t_cmd *operateur,
									bool mini_ast_pipe);
t_cmd							*next_operateur_and_or(t_cmd *next_cmd);

// ##############################  exec  ##########################
// ##############################  exec  ##########################
// ##############################  exec  ##########################

// exec_general.c
int								exec(t_cmd *cmd, t_general *g);
int								is_built_in(t_cmd *cmd);

// exec_ast.c
int								exec_ast(t_cmd *cmd, t_general *g);
void							exec_and(t_cmd *cmd, t_general *g);
void							exec_or(t_cmd *cmd, t_general *g);
void							exec_pipe(t_cmd *cmd, t_general *g);
void							exec_subshell(t_cmd *cmd, t_general *g);

// exec_cmd.c
void							join_cmd_to_paths(t_general *g, char *cmd_name);
int								exec_cmd(t_cmd *cmd, t_general *g);
int								waitepid_and_status(pid_t pipes, t_general *g);
void							make_execve(t_cmd *cmd, t_general *g);
void							make_execve_slash(t_cmd *cmd, t_general *g);

// exec_cmd_utils.c
int								find_quote(char *str);
int								compt_heredoc(t_cmd *cmd);
int								redir_g(t_files *tmp_files);
int								redir_in(t_files *tmp_files);
int								redir_out(t_files *tmp_files);

// exec_cmd_utils2.c
int								redir_append(t_files *tmp_files);
int								redir_heredoc(t_files *tmp_files, int compt);
char							**removed_quoat(char **arg);

// exec_cmd_utils3.c
char							*remove_outer_quotes(char *str);
int								handle_single_quote(char *str, int *i,
									char *result, int *j);
int								handle_double_quote(char *str, int *i,
									char *result, int *j);

// get_path.c
void							get_path(t_general *g, int i);
// int								ft_strncmp_(const char *s1, const char *s2,
//									size_t n);

// expand.c
char							**expand(char **arg, t_general *g);
int								check_if_need_to_expand(char *arg, int j);
char							*find_in_path(char *arg, t_general *g, int j,
									int len);
char							*ft_strjoin_one_char(char *s1, char s2);
char							*expand_line(char *line, t_general *g);

// expand_utils.c
int								process_double_quote(char *line, int *i,
									char **res, t_general *g);
int								process_single_quote(char *line, int *i,
									char **res);
int								process_variable(char *line, int *i, char **res,
									t_general *g);

int								ft_fork(void);

// ##############################  signals  ##########################
// ##############################  signals  ##########################
// ##############################  signals  ##########################

// signals.c
void							set_signal_child(void);
void							ft_signal(void);
void							signal_handler(int sig);
int								sig_event(void);
// signals2.c
void							ft_signal_heredoc(void);
void							heredoc_signal_handler(int sig);
// ##############################  test->need to remove  ##########################
// ##############################  test->need to remove  ##########################
// fonction de test
// void				print_list(t_node *node);
void							print_list_cmd(t_cmd *cmd);
void							free_node(t_node *node);
void							free_cmd(t_cmd *cmd);
void							clear_tmp(t_tmp **tmp);
void							print_ast(t_cmd *node, int depth);
void							print_indent(int depth);
void							free_g(t_general *g);

/*BUILT INS*/
void							exec_built_in(t_cmd *cmd, t_general *g);

t_satoi							ps_atoi(char *str);
int								ft_strcmp(const char *s1, const char *s2);
int								print_pwd(t_cmd *cmd);
void	manage_exit(t_cmd *cmd, t_general *g);
void							move_cd(t_cmd *cmd, t_general *g);
void							free_double(char **str);
int								manage_echo(t_cmd *cmd);
void							do_export(t_cmd *cmd, t_general *g);
void							do_unset(t_cmd *cmd, t_general *g);
int								get_env(t_general *g);
void							init_env(t_env **env_list, char **env);
char							*get_env_value(t_general *g, const char *key);
t_env							*env_to_envlst(char **envp);
int								print_env(t_general *g);
void							print_export(t_env *env);

#endif

// garbege colector

// valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes
// -q --suppressions=./ignore_leak_readline ./MINI

// ################################################################################################ #
// sl | lksadj ls < dsf > df ds | ""fdsf sdf""fds sdfafja"ajakhdf"sdkafjah | < out | > in cat > fd
// -e | (jsdahf | dfsad)
// ((date) && (whoami))

// ls | -la mdr le test il pete un cable
// regarde si tu leak pas dans les enfants c'est possible
// ls || cat && ls | wc | wc -l && ls
// ft_ft_fork