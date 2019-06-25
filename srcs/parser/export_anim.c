/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_anim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 20:54:08 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/26 01:25:55 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animate.h"
#include <stdio.h>
#include <unistd.h>
#include "t_data.h"

static inline const char
	*get_anim_str(int type)
{
	const char	*motion_strs[] = {
		"none", "translate", "orbit", "rotate"
	};

	return (motion_strs[type]);
}

static inline void
	export_anim(int fd, t_list *node)
{
	t_anim	*anim;

	anim = node->content;
	dprintf(fd, "\tobject(%s)\n\t{\n", anim->obj->name);
	while (anim)
	{
		dprintf(fd, "\t\tmotion(%s)\n\t\t{\n", get_anim_str(anim->type));
		if (anim->res)
			anim->export(fd, anim);
		write(fd, "\t\t}\n", 4);
		anim = anim->next;
	}
	write(fd, "\t}\n", 3);
}

static inline void
	export_anim_cam(int fd, void *res)
{
	t_anim	*anim;

	anim = res;
	dprintf(fd, "\tobject(camera)\n\t{\n");
	while (anim)
	{
		dprintf(fd, "\t\tmotion(%s)\n\t\t{\n", get_anim_str(anim->type));
		if (anim->res)
			anim->export(fd, anim);
		write(fd, "\t\t}\n", 4);
		anim = anim->next;
	}
	write(fd, "\t}\n", 3);
}

static inline void
	export_anim_light(int fd, t_list *node)
{
	t_anim	*anim;

	anim = node->content;
	dprintf(fd, "\tobject(%s)\n\t{\n", anim->light->name);
	while (anim)
	{
		dprintf(fd, "\t\tmotion(%s)\n\t\t{\n", get_anim_str(anim->type));
		if (anim->res)
			anim->export(fd, anim);
		write(fd, "\t\t}\n", 4);
		anim = anim->next;
	}
	write(fd, "\t}\n", 3);
}

void
	export_animation(int fd, t_data *app)
{
	write(fd, "animation\n{\n", 12);
	if (app->cam.anim)
		export_anim_cam(fd, app->cam.anim);
	if (app->scene.lst_anim)
		ft_lstiter_arg(fd, app->scene.lst_anim, &export_anim);
	if (app->scene.lst_anim_light)
		ft_lstiter_arg(fd, app->scene.lst_anim_light, &export_anim_light);
	write(fd, "}\n", 2);
}
