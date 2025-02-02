/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:17:56 by tdelage           #+#    #+#             */
/*   Updated: 2025/01/31 19:24:45 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <render/collision.h>

bool	sphere_collide(struct s_ray *ray, struct s_sphere *sphere,
		t_collision *coll)
{
	const float	radius = sphere->diameter / 2;
	float		determinant;
	t_vec3		ray_to_sphere;
	float		rtsp_norm_squarred;
	float		ray_dot_rtsp;

	ray_to_sphere = vec3_sub(sphere->base.position, ray->origin);
	ray_dot_rtsp = vec3_dot(ray->direction, ray_to_sphere);
	rtsp_norm_squarred = vec3_lenght_sq(ray_to_sphere);
	determinant = ray_dot_rtsp * ray_dot_rtsp - (rtsp_norm_squarred - radius
			* radius);
	if (determinant < 0)
		return (false);
	if (coll)
	{
		determinant = sqrtf(determinant);
		coll->dist = ray_dot_rtsp - determinant;
		if (coll->dist < 0.0f)
			coll->dist += 2 * determinant;
		coll->position = vec3_add(ray->origin, vec3_scal_mul(ray->direction,
					coll->dist));
		coll->normal = vec3_normalise(vec3_sub(coll->position,
					sphere->base.position));
		if (ray_dot_rtsp < determinant)
			coll->normal = vec3_scal_mul(coll->normal, -1.0f);
	}
	return (true);
}
