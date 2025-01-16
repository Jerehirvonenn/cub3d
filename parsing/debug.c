#include "parsing.h"

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

	printf("Norm_Map:\n");
	if (parsing->norm_map)
		for (int i = 0; parsing->norm_map[i]; i++)
			printf("%s\n", parsing->norm_map[i]);
	else
		printf("Map is not set.\n");
}
