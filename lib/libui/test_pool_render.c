/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pool_render.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 11:32:35 by nihuynh           #+#    #+#             */
/*   Updated: 2019/04/24 16:12:54 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "includes/libui.h"
#include "../libft/includes/libft.h"

# define BATCH_SIZE 16
# define WIDTH 		800
# define HEIGHT		800

/*
**	gcc -Wall -Werror -Wextra test_pool_render.c libui.a -I/Users/nihuynh/.brew/include/SDL2 -L/Users/nihuynh/.brew/lib -lSDL2 ../libft/libft.a
*/

void
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


int
	do_batch(t_thr_pool *pool)
{
	int		task_id;
	int 	idx_batch;
	int 	idx;

	idx_batch = -1;
	pthread_mutex_lock(&pool->idx_lock);
	task_id = pool->pxl_idx;
	pool->pxl_idx += BATCH_SIZE;
	pthread_mutex_unlock(&pool->idx_lock);
	if (task_id >= WIDTH * HEIGHT)
		return (-1);
	while (++idx_batch < BATCH_SIZE)
	{
		idx = task_id + idx_batch;
		pool->sdl->img.pixels[idx] = pool->do_pxl(idx % WIDTH,
			idx / WIDTH, pool->prg_data) | C_MASK;
	}
	return (task_id);
}

void
	*thr_routine(void *arg)
{
	t_thr_pool	*pool;
	int			task_id;

	pool = arg;
	task_id = 0;
	while (42)
	{
		pthread_mutex_lock(&pool->wait_lock);
		while (!pool->sdl->needs_render && !pool->is_stopped)
			pthread_cond_wait(&pool->wait_sig, &pool->wait_lock);
		pthread_mutex_unlock(&pool->wait_lock);
		if (pool->is_stopped)
            pthread_exit(NULL);
		while (task_id >= 0)
			task_id = do_batch(pool);
		pthread_mutex_lock(&pool->idle_lock);
		pool->idle_count++;
		if (pool->idle_count == pool->thr_count)
			pthread_cond_signal(&pool->render_done);
		pthread_mutex_unlock(&pool->idle_lock);
	}
}

int
	init_pool(t_sdl *sdl, int (*do_pxl) (int, int, void*), void *prg_d, uint16_t thr_count)
{
	unsigned short	idx;
	int				sats;

	idx = -1;
	sats = 0;
	if (!(sdl->pool = ft_memalloc(sizeof(t_thr_pool))))
		ft_error(__func__, __LINE__);
	sdl->pool->wait_lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	sdl->pool->wait_sig = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
	sdl->pool->idx_lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	sdl->pool->idle_lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
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

int
	pool_render(t_thr_pool *pool)
{
	long	elapsed_time;

	if (pool->sdl->needs_render == false)
		return (EXIT_SUCCESS);
	elapsed_time = ft_curr_usec();
	pthread_mutex_lock(&pool->idx_lock);
	pool->pxl_idx = 0;
	pool->idle_count = 0;
	printf("Pool is started\n");
	pthread_cond_broadcast(&pool->wait_sig);
	while (pool->pxl_idx > WIDTH * HEIGHT - BATCH_SIZE)
		pthread_cond_wait(&pool->render_done, &pool->idx_lock);
	pthread_mutex_unlock(&pool->idx_lock);
	SDL_RenderPresent(pool->sdl->renderer);
	pool->sdl->needs_render = false;
	elapsed_time = ft_curr_usec() - elapsed_time;
	ft_printf("Frame took %f ms to render\n", (float)elapsed_time / 1000);
	return (EXIT_SUCCESS);
}

int destroy_pool(t_thr_pool *pool)
{
	pool->is_stopped = 1;
	pthread_cond_broadcast(&pool->wait_sig);
	SDL_Delay(100);
	if (pool)
	{
		if (pool->threads)
			free(pool->threads);
		free(pool);
	}
	return (EXIT_SUCCESS);
}

/*
** return (0x00FF00);
** return (0x0000FF);
*/

int
	process_pixel(int x, int y, void *arg)
{
	(void)x;
	(void)y;
	(void)arg;
	return (0xFF0000);
}

int
	main(void)
{
	t_sdl		sdl;
	SDL_Event	event;
	int			quit;

	quit = 0;
	init_sdl(&sdl, WIDTH, HEIGHT);
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
	// while (1)
	// 	;
	return (0);
}
