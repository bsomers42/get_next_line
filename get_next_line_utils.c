/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/14 18:57:19 by bsomers       #+#    #+#                 */
/*   Updated: 2021/12/17 17:07:37 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*ft_substr(char const *s, unsigned int start, size_t len, t_info *stat)
{
	char			*sub;
	size_t			count;
	size_t			strl;

	count = 0;
	if (s == NULL)
		return (0);
	strl = ft_strlen(s);
	if (strl == 0)
		return (NULL);
	if ((start + len) > strl)
		len = strl - start;
	sub = malloc((len + 1) * (sizeof(unsigned char)));
	if (sub == NULL)
		stat->flag = 1;
	if (stat->flag == 1)
		return (NULL);
	while (count < len && s[start] != '\0')
	{
		sub[count] = s[start];
		start++;
		count++;
	}
	sub[count] = '\0';
	return (sub);
}

char	*joinstr(char *s1, char c, char *sdef)
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
