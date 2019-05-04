/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_pool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 11:12:38 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/04 15:09:26 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include "libui.h"
#include "libft.h"

static inline int
	do_batch(t_thr_pool *pool)
{
	int	task_id;
	int	idx_batch;
	int	idx;

	idx_batch = -1;
	pthread_mutex_lock(&pool->idx_lock);
	task_id = pool->pxl_idx;
	pool->pxl_idx += BATCH_SIZE;
	pthread_mutex_unlock(&pool->idx_lock);
	if (task_id + BATCH_SIZE >= pool->limit)
		return (-1);
	while (++idx_batch < BATCH_SIZE)
	{
		idx = task_id + idx_batch;
		pool->sdl->img.pixels[idx] = pool->do_pxl(idx % pool->sdl->img.width,
			idx / pool->sdl->img.width, pool->prg_data) | C_MASK;
	}
	return (task_id);
}

static inline void
	*thr_fun(void *arg)
{
	t_thr_pool	*pool;
	int			task_id;

	pool = arg;
	task_id = -1;
	while (42)
	{
		pthread_mutex_lock(&pool->wait_lock);
		while (task_id < 0)
		{
			pthread_cond_wait(&pool->wait_sig, &pool->wait_lock);
			task_id = 0;
		}
		pthread_mutex_unlock(&pool->wait_lock);
		if (pool->is_stopped == 1)
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
	init_pool(t_sdl *sdl, int (*do_pxl) (int, int, void*), void *prg_d,
		uint16_t thr_count)
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
	if (!(sdl->pool->thrs = ft_memalloc(sizeof(pthread_t) * thr_count)))
		ft_error(__func__, __LINE__);
	sdl->pool->limit = sdl->img.width * sdl->img.height;
	sdl->pool->thr_count = thr_count;
	sdl->pool->sdl = sdl;
	sdl->pool->do_pxl = do_pxl;
	sdl->pool->prg_data = prg_d;
	while (++idx < thr_count && !sats)
	{
		sats = pthread_create(&sdl->pool->thrs[idx], NULL, thr_fun, sdl->pool);
		pthread_detach(sdl->pool->thrs[idx]);
	}
	return (EXIT_SUCCESS);
}

int
	pool_render(t_thr_pool *pool)
{
	long	elapsed_time;

	elapsed_time = ft_curr_usec();
	pthread_mutex_lock(&pool->idx_lock);
	pool->pxl_idx = 0;
	pthread_mutex_lock(&pool->idle_lock);
	pool->idle_count = 0;
	pthread_mutex_unlock(&pool->idle_lock);
	pthread_cond_broadcast(&pool->wait_sig);
	while (pool->pxl_idx + BATCH_SIZE <= pool->limit)
		pthread_cond_wait(&pool->render_done, &pool->idx_lock);
	pool->pxl_idx = 0;
	pthread_mutex_unlock(&pool->idx_lock);
	pool->sdl->needs_render = false;
	elapsed_time = ft_curr_usec() - elapsed_time;
	ft_printf("Frame took %f ms to render\n", (float)elapsed_time / 1000);
	return (EXIT_SUCCESS);
}

int
	destroy_pool(t_thr_pool *pool)
{
	pool->is_stopped = 1;
	// pthread_cond_broadcast(&pool->wait_sig);
	// SDL_Delay(100);
	// if (pool)
	// {
	// 	if (pool->thrs)
	// 		free(pool->thrs);
	// 	free(pool);
	// }
	return (EXIT_SUCCESS);
}
