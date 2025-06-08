#include "minishell.h"
#include "parsing.h"

t_token *lexer(char *input) {
    t_token *tokens = NULL;
    char *token = strtok(input, " \t\n");

    while (token) {
        t_arg type = WORD;
        if (strcmp(token, ">") == 0) type = OUTPUT;
        else if (strcmp(token, ">>") == 0) type = APPEND;
        else if (strcmp(token, "<") == 0) type = INPUT;
        else if (strcmp(token, "|") == 0) type = PIPE;

        token_add_back(&tokens, create_token(strdup(token), type));
        token = strtok(NULL, " \t\n");
    }
    return tokens;
}

