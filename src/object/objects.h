#ifndef OBJECTS_H
# define OBJECTS_H

# include <math/la.h>
# include <stddef.h>
# include <stdint.h>


typedef union u_color
{
	uint32_t		rgb;
	struct
	{
		uint8_t		r;
		uint8_t		g;
		uint8_t		b;
	};
}					t_color;

enum				e_object_type
{
	OBJ_LIGHT,
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
};

struct				s_object
{
	int				type;
	struct s_vec3	position;
	union u_color	color;
};

struct				s_light
{
	struct s_object	base;
	float			ratio;
};

struct				s_sphere
{
	struct s_object	base;
	float			diameter;
};

struct				s_plane
{
	struct s_object	base;
	struct s_vec3	normal;
};

struct				s_cylinder
{
	struct s_object	base;
	struct s_vec3	axis;
	float			diameter;
	float			height;
};

struct s_object		*object_new(size_t size, int type);
void				print_vec3(char *tabs, char *name, struct s_vec3 vec);
void				print_color(char *tabs, union u_color c);
void				print_float(char *tabs, char *name, float value);
void				print_light(struct s_light *light);
void				print_sphere(struct s_sphere *sphere);
void				print_plane(struct s_plane *plane);
void				print_cylinder(struct s_cylinder *cylinder);

#endif // OBJECTS_H
