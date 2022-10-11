#pragma once
#include<iostream>
#include<vector>
#include<string>



class Animal {
public:
	Animal(std::string inName, int inEnergy = 100);
	virtual int feed(int amount) {
		return hungry;
	}; //傳入消耗量，回傳飢餓度
	virtual int exercise(int times) {
		return 1;
	}; //傳入次數，回傳所賺的錢
	virtual int rest(int &food, int &water) {
		return hungry;
	}; //需要傳入一些資訊方便你調整動物園食物量 水量...
	virtual int drink(int amount) {
		return 1;
	};
	virtual void print();
protected:
	std::string Name;
	int hungry;	//hungry index (initial = 0, upper bound is varying)
	int energy; //energy index (initial = 100)
};

class Zoo {
	friend std::ostream& operator<<(std::ostream& output, Zoo& z);
public:
	Zoo(size_t size = 5) : foodCount(500), waterCount(100), deposit(100), sizeLimit(size) {};
	~Zoo();
	int Run(int quantity = 1);
	bool FeedFood(int quantity = 1);
	bool FeedWater(int quantity = 1);
	bool AskRest();
	void Listing();
	bool AddAnimal(Animal* inPtr);
	int getCount();
	bool isBankrupt();
	int getMoreFood(int amount);
	Zoo& operator+= (Animal* inPtr);
	Animal* operator[] (size_t pos);
	


private:
	std::vector<Animal*> house;
	int foodCount; //動物園食物 沒食物可以用存款轉換
	int waterCount; //動物園水 每RUN會增加100;
	int deposit; //動物園存款 動物運動可增加
	const int sizeLimit; //動物園設計上限(初次創建時設定)可超過但追加動物會警告
};

class Horse:public Animal {
public:
	Horse(std::string inName, int inEnergy = 100);
	int feed(int amount); //傳入消耗量，回傳飢餓度
	int exercise(int times); //傳入次數，回傳所賺的錢
	int rest(int &food, int &water); //需要傳入一些資訊方便你調整動物園食物量 水量...
	int drink(int amount);
};
class Pig :public Animal {
public:
	Pig(std::string inName, int inEnergy = 100);
	int feed(int amount); //傳入消耗量，回傳飢餓度
	int exercise(int times); //傳入次數，回傳所賺的錢
	int rest(int &food, int &water); //需要傳入一些資訊方便你調整動物園食物量 水量...
	int drink(int amount);
};
class Human :public Animal {
public:
	Human(std::string inName, int inEnergy = 100);
	int feed(int amount); //傳入消耗量，回傳飢餓度
	int exercise(int times); //傳入次數，回傳所賺的錢
	int rest(int &food, int &water); //需要傳入一些資訊方便你調整動物園食物量 水量...
	int drink(int amount);
};