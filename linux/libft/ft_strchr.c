/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:12:34 by jle-corr          #+#    #+#             */
/*   Updated: 2019/12/20 20:51:15 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchr(const char *s, int c)
{
	char		*s_cp;
	char		d;

	s_cp = (char*)s;
	d = (char)c;
	while (*s_cp != d)
		if (!*s_cp++)
			return (NULL);
	return (s_cp);
}
