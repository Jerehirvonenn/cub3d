#include "parsing.h"

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
