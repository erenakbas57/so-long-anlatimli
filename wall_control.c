/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 16:18:00 by makbas            #+#    #+#             */
/*   Updated: 2022/12/27 17:25:03 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
	duvar kontrolünde ilk ve son satır tamamen 1
	arada kalan tüm satırların 1. ve sonuncu indeksinin
	1 olması isteniyor.
*/
int	wall_c(t_map *map)
{
	int	y;
	int	value;
	int	value2;

	y = 0;
	value = wall_f_e(map, y);
	if (value != 0)
	{
		ft_printf("HATA : %d. satırda duvar hatası!", value);
		return (1);
	}
	y = 1;
	value2 = wall_middle(map, y);
	if (value2 != 0)
	{
		ft_printf("HATA : %d. satırda duvar hatası!", value2);
		return (1);
	}
	return (0);
}

/*
	ilk ve son satırın kontrolünü aynı anda gerçekleştiriyoruz.
	iç içe while döngüsünde dönerken 1. ve sonuncu satır kontrolünü 
	aynı anda yapıp hata varsa geri hata yolluyoruz
*/
int	wall_f_e(t_map *map, int y)
{
	int	x;
	int	len;

	len = map->map_y_line;
	if (y == 0 || y == (len - 1))
	{
		x = 0;
		while (map->map_line[y][x] != '\n')
		{
			if (map->map_line[0][x] != '1')
				return (1);
			if (map->map_line[len - 1][x] != '1')
				return (len);
			x++;
		}
	}
	return (0);
}

/*
	orta satırların 1. ve sonuncu elemanı "1" olması gerekiyor
*/
int	wall_middle(t_map *map, int y)
{
	int	line_len;

	line_len = ft_strlen(map->map_line[0]) - 2;
	while (map->map_line[y] != 0)
	{
		if (map->map_line[y][0] != '1'
				|| map->map_line[y][line_len] != '1')
			return (y + 1);
		y++;
	}
	return (0);
}
