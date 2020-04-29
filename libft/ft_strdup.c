/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:14:45 by jle-corr          #+#    #+#             */
/*   Updated: 2019/12/20 20:13:08 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s1)
{
	int		i;
	char	*dup;

	if (!(dup = ft_strnew(ft_strlen(s1))))
		return (NULL);
	i = 0;
	while (*s1)
		dup[i++] = *s1++;
	return (dup);
}
