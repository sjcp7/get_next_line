/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 15:25:52 by samupedr          #+#    #+#             */
/*   Updated: 2026/09/03 17:01:37 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_string	gnl_create_string(char *str, size_t capacity)
{
	t_string	s;

	s.s = str;
	s.capacity = capacity;
	s.len = ft_strlen(str);
	return (s);
}

void	gnl_string_append(t_string str, char *s)
{

}

size_t	ft_strlen(const char *s)
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

	str = (char *)malloc(size);
	if (!str)
		return ;
}