#ifndef FILES_H
# define FILES_H

# include <fcntl.h>
# include <libft.h>
# include <strings/dstring.h>
# include <unistd.h>

# define FMAP_BUF_SIZE 200

bool			get_file(struct s_string *file, const char *arg);

#endif // FILES_H
