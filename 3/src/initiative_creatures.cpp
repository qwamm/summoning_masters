#include "include/classes.hpp"

void initiative_creatures::move_to_cell(char d)
{
	if (d == 'u')
	{
		(coordinats.second)++;
	}
	else if (d == 'd')
	{
		(coordinats.second)--;
	}
	else if (d == 'l')
	{
		(coordinats.first)--;
	}
	else if (d == 'r')
	{
		(coordinats.first)++;
	}
}
