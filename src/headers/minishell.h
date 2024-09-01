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
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include "../../lib/libft/libft.h"
#define READ 0
#define WRITE 1
typedef struct s_data
{
    char **tokens;
    int is_op;
    int len_tokens;
} t_data;

typedef struct s_file
{
    int input;
    int output;
    int fd_aux[2];
    char *end_heredoc;
} t_file;

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
    OPEN_BRACE,   // 17 Open brace ({)
    CLOSE_BRACE   // 18 Close brace (})
} t_states;
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
    char **cmd;    // El el desgloce del comando
    int fd_aux[2]; // fd auxiliar para redireccionar
    pid_t pid;     // El pid del proceso
    int status;    // El estado de ejecucion del comando
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
    int *state;
    int op;
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
    t_data *info;     //
    int state[3];
    int fd[2];                                              // este es el fd padre que se va a usar para cada el hijo
    int code;                                               // Aqui debe tener el codigo de error
    char **env;                                             // Esto debe ser el entorno
    char *line;                                             // Esto debe ser la linea de comando
    struct s_exec *exec;                                    // Esto debe llenarse con la estructura de ejecucion
    struct s_handler *(*seg)(struct s_handler *rule);       // Debe ser funciones especificas, Parser, Handler-error, Executer, etc..
    void (*fta[20][20][20])(struct s_handler *rule, int i); // Debe ser funciones especificas, Parser, Handler-error, Executer, etc..
} t_handler;

int *ft_pipe(t_exec *e);
int *ft_builtins(t_exec *e);
int *ft_signals(t_exec *e);
int *ft_exec_pipe(t_exec *e);
int *ft_exec_wildcard(t_exec *e);
int *ft_exec_or(t_exec *e);
int *ft_exec_and(t_exec *e);
int *ft_exec_heredoc(t_exec *e);

t_handler *ft_parser(t_handler *s);
t_handler *ft_execute(t_handler *s);
t_handler *ft_error(t_handler *s);
void ft_conf_or(t_handler *s, int i);
void ft_conf_and(t_handler *s, int i);
void ft_conf_amper(t_handler *s, int i);
void ft_conf_append(t_handler *s, int i);
void ft_conf_heredoc(t_handler *s, int i);
void ft_conf_pipe(t_handler *s, int i);
void ft_conf_greater(t_handler *s, int i);
void ft_conf_less(t_handler *s, int i);

void alphabet_init(t_automata *a);
void errors_init(t_automata *a);
int get_state(int i, int j);

/* Single Actions */
void sactions_init(t_automata *a);
void get_token(t_automata *a, void *data);
// void	count_player(t_automata *a, void *data);

/* Transition Actions */
void tactions_init(t_automata *a);
void operators_init(t_handler *a);
void tactions_handler_init(t_handler *a);
int ft_strlen(const char *str);
char *ft_strdup(const char *str);
char *ft_substr(const char *str, unsigned int start, size_t len);
void ft_bzero(void *str, size_t n);
int ft_chrpos(char *str, int chr, int start);
int idx(char *alphabet[], char c);
int evaluate(t_automata *a);
void automata_init(t_automata *a, void *data);
int ft_sarrprint(char **arr);
char **ft_sarradd(char **arr, char *string);
void ft_sarrfree(char ***arr);
int ft_sarrsize(char **arr);
// char **ft_split(char *s, char c);

void ft_free_p2(char **p2);

#endif