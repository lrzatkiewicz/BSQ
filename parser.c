#include "project.h"
#include <stdio.h>
#include <unistd.h>

// Extract the last three characters as special characters
// Ensure that all special characters are distinct
// Extract n_rows from the beginning up to (first_line_length - 3)
static int	assign_map_info_vals(char *buffer, MapInfo *map_info,
									int first_line_length)
{
	int	j;

	map_info->empty_char = buffer[first_line_length - 3];
	map_info->obstacle_char = buffer[first_line_length - 2];
	map_info->full_char = buffer[first_line_length - 1];
	if (map_info->empty_char == map_info->obstacle_char
		|| map_info->empty_char == map_info->full_char
		|| map_info->obstacle_char == map_info->full_char)
	{
		print_error("Error: Duplicate characters in metadata.");
		return (0);
	}
	map_info->n_rows = 0;
	j = 0;
	while (j < first_line_length - 3)
	{
		if (buffer[j] >= '0' && buffer[j] <= '9')
			map_info->n_rows = map_info->n_rows * 10 + (buffer[j] - '0');
		else
		{
			print_error("Error: Invalid character in row count.");
			return (0);
		}
		++j;
	}
	map_info->metadata_row_len = first_line_length;
	return (1);
}

static int	read_first_line(int fd, char *buffer, size_t buffer_size, size_t *i)
{
	ssize_t	bytes_read;
	char	c;

	while (*i < buffer_size - 1)
	{
		bytes_read = read(fd, &c, 1);
		if (bytes_read == 1)
		{
			buffer[(*i)++] = c;
			if (c == '\n')
			{
				buffer[*i] = '\0';
				break ;
			}
		}
		else if (bytes_read == 0)
		{
			print_error("Error: Unexpected end of file in metadata.");
			return (0);
		}
		else
		{
			print_error("Error: Failed to read the file.");
			return (0);
		}
	}
	if (*i == buffer_size - 1)
	{
		print_error("Error: Metadata line too long.");
		return (0);
	}
	return (1);
}

int	extract_map_info(int fd, MapInfo *map_info)
{
	char	buffer[1024];
	size_t	i;
	int		first_line_length;

	i = 0;
	if (!read_first_line(fd, buffer, sizeof(buffer), &i))
		return (0);
	first_line_length = i - 1;
	if (first_line_length < 4)
	{
		print_error("Error: Metadata line too short.");
		return (0);
	}
	if (!assign_map_info_vals(buffer, map_info, first_line_length))
	{
		print_error("Error: Values not assigned to the map_info.");
		return (0);
	}
	if (map_info->n_rows <= 0)
	{
		print_error("Error: Number of rows must be greater than zero.");
		return (0);
	}
	return (1);
}
