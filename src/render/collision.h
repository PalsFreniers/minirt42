/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 23:19:03 by tdelage           #+#    #+#             */
/*   Updated: 2024/12/17 16:52:26 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLISION_H
# define COLLISION_H

# include <math/ray.h>
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
	struct s_vec3	position;
	struct s_vec3	normal;
	struct s_object	*object;
}					t_collision;

float				ft_abs(float val);

// int					next_object(struct s_object **objects, int i);

bool				test_collision(struct s_mlx *mlx, struct s_object *object,
						struct s_ray ray, t_collision *collision);

bool				sphere_collide_function(struct s_ray ray,
						struct s_sphere *sphere, t_collision *collision,
						t_matrices *mats);
bool				plane_collide_function(struct s_ray ray,
						struct s_plane *plane, t_collision *coll,
						t_matrices *m);

bool				lit_collision(struct s_mlx *mlx, t_collision collision);

#endif // COLLISION_H
