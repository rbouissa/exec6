/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: met-tahe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:09:53 by met-tahe          #+#    #+#             */
/*   Updated: 2023/03/16 11:09:55 by met-tahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset(char *var, t_mini **tmp)
{
	t_mini	*exp;
	t_mini	*tmp1;

	exp = *tmp;
	tmp1 = *tmp;
	if (var == NULL)
		(ft_putstr_fd("miissing variiable name\n", 2),my_global->status = 1);
	else
	{
		if (check_error(var) == 0)
		{
			my_global->status = 1;
			ft_putstr_fd("minishell: unset:`", 2);
			ft_putstr_fd(var, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return ;
		}
		if (ft_strcmp((*tmp)->data_var, var) == 0)
		{
			tmp1 = (*tmp)->next;
			free((*tmp)->data_var);
			free((*tmp)->data_val);
			free((*tmp));
			*tmp = tmp1;
			return ;
		}
		else
		{
			while (*tmp)
			{
				if (ft_strcmp((*tmp)->data_var, var) == 0)
				{
					tmp1->next = (*tmp)->next;
					free((*tmp)->data_var);
					free((*tmp)->data_val);
					free(*tmp);
					
					break ;
				}
				else
				{
					tmp1 = *tmp;
					*tmp = (*tmp)->next;
				}
			}
		}
	}
	*tmp = exp;
	
}
// int	main(int c, char **v, char **env)
// {
// 	t_mini	*b;

// 	(void)c;
// 	(void)v;
// 	b = env_iniit(env);
// 	//ft_export("ghkg", b);
// 	ft_unset("PWD", &b);
// 	printf("---------------------------\n");
// 	system("leaks minishell");
// 	//ft_export(NULL, b);
// 	printf("---------------------------\n");
// }
