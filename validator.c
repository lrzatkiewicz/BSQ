#include "project.h"
#include <stdio.h>
#include <stdlib.h>

int	validate_map_character(char c, MapInfo *map_info)
{
	if (c == map_info->empty_char || c == map_info->obstacle_char
		|| c == map_info->full_char
		|| c == '\n')
	{
		return (1);
	}
	else
		return (0);
}

int	finalize_validation(int has_valid_box, int row_count, MapInfo *map_info)
{
	if (!has_valid_box)
	{
		print_error("Error: The map must have at least one line with valid boxes.");
		return (0);
	}
	if (row_count != map_info->n_rows)
	{
		print_error("Error: Number of rows doesn't match the metadata.");
		return (0);
	}
	return (1);
}

int	is_map_valid(int fd, MapInfo *map_info, char ***map_arr)
{
	ssize_t	file_bytes;
	int		row;
	int		has_valid_box;
	int		row_count;

	row = 0;
	has_valid_box = 0;
	row_count = 0;
	map_info->row_len = 0;
	*map_arr = malloc(sizeof(char *) * map_info->n_rows);
	if (!*map_arr)
	{
		print_error("Error: Memory allocation failed.");
		return (0);
	}
	if (!process_first_row(fd, map_info, map_arr, &row, &has_valid_box))
	{
		free_map_arr(*map_arr, row);
		return (0);
	}
	row_count++;

	char	buffer[1024];
	int		curr_row_len = 0;
	int		col = 0;
	int		i;
	char	c;

	while ((file_bytes = read(fd, buffer, sizeof(buffer))) > 0)
	{
		i = 0;
		while (i < file_bytes)
		{
			c = buffer[i];
			if (!validate_map_character(c, map_info))
			{
				print_error("Error: Invalid character in the map.");
				free_map_arr(*map_arr, row + 1);
				return (0);
			}
			if (process_map_character(c, map_info, &curr_row_len, &has_valid_box))
			{
				if (!validate_and_store_row(map_info, map_arr, &row, NULL, col, 0))
				{
					free_map_arr(*map_arr, row + 1);
					return (0);
				}
				curr_row_len = 0;
				col = 0;
				row_count++;
			}
			else
			{
				if (col == 0)
				{
					if (!allocate_row_memory(map_arr, row, map_info->row_len))
					{
						free_map_arr(*map_arr, row);
						return (0);
					}
				}
				(*map_arr)[row][col++] = c;
			}
			++i;
		}
	}
	if (file_bytes == -1)
	{
		print_error("Error: Failed to read the file.");
		free_map_arr(*map_arr, row);
		return (0);
	}
	if (curr_row_len > 0)
		row_count++;
	if (!finalize_validation(has_valid_box, row_count, map_info))
	{
		free_map_arr(*map_arr, row);
		return (0);
	}
	return (1);
}
