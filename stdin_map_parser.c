#include "project.h"
#include <stdlib.h>

int	process_input_buffer(char *input_buffer, int total_bytes, MapInfo *map_info, char ***map_arr)
{
	int	pos;
	int	line_start;
	int	line_end;
	int	line_length;

	pos = 0;
	line_start = 0;
	line_end = 0;
	line_length = 0;
	while (pos < total_bytes && input_buffer[pos] != '\n')
		pos++;
	if (pos >= total_bytes)
	{
		print_error("Error: Missing map data.");
		return (0);
	}
	line_end = pos;
	line_length = line_end - line_start;
	input_buffer[line_end] = '\0';
	if (!parse_metadata(input_buffer + line_start, map_info))
		return (0);
	pos++;
	line_start = pos;
	*map_arr = malloc(sizeof(char *) * map_info->n_rows);
	if (!*map_arr)
	{
		print_error("Error: Memory allocation failed.");
		return (0);
	}
	int	row = 0;
	int	has_valid_box = 0;
	while (pos <= total_bytes && row < map_info->n_rows)
	{
		while (pos < total_bytes && input_buffer[pos] != '\n')
			pos++;
		line_end = pos;
		line_length = line_end - line_start;
		if (line_length != map_info->row_len && map_info->row_len != 0)
		{
			print_error("Error: Inconsistent row length in map.");
			free_map_arr(*map_arr, row);
			return (0);
		}
		else if (map_info->row_len == 0)
			map_info->row_len = line_length;
		(*map_arr)[row] = malloc(sizeof(char) * (line_length + 1));
		if (!(*map_arr)[row])
		{
			print_error("Error: Memory allocation failed.");
			free_map_arr(*map_arr, row);
			return (0);
		}
		int		i = 0;
		char	c;
		while (i < line_length)
		{
			c = input_buffer[line_start + i];
			if (!validate_map_character(c, map_info))
			{
				print_error("Error: Invalid character in the map.");
				free_map_arr(*map_arr, row + 1);
				return (0);
			}
			(*map_arr)[row][i] = c;
			if (c == map_info->empty_char || c == map_info->obstacle_char)
				has_valid_box = 1;
			i++;
		}
		(*map_arr)[row][line_length] = '\0';
		row++;
		if (pos < total_bytes && input_buffer[pos] == '\n')
		{
			pos++;
			line_start = pos;
		}
		else
			break ;
	}
	if (row != map_info->n_rows)
	{
		print_error("Error: Number of rows does not match metadata.");
		free_map_arr(*map_arr, row);
		return (0);
	}
	if (!has_valid_box)
	{
		print_error("Error: The map must contain at least one valid character.");
		free_map_arr(*map_arr, row);
		return (0);
	}
	return (1);
}

int	parse_metadata(char *line, MapInfo *map_info)
{
	int	i;
	int	n_rows;

	i = 0;
	n_rows = 0;
	while (line[i] >= '0' && line[i] <= '9')
	{
		n_rows = n_rows * 10 + (line[i] - '0');
		i++;
	}
	if (n_rows <= 0)
	{
		print_error("Error: Invalid number of rows in metadata.");
		return (0);
	}
	map_info->n_rows = n_rows;
	map_info->empty_char = line[i++];
	map_info->obstacle_char = line[i++];
	map_info->full_char = line[i++];
	if (line[i] != '\0')
	{
		print_error("Error: Invalid metadata format.");
		return (0);
	}
	return (1);
}
