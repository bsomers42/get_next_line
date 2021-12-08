/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_copy3.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/29 13:49:34 by bsomers       #+#    #+#                 */
/*   Updated: 2021/12/08 16:48:36 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// This get_next_line is recursive with a few static variables.
// Notes:
// 	* On line xxx, you set nextline to NULL because it is has the value of the previous
// 	  time you ran gnl (that ended with a newline character. That's also when R is set to 1).
// 	* In case you enter a newline, you determine nexpart with ft_substr. You pass n + 1 as
// 	  third argument. The '1' is needed to take the newline with you.
// 	* the if-statement when you encounter a newline, is to use memmove. This way you make
// 	  sure you save the part in the buffer áfter the newline character. r is being set to 
// 	  1, so that gnl won't read again and overwrite this leftover when you call it again.

#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
//#include "get_next_line.h"

#define BUFFER_SIZE 42


///////////BELOW IS IN UTILS////////////

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static char	*joinstr(char *s1, char *s2, char *sdef)
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
	while (s2[j] != '\0')
	{
		sdef[i] = s2[j];
		i++;
		j++;
	}
	sdef[i] = '\0';
	return (sdef);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*sdef;
	int		i;
	int		j;

	i = 0;
	if (s2 == NULL)
		return (0);
	if (s1)
		i = ft_strlen(s1);
	j = ft_strlen(s2);
	if (s1 == NULL)
	{
		sdef = malloc((j + 1) * (sizeof(char)));
		if (sdef == NULL)
			return (NULL);
		while (i <= j)//adjusted
		{
			sdef[i] = s2[i];
			i++;
		}
		//sdef[i] = '\0';
		return (sdef);
	}
	sdef = malloc((i + j + 1) * (sizeof(char)));
	if (sdef == NULL)
		return (NULL);
	sdef = joinstr(s1, s2, sdef);
	free(s1);
	return (sdef);
}

static	int	ft_overlap(const void *dst, const void *src, size_t len)
{
	if (src < dst && dst < src + len)
		return (1);
	else
		return (0);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	size_t	x;

	i = 0;
	if (((void *)dst == NULL) && ((void *)src == NULL))
		return (NULL);
	if (ft_overlap(dst, src, len))
	{
		while (i < len)
		{
			x = len - i - 1;
			((unsigned char *)dst)[x] = ((unsigned char *)src)[x];
			i++;
		}
		return (dst);
	}
	else
	{
		while (i < len)
		{
			i++;
			((unsigned char *)dst)[i - 1] = ((const unsigned char *)src)[i - 1];
		}
	}
	return (dst);
}

////////////////ABOVE IS IN UTILS///////////

size_t	ft_strn(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (0);
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

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	int			ret = 0;
	int			n = 0;
	static char *nextpart = NULL;
	static char *nextline = NULL;
	static int 	R = 0;

	printf("GNL START");

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (R == 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret < 0)
			return (NULL);
		if (ret == 0)
			return (NULL);
		buf[ret] = '\0';
	}

	printf("__Buf: --%s--, Val of R: %d, ret: %d\n", buf, R, ret);


	if (ret != 0 || R == 1)
	{
		if (R == 1)
			nextline = NULL;
		n = ft_strn(buf);
		if (ret == 0 && R == 0)
			return(NULL);
		if (n == 0 && buf[n] != '\n' && buf[n] != '\0') //last condition just added, after adding this - gnlTester gave sigsegv results
		{
			printf("No newline in buf\n");
			nextpart = ft_substr(buf, 0, BUFFER_SIZE);
			// if (ret == 0) //in case EOF, just added DID NOT WORK
			// 	return (NULL);
			nextline = ft_strjoin(nextline, nextpart);
			free (nextpart);
			R = 0;
			get_next_line(fd);
		}
		if (buf[n] == '\n')
		{			
			printf("Newline in buf\n");
			nextpart = ft_substr(buf, 0, n + 1);
			nextline = ft_strjoin(nextline, nextpart);
			free (nextpart); 
			if (n < ret || ret == 0)
			{
				R = 1;
				printf("Before moving. Value of n: %d, buf: --%s--, nextline: --%s--\n", n, buf, nextline);
				ft_memmove(buf, buf + n + 1, BUFFER_SIZE);
				printf("After moving. Value of n: %d, buf: --%s--, nextline: --%s--\n", n, buf, nextline);
			}
			return (nextline);
		}
		nextpart = NULL;
		printf("Here\n");
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
	printf("\033[0;35m");
	printf("\n==================================\n");
	printf("\033[0m");

	while ((str = get_next_line(fd)))
    {
		printf("\033[0;31m");
		printf("\n==================================\nGNL RUN:   ");
		printf("\033[0m");
		printf("\033[0;32m");
	    printf("--%s--\n", str);
		printf("\033[0m");
		free (str);
    }
	str = get_next_line(fd);
    	printf("\033[0;31m");
		printf("\n==================================\nGNL RUN:   ");
		printf("\033[0m");
		printf("\033[0;33m");
	    printf("--%s--\n", str);
		printf("\033[0m");
		free (str);
    return(0);
}
