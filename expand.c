
#include "minishell.h"

char *get_it_witout_$(char *str)
{
	char	*var;
	int		i;
	int		j;

	i = 1;
	j = 0;
	var = malloc(ft_strlen(str));
	while (str[i])
	{
		var[j] = str[i];
		i++;
		j++;
	}
	var[j] = 0;
	return (var);
}

int	ft_len_val(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (i);
}

int	len_of_out(int j, char *env)
{
	int	k;

	k = j;
	while (env[k])
		k++;
	return (k);
}

char	*find_valeur(char *s, char **env)
{
	char	*str;
	char	*var;
	int		i;
	int		j;
	int		k;

	i = 0;
	
	while (env[i])
	{
        j = 0;
		str = malloc(ft_len_val(env[i]));
		while (env[i][j] && env[i][j] != '=')
		{
			str[k] = env[i][j];
			j++;
			k++;
		}
		str[k] = 0;
		k = 0;
		if (!ft_strcmp(str, get_it_witout_$(s)))
		{
            //printf("FFF\n");
			free(str);
			j++;
			var = malloc(len_of_out(j, env[i]) + 1);
			while (env[i][j])
			{
				var[k] = env[i][j];
				j++;
				k++;
			}
			var[k] = 0;
		}
		else
			i++;
	}
	return (var);
}
