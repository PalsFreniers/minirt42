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
	struct s_vec3		orientation;
	float				fov;
	bool				exist;
};

typedef struct s_scene
{
	struct s_ambient	ambient;
	struct s_camera		camera;
	struct s_object	**objects;
	size_t				capacity;
	size_t				len;
}						t_scene;

void					print_scene(struct s_scene scene);
bool					scene_append(struct s_scene *scene,
							struct s_object *obj);
void	free_scene(struct s_scene *scene);

#endif // SCENE_H
