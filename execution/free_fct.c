
#include "../minishell.h"

void	struct_free(t_vars *vars)
{
	int	i;

	i = 0;
	
	while (i <= vars->pip_count)
	{
		free(vars->fd[i]);
		i++;
	}
	free(vars->fd);
	i = 0;
	while(vars->paths[i])
	{
		free(vars->paths[i]);
		i++;
	}
	free(vars->paths);
	free(vars);
}

void global_free()
{
	int i;

	i = 0;
	while(i <= my_global->hrdsize)
	{
		free(my_global->hrd[i]);
		i++;
	}
	free(my_global->hrd);
}