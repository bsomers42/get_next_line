/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/14 18:04:24 by bsomers       #+#    #+#                 */
/*   Updated: 2021/04/14 19:00:54 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h> //!
#include <sys/uio.h>//!
#include <unistd.h>//!
#include <stdio.h>//!
#include <fcntl.h>//!
#include "get_next_line.h"

#define BUF_SIZE 4096

int	get_next_line(int fd/*, char **line*/)
{
	int ret;
	char buf[BUF_SIZE +1];

	if (fd == 1)
	{
		printf("open error");
		return(1);
	}
	while (ret = (read(fd, buf, BUF_SIZE)))
	{
		buf[ret] = '\0';
		printf("%d, %s", ret, buf);
	}
printf("%d", ret);
if (close(fd) == -1)
{
	printf("close error");
	return (1);
}
return 0;
}

int	main()
{
	int fd;
	static int i;
	char **lines;

	fd = open("42", O_RDONLY);
	get_next_line(fd);
}