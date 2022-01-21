/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/14 18:51:36 by bsomers       #+#    #+#                 */
/*   Updated: 2021/12/17 17:07:36 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <limits.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "get_next_line.h"

typedef struct s_info
{
	int		ret;
	int		n;
	char	*nextline;
	int		a;
	int		flag;
}		t_info;

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len, t_info *stat);
void	*ft_memmove(void *dst, const void *src, size_t len);
char	*joinstr(char *s1, char c, char *sdef);

#endif
