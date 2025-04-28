#include "minishell.h"

int main(int ac, char **av, char **envp)
{
    char    *line;
    t_token *tokens;
    t_cmd   *cmds;
    int     status;

    (void)ac;
    (void)av;
    g_env = copy_env(envp);
    if (!g_env)
        return (1);
    status = 0;
    while (1)
    {
        printf("minishell> ");
        line = get_next_line(0);
        if (!line)
        {
            printf("\n");
            break;
        }
        if (*line)
        {
            tokens = tokenizer(line);
            if (parsing(&tokens))
            {
                cmds = cmd(tokens);
                status = exec_commands(cmds, g_env);
                cmd_clear(&cmds);
            }
            token_clear(&tokens);
        }
        free(line);
    }
    free_env(g_env);
    return (status);
}

