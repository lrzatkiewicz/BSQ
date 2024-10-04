#include "project.h"
#include <stdlib.h>

int	allocate_row_memory(char ***map_arr, int row, int row_len)
{
	(*map_arr)[row] = malloc(sizeof(char) * (row_len + 1));
	if (!(*map_arr)[row])
	{
		print_error("Error: Memory allocation failed.");
		return (0);
	}
	return (1);
}

void	free_map_arr(char **map_arr, int rows_allocated)
{
	int	i;

	i = 0;
	if (map_arr == NULL)
		return ;
	while (i < rows_allocated)
	{
		if (map_arr[i] != NULL)
			free(map_arr[i]);
			map_arr[i] = NULL;
		++i;
	}
	free(map_arr);
	map_arr = NULL;
}

// Function to allocate memory for a single int row
int	allocate_int_row(int ***int_map_arr, int row, int row_len)
{
	(*int_map_arr)[row] = malloc(sizeof(int) * row_len);
	if (!(*int_map_arr)[row])
	{
		print_error("Error: Memory allocation failed for int row.");
		return (0);
	}
	return (1);
}

// Function to free memory allocated for the int map array
void	free_int_map_arr(int **int_map_arr, int rows_allocated)
{
	int	i;

	if (int_map_arr == NULL)
		return ;
	i = 0;
	while (i < rows_allocated)
	{
		if (int_map_arr[i] != NULL)
			free(int_map_arr[i]);
		int_map_arr[i] = NULL;
		++i;
	}
	free(int_map_arr);
	int_map_arr = NULL;
}

// Function to allocate memory for a 2D int array
// Parameters:
//   - rows: Number of rows in the array
//   - cols: Number of columns in each row
//   - int_map_arr: Pointer to the int** array to be allocated
// Returns:
//   - 1 on success, 0 on failure (memory allocation failed)
int	allocate_2d_int_array(int ***int_map_arr, int rows, int cols)
{
	int	i;
	int	j;

	*int_map_arr = malloc(sizeof(int *) * rows);
	if (!(*int_map_arr))
	{
		print_error("Error: Memory allocation failed for int_map_arr.");
		return (0);
	}
	i = 0;
	while (i < rows)
	{
		(*int_map_arr)[i] = malloc(sizeof(int) * cols);
		if (!(*int_map_arr)[i])
		{
			print_error("Error: Memory allocation failed for int_map_arr row.");
			j = 0;
			while (j < i)
			{
				free((*int_map_arr)[j]);
				j++;
			}
			free(*int_map_arr);
			*int_map_arr = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}
