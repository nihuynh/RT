/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pool_render.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 11:32:35 by nihuynh           #+#    #+#             */
/*   Updated: 2019/04/18 16:34:35 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "includes/libui.h"
#include "../libft/includes/libft.h"

/*
**	gcc -Wall -Werror -Wextra test_pool_render.c libui.a -I/Users/nihuynh/.brew/include/SDL2 -L/Users/nihuynh/.brew/lib -lSDL2 ../libft/libft.a
*/

static inline void
	putcolor(t_sdl *sdl, int color, int x, int y)
{
	uint8_t r;
	uint8_t g;
	uint8_t b;

	r = color >> 16;
	g = color >> 8;
	b = color;
	SDL_SetRenderDrawColor(sdl->renderer, r, g, b, 255);
	SDL_RenderDrawPoint(sdl->renderer, x, y);
}

void *thr_routine(void *arg)
{
	t_thr_pool	*pool;
	t_pxl		idx;
	int			task_id;
	int			res;
	pthread_mutex_t lock;

	pool = arg;
	while (42)
	{
		pthread_mutex_lock(&(pool->idx_lock));
			task_id = pool->pxl_idx;
			pool->pxl_idx += 1;
		pthread_mutex_unlock(&(pool->idx_lock));
		// if (task_id > pool->sdl->img.width * pool->sdl->img.height)
		if (task_id > 800 * 800)
		{
			pthread_mutex_lock(&(pool->idle_count_lock));
				pool->idle_count += 1;
				if (pool->idle_count == pool->thr_count)
					pthread_cond_signal(&(pool->render_done));
			pthread_cond_wait(&(pool->wait_sig), &(pool->idle_count_lock));
			pthread_mutex_unlock(&(pool->idle_count_lock));
		}
		idx.x = task_id / pool->sdl->img.width;
		idx.y = task_id % pool->sdl->img.width;
		res = pool->do_pxl(idx.x, idx.y, pool->prg_data);
		putcolor(pool->sdl, res, idx.x, idx.y);
		// pool->sdl->img.pixels[task_id] = res | C_MASK;
	}
	pthread_exit(NULL);
}

int init_pool(t_sdl *sdl, int (*do_pxl) (int, int, void*), void *prg_d, unsigned short thr_count)
{
	unsigned short	idx;
	int				sats;

	idx = -1;
	sats = 0;
	if (!(sdl->pool = ft_memalloc(sizeof(t_thr_pool))))
		ft_error(__func__, __LINE__);
	sdl->pool->idx_lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	sdl->pool->idle_count_lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	sdl->pool->wait_sig = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
	sdl->pool->render_done = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
	if (!(sdl->pool->threads = ft_memalloc(sizeof(pthread_t) * thr_count)))
		ft_error(__func__, __LINE__);
	sdl->pool->thr_count = thr_count;
	sdl->pool->sdl = sdl;
	sdl->pool->do_pxl = do_pxl;
	sdl->pool->prg_data = prg_d;
	while (++idx < thr_count && !sats)
	{
		sats = pthread_create(&sdl->pool->threads[idx], NULL,
								thr_routine, sdl->pool);
		pthread_detach(sdl->pool->threads[idx]);
	}
	if (idx != thr_count)
		ft_error(__func__, __LINE__);
	return (EXIT_SUCCESS);
}

int pool_render(t_thr_pool *pool)
{
	long	elapsed_time;
	pthread_mutex_t lock;

	if (pool->sdl->needs_render == false)
		return (EXIT_SUCCESS);
	elapsed_time = ft_curr_usec();
	pthread_mutex_lock(&lock);
	pthread_cond_wait(&pool->render_done, &lock);
	pthread_mutex_unlock(&lock);
	SDL_RenderPresent(pool->sdl->renderer);
	pool->sdl->needs_render = false;
	elapsed_time = ft_curr_usec() - elapsed_time;
	ft_printf("Frame took %f ms to render\n", (float)elapsed_time / 1000);
	return (EXIT_SUCCESS);
}

int destroy_pool(t_thr_pool *pool)
{
	if (pool)
	{
		pthread_mutex_lock(&(pool->idx_lock));
        pthread_mutex_destroy(&(pool->idx_lock));
		pthread_cond_destroy(&(pool->wait_sig));
		free(pool);
	}
	return (EXIT_SUCCESS);
}

int	process_pixel(int x, int y, void *arg)
{
	(void)x;
	(void)y;
	(void)arg;
	return (0xFF0000);
	// return (0x00FF00);
	// return (0x0000FF);
}

int	main(void)
{
	t_sdl		sdl;
	SDL_Event	event;
	int			quit = 0;

	init_sdl(&sdl, 800, 800);
	sdl.needs_render = true;
	init_pool(&sdl, &process_pixel, NULL, 16);
	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				quit = 1;
		}
		pool_render(sdl.pool);
		// render_sdl(&sdl, &process_pixel, NULL);
	}
	destroy_pool(sdl.pool);
	exit_sdl(&sdl);
	return (0);
}
