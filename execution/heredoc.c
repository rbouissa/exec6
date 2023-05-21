/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: met-tahe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 18:15:40 by met-tahe          #+#    #+#             */
/*   Updated: 2023/03/31 18:15:42 by met-tahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*heredoc(char **herdoc)
{
	char	*s;
	int		i;
	char	*reading;
	//char *l;
	i = 0;
	reading= NULL; 
	
	while (herdoc && herdoc[i])
	{
		s = readline("> ");
		if(reading!=NULL)
		{
				free(reading);
				reading = NULL;
		}
		while (s)
		{
			if (ft_strcmp(s, herdoc[i]) == 0)
			{
				free(s);
				break ;
			}
		//	if (herdoc[i + 1] == NULL)
			//{
				s = new_expand(s,my_global->m_env); // expand
				reading = ft_strjoin(reading, s);
				reading = ft_strjoin(reading, "\n");
				free(s);
			//}
			s = readline("> ");
		}
		i++;
	}
	return (reading);
}

