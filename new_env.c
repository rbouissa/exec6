

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

char	*finnd_valeur(t_mini *env, char *str)
{
	t_mini	*tmp_env;

	tmp_env = env;
	if (str[0] == '?')
		return (ft_itoa(my_global->status));
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

char	*new_expand(char *str, t_mini *env)
{
	char	*new_str;
	char	*var;
	char	*valeur;
	char	*dollar;
	int		quotes;
	int		i;
	int		k;
	int		j;
	int		e;
	int		h;

	i = 0;
	j = 0;
	k = 0;
	quotes = 0;
	e = 0;
	h = 0;
	new_str = NULL;
	dollar = NULL;
	var = NULL;
	valeur = NULL;
	dollar = malloc(2);
	dollar[0] = '$';
	dollar[1] = '\0';
	while (str[i])
	{
		e = 0;
		h=0;
		if (str[i] == '\'' && quotes == no_quotes)
			quotes = isingle_quotes;
		else if (str[i] == '\"' && quotes == no_quotes)
			quotes = idouble_quotes;
		else if (str[i] == '\"' && quotes == idouble_quotes)
			quotes = no_quotes;
		else if (str[i] == '\'' && quotes == isingle_quotes)
			quotes = no_quotes;
		if (str[i] == '$' && quotes != isingle_quotes)
		{
			while (str[i] == '$')
			{
				i++;
				e++;
			}
			if (str[i] == '?')
			{
				var = malloc(2);
				var[0] = '?';
				var[1] = '\0';
				i++;
				h++;
			}
			else
			{
				k = i;
				while (!find_spliter1(str[k], "|>< \t\n\'\""))
				{
					k++;
					j++;
				}
				var = malloc(j + 1);
				k = i;
				j = 0;
				while (!find_spliter1(str[k], "|>< \t\n\'\""))
				{
					var[j] = str[k];
					k++;
					j++;
				}
				var[j] = '\0';
				k = 0;
			}
			printf("%d\n",h);
			if ((e % 2 != 0 && e > 2) || (e == 1 && !str[i] && h != 1))
				new_str = ft_strjoin(new_str, dollar);
			valeur = finnd_valeur(env, var);
			new_str = ft_strjoin(new_str, valeur);
			while (!find_spliter1(str[i], "|>< \t\n\'\""))
				i++;
			
		}
		else
		{
			new_str = ft_strjoin(new_str, (char[]){str[i], 0});
			i++;
		}
	}
	free(var);
	free(dollar);
	if (quotes == idouble_quotes || quotes == isingle_quotes)
	{
		ft_write("syntax error exepected quote");
		return (NULL);
	}
	else
		return (new_str);
}

// char	*handle_quotes(char *str, t_mini *env)
// {
// 	int quotes;
// 	char *buffer;
// 	int i;
// 	int k;

// 	quotes = no_quotes;
// 	buffer = NULL;
// 	(void)env;
// 	k = 0;
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\'' && quotes == no_quotes)
//         {
// 			quotes = isingle_quotes;
//         }
// 		else if (str[i] == '\"' && quotes == no_quotes)
// 		{
// 			quotes = idouble_quotes;
// 		}
// 		else if (str[i] == '\"' && quotes == idouble_quotes)
// 		{

// 			quotes = no_quotes;
// 		}
// 		else if (str[i] == '\'' && quotes == isingle_quotes)
// 		{

// 			quotes = no_quotes;
// 		}
// 		if (str[i] == '$' && quotes != isingle_quotes)
// 		{
// 			buffer = new_expand(str, env);
// 			k++;
// 		}
// 		i++;
// 	}
// 	if (quotes == idouble_quotes || quotes == isingle_quotes)
// 	{
// 		ft_write("syntax error exepected quote");
// 		exit(0);
// 		return (NULL);
// 	}
// 	else if (k)
// 	{
// 		return (buffer);
// 	}
// 	else
// 	{
// 		return (str);
// 	}
// }