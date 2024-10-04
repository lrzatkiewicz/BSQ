// project.h

#ifndef PROJECT_H
#define PROJECT_H

#include <unistd.h>

typedef struct {
    int n_rows;
    int row_len;
    int metadata_row_len;
    int first_row_len;
    char empty_char;
    char obstacle_char;
    char full_char;
} MapInfo;

typedef struct {
    int max_square_size;
    int max_i;
    int max_j;
} BiggestSquare;

// Function prototypes
int **numerize_map(char **map_arr, MapInfo *map_info);
void map_calculations(int **num_map_arr, MapInfo *map_info, BiggestSquare *biggest_square);
int min(int a, int b, int c);
void print_max_square(char **map_arr, MapInfo *map_info, BiggestSquare *biggest_square);
void find_max_square(int **sum_arr, int C, int R, BiggestSquare *biggest_square);

// From validator.c
int is_map_valid(int fd, MapInfo *map_info, char ***map_arr);
int validate_map_character(char c, MapInfo *map_info);
int finalize_validation(int has_valid_box, int row_count, MapInfo *map_info);

// From memory_mgmt.c
int allocate_row_memory(char ***map_arr, int row, int row_len);
void free_map_arr(char **map_arr, int rows_allocated);
int allocate_int_row(int ***int_map_arr, int row, int row_len);
void free_int_map_arr(int **int_map_arr, int rows_allocated);
int allocate_2d_int_array(int ***int_map_arr, int rows, int cols);

// From processor.c
int process_map_character(char c, MapInfo *map_info, int *curr_row_len, int *has_valid_box);
int process_first_row(int fd, MapInfo *map_info, char ***map_arr, int *row, int *has_valid_box);
int validate_and_store_row(MapInfo *map_info, char ***map_arr, int *row, char *buffer, int buffer_len, int first_row);

// Utility function
void print_error(const char *message);
void print_map(char **map_arr, MapInfo *map_info);
void ft_strcpy(char *dest, const char *src);
void ft_putnbr(int nb);
void ft_putstr(char *str);
int ft_strlen(char *str);
void ft_putchar_space(char c);
int min(int a, int b, int c);
void ft_put_new_line();

int extract_map_info(int fd, MapInfo *map_info);

int process_input_buffer(char *input_buffer, int total_bytes, MapInfo *map_info, char ***map_arr);
int parse_metadata(char *line, MapInfo *map_info);

#endif // PROJECT_H
