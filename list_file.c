
#include"parsing.h"

t_file	*ft_last_file(void *tmp)
{
	t_file	*a;

	a = (t_file *)tmp;
	while (a->next)
		a = a->next;
	return (a);
}

void	ft_lstadd_back_file(t_file **lst, t_file *new)
{
	t_file	*ptr;

	if (lst)
	{
		if (*lst)
		{
			ptr = ft_last_file(*lst);
			ptr->next = new;
		}
		else
			*lst = new;
	}
}
t_file	*ft_lstnew_file(char *content, int in, int out)
{
	t_file	*node;

	node = malloc(sizeof(t_file));
	if (!node)
		return (NULL);
	node->file = content;
	node->infile = in;
    node->outfile = out;
	node->next = NULL;
	return (node);
}
