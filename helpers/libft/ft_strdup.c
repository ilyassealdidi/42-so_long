/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 20:01:10 by ialdidi           #+#    #+#             */
/*   Updated: 2024/02/05 13:27:21 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strdup(const char *str)
{
	char	*ptr;
	char	*string;

	if (!str)
		return (ft_strdup(""));
	ptr = (char *)malloc(ft_strlen(str) + 1);
	if (!ptr)
		return (NULL);
	string = ptr;
	while (*str)
		*ptr++ = *str++;
	*ptr = '\0';
	return (string);
}
