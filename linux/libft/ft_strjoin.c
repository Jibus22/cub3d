/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:15:19 by jle-corr          #+#    #+#             */
/*   Updated: 2019/12/16 20:14:24 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		bufsize;

	if (!s1 || !s2)
		return (NULL);
	bufsize = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(s3 = (char*)malloc(sizeof(*s3) * bufsize)))
		return (NULL);
	ft_strlcpy(s3, s1, bufsize);
	ft_strlcat(s3, s2, bufsize);
	return (s3);
}
