/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 15:32:28 by tdarchiv          #+#    #+#             */
/*   Updated: 2019/05/03 15:32:32 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftio.h>
#include <ftstring.h>
#include <ftconvert.h>
#include <unistd.h>
#include <stdlib.h>

/*
** We want to use read() for the pixel data but ft_gnl will mess with the cursor
** offset.
** To reposition the cursor immediately after the metadata, we have to reopen
** the file and read past the metadata to skip it.
*/

char	*read_pixel_data(char *filename, int cursor, int pixel_count)
{
	char	*pixels;
	int		fd;

	pixels = malloc(pixel_count * 3);
	if (pixels == NULL)
		ft_error(__func__, __LINE__);
	fd = ft_fopen_read(filename);
	read(fd, pixels, cursor);
	read(fd, pixels, pixel_count * 3);
	close(fd);
	return (pixels);
}

char	*load_texture(char *filename, int *width, int *height)
{
	int		fd;
	char	*line;
	int		cursor;

	cursor = 0;
	fd = ft_fopen_read(filename);
	ft_gnl(fd, &line, "\t\n\r\v ");
	cursor += ft_strlen(line) + 1;
	if (ft_strncasecmp(line, "P6", 2) != 0)
	{
		ft_printf("Bad header [%s]\n", line);
		ft_error(__func__, __LINE__);
	}
	ft_gnl(fd, &line, "\t\n\r\v ");
	cursor += ft_strlen(line) + 1;
	*width = ft_atoi(line);
	ft_gnl(fd, &line, "\t\n\r\v ");
	cursor += ft_strlen(line) + 1;
	*height = ft_atoi(line);
	ft_gnl(fd, &line, "\t\n\r\v ");
	cursor += ft_strlen(line) + 1;
	close(fd);
	ft_printf("%d x %d\n", *width, *height);
	return (read_pixel_data(filename, cursor, *width * *height));
}
