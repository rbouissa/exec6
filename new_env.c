

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
	char	*s;

	s = ft_itoa(my_global->status);
	tmp_env = env;
	if (str[0] == '?')
	{
		return (s);
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
	return ("\0");
}

t_norm2	*norm_sp1()
{
	t_norm2	*norm;

	norm = malloc(sizeof(t_norm2));
	norm->i = 0;
	norm->j = 0;
	norm->k = 0;
	norm->quotes = 0;
	norm->e = 0;
	norm->h = 0;
	norm->new_str = NULL;
	norm->dollar = NULL;
	norm->var = NULL;
	norm->valeur = NULL;
	return (norm);
}
void	for_dollar(t_norm2 **norm, char *str)
{
	while (str[(*norm)->i] == '$')
	{
		(*norm)->i++;
		(*norm)->e++;
	}
}
void	alloc_built(t_norm2 **norm, char *str)
{
	(void)str;
	(*norm)->var = malloc(2);
	(*norm)->var[0] = '?';
	(*norm)->var[1] = '\0';
	(*norm)->i++;
	(*norm)->h++;
}
void	alloc_simple(t_norm2 **norm, char *str)
{
	(*norm)->k = (*norm)->i;
	while (!find_spliter1(str[(*norm)->k], "|>< \t\n\'\""))
	{
		(*norm)->k++;
		(*norm)->j++;
	}
	(*norm)->var = malloc((*norm)->j + 1);
	(*norm)->k = (*norm)->i;
	(*norm)->j = 0;
	while (!find_spliter1(str[(*norm)->k], "|>< \t\n\'\""))
	{
		(*norm)->var[(*norm)->j] = str[(*norm)->k];
		(*norm)->k++;
		(*norm)->j++;
	}
	(*norm)->var[(*norm)->j] = '\0';
	(*norm)->k = 0;
}
void	join_character(t_norm2 **norm, char *str, t_mini **env)
{
	(void)str;
	(*norm)->valeur = finnd_valeur((*env), (*norm)->var);
	(*norm)->new_str = ft_strjoin((*norm)->new_str, (*norm)->valeur);
	while (!find_spliter1(str[(*norm)->i], "|>< \t\n\'\""))
		(*norm)->i++;
}
void	lite_expand(t_norm2 **norm, char *str, t_mini **env)
{
	for_dollar(norm, str);
	if (str[(*norm)->i] == '?')
		alloc_built(norm, str);
	else
		alloc_simple(norm, str);
	if (((*norm)->e % 2 != 0 && (*norm)->e > 2) || ((*norm)->e == 1
			&& !str[(*norm)->i] && (*norm)->h != 1))
		(*norm)->new_str = ft_strjoin((*norm)->new_str, (*norm)->dollar);
	join_character(norm, str, env);
}
void	do_all_work(t_norm2 **norm, char *str, t_mini **env)
{
	while (str[(*norm)->i])
	{
		(*norm)->e = 0;
		(*norm)->h = 0;
		if (str[(*norm)->i] == '\'' && (*norm)->quotes == no_quotes)
			(*norm)->quotes = isingle_quotes;
		else if (str[(*norm)->i] == '\"' && (*norm)->quotes == no_quotes)
			(*norm)->quotes = idouble_quotes;
		else if (str[(*norm)->i] == '\"' && (*norm)->quotes == idouble_quotes)
			(*norm)->quotes = no_quotes;
		else if (str[(*norm)->i] == '\'' && (*norm)->quotes == isingle_quotes)
			(*norm)->quotes = no_quotes;
		if (str[(*norm)->i] == '$' && (*norm)->quotes != isingle_quotes)
            lite_expand(norm,str,env);
		else
		{
			(*norm)->new_str = ft_strjoin((*norm)->new_str,
					(char[]){str[(*norm)->i], 0});
			(*norm)->i++;
		}
	}
}
char	*new_expand(char *str, t_mini *env)
{
	t_norm2	*norm;

	norm = norm_sp1();
	norm->dollar = malloc(2);
	norm->dollar[0] = '$';
	norm->dollar[1] = '\0';
	do_all_work(&norm, str, &env);
	free(norm->var);
	free(norm->dollar);
	if (norm->quotes == idouble_quotes || norm->quotes == isingle_quotes)
	{
		ft_write("syntax error exepected quote");
		return (NULL);
	}
	else
		return (norm->new_str);
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