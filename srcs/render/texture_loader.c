/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 15:32:28 by tdarchiv          #+#    #+#             */
/*   Updated: 2019/06/14 18:28:55 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <SDL_image.h>
#include "rtstruct.h"
#include "config.h"
#include "ftio.h"
#include "ftstring.h"
#include "rt.h"

void	load_texture(t_texture *tex)
{
	SDL_Surface	*surface;

	if (tex->dir == NULL)
		return ;
	if (DEBUG)
		ft_printf("Loading [%s] ... ", tex->name);
	surface = IMG_Load(tex->dir);
	if (surface == NULL)
	{
		ft_printf("%s\n", SDL_GetError());
		ft_error(__PRETTY_FUNCTION__, __LINE__);
	}
	tex->width = surface->w;
	tex->height = surface->h;
	tex->bpp = surface->format->BytesPerPixel;
	tex->pixels = malloc(tex->width * tex->height * tex->bpp);
	if (tex->pixels == NULL)
		ft_error(__func__, __LINE__);
	memcpy(tex->pixels, surface->pixels, tex->width * tex->height * tex->bpp);
	SDL_FreeSurface(surface);
	if (DEBUG)
		ft_printf("%d x %d\n", tex->width, tex->height);
}

void	add_texture(char *name, t_data *app, char *abs_path)
{
	t_texture	tex;

	if (!(tex.dir = ft_strjoin(abs_path, name)))
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
	char			*abs_path;

	abs_path = ft_strjoin(app->option.path, TEX_DIR);
	d = opendir(abs_path);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (ft_strstr(dir->d_name, ".ppm") ||
				ft_strstr(dir->d_name, ".png") ||
				ft_strstr(dir->d_name, ".jpg") ||
				ft_strstr(dir->d_name, ".jpeg"))
				add_texture(dir->d_name, app, abs_path);
		}
		closedir(d);
	}
	ft_strdel(&abs_path);
}
