/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 23:21:44 by maamine           #+#    #+#             */
/*   Updated: 2024/12/17 23:37:25 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <mlx/mmlx.h>
# include <math/la.h>

t_vec3	map_vec3(t_vec3 vec, t_vec3 translation, t_mat3 transform);
t_vec3	unmap_vec3(t_vec3 vec, t_vec3 translation, t_mat3 inverse_transform);
void	map_scene(struct s_scene *scene, t_vec3 translation, t_mat3 transform);

#include <stdio.h>	//
void	printf_vec3(t_vec3 vec);	// 
void	printf_obj_type(struct s_object *obj);	// 
void	printf_mat3(t_mat3 mat);	// 

extern bool	g_debug_show_grid;

#endif // MINIRT_H
