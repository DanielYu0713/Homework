//Prog 3 1091438 ­§®fÞ³ 
#include <pthread.h>
#include <iostream>

#include <stdio.h>  //random
#include <time.h>   //random
#include <math.h>   //pow
#include <algorithm> // for sort
using namespace std;

bool aircraft[4] = {false,true,false,false};   //Dispatcher,Producer 1~3
bool propeller[4] = {false,false,false,false};
bool battery[4] = {false,false,false,false};
bool gate[3] = {true,true,true}; // To check every Producer has seen the platform
int drones[3] = {0,0,0};         //Producer 1~3
int item[3] ={0,0,0}; // The total number of items produced , sequence => aircraft,propeller,battery
int randomseed = 0;
int alldrone = 0; // The count of drone(S)


pthread_mutex_t lock;

void* Producer(void *arg){   //P1
	while(true){

 	pthread_mutex_lock(&lock);

 	if(alldrone >= 50){
 		pthread_mutex_unlock(&lock);
 		break;
 	}
 
 	string str = (string)(char *)arg;
 
 	int count;
 	if(str == "Producer 1 (aircraft):"){
 		count = 1;
 	}
 	else if(str == "Producer 2:"){
 		count = 2;
 	}
 	else if(str == "Producer 3:"){
 		count = 3;
 	}
 	gate[count-1] = true;
	if(aircraft[0] && !propeller[0] && !battery[0]){
		if(!aircraft[count] && count != 1){
				aircraft[count] = true;
				aircraft[0] = false;
				cout<<str<<" get aircraft"<<endl;
		}
		
		
	}// Platform have aircraft,Producer 1 have aircraft forever
	else if(!aircraft[0] && propeller[0] && !battery[0]){
		if(!propeller[count]){
				propeller[count] = true;
				propeller[0] = false;
				cout<<str<<" get propeller"<<endl;
		}
	
	}// Platform have propeller
	else if(!aircraft[0] && !propeller[0] && battery[0]){
		if(!battery[count]){
				battery[count] = true;
				battery[0] = false;
				cout<<str<<" get battery"<<endl;
		}
	
	}// Platform have battery
	else if(!aircraft[0] && propeller[0] && battery[0]){
		if(!propeller[count]){
			propeller[count] = true;
			propeller[0] = false;
			cout<<str<<" get propeller"<<endl;
		}
		else if (!battery[count]){
			battery[count] = true;
			battery[0] = false;
			cout<<str<<" get battery"<<endl;
		}
		
	}// Platform have propeller and battery	
	else if(aircraft[0] && !propeller[0] && battery[0]){
		if(!aircraft[count] && count!=1){
			aircraft[count] = true;
			aircraft[0] = false;
			cout<<str<<" get aircraft"<<endl;
		}
		else if (!battery[count]){
			battery[count] = true;
			battery[0] = false;
			cout<<str<<" get battery"<<endl;
		}
		
	}// Platform have aircraft and battery	
	else if(aircraft[0] && propeller[0] && !battery[0]){
		
		if(!aircraft[count] && count!=1){
			aircraft[count] = true;
			aircraft[0] = false;
			cout<<str<<" get aircraft"<<endl;
		}
		else if (!propeller[count]){
			propeller[count] = true;
			propeller[0] = false;
			cout<<str<<" get propeller"<<endl;
		}
		
	}// Platform have aircraft and propeller
	else if(aircraft[0] && propeller[0] && battery[0]){
		if(!aircraft[count] && count!=1){
			aircraft[count] = true;
			aircraft[0] = false;
			cout<<str<<" get aircraft"<<endl;
		}
		else if (!propeller[count]){
			propeller[count] = true;
			propeller[0] = false;
			cout<<str<<" get propeller"<<endl;
		}
		else if (!battery[count]){
			battery[2] = true;
			battery[0] = false;
			cout<<str<<" get battery"<<endl;
		}
		
		
	}// Platform have all items
	
	if(aircraft[count] && propeller[count] && battery[count]){
		if(count!=1){
		     aircraft[count] = false;
		}
		propeller[count]  = false;
		battery[count] = false;
		drones[--count]++;
		alldrone++;
		cout<<str<<" OK, "<<drones[count]<<" drone(s)"<<endl;	
	}
	pthread_mutex_unlock(&lock);

	}
	return NULL;
	
}

void* Dispatcher(void *arg){ // P0
	srand((unsigned)time(NULL)^randomseed);
	while(true){

	pthread_mutex_lock(&lock);

	if(alldrone >= 50){
 		pthread_mutex_unlock(&lock);
 		break;
 	}
 	
 	if(!gate[0] || !gate[1] || !gate[2]){
 		pthread_mutex_unlock(&lock);
 		continue; // back to while(True)
 	}
 	
	if(!aircraft[0] && !propeller[0] && !battery[0]){
		int ran = rand() % 3;
		switch(ran){
			case 0:
				aircraft[0] = true;
				item[0]++;
				cout<<(char *)arg<<" aircraft"<<endl;
				break;
			case 1:
				propeller[0] = true;
				item[1]++;
				cout<<(char *)arg<<" propeller"<<endl;
				break;
			case 2:
				battery[0] = true;
				item[2]++;
				cout<<(char *)arg<<" battery"<<endl;
				break;
		}	  
	} // All three objects are off the platform
	else if(aircraft[0] && !propeller[0] && !battery[0]){
		int ran = rand() % 2;
		switch(ran){
			case 0:
				propeller[0] = true;
				item[1]++;
				cout<<(char *)arg<<" propeller"<<endl;
				break;
			case 1:
				battery[0] = true;
				item[2]++;
				cout<<(char *)arg<<" battery"<<endl;
				break;
		}
	}// Platform have aircraft
	else if(!aircraft[0] && propeller[0] && !battery[0]){
		int ran = rand() % 2;
		switch(ran){
			case 0:
				aircraft[0] = true;
				item[0]++;
				cout<<(char *)arg<<" aircraft"<<endl;
				break;
			case 1:
				battery[0] = true;
				item[2]++;
				cout<<(char *)arg<<" battery"<<endl;
				break;
		}
	}// Platform have propeller
	else if(!aircraft[0] && !propeller[0] && battery[0]){
		int ran = rand() % 2;
		switch(ran){
			case 0:
				aircraft[0] = true;
				item[0]++;
				cout<<(char *)arg<<" aircraft"<<endl;
				break;
			case 1:
				propeller[0] = true;
				item[1]++;
				cout<<(char *)arg<<" propeller"<<endl;
				break;
		}
	}// Platform have battery
	else if(!aircraft[0] && propeller[0] && battery[0]){
		aircraft[0] = true;
		item[0]++;
		cout<<(char *)arg<<" aircraft"<<endl;
	}// Platform have propeller and battery	
	else if(aircraft[0] && !propeller[0] && battery[0]){
		propeller[0] = true;
		item[1]++;
		cout<<(char *)arg<<" propeller"<<endl;
	}// Platform have aircraft and battery	
	else if(aircraft[0] && propeller[0] && !battery[0]){
		battery[0] = true;
		item[2]++;
		cout<<(char *)arg<<" battery"<<endl;
	}// Platform have aircraft and propeller

	gate[0] = false;
	gate[1] = false;
	gate[2] = false;

	pthread_mutex_unlock(&lock);

	}
	return NULL;
}

int main(int argc,char *argv[]){
	//argv[1] , basic mode
	pthread_t tid[4];
	if(pthread_mutex_init(&lock,NULL)!=0){
		cout<<"mutex init failed"<<endl;
		return 1;
	}
	string str = argv[2]; //randomseed
	int tmp2 = str.size() - 1;
        for(int i = 0;i <= tmp2;i++){
        	int tmp1 = str[i] - '0';        	
        	randomseed = randomseed + tmp1 * pow(10,tmp2);
        	tmp2--;
        }
      
  	if(*argv[1] == '0'){
		//Create the thread:Producer1~3 and Dispatcher
		pthread_create(&(tid[0]),NULL,&Dispatcher,(void *)"Dispatcher:");
		pthread_create(&(tid[1]),NULL,&Producer,(void *)"Producer 1 (aircraft):");
		pthread_create(&(tid[2]),NULL,&Producer,(void *)"Producer 2:");
		pthread_create(&(tid[3]),NULL,&Producer,(void *)"Producer 3:");
 
	
		pthread_join(tid[0],NULL);
		pthread_join(tid[1],NULL);
		pthread_join(tid[2],NULL);
		pthread_join(tid[3],NULL);

		while(true){
			if(alldrone >= 50){
				cout<<"50 drones have been completed!!"<<endl<<endl;
				cout<<"How many different module accessories are Dispatcher prepared ?"<<endl;
				cout<<"Aircraft: "<<item[0]<<", Propeller: "<<item[1]<<" , Battery: "<<item[2]<<endl;
				int compare[3] = {drones[0],drones[1],drones[2]};
				sort(compare,compare+3,greater<int>());  //sorting,from big to small
				int output = 0;
				bool outputjudge[3] = {false,false,false};
				while(output != 3){
					for(int i = 0; i < 3; i++){
						if(drones[i] == compare[output] && outputjudge[i] == false){
							cout<<"Producer "<< i+1;
							if(i == 0){
								cout<<" (aircraft): ";
							}
							else{
								cout<<": ";
							}
							cout<<drones[i]<<" drone(s)"<<endl;
							outputjudge[i] = true;
						}
						
					}
					output++;
				}
				break;
			}
		}
		pthread_mutex_destroy(&lock);
	}
	else{
		cout<<"Advanced mode are not made"<<endl;
	}
	return 0;
}


