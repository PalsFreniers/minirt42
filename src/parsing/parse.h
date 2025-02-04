/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:23:01 by tdelage           #+#    #+#             */
/*   Updated: 2025/02/04 17:20:57 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <object/objects.h>
# include <scene/scene.h>
# include <stdbool.h>
# include <strings/dstring.h>

bool	parse_file(const char *path, struct s_scene *scene);
bool	parse_line(struct s_string line, struct s_scene *scene);
bool	parse_color(struct s_string rgb, union u_color *color);
bool	parse_float(struct s_string sratio, float *ratio);
bool	parse_position(struct s_string spos, struct s_vec3 *pos);
bool	parse_camera(struct s_string *p, size_t c, struct s_camera *cam);
bool	parse_ambient_light(struct s_string *p, size_t c, struct s_ambient *l);
bool	parse_range(struct s_string sratio, float *ratio, float up, float down);
bool	parse_ranged_vector(struct s_string r, struct s_vec3 *p, float u,
			float d);
bool	parse_light(struct s_string *parts, size_t count,
			struct s_scene *scene);
bool	parse_sphere(struct s_string *parts, size_t count,
			struct s_scene *scene);
bool	parse_plane(struct s_string *parts, size_t count,
			struct s_scene *scene);
bool	parse_cylinder(struct s_string *parts, size_t count,
			struct s_scene *scene);

void	camera_create_transform(struct s_camera *camera);

#endif // PARSE_H
