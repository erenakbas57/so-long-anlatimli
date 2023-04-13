/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 17:41:07 by makbas            #+#    #+#             */
/*   Updated: 2022/12/27 17:53:36 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
	oyuncudan aldığımız x ve y konumlarını burada kulanacağız
	oyuncunun hareket edebildiği yerleri anlamak için recursive fonksiyon
	kullandım. 
	gidebildiği yerler P olacak ve çıkış ya da collectible'a ulaşamazsa hata verecek
*/
int	valid_c(t_map *map)
{
	recursive_p(map, map->p_y_loc, map->p_x_loc);
	if (coin_c(map) || exit_c(map))
		return (1);
	return (0);
}

/*
	oyuncunun x+1, x-1, y+1 ve y-1 taraflarına gidebildiğini sırasıyla kontrol ediyoruz.
	eğer gidebiliyorsa (yani orası 0 ya da C ise) orayı P'ye eşitliyoruz.
	tekrar recursive fonksiyona  yeni konumunu yolluyoruz ve yeni tekrardan çalışıyor.
	------------------------
	oyuncunun gidebildiği (0 ve C) yerler P ile değişti.
*/
void	recursive_p(t_map *map, int y, int x)
{
	if (map->map_line[y][x + 1] == '0' || map->map_line[y][x + 1] == 'C')
	{
		map->map_line[y][x + 1] = 'P';
		recursive_p(map, y, x + 1);
	}
	if (map->map_line[y][x - 1] == '0' || map->map_line[y][x - 1] == 'C')
	{
		map->map_line[y][x - 1] = 'P';
		recursive_p(map, y, x - 1);
	}
	if (map->map_line[y + 1][x] == '0' || map->map_line[y + 1][x] == 'C')
	{
		map->map_line[y + 1][x] = 'P';
		recursive_p(map, y + 1, x);
	}
	if (map->map_line[y - 1][x] == '0' || map->map_line[y - 1][x] == 'C')
	{
		map->map_line[y - 1][x] = 'P';
		recursive_p(map, y - 1, x);
	}
}

/*
	haritada C varsa orayı da gidilebilecek yer yapıp P ile değştirmiştik
	haritayı iç içe while ile dönüp eğer C görürsek oraya duvarlardan dolayı
	gidemediği için coin hatası verecek
*/
int	coin_c(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (map->map_line[y])
	{
		x = 0;
		while (map->map_line[y][x] != 0 && map->map_line[y][x] != '\n')
		{
			if (map->map_line[y][x] == 'C')
			{
				ft_printf("HATA : Oyuncu toplanabilir eşyaya ulaşamıyor!");
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

/*
	oyuncunun çıkışa ulaşabilmesi için tek yol var.
	oyuncunun gidebildiği her kare P olduğu için
	eğer E harfinin dört yanından birinde P harfi varsa
	oyuncu çıkışa ulaşabiliyor demektir.
*/
int	exit_c(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (map->map_line[y] != 0)
	{
		x = 0;
		while (map->map_line[y][x] != '\n')
		{
			if (map->map_line[y][x] == 'E')
				break ;
			x++;
		}
		if (map->map_line[y][x] == 'E')
			break ;
		y++;
	}
	if (map->map_line[y][x + 1] == 'P' || map->map_line[y][x - 1] == 'P' || \
			map->map_line[y + 1][x] == 'P' || map->map_line[y - 1][x] == 'P')
		return (0);
	ft_printf("HATA : Oyuncu çıkışa ulaşamıyor!");
	return (1);
}
