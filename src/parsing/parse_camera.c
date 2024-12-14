#include "strings/dstring.h"
#include <logger/logger.h>
#include <parsing/obey.h>
#include <parsing/parse.h>
#include <ui/window.h>
#include <math.h>

/**
 * ray_cam is expressed in camera coordinates.
 * ray_world is the same ray, expressed in world coordinates.
 * 
 * ray_world = (camera->transform * ray_cam) + camera->position
 * 
 * camera->transform (T) is made from camera->direction. it cannot be created if camera is pointed to the top or bottom.
 * 
 * ray_world = (
 * 		rwx,
 * 		rwy,
 * 		rwz)
 * 
 * T = (
 * 		m00	m01	m02,
 * 		m10	m11	m12,
 * 		m20	m21	m22)
 * 
 * ray_cam = (
 * 		rcx,
 * 		rcy
 * 		rcz)
 * 
 * T * ray_cam = (
 * 		m00 * rcx + m01 * rcy + m02 * rcz,
 * 		m10 * rcx + m11 * rcy + m12 * rcz,
 * 		m20 * rcx + m21 * rcy + m22 * rcz)
 * 
 * If ray_cam = (0, 0, 1), then T * ray_cam = camera->direction.
 * T * (0, 0, 1) = (
 * 		m00 * 0 + m01 * 0 + m02 * 1,
 * 		m10 * 0 + m11 * 0 + m12 * 1,
 * 		m20 * 0 + m21 * 0 + m22 * 1)
 * 		= (m02, m12, m22) = direction
 * camera->direction is the camera's depth, it's Z vector cZ.
 * So we can deduce:
 * T = (
 * 		cXx cYx cZx,
 * 		cXy cYy cZy,
 * 		cXz cYz cZz)
 * cX will always by parallel with the ground. if cZ isn't perpendicular to the ground, it can be found.
 * cY can be deduced from cX and cZ.
 * 
 */
void	camera_create_transform(struct s_camera *camera)
{
	t_vec3	t_x;
	t_vec3	t_y;

	t_x = vec3_cross_prod(
		vec3_normalise(vec3_new(camera->direction.x, camera->direction.y, 0)),
		vec3_new(0, 0, 1));		// CAREFUL, THIS CAN BREAK
	t_y = vec3_cross_prod(camera->direction, t_x);
	// camera->transform.m00 = t_x.x;
	// camera->transform.m01 = t_y.x;
	// camera->transform.m02 = camera->direction.x;
	// camera->transform.m10 = t_x.y;
	// camera->transform.m11 = t_y.y;
	// camera->transform.m12 = camera->direction.y;
	// camera->transform.m20 = t_x.z;
	// camera->transform.m21 = t_y.z;
	// camera->transform.m22 = camera->direction.z;
	camera->transform.m00 = -t_x.x;
	camera->transform.m01 = -t_x.y;
	camera->transform.m02 = -t_x.z;
	camera->transform.m10 = -t_y.x;
	camera->transform.m11 = -t_y.y;
	camera->transform.m12 = -t_y.z;
	camera->transform.m20 = camera->direction.x;
	camera->transform.m21 = camera->direction.y;
	camera->transform.m22 = camera->direction.z;
}

// #include <stdio.h>	// 
static bool	parse_camera_impl(struct s_camera *camera, struct s_string *parts)
{
	if (!parse_position(parts[1], &(camera->position)))
		return (false);
	if (!parse_ranged_vector(parts[2], &(camera->direction), 1, -1))
		return (false);
	if (!parse_range(parts[3], &(camera->fov), 180, 0))
		return (false);
	camera_create_transform(camera);
	// printf("Camera transform:\n");
	// printf("/% .3f % .3f % .3f\\\n", camera->transform.m00, camera->transform.m01, camera->transform.m02);
	// printf("|% .3f % .3f % .3f|\n", camera->transform.m10, camera->transform.m11, camera->transform.m12);
	// printf("\\% .3f % .3f % .3f/\n", camera->transform.m20, camera->transform.m21, camera->transform.m22);
	camera->screen_to_camera_factor = (2 * tanf(camera->fov / 2)) / WIN_WIDTH;
	return (true);
}

bool	parse_camera(struct s_string *parts, size_t count,
		struct s_camera *camera)
{
	if (camera->exist)
	{
		logger_error("only one camera is able to exist at one time");
		return (false);
	}
	if (count != 4)
	{
		logger_error("unable to parse camera");
		return (false);
	}
	if (!parse_camera_impl(camera, parts))
		return (false);
	camera->exist = true;
	return (true);
}
