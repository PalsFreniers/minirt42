#include <math.h>
#include <stdint.h>
#include <strings/dstring.h>

static struct s_string	destroy_zero(struct s_string *a)
{
	if (a)
		string_destroy(a);
	return (string_zero());
}

struct s_string	string_from_float(float value, int a_dot)
{
	struct s_string	ret;
	float			fpart;
	struct s_string	dec;

	ret = string_from_sqword(value);
	if (string_error(false, 0) != STRING_SUCCESS)
		return ((struct s_string){0});
	fpart = value - (int64_t)value;
	if (fpart == 0)
		return (ret);
	fpart *= pow(10, a_dot);
	string_push(&ret, '.');
	if (string_error(false, 0) != STRING_SUCCESS)
		return (destroy_zero(&ret));
	dec = string_from_uqword(fpart);
	if (string_error(false, 0) != STRING_SUCCESS)
		return (destroy_zero(&ret));
	string_append(&ret, dec);
	string_destroy(&dec);
	if (string_error(false, 0) != STRING_SUCCESS)
		return (destroy_zero(&ret));
	if (value < 0 && (int)value == 0)
		string_push_front(&ret, '-');
	return (ret);
}
