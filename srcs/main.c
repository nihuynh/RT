/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:12:24 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/27 11:37:05 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libui.h"
#include "libft.h"
#include <unistd.h>
#include <librt.h>

void	interactive(char *filename, int runmode)
{
	t_data		data;

	ft_bzero(&data, sizeof(t_data));
	data.arg = filename;
	if (reader(filename, &data) == EXIT_FAILURE)
		ft_error(__func__, __LINE__);
	if (runmode == RM_UNIT_TEST)
		return ;
	init(&data);
	init_mthr_sdl(&data.sdl, &process_pixel, &data);
	loop_sdl(&data.sdl, &data);
	exit_safe(&data);
}

#define RAD_TO_DEG(x) (x * M_INV_PI_F * 180)
t_matrix
	create_rotation_between_up_and_vec(t_vec3 direction)
{
	float polar;
	float azimuth;

	vec3_cartesian_to_spherical(direction, &azimuth, &polar);
	printf("azimuth: %.3f   polar: %.3f\n", RAD_TO_DEG(azimuth), RAD_TO_DEG(polar));
	polar = -polar;
//	azimuth = -azimuth - M_PI_F;
//	azimuth = azimuth - M_PI_F;
	printf("ajustement...\n");
//	polar = DEG_TO_RAD * -10;
	printf("azimuth: %.3f   polar: %.3f\n", RAD_TO_DEG(azimuth), RAD_TO_DEG(polar));
	// negative polar angle -> look up
	// positive polar angle -> look down
	return (set_rotation(polar, azimuth));
}

void  frisvad(t_vec3 n, t_vec3 *b1, t_vec3 *b2)
{
	if (n.z <  -0.9999999f) //  Handle  the  singularity
	{
		*b1 = (t_vec3){0.0f,  -1.0f, 0.0f};
		*b2 = (t_vec3){-1.0f,   0.0f, 0.0f};
		return;
	}
	const  float a = 1.0f/(1.0f + n.z);
	const  float b = -n.x * n.y * a;
	*b1 = (t_vec3){1.0f - n.x * n.x * a, b, -n.x};
	*b2 = (t_vec3){b, 1.0f - n.y * n.y * a, -n.y};

}
// TODO: We really need a full basis per object (and in scene file)
// We can do without but the basis will not be stable for small normal changes
// Try this on plane to see
int		main(int ac, char **av)
{
	int		options;
	int		mode;

	t_vec3 dir = (t_vec3) {0, 1, 0};
	vec3_normalize(&dir);
	vec3_print(&dir);
	t_matrix rotation;
	rotation = create_rotation_between_up_and_vec(dir);
	t_vec3 x_axis;
	t_vec3 z_axis;
	frisvad(dir, &x_axis, &z_axis);
	rotation.m[0][0] = x_axis.x;
	rotation.m[1][0] = x_axis.y;
	rotation.m[2][0] = x_axis.z;
	rotation.m[0][1] = dir.x;
	rotation.m[1][1] = dir.y;
	rotation.m[2][1] = dir.z;
	rotation.m[0][2] = z_axis.x;
	rotation.m[1][2] = z_axis.y;
	rotation.m[2][2] = z_axis.z;
	print_matrix(&rotation);
//	return 0;
	if (ac == 1)
	{
		ft_putendl(USAGE);
		return (-1);
	}
	if ((options = ft_options(ac, av, USAGE)) == -1)
		return (-1);
	if (ac == 2 || (ac > 2 && options != 0))
	{
		mode = (options & (1 << 19)) ? RM_UNIT_TEST : RM_NORMAL;
		interactive(av[1], mode);
	}
	while (options & (1 << 11))
		;
	return (0);
}
