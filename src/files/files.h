/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 01:59:21 by maamine           #+#    #+#             */
/*   Updated: 2025/01/30 01:59:22 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILES_H
# define FILES_H

# include <fcntl.h>
# include <libft.h>
# include <strings/dstring.h>
# include <unistd.h>

# define FMAP_BUF_SIZE 200

bool			get_file(struct s_string *file, const char *arg);

#endif // FILES_H
