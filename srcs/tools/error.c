/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 09:53:33 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/20 18:00:15 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "libui.h"
#include "parse.h"

void
	free_app(t_data *app)
{
	free_lst(app);
	SDL_GL_DeleteContext(app->gui.gl_context);
	exit_sdl(&app->sdl);
}

void
	exit_safe(t_data *app)
{
	free_lst(app);
	SDL_GL_DeleteContext(app->gui.gl_context);
	exit_sdl(&app->sdl);
	exit(0);
}
