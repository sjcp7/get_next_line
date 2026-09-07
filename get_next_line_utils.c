/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 15:25:52 by samupedr          #+#    #+#             */
/*   Updated: 2026/09/07 11:01:27 by samupedr         ###   ########.fr       */
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

void	gnl_string_append(t_string *str, char *s)
{
	size_t	s_len;
	size_t	i;

	s_len = gnl_strlen(s);
	if (s_len + str->len > str->capacity)
	{
		if (s_len + str->len > 2 * str->capacity)
			str->capacity = s_len + str->len;
		else
			str->capacity *= 2;
		gnl_resize(&str->s, str->capacity);
	}
	i = str->len;
	while (i - str->len < s_len)
	{
		str->s[i] = s[i - str->len];
		i++;
	}
	str->len += s_len;
}

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

void	gnl_resize(char **s, size_t size)
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