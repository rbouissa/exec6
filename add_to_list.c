#include "minishell.h"


int	check_string(char *str)
{
	int	i;
	int	k;

	i = 0;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
		{
			k = str[i];
			i++;
			while (str[i] != k && str[i])
				i++;
			if (str[i] != k)
			{
				ft_write("syntax error exepected quote");
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	check_eroor(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{  
		if ((str[0] == ' ' || str[0] == '\t'))
		{
			while ((str[i] == ' ' || str[i] == '\t') && str[i])
				i++;
			if ((str[i] == '|' || str[i] == '>' || str[i] == '<') )
			{
				ft_write("syntax error near unexpected token `|'");
				return (0);
			}
			else if(str[i])
                i++;
		}
        else if (str[0] == '|' )
		{
			ft_write("syntax error near unexpected token `|'");
			return (0);
		}
		else if (str[i] == '|' && (!str[i + 1] || (str[i + 1] == '\t' || str[i
						+ 1] == ' ' || str[i+1] == '|')))
		{
			if (str[i + 1] == ' ' || str[i + 1] == '\t' || str[i + 1] == '|')
			{
				i++;
				while (str[i] && (str[i] == '\t' || str[i] == ' ')) 
					i++;
				if (!str[i] || str[i] == '|')
				{
					ft_write("syntax error near unexpected token `|'");
					return (0);
				}
			}
			else if (!str[i + 1])
			{
				ft_write("syntax error near unexpected token `|'");
				return (0);
			}
		}
		else if ((str[i] == '>' || str[i] == '<') && !str[i + 1])
		{
			ft_write("syntax error near unexpected token `newline'");
			return (0);
		}
		else
			i++;
	}
	return (1);
}

t_list	*split_fuul_cmd(char **s)
{
	t_list *tmp;
	int token;
	int i;
	i = 1;

	if (!ft_strcmp(s[0], "|"))
		token = 1;
	else if (!ft_strcmp(s[0], ">"))
		token = 2;
	else if (!ft_strcmp(s[0], "<"))
		token = 3;
	else
		token = 0;
	tmp = ft_lstnew(s[0], token);
	while (s[i])
	{
		if (!ft_strcmp(s[i], "|"))
			token = 1;
		else if (!ft_strcmp(s[i], ">"))
			token = 2;
		else if (!ft_strcmp(s[i], "<"))
			token = 3;
		else
			token = 0;
		ft_lstadd_back(&tmp, ft_lstnew(s[i], token));
		i++;
	}
	return (tmp);
}
