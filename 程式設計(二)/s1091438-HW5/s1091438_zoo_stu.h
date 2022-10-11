#pragma once
#include<iostream>
#include<vector>
#include<string>



class Animal {
public:
	Animal(std::string inName, int inEnergy = 100);
	virtual int feed(int amount) {
		return hungry;
	}; //�ǤJ���Ӷq�A�^�ǰ��j��
	virtual int exercise(int times) {
		return 1;
	}; //�ǤJ���ơA�^�ǩ��Ȫ���
	virtual int rest(int &food, int &water) {
		return hungry;
	}; //�ݭn�ǤJ�@�Ǹ�T��K�A�վ�ʪ��魹���q ���q...
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
	int foodCount; //�ʪ��魹�� �S�����i�H�Φs���ഫ
	int waterCount; //�ʪ���� �CRUN�|�W�[100;
	int deposit; //�ʪ���s�� �ʪ��B�ʥi�W�[
	const int sizeLimit; //�ʪ���]�p�W��(�즸�Ыخɳ]�w)�i�W�L���l�[�ʪ��|ĵ�i
};

class Horse:public Animal {
public:
	Horse(std::string inName, int inEnergy = 100);
	int feed(int amount); //�ǤJ���Ӷq�A�^�ǰ��j��
	int exercise(int times); //�ǤJ���ơA�^�ǩ��Ȫ���
	int rest(int &food, int &water); //�ݭn�ǤJ�@�Ǹ�T��K�A�վ�ʪ��魹���q ���q...
	int drink(int amount);
};
class Pig :public Animal {
public:
	Pig(std::string inName, int inEnergy = 100);
	int feed(int amount); //�ǤJ���Ӷq�A�^�ǰ��j��
	int exercise(int times); //�ǤJ���ơA�^�ǩ��Ȫ���
	int rest(int &food, int &water); //�ݭn�ǤJ�@�Ǹ�T��K�A�վ�ʪ��魹���q ���q...
	int drink(int amount);
};
class Human :public Animal {
public:
	Human(std::string inName, int inEnergy = 100);
	int feed(int amount); //�ǤJ���Ӷq�A�^�ǰ��j��
	int exercise(int times); //�ǤJ���ơA�^�ǩ��Ȫ���
	int rest(int &food, int &water); //�ݭn�ǤJ�@�Ǹ�T��K�A�վ�ʪ��魹���q ���q...
	int drink(int amount);
};