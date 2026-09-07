/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 15:25:52 by samupedr          #+#    #+#             */
/*   Updated: 2026/09/07 18:19:02 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_string	gnl_create_string(char *str, size_t capacity)
{
	t_string	s;

	s.s = str;
	s.capacity = capacity;
	s.len = gnl_strlen(str);
	return (s);
}

void	gnl_string_append(t_string *str, char c)
{
	size_t	i;

	if (str->len + 1 > str->capacity)
	{
		str->capacity *= 2;
		gnl_resize(&str->s, str->capacity);
	}
	str->s[str->len++] = c;
}

static size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

static void	gnl_resize(char **s, size_t size)
{
	char	*str;
	size_t	i;

	str = (char *)malloc(size);
	if (!str)
		return ;
	i = 0;
	while (s[i])
	{
		str[i] = *s[i];
		i++;
	}
	while (i < size)
		str[i++] = '\0';
	free(*s);
	*s = str;
}
