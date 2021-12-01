/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/14 18:57:19 by bsomers       #+#    #+#                 */
/*   Updated: 2021/11/30 20:03:37 by bsomers       ########   odam.nl         */
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
