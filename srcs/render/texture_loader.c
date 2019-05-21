/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 15:32:28 by tdarchiv          #+#    #+#             */
/*   Updated: 2019/05/21 03:34:24 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "config.h"
#include "ftio.h"
#include "ftstring.h"
#include "ftconvert.h"
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>

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
	ft_strdel(&line);
	ft_gnl(fd, &line, "\t\n\r\v ");
	header_bytes += ft_strlen(line) + 1;
	*width = ft_atoi(line);
	ft_strdel(&line);
	ft_gnl(fd, &line, "\t\n\r\v ");
	header_bytes += ft_strlen(line) + 1;
	*height = ft_atoi(line);
	ft_strdel(&line);
	ft_gnl(fd, &line, "\t\n\r\v ");
	header_bytes += ft_strlen(line) + 1;
	ft_strdel(&line);
	while (ft_gnl(fd, &line, "\t\n\r\v"))
		ft_strdel(&line);
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

	pixels = malloc(pixel_count * 3);
	if (pixels == NULL)
		ft_error(__func__, __LINE__);
	fd = ft_fopen_read(filename);
	read(fd, pixels, cursor);
	read(fd, pixels, pixel_count * 3);
	ft_gnl(fd, &line, "\n");
	ft_strdel(&line);
	close(fd);
	return (pixels);
}

char	*load_texture(t_texture *tex)
{
	int	fd;
	int	header_bytes;

	if (tex->dir == NULL)
		return (NULL);
	if (DEBUG)
		ft_printf("Loading [%s] ... ", tex->dir);
	fd = ft_fopen_read(tex->dir);
	header_bytes = parse_header(fd, &tex->width, &tex->height);
	close(fd);
	if (DEBUG)
		ft_printf("%d x %d\n", tex->width, tex->height);
	return (read_pixel_data(tex->dir, header_bytes, tex->width * tex->height));
}

void	add_texture(char *name, t_data *app)
{
	t_texture	tex;

	if (!(tex.dir = ft_strjoin(TEX_DIR, name)))
		ft_error(__func__, __LINE__);
	tex.pixels = NULL;
	tex.f_texture = &sample;
	if (!(tex.name = ft_strdup(name)))
		ft_error(__func__, __LINE__);
	ft_lstpushnew(&app->lst_tex, &tex, sizeof(t_texture));
	if (DEBUG)
		ft_printf("Texture added : %s\n", name);
}

void	open_textures(t_data *app)
{
	DIR				*d;
	struct dirent	*dir;

	d = opendir(TEX_DIR);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (ft_strstr(dir->d_name, ".ppm"))
				add_texture(dir->d_name, app);
		}
		closedir(d);
	}
}
