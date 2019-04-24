/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fullscreen.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 11:58:45 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/19 12:05:48 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	render_fullscreen(t_sdl *sdl, t_img *img)
{
	int x;
	int y;

	y = -1;
	while(++y < img->height)
	{
		x = -1;
		while (++x < img->width)
			putcolor_sdl(sdl, img->pixels[(y * img->height) + x], x, y);
	}
}
