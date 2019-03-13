/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archives.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 22:01:52 by nihuynh           #+#    #+#             */
/*   Updated: 2018/12/19 22:02:30 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void				bench(char *filename, unsigned int frame_count)
{
	t_data			data;
	unsigned int	frame;

	frame = frame_count;
	ft_bzero(&data, sizeof(t_data));
	reader(filename, &data);
	init_sdl(&data.sdl, WIDTH, HEIGHT);
	init_render(&data);
	init_mthr_sdl(&data.sdl, &process_pixel, &data);
	while (--frame > 0)
	{
		render_mthr_sdl(&data.sdl);
		data.sdl.isrender = 0;
		while (SDL_PollEvent(&data.sdl.event))
		{
			if (data.sdl.event.type == SDL_QUIT)
				frame = 0;
		}
	}
	exit_safe(&data);
}

static inline void	matrix_math(float datcos, float datsin, t_vec3 *axis, \
								t_matrix *matrix)
{
	matrix->m[0][0] = datcos + axis->x * axis->x * (1 - datcos);
	matrix->m[0][1] = axis->x * axis->y * (1 - datcos) - axis->z * datsin;
	matrix->m[0][2] = axis->x * axis->z * (1 - datcos) + axis->y * datsin;
	matrix->m[1][0] = axis->y * axis->x * (1 - datcos) + axis->z * datsin;
	matrix->m[1][1] = datcos + axis->y * axis->y * (1 - datcos);
	matrix->m[1][2] = axis->y * axis->z * (1 - datcos) - axis->x * datsin;
	matrix->m[2][0] = axis->z * axis->x * (1 - datcos) - axis->y * datsin;
	matrix->m[2][1] = axis->z * axis->y * (1 - datcos) + axis->x * datsin;
	matrix->m[2][2] = datcos + axis->z * axis->z * (1 - datcos);
}

void				vec3_matrix_camera(t_matrix *matrix, t_cam *cam)
{
	t_vec3	axis;
	float	datcos;
	float	datsin;
	t_vec3	toby[2];

	vec3_find(&(t_pt3){0, 0, 0}, &(t_pt3){0, 0, -1}, &toby[0]);
	vec3_normalize(&toby[0]);
	vec3_print(&toby[0]);
	vec3_find(&cam->pos, (t_pt3*)&cam->dir, &toby[1]);
	vec3_normalize(&toby[1]);
	vec3_print(&toby[1]);
	datcos = vec3_dot(&toby[0], &toby[1]);
	vec3_cross(&toby[0], &toby[1], &axis);
	datsin = vec3_mag(&axis);
	matrix_math(datcos, datsin, &axis, matrix);
	print_matrix(matrix);
}
