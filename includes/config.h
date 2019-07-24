/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 21:59:27 by nihuynh           #+#    #+#             */
/*   Updated: 2019/07/02 03:29:10 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

/*
** Definition for the RT :
** Config :
*/

# define BACK_COLOR		0x000000
# define FOV			40.0f
# define DEPTH_MAX		2
# define SUB_SAMPLE		8

# define DEBUG			0
# define MAC			MACB
# define KEYMAP_PATH	"resources/layout.jpg"
# define TEX_DIR		"resources/textures/"
# define MAT_LST_DIR	"resources/materialList.csv"
# define SCENE_DIR		"scenes/"
# define NEW_SCENE		"resources/new_scene.rt"

/*
** Usage :
*/

# define USAGE "Usage : ./RT <scene.rt> [options]\nOptions : hlt"

/*
** User def :
*/

# define T_STEP			5.0f
# define A_STEP			5 * DEG_TO_RAD
# define MOUSE_SCALING	0.005f

/*
** UI :
*/

# define RENDER_SCALE	0.75
# define MENUBAR_HEIGHT 18

/*
** Static def :
*/

# define MACB			1
# define IMAC			2
# define IMAC4K			3

/*
** Automatic parameters :
*/

# if (MAC == MACB)
#  define WIDTH			1680
#  define HEIGHT		1000
# elif (MAC == IMAC)
#  define WIDTH			2560
#  define HEIGHT		1400
# elif (MAC == IMAC4K)
#  define WIDTH			3200
#  define HEIGHT		1800
# else
#  define WIDTH			840
#  define HEIGHT		500
# endif

#endif
