

#include "minishell.h"

int	find_spliter(char s, char *sp)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (sp[i])
	{
		if (s == sp[i])
			return (1);
		i++;
	}
	return (0);
}

int	my_token(char *s)
{
	int	token;

	token = 0;
	if (!ft_strcmp(s, "|"))
		token = 5;
	else if (!ft_strcmp(s, ">"))
		token = 2;
	else if (!ft_strcmp(s, "<"))
		token = 3;
	else if (!ft_strcmp(s, "<<"))
		token = 4;
	else if (!ft_strcmp(s, ">>"))
		token = 9;
	else if (!ft_strcmp(s, "||"))
		token = 6;
	return (token);
}

t_nor_sp	*norm_sp()
{
	t_nor_sp	*norm;

	norm = malloc(sizeof(t_nor_sp));
	norm->check = 0;
	norm->check_q = 0;
	norm->quotes = 0;
	norm->node = NULL;
	norm->st = NULL;
	norm->j = 0;
	norm->i = 0;
	norm->e = 0;
	norm->token = 0;
	norm->k = 0;
	return (norm);
}

int	count_nosplit(t_nor_sp **norm, char *str)
{
	while (str[(*norm)->i] && !find_spliter(str[(*norm)->i], "|<> \t"))
	{
		if (str[(*norm)->i] == 34 || str[(*norm)->i] == 39)
		{
			while (str[(*norm)->i] == 34 || str[(*norm)->i] == 39)
			{
				(*norm)->quotes = str[(*norm)->i];
				(*norm)->i++;
				while (str[(*norm)->i] && (str[(*norm)->i] != (*norm)->quotes))
					(*norm)->i++;
			}
		}
		else
			(*norm)->i++;
	}
	return ((*norm)->i);
}

char	*fill_quotes(t_nor_sp **norm, char *str)
{
	while (str[(*norm)->i] == 34 || str[(*norm)->i] == 39)
	{
		(*norm)->node[(*norm)->j] = str[(*norm)->i];
		(*norm)->quotes = str[(*norm)->i];
		(*norm)->i++;
		(*norm)->j++;
		while (str[(*norm)->i] && (str[(*norm)->i] != (*norm)->quotes))
		{
			(*norm)->node[(*norm)->j] = str[(*norm)->i];
			(*norm)->j++;
			(*norm)->i++;
		}
		(*norm)->node[(*norm)->j] = str[(*norm)->i];
		(*norm)->j++;
		(*norm)->i++;
		(*norm)->node[(*norm)->j] = 0;
	}
	return ((*norm)->node);
}

char	*fill_node(t_nor_sp **norm, char *str)
{
	while (str[(*norm)->i] && !find_spliter(str[(*norm)->i], "|<> \t"))
	{
		if (str[(*norm)->i] == 34 || str[(*norm)->i] == 39)
			(*norm)->node = fill_quotes(norm, str);
		else
		{
			{
				(*norm)->node[(*norm)->j] = str[(*norm)->i];
				(*norm)->j++;
				(*norm)->i++;
			}
			(*norm)->node[(*norm)->j] = 0;
		}
	}
	return ((*norm)->node);
}

int	count_spl(t_nor_sp **norm, char *str)
{
	while (str[(*norm)->i] && find_spliter(str[(*norm)->i], "|<> \t"))
	{
		if (find_spliter(str[(*norm)->i], "|<>"))
			(*norm)->j++;
		(*norm)->i++;
	}
	return ((*norm)->j);
}

char	*fill_sp(t_nor_sp **norm, char *str)
{
	while (str[(*norm)->i] && find_spliter(str[(*norm)->i], "|<> \t"))
	{
		if (find_spliter(str[(*norm)->i], "|<>"))
		{
			(*norm)->st[(*norm)->j] = str[(*norm)->i];
			(*norm)->j++;
			(*norm)->i++;
			if (str[(*norm)->i] == str[(*norm)->i - 1])
			{
				(*norm)->st[(*norm)->j] = str[(*norm)->i];
				(*norm)->i++;
				(*norm)->j++;
			}
			break ;
		}
		(*norm)->i++;
	}
	(*norm)->st[(*norm)->j] = 0;
	return ((*norm)->st);
}

void	fill_struct(t_nor_sp **norm, t_list **s, char *str)
{
	(*norm)->node = malloc((*norm)->i - (*norm)->k + 1);
	(*norm)->i = (*norm)->k;
	(*norm)->j = 0;
	(*norm)->node = fill_node(norm, str);
	ft_lstadd_back(s, ft_lstnew(string_no_quotes((*norm)->node), 0));
}

void	fill_struct2(t_nor_sp **norm, t_list **s, char *str)
{
	(*norm)->st = malloc((*norm)->j + 1);
	(*norm)->j = 0;
	(*norm)->i = (*norm)->k;
	(*norm)->st = fill_sp(norm, str);
	(*norm)->token = my_token((*norm)->st);
	ft_lstadd_back(s, ft_lstnew(string_no_quotes((*norm)->st),
				(*norm)->token));
}

t_list	*our_list(t_nor_sp **norm, t_list *s, char *str)
{
	while (str[(*norm)->i])
	{
		(*norm)->k = (*norm)->i;
		(*norm)->i = count_nosplit(norm, str);
		if ((*norm)->i - (*norm)->k != 0)
		{
			fill_struct(norm, &s, str);
			free((*norm)->node);
			(*norm)->node = NULL;
		}
		else
		{
			(*norm)->k = (*norm)->i;
			(*norm)->j = 0;
			(*norm)->j = count_spl(norm, str);
			if ((*norm)->j != 0)
			{
				fill_struct2(norm, &s, str);
				free((*norm)->st);
				(*norm)->st = NULL;
			}
		}
	}
	return (s);
}

t_list	*ft_split_them(char *str)
{
	t_list		*s;
	t_nor_sp	*norm;

	norm = norm_sp();
	s = NULL;
	s = our_list(&norm, s, str);
	return (s);
}
