/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: met-tahe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:53:27 by met-tahe          #+#    #+#             */
/*   Updated: 2023/03/08 11:53:29 by met-tahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_allpha(char s)
{
	if ((s >= 65 && s <= 90) || (s >= 97 && s <= 122) || s == '_')
		return (1);
	return (0);
}
int	is_digit(char s)
{
	if ((s >= 48 && s <= 57))
		return (1);
	return (0);
}
int	is_valid(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (is_allpha(s[i]) == 0 && is_digit(s[i]) == 0 && s[i] != '=')
			return (0);
		i++;
	}
	return (1);
}

int	check_error(char *s)
{
	size_t	i;
	char	**v;

	v = var_split(s, '=');
	i = 0;
	if (is_allpha(s[i]) == 0)
		return (0);
	while (v[0][i])
	{
		if (is_allpha(v[0][i]) || is_digit(v[0][i]) || (v[0][i] == '+'
				&& ft_strchr(s, '=')) || (v[0][i] == '_'))
		{
			if (v[0][i] == '+')
			{
				if (i == ft_strlen(v[0]) - 1)
					i++;
				else
					return (0);
			}
			i++;
		}
		else
			return (0);
	}
	ft_free(v);
	//system("leaks minishell");
	return (1);
}

int	search_exp(char *s)
{
	t_mini	*tmp;

	tmp = my_global->m_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->data_var, s) == 0)
			return (1);
		else
			tmp = tmp->next;
	}
	return (0);
}
void	export_null(char *var)
{
	t_mini	*tmp;

	tmp = my_global->m_env;
	if (var == NULL)
	{
		while (tmp)
		{
			if ((tmp)->data_val)
				printf("declare -x %s=\"%s\"\n", (tmp)->data_var,
						(tmp)->data_val);
			else
				printf("declare -x %s\n", (tmp)->data_var);
			tmp = (tmp)->next;
		}
	}
}
void	export_ecrase(t_mini **tmp1, char **v)
{
	while (*tmp1)
	{
		
		if (ft_strcmp((*tmp1)->data_var, v[0]) == 0)
		{
			(*tmp1)->valid = 0;
			(*tmp1)->data_val = ft_strdup(v[1]);
			break ;
		}
		else
			*tmp1 = (*tmp1)->next;
	}
}
void	export_join(t_mini **tmp1, char **v)
{
	while (*tmp1)
	{
		if (ft_strcmp((*tmp1)->data_var, v[0]) == 0)
		{
			(*tmp1)->valid = 0;
			(*tmp1)->data_val = ft_strjoin((*tmp1)->data_val, v[1]);
			break ;
		}
		else
			*tmp1 = (*tmp1)->next;
	}
}

int	print_export_err(char *var)
{
	if (check_error(var) == 0)
	{
		ft_putstr_fd("minishell: export:`", 2);
		ft_putstr_fd(var, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		my_global->status = 1;
		return (1);
	}
	else
		return (0);
}
void	export_with_egal(char *var, char **v, int q)
{
	t_mini	*tmp;
	t_mini	*tmp1;

	tmp1 = my_global->m_env;
	tmp = my_global->m_env;
	if (ft_strchr(var, '='))
	{
		if (search_exp(v[0]) == 0)
		{
			tmp = ft_add_new(v[0], v[1], 0);
			add_back_lst(&my_global->m_env, tmp);
		}
		else if (search_exp(v[0]) == 1 && q == 0)
			export_ecrase(&tmp1, v);
		else if (search_exp(v[0]) == 1 && q == 10)
			export_join(&tmp1, v);
	}
	else
	{
		if(search_exp(v[0]) == 0)
		{
			tmp = ft_add_new(v[0], v[1], 1);
			add_back_lst(&my_global->m_env, tmp);
		}
	}
}

void	ft_export(char *var)
{
	char	**v;
	int		i;
	int		q;

	q = 0;
	i = 0;
	v = NULL;
	export_null(var);
	if (var != NULL)
	{
		if (print_export_err(var) == 1)
			return ;
		v = var_split(var, '=');
		if (v[0][ft_strlen(v[0]) - 1] == '+')
		{
			q = 10;
			v[0] = ft_substr(v[0], 0, ft_strlen(v[0]) - 1);
		}
		export_with_egal(var, v, q);
		free(v);
	}
}
// int	main(int c, char **v, char **env)
// {
// 	t_mini	*b;

// 	(void)c;
// 	(void)v;
// 	b = env_iniit(env);
// 	ft_export("lm=kk", b);
// 	printf("-----------------------\n");
// 	ft_export(NULL, b);
// 	printf("-----------------------\n");

// 	ft_export("lm=yy", b);
// 	printf("-----------------------\n");
// 	ft_export(NULL, b);
// 	printf("-----------------------\n");
// }
