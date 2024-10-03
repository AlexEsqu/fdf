/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:31:17 by mkling            #+#    #+#             */
/*   Updated: 2024/06/03 13:05:05 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t nbr, size_t size)
{
	void	*result;

	if (nbr == 0 || size == 0 || ((size_t) - 1 / nbr) < size)
		return (malloc(0));
	result = malloc(nbr * size);
	if (!result)
		return (NULL);
	ft_bzero(result, nbr * size);
	return (result);
}