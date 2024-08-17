#ifndef PARSE_H
# define PARSE_H

# include <object/objects.h>
# include <scene/scene.h>
# include <stdbool.h>
# include <strings/dstring.h>

bool	parse_file(const char *path, struct s_scene *scene, const char *prog);
bool	parse_line(struct s_string line, struct s_scene *scene);
bool	parse_color(struct s_string rgb, union u_color *color);
bool	parse_position(struct s_string spos, struct s_vec3 *pos);
bool	parse_camera(struct s_string *p, size_t c, struct s_camera *cam);
bool	parse_ambient_light(struct s_string *p, size_t c, struct s_ambient *l);
bool	parse_range(struct s_string sratio, float *ratio, float up, float down);
bool	parse_ranged_vector(struct s_string r, struct s_vec3 *p, float u,
			float d);

#endif // PARSE_H
