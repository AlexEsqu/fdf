/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:32:09 by mkling            #+#    #+#             */
/*   Updated: 2024/10/03 12:59:25 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*iteri;

	iteri = lst;
	while (iteri)
	{
		(*f)(iteri->content);
		iteri = iteri->next;
	}
}

// void	ft_lstiterr(t_list *lst, void (*f)(void *))
// {
// 	if (!lst)
// 		return ;
// 	(*f)(lst->content);
// 		return (ft_lstiterr(lst->next, f));
// }


