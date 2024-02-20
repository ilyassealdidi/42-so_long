/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:09:09 by ialdidi           #+#    #+#             */
/*   Updated: 2024/02/05 13:13:50 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t len)
{
	size_t	dlen;
	size_t	slen;

	if (!len)
		return (ft_strlen(src));
	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	if (len < dlen)
		return (len + slen);
	len -= dlen;
	if (len)
	{
		while (*src && --len)
			*(dst++ + dlen) = *src++;
		*(dst + dlen) = 0;
	}
	return (dlen + slen);
}
