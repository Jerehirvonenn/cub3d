#ifndef PARSING_H
#define PARSING_H

#include "../libft/libft.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif

typedef struct s_parsing
{
	char  *cont;
	char  *file;
	char  *north;
	char  *south;
	char  *west;
	char  *east;
	char **map;
	int	   fd;
	int	   floor[3];
	int	   ceiling[3];
	int	   map_start;
} t_parsing;

int	   count_rows(char **map);
int	   find_longest(char **map);
char **normalize_map(char **map);
bool   validate_characters(char **map);
bool   flood_fill(char **map, int x, int y, int rows, int col);
bool   check_walls(char **norm_map, int rows, int col);
bool   validate_map(t_parsing *pars, char **map);

//gather_data
void gather_data(t_parsing *pars, char **map);
#endif
