
#include "minishell.h"


static int	ft_intlen(int numb)
{
	int	cmpt;

	cmpt = 0;
	if (numb == 0)
	{
		cmpt ++;
	}
	if (numb < 0)
	{
		numb = numb * (-1);
		cmpt ++;
	}
	while (numb != 0)
	{
		numb = numb / 10;
		cmpt ++;
	}
	return (cmpt);
}

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c += 32;
	return (c);
}

char	*ft_itoa(int n)
{
	int		i;
	long	j;
	char	*numb;

	j = n;
	numb = (char *)(malloc (sizeof(char) * ft_intlen(n) + 1));
	i = ft_intlen(n) - 1;
	if (!numb)
		return (0);
	if (j < 0)
	{
		j = j * (-1);
		numb[0] = '-';
	}
	while (j != 0)
	{
		numb[i] = j % 10 + 48;
		j = j / 10;
		i --;
	}
	if (n == 0)
		numb[0] = '0';
	numb[ft_intlen(n)] = '\0';
	return (numb);
}
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if(s1==NULL)
	{
		return(2);
	}
	if(s2==NULL)
	{
		return(2);
	}
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		i++;
	}
	write(fd, s, i);
}

void	error_msg(char *s)
{
	ft_putstr_fd("exit\nminishell: exit: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(255);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if ((unsigned char)s1[i] < (unsigned char)s2[i])
		{
			return (-1);
		}
		else if ((unsigned char)s1[i] > (unsigned char)s2[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*p;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	k = ft_strlen(s);
	if (k < len)
		len = k;
	p = (char *)malloc(sizeof(*s) * (len + 1));
	if (!s || !p)
		return (0);
	while (s[i] && i < start)
		i++;
	while (s[i] && i < start + len)
	{
		p[j] = s[i];
		i++;
		j++;
	}
	p[j] = 0;
	return (p);
}

// char	*ft_strjoin(char *left_str, char *buff)
// {
// 	size_t	i;
// 	size_t	j;
// 	char	*str;

// 	if (!left_str)
// 	{
// 		left_str = (char *)malloc(1 * sizeof(char));
// 		left_str[0] = '\0';
// 	}
// 	// if (!left_str || !buff)
// 	// 	return (NULL);
// 	str = malloc(sizeof(char) * ((ft_strlen(left_str) + ft_strlen(buff)) + 1));
// 	if (str == NULL)
// 		return (NULL);
// 	i = -1;
// 	j = 0;
// 	if (left_str)
// 		while (left_str[++i] != '\0')
// 			str[i] = left_str[i];
// 	while (buff[j] != '\0')
// 		str[i++] = buff[j++];
// 	str[ft_strlen(left_str) + ft_strlen(buff)] = '\0';
// 	free(left_str);
// 	return (str);
// }
char	*ft_strjoin(char *left_str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;
    int check = 0;

	if (!left_str)
	{
		left_str = (char *)malloc(1 * sizeof(char));
		left_str[0] = '\0';
	}
	// if (!left_str || !buff)
	// 	return (NULL);
    if (!left_str)
    {
        left_str = malloc(1);
        left_str[0] = 0;
    }
    if(!buff)
    {
        buff = malloc(1);
        buff[0] = 0;
        check = 1;
    }
	str = malloc(sizeof(char) * ((ft_strlen(left_str) + ft_strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (left_str)
		while (left_str[++i] != '\0')
			str[i] = left_str[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen(left_str) + ft_strlen(buff)] = '\0';
	free(left_str);
    if (check == 1)
        free(buff);
	return (str);
}

 char	*ft_strcpy(char *dest,  char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(char *src)
{
	char	*dest;

	dest = (char *) malloc((sizeof(char) * ft_strlen(src)) + 1);
	if (!dest)
		return (0);
	dest = ft_strcpy(dest, src);
	return (dest);
}

void ft_write(char *s)
{
    int i;
    i= 0;
    while(s[i])
    {
        write(1,&s[i],1);
        i++;
    }
    write(1,"\n",1);
}