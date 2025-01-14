#ifndef PARSING_H
#define PARSING_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"

typedef struct s_parsing
{
    char *north;
    char *south;
    char *west;
    char *east;
    char **map;
    int floor[3];
    int ceiling[3];
    int map_start;
} t_parsing;

int count_rows(char **map);
int find_longest(char **map);
char **normalize_map(char **map);
bool validate_characters(char **map);
bool flood_fill(char **map, int x, int y, int rows, int col);
bool check_walls(char **norm_map, int rows, int col);
bool validate_map(t_parsing *pars, char **map);

#endif
