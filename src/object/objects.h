#ifndef OBJECTS_H
#define OBJECTS_H

#include <stdint.h>

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

enum					e_object_type
{
	OBJ_LIGHT,
};

struct					s_object
{
	int					type;
	struct s_vec3		position;
	union u_color		color;
};

struct					s_light
{
	struct s_object		base;
	float				ratio;
};

struct					s_sphere
{
	struct s_object		base;
	float				diameter;
};

#endif // OBJECTS_H
