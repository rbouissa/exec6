
#include "minishell.h"

void	ft_free_cmd(t_list *list)
{
	t_list	*node;

	node = NULL;
	if (!list)
		return ;
	while (list)
	{
		node = list;
		list = list->next;
		free(node->data);
		free(node);
	}
	free(list);
}
void	ft_free_cmd2(t_cmd *list)
{
	t_cmd	*node;
	int		i;

	i = 0;
	node = NULL;
	if (!list)
		return ;
	while (list)
	{
        i = 0;
		node = list;
		list = list->next;
		while (node->cmd[i])
		{
			free(node->cmd[i]);
			i++;
		}
        free(node->cmd[i]);
        free(node->cmd);
        i=0;
        while(node->herdoc[i])
        {
            free(node->herdoc[i]);
            i++;
        }
        free(node->herdoc[i]);
        free(node->herdoc);
		free(node);
	}
	free(list);
}
