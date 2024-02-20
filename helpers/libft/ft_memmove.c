/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:05:24 by ialdidi           #+#    #+#             */
/*   Updated: 2024/02/05 13:13:50 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*source;
	unsigned char	*destination;

	if (dst == src)
		return (dst);
	source = (unsigned char *)src;
	destination = (unsigned char *)dst;
	if (source < destination)
		while (len--)
			destination[len] = source[len];
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
