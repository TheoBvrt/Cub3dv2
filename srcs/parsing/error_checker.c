#include "cube.h"

int	check_map_file(char *map_path)
{
	int	i;

	i = ft_strlen(map_path);
	if (i <= 4)
	{
		ft_printf("Map format error !\n");
		return (0);
	}
	if (!(map_path[i - 1] == 'b'
		&& map_path[i - 2] == 'u'
		&& map_path[i - 3] == 'c'
		&& map_path[i - 4] == '.'))
	{
		ft_printf("Map format error !\n");
		return (0);
	}
	return (1);
}