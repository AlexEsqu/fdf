/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:52:14 by mkling            #+#    #+#             */
/*   Updated: 2024/10/03 15:03:01 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include "mlx-linux/mlx.h"
# include "libft/libft.h"

enum	e_error
{
	SUCCESS = 0,
	MALLOC_ERR = 1,
};

typedef struct s_display
{
	void	*link;
	void	*window;
	int		size_x;
	int		size_y;
	char	*title;
}	t_display;


#endif
