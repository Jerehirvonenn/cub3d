#include "parsing.h"

bool validate_map(char **map)
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

int main(int ac, char **av)
{
	if (ac < 2)
		return (1);
	ac--;
	av++;
	validate_map(av);
}
