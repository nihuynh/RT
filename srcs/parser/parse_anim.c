/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_anim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 22:51:37 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/19 02:00:10 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "interface.h"
#include "libft.h"

int		get_motion_type(char *key)
{
	int			type;
	const char	*motion_str[] = {
		"none", "translate", "orbit", "rotate"
	};

	type = 0;
	while (type < 4)
	{
		if (ft_strncmp(key, motion_str[type], ft_strlen(motion_str[type])) == 0)
			return (type);
		type++;
	}
	return (-1);
}

void	parse_motion(t_parse_txt *scene_file, t_anim *anim)
{
	char	*motion;
	int		type;

	while ((motion = parse_str(scene_file, "motion(")))
	{
		if ((type = get_motion_type(motion)) == -1)
		{
			err_set(scene_file, __func__, __LINE__, __FILE__);
			err_exit(ERR_UNKNWD_MOTION, scene_file);
		}
		check_opening_bracket(scene_file);
		if (anim->res)
		{
			anim_add_another(anim);
			anim = anim->next;
		}
		anim_set(anim, type);
		if (anim->parse)
			anim->parse(scene_file, anim->res);
		check_closing_bracket(scene_file);
	}
}

void	parse_anim_specials(t_parse_txt *scene_file, char *line)
{
	t_light	*light;
	t_list	*lst;

	if (ft_strncmp(line, "camera", 5) == 0 && scene_file->app->cam.anim == NULL)
	{
		anim_add_camera(&scene_file->app->cam);
		parse_motion(scene_file, scene_file->app->cam.anim);
		check_closing_bracket(scene_file);
	}
	else if ((light = ft_lstgetelt(scene_file->app->scene.lst_light,
		&light_cmp_key, line)))
	{
		anim_add_light(scene_file->app, light);
		lst = ft_lstlast(scene_file->app->scene.lst_anim_light);
		parse_motion(scene_file, lst->content);
	}
	else
	{
		err_set(scene_file, __func__, __LINE__, __FILE__);
		err_exit(ERR_UNKNWD_OBJ_A, scene_file);
	}
}

void	parse_anim_extend(t_parse_txt *scene_file, char *line)
{
	t_obj	*obj;
	t_list	*lst;

	check_opening_bracket(scene_file);
	if (!(obj = ft_lstgetelt(scene_file->app->scene.lst_obj,
		&obj_cmp_key, line)))
		parse_anim_specials(scene_file, line);
	else
	{
		anim_add(scene_file->app, obj);
		lst = ft_lstlast(scene_file->app->scene.lst_anim);
		parse_motion(scene_file, lst->content);
		check_closing_bracket(scene_file);
	}
}

void	parse_anim(t_parse_txt *scene_file)
{
	char	*line;

	scene_file->app->scene.lst_anim = NULL;
	scene_file->line_idx++;
	check_opening_bracket(scene_file);
	while (scene_file->line_idx < scene_file->line_max - 1)
	{
		if (ft_strrchr(get_curr_line(scene_file), '}') != NULL)
			break ;
		if ((line = get_args_key_require(scene_file, "object(")))
			parse_anim_extend(scene_file, line);
		else
		{
			err_set(scene_file, __func__, __LINE__, __FILE__);
			err_exit(ERR_UNKNWD_OBJ_A, scene_file);
		}
	}
	check_closing_bracket(scene_file);
}
