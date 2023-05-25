/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouissa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:54:47 by met-tahe          #+#    #+#             */
/*   Updated: 2023/05/21 19:18:38 by rbouissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# define no_quotes 0
# define isingle_quotes 1
# define idouble_quotes 2

typedef struct s_mini
{
	int				valid;
	char			*data_var;
	char			*data_val;
	struct s_mini	*next;
}					t_mini;

typedef struct s_list
{
	char			*data;
	int				token;
	struct s_list	*next;
}					t_list;

typedef struct s_norm
{
	char			*cmd;
	char			*hrd;
	char			**herdoc;
	char			**full_cmd;
	int				check;
	char			*spliter;
	int				token;
	int				token2;
}					t_norm;
typedef struct s_norm2
{
    char	*new_str;
	char	*var;
	char	*valeur;
	char	*dollar;
	int		quotes;
	int		i;
	int		k;
	int		j;
	int		e;
	int		h;
    
}   t_norm2;
typedef struct s_nor_sp
{
    int		i;
	int		e;
	char	*node;
	char	*st;
	int		j;
	int		k;
	int		check;
	int		token;
	int		quotes;
	int		check_q;
}   t_nor_sp;
typedef struct s_cmd
{
	char			**herdoc;
	int				herdoc_token;
	char			**cmd;
	int				infile;
	int				outfile;
	struct s_cmd	*next;
}					t_cmd;
typedef struct s_vars
{
	int				**fd;
	int				pip_count;
	int				i;
	char			**paths;
	int				check;
	int				stat1;
}					t_vars;

typedef struct s_global
{
	t_list			*m_cmd;
	t_mini			*m_env;
	int				status;
	int				hrdsize;
	int				**hrd;
	int				hrd_id;
	int				count_cmd;
	pid_t			*id;
	int				num_phrd;
}					t_global;

t_global			*my_global;

/*-----------------------------------MY PART--------------------------------*/
t_cmd				*ft_last_new(void *tmp);
void				ft_pwd(void);
//char				*ft_strjoin(char *s1, char *s2);
int					ft_strchr(char *s, int c);
t_list				*ft_last(void *tmp);
int					ft_strncmp(char *s1, char *s2, int len);
void				ft_env(t_mini *lst);
t_list				*sort_list(t_list *lst, int (*cmp)(char *, char *));
void				freestack(t_list **stack);
void				cd_error(char *path);
void				add_back_lst(t_mini **lst, t_mini *new);
t_mini				*ft_add_new(char *var, char *value, int valid);
t_mini				*last_lst(t_mini *a);
t_mini				*env_iniit(char **env);
char				*ft_substr(char *s, int start, int len);
char				**var_split(char *s, char c);
void				ft_putstr_fd(char *s, int fd);
void				ft_export(char *var);
int					ft_atoi(char *str);
int					s_digit(char *s);
void				ft_free(char **str);
int					check_error(char *s);
void				exec_cmd(t_mini *mini, t_cmd *cmd, char **env);
void				echo(char **cmd);
void				ft_unset(char *var, t_mini **tmp);
void				ft_cd(char *path, t_mini *lst);
char				*heredoc(char **herdoc);
char				*get_path();
void				execute(char **cmd, char **paths, char **env);
void				close_pipes(int pip_count, int **fd);
void				close_pipes2(int pip_count, int **fd, char **herdoc);
void				fct_error(char *str);
void				shell_error(char *str);
void				ft_exit(char *str);
void				parent_closing(int i, int pip_count, int **fd,
						char **herdoc);
void				ctrlc_handler(int sig);
void				ctrld_handler(int sig);
void				sig_sil(int sig);
void				rl_replace_line(const char *text, int clear_undo);
void				multiple_cmd(t_cmd **cmd, t_vars *vars, char **env,
						t_mini *mini, int *n);
int					ft_tolower(int c);
void				struct_free(t_vars *vars);
void				global_free(void);
void				check_parent(t_vars **vars);
/*---------------------------------REDA PART---------------------------------------------*/
char				**ft_split(char *s, char c);
int					ft_strcmp(char *s1, char *s2);
char				*ft_strjoin(char *left_str, char *buff);
t_list				*split_fuul_cmd(char **s);
char				*ft_strcpy(char *dest, char *src);
char				*ft_strdup(char *src);
char				**split_command(char *str);
void				ft_lstadd_back(t_list **lst, t_list *new);
t_list				*ft_lstnew(char *content, int t);
int					check_eroor(char *str);
void				ft_write(char *s);
int					check_string(char *str);
size_t				ft_strlen(char *s);
t_list				*ft_split_them(char *str);
t_cmd				*ft_lstnew_new(char **content, int t, int k, char **her,
						int t_her);
void				ft_lstadd_back_new(t_cmd **lst, t_cmd *new);
t_cmd				*split_to_commands(t_list *comm);
int					ther_are_pipe(char *str);
char				*handle_quotes(char *str, t_mini *env);
int					find_spliter(char s, char *sp);
char				*ft_itoa(int n);
int					check_eroor(char *str);
char				*remove_quotes(t_list *node);
int					size_of_quotes(char *c);
char				*string_no_quotes(char *str);
char				*new_expand(char *str, t_mini *env);
int					find_spliter1(char s, char *sp);
int					is_digit1(char s);
int					is_allpha1(char s);
char				*finnd_valeur(t_mini *env, char *str);
int					ft_check_cote(char *str, int i);
void				ft_free_cmd(t_list *list);
void				ft_free_cmd2(t_cmd *list);

#endif
