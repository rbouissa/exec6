/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: met-tahe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:53:00 by met-tahe          #+#    #+#             */
/*   Updated: 2023/03/08 11:53:02 by met-tahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo(char **cmd)
{
	int		n;
	int		nb_arg;
	size_t	i;
	int		j;

	i = 2;
	n = 0;
	nb_arg = 1;
	j = 0;
	if (cmd[1])
	{
		if (ft_strncmp(cmd[1], "-n", 2) == 0)
		{
			while (cmd[1][i] == 'n' && cmd[1][i] != '\0')
				i++;
			if (ft_strlen(cmd[1]) == i)
				(n = 1, nb_arg = 2);
		}
	}
	while (cmd[nb_arg])
	{
		if (ft_strncmp(cmd[nb_arg], "-n", 2) == 0 && n == 1)
		{
			i = 2;
			while (cmd[nb_arg][i] == 'n' && cmd[nb_arg][i] != '\0')
				i++;
			if (ft_strlen(cmd[nb_arg]) == i &&j == 0)
			{
				(nb_arg++);
				continue ;
			}
			j = 1;
			(printf("%s", cmd[nb_arg]), printf(" "));
		}
		else
			(j =1,printf("%s", cmd[nb_arg]));
		nb_arg++;
		if (cmd[nb_arg])
			printf(" ");
	}
	if (n == 0)
		printf("\n");
}
// int	main(int c, char **v)
// {
// 	(void)c;
// 	echo(v);
// }
// while (cmd[1][i])
// {
// 	if (cmd[1][i] == '-')
// 	{
// 		i++;
// 		if (cmd[1][i] == 'n')
// 		{
// 			if(cmd[1][i+1]!='\0')
// 				break ;
// 			else
// 				i++;

// 		}
// 		else
// 			break ;
// 	}
// 	else
// 		break ;
// }