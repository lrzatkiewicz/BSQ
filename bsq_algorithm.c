#include "project.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/* Function transforms the original map into an 2d array of integers
   "num_map_arr" in such way that an obstacle character is changed into '0' and
   an empty character is changed into '1'. The function returns the 2d int array
   that will be then used to perform caluclations which will allow to find the
   biggest square on the original map. Example:
   map_arr:  num_map_arr:
   ....      1111  
   ..o.      1101  
   ....      1111  
   ...o      1110  */
int	**numerize_map(char **map_arr, MapInfo *map_info)
{
	int	**num_map_arr;
	int	C;
	int	R;
	int	j;
	int	row;

	C = map_info->row_len;
	R = map_info->n_rows;
	if (!allocate_2d_int_array(&num_map_arr, R, C))
		return (NULL);
	row = 0;
	while (row < R)
	{
		j = 0;
		while (j < C)
		{
			if (map_arr[row][j] == map_info->empty_char)
				num_map_arr[row][j] = 1;
			else
				num_map_arr[row][j] = 0;
			++j;
		}
		++row;
	}
	return (num_map_arr);
}

/* Set the first column of sum_arr[][] to be the same as the first column of num_map_arr
   Set the first row of sum_arr[][] to be the same as the first row of num_map_arr
   Construct other entries of sum_arr[][] */
void	map_calculations(int **num_map_arr, MapInfo *map_info, BiggestSquare *biggest_square)
{
	int	i;
	int	j;
	int	**sum_arr;
	int	cols;
	int	rows;

	cols = map_info->row_len;
	rows = map_info->n_rows;
	if (!allocate_2d_int_array(&sum_arr, rows, cols))
		return ;
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (i == 0 || j == 0)
				sum_arr[i][j] = num_map_arr[i][j];
			else
			{
				if (num_map_arr[i][j] == 1)
					sum_arr[i][j] = min(sum_arr[i - 1][j], sum_arr[i - 1][j - 1], sum_arr[i][j - 1]) + 1;
				else
					sum_arr[i][j] = 0;
			}
			++j;
		}
		++i;
	}
	find_max_square(sum_arr, cols, rows, biggest_square);
	free_int_map_arr(sum_arr, rows);
}

void	find_max_square(int **sum_arr, int C, int R,
							BiggestSquare *biggest_square)
{
	int	max_square;
	int	max_i;
	int	max_j;
	int	i;
	int	j;

	max_square = sum_arr[0][0];
	max_i = 0;
	max_j = 0;
	i = 0;
	while (i < R)
	{
		j = 0;
		while (j < C)
		{
			if (max_square < sum_arr[i][j])
			{
				max_square = sum_arr[i][j];
				max_i = i;
				max_j = j;
			}
			++j;
		}
		++i;
	}
	biggest_square->max_square_size = max_square;
	biggest_square->max_i = max_i;
	biggest_square->max_j = max_j;
}

/* Function that prints the orginal map with the biggest square
   depicted using the 'full characters'. Example:  
   x x . . 
   x x o . 
   . . . . 
   . . . o  */
void	print_max_square(char **map_arr, MapInfo *map_info,
						BiggestSquare *biggest_square)
{
	int	i;
	int	j;
	int	max_square_size;
	int	max_i;
	int	max_j;

	max_square_size = biggest_square->max_square_size;
	max_i = biggest_square->max_i;
	max_j = biggest_square->max_j;
	i = 0;
	while (i < map_info->n_rows)
	{
		j = 0;
		while (j < map_info->row_len)
		{
			if (i < (max_i + 1) && i >= (max_i + 1 - max_square_size)
				&& j < (max_j + 1)
				&& j >= (max_j + 1 - max_square_size))
				ft_putchar_space(map_info->full_char);
			else
				ft_putchar_space(map_arr[i][j]);
			++j;
		}
		ft_put_new_line();
		++i;
	}
}
