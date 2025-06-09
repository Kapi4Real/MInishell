#include "parsing.h"
#include "minishell.h"
#include "libft.h"

t_cmd	*parser(t_token *tokens, t_env *env)
{
	t_cmd	*cmd_list;
	t_token	*current;
	t_cmd	*new_cmd;

	cmd_list = NULL;
	current = tokens;
	while (current)
	{
		new_cmd = create_cmd(&current, env);
		if (!new_cmd)
		{
			cmd_clear(&cmd_list);
			return (NULL);
		}
		cmd_add_back(&cmd_list, new_cmd);
		if (current && current->type == PIPE)
			current = current->next;
	}
	return (cmd_list);
}
