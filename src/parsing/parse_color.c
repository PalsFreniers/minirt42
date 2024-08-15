#include <libft.h>
#include <logger/logger.h>
#include <parsing/obey.h>
#include <parsing/parse.h>

static bool	get_byte(struct s_string byte, uint8_t *byt, struct s_string *parts)
{
	*byt = string_to_ubyte(byte);
	if (string_error(false, 0) != STRING_SUCCESS)
	{
		logger_error("byte values should be in range 0-255");
		logger_info("byte value is currently: %d (0x%x)", *byt, *byt);
		ft_free("p", parts);
		return (false);
	}
	return (true);
}

bool	parse_color(struct s_string rgb, union u_color *color)
{
	struct s_string	*parts;
	size_t			count;

	parts = string_split(rgb, string_new_u_from_cstr(","), &count);
	if (string_error(false, 0) != STRING_SUCCESS)
		return (false);
	if (!string_obey(rgb, color_obey) || count != 3)
	{
		logger_error("unable to parse color");
		ft_free("p", parts);
		return (false);
	}
	color->rgb = 0;
	if (!get_byte(parts[0], &(color->r), parts))
		return (false);
	if (!get_byte(parts[1], &(color->g), parts))
		return (false);
	if (!get_byte(parts[2], &(color->b), parts))
		return (false);
	ft_free("p", parts);
	return (true);
}
