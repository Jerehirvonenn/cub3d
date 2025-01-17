#include "parsing.h"

void	free_close(t_parsing *pars, char *s, char *free_str)
{
	if (s)
		ft_putstr_fd(s, 2);
	if (pars->fd > 0)
		close(pars->fd);
	free(free_str);
	exit(1);
}

void	free_array(char ***array)
{
	int	i;

	if (!array || !*array)
		return ;
	i = 0;
	while ((*array)[i])
	{
		free((*array)[i]);
		i++;
	}
	free(*array);
	*array = NULL;
}

void	free_and_null(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

void	parse_clean_exit(t_parsing *parse, int exit_code, char *str)
{
	int	i;

	i = 0;
	free_and_null(&parse->north);
	free_and_null(&parse->south);
	free_and_null(&parse->west);
	free_and_null(&parse->east);
	if (parse->map)
	{
		while (parse->map[i])
			free_and_null(&parse->map[i++]);
		free(parse->map);
	}
	i = 0;
	if (parse->norm_map)
	{
		while (parse->norm_map[i])
			free_and_null(&parse->norm_map[i++]);
		free(parse->norm_map);
	}
	if (str)
		ft_putstr_fd(str, 2);
	if (exit_code != 0)
		exit(exit_code);
}
