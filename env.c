#include "minishell.h"

int	is_allpha1(char s)
{
	if ((s >= 65 && s <= 90) || (s >= 97 && s <= 122))
		return (1);
	return (0);
}

int	is_digit1(char s)
{
	if ((s >= 48 && s <= 57))
		return (1);
	return (0);
}

int	find_spliter1(char s, char *sp)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (sp[i])
	{
		if (s == sp[i] || (!is_digit1(s) && !is_allpha1(s)))
			return (1);
		i++;
	}
	return (0);
}

char *get_it_witout_$(char *str)
{
	char	*var;
	int		i;
	int		j;

	i = 1;
	j = 0;
	var = malloc(ft_strlen(str));
	while (str[i])
	{
		var[j] = str[i];
		i++;
		j++;
	}
	var[j] = 0;
	return (var);
}

char	*finnd_valeur(t_mini *env, char *str)
{
	t_mini	*tmp_env;

	tmp_env = env;
	if (str[0] == '?')
	{
		//printf("------------|||||%s\n",str);
		return (ft_itoa(my_global->status));
	}
	else
	{
		while (tmp_env)
		{
			if (!ft_strcmp(tmp_env->data_var, str))
				return (tmp_env->data_val);
			tmp_env = tmp_env->next;
		}
	}
	return (NULL);
}

char	*ft_expand(char *str, t_mini *expand, int start)
{
	char	*after;
	char	*before;
	char	*var;
	char	*valeur;
	char	*full_string;
	int		i;
	int		j;

	i = 0;
	j = 0;
	after = NULL;
	before = NULL;
	var = NULL;
	valeur = NULL;
	full_string = NULL;
	before = malloc(start);
	while (i < start - 1)
	{
		before[i] = str[i];
		i++;
	}
	before[i] = '\0';
	i = 0;
	if (str[start + i] == '?')
	{
		var = malloc(2);
		var[0] = '?';
		var[1] = '\0';
		i++;
		//printf("vaaaaaaaaaaar     %s\n", var);
	}
	else
	{
		while (!find_spliter1(str[start + i], "|>< \t\n\'\""))
			i++;
		var = malloc(i + 1);
		i = 0;
		while (!find_spliter1(str[start + i], "|>< \t\n\'\""))
		{
			var[i] = str[start + i];
			i++;
		}
		var[i] = '\0';
	}
	// printf("->>>>%s\n",var);
	valeur = finnd_valeur(expand, var);
	//printf("the valeur is :  %s\n",valeur);
	j = 0;
	//printf("here    %c\n",str[start+i+j]);
	while (str[start + i + j])
		j++;
	after = malloc(j + 1);
	j = 0;
	while (str[start + i])
	{
		after[j] = str[start + i];
		i++;
		j++;
	}
	after[j] = '\0';
	//printf("after_is   %s\n",after);
	full_string = ft_strjoin(before, valeur);
	if (after[0] == 0)
		return (full_string);
	else
		full_string = ft_strjoin(full_string, after);
	//printf("full_string_is:->>>%s\n",full_string);
	return (full_string);
}

int	ft_check_cote(char *str, int i)
{
	int	j;
	int	z;

	j = 0;
	z = 0;
	while (str[j] && j < i)
	{
		if (str[j] == '\"')
			z++;
		j++;
	}
	if (z % 2 == 0)
		return (0);
	else
		return (1);
}

int	dollar(char *str, int i)
{
	int	j;

	j = 0;
	while (i > 0)
	{
		i--;
		j++;
		if (str[i] && str[i + 1] && str[i] != 39 && str[i] != 34 && str[i
			+ 1] == '$')
			// if (str[i] &&str[i] == '$')
			return (j + 1);
	}
	return (0);
}

char	*exp_hoho(char *str, t_mini *expand)
{
	int	i;
	int	z;

	i = 0;
	z = 0;
	while (str[i])
	{
		if (str[i] == '\'' && str[i + 1] && ft_check_cote(str, i) == 0)
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (str[i])
				i++;
			continue ;
		}
		else if (str[i] == '$' && str[i + 1])
		{
			i++;
			//printf("sssssss    %s\n",str+i);
			str = ft_expand(str, expand, i);
            //printf("str_is:     %s--------%c\n",str,str[i]);
			z = dollar(str, i);
			//printf("z------->%i\n",z);
			while (z >= 0)
			{
                if (str[i]=='\0')
					break ;
				else
					i--;
				z--;
				
                    //printf("hhh\n");
			}
			//printf("zbental-------->%c\n",str[i]);
		}
		else if (!str[i])
			break ;
		//printf("stttttttr    %s",str);
		else if (str[i] != '$')
		{
			i++;
		}
		else if (!str[i + 1])
			i++;
        //break;
	}
	str[i] = '\0';
	return (str);
}


