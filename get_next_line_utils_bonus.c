/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 15:25:52 by samupedr          #+#    #+#             */
/*   Updated: 2026/10/01 18:23:01 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static size_t	gnl_strlen(const char *s);
static void		gnl_string_resize(t_string *s, size_t size);

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
	if (!str->s)
		gnl_string_resize(str, str->capacity);
	else if (str->len + 1 > str->capacity)
		gnl_string_resize(str, str->capacity * 2);
	str->s[str->len++] = c;
	str->s[str->len] = '\0';
}

static size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

static void	gnl_string_resize(t_string *s, size_t size)
{
	char	*str;
	size_t	i;

	str = (char *)malloc(size + 1);
	if (!str)
		return ;
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
}
