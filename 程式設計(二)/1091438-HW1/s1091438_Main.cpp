#include<iostream>
#include <stdlib.h> //srand(), rand()
#include <time.h> 
#include "s1091438_Date.h"
#include "s1091438_Container.h"
using namespace std;
int main() {
	srand(time(NULL));
	int n = rand() % 9 + 2;
	Container vessel(n);
	for (int i = 1; i <= n; i++) {
		Date d;
		vessel.addDate(d);
	}
	vessel.printALL();
}