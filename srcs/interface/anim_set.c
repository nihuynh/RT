/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:36:18 by sklepper          #+#    #+#             */
/*   Updated: 2019/07/18 17:14:32 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animate.h"
#include "stdlib.h"
#include "libft.h"
#include "t_data.h"

static inline void
	anim_set_translate(t_anim *anim)
{
	t_translate *translate;

	if (!(translate = malloc(sizeof(t_translate))))
		ft_error(__func__, __LINE__);
	ft_bzero(translate, sizeof(t_translate));
	anim->res = translate;
	anim->anim_obj = &anim_translate;
	anim->ui_anim = &ui_translate;
	anim->export = &export_translate;
	anim->parse = &parse_translate;
}

static inline void
	anim_set_orbit(t_anim *anim)
{
	t_orbit	*orbit;

	if (!(orbit = malloc(sizeof(t_orbit))))
		ft_error(__func__, __LINE__);
	ft_bzero(orbit, sizeof(t_orbit));
	anim->res = orbit;
	anim->anim_obj = &anim_orbit;
	anim->ui_anim = &ui_orbit;
	anim->export = &export_orbit;
	anim->parse = &parse_orbit;
}

static inline void
	anim_set_rotate(t_anim *anim)
{
	t_rotate	*rotate;

	if (!(rotate = malloc(sizeof(t_rotate))))
		ft_error(__func__, __LINE__);
	ft_bzero(rotate, sizeof(t_rotate));
	anim->res = rotate;
	anim->anim_obj = &anim_rotate;
	anim->ui_anim = &ui_rotate;
	anim->export = &export_rotate;
	anim->parse = &parse_rotate;
}

static inline void
	anim_reset(t_anim *anim)
{
	anim->type = 0;
	anim->anim_obj = NULL;
	anim->ui_anim = NULL;
	anim->export = NULL;
	anim->parse = NULL;
}

void
	anim_set(t_anim *anim, int type)
{
	if (anim->type == type)
		return ;
	anim_free(anim);
	if (type == 0)
		anim_reset(anim);
	else if (type == 1)
		anim_set_translate(anim);
	else if (type == 2 || type == 3)
		anim_set_orbit(anim);
	else if (type == 4)
		anim_set_rotate(anim);
	anim->type = type;
}
