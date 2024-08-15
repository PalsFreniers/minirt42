#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdint.h>

typedef struct s_vec3
{
	float				x;
	float				y;
	float				z;
}						t_vec3;

typedef union u_color
{
	uint32_t			rgb;
	struct
	{
		uint8_t			r;
		uint8_t			g;
		uint8_t			b;
	};
}						t_color;

struct					s_ambient
{
	float				ratio;
	union u_color		color;
};

struct					s_camera
{
	struct s_vec3		position;
	struct s_vec3		orientation;
	int					fov;
};

enum					e_object_type
{
	OBJ_LIGHT,
};

struct					s_object
{
	int					type;
};

struct					s_light
{
	int					type;
	struct s_vec3		position;
	float				ratio;
	union u_color		color;
};

struct					s_sphere
{
	int					type;
	struct s_vec3		position;
	float				diameter;
	union u_color		color;
};

typedef struct s_scene
{
	struct s_ambient	ambient;
	struct s_camera		camera;
	struct s_objects	**objects;
}						t_scene;

#endif // STRUCTS_H
