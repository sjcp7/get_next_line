/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 14:37:09 by samupedr          #+#    #+#             */
/*   Updated: 2026/09/03 15:26:53 by samupedr         ###   ########.fr       */
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

char	*get_next_line(int fd);

#endif