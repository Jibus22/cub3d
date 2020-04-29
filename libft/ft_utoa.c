/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 16:16:32 by jle-corr          #+#    #+#             */
/*   Updated: 2020/03/25 18:33:48 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_utoa(unsigned int n)
{
	char			*str;
	unsigned int	e;
	int				i;

	i = 1;
	e = n;
	while ((e /= 10))
		i++;
	if (!(str = ft_strnew(i)))
		return (NULL);
	while (i--)
		str[i] = ((n / ft_pow(10, e++)) % 10) + 48;
	return (str);
}
