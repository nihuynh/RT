/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 03:32:43 by nihuynh           #+#    #+#             */
/*   Updated: 2019/04/24 12:12:28 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBUI_H
# define LIBUI_H

# include <SDL.h>
# include <stdbool.h>

# define THR_C		20
# define C_MASK		0xFF000000

typedef struct		s_pxl
{
	int				x;
	int				y;
}					t_pxl;

typedef struct s_data_thr	t_data_thr;
typedef struct s_thr_pool	t_thr_pool;

typedef struct		s_img
{
	uint32_t		*pixels;
	int				width;
	int				height;
}					t_img;


typedef struct		s_sdl
{
	bool			fullscreen;
	t_img			img;
	bool			needs_render;
	int				width_vp;
	int				height_vp;
	// mthr data
	int				thr_len;
	t_data_thr		*data_thr;
	// pool data
	t_thr_pool		*pool;
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	void			(*key_map)(int*, SDL_Keycode, void*, bool state);
	void			(*mouse_map)(SDL_Event*, void *);
	void			(*click_map)(SDL_Event *, void *);
	void			(*update)(void *arg);
	void			(*render_gui)(void *arg);
}					t_sdl;

struct				s_data_thr
{
	int				*data;
	int				idx;
	t_sdl			*sdl;
	int				(*do_pxl) (int, int, void*);
	void			*prg_data;
};

struct				s_thr_pool
{
	int				is_stopped;
	unsigned short	thr_count;
	pthread_mutex_t	wait_lock;
	pthread_cond_t	wait_sig;
	unsigned int	pxl_idx;
	pthread_mutex_t	idx_lock;
	pthread_mutex_t	idle_lock;
	unsigned short	idle_count;
	pthread_cond_t	render_done;
	t_sdl			*sdl;
	int				(*do_pxl) (int, int, void*);
	void			*prg_data;
	pthread_t		*threads;
};

/*
** SDL :
*/

void				error_sdl(t_sdl *sdl);
int					init_sdl(t_sdl *sdl, int width, int height);
void				exit_sdl(t_sdl *sdl);
void				render_sdl(t_sdl *sdl, int (*f) (int, int, void*), void *d);
void				loop_sdl(t_sdl *sdl, void *arg);
void				save_screenshot(t_sdl *sdl, char *arg);
void				init_mthr_sdl(t_sdl *sdl, int (*do_pxl)(int, int, void*),
									void *data);
void				render_mthr_sdl(t_sdl *sdl);
void				putcolor_sdl(t_sdl *sdl, int color, int x, int y);
void				render_fullscreen(t_sdl *sdl, t_img *img);

#endif
