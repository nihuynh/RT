/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 21:59:27 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/14 22:04:21 by nihuynh          ###   ########.fr       */
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

# define DEBUG			0
# define MAC			MACB

/*
** User def :
*/

# define T_STEP			5
# define Z_STEP			1
# define A_STEP			5 * DEG_TO_RAD
# define MOUSE_SCALING	0.005f

/*
** UI :
*/

# define RENDER_STATIC	1
# define SHOW_DEMO		0
# define RENDER_SCALE	0.7

/*
** Static def :
*/

# define DEV			0
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
