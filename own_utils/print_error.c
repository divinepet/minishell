#include "../liba.h"

void	print_error_end(int print_code)
{
	if (print_code == 1)
		write(2, "command not found\n", 18);
	else if (print_code == 2)
		write(2, "No such file or directory\n", 26);
	else if (print_code == 3)
		write(2, "is a directory\n", 15);
	else if (print_code == 4)
		write(2, "Premission denied\n", 18);
	else if (print_code == 5)
		write(2, "not a valid identifier\n", 23);
	else if (print_code == 6)
		write(2, "syntax error near unexpected token `newline'\n", 45);
	else if (print_code == 7)
		write(2, "too many arguments\n", 19);
	else if (print_code == 8)
		write(2, "syntax error near unexpected token `;'\n", 39);
	else if (print_code == 9)
		write(2, "syntax error near unexpected token `|'\n", 39);
	else if (print_code == 10)
		write(2, "HOME not set\n", 13);
}

int	print_error_r(char *fail_file, int error_code)
{
	SHOW_PROMPT();
	write(2, fail_file, ft_strlen(fail_file));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	g_global_error = error_code;
	return (1);
}

/*
* print_code - код выводимой ошибки
* error_code - код присваиваемой ошибки
* value - дополнительный аргумент для вывода
* builtin - строка после "bash: " выводимая только в билт-инах
*/
int	print_error(int print_code, int error_code, char *value, char *builtin)
{
	g_global_error = error_code;
	SHOW_PROMPT();
	if (*builtin != '\0')
	{
		write(2, builtin, ft_strlen(builtin));
		write(2, ": ", 2);
	}
	if (*value != '\0')
	{
		if (print_code == 5)
			write(2, "`", 1);
		write(2, value, ft_strlen(value));
		if (print_code == 5)
			write(2, "'", 1);
		write(2, ": ", 2);
	}
	print_error_end(print_code);
	return (1);
}

/*
* Для команды $?
*/
void	show_error(void)
{
	SHOW_PROMPT();
	ft_putnbr_fd(g_global_error, 2);
	write(2, ": ", 2);
	write(2, "command not found\n", 18);
	g_global_error = 127;
}
