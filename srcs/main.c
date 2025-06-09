#include "parsing.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <string.h>

char **g_env = NULL;
int g_exit_status = 0;

static void init_env(t_env **env, char **envp)
{
    char *eq;
    
    while (*envp)
    {
        eq = strchr(*envp, '=');
        if (eq)
        {
            *eq = '\0';
            env_add_back(env, env_new(*envp, eq + 1));
            *eq = '=';
        }
        envp++;
    }
}

int main(int ac, char **av, char **envp) 
{
    (void)ac;
    (void)av;
    char *input;
    t_token *tokens;
    t_cmd *cmds;
    t_env *env = NULL;

    init_env(&env, envp);
    g_env = envp;  
    setup_signals();

    while (1) {
        input = readline("minishell> ");
        if (!input) break;
        if (strlen(input) > 0) {
            add_history(input);
            if (!check_quotes(input)) {
                ft_putstr_fd("minishell: syntax error: unclosed quotes\n", 2);
                free(input);
                g_exit_status = 1;
                continue;
            }
            tokens = tokenizer(input);
            if (!tokens) {
                free(input);
                continue;
            }
            if (!parsing(&tokens)) {
                ft_putstr_fd("minishell: syntax error\n", 2);
                token_clear(tokens);
                free(input);
                g_exit_status = 2;
                continue;
            }
	    cmds = cmd(tokens, env);
            token_clear(tokens);
            if (!cmds) {
                free(input);
                continue;
            }
            exec_commands(cmds, envp); // On utilise envp au lieu de env
            cmd_clear(&cmds);
        }
        free(input);
    }
    env_clear(env);
    return (g_exit_status);
}
