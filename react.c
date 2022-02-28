/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   react.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:48:43 by obouadel          #+#    #+#             */
/*   Updated: 2022/01/21 19:49:32 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "react.h"
static void	render(t_data *data);

unsigned int	get_time(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
void	*counter(void *arg)
{
	t_data *data;
	data = arg;
	while (1337)
	{
		data->time = get_time();
		if (data->time - data->create_date == data->start)
		{
			puts("GO!\n");
			data->on = 1;
			render(data);
			data->save = get_time() - data->create_date;
		}
	}
	return (NULL);
}
void	data_init(t_data *data)
{
	srand(time(NULL));
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "REACT");
	data->time = get_time();
	data->clicked = 0;
	data->start = randnum(5000, 7000);
	data->square.color = BLUE;
	data->square.x = 200;
	data->square.y = 200;
	data->on = 0;
	data->square.width = 100;
	data->square.height = 50;
	render(data);
}
void	draw_sq(t_data *data)
{
	int	i;
	int j = 0;
	int x = 230;
	int y = 215;
	while (j <= data->square.height)
	{
		i = 0;
		while (i <= data->square.width)
		{
			mlx_pixel_put(data->mlx, data->win, data->square.x + i, data->square.y + j, data->square.color);
			i++;
		}
		j++;	
	}
	if (data->on)
	{
		mlx_string_put(data->mlx, data->win, x, y - 7 , BLACK, "CLICK");
		mlx_string_put(data->mlx, data->win, x, y + 10, BLACK, "HERE");
	}
	else
		mlx_string_put(data->mlx, data->win, x, y, WHITE, "HERE");
		
}

int	mouse_button(int button,int x, int y, t_data *data)
{
	if (x < data->square.x || x > data->square.x + data->square.width || y < data->square.y
		|| y > data->square.y + data->square.height)
		return (0);
	if (button == 1)
	{
		if (data->on)
		{
			data->clicked = get_time() - data->create_date;
			data->square.color = BLUE;
			printf("Your reaction time is %u milisec\n", data->clicked - data->save);
			data->on = 0;
			render(data);
		}
		else
		{
			render(data);
			mlx_string_put(data->mlx, data->win, 215, 180, WHITE, "NOT YET");
		}
	}
	return (1);
}

static void	render(t_data *data)
{
	data->square.color = BLUE;
	if (data->on)
		data->square.color = GREEN;
	mlx_clear_window(data->mlx, data->win);
	draw_sq(data);
}

int main(void)
{
	t_data data;
	data.create_date = get_time();
	pthread_t temp;
	data_init(&data);
	pthread_create(&temp, NULL, counter, &data);
	pthread_detach(temp);
	mlx_mouse_hook(data.win, mouse_button, &data);
	mlx_loop(data.mlx);
	return (0);	
}