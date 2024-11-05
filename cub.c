#include "cub.h"

int main(int ac, char **av)
{
	if (ac != 2)
		return (write(2, "usage: ./cub3d map_in_format_*.cub", 34), 1);
	
	//void *paring_data;
	//char **map = parser(parsing_data); this
	//function will pars and set the data stored in the .cub file (av[1])
	char *test_map[] = {
		"111111111111111",
		"100000000000001",
		"101000111100001",
		"11P000000000001",
		"101010000010001",
		"111110111111101",
		"100000100000101",
		"100000001011101",
		"100011111110001",
		"100000000000001",
		"111111111111111",
		NULL
	};
	get_start(test_map);
}