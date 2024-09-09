#include "../../headers/minishell.h"

char *local_path(int i)
{
	char *s;
	char *res;

	s = malloc(sizeof(char) * (MAXPATHLEN + 1));
	if (!s)
		(printf("Error malloc"), exit(22));
	if (!getcwd(s, MAXPATHLEN))
		(printf("Error malloc"), exit(22));
	while (s[i])
		i++;
	res = malloc(sizeof(char) * i + 1);
	if (!res)
		(printf("Error malloc"), exit(23));
	i = -1;
	while (s[++i])
		res[i] = s[i];
	free(s);
	res[i] = '\0';
	return (res);
}

char *ft_getenv(t_cmd *cmd, char *str)
{
	int i;

	i = -1;
	while (cmd->handler->env[++i])
	{
		if (!ft_strncmp(cmd->handler->env[i], str, ft_strlen(str)))
			return (cmd->handler->env[i] + ft_strlen(str) + 1);
	}
	return NULL;
}
void change_value_pwd(char *s, t_cmd *cmd, int control)
{
	int i;
	char *temp;

	i = -1;
	s = local_path(0);
	while (cmd->handler->env[++i])
	{
		if (control == 0 && cmd->handler->env[i] && !ft_strncmp(cmd->handler->env[i], "OLDPWD", 6))
		{
			temp = ft_strjoin("OLDPWD=", s);
			free(cmd->handler->env[i]);
			cmd->handler->env[i] = temp;
		}
		if (control == 1 && cmd->handler->env[i] && !ft_strncmp(cmd->handler->env[i], "PWD", 3))
		{
			// printf("PWD:%s\n", cmd->handler->env[i]);
			temp = ft_strjoin("PWD=", s);
			free(cmd->handler->env[i]);
			cmd->handler->env[i] = temp;
		}
	}
	free(s);
}
void ft_exec_cd(t_cmd *cmd)
{
	char *temp;

	char *line;
	char **str;
	size_t len;

	cmd->status = 0;
	line = ft_strnstr(cmd->line, "cd", ft_strlen(cmd->line));
	if (line)
	{
		len = ft_strlen("cd"); // Longitud de la subcadena
		memmove(line, line + len, strlen(line + len) + 1);
	}
	line = ft_strtrim(line, " ");
	str = ft_split(line, ' ');
	if (ft_sarrsize(str) > 1)
	{
		ft_putstr_fd(" too many arguments\n", 2);
		cmd->status = 1;
		return;
	}
	change_value_pwd(NULL, cmd, 0);
	if (str[0] == 0)
	{
		// chdir(ft_getenv(cmd,"HOME"));
		chdir(getenv("HOME"));
		return;
	}
	temp = str[0];
	if (ft_isdigit(temp[0])) // verificar tambien si es un directorio accesible
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		cmd->status = 1;
		return;
	}
	if (temp[0] == '~')
	{
		temp = ft_strjoin(getenv("HOME"), temp + 1);
	}
	else if (!ft_strncmp(temp, "-", 2))
	{
		chdir(getenv("OLDPWD"));
		// chdir(ft_getenv(cmd,"OLDPWD"));
	}
	else if (ft_strchr(temp, '$'))
	{
		temp = ft_getenv(cmd, temp + 1);
		if (temp)
		{
			if (chdir(temp) == -1)
			{
				printf("No such file or directory");
				cmd->status = 1;
			}
			else
			{
				change_value_pwd(NULL, cmd, 1);
				return;
			}
		}
	}
	else if (chdir(temp) == -1)
		printf("No such file or directory");
	else
	{
		change_value_pwd(NULL, cmd, 1);
		free(temp);
		return;
	}
	free(temp);
	cmd->status = 0;
}