#include "parsing.h"
#include <string.h>

char *grow_buffer(char *old_buffer, int old_size, int new_size)
{
	char *new_buffer;
	int	  i;

	new_buffer = malloc(new_size);
	if (!new_buffer)
	{
		perror("Memory allocation failed");
		free(old_buffer); // Free the old buffer to prevent memory leaks, need
		exit(1);
	}
	i = 0;
	while (i < old_size)
	{
		new_buffer[i] = old_buffer[i];
		i++;
	}
	new_buffer[i] = 0;
	free(old_buffer);
	return new_buffer;
}

void read_file(t_parsing *pars)
{
	char buffer[BUFFER_SIZE + 1];
	int	 b_read;
	int	 size;
	int	 capacity;

	capacity = BUFFER_SIZE + 1;
	size = 0;
	pars->cont = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!pars->cont)
		exit(1); // protect
	pars->cont[0] = 0;
	b_read = read(pars->fd, buffer, BUFFER_SIZE);
	buffer[b_read] = 0;
	while (b_read > 0)
	{
		if (size + b_read >= capacity)
		{
			capacity *= 2;
			pars->cont = grow_buffer(pars->cont, size, capacity);
		}
		for (ssize_t i = 0; i < b_read; i++)
			pars->cont[size++] = buffer[i];
		b_read = read(pars->fd, buffer, BUFFER_SIZE);
		buffer[b_read] = 0;
	}
	if (b_read < 0)
	{
		ft_putstr_fd("Error\nError while reading file", 2);
		free(pars->cont);
		close(pars->fd);
		exit(EXIT_FAILURE);
	}
	close(pars->fd);
	pars->cont[size] = 0;
	printf("%s", pars->cont);
}

void validate_file(t_parsing *pars)
{
	pars->fd = open(pars->file, O_RDONLY);
	if (pars->fd < 0)
	{
		ft_putstr_fd("Error\nCannot open provided file\n", 2);
		exit(1);
	}
	read_file(pars);
	pars->map = ft_split(pars->cont, '\n');
	free(pars->cont);
	if (!pars->map)
		exit(1); // message
	printf("\nAFTER SPLIT\n");
	for (int i = 0; pars->map[i]; i++)
		printf("%s\n", pars->map[i]);
}

void parse_file(t_parsing *pars)
{
    validate_file(pars);
    gather_data(pars, pars->map);
    if (!validate_map(pars, pars->map + pars->map_start))
		printf("Map validation Failed\n");
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
		ft_putstr_fd("Error\nUsage: ./cub3d <example.cub>", 2);
		return (1);
	}
    init_pars_struct(&pars, av[1]);
	pars.file = av[1];
	parse_file(&pars);
}
