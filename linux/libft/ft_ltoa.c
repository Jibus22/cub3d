/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 16:16:32 by jle-corr          #+#    #+#             */
/*   Updated: 2020/03/25 18:33:48 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ltoa(long n)
{
	short int	res;
	char		*str;
	long		e;
	int			i;

	i = (n < 0 ? 2 : 1);
	e = n;
	while ((e /= 10) != 0)
		i++;
	if (!(str = ft_strnew(i)))
		return (NULL);
	while (i-- > (n < 0 ? 1 : 0))
	{
		res = ((n / ft_pow(10, e++)) % 10);
		str[i] = res + (n > 0 ? 48 : (48 - (res * 2)));
	}
	if (n < 0)
		str[i] = '-';
	return (str);
}
