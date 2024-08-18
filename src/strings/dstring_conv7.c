#include <math.h>
#include <stdint.h>
#include <strings/dstring.h>

struct s_string	string_from_float(float value, int a_dot)
{
	struct s_string	ret;
	float			fpart;

	ret = string_from_uqword(value);
	if (string_error(false, 0) != STRING_SUCCESS)
		return ((struct s_string){0});
	fpart = value - (int64_t)value;
	if (fpart == 0)
		return (ret);
	fpart *= pow(10, a_dot);
	string_push(&ret, '.');
	string_append(&ret, string_from_uqword(fpart));
	return (ret);
}
