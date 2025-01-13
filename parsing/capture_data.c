#include "parsing.h"
#include <string.h> //CHANGE TO FT FUNCTIONS!!!

int parse_color(char *color_str, int *color)
{
	char *token = strtok(color_str, ",");
	int	  i = 0;
	while (token)
	{
		color[i++] = atoi(token);
		if (i > 3)
			return 0; // Invalid format
		token = strtok(NULL, ",");
	}
	return i == 3;
}

bool check_str(char *str, t_parsing *pars)
{
	int i;
	int j;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (strlen(str + i) == 0)
		return true; // Skip empty lines
	if (strncmp(str + i, "NO ", 3) == 0)
		pars->north = strdup(str + i);
	else if (strncmp(str + i, "SO ", 3) == 0)
		pars->south = strdup(str + i);
	else if (strncmp(str + i, "WE ", 3) == 0)
		pars->west = strdup(str + i);
	else if (strncmp(str + i, "EA ", 3) == 0)
		pars->east = strdup(str + i);
	else if (str[i] == 'F' && str[i + 1] == ' ')
	{
		if (!parse_color(str + i + 2, pars->floor))
		{
			fprintf(stderr, "Invalid floor color format\n");
			exit(EXIT_FAILURE);
		}
	}
	else if (str[i] == 'C' && str[i + 1] == ' ')
	{
		if (!parse_color(str + i + 2, pars->floor))
		{
			fprintf(stderr, "Invalid ceiling color format\n");
			return false;
		}
	}
	else
	{
		fprintf(stderr, "Unknown identifier: %s\n", str);
		return false;
	}
	return true;
}

bool gather_data(t_parsing *pars, char **map)
{
	int i;

	i = -1;
	while (map[++i])
		if (!check_str(map[i], pars))
			return false;
	return true;
}

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
	if (!gather_data(&pars, av))
		printf("Error collecting atributes\n");
    print_parsing(&pars);
}
