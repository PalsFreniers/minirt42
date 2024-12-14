#ifndef SCENE_H
# define SCENE_H

# include <object/objects.h>
# include <stdbool.h>
# include <stddef.h>

struct					s_ambient
{
	float				ratio;
	union u_color		color;
	bool				exist;
};

struct					s_camera
{
	struct s_vec3		position;
	struct s_vec3		direction;
	t_mat3				transform;
	t_mat3				inverse_transform;
	float				fov;
	float				screen_to_camera_factor;
	bool				exist;
};

typedef struct s_scene
{
	struct s_ambient	ambient;
	struct s_camera		camera;
	struct s_object		**objects;
	size_t				capacity;
	size_t				len;
}						t_scene;

void					print_scene(struct s_scene *scene);
bool					scene_append(struct s_scene *scene,
							struct s_object *obj);
void					free_scene(struct s_scene *scene);

void					camera_create_transform(struct s_camera *camera);

#endif // SCENE_H
