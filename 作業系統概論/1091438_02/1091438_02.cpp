// 1091438
#include<iostream>
#include<fstream>
#include <vector>
#include <string>
#include <map>
#include <pthread.h>
#include <unistd.h> // tid
#include <sys/types.h>  // tid
#include <math.h> //sqrt
#include <iomanip> //setprecision
#include <time.h> //clock

using namespace std;
// Global variable
map<string,int>words;
map<string,int>seq;
vector< vector<int> >fre_last; //the final ans of frequency 
vector <string> id;
vector <double> cos_aver; //The files's average_cosine
int wt = 0; //wait or run
int totalwords = 0;
pid_t tid;

void change(string &str,int size){
	for(int i = 0;i < size ; i++){
		if((str[i]<=57 && str[i]>=48) || (str[i]<=90 && str[i] >=65) || (str[i]<=122 && str[i] >= 97)){ //use ascii
		
		}
		else{
			str[i] = ' ';
		}
	}
	// Make everything except a-z,A-Z and 0-9 blank
	int count = 0;
	bool dele = false;
	for(int i = 0;i < size ; i++){
	     if(str[i] == ' ' || i == size - 1){ // Because the last word don't have blank,need a extra judgement(i == size -1)
	        int tmp = (i == size - 1) ? size : i; 
	   
	     	for(int j = count ; j < tmp; j++){
	     	    if(str[j]<=57 && str[j]>=48){ // if the word have 0-9,ignore this word (dele = true)
	     	    	dele = true;
	     	    	break;
	     	    }
	     	}
	     	if(dele){
	     		for(int j = count ; j < tmp; j++){
	     			str[j] = ' ';
	     		}
	     		dele = false; //initialize
	     	}
	     	count = i + 1; // the start of the next word
	     }
	}
} 

void frequency(string &str,int size){
	for(int i=0;i<size;i++){
		string word_tmp;
		while(str[i] != ' ' && i != size){
			word_tmp+=str[i];
			i++;
		}
		if(words.find(word_tmp)==words.end()){ //Don't find the word_tmp,the first time this word has ever appear
			totalwords++;
			seq[word_tmp] = totalwords;
			words[word_tmp] = 1;
		}
		else{
			words[word_tmp]++;
		}
	}
	int tmp = 1;
	vector<int>tmp_fre;
	while(tmp<=totalwords){
		for(map<string,int>::iterator it1 = seq.begin();it1 != seq.end();++it1){
			if(it1->second==tmp){
				tmp_fre.push_back(words[it1->first]);
				words[it1->first] = 0; //initialize
			}
		}
		tmp++;
	}
	fre_last.push_back(tmp_fre);
}

void *child(void *arg){
	double START,END;  //CPU Time
	START = clock();
	int n = *(int *)arg;
	tid = gettid();
        wt++;
        
	while(true){
  		if(wt == 2){
  			cout<<"[TID="<<tid<<"] DocID:"<<id[n]<<"["<<fre_last[n][0];
  			for(int i = 1;i <totalwords ; i++){
  				cout<<","<<fre_last[n][i];
  			}
  			cout<<"]"<<endl;
  			wt++;
 			break;
 		}
  	}

	double aver = 0.0;
  	for(long unsigned int i = 0; i <id.size();i++){
  		if(i != (long unsigned int)n){
  			int up = 0;
  			double down_left = 0.0,down_right = 0.0,sim = 0.0;
  			for(int j = 0 ; j < totalwords;j++){
  				up = up + fre_last[i][j]*fre_last[n][j]; 
  				down_left = down_left +fre_last[i][j]*fre_last[i][j]; //Vi
  				down_right = down_right + fre_last[n][j]*fre_last[n][j]; //Vs
  			}
			sim = up / (sqrt(down_left)*sqrt(down_right));
			cout<<"[TID="<<tid<<"] cosine("<<id[n]<<","<<id[i]<<")="<<fixed<<setprecision(4)<<sim<<endl;
			aver = aver + sim;
  		}
  	}
  	aver = aver / ((double)id.size()-1.0);
  	cout<<"[TID="<<tid<<"] Avg_cosine: "<<aver<<endl;
  	cos_aver.push_back(aver);
  	END = clock();  //CPU Time
  	cout<<"[TID="<<tid<<"] CPU time: "<<fixed<<setprecision(0)<< (END - START)<<"ms"<<endl;
	return NULL;
}

int main(int argc,char *argv[]){
	double START,END;  //CPU Time
	START = clock();
	vector <string> inner;
  	string line;
  	ifstream myFile;
  	myFile.open(argv[1]);  //cin the file name
  	int count = 0; //The count of files
  	while(getline(myFile,line)){
  		if(line!=""){
  			id.push_back(line);
  			getline(myFile,line);
  			inner.push_back(line);
  			count++;
  		}
  		else{
  			break;
  		}
  	}

  	for(int i = 0;i < count;i++){
  		string tmp1 = inner[i];      // To store the inner[i].size()
  		change(inner[i],tmp1.size()); 
  		frequency(inner[i],tmp1.size());
  	}
  	int fresize = fre_last.size();
  	for(int i = 0;i < fresize ; i++){
  		int fre_isize = fre_last[i].size();
  		for(int j = 0;j < fre_isize ; j++){
  			if(j == fre_isize - 1  && j <totalwords){
  				for(int k = fre_isize ;k < totalwords ; k++){
  					fre_last[i].push_back(0); //fill with 0
  				}
  			}
  		}
  	}

  	pthread_t thread[count]; //How many Files,how many child thread
  	for(int i = 0 ; i < count ; i++){
  		pthread_create(&thread[i],NULL,child,&i); // i = current file
  		while(true){
  			if(wt == 1){
  				cout<<"[Main thread]: create TID:"<<tid<<",DocID:"<<id[i]<<endl;
  				wt++;
  				break;
  			}
  		}
  		pthread_join(thread[i],NULL);
  		wt = 0; // give the next thread
  	}
  	double max = -2; //cos's range is -1 ~ 1 
  	int KeyID;
  	for(int i = 0 ; i < count ; i++){
  		if(max < cos_aver[i]){
  			KeyID = i;
  			max = cos_aver[i];
  		}
  	}
  	cout<<"[Main thread] KeyDocID:"<<id[KeyID]<<" Highest Average Cosine:"<<fixed<<setprecision(4)<<max<<endl;
	END = clock();  //CPU Time
  	cout<<"[Main thread] CPU time: "<<fixed<<setprecision(0)<< (END - START)<<"ms"<<endl;
}

