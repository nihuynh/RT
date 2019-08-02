/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 03:32:43 by nihuynh           #+#    #+#             */
/*   Updated: 2019/07/25 13:43:18 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBUI_H
# define LIBUI_H

# include <SDL.h>
# include <stdbool.h>
# include <pthread.h>

# define THR_C			10
# define BATCH_SIZE		16
# define C_MASK			0xFF000000
# define P_TIME_LEN		80
# define GUI_FPS		60

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

typedef struct s_sdl	t_sdl;

struct				s_sdl
{
	t_img			img;
	float			progress_sub_sample;
	int				sub_sample;
	bool			needs_render;
	bool			partial_render;
	bool			fullscreen;
	bool			layout;
	int				width_vp;
	int				height_vp;
	int				thr_len;
	t_data_thr		*data_thr;
	SDL_Window		*win;
	void			(*key_map)(int*, SDL_Keycode, void*, bool state);
	void			(*mouse_map)(SDL_Event*, void *);
	void			(*click_map)(SDL_Event *, void *);
	void			(*update)(void *arg);
	void			(*render_gui)(void *arg);
	void			(*prep_render)(t_sdl *sdl);
	bool			sepia;
	bool			grayscale;
	bool			cartoon;
	bool			negative;
	bool			sub_s;
	float			render_time[P_TIME_LEN];
	float			gui_time[GUI_FPS];
};

struct				s_data_thr
{
	uint32_t		*pixels;
	int				idx;
	t_sdl			*sdl;
	int				(*do_pxl) (int, int, void*);
	void			*prg_data;
};

struct				s_thr_pool
{
	int				is_stopped;
	short			thr_count;
	pthread_mutex_t	wait_lock;
	pthread_cond_t	wait_sig;
	int				pxl_idx;
	int				limit;
	pthread_mutex_t	idx_lock;
	pthread_mutex_t	idle_lock;
	short			idle_count;
	pthread_cond_t	render_done;
	t_sdl			*sdl;
	int				(*do_pxl) (int, int, void*);
	void			*prg_data;
	pthread_t		*thrs;
};

/*
** SDL :
*/

void				error_sdl(t_sdl *sdl);
t_sdl				*init_sdl(int width, int height);
void				exit_sdl(t_sdl *sdl);
void				render_sdl(t_sdl *sdl, int (*f) (int, int, void*), void *d);
void				loop_sdl(t_sdl *sdl, void *arg);
void				save_screenshot(t_sdl *sdl, char *arg);
void				init_mthr_sdl(t_sdl *sdl, int (*do_pxl)(int, int, void*),
									void *data, void (*prep_render)(t_sdl*));
void				render_mthr_sdl(t_sdl *sdl);
void				apply_simple_filter(t_sdl *sdl, uint32_t (*fun) (uint32_t));

void				push_render_time(t_sdl *sdl, float time_frame_ms);
void				push_gui_time(t_sdl *sdl, long new_frame);

void				mthr_task(t_data_thr *data_thr, void *(*func)(void *));
/*
** Pool Render :
*/

int					init_pool(t_sdl *sdl, int (*do_pxl) (int, int, void*),
	void *prg_d, uint16_t thr_count);
int					pool_render(t_thr_pool *pool);
int					destroy_pool(t_thr_pool *pool);

#endif
