/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 03:32:43 by nihuynh           #+#    #+#             */
/*   Updated: 2019/03/18 11:39:29 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBUI_H
# define LIBUI_H

# include <SDL.h>
# include <stdbool.h>
# include "color.h"

# define THR_C 20

typedef struct		s_pxl
{
	int				x;
	int				y;
}					t_pxl;

typedef struct s_data_thr	t_data_thr;

typedef struct		s_sdl
{
	bool			isrender;
	int				width_vp;
	int				height_vp;
	// mthr render data
	int				thr_len;
	t_data_thr		*data_thr;
	// pool render data
	int				sample_scale;
	int				pxl_idx;
	int				offset;
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	void			(*key_map)(int*, SDL_Keycode, void*, bool state);
	void			(*mouse_map)(SDL_Event*, void *arg);
	void			(*update)(void *arg);
}					t_sdl;

struct				s_data_thr
{
	int				*data;
	int				idx;
	t_sdl			*sdl;
	int				(*do_pxl) (int, int, void*);
	void			*prg_data;
};

/*
** Color :
*/

void				color_mult(t_color *color, t_color *mult);
void				color_scalar(t_color *color, float k);
void				color_add(t_color *color, t_color *add);
void				color_sub(t_color *color, t_color *sub);
void				color_max(t_color *col1, t_color *col2);
void				itocolor(t_color *res, int color);
int					colortoi(t_color *color);
/*
** SDL :
*/

void				putcolor_sdl(t_sdl *sdl, int color, int x, int y);
void				putpixel_sdl(t_sdl *sdl, t_color col, int x, int y);
void				error_sdl(t_sdl *sdl);
int					init_sdl(t_sdl *sdl, int width, int height);
void				exit_sdl(t_sdl *sdl);
void				render_sdl(t_sdl *sdl, int (*f) (int, int, void*), void *d);
void				loop_sdl(t_sdl *sdl, void *arg);
void				save_screenshot(t_sdl *sdl, char *arg);
void				init_mthr_sdl(t_sdl *sdl, int (*do_pxl)(int, int, void*),
									void *data);
void				render_mthr_sdl(t_sdl *sdl);
#endif
