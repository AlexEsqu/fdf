/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:26:33 by mkling            #+#    #+#             */
/*   Updated: 2024/10/03 12:59:23 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_lstsize(t_list *lst)
{
	int i;
	t_list *iteri;

	i = 0;
	if (lst == NULL)
		return (0);
	iteri = lst;
	while (iteri != NULL)
	{
		iteri = iteri->next;
		i++;
	}
	return (i);
}

// int ft_lstsizer(t_list *lst)
// {
// 	if (!lst)
// 		return 0;
// 	return 1 + ft_lstsizer(lst->next);
// }
