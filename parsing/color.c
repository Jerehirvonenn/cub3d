#include "parsing.h"

static int	ft_atoi_color(const char *str, int *j, int position)
{
	int	i;
	int	result;

	result = -1;
	i = *j;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '\0')
		return (-1);
	if (str[i] >= '0' && str[i] <= '9')
		result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result > 255)
			return (-1);
		i++;
	}
	if (str[i] != '\0' && str[i] != ',' && str[i] != ' ')
		return (-1);
	if (str[i] == ',' && position == 2)
		return (-1);
	*j = i;
	return (result);
}

void	parse_color(char *str, int *color, t_parsing *parse)
{
	int	index;
	int	i;

	i = 0;
	index = 0;
	if (color[0] != -1)
		parse_clean_exit(parse, 1, "Error\nDuplicate color in assignment\n");
	while (str[i])
	{
		if (index == 3)
			parse_clean_exit(parse, 1, "Error\nToo many colors assigned\n");
		color[index] = ft_atoi_color(str, &i, index);
		index++;
		if (color[index - 1] == -1)
			parse_clean_exit(parse, 1, "Error\nInvalid color syntax\n");
		if (color[index - 1] == -2)
			parse_clean_exit(parse, 1, "Error\nInvalid color syntax\n");
		while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			i++;
		if (str[i] == ',')
			i++;
	}
	if (index != 3)
		parse_clean_exit(parse, 1, "Error\nInvalid number of color values\n");
}
