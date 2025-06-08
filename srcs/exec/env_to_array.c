#include "minishell.h"

char	**env_to_array(t_env *env)
{
	char	**arr;
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp && ++i)
		tmp = tmp->next;
	arr = malloc((i + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		arr[i] = ft_strjoin3(tmp->name, "=", tmp->val);
		if (!arr[i])
		{
			free_array(arr);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}