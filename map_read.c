/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 17:59:32 by makbas            #+#    #+#             */
/*   Updated: 2022/12/27 18:00:51 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
	iç içe while döngüsü ile haritanın her karakterine gireceğiz
	uzunluk referansı ilk satırın uzunluğuna göre olacak.
	uzunluğun içinde '\n' karaktteri de olduğu için "len - 1"e eşitse
	satır sayısını arttırıp diğer satırı kontrol edecek.
	eğer diğer satırlardan biri ilk satırın uzunluğuna eşit değilse
	hata döndürecek
*/
int	rectangle_c(t_map *map)
{
	int	y;
	int	x;
	int	len;

	len = ft_strlen(map->map_line[0]);
	y = 0;
	while (y < map->map_y_line)
	{
		x = 0;
		while (map->map_line[y] && map->map_line[y][x] != '\n' && \
			x < (int)(ft_strlen(map->map_line[y])))
			x++;
		if (x != len -1)
		{
			ft_printf("HATA : %d. satırda dikdörtgen hatası!", y + 1);
			return (1);
		}
		y++;
	}
	return (0);
}

/*
	ilk önce map_read fonksiyonuna gönderiyoruz.
	malloc ile yer açtığımız dizideki elemanlara
	get_next_line ile satırları içine yazacağız
*/
int	map_read_c(t_map *map, char *f_name)
{
	int	fd;
	int	i;

	map_read(map, f_name);
	if (!(map->map_line) || map->map_y_line <= 0)
	{
		map->map_line = NULL;
		return (1);
	}
	fd = open(f_name, O_RDONLY);
	if (fd == -1)
	{
		free(map->map_line);
		return (1);
	}
	i = 0;
	map->map_line[i] = get_next_line(fd);
	while (map->map_line[i])
	{
		i++;
		map->map_line[i] = get_next_line(fd);
	}
	close(fd);
	return (0);
}

/*
	buradaki yaptığımız işlem; harita dosyamızı açıyoruz ve
	sayma işlemi yapıyoruz.
	haritamızı diziye (char ** yapısı) aktaracağımız için
	haritanın satır sayısını alacağız ve malloc ile yer açıp
	kontrolleri sağlayacağız 
*/
void	map_read(t_map *map, char *f_name)
{
	int		len;
	int		fd;
	char	c;

	fd = open(f_name, O_RDONLY);
	if (fd < 0)
	{
		map->map_y_line = 0;
		return ;
	}
	len = 0;
	while (read(fd, &c, 1))
	{
		if (c == '\n')
			len++;
	}
	len++;
	close(fd);
	map->map_line = malloc(sizeof(char *) * len + 1);
	if (!map->map_line)
		return ;
	map->map_line[len + 1] = NULL;
	map->map_y_line = len;
}

/*
	haritanın satırlarını tutan dizi elemanlarını
	free'ledikten sonra diziyi de free'liyoruz
*/
void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->map_y_line)
	{
		free(map->map_line[i]);
		i++;
	}
	free(map->map_line);
}

/*
	çıkış yaptığımızda mlx kütüphanesinin bize verdiği
	fonksiyon ile resimleri temizliyoruz.
	yine mlx kütüphane fonksiyonu ile ekranı temizliyoruz.
	ve map struct'ını tamamen free'liyoruz.
*/
int	ft_exit(t_map *map)
{
	mlx_destroy_image(map->mlx, map->img_b);
	mlx_destroy_image(map->mlx, map->img_w);
	mlx_destroy_image(map->mlx, map->img_e);
	mlx_destroy_image(map->mlx, map->img_p);
	mlx_destroy_image(map->mlx, map->img_c);
	mlx_clear_window(map->mlx, map->mlx_win);
	free_map(map);
	exit(0);
	return (0);
}
