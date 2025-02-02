/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 23:19:03 by tdelage           #+#    #+#             */
/*   Updated: 2025/01/31 22:14:54 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLISION_H
# define COLLISION_H

# include <render/ray.h>
# include <mlx/mmlx.h>
# include <stdbool.h>

typedef struct s_matrices
{
	t_mat3			rotation;
	t_vec3			translation;
}					t_matrices;

typedef struct s_collision
{
	float			dist;
	t_vec3			position;
	t_vec3			normal;
	t_ray			ray;
	struct s_object	*object;
}					t_collision;

bool				test_collision(struct s_object *object, struct s_ray *ray,
						t_collision *collision);
bool				sphere_collide(struct s_ray *ray,
						struct s_sphere *sphere, t_collision *collision);
bool				plane_collide(struct s_ray *ray,
						struct s_plane *plane, t_collision *coll);
bool				cylinder_collide(struct s_ray *ray,
						struct s_cylinder *cylinder, t_collision *coll);

#endif // COLLISION_H
