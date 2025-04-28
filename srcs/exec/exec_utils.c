int handle_redirections(t_cmd *cmd)
{
}

int is_builtin(char *cmd)
{
    if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "pwd") == 0) {
        return 1;
    }
    return 0;
}

int run_builtin(t_cmd *cmd)
{
    if (ft_strcmp(cmd->arguments[0], "echo") == 0) {
        echo(cmd->arguments);
    }

    return 0;
}

char *find_exec(char *cmd, char **envp)
{
}

