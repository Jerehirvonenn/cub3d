#include "parsing.h"

char	*grow_buffer(char *old, int len, int new_size, t_parsing *pars)
{
	char	*new_buffer;
	int		i;

	new_buffer = malloc(new_size);
	if (!new_buffer)
	{
		perror("Memory allocation failed");
		close(pars->fd);
		free(old);
		exit(1);
	}
	i = 0;
	while (i < len)
	{
		new_buffer[i] = old[i];
		i++;
	}
	new_buffer[i] = 0;
	free(old);
	return (new_buffer);
}

void	read_file(t_parsing *pars)
{
	char	buffer[BUFFER_SIZE + 1];
	int		b_read;
	int		size;
	int		capacity;

	capacity = BUFFER_SIZE + 1;
	size = 0;
	pars->cont = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!pars->cont)
		free_close(pars, "Error\nMalloc failure\n", NULL);
	pars->cont[0] = 0;
	b_read = read(pars->fd, buffer, BUFFER_SIZE);
	buffer[b_read] = 0;
	while (b_read > 0)
	{
		if (size + b_read >= capacity)
		{
			capacity *= 2;
			pars->cont = grow_buffer(pars->cont, size, capacity, pars);
		}
		for (ssize_t i = 0; i < b_read; i++)
			pars->cont[size++] = buffer[i];
		b_read = read(pars->fd, buffer, BUFFER_SIZE);
		buffer[b_read] = 0;
	}
	if (b_read < 0)
		free_close(pars, "Error\nError while reading file\n", pars->cont);
	close(pars->fd);
	pars->cont[size] = 0;
	printf("Map in string form\n%s", pars->cont);
}

void	validate_file(t_parsing *pars)
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
