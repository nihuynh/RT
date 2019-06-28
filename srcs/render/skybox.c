#include "render.h"
#include "librt.h"

t_color get_sky_color(t_scene scene, t_settings settings, t_ray ray)
{
	float azimuth;
	float polar;

	if (settings.skybox)
	{
		vec3_cartesian_to_spherical(ray.dir, &azimuth, &polar);
		azimuth = remap_to_0_to_1(azimuth / M_PI_F);
		polar /= M_PI_F;
		return sample(NULL, scene.skybox, (t_vec3){1 - azimuth, polar, 0});
	}
	else
		return settings.back_color;
}
