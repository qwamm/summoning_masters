#include "include/classes.hpp"

bool Summoner::improve_school (std::string school_name)
{
	if (possession_of_schools.contains(school_name))
        {
		if (unspent_experience > 0)
		{
                	possession_of_schools[school_name] += unspent_experience;
			unspent_experience = 0;
			return true;
		}
		else
		{
			return false;
		}
        }
        else
        {
                throw std::invalid_argument("map doesn't consist this school name");
        }
}
