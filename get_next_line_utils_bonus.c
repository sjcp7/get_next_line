/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 15:25:52 by samupedr          #+#    #+#             */
/*   Updated: 2026/10/01 18:30:34 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static size_t	gnl_strlen(const char *s);
static int		gnl_string_resize(t_string *s, size_t size);

t_string	gnl_create_string(char *str, size_t capacity)
{
	t_string	s;

	s.s = str;
	s.capacity = capacity;
	s.len = gnl_strlen(str);
	return (s);
}

int	gnl_string_append(t_string *str, char c)
{
	if (!str->s)
	{
		if (!gnl_string_resize(str, str->capacity))
			return (0);
	}
	else if (str->len + 1 > str->capacity)
		if (!gnl_string_resize(str, str->capacity * 2))
			return (0);
	str->s[str->len++] = c;
	str->s[str->len] = '\0';
	return (1);
}

static size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

static int	gnl_string_resize(t_string *s, size_t size)
{
	char	*str;
	size_t	i;

	str = (char *)malloc(size + 1);
	if (!str)
		return (0);
	i = 0;
	while (i < s->len)
	{
		str[i] = s->s[i];
		i++;
	}
	str[i] = '\0';
	free(s->s);
	s->s = str;
	s->capacity = size;
	return (1);
}
