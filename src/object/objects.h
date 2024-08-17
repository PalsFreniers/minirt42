#ifndef OBJECTS_H
# define OBJECTS_H

# include <stddef.h>
# include <stdint.h>

typedef struct s_vec3
{
	float			x;
	float			y;
	float			z;
}					t_vec3;

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

struct s_object		*object_new(size_t size, int type);
void				print_vec3(char *tabs, char *name, struct s_vec3 vec);
void				print_color(char *tabs, union u_color c);
void				print_float(char *tabs, char *name, float value);
void				print_light(struct s_light *light);

#endif // OBJECTS_H
