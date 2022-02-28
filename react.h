/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   react.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:50:40 by obouadel          #+#    #+#             */
/*   Updated: 2022/01/21 19:37:06 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <mlx.h>
#include <pthread.h>
#include <unistd.h>

# define WIDTH 500
# define HEIGHT 500
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define BLACK 0x00000000
# define WHITE 0xFFFFFFFF
#define randnum(min, max) \
        ((rand() % (int)(((max) + 1) - (min))) + (min))

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef struct s_quare
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}	t_square;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	int 			on;
	unsigned int		time;
	unsigned int		save;
	unsigned int		clicked;
	unsigned int		create_date;
	unsigned int		start;
	t_square		square;	
}	t_data;
