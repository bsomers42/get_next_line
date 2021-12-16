/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line33_DONE.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/29 13:49:34 by bsomers       #+#    #+#                 */
/*   Updated: 2021/12/15 13:40:17 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h>

#define BUFFER_SIZE 1

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	size_t			count;
	size_t			strl;

	count = 0;
	if (s == NULL)
		return (0);
	strl = ft_strlen(s);
	if (strl == 0) //added so he doesn't return just a nullterm
		return (NULL);
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
	free(s1);
	return (sdef);
}

// char *find_and_make_newline(char *buf, int n, char *nextline, int ret)
// {
// 	while (buf[n] != '\n')
// 	{
// 		if ((buf[n] == '\0' || ret == 0))
// 		{
// 			ret = read(fd, buf, BUFFER_SIZE);
// 			if (ret <= 0)
// 			{
// 				if (nextline != NULL)
// 					return (nextline);
// 				return (NULL);
// 			}
// 			buf[ret] = '\0';
// 			n = 0;
// 		}
// 		if (buf[n] == '\n')
// 			break;
// 	 	nextline = ft_charjoin(nextline, buf[n]);
// 		n++;
// 	}
// 	return (nextline);
// }

char *gnl_arrange(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	int		ret;
	int		n;
	static int R;
	char *nextline;

	nextline = NULL;
	ret = 0;
	n = 0;
	 printf("Buf: --%s--\n", buf);
	if (R == 1)
	{
		while ((buf[n] != '\n') && (buf[n] != '\0') /*&& (n != -1)*/)
			n++;
		if (n < (BUFFER_SIZE - 1) && buf[n] != '\0') //a.k.a., if there's a newline
		{
			nextline = ft_substr(buf, 0, n + 1);
			ft_memmove(buf, buf + n + 1, BUFFER_SIZE - n);
			return(nextline);
		}
		nextline = ft_substr(buf, 0, n);
		R = 0;
	}
	//nextline = find_and_make_newline(buf, n, nextline, ret);
	while (buf[n] != '\n')
	{
		if ((buf[n] == '\0' || ret == 0))
		{
			ret = read(fd, buf, BUFFER_SIZE);
			printf("reading\n");
			if (ret <= 0)
			{
				if (nextline != NULL)
					return (nextline);
				return (NULL);
			}
			buf[ret] = '\0';
			n = 0;
		}
		if (buf[n] == '\n')
			break;
	 	nextline = ft_charjoin(nextline, buf[n]);
		 printf("Nextline: --%s--\n", nextline);
		n++;
	}
	if (buf[n] == '\n')
	{
		nextline = ft_charjoin(nextline, buf[n]);
		 printf("Nextline later: --%s--, buf before: --%s--, ret: %d\n", nextline, buf, ret);
		if (n < ret && (buf[n /*+ 1*/] != '\0')) //HIJ BLIJFT RUNNEN NA TOEVOEGING +1 -> WHY?
		{
			ft_memmove(buf, buf + n + 1, BUFFER_SIZE - n);
			R = 1;
			printf("Buf after: --%s--", buf);
		}
	}
	return (nextline);
}

char *get_next_line(int fd)
{
	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	return (gnl_arrange(fd));
}
