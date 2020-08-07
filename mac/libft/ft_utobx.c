/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utobx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 18:19:32 by jle-corr          #+#    #+#             */
/*   Updated: 2020/03/26 19:23:48 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_utobx(unsigned int n)
{
	unsigned int	e;
	short int		res;
	char			*str;
	int				i;

	i = 1;
	e = n;
	while ((e /= 16))
		i++;
	if (!(str = ft_strnew(i)))
		return (NULL);
	while (i--)
	{
		res = ((n / ft_pow(16, e++)) % 16);
		str[i] = (res < 10 ? (res += 48) : (res += 55));
	}
	return (str);
}
