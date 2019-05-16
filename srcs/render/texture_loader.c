/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 15:32:28 by tdarchiv          #+#    #+#             */
/*   Updated: 2019/05/16 15:39:45 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
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
	while (ft_gnl(fd, &line, "\t\n\r\v"))
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

#include "rt.h"
#include <dirent.h>
#include "libft.h"

void	add_texture(char *name, t_data *app)
{
	char		*dir;
	t_texture	tex;

	if (!(dir = ft_strjoin("./resources/textures/", name)))
		ft_error(__func__, __LINE__);
	tex.pixels = load_texture(dir, &tex.width, &tex.height);
	tex.f_texture = &sample;
	if(!(tex.name = ft_strdup(name)))
		ft_error(__func__, __LINE__);
	ft_lstpushnew(&app->lst_tex, &tex, sizeof(t_texture));
	ft_printf("Texture loaded : %s\n", name);
	free(dir);
}

void	open_textures(t_data *app)
{
	DIR *d;
	struct dirent *dir;

	(void)app;
	d = opendir("./resources/textures");
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
