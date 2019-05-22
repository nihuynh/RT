/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 15:32:58 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/22 23:05:40 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	push_render_time(t_sdl *sdl, float time_frame_ms)
{
	int idx;

	idx = -1;
	while (++idx < P_TIME_LEN)
		sdl->render_time[idx] = sdl->render_time[idx + 1];
	sdl->render_time[idx] = time_frame_ms;
}

void	push_gui_time(t_sdl *sdl, long new_frame)
{
	int i;

	i = -1;
	while (++i < GUI_FPS)
		sdl->gui_time[i] = sdl->gui_time[i + 1];
	sdl->gui_time[i] = (float) (1000000 / new_frame);
}
