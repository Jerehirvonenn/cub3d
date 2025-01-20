#include "parsing.h"

/*
 * 0 .normalize map so each row is max length
 * 1. check the map for only 1, 0, one spawn or spaces
 * 2. floodfill from 0 and starting points to see its walled
 */

bool validate_characters(t_parsing *pars, char **map)
{
	int	 i;
	int	 j;
	int	 spawn;

	i = 0;
	spawn = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			char c = map[i][j];
			if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'E' &&
				c != 'W' && c != ' ')
				return (false);
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				spawn++;
			j++;
		}
		i++;
	}
	if (spawn != 1)
		parse_clean_exit(pars, 1, "Error\nMap has to contain exactly 1 spawn\n");
	return (true);
}

bool check_walls(char **norm_map, int rows)
{
	int i;
	int j;

	i = 0;
	while (norm_map[i])
	{
		j = 0;
		while (norm_map[i][j])
		{
			if (norm_map[i][j] == '0' || norm_map[i][j] == 'N' ||
				norm_map[i][j] == 'S' || norm_map[i][j] == 'E' ||
				norm_map[i][j] == 'W')
				if (!flood_fill(norm_map, i, j, rows))
					return false;
			j++;
		}
		i++;
	}
	return true;
}

void validate_map(t_parsing *pars, char **map)
{
	if (!validate_characters(pars, map))
		parse_clean_exit(pars, 1, "Error\nInvalid character in map\n");
	pars->norm_map = normalize_map(pars, map);
	if (!check_walls(pars->norm_map, count_rows(pars->norm_map)))
		parse_clean_exit(pars, 1, "Error\nMap not Isolated with walls\n");
	fill_map(pars);
	free_array(&pars->map);
}
