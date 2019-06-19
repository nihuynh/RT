/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_anim_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 15:09:20 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/19 08:52:00 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "animate.h"

void	parse_orbit(void *parse, void *res)
{
	t_orbit		*orbit;
	char		*center_obj;
	t_parse_txt	*scene_file;

	orbit = res;
	scene_file = parse;
	if (!(center_obj = get_args_key_require(scene_file, "center_obj(")))
	{
		err_set(scene_file, __func__, __LINE__, __FILE__);
		err_exit(ERR_UNKNWD_OBJ_A, scene_file);
	}
	if (!(orbit->obj_center = ft_lstgetelt(scene_file->app->scene.lst_obj,
		&obj_cmp_key, center_obj)))
	{
		err_set(scene_file, __func__, __LINE__, __FILE__);
		err_exit(ERR_UNKNWD_OBJ_A, scene_file);
	}
	orbit->axis = parse_vector("axis(", scene_file);
	orbit->deg = parse_fval("deg(", scene_file);
}

void	parse_translate(void *parse, void *res)
{
	t_translate		*translate;
	t_parse_txt	*scene_file;

	translate = res;
	scene_file = parse;
	translate->dir = parse_vector("dir(", scene_file);
	translate->speed = parse_fval("speed(", scene_file);
}

void	parse_rotate(void *parse, void *res)
{
	t_rotate		*rotate;
	t_parse_txt	*scene_file;

	rotate = res;
	scene_file = parse;
	rotate->axis = parse_vector("axis(", scene_file);
	rotate->deg = parse_fval("deg(", scene_file);
}
