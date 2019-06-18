/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_anim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 20:54:08 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/18 04:16:38 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include "libft.h"
#include "export.h"

#include <stdio.h>
#include <locale.h>
#include <fcntl.h>
#include <unistd.h>

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

void	export_anim_cam(int fd, void *res)
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

void
	export_animation(int fd, t_data *app)
{
	write(fd, "animation\n{\n", 12);
	if (app->cam.anim)
		export_anim_cam(fd, app->cam.anim);
	if (app->scene.lst_anim)
		ft_lstiter_arg(fd, app->scene.lst_anim, &export_anim);
	write(fd, "}\n", 2);
}