#include<iostream>
#include<vector>
#include<string>
using namespace std;
#include "s1091438_zoo_stu.h"

ostream& operator<< (ostream& output, Zoo& z) {
	output << "[INFO] Food: " << z.foodCount << ", Water: " << z.waterCount << ", Fund$: " << z.deposit << "$";
	return output;
}

int Zoo::Run(int quantity ) {
	int amount = 0;
	for (int i = 0; i < quantity; i++) {
		cout << "Before exercise..." << endl;
		Listing();
		for (vector<Animal*>::iterator iter = house.begin(); iter != house.end(); ++iter) {
			int tmp =(*iter)->exercise(1);
			if (tmp == 0) { //當此動物產能($$)為0時,餵他食物和水,讓他減少飢餓度以及獲得能量
				FeedWater(1);
				FeedFood(1);
			}
			else {
				amount += tmp;
			}

		}
		getMoreFood(100);//避免之後餵到一半時沒食物的窘境,每運動完1輪就去買一次食物
		AskRest();
		Listing();
		cout << "After Exercise..." << endl;
	}
	waterCount += 100;
	deposit += amount;
	return deposit;
}
Zoo::~Zoo() {
	house.clear();
}
bool Zoo::FeedFood(int quantity) {
	std::cout << "[LOG] Feeding food...\n";
	int feeds = 0;
	for (int i = 0; i < quantity; i++) {
		for (std::vector<Animal*>::iterator iter = house.begin(); iter != house.end(); ++iter) {
			if (foodCount > feeds) {
				(*iter)->feed(50);
				feeds += (quantity * 50);
				foodCount -= (quantity * 50);
			}
			else {
				cout << "[WARNING] Insufficient food !!!\n";
				return false;
			}
		}
	}
	cout << "[LOG] total consume " << feeds << " food.\n";
	return true;
}
bool Zoo::FeedWater(int quantity) {
	std::cout << "[LOG] Feeding water...\n";
	int feeds = 0;
	for (int i = 0; i < quantity; i++) {
		for (std::vector<Animal*>::iterator iter = house.begin(); iter != house.end(); ++iter) {
			if (waterCount > feeds) {
				(*iter)->drink(50);
				feeds += (quantity * 50);
				waterCount -= (quantity * 50);
			}
			else {
				std::cout << "[WARNING] Insufficient water !!!\n";
				return false;
			}
		}
	}
	cout << "[LOG] total consume " << feeds << " water.\n";
	return true;
}
bool Zoo::AskRest() {
	std::cout << "[LOG] ask all animals to rest.\n";
	for (std::vector<Animal*>::iterator iter = house.begin(); iter != house.end(); ++iter) {
		(*iter)->rest(foodCount, waterCount);
	}
	return true;
}
void Zoo::Listing() { //印出所有動物資訊
	for (std::vector<Animal*>::iterator iter = house.begin(); iter != house.end(); ++iter) {
		(*iter)->print();
	}
}
bool Zoo::AddAnimal(Animal* inPtr) {
	house.push_back(inPtr);
	if (house.size() >= sizeLimit + 1) {
		cout << "[WARNING] Too many animals !!!" << endl;
	}
	return true;
}
int Zoo::getCount() { 
	return house.size(); 
}
bool Zoo::isBankrupt() {
	if (foodCount == 0 && deposit == 0) {
		return true;
	}

	else {
		return false;
	}
}
Zoo& Zoo::operator+= (Animal* inPtr) {
	this->AddAnimal(inPtr);
	return *this;
}

Animal* Zoo::operator[] (size_t pos){
	return house[pos];
}

int Zoo::getMoreFood(int amount) { //try to buy food
	int gain;
	if (deposit >= amount) {
		gain = amount * 2;
		deposit -= amount;
	}
	else {
		gain = deposit * 2;
		deposit = 0;
		cout << "[WARNING] Insufficient funds !!!" << endl;
	}
	cout << "[LOG] Transfer $" << amount << " to " << gain << " food" << endl;
	foodCount += gain;
	return gain;
}


Animal::Animal(string inName, int inEnergy)
	: Name(inName), hungry(0), energy(inEnergy) {};
void Animal::print() {
	std::cout << Name << " (hungry: " << hungry << ", energy : " << energy << ")" << std::endl;
}
Horse::Horse(string inName, int inEnergy) :Animal(inName, inEnergy){
	hungry = 0;
};
int Horse::feed(int amount) {
	cout << "[LOG] " << Name << " eat " << amount << " food" << endl;
	if (hungry - amount < 0) {
		hungry = 0;
	}
	else {
		energy += amount * 2;
		hungry -= amount;
	}
	return hungry;
}; 
int Horse::exercise(int times) {
	int earn = 0;
	if (energy > 0 && hungry < 100) {
			if ((hungry + times * 35) >= 100) {
				hungry = 100;
			}
			else {
				hungry += times * 35;
			}

			if (energy - times * 35 <= 0) {
				earn = earn + 50 * (energy / 35.0);
				energy = 0;
			}//依比例
			else {
				earn = times * 50;
				energy -= times * 35;
			}
			cout << "[LOG] " << Name << " do exercise and earn " << earn << "$" << endl;
	}
	else if (hungry >= 100 && energy > 0) {
		if (energy - times * 35 <= 0) {
			earn = earn + 25 * (energy / 35.0);
			energy = 0;
		}//依比例
		else {
			earn = times * 25;
			energy -= times * 50;
		}
		cout << "[LOG] " << Name << " do exercise and earn " << earn << "$" << endl;
	}
	else {
		cout << "[LOG] " << Name << " is Exhausted!!! " << endl;
	}
	return earn;
}; 
int Horse::rest(int &food, int &water) {
	if (water >= 10) {
		cout << "[LOG] " << Name << " take a rest, eat 0 food & drink 10 water, gain 10 energy" << endl;
		water -= 10;
		energy += 10;
		return 1;
	}
	else {
		return 0;
	}
};
int Horse::drink(int amount) {
	energy += amount;
	cout << "[LOG] " << Name << " drink " << amount << " water" << endl;
	return hungry;
};
Pig::Pig(string inName, int inEnergy) :Animal(inName, inEnergy) {
	hungry = 0;
};
int Pig::feed(int amount) {
	cout << "[LOG] " << Name << " eat " << amount << " food" << endl;
	hungry -= amount;
	if (hungry < 0) {
		energy += 2 * abs(hungry);
		hungry = 0;
	}
	return hungry;
}; //傳入消耗量，回傳飢餓度
int Pig::exercise(int times) {
	int earn = 0;
	if (energy > 0 && hungry < 50) {
		if (hungry + times * 20 >= 50) {
			hungry = 50;
		}
		else {
			hungry += times * 20;
		}

		if (energy - times * 35 <= 0) {
			earn = earn + 100 *(energy / 35.0);
		}
		else {
			energy -= times * 35;
			earn += (100 * times);
		}
		cout << "[LOG] " << Name << " do exercise and earn " << earn << "$" << endl;
	}
	else if (energy <= 0 && hungry<50) {
		cout << "[LOG] " << Name << " is Exhausted!!! " << endl;
	}
	else if (hungry >= 50 && energy > 0) {
		cout << "[LOG] " << Name << " is Hungry!!! " << endl;
	}
	else if (energy <= 0 && hungry >= 50) {
		cout << "[LOG] " << Name << " is Exhausted & Hungry!!!" << endl;
	}
	return earn;
}; //傳入次數，回傳所賺的錢
int Pig::rest(int &food, int &water) {
	if (food - 10 > 0) {
		cout << "[LOG] " << Name << " take a rest, eat 10 food & drink 0 water, gain 0 energy" << endl;
		food -= 10;
		return 1;
	}
	else {
		return 0;
	}
}; //需要傳入一些資訊方便你調整動物園食物量 水量...
int Pig::drink(int amount) {
	energy += amount;
	/*if (hungry - amount < 0) {
		hungry = 0;
	}
	else {
		hungry -= amount;
	}*/
	cout << "[LOG] "<<Name<<" drink "<<amount<<" water" << endl;
	return hungry;
};
Human::Human(string inName, int inEnergy) :Animal(inName, inEnergy) {
	hungry = 0;
};
int Human::feed(int amount) {
	energy = energy + amount - 10;
	hungry -= amount;
	if (hungry < 0) {
		hungry = 0;
	}
	cout << "[LOG] " << Name << " eat " << amount << " food" << endl;
	return hungry;
}; 
int Human::exercise(int times) {
	int earn = 0;
	if (energy > 0 && hungry < 150) {
		if ((hungry + times * 35) > 150) {
			hungry = 150;
		}
		else {
			hungry += times * 35;
		}
		
		if (energy - times * 35 <= 0) {
			earn = earn + 100 * (energy / 35.0);
			energy = 0;
		}//依比例
		else {
			energy -= times * 35;
			earn += (100 * times);
		}
	}
	else {
		if (energy == 0) {
			if (hungry == 150) {
				cout << "[LOG] " << Name << " is Exhausted & Hungry!!! " << endl;
			}
			else {
				cout << "[LOG] " << Name << " is Exhausted!!! " << endl;
			}
		}
		cout << "[LOG] " << Name << " is Hungry!!! " << endl;
	}
	return earn;
}; //做任何事情減少 10 energy??
int Human::rest(int &food, int &water) {
	if (food >= 10 && water >= 20) {
		food -= 10;
		water -= 20;
		energy += 10;
		cout << "[LOG] " << Name << " take a rest, eat 10 food & drink 20 water, gain 10 energy" << endl;
		return 1;
	}
	else {
		return 0;
	}
};
int Human::drink(int amount) {
	energy = energy + 2 * amount - 10;
	cout << "[LOG] " << Name << " drink " << amount << " water" << endl;
	return hungry;
};