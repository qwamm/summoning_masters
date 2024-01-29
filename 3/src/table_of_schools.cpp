#include "include/classes.hpp"

#include <unordered_map>

void Table_of_schools::add_school(School &obj)
{
         schools.insert({obj.get_name(), obj});
}

void Table_of_schools::add_skill(std::string school_name, Skill &s)
{
        schools[school_name].add_skill(s);
}

void Table_of_schools::change_creature(std::string school_name, std::string creature_name, Skill &obj)
{
	if (schools.contains(school_name))
	{
		schools[school_name].change_creature(creature_name, obj);
	}
}

Skill& Table_of_schools::get_creature(std::string school_name, std::string skill_name)
{
       if (schools.contains(school_name))
       {
		try
		{
			schools[school_name].find_creature(skill_name);
		}
		catch(...)
		{
			throw;
		}
		Skill &s = schools[school_name].find_creature(skill_name);
		return s;
       }
       else
       {
		throw std::invalid_argument("table of schools doesn't contains given school name");
       }
}

int Table_of_schools::get_num_of_creatures(std::string school_name)
{
         if (schools.contains(school_name))
         {
                 return schools[school_name].get_num_of_creatures();
         }
         return -1;
}
