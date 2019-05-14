/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 15:32:28 by tdarchiv          #+#    #+#             */
/*   Updated: 2019/05/14 20:30:19 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftio.h"
#include "ftstring.h"
#include "ftconvert.h"
#include <unistd.h>
#include <stdlib.h>

int		parse_header(int fd, int *width, int *height)
{
	char	*line;
	int		header_bytes;

	ft_gnl(fd, &line, "\t\n\r\v ");
	header_bytes = ft_strlen(line) + 1;
	if (ft_strncasecmp(line, "P6", 2) != 0)
	{
		ft_printf("Bad header [%s]\n", line);
		ft_error(__func__, __LINE__);
	}
	free(line);
	ft_gnl(fd, &line, "\t\n\r\v ");
	header_bytes += ft_strlen(line) + 1;
	free(line);
	*width = ft_atoi(line);
	ft_gnl(fd, &line, "\t\n\r\v ");
	header_bytes += ft_strlen(line) + 1;
	free(line);
	*height = ft_atoi(line);
	ft_gnl(fd, &line, "\t\n\r\v ");
	header_bytes += ft_strlen(line) + 1;
	free(line);
	return (header_bytes);
}

/*
** We want to use read() for the pixel data but ft_gnl will mess with the cursor
** offset.
** To reposition the cursor immediately after the metadata, we have to reopen
** the file and read past the metadata to skip it.
** ft_gnl will return incorrect data on a sucessive read if ft_gnl doesn't reach
** the end of the file, so we do a dummy gnl call at the end
*/

char	*read_pixel_data(char *filename, int cursor, int pixel_count)
{
	char	*pixels;
	int		fd;
	char	*line;

	if (!(pixels = malloc(pixel_count * 3)))
		ft_error(__func__, __LINE__);
	if (pixels == NULL)
		ft_error(__func__, __LINE__);
	fd = ft_fopen_read(filename);
	read(fd, pixels, cursor);
	read(fd, pixels, pixel_count * 3);
	ft_gnl(fd, &line, "\n");
	free(line);
	close(fd);
	return (pixels);
}

char	*load_texture(char *filename, int *width, int *height)
{
	int	fd;
	int	header_bytes;

	ft_printf("Loading [%s] ... ", filename);
	fd = ft_fopen_read(filename);
	header_bytes = parse_header(fd, width, height);
	close(fd);
	ft_printf("%d x %d\n", *width, *height);
	return (read_pixel_data(filename, header_bytes, *width * *height));
}
