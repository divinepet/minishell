#ifndef LIBA_H
# define LIBA_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <ctype.h>
# include <term.h>
# include <termcap.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <sys/errno.h>
# include <sys/wait.h>

# define BUFFER_SIZE 1
# define MAGENTA "\x1b[35m"
# define RESET   "\x1b[0m"
# define RED     "\x1b[31m"
# define PINK    "\x1b[34m"

int					g_global_error;

typedef struct s_env {
	char				*key;
	char				*value;
	int					hidden;
	int					toSort;
	struct s_env		*next;
}	t_env;

typedef struct s_parse_data {
	int					isError;
	char				quotes;
	int					redirect_type;
	int					pipe_flag;
	int					status;
	char				*old_pwd;
	char				**envp_array;
	char				**args_for_cmd;
	int					i;
	int					b;
	int					j;
}	t_parse_data;

typedef struct s_redirect {
	int					i;
	int					j;
	int					fd;
	int					fd_copy;
	char				redirect;
	char				*args;
	char				*files;
	char				*spec_file;
	char				*command;
}	t_redirect;

typedef struct s_history {
	char				*str;
	struct s_history	*next;
	struct s_history	*prev;
}	t_history;

typedef struct s_hst_data {
	char				*str;
	struct termios		term;
	struct termios		old_term;
	int					count_delete;
	int					flag_end;
	int					count_hst;
	int					flag_next;
	int					flag_hst;	
	t_history			*hst;
}	t_hst_data;

int						main(int ac, char **av, char **envp);

	/* LIBFT */
void					*ft_memset(void *dst, int c, size_t n);
int						ft_isalnum(int ch);
int						ft_strcmp(char *s1, char *s2);
char					*ft_strjoin(char const *s1, char const *s2);
char					**ft_split(char const *s, char c);
char					**ft_split_modified(char const *s, char c);
char					*ft_strtrim(char const *s1, char const *set);
char					*ft_strchr(const char *str, int ch);
char					*ft_substr(char const *s, char end);
char					*ft_strdup(const char *s1);
char					*ft_strcpy(char *dest, char *src);
int						ft_putchar(int c);
void					ft_putnbr_fd(int n, int fd);
char					*ft_itoa(int n);
int						cmpp(char *s1, char *s2);
int						ft_atoi(const char *str);
size_t					ft_strlen(const	char *str);
void					*ft_calloc(size_t num, size_t size);

	/* OWN UTILS */
void					free_double_array(char **array);
void					free_redirect_struct(t_redirect **re);
void					free_struct(t_env **env);
void					free_data_struct(t_parse_data **data);
void					free_redirect_args(char **s);
void					free_and_errors(t_parse_data *data, char **cmd, \
							int flag, char **buf);
void					redirect_struct_init(t_redirect **re);
void					parse_data_struct_init(t_parse_data **data);
void					envpToStruct(t_env **env, char **ev);
char					**envp_to_double_array(t_env *env);
int						print_error(int print_code, int error_code,
							char *value, char *builtin);
int						print_error_r(char *fail_file, int error_code);
int						isForbiddenEnviroment(const char *s);
char					*deleteSpaces(char *str, int i, int j);
char					*command_cutter(char *str);
int						get_next_line(int fd, char **line);
void					SHOW_PROMPT(void);
void					show_error(void);
void					signal_use(void);
void					level_up(t_env **env);
char					**split_in_args(char *str, int i, int k, int quotes);

	/* BUILTIN COMMANDS */
void					my_echo(t_parse_data *data);
void					my_env(t_env *env);
void					my_pwd(t_env *env);
void					my_export(t_env *env, t_parse_data *data);
void					my_cd(t_env *env, t_parse_data *data);
void					my_unset(t_env *env, t_parse_data *data);
void					my_exit(t_parse_data *data);

	/* STRING PARSER */
void					pre_parse(char *s, t_env *env, t_parse_data *data);
void					delete_spaces_and_quotes(char *str,
							t_env *env, t_hst_data *history);

	/* ELEMENT PARSING */
char					*env_parse(t_env *env, char *str);
char					*tilda_parse(t_env *env, char *str);
int						quotes_parse_first(t_parse_data *data,
							char *str, int *i);
int						quotes_parse_second(int *quotes, char *str, int i);
int						semicolon_parse(int *i, char **buffer, char *str);
int						rdr_parse(char **buffer, char *str, int *i, int *b);
int						pipe_ch_parse(char **buffer, char *str, int *i, int *b);

	/* EXECVE */
void					bin_commands(t_env *env, char *command, \
							t_parse_data *data);
void					sh_open(t_env *env, t_parse_data *data);

	/* TERMCAP */
void					delete_symbol(void);
t_history				*create_history(char *str, char **res,
							t_hst_data *hst, t_history *tmp);
t_history				*read_from_term(char *str, t_history *tmp,
							t_hst_data *history, char **res);
void					load_from_file(t_hst_data **hst);
void					turn_signals(t_hst_data *history, int flag);
void					ft_print_and_save(char *str, char **res, int l);
int						allowed_characters(char c);
t_history				*ctrl_c(t_hst_data *history, char **res);
char					*copy_str(char *res, t_hst_data *history, \
												t_history *tmp);
char					*live_string(t_hst_data *history, char *res);
t_history				*down_utils(t_hst_data *history, \
							t_history *tmp, char **res);

	/* STRUCT METHODS */
t_env					*create(char *key, char *value, int hidden);
void					add_env(t_env **list, char *key,
							char *value, int hidden);
void					add_to_env(t_env **env, char *str, int hidden);
char					*get_value_for_key(t_env *lst, char *key);
int						isKeyExist(t_env **env, char *key,
							char *value, int hidden);
void					deleteKey(t_env **env, char *key);
t_env					*sort_export(t_env *env);
t_env					*sort_env(t_env *env);

	/* REDIRECT */
void					redirecting(char *str, t_env *env, t_parse_data *data);
int						get_command(t_redirect *re, char *str, int k);
char					*new_str(char *str, int i, int k);
int						search_errors_in_args(t_redirect *re, \
										t_parse_data *data);
int						search_errors_in_fd(t_redirect *re, t_parse_data *data);

	/* PIPES */
void					pipe_check(char *buf, t_env *env, t_parse_data *data);
char					**str_prepare(char *buf, t_parse_data *data);
int						last_prepare(char **av, char *new_string);
void					middle_child(int **pipes, t_env *env, \
								char **av, t_parse_data *data);
void					last_child(int **pipes, t_env *env, char **av, \
													t_parse_data *data);
void					first_child(int **pipes, t_env *env, char **av, \
													t_parse_data *data);
char					*new_str_for_pipe(char *str, int i, int k);
void					close_other_fd(int **fd, int k, int j);
void					command_parse_modified(char *buffer, t_env *env, \
													t_parse_data *data);
int						try_to_open_modified(char **paths, t_parse_data *data, \
							int i, int flag);
void					pre_parse_modified(char *s, t_env *env, \
							t_parse_data *data);
void					sh_open_modified(t_env *env, t_parse_data *data);

	/* SIGNAL */
void					ft_signal_child_process(void);
void					ft_signal(void);

	/* ? */
void					tgetend(char **buf, char **array);

#endif