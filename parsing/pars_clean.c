#include "parsing.h"

void free_array(char ***array)
{
	int i;

	if (!array || !*array)
		return;
	i = 0;
	while ((*array)[i])
	{
		free((*array)[i]);
		i++;
	}
	free(*array);
	*array = NULL;
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
	if (parse->norm_map)
	{
		for (int i = 0; parse->norm_map[i]; i++)
			free_and_null(&parse->norm_map[i]);
		free(parse->norm_map);
		parse->map = NULL;
	}
	if (str)
		ft_putstr_fd(str, 2);
	if (exit_code != 0)
		exit(exit_code);
}
