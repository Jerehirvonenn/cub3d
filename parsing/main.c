#include "parsing.h"

bool validate_map(t_parsing *pars, char **map)
{
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

void    init_pars_struct(t_parsing *pars, char *file)
{
    pars->file = file;
	pars->north = NULL;
	pars->south = NULL;
	pars->east = NULL;
	pars->west = NULL;
	pars->map = NULL;
    pars->fd = -1;
    pars->map_size = 20;
	pars->floor[0] = -1;
	pars->floor[1] = -1;
	pars->floor[2] = -1;
    pars->ceiling[0] = -1;
	pars->ceiling[1] = -1;
	pars->ceiling[2] = -1;
	pars->map_start = -1;
	pars->map = NULL;
}

int main(int ac, char **av)
{
	t_parsing pars;

	if (ac < 2)
    {
        ft_putstr_fd("Error\nUsage: ./cub3d <example.cub>", 2);
		return (1);
    }
	ac--;
	av++;
    init_pars_struct(&pars);
	gather_data(&pars, av);
	print_parsing(&pars);
	if (!validate_map(&pars, av + pars.map_start))
		printf("Map validation Failed\n");
}
