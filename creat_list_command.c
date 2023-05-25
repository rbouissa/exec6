#include "minishell.h"

void	freestack_last(t_list **stack)
{
	t_list	*temp;

	if (!*stack)
		return ;
	temp = *stack;
	while (*stack && (*stack)->next && (*stack)->token != 5)
	{
		(*stack) = (*stack)->next;
		free(temp->data);
		free(temp);
		temp = *stack;
	}
	*stack = (*stack)->next;
	if (temp->data)
		free(temp->data);
	free(temp);
}

int	file_numb(t_list *comm)
{
	t_list	*command;
	t_list	*cm;
	int		token;

	token = -2;
	cm = comm;
	command = comm;
	while (command->next)
	{
		if (command->next->token == 5 || command->next == NULL)
			break ;
		if (command->token == 2 || command->token == 9)
		{
			if (token != -2)
				close(token);
			if (command->token == 2)
			{
				token = open(command->next->data, O_CREAT | O_WRONLY, 0777);
				if (token == -1)
				{
					perror("open");
					my_global->status = -1;
					return (my_global->status);
				}
			}
			else if (command->token == 9)
			{
				token = open(command->next->data, O_CREAT | O_WRONLY | O_APPEND,
						0777);
				if (token == -1)
				{
					perror("open");
					my_global->status = 1;
					return (-1);
				}
			}
		}
		command = command->next;
	}
	return (token);
}

int	her_pip(t_list *cmd)
{
	while (cmd)
	{
		if (cmd->token == 5)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

int	file_numb2(t_list *comm)
{
	t_list	*command;
	t_list	*cm;
	int		token;

	token = -2;
	cm = comm;
	command = comm;
	while (command->next)
	{
		if (command->next->token == 5 || command->next == NULL)
			break ;
		if (command->token == 3)
		{
			if (token != -2)
				close(token);
			token = open(command->next->data, O_RDONLY);
			if (token == -1)
			{
				printf("minishell: %s: No such file or directory\n",
						command->next->data);
				my_global->status = 1;
				return (-1);
			}
		}
		command = command->next;
	}
	return (token);
}

// void	one_cmd_splited(t_list **command,t_list **comm)
// {
// 	while (command)
// 	{
// 		//split_cm_one_pip(command,comm,token);
// 		if (command->token == 2 || command->token == 3 || command->token == 9)
// 		{
// 			if (command->token == 2 || command->token == 9)
// 				token = file_numb(comm);
// 			else if (command->token == 3)
// 				token2 = file_numb2(comm);
// 			command = command->next->next;
// 		}
// 		else if (command->token == 4)
// 		{
// 			command = command->next;
// 			hrd = ft_strjoin(hrd, spliter);
// 			hrd = ft_strjoin(hrd, command->data);
// 			command = command->next;
// 		}
// 		else
// 		{
// 			cmd = ft_strjoin(cmd, spliter);
// 			cmd = ft_strjoin(cmd, command->data);
// 			command = command->next;
// 		}
// 	}
// }
// t_norm *init_norm()
// {
//     t_norm *norm;
//     norm = malloc(sizeof(t_norm));
//     norm->cmd =NULL;
// }

t_cmd	*split_to_commands(t_list *comm)
{
	char	*cmd;
	char	*hrd;
	t_list	*command;
	char	**herdoc;
	char	**full_cmd;
	int		check;
	char	*spliter;
	t_cmd	*list;
	int		token;
	int		token2;

	cmd = NULL;
	hrd = NULL;
	herdoc = NULL;
	full_cmd = NULL;
	list = NULL;
	command = comm;
	check = 0;
	spliter = malloc(2);
	spliter[0] = 19;
	spliter[1] = '\0';
	token = -2;
	token2 = -2;
	if (!her_pip(command))
	{
		while (command)
		{
			//split_cm_one_pip(command,comm,token);
			if (command->token == 2 || command->token == 3
				|| command->token == 9)
			{
				if (command->token == 2 || command->token == 9)
					token = file_numb(comm);
				else if (command->token == 3)
					token2 = file_numb2(comm);
				command = command->next->next;
			}
			else if (command->token == 4)
			{
				command = command->next;
				hrd = ft_strjoin(hrd, spliter);
				hrd = ft_strjoin(hrd, command->data);
				command = command->next;
			}
			else
			{
				cmd = ft_strjoin(cmd, spliter);
				cmd = ft_strjoin(cmd, command->data);
				command = command->next;
			}
		}
		if (hrd != NULL)
		{
			if (cmd == NULL)
			{
				full_cmd = malloc(sizeof(char *));
				full_cmd[0] = 0;
				list = ft_lstnew_new(full_cmd, token, token2, ft_split(hrd, 19),
						1);
				token = -2;
				token2 = -2;
			}
			else
			{
				list = ft_lstnew_new(ft_split(cmd, 19), token, token2,
						ft_split(hrd, 19), 1);
				token = -2;
				token2 = -2;
			}
		}
		else
		{
			herdoc = malloc(sizeof(char *));
			herdoc[0] = 0;
			list = ft_lstnew_new(ft_split(cmd, 19), token, token2, herdoc, -2);
			token = -2;
			token2 = -2;
			//free(herdoc);
		}
		free(cmd);
		free(hrd);
	}
	//for multiple pipe
	else
	{
       
		while (command != NULL)
		{
			if (command->token == 5)
			{
                if(command->next!=NULL)
				command = command->next;
				if (command->token == 2 || command->token == 9)
					token = file_numb(comm);
				else if (command->token == 3)
					token2 = file_numb2(comm);
				freestack_last(&comm);
				if (hrd != NULL)
				{
					if (cmd != NULL)
					{
						ft_lstadd_back_new(&list,
											ft_lstnew_new(ft_split(cmd, 19),
															token,
															token2,
															ft_split(hrd,
																	19),
															1));
					}
					else
					{
						full_cmd = malloc(sizeof(char *));
						full_cmd[0] = 0;
						ft_lstadd_back_new(&list, ft_lstnew_new(full_cmd, token,
									token2, ft_split(hrd, 19), 1));
					}
				}
				else
				{
                     
					herdoc = malloc(sizeof(char *));
					herdoc[0] = 0;
					ft_lstadd_back_new(&list, ft_lstnew_new(ft_split(cmd, 19),
								token, token2, herdoc, 1));
				}
				token = -2;
				token2 = -2;
				free(cmd);
				free(hrd);
				cmd = NULL;
				hrd = NULL;
			}
			else if (command->token == 2 || command->token == 3
					|| command->token == 9)
			{
				if (command->token == 2 || command->token == 9)
					token = file_numb(comm);
				else if (command->token == 3)
					token2 = file_numb2(comm);
				command = command->next->next;
			}
			else if (command->token == 4)
			{
				command = command->next;
				hrd = ft_strjoin(hrd, spliter);
				hrd = ft_strjoin(hrd, command->data);
				command = command->next;
			}
			//this part make a segfaul in the function of get token file
			else
			{
				cmd = ft_strjoin(cmd, spliter);
				cmd = ft_strjoin(cmd, command->data);
				command = command->next;
			}
		}
		if (hrd != NULL)
		{
			if (cmd != NULL)
				ft_lstadd_back_new(&list, ft_lstnew_new(ft_split(cmd, 19),
							token, token2, ft_split(hrd, 19), 1));
			else
			{
				full_cmd = malloc(sizeof(char *));
				full_cmd[0] = 0;
				ft_lstadd_back_new(&list, ft_lstnew_new(full_cmd, token, token2,
							ft_split(hrd, 19), 1));
			}
			token = -2;
			token2 = -2;
		}
		else
		{
			herdoc = malloc(sizeof(char *));
			herdoc[0] = 0;
			ft_lstadd_back_new(&list, ft_lstnew_new(ft_split(cmd, 19), token,
						token2, herdoc, 1));
			token = -2;
			token2 = -2;
		}
		free(hrd);
		free(cmd);
	}
	free(spliter);
	ft_free_cmd(comm);
	return (list);
}
