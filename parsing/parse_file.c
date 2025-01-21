/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhirvone <jhirvone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:51:52 by jhirvone          #+#    #+#             */
/*   Updated: 2025/01/20 13:27:06 by jhirvone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*grow_buffer(char *old, int len, int new_size, t_parsing *pars)
{
	char	*new_buffer;
	int		i;

	new_buffer = malloc(new_size);
	if (!new_buffer)
	{
		ft_putstr_fd("Error\nMalloc failure\n", 2);
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

void	ft_save_lines(t_parsing *pars, int *capacity, int *size)
{
	*capacity *= 2;
	pars->cont = grow_buffer(pars->cont, *size, *capacity, pars);
}

void	read_file(t_parsing *pars, int capacity, int size)
{
	char	buffer[BUFFER_SIZE + 1];
	int		b_read;
	int		i;

	pars->cont = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!pars->cont)
		free_close(pars, "Error\nMalloc failure\n", NULL);
	pars->cont[0] = 0;
	b_read = read(pars->fd, buffer, BUFFER_SIZE);
	while (b_read > 0)
	{
		buffer[b_read] = 0;
		if (size + b_read >= capacity)
			ft_save_lines(pars, &capacity, &size);
		i = -1;
		while (++i < b_read)
			pars->cont[size++] = buffer[i];
		b_read = read(pars->fd, buffer, BUFFER_SIZE);
	}
	if (b_read < 0)
		free_close(pars, "Error\nError while reading file\n", pars->cont);
	close(pars->fd);
	pars->cont[size] = 0;
}

void	check_file_name(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0 && str[i] != '.')
		i--;
	if (!ft_strncmp(str + i, ".cub", 5))
		return ;
	ft_putstr_fd("Error\nProvide .cub file\n", 2);
	exit(1);
}

void	validate_file(t_parsing *pars)
{
	int	capacity;
	int	size;

	capacity = BUFFER_SIZE + 1;
	size = 0;
	check_file_name(pars->file);
	pars->fd = open(pars->file, O_RDONLY);
	if (pars->fd < 0)
	{
		ft_putstr_fd("Error\nCannot open provided file\n", 2);
		exit(1);
	}
	read_file(pars, capacity, size);
	pars->map = ft_split(pars->cont, '\n');
	free(pars->cont);
	if (!pars->map)
	{
		ft_putstr_fd("Error\nMalloc failure\n", 2);
		exit(1);
	}
}
