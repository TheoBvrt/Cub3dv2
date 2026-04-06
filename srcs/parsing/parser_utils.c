#include "cube.h"

int	get_file_size(char *map_path)
{
	char	*line;
	int		fd;
	int		size;

	size = 0;
	fd = open(map_path, O_RDONLY);
	if (fd == -1 || fd == 0)
		return (0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		free (line);
		line = get_next_line(fd);
		size ++;
	}
	close(fd);
	return (size);
}