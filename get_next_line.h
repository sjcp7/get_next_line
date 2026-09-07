/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 14:37:09 by samupedr          #+#    #+#             */
/*   Updated: 2026/09/07 17:56:25 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

#include <stdlib.h>
#include <unistd.h>

typedef struct s_string
{
	char	*s;
	size_t	capacity;
	size_t	len;
}	t_string;

typedef struct s_buffer
{
	char	*buf;
	ssize_t	len;
	size_t	i;
}	t_buffer;


char		*get_next_line(int fd);
t_string	gnl_create_string(char *str, size_t capacity);
void		gnl_string_append(t_string *str, char c);

#endif