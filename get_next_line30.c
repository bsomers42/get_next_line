/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line30.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/29 13:49:34 by bsomers       #+#    #+#                 */
/*   Updated: 2021/12/13 18:04:08 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h>


#define BUFFER_SIZE 3

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		len;
	char	*dup;
	int		i;

	len = 0;
	i = 0;
	while (s[len] != '\0')
		len++;
	dup = malloc((sizeof(char)) *(len + 1));
	if (dup == NULL)
		return (NULL);
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	size_t			count;
	size_t			strl;

	count = 0;
	if (s == NULL)
		return (0);
	strl = ft_strlen(s);
	// if (start >= strl)
	// 	return (ft_strdup(""));
	if ((start + len) > strl)
		len = strl - start;
	sub = malloc((len + 1) * (sizeof(unsigned char)));
	if (sub == NULL)
		return (NULL);
	while (count < len && s[start] != '\0')
	{
		sub[count] = s[start];
		start++;
		count++;
	}
	sub[count] = '\0';
	return(sub);
}

static char	*joinstr(char *s1, char c, char *sdef)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		sdef[i] = s1[i];
		i++;
	}
	sdef[i] = c;
	sdef[i + 1] = '\0';
	return (sdef);
}

char	*ft_charjoin(char *s1, char c)
{
	char	*sdef;
	int		i;

	i = 0;
	if (c == 0)
		return (0);
	if (s1)
		i = ft_strlen(s1);
	if (s1 == NULL)
	{
		sdef = malloc((2) * (sizeof(char)));
		if (sdef == NULL)
			return (NULL);
		sdef[0] = c;
		sdef[1] = '\0';
		return (sdef);
	}
	sdef = malloc((i + 2) * (sizeof(char)));
	if (sdef == NULL)
		return (NULL);
	sdef = joinstr(s1, c, sdef);
	//free(s1);
	return (sdef);
}

// char *gnl_newline(char *nextline, char *buf, int n)
// {
// 	char *lastpart;

// 	lastpart = ft_substr(buf, 0, n);
// 	nextline = ft_strjoin(nextline, lastpart);
// 	free (lastpart);
// 	return (nextline);
// }

char *get_next_line(int fd)
{
	char	buf[BUFFER_SIZE + 1];
	int		ret;
	int		n;
	char	*nextline;
	static char *rest;
	
	ret = 0;
	n = 0;
	nextline = NULL;
	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (rest != NULL)
	{
		nextline = ft_strdup(rest);
		n = ft_strlen(nextline);
		free(rest);
	}
	printf("Restnextline: --%s--\n", nextline);
	while (buf[n] != '\n')
	{
		if (buf[n] == '\0' || ret == 0)
		{
			printf("reading\n");
			ret = read(fd, buf, BUFFER_SIZE);
			if (ret <= 0)
			{
				if (nextline != NULL)
					return (nextline);
				return (NULL);
			}
			buf[ret] = '\0';
			n = 0;
		}
		nextline = ft_charjoin(nextline, buf[n]);
		printf("Looping: %c, nextline: --%s--, buf: --%s--, n: %d, ret: %d\n", buf[n], nextline, buf, n, ret);
		if (buf[n] == '\n')
			break;
		n++;
	}
	if (buf[n] == '\n')
	{
		nextline = ft_charjoin(nextline, buf[n]);
		rest = ft_substr(buf, n, BUFFER_SIZE - n);
		return (nextline);
	}
	return (NULL);
}

int	main()
{
	int fd;
	int	i;
	char *str;

	i = 0;
	fd = open("42", O_RDONLY);
    while (i < 7)
    {
		printf("\n\nGNL RUN %d:\n", i);
		str = get_next_line(fd);
	    printf("RETURNVAL: --%s--\n", str);
		free (str);
        i++;
    }
    return(0);
}
