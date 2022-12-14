#include <iostream>
#include "s1091438_zoo_stu.h"
using namespace std;

int main()
{
	std::cout << "Hello World!\n";
	Zoo ZooSim1(5);

	ZooSim1.AddAnimal(new Horse("Pony", 100));
	ZooSim1.AddAnimal(new Pig("Piggy", 100));
	ZooSim1.AddAnimal(new Human("Pony", 100));
	ZooSim1 += new Pig("Piggy", 100);

	ZooSim1.Listing();
	std::cout << "==================================\n";
	//...example...
	//std::cout << ZooSim1 << std::endl;
	//ZooSim1.Run(3);
	//std::cout << "==================================\n";
	//std::cout << "---Test getMorefood()--- \n";
	//std::cout << "Before:  "<< ZooSim1 << std::endl;
	//ZooSim1.getMoreFood(100);
	//std::cout << "After:  " << ZooSim1 << std::endl;
	//ZooSim1.getMoreFood(500);
	//std::cout << "==================================\n";
	//std::cout << "---Test food/water Insufficient--- \n";
	//ZooSim1.Listing();
	//while (ZooSim1.FeedFood(10)) {}
	//while (ZooSim1.FeedWater(20)) {}
	//ZooSim1.Listing();
	//...

	while (!ZooSim1.isBankrupt())
	{
		std::cout << ZooSim1 << std::endl;
		ZooSim1.Run();
	}
}