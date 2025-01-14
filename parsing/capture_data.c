#include "parsing.h"
#include <string.h> //CHANGE TO FT FUNCTIONS!!!

bool false_message(char *str)
{
	if (str)
		ft_putstr_fd(str, 2);
	return false;
}

void free_and_null(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

void parse_clean_exit(t_parsing *parse, int exit_code)
{
	free_and_null(&parse->north);
	free_and_null(&parse->south);
	free_and_null(&parse->west);
	free_and_null(&parse->east);
	if (parse->map)
	{
		for (int i = 0; parse->map[i]; i++)
			free_and_null(&parse->map[i]);
		free(parse->map);
		parse->map = NULL;
	}
	if (exit_code != 0)
		exit(exit_code);
}

int ft_atoi_color(const char *str, int *j)
{
	int i;
	int result;

	result = -1;
	i = *j;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '\0')
		return -1;
	if (str[i] >= '0' && str[i] <= '9')
		result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result > 255)
			return -1;
		i++;
	}
	if (str[i] != '\0' && str[i] != ',')
		return -1;
	*j = i;
	return result;
}

void parse_color(char *str, int *color, t_parsing *parse)
{
	int index;
	int i;

	i = 0;
	index = 0;
	if (color[0] != -1)
	{
		ft_putstr_fd("Error\nDuplicate color in assignment\n", 2);
		parse_clean_exit(parse, 1);
	}
	while (str[i])
	{
		if (index == 3)
		{
			ft_putstr_fd("Error\nToo many colors assigned\n", 2);
			parse_clean_exit(parse, 1);
		}
		color[index++] = ft_atoi_color(str, &i);
		if (color[index - 1] == -1)
		{
			ft_putstr_fd("Error\nColor value missin or not in range 0-255\n",
						 2);
			parse_clean_exit(parse, 1);
		}
		while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			i++;
		if (str[i] == ',')
			i++;
	}
	if (index != 3)
	{
		ft_putstr_fd("Error\nInvalid number of color values\n", 2);
		parse_clean_exit(parse, 1);
	}
}

void check_and_set_texture(char **texture, const char *value, t_parsing *pars)
{
	if (*texture)
	{
		ft_putstr_fd("Error\nDuplicate texture assignment\n", 2);
		parse_clean_exit(pars, 1);
	}
	*texture = strdup(value);
	if (!*texture)
	{
		ft_putstr_fd("Error\nMalloc failure\n", 2);
		parse_clean_exit(pars, 1);
	}
}

void check_str(char *str, t_parsing *pars)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (strlen(str + i) == 0)
		return;
	if (strncmp(str + i, "NO ", 3) == 0)
		check_and_set_texture(&pars->north, str + i + 3, pars);
	else if (strncmp(str + i, "SO ", 3) == 0)
		check_and_set_texture(&pars->south, str + i + 3, pars);
	else if (strncmp(str + i, "WE ", 3) == 0)
		check_and_set_texture(&pars->west, str + i + 3, pars);
	else if (strncmp(str + i, "EA ", 3) == 0)
		check_and_set_texture(&pars->east, str + i + 3, pars);
	else if (str[i] == 'F' && str[i + 1] == ' ')
		parse_color(str + i + 2, pars->floor, pars);
	else if (str[i] == 'C' && str[i + 1] == ' ')
		parse_color(str + i + 2, pars->ceiling, pars);
	else
	{
		ft_putstr_fd("Error\nInvalid identifier encoutnered\n", 2);
		parse_clean_exit(pars, 1);
	}
}

bool all_filled(t_parsing *pars)
{
	if (!pars->north || !pars->south || !pars->west || !pars->east)
		return false;
	for (int i = 0; i < 3; i++)
		if (pars->floor[i] < 0 || pars->ceiling[i] < 0)
			return false;
	return true;
}

int skip_empty_lines(t_parsing *pars, char **map, int i)
{
	int j;

	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] == ' ') // need tocheck all whitespace?
			j++;
		if (map[i][j])
			return i;
		i++;
	}
	// theres no map to check, its invalid
	ft_putstr_fd("Error\nNo possible map to check", 2);
	parse_clean_exit(pars, 1);
	return (0);
}

void gather_data(t_parsing *pars, char **map)
{
	int i;

	i = -1;
	while (map[++i])
	{
		check_str(map[i], pars);
		if (all_filled(pars))
		{
			printf("Everything filled\n");
			pars->map_start = skip_empty_lines(pars, map, i + 1);
			return ;
		}
	}
	ft_putstr_fd("Error\nNot all needed data available in file", 2);
	parse_clean_exit(pars, 1);
}

// debug
void print_parsing(const t_parsing *parsing)
{
	if (!parsing)
	{
		printf("Parsing structure is NULL.\n");
		return;
	}

	printf("North Texture: %s\n", parsing->north ? parsing->north : "Not set");
	printf("South Texture: %s\n", parsing->south ? parsing->south : "Not set");
	printf("West Texture: %s\n", parsing->west ? parsing->west : "Not set");
	printf("East Texture: %s\n", parsing->east ? parsing->east : "Not set");

	printf("Floor Color: %d, %d, %d\n", parsing->floor[0], parsing->floor[1],
		   parsing->floor[2]);
	printf("Ceiling Color: %d, %d, %d\n", parsing->ceiling[0],
		   parsing->ceiling[1], parsing->ceiling[2]);

	printf("Map:\n");
	if (parsing->map)
		for (int i = 0; parsing->map[i]; i++)
			printf("  %s\n", parsing->map[i]);
	else
		printf("  Map is not set.\n");
}

bool validate_map(t_parsing *pars, char **map)
{
	printf("MAP FIRST LINE IS %s\n", map[0]);
	if (!validate_characters(map))
		return (false);
	char **norm_map = normalize_map(map);
	if (!check_walls(norm_map, count_rows(norm_map), find_longest(norm_map)))
		printf("Error with walls\n");

	printf("Normalized map\n");
	int i = -1;
	while (map[++i])
		printf("%s\n", norm_map[i]);
	return (true);
}

int main(int ac, char **av)
{
	if (ac < 2)
		return (1);
	ac--;
	av++;

	t_parsing pars;
	pars.north = NULL;
	pars.south = NULL;
	pars.east = NULL;
	pars.west = NULL;
	pars.map = NULL;
	pars.floor[0] = -1;
	pars.floor[1] = -1;
	pars.floor[2] = -1;
	pars.ceiling[0] = -1;
	pars.ceiling[1] = -1;
	pars.ceiling[2] = -1;
	pars.map_start = 0;
	pars.map = NULL;
	gather_data(&pars, av);
	print_parsing(&pars);
	if (!validate_map(&pars, av + pars.map_start))
		printf("Map validation Failed\n");
}
