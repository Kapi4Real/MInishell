#include "minishell.h"

/*
t_env *env_new(char *name, char *val)
{
    t_env *new = malloc(sizeof(t_env));
    if (!new)
        return NULL;
    new->name = ft_strdup(name);
    new->val = ft_strdup(val);
    new->next = NULL;
    return new;
}*/

/*
void env_add_back(t_env **env, t_env *new)
{
    t_env *tmp;

    if (!env || !new)
        return;
    if (!*env)
    {
        *env = new;
        return;
    }
    tmp = *env;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}*/

/*
void env_clear(t_env **env)
{
    t_env *tmp;

    if (!env || !*env)
        return;
    while (*env)
    {
        tmp = (*env)->next;
        free((*env)->name);
        free((*env)->val);
        free(*env);
        *env = tmp;
    }
}*/
