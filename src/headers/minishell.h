#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h> // Para fstat
#include <sys/stat.h>  // Para stat, lstat, fsta
#include <inttypes.h>  // Incluir para uintmax_t e intmax_t
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <signal.h>
#include <limits.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <sys/param.h>
#include "../../lib/libft/libft.h"
#define READ 0
#define WRITE 1

typedef struct s_data
{
    char **tokens;
    int is_op;
    int len_tokens;
    int i;
    int oid;
} t_data;

typedef struct s_file
{
    int input;
    int output;
    int fd_aux[2];
    char *end_heredoc;
    char *dir_file;
} t_file;

typedef enum e_operators
{
    OP_EMPTY,   // 0
    OP_GREATER, // 1
    OP_LESS,    // 2
    OP_HEREDOC, // 3
    OP_APPEND,  // 4
    OP_AMPER,   // 5
    OP_PIPE,    // 6
    OP_OR,      // 7
    OP_AND,     // 8
    OP_INVALID, // 9
} t_operators;

typedef enum e_op_block
{
    BLOCK_EMPTY, // 0
    BLOCK_AND,   // 1
    BLOCK_OR,    // 2
} t_op_block;

typedef enum e_states
{
    EMPTY,        // 0  Empty input
    DQUOTES,      // 1  Open double quotes (")
    SQUOTES,      // 2  Open single quotes (')
    PIPE,         // 3  Pipe (|)
    OR,           // 4  Or (||)
    LESS,         // 5  Less (<)
    HEREDOC,      // 6  Heredoc (<<)
    GREATER,      // 7  Greater (>)
    APPEND,       // 8  Append (>>)
    AMPER,        // 9  Ampersand (&)
    AND,          // 10 And (&&)
    INVALID,      // 11 Invalid input
    SPACES_NW,    // 12 Spaces without words
    SPACES_BTW,   // 13 Spaces between words
    NOT_OPERATOR, // 14 Not operators
    OPEN_PAREN,   // 15 Open parenthesis (()
    CLOSE_PAREN,  // 16 Close parenthesis ())
    UNIQ_COMMAND,
} t_states;

typedef struct s_block
{
    struct s_exec *prev_exec; // lista de ejeciones anteriores
    struct s_exec *next_exec; // Lista de ejecuciones siguientes
    int len_exec_prev;        // Cantidad de ejecuciones
    int len_exec_next;        // Cantidad de ejecuciones
    int len_exec;             // Cantidad de ejecuciones
    int op;                   // Operador
    int priority;             // Prioridad de ejecucion
    int type;                 // Tipo de ejecucion
    int fd[2];                // este es el fd padre que se va a usar para cada el hijo
    t_file file;              // fichero Salida para esta ejecucion
    int status;               // Estado de la ejecucion
    int isnext;               // Si es siguiente
} t_block;

typedef struct s_automata
{
    void *data;                                            //
    char **alphabet;                                       // Alphabet of operators that i'm used for select o divider tokens
    char **errors;                                         //
    char *str;                                             //
    int state;                                             // Current State
    int ostate;                                            // Old/Previous State
    int errorlen;                                          //
    int i;                                                 //
    int j;                                                 //
    void (*fsa[20])(struct s_automata *a, void *data);     //
    void (*fta[20][20])(struct s_automata *a, void *data); //
    int (*get_state)(int state, int abc_idx);              //
} t_automata;

typedef struct s_cmd
{
    char **cmd;                // El el desgloce del comando
    char *line;                // El el desgloce del comando
    int fd_aux[2];             // fd auxiliar para redireccionar
    pid_t pid;                 // El pid del proceso
    int status;                // El estado de ejecucion del comando
    int towait;                // espero o no espero
    struct s_handler *handler; // espero o no espero
                               // struct s_cmd *next; // d
} t_cmd;
/*
Aqui les dare las propiedades para ejecutarse,
si necesita redirijir o si tienen que tener alta prioridad porque estan en parentesis
*/

typedef struct s_exec
{
    // Propiedades para ejecutar
    // cuantos comandos va a ejecutarse y como
    int priority;
    int finish;
    int *state;
    int op;
    struct s_exec *blocks;
    t_file file;                               // fichero Salida para esta ejecucion
    int status;                                // Estado de las ejecuciones
    t_cmd *cmd;                                // Aqui se guardan los comandos a ejecutarse en cada funcion
    struct s_handler *handler;                 // Aqui se guardan los comandos a ejecutarse en cada funcion
    int *(*func[20][20])(struct s_exec *rule); // Son funciones de ejecucion, personalizadas
    // struct s_exec *next;
} t_exec;

/*
hanndler sabe que funcion debe llamar para configurar s_exec, por tanto hay que inicializar las fucniones respectoa  los estados
luego debo programar la matriz de estados.
*/

typedef struct s_handler
{
    char **operators; //
    char **builtins;  //
    t_block *block;   //
    int len_block;    //
    char *line;
    t_cmd *w_cmd;                                           //
    int n_pids;                                             //
    t_data *info;                                           //
    int state[3];                                           //
    int code;                                               // Aqui debe tener el codigo de error
    char **env;                                             // Esto debe ser el entorno
    struct s_handler *(*seg[5])(struct s_handler *rule);    // Debe ser funciones especificas, Parser, Handler-error, Executer, etc..
    void (*fb[10])(struct s_cmd *cmd);                      // Son funciones de ejecucion, personalizadas
    void (*fta[20][20][20])(struct s_handler *rule, int i); // Debe ser funciones especificas, Parser, Handler-error, Executer, etc..
} t_handler;

t_exec *add_exec(t_exec *execs, t_exec exec);
char *ft_getenv(t_cmd *cmd, char *str);
void *ft_realloc(void *ptr, size_t size);
int dispatch_command(t_exec *e);
void ft_exec_echo(t_cmd *cmd);
void ft_exec_echon(t_cmd *cmd);
void ft_exec_cd(t_cmd *cmd);
void ft_exec_pwd(t_cmd *cmd);
void ft_exec_export(t_cmd *cmd);
void ft_exec_unset(t_cmd *cmd);
void ft_exec_env(t_cmd *cmd);
void ft_exec_exit(t_cmd *cmd);
int dispatch_command_built(t_exec *e);
int *ft_pipe(t_exec *e);
int *ft_builtins(t_exec *e);
int *ft_signals(t_exec *e);
int *ft_exec_wildcard(t_exec *e);

int *ft_exec_and(t_exec *e);
int *ft_exec_pipe(t_exec *e);
int *ft_exec_or(t_exec *e);
int *ft_exec_heredoc(t_exec *e);
int *ft_exec_cmd(t_exec *e);
int *ft_exec_greater(t_exec *e);
int *ft_exec_amper(t_exec *e);
int *ft_exec_append(t_exec *e);
int *ft_exec_less(t_exec *e);
void init_handler(t_handler *s);
void tactions_builtins_init(t_handler *a);
void builtings_init(t_handler *a);
t_handler *ft_parser(t_handler *s);
t_handler *ft_execute(t_handler *s);
t_handler *ft_error(t_handler *s);
t_handler *ft_clear(t_handler *s);
t_handler *ft_execute(t_handler *s);
t_handler *ft_config(t_handler *s);

int ft_isbuiltin(char **builtins, char *token);
void ft_conf_or(t_handler *s, int i);
void ft_conf_and(t_handler *s, int i);
void ft_conf_amper(t_handler *s, int i);
void ft_conf_append(t_handler *s, int i);
void ft_conf_heredoc(t_handler *s, int i);
void ft_conf_pipe(t_handler *s, int i);
void ft_conf_greater(t_handler *s, int i);
void ft_conf_less(t_handler *s, int i);
void ft_conf_cmd(t_handler *s, int i);

void alphabet_init(t_automata *a);
void errors_init(t_automata *a);
int get_state(int i, int j);

/* Single Actions */
void sactions_init(t_automata *a);
void get_token(t_automata *a, void *data);
// void	count_player(t_automata *a, void *data);

/*Service Exception*/
void ft_conf_exception(t_handler *s, int i);
void ft_token_exception(t_automata *a, void *data);
void ft_execute_exception(t_cmd *cmd);

/* Transition Actions */
void tactions_init(t_automata *a);
void operators_init(t_handler *a);
void tactions_handler_init(t_handler *a);
void ft_bzero(void *str, size_t n);
int ft_chrpos(char *str, int chr, int start);
int evaluate(t_automata *a);
void automata_init(t_automata *a, void *data);
int ft_sarrprint(char **arr);
char **ft_sarradd(char **arr, char *string);
void ft_sarrfree(char ***arr);
int ft_sarrsize(char **arr);
// char **ft_split(char *s, char c);
t_cmd *delete_cmd(t_cmd *cmds, int i);
void ft_free_p2(char **p2);
int idx(char *alphabet[], char c);
int idstr(char *alphabet[], char *str);
char *get_path(char *command, char **env);
char **do_exec(char *line, char **env);
char *find_str(char *str, char **env);
#endif