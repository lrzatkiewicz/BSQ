#include "project.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	MapInfo map_info = {0};
	BiggestSquare biggest_square = {0};
	int i = 0;

	if (argc >= 2)
	{
		int	map_id = 1;
		while (map_id < argc)
		{
			int		fd = open(argv[map_id], O_RDONLY);
			char	**map_arr = NULL;
			char	*filename = argv[map_id];

			ft_putstr(filename);
			ft_putstr(": Largest square: \n");
			if (fd == -1)
			{
				print_error("Error: Failed to open the file.");
				map_id++;
				ft_put_new_line();
				continue ;
			}
			if (!extract_map_info(fd, &map_info))
			{
				print_error("Error: Failed to extract map info.");
				close(fd);
				map_id++;
				ft_put_new_line();
				continue ;
			}
			map_info.first_row_len = 0;
			if (!is_map_valid(fd, &map_info, &map_arr))
			{
				print_error("Error: Invalid map.");
				close(fd);
				map_id++;
				ft_put_new_line();
				continue ;
			}
			int		**num_map_arr;
			num_map_arr = numerize_map(map_arr, &map_info);
			if (!num_map_arr)
			{
				free_map_arr(map_arr, map_info.n_rows);
				close(fd);
				map_id++;
				ft_put_new_line();
				continue ;
			}
			map_calculations(num_map_arr, &map_info, &biggest_square);
			print_max_square(map_arr, &map_info, &biggest_square);
			int i = 0;
			while (i < map_info.n_rows)
			{
				free(num_map_arr[i]);
				++i;
			}
			free(num_map_arr);
			i = 0;
			while (i < map_info.n_rows)
			{
				free(map_arr[i]);
				++i;
			}
			free(map_arr);
			close(fd);
			if (argc > 2)
				ft_put_new_line();
			++map_id;
		}
	}
	else
	{
		char		**map_arr = NULL;
		char		*input_buffer = NULL;
		int			buffer_size = 1024 * 1024;
		int			total_bytes = 0;
		int			bytes_read = 0;

		input_buffer = malloc(buffer_size);
		if (!input_buffer)
		{
			print_error("Error: Memory allocation failed.");
			return (1);
		}
		while ((bytes_read = read(0, input_buffer + total_bytes, buffer_size - total_bytes)) > 0)
		{
			total_bytes += bytes_read;
			if (total_bytes >= buffer_size)
			{
				print_error("Error: Input too large.");
				free(input_buffer);
				return (1);
			}
		}
		if (bytes_read == -1)
		{
			print_error("Error: Failed to read from standard input.");
			free(input_buffer);
			return (1);
		}
		if (total_bytes < buffer_size)
			input_buffer[total_bytes] = '\0';
		else
			input_buffer[buffer_size - 1] = '\0';
		if (!process_input_buffer(input_buffer, total_bytes, &map_info, &map_arr))
		{
			free(input_buffer);
			return (1);
		}
		int			**num_map_arr = numerize_map(map_arr, &map_info);
		if (!num_map_arr)
		{
			free_map_arr(map_arr, map_info.n_rows);
			free(input_buffer);
			return (1);
		}
		map_calculations(num_map_arr, &map_info, &biggest_square);
		ft_put_new_line();
		ft_putstr("Map's largest square: \n");
		print_max_square(map_arr, &map_info, &biggest_square);
		i = 0;
		while (i < map_info.n_rows)
		{
			free(num_map_arr[i]);
			free(map_arr[i]);
			++i;
		}
		free(num_map_arr);
		free(map_arr);
		free(input_buffer);
	}
	return (0);
}
