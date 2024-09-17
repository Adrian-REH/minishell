/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:14:52 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:23:07 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <inttypes.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <limits.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <sys/param.h>
# include "../../lib/libft/libft.h"
# define READ 0
# define WRITE 1

typedef struct s_data
{
	char	**tokens;
	int		is_op;
	int		len_tokens;
	int		i;
	int		oid;
}			t_data;

typedef struct s_file
{
	int		input;
	int		output;
	int		fd_aux[2];
	char	*end_heredoc;
	char	**content;
	int		len_content;
	char	*in_dir_file;
	char	*odfile;
}			t_file;

typedef enum e_operators
{
	OP_EMPTY,
	OP_GREATER,
	OP_LESS,
	OP_HEREDOC,
	OP_APPEND,
	OP_AMPER,
	OP_PIPE,
	OP_OR,
	OP_AND,
	OP_INVALID,
}	t_operators;

typedef enum e_op_block
{
	BLOCK_EMPTY,
	BLOCK_AND,
	BLOCK_OR,
}	t_op_block;

typedef enum e_states
{
	EMPTY,
	DQUOTES,
	SQUOTES,
	PIPE,
	OR,
	LESS,
	HEREDOC,
	GREATER,
	APPEND,
	AMPER,
	AND,
	INVALID,
	SPACES_NW,
	SPACES_BTW,
	NOT_OPERATOR,
	OPEN_PAREN,
	CLOSE_PAREN,
	UNIQ_COMMAND,
}	t_states;

typedef struct s_block
{
	struct s_exec	*prev_exec;
	struct s_exec	*next_exec;
	int				len_exec_prev;
	int				len_exec_next;
	int				len_exec;
	int				op;
	int				priority;
	int				type;
	int				fd[2];
	t_file			file;
	int				status;
	int				isnext;
}					t_block;

typedef struct s_automata
{
	void	*data;
	char	**alphabet;
	char	**errors;
	char	*str;
	int		state;
	int		ostate;
	int		errorlen;
	int		i;
	int		j;
	int		(*get_state)(int state, int abc_idx);
	void	(*fsa[20])(struct s_automata *a, void *data);
	void	(*fta[20][20])(struct s_automata *a, void *data);
}			t_automata;

typedef struct s_cmd
{
	char				**cmd;
	char				*line;
	int					fd_aux[2];
	pid_t				pid;
	int					status;
	int					towait;
	struct s_handler	*handler;
}						t_cmd;

/*
Aqui les dare las propiedades para ejecutarse,
si necesita redirijir o si tienen que tener
alta prioridad porque estan en parentesis
*/
typedef struct s_exec
{
	int					priority;
	int					finish;
	int					*state;
	int					op;
	struct s_exec		*blocks;
	t_file				file;
	int					status;
	t_cmd				*cmd;
	struct s_handler	*handler;
	int					*(*func[20][20])(struct s_exec *rule, int index);
}						t_exec;

/*
hanndler sabe que funcion debe llamar para
configurar s_exec, por tanto hay que 
inicializar las fucniones respectoa  los estados
luego debo programar la matriz de estados.
*/
typedef struct s_handler
{
	char				**operators;
	char				**builtins;
	t_block				*block;
	int					len_block;
	char				*line;
	t_cmd				*w_cmd;
	int					n_pids;
	t_data				*info;
	int					state[3];
	int					code;
	char				**env;
	struct s_handler	*(*seg[5])(struct s_handler *rule);
	void				(*fb[10])(struct s_cmd *cmd);
	void				(*fta[20][20][20])(struct s_handler *rule, int i);
}						t_handler;
/*------------EXECUTE--------------*/
int			dispatch_command_built(t_exec *e);
void		ft_exec_echo(t_cmd *cmd);
void		ft_exec_echon(t_cmd *cmd);
void		ft_exec_cd(t_cmd *cmd);
void		ft_exec_pwd(t_cmd *cmd);
void		ft_exec_export(t_cmd *cmd);
void		ft_exec_unset(t_cmd *cmd);
void		ft_exec_env(t_cmd *cmd);
void		ft_exec_exit(t_cmd *cmd);
int			*ft_exec_wildcard(t_exec *e);//terminar
int			*ft_exec_pipe(t_exec *e, int index);
int			*ft_exec_heredoc(t_exec *e, int index);
int			*ft_exec_cmd(t_exec *e, int index);
int			*ft_exec_greater(t_exec *e, int index);
int			*ft_exec_amper(t_exec *e, int index);
int			*ft_exec_append(t_exec *e, int index);
int			*ft_exec_less(t_exec *e, int index);
/*------------FSM--------------*/
t_handler	*ft_parser(t_handler *s);
t_handler	*ft_execute(t_handler *s);
t_handler	*ft_error(t_handler *s);
t_handler	*ft_clear(t_handler *s);
t_handler	*ft_execute(t_handler *s);
t_handler	*ft_config(t_handler *s);
t_handler	*ft_subprocess(t_handler *handler);
/*------------LEARNING--------------*/
void		init_handler(t_handler *s);
void		tactions_builtins_init(t_handler *a);
void		builtings_init(t_handler *a);
int			get_state(int i, int j);
void		errors_init(t_automata *a);
void		alphabet_init(t_automata *a);
void		tactions_init(t_automata *a);
void		operators_init(t_handler *a);
void		tactions_handler_init(t_handler *a);
void		automata_init(t_automata *a, void *data);
/*------------CONFIGURATION--------------*/
void		ft_conf_or(t_handler *s, int i);
void		ft_conf_and(t_handler *s, int i);
void		ft_conf_amper(t_handler *s, int i);
void		ft_conf_append(t_handler *s, int i);
void		ft_conf_heredoc(t_handler *s, int i);
void		ft_conf_pipe(t_handler *s, int i);
void		ft_conf_greater(t_handler *s, int i);
void		ft_conf_less(t_handler *s, int i);
void		ft_conf_cmd(t_handler *s, int i);
/*------------UTILS--------------*/
t_cmd		*add_cmd(t_cmd *cmds, t_cmd cmd);
t_cmd		*delete_cmd(t_cmd *cmds, int i);
t_exec		*add_exec(t_exec *execs, t_exec exec);
char		*ft_strdelchr(char *str, char c);
void		*ft_realloc(void *ptr, size_t size);
int			dispatch_command(t_exec *e);
int			*ft_signals(t_exec *e);
char		*ft_getenv(t_cmd *cmd, char *str);
int			ft_isbuiltin(char **builtins, char *token);
void		get_token(t_automata *a, void *data);
void		ft_bzero(void *str, size_t n);
void		ft_free_p2(char **p2);
char		*get_path(char *command, char **env);
char		**do_exec(char *line, char **env);
char		*find_str(char *str, char **env);
int			ft_chrpos(char *str, int chr, int start);
int			idx(char *alphabet[], char c);
int			idstr(char *alphabet[], char *str);
char		**duparr(char **argenv);
void		ft_sarrfree(char ***arr);
char		**ft_sarradd(char **arr, char *string);
int			ft_sarrprint(char **arr);
int			ft_sarrsize(char **arr);
char		**sarr_clean_quote(char **arr);
/*-----------EXCEPTIONS-------------------*/
void		ft_exeption_fd(int inp, int out, int fd[2]);

#endif