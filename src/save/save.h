#ifndef SAVE_H
# define SAVE_H

# include <scene/scene.h>

bool	save_ambient_light(struct s_ambient *self, int fd);
bool	save_camera(struct s_camera *self, int fd);
bool	save_float(float f, int fd);
bool	save_color(union u_color c, int fd);
bool	save_vec3(struct s_vec3 vec, int fd);
bool	save_sphere(struct s_sphere *self, int fd);
bool	save_light(struct s_light *self, int fd);
bool	save_plane(struct s_plane *self, int fd);
bool	save_cylinder(struct s_cylinder *self, int fd);

#endif // SAVE_H
