/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 14:27:23 by makbas            #+#    #+#             */
/*   Updated: 2022/12/27 18:05:15 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
	argümanımızın dosya uzantısının ".ber" olduğunu ve 
	argüman sayısının 2 olduğunun kontrolünü yapıyoruz.
*/
int	file_control(int argc, char *argv)
{
	char	*a;

	a = argv;
	if (argc != 2)
	{
		ft_printf("HATA : geçersiz argüman sayısı!");
		return (1);
	}
	if (argv[ft_strlen(argv) - 1] != 'r' && argv[ft_strlen(argv) - 2] != 'e' && \
			argv[ft_strlen(a) - 3] != 'b' && argv[ft_strlen(a) - 4] != '.')
	{
		ft_printf("HATA : dosya uzantısı hatası!");
		return (1);
	}
	return (0);
}

/*
	okuduğumuz haritayı dizi elemanlarına yazdırdık ve harita
	kontrolüne geldik.
	1. dikdörtgen kontrolü
	2. player, collectible ve exit sayı kontrolü
	3. duvar kontrolü
	4. "01CEP" karakterlerinden başka karakter olmaması (geçersiz karakter kontrolü)
	5. oyuncu, çıkışa ve toplanabilirlere ulaşabiliyor mu kontrolü
*/
int	map_control(t_map *map)
{
	if (rectangle_c(map) || char_c(map) || wall_c(map) || \
			element_c(map) || valid_c(map))
	{
		free_map(map);
		return (1);
	}
	free_map(map);
	return (0);
}

/*
	ilk 4 işlemi basitçe yazdım.
	----------------------
	mlx_win fonksiyonuna mlx değerini ve sonradan x ve y piksellerini yollamamız gerekiyor.
	piksl uzunluğu x tane eleman * (her eleman 64px) olduğu için
	ve aynı şekilde yükseklikte y sayısı* 64px yaptık
	---------------------
	hook fonksiyonları
	ilk değişken pencereyi verdik.
	ikinci değişken 42doc sitesinde de verilen keypress eventinin numarası
	3. değişken maskeleme ama mac işletim sisteminde gerek olmuyor. linux için gerekli
	4. event olunca uygulanacak fonksiyon
	5. değişken struct yapımız 
*/
int	map_init(t_map *map, char *argc)
{
	int	x;

	map_read_control(map, argc);
	map->p_move_c = 0;
	map->mlx = mlx_init();
	x = ft_strlen(map->map_line[0]) - 1;
	map->mlx_win = mlx_new_window(map->mlx, \
		64 * x, 64 * map->map_y_line, "SO_LONG");
	if (!map->mlx || !map->mlx_win || create_xpm(map))
	{
		ft_printf("HATA : MLX hatası!");
		return (1);
	}
	win_put_img(map);
	mlx_string_put(map->mlx, map->mlx_win, 15, 15, 16777215, "0");
	mlx_hook(map->mlx_win, 2, 1L << 2, ft_move, map);
	mlx_hook(map->mlx_win, 17, 1L << 2, ft_exit, map);
	mlx_loop(map->mlx);
	return (0);
}

/*
	fonksiyonlar uzun olduğu için asıl fonksiyonumuz
	işlemi yaptıktan sonra burada if ile hata kontrolü
	yapılıyor
*/
int	map_read_control(t_map *map, char *f_name)
{
	map_read_c(map, f_name);
	if (!(map->map_line))
	{
		ft_printf("HATA : dosya okunamıyor!");
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_map	map;

	if (file_control(argc, argv[1]) || map_read_control(&map, argv[1]))
		return (1);
	if (map_control(&map))
		return (1);
	if (map_init(&map, argv[1]))
		return (1);
	return (0);
}
