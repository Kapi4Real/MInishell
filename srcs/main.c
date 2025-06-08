/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:00:00 by user              #+#    #+#             */
/*   Updated: 2023/05/01 12:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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



char **parse_input(char *input) {
    char **args = malloc(64 * sizeof(char *));
    char *token = strtok(input, " ");
    int i = 0;

    while (token != NULL) {
        args[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
    return args;
}

int execute_command(char **args) {
    pid_t pid = fork();

    if (pid == 0) {
        execvp(args[0], args);
        perror("minishell");
        exit(1);
    } else if (pid > 0) {
        wait(NULL);
    } else {
        perror("fork");
        return 1;
    }
    return 0;
}

int main() {
    char *input;
    t_token *tokens;
    t_cmd *cmds;

    setup_signals();

    while (1) {
        input = readline("minishell> ");
        if (!input) break;
        if (strlen(input) > 0) {
            add_history(input);
            tokens = lexer(input);
            if (!tokens) {
                free(input);
                continue;
            }
            cmds = parser(tokens);
            token_clear(tokens);
            if (!cmds) {
                free(input);
                continue;
            }
            exec_commands(cmds, g_env);
            cmd_clear(&cmds);
        }
        free(input);
    }
    return 0;
}
