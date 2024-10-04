#include "project.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int	process_map_character(char c, MapInfo *map_info,
							int *curr_row_len, int *has_valid_box)
{
	if (c == map_info->empty_char || c == map_info->obstacle_char
		|| c == map_info->full_char)
	{
		*has_valid_box = 1;
		++(*curr_row_len);
		return (0);
	}
	else if (c == '\n')
		return (1);
	return (0);
}

static int	validate_row(int curr_row_len, MapInfo *map_info)
{
	if (curr_row_len == 0)
	{
		print_error("Error: Empty row in the map.");
		return (0);
	}
	if (map_info->first_row_len == 0)
	{
		map_info->first_row_len = curr_row_len;
		map_info->row_len = curr_row_len;
	}
	else if (curr_row_len != map_info->first_row_len)
	{
		print_error("Error: Invalid length of one of the rows in the map.");
		return (0);
	}
	return (1);
}

int	validate_and_store_row(MapInfo *map_info, char ***map_arr, int *row, char *buffer, int buffer_len, int first_row)
{
	if (!validate_row(buffer_len, map_info))
		return (0);
	if (first_row)
	{
		if (!allocate_row_memory(map_arr, *row, map_info->row_len))
			return (0);
		buffer[buffer_len] = '\0';
		ft_strcpy((*map_arr)[*row], buffer);
		(*row)++;
	}
	else
	{
		(*map_arr)[*row][buffer_len] = '\0';
		(*row)++;
	}
	return (1);
}

int	process_first_row(int fd, MapInfo *map_info, char ***map_arr, int *row, int *has_valid_box)
{
	char	c;
	int		curr_row_len;
	char	temp_row[1024];
	int		temp_col;

	curr_row_len = 0;
	temp_col = 0;
	while (read(fd, &c, 1) == 1)
	{
		if (!validate_map_character(c, map_info))
		{
			print_error("Error: Invalid character in the map.");
			return (0);
		}
		if (process_map_character(c, map_info, &curr_row_len, has_valid_box))
		{
			if (!validate_and_store_row(map_info, map_arr, row, temp_row, temp_col, 1))
				return (0);
			break ;
		}
		else
		{
			if (temp_col >= 1023)
			{
				print_error("Error: First row is too long.");
				return (0);
			}
			temp_row[temp_col++] = c;
		}
	}
	if (curr_row_len == 0)
	{
		print_error("Error: First row is empty.");
		return (0);
	}
	return (1);
}
