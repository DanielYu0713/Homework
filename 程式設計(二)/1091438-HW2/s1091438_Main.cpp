#include <iostream>
#include <stdlib.h> //srand(), rand()
#include <time.h> 
#include "s1091438_Container.h"
using namespace std;
int main() {
	int randomSeed;
	cout << "Input random seed: ";
	cin >> randomSeed;
	srand(randomSeed);
	int randomSize = rand() % 5 + 1;
	cout << "Allocate " << randomSize << " slots" << endl;  //random size 1~5
	Container con(randomSize);
	int plays = rand() % 6 + 15;
	for (int i = 0; i < plays; i++) {// 15-20 plays
		int test = rand() % 3 + 1;//pop(),push(),resize()
		if (test == 1){
			randomSize = rand() % 10 + 1;//Container內容 1~10整數
			cout << "Push " << randomSize << endl;
			con.push(randomSize);
		}
		else if (test == 2){
			cout << "Pop" << endl;
			con.pop();
		}
		else if (test == 3){
			randomSize = rand() % 10 + 1;//Container內容 1~10整數
			cout << "Resize to " << randomSize<<" slots "<< endl;
			con.resize(randomSize);
		}
		con.printALL();
	}
	Container A(3), B(5);
	cin >> A >> B;
	cout << A << B << A + B;
	cout << (A = A + 3);
	Container C = A + B;
	cout << C;
	C = A + C + B;
	cout << C + 4;
	cout << Container::cat(A, B);
}