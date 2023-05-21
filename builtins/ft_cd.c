/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: met-tahe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:52:51 by met-tahe          #+#    #+#             */
/*   Updated: 2023/03/08 11:52:52 by met-tahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//cette fonction change OLDPWD dans mon env;
char	*oldpwd_change(char *path, t_mini *tmp)
{
	char	*pwd;
	t_mini	*tmp1;

	tmp1 = tmp;
	while (tmp1)
	{
		if (ft_strncmp(tmp1->data_var, "OLDPWD", 6) == 0)
		{
			pwd = getcwd(NULL, 0);
			if (pwd == NULL)
				pwd = get_path();
			path = ft_strdup(tmp1->data_val);
			free(tmp1->data_val);
			tmp1->data_val = ft_strdup(pwd);
			free(pwd);
			break ;
		}
		tmp1 = tmp1->next;
	}
	// path = getenv("OLDPWD");
	return (path);
}

// cette fonction change PWD dans mon env;
void	new_pwd_change(t_mini *tmp, char *s1, int size)
{
	char	*pwd;

	while (tmp)
	{
		if (ft_strncmp(tmp->data_var, s1, size) == 0)
		{
			pwd = getcwd(NULL, 0);
			if (pwd == NULL)
				pwd = get_path();
			free(tmp->data_val);
			if (pwd != NULL)
				tmp->data_val = ft_strdup(pwd);
			free(pwd);
			break ;
		}
		else
			tmp = tmp->next;
	}
}
void	change_directory(char *str, t_mini *tmp)
{
	
	new_pwd_change(tmp, "OLDPWD", 6);
	
	if (chdir(str) < 0)
		(my_global->status = 1, printf("cd: HOME not set\n"));
}

void	cd_with_symbol(char *path, t_mini *tmp)
{
	path = oldpwd_change(path, tmp);
	if (chdir(path) < 0)
		(my_global->status = 1, perror("cd"));
	else
		printf("%s\n", path);
}

char	*home_path(t_mini *lst)
{
	char	*home;
	t_mini	*tmp;

	tmp = lst;
	home = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->data_var, "HOME", 4) == 0)
		{
			home = ft_strdup(tmp->data_val);
			break ;
		}
		tmp = tmp->next;
	}
	return (home);
}

void	ft_cd(char *path, t_mini *lst)
{
	t_mini	*tmp;
	char	*pwd;
	char	*home_check;

	tmp = lst;
	pwd = getcwd(NULL, 0);
	home_check = home_path(lst);
	if (path == NULL)
		change_directory(home_check, tmp);
	else if (ft_strcmp(path, "") == 0)
	{
		if (chdir(pwd) < 0)
			(my_global->status = 1, perror("cd"));
	}
	else if (path == NULL || ft_strcmp(path, "~") == 0)
		change_directory(home_check, tmp);
	else if (ft_strcmp(path, "-") == 0)
		cd_with_symbol(path, tmp);
	else if (access(path, R_OK) != 0)
		(my_global->status = 1, cd_error(path));
	else
		change_directory(path, tmp);
	tmp = lst;
	new_pwd_change(tmp, "PWD", 3);
	(free(pwd),free(home_check));
}

// int	main(int c, char **v, char **env)
// {
// 	t_mini	*lst;
// 	int		i;

// 	i = 0;
// 	(void)v;
// 	(void)c;
// 	(void)env;
// 	lst = env_iniit(env);
// 	//ft_env(lst);
// 	printf("------------------------------\n");
// 	ft_cd("rr", lst);
// 	printf("------------------------------\n");
// 	//ft_env(lst);
// 	system("leaks minishell");
// 	//ft_cd("-", lst);
// }
