#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# define BUFFER_SIZE 1024

typedef struct s_parsing
{
	char	*cont;
	char	*file;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	**map;
	char	**norm_map;
	int		fd;
	int		floor[3];
	int		ceiling[3];
	int		map_start;
}	t_parsing;

int		count_rows(char **map);
int		find_longest(char **map);
char	**normalize_map(t_parsing *pars, char **map);
bool	validate_characters(t_parsing *pars, char **map);
bool	check_walls(char **norm_map, int rows);
void	validate_map(t_parsing *pars, char **map);

// parse_file
void	validate_file(t_parsing *pars);

// gather_data
void	gather_data(t_parsing *pars, char **map);
char	**normalize_map(t_parsing *pars, char **map);

// color
void	parse_color(char *str, int *color, t_parsing *parse);

// utils
char	*ft_strdup_trim(char *s);
int		count_rows(char **map);
int		find_longest(char **map);
bool	flood_fill(char **map, int x, int y, int rows);
void	fill_map(t_parsing *pars);

// cleanup
void	free_array(char ***array);
void	free_close(t_parsing *pars, char *s, char *free_str);
void	free_and_null(char **str);
void	parse_clean_exit(t_parsing *parse, int exit_code, char *str);

// debug
void	print_parsing(const t_parsing *parsing);
void	free_array(char ***array);
#endif
