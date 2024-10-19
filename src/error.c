/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:40:48 by mkling            #+#    #+#             */
/*   Updated: 2024/10/19 20:43:00 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	exit_if(bool condition, char *error_message, t_display *display)
{
	if (condition == false)
		return ;
	if (error_message)
		ft_putstr_fd(error_message, 2);
	if (display)
		wipe(display);
	exit(1);
}
