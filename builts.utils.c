#include "minishell.h"

void echo (char **args)
{
	int		newline;
	int		i;

	newline = 1;
	i = 1;

	if(args[1] && (strcmp(args[1], "-n") == 0))
	{
		newline = 0;
		i++;
	}

	while(args[i])
	{
		printf("%s", args[i]);
		if(args[i + 1])
			printf(" ");
		i++;
	}

	if (newline)
		printf("\n");
}

void ft_pwd(void)
{
	char *cwd[PATH_MAX];

	if(getcwd(cwd, sizeof(cwd) != NULL))
		printf("%s",cwd);
	else
		perror("minishell : pwd")
}

void ft_env (char **envp)
{
	int	i;

	i = 0;
	while(envp[i])
	{
		printf("%s",envp[i]);
		i++;
	}
}

