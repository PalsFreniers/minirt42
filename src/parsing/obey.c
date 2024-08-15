#include <libft.h>
#include "obey.h"

bool	float_obey(char c)
{
	return (ft_isdigit(c) || c == '.' || c == '-');
}

bool	float_vec_obey(char c)
{
	return (float_obey(c) || c == ',');
}

bool	color_obey(char c)
{
	return (ft_isdigit(c) || c == ',');
}
