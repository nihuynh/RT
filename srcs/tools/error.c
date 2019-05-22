/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 09:53:33 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/22 09:30:15 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void
	free_app(t_data *app)
{
	free_lst(app);
	SDL_GL_DeleteContext(app->gui.gl_context);
	exit_sdl(app->sdl);
}

void
	exit_safe(t_data *app)
{
	free_app(app);
	exit(0);
}
