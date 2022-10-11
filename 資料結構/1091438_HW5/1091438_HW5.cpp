#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <string>
#include <cmath>
//1091438 郁宸瑋 
using namespace std;

//跟大富翁差不多 
void getXY(int num,int n,int &x, int &y){
	x = (num - 1) / n;
	y = (num - 1) % n;
    if (x % 2 == 1) y = n - 1 - y;
    x = n - 1 - x;	
}  //找位置 
int Ans(int maze[][10]){
    const int N = 10;
    int steps = 0;
    vector<int> seen(N * N + 1, 0); //是否走過 
    queue<int> q;
    q.push(1); //起點為1 
    seen[1] = 1;  //1代表已經走過 
    while (!q.empty()) {
      int size = q.size();
      ++steps;
      while (size--) {
        int s = q.front(); q.pop();        
        for (int x = s + 1; x <= min(s + 6, N * N); ++x) {  //s+1~s+6均為s可以到達的地方        
          int r, c;                                         //骰子1~6,最大就到N*N(100) 
          getXY(x, N, r, c); // 先找該點的座標(row,col) 
          int nx = maze[r][c] == -1 ? x : maze[r][c];  //maze[r][c] = -1代表沒有蜈蚣或是梯子,nx:下一個點        
          if (seen[nx]) continue;
          if (nx == N * N) return steps;
          q.push(nx);
          seen[nx] = 1;      //走過的毋須再走一遍 
        } 
      }      
    }
    return -1;
}  //10 x 10 

int task1(char* fname)
{
	string line;
	ifstream myFile;
	myFile.open(fname);
	int maze[10][10];
	for(int i = 0;i < 10 ; i++){
		for(int j = 0;j < 10 ; j++){
			maze[i][j] = -1;
		}
	}
	int n = 10;
	while(getline(myFile,line)!=NULL){
		bool first = true;
		int x = -1,y = -1 , a = 0 , b = 0;
		for(int i = 0;i < line.size() ; i++){
			int tmp = i,ex = -1,sum = 0;
			while(line[i]!=','&& i < line.size()){
				ex++;
				i++;
			}
			for(int j = tmp ; j < i ; j++){
				int ele = line[j] - '0';
				sum = sum + ele*pow(10,ex);
				ex--;	
			}
			if(first){
				a = sum;
				first = false;
			} // a = firstelement
			else{
				b = sum;
			} // b = secondelement
		}
		getXY(a,10,x,y); // 這裡要有個橋or蜈蚣的判斷 
		maze[x][y] = b;
	}
	cout<<Ans(maze)<<endl;
}

//--------task2--------//
struct word
{
	string w;
	char first;
	char last;
}; // 負責存,原本的字,字首和字尾 
vector<struct word> list_t2;

int save[51], ans[5][51], ans_num = 0;; //存取每個node的下一個node
int search(int num ,int count,int times)
{
	int next;
	if (count != times-1 && list_t2[0].first == list_t2[num].last)
		return 0; //有cycle,但並未讀取所有的words 
	else if (count == times - 1 && list_t2[0].first == list_t2[num].last)
	{
		save[num] = 0;
		return 2;  //一個cycle做完
	}
	for (int i = 0; i < times; i++)
	{
		if (num == i)  
			continue;
		if (save[i] == -1 && list_t2[num].last == list_t2[i].first) //自己的尾巴找到一個可以接起來的頭，且那個頭沒有被做過
		{
			save[num] = i;  //代表save[num]下一個要拜訪誰
			count++;
			next = search(i, count , times);
			if (num == 0 && ans_num > 0)   //當一個可能做完後回到頭要做第二個可能時count會多1(因為count++在上面，但回到num=0時是count已加一的狀態)，因此要減一
				count--;

			if (next == 3)
				return 3;  //代表已做了5種可能性了
			else if (next == 0)  //因提前做完，往回走,當前(save[num] = -1) 
			{
				save[num] = -1;
				continue;
			}
			else if (next == 2)  
			{
				for (int j = 0; j < times; j++)  //已做完一輪，將答案丟到二微陣列ans中
					ans[ans_num][j] = save[j];
				save[i] = -1;   //準備回頭，將現在位置的element重製
				ans_num++;
				if (ans_num == 5)   //做完最多5種可能，必須結束
					return 3;
				return 1; //已做完一個cycle，正在往回看有無其他可能或是cycle不完整往回中
			}
			else if (next == 1)
			{
				save[i] = -1;  //確定當前位置的element不合適(可能為做完一個cycle或cycle不完整)
				continue;
			}
		}
	}
	return 1;
}


int task2(char* fname)
{
	string line;
	ifstream myFile;
	myFile.open(fname);
	int times = 0;
	while (getline(myFile, line))
	{
		times++;
		word tmp;
		tmp.w = line;
		if (line[0] >= 65 && line[0] <= 90) // 大寫先全部換小寫 
			line[0] += 32;                  //ASCII
		if (line[line.size() - 1] >= 65 && line[line.size() - 1] <= 90)
			line[line.size() - 1] += 32;
		tmp.first = line[0];
		tmp.last = line[line.size() - 1];
		list_t2.push_back(tmp);
	}
	bool connect = false , complete = false;
	for (int i = 0; i < times; i++)
	{
		for (int j = i+1; j < times; j++)
		{
			if (list_t2[i].w == list_t2[j].w)
			{
				list_t2.clear();
				cout << "Same Words Detected" << endl;
				return 0;
			}
		}
	}
	for (int i = 1; i < times; i++)
	{
		if (list_t2[0].last == list_t2[i].first)
			connect = true;
		if (list_t2[0].first == list_t2[i].last)
			complete = true;
	}
	if (connect == false)
	{
		list_t2.clear();
		cout << "No Connection" << endl;
		return 0;
	}
	else if (complete == false)
	{
		list_t2.clear();
		cout << "Circle Not Complete" << endl;
		return 0;
	}
	int count = 0,num = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 51; j++)
		{
			save[j] = -1;
			ans[i][j] = -1;
		}
	}

	search(num , count , times);
	if (ans[0][0] == -1)
	{
		cout<< "Circle Not Complete" << endl;
		return 0;
	} // 沒答案就是CNC,因為No connection在前面就以判斷且輸出過 
	int a = 1;
	for (int i = 0; i < ans_num; i++)
	{
		cout << "Ans " << a << ":" << endl;
		int head = 0;
		for (int j = 0; j < times; j++)
		{
			cout << list_t2[head].w << "-" << list_t2[ans[i][head]].w << endl;
			head = ans[i][head];
		}
		a++;
	}
	ans_num = 0;
	list_t2.clear();
	return 0;
}


int task3(char* fname)
{
	string line;
	ifstream myFile;
	myFile.open(fname);
	vector<int>graph;
	int edge = 0,count1 = 0,count2 = 0,ans = -1,first,second;
	bool judge = true;
	while(getline(myFile,line)!=NULL){
		edge++;
		for(int i = 0;i<line.size();i++){
			int tmp = i,ex = -1,sum =0; //初始位置 
			while(line[i]!=',' && i < line.size()){
				ex++;
				i++;
			} 
			
			for(int j = tmp ; j < i ; j++){
				int ele = line[j] - '0';
				sum = sum + ele*pow(10,ex);
				ex--;	
			}
			
			if(edge == 1){
				if(judge){
					first = sum;
					judge = false;
				}
				else{
					second = sum;
				}
			}//first edge
            else{
            	if(first == sum){
            		ans = sum;
					count1++;
            	}
            	else if(second == sum){
            		ans = sum;
					count2++;
				}
			}//拿第一個edge去跟其他edge比較,若有middle,則每一條邊一定都會有中間點在裡面(與另一個點做連接)
			 //為了避免輸入一模一樣的edge,task3_3,設立了count1和count2 
		}
	}
	if( (count1 == edge - 1 || count2 == edge - 1 ) && (count1 != count2) ){
		cout<<ans<<endl;
	} // 不可能有兩個middle 
	else{
		cout<<"No middle"<<endl;
	}
}

int main()
{
	mmenu:
	int menu=0;
	cout <<"ID:<1091438>"<< endl;
	cout <<"Homework 5"<< endl;
	cout <<"----------------"<< endl;
	cout <<"Choose to access"<< endl;
	cout <<"1.<Task1>"<< endl;
	cout <<"2.<Task2>"<< endl;
	cout <<"3.<Task3>"<< endl;
	cout <<"----------------"<< endl;
	cin >> menu;
	
	switch(menu) {
	  char bmenu;
	  case 1:
	  	system("cls");
	  	cout <<"Task 1"<< endl;
		cout <<"----------------"<< endl;
	  	
		task1("task1_1.txt");
		task1("task1_2.txt");
		task1("task1_3.txt");
		task1("task1_4.txt");
		task1("task1_5.txt");
		task1("task1_6.txt");
		task1("task1_7.txt");
		task1("task1_8.txt");
	    
	    cout <<"Back to menu? (y/n)"<< endl;
	    cin >> bmenu;
	    switch(bmenu){
		 case 'y':
		 	system("cls");
		 	goto mmenu;
		 break;
		 case 'n':
		 	exit(0);
		 break;
		}
	    
	  break;
	  
	  case 2:
	  	system("cls");
	  	cout <<"Task 2"<< endl;
	  	cout <<"----------------"<< endl;
	  	
		task2("task2_1.txt");
		task2("task2_2.txt");
		task2("task2_3.txt");
		task2("task2_4.txt");
		task2("task2_5.txt");
		task2("task2_6.txt");
		task2("task2_7.txt");
		task2("task2_8.txt");
	    
	    cout <<"Back to menu? (y/n)"<< endl;
	    cin >> bmenu;
	    switch(bmenu){
		 case 'y':
		 	system("cls");
		 	goto mmenu;
		 break;
		 case 'n':
		 	exit(0);
		 break;
		}
	  break;
	  
	  case 3:
	  	system("cls");
	  	cout <<"Task 3"<< endl;
	  	cout <<"----------------"<< endl;
	  	
		task3("task3_1.txt");
		task3("task3_2.txt");
		task3("task3_3.txt");
		task3("task3_4.txt");
		task3("task3_5.txt");
		task3("task3_6.txt");
		task3("task3_7.txt");
		task3("task3_8.txt");
	    
	    cout <<"Back to menu? (y/n)"<< endl;
	    cin >> bmenu;
	    switch(bmenu){
		 case 'Y': case 'y':
		 	system("cls");
		 	goto mmenu;
		 	
		 break;
		 case 'n':
		 	exit(0);
		 break;
		}
	  break;
	return 0;
    }
}
