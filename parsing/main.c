#include "parsing.h"

void parse_file(t_parsing *pars)
{
    validate_file(pars);
    gather_data(pars, pars->map);
    validate_map(pars, pars->map + pars->map_start);
}

void    init_pars_struct(t_parsing *pars, char *file)
{
    pars->file = file;
    pars->cont = NULL;
	pars->north = NULL;
	pars->south = NULL;
	pars->east = NULL;
	pars->west = NULL;
	pars->map = NULL;
	pars->norm_map = NULL;
    pars->fd = -1;
	pars->floor[0] = -1;
	pars->floor[1] = -1;
	pars->floor[2] = -1;
    pars->ceiling[0] = -1;
	pars->ceiling[1] = -1;
	pars->ceiling[2] = -1;
	pars->map_start = -1;
}

int main(int ac, char **av)
{
	t_parsing pars;

	if (ac < 2)
	{
		ft_putstr_fd("Error\nUsage: ./cub3d <example.cub>\n", 2);
		return (1);
	}
    init_pars_struct(&pars, av[1]);
	parse_file(&pars);
    print_parsing(&pars);
    parse_clean_exit(&pars, 0, "Program finished succesfully\n");
}
