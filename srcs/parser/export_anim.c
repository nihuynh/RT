/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_anim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 20:54:08 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/16 04:07:02 by sklepper         ###   ########.fr       */
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

void
	export_animation(int fd, t_list *lst_anim)
{
	write(fd, "animation\n{\n", 12);
	if (lst_anim)
		ft_lstiter_arg(fd, lst_anim, &export_anim);
	write(fd, "}\n", 2);
}
