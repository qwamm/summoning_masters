#include <iostream>
#include "headers/simple_class.h"

using namespace simple_class;

int invite();
int D_Init (Dice &d);
int D_Random_Value (Dice &d);
int D_Generation_based_on_probabilities (Dice &d);
int D_Art (Dice &d);
int D_Print (Dice &d);
int D_Compare (Dice &a, Dice &b);

int (*f[])(Dice&) = {NULL, D_Init, D_Random_Value, D_Generation_based_on_probabilities, D_Art, D_Print};

int main()
{
    srand(time(nullptr));
    int rc;
    Dice d = 5;
    D_Print(d);
    while (rc = invite())
    {
		if (rc == 5)
		{
			Dice second;
			second.set_state(std::cin, std::cout);
			D_Compare(d, second) == 1 ? std::cout<<"Dices are equal\n" : std::cout<<"Dices aren't equal\n";
		}
		else
		{
			if (rc == 6)
				rc--;
			/*if (rc == 2)
			{
				d.~Dice();
				Dice x;
				d = x;
				D_Print(d);
			}*/
			if (!f[rc](d))
			{
                		break;
			}
		}
    }
    //D_Print(d);
    std::cout<<"That's all. Good luck!\n";
}

int D_Compare (Dice &a, Dice &b)
{
		return a==b ? 1 : 0;
}

int D_Art (Dice &d)
{
	std::string res = d.ascii_art();
	for (int i=0; i < res.length(); i++)
	{
		if (i>=9 && i%9 == 0)
		{
			std :: cout << "\n";
		}
			std :: cout << res[i];
	}
	std::cout << "\n";
	return 1;
}

int D_Print (Dice &d)
{
	d.print(std::cout);
	return 1;
}

int D_Generation_based_on_probabilities (Dice &d)
{
	d.generate_random_value();
	return 1;
}

int D_Random_Value (Dice &d)
{
	Dice x;
	d.set_val(x.get_val());
	for (int i=0; i<6; i++)
	{
		d.set_probability_of_dropping(1.0 / 6.0, i+1);
	}
	return 1;
}

int D_Init (Dice &d)
{
	d.set_state(std::cin, std::cout);
	return 1;
}

int invite()
{
        std::cout << "Select one option:\n";
        std::cout << " 0. Quit\n";
        std::cout << " 1. Initialization with the side dropped out and probabilities of dropping sides:\n";
        std::cout << " 2. Initialization with the random side\n";
        std::cout << " 3. Generating a random value for a dice based on probability\n";
        std::cout << " 4. ASCII-art\n";
        std::cout << " 5. Compare two dices\n";
	std::cout << " 6. Print\n";

	int rc;
        rc = getNum<int>(std::cin, std::cout, 0,6);
        return rc;
}
