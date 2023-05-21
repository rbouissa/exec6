#include "../minishell.h"

void	ctrlc_handler(int sig)
{
	int	i;

	(void)sig;
	i = 0;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	if (my_global->hrd_id)
	{
		kill(my_global->hrd_id, SIGINT);
	}
	if (my_global->id)
	{
		while (my_global->id[i])
		{
			kill(my_global->id[i], SIGINT);
			i++;
		}
	}
	my_global->status = 1;
}

void	ctrld_handler(int sig)
{
	int	i;

	(void)sig;
	i = 0;
	if (my_global->hrd_id != 0)
		rl_on_new_line();
	else
	{
		rl_on_new_line();
		rl_redisplay();
	}
	if (my_global->id)
	{
		while (my_global->id[i])
		{
			kill(my_global->id[i], SIGQUIT);
			i++;
		}
	}
}

void	sig_sil(int sig)
{
	(void)sig;
	rl_on_new_line();
	//rl_redisplay();
	return ;
}
// void	read_heredoc(t_cmd *cmd, int *stat1)
// {
// 	char			*line;
// 	int				j;
// 	int				z;
// 	t_cmd			*tmp1;
// 	struct termios	term;
// 	struct termios	term2;
// 	int				d;

// 	j = 0;
// 	tmp1 = cmd;
// 	z = 0;
// 	line = NULL;
// 	tcgetattr(0, &term);
// 	term2 = term;
// 	term.c_lflag &= ~ISIG;
// 	term.c_lflag &= ~ECHOCTL;
// 	my_global->hrd_id = fork();
// 	if (my_global->hrd_id < 0)
// 		fct_error("fork");
// 	else if (my_global->hrd_id == 0)
// 	{
// 		(signal(SIGINT, SIG_DFL), signal(SIGQUIT, ctrld_handler));
// 		while (tmp1)
// 		{
// 			if (tmp1->herdoc && tmp1->herdoc[0] != NULL)
// 			{
// 				line = heredoc(tmp1->herdoc);
// 				ft_putstr_fd(line, my_global->hrd[j][1]);
// 				(free(line), exit(0));
// 				j++;
// 			}
// 			// if (*stat1 == 1)
// 			// {
// 			// 	my_global->status = 1;
// 			// 	break ;
// 			// }
// 			tmp1 = tmp1->next;
// 		}
// 		close_pipes(my_global->hrdsize, my_global->hrd);
// 	}
// 	else
// 	{
// 		waitpid(my_global->hrd_id, stat1, 0);
// 		d = 0;
// 		while (d < my_global->hrdsize)
// 		{
// 			close(my_global->hrd[d][1]);
// 			d++;
// 		}
// 		if (WIFSIGNALED(*stat1))
// 		{
// 			my_global->status = 1;
// 			(*stat1) = 1;
// 		}
// 	}
// 	//printf("------>>%d\n",my_global->status);
// }