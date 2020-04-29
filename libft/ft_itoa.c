/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:16:32 by jle-corr          #+#    #+#             */
/*   Updated: 2019/12/04 18:33:48 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	short int	res;
	char		*str;
	int			i;
	int			e;

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
