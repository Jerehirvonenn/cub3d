#include "parsing.h"

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

void parse_clean_exit(t_parsing *parse, int exit_code, char *str)
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
    if (str)
        ft_putstr_fd(str, 2);
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
		parse_clean_exit(parse, 1, "Error\nDuplicate color in assignment\n");
	while (str[i])
	{
		if (index == 3)
			parse_clean_exit(parse, 1, "Error\nToo many colors assigned\n");
		color[index++] = ft_atoi_color(str, &i);
		if (color[index - 1] == -1)
			parse_clean_exit(parse, 1, "Error\nToo many colors assigned\n");
		while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			i++;
		if (str[i] == ',')
			i++;
	}
	if (index != 3)
		parse_clean_exit(parse, 1, "Error\nInvalid number of color values\n");
}

char *ft_strdup_trim(char *s)
{
    int start;
    int end;
    char *result;
    int len;

    start = 0;
    while (s[start] && s[start] == ' ')
        start++;
    end = ft_strlen(s) - 1;
    while (end > start && s[end] == ' ')
        end--;
    if (end >= start)
        len = end - start + 1;
    else
        len = 0; // maybe just insta quit?
    result = (char *)malloc(len + 1);
    if (!result)
        return (NULL);
    len = 0;
    while (start <= end)
        result[len++] = s[start++];
    result[len] = 0;

    return (result);
}

void check_and_set_texture(char **texture, char *value, t_parsing *pars)
{
	if (*texture)
		parse_clean_exit(pars, 1, "Error\nDuplicate texture assignment\n");
	*texture = ft_strdup_trim(value);
	if (!*texture)
		parse_clean_exit(pars, 1, "Error\nMalloc failure\n");
}

void check_str(char *str, t_parsing *pars)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (ft_strlen(str + i) == 0)
		return;
	if (ft_strncmp(str + i, "NO ", 3) == 0)
		check_and_set_texture(&pars->north, str + i + 3, pars);
	else if (ft_strncmp(str + i, "SO ", 3) == 0)
		check_and_set_texture(&pars->south, str + i + 3, pars);
	else if (ft_strncmp(str + i, "WE ", 3) == 0)
		check_and_set_texture(&pars->west, str + i + 3, pars);
	else if (ft_strncmp(str + i, "EA ", 3) == 0)
		check_and_set_texture(&pars->east, str + i + 3, pars);
	else if (str[i] == 'F' && str[i + 1] == ' ')
		parse_color(str + i + 2, pars->floor, pars);
	else if (str[i] == 'C' && str[i + 1] == ' ')
		parse_color(str + i + 2, pars->ceiling, pars);
	else
		parse_clean_exit(pars, 1, "Error\nInvalid identifier encoutnered\n");
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
		while (map[i][j] == ' ')
			j++;
		if (map[i][j])
			return i;
		i++;
	}
	parse_clean_exit(pars, 1, "Error\nNo possible map to check\n");
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
	parse_clean_exit(pars, 1, "Error\nNot all needed data available in file\n");
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

	printf("Map:\n")\n;
	if (parsing->map)
		for (int i = 0; parsing->map[i]; i++)
			printf("  %s\n", parsing->map[i]);
	else
		printf("Map is not set.\n");
}

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
