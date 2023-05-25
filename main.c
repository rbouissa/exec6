#include "minishell.h"
//cat Makefile >1| <<k <<l<<l cat>>1|ls|wc|cat >>1
//<Makefile cat <main.c | wc -l;

// t_global			*my_global;

int	ther_are_pipe(char *str)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (str[i])
	{
		if (str[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

void	print_cmd(t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = cmd;
	while (tmp)
	{
		i = 0;
		if (tmp->cmd == NULL)
			printf("cmd = NULL\n");
		while (tmp->cmd && tmp->cmd[i])
		{
			printf("%s\n", tmp->cmd[i]);
			i++;
		}
		printf("infile = %d\n", tmp->infile);
		printf("outfile = %d\n", tmp->outfile);
		i = 0;
		while (tmp->herdoc && tmp->herdoc[i])
		{
			printf("herdoc = %s\n", tmp->herdoc[i]);
			i++;
		}
		tmp = tmp->next;
	}
}

int	alot_of_spliter(char *s)
{
	int	i;

	i = 0;
	while (find_spliter(s[i], "|<> \t"))
		i++;
	if (s[i] && !find_spliter(s[i], "|<> \t"))
		return (1);
	else
		return (0);
}

void	init_my_global(void)
{
	my_global->m_cmd = NULL;
	my_global->hrdsize = 0;
	my_global->status = 0;
	my_global->hrd = NULL;
	my_global->hrd_id = 0;
	my_global->count_cmd = 0;
	my_global->id = NULL;
	//my_global->id[0] = 0;
}
void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		ft_free(tmp->cmd);
		ft_free(tmp->herdoc);
		tmp = tmp->next;
	}
	free(cmd);
}
int	main(int argc, char **argv, char **env)
{
	char			*str;
	t_list			*cmd;
	t_cmd			*commands;
	t_list			*tmp;
	t_mini			*mini;
	int				i;
	struct termios	term;
	struct termios	term2;
	char			*str_2;

	i = 0;
	mini = NULL;
	tmp = NULL;
	str = NULL;
	(void)argc;
	(void)argv;
	str_2 = NULL;
	my_global = malloc(sizeof(t_global));
	mini = env_iniit(env);
	my_global->m_env = mini;
	init_my_global();
	my_global->status = 0;
	signal(SIGINT, ctrlc_handler);
	signal(SIGQUIT, ctrld_handler);
	while (1)
	{
		tcgetattr(0, &term);
		term2 = term;
		term.c_lflag &= ~ISIG;
		term.c_lflag &= ~ECHOCTL;
		tcsetattr(0, TCSANOW, &term);
		str = readline("minishell>");
		tcsetattr(0, TCSANOW, &term2);
		if (!str)
		{
			(write(1, "exit\n", 5), free(str));
			exit(my_global->status);
		}
        
		str_2 = new_expand(str, mini);
       // printf("---==>str_2==%s\n",str_2);
		if (str_2 != NULL && check_eroor(str_2) && alot_of_spliter(str_2))
		{
			//add expanding variables
			if (str_2[0])
			{
				cmd = ft_split_them(str_2);
              
				tmp = cmd;
				//(void)commands;
				 while(tmp)
				 {
				    printf("00---%s\n",tmp->data);
				    tmp=tmp->next;
				 }
				
				commands = split_to_commands(cmd);
				if (commands == NULL)
					continue ;
				//system("leaks minishell");
				//tmp = commands;
				//print_cmd(commands);
				//  if (commands->outfile != -1 && commands->outfile != -1)
				// 	exec_cmd(mini, commands, env);
				//free_cmd(commands);
				//ft_free_cmd2(cmmands);
			}
		}
		add_history(str);
		free(str);
		str = NULL;
		if (str_2 != NULL)
		{
			free(str_2);
			ft_free_cmd2(commands);
			commands = NULL;
			str_2 = NULL;
		}
	}
}
