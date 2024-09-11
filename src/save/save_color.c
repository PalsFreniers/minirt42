#include <save/save.h>
#include <strings/dstring.h>
#include <unistd.h>

bool	destroy_all_color_string(bool ret, struct s_string *r,
		struct s_string *g, struct s_string *b)
{
	if (r)
		string_destroy(r);
	if (g)
		string_destroy(g);
	if (b)
		string_destroy(b);
	return (ret);
}

bool	save_color(union u_color c, int fd)
{
	struct s_string	r;
	struct s_string	g;
	struct s_string	b;
	struct s_string	ret;

	r = string_from_ubyte(c.r);
	if (string_error(false, 0) != STRING_SUCCESS)
		return (destroy_all_color_string(false, &r, NULL, NULL));
	g = string_from_ubyte(c.g);
	if (string_error(false, 0) != STRING_SUCCESS)
		return (destroy_all_color_string(false, &r, &g, NULL));
	b = string_from_ubyte(c.b);
	if (string_error(false, 0) != STRING_SUCCESS)
		return (destroy_all_color_string(false, &r, &g, &b));
	ret = string_new_with_capacity(15);
	if (string_error(false, 0) != STRING_SUCCESS)
		return (destroy_all_color_string(false, &r, &g, &b));
	string_append(&ret, r);
	string_push(&ret, ',');
	string_append(&ret, g);
	string_push(&ret, ',');
	string_append(&ret, b);
	write(fd, ret.ptr, ret.len);
	string_destroy(&ret);
	return (destroy_all_color_string(true, &r, &g, &b));
}
