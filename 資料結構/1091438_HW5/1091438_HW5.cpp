#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <string>
#include <cmath>
//1091438 ���f޳ 
using namespace std;

//��j�I�ήt���h 
void getXY(int num,int n,int &x, int &y){
	x = (num - 1) / n;
	y = (num - 1) % n;
    if (x % 2 == 1) y = n - 1 - y;
    x = n - 1 - x;	
}  //���m 
int Ans(int maze[][10]){
    const int N = 10;
    int steps = 0;
    vector<int> seen(N * N + 1, 0); //�O�_���L 
    queue<int> q;
    q.push(1); //�_�I��1 
    seen[1] = 1;  //1�N��w�g���L 
    while (!q.empty()) {
      int size = q.size();
      ++steps;
      while (size--) {
        int s = q.front(); q.pop();        
        for (int x = s + 1; x <= min(s + 6, N * N); ++x) {  //s+1~s+6����s�i�H��F���a��        
          int r, c;                                         //��l1~6,�̤j�N��N*N(100) 
          getXY(x, N, r, c); // ������I���y��(row,col) 
          int nx = maze[r][c] == -1 ? x : maze[r][c];  //maze[r][c] = -1�N��S�����G�άO��l,nx:�U�@���I        
          if (seen[nx]) continue;
          if (nx == N * N) return steps;
          q.push(nx);
          seen[nx] = 1;      //���L���𶷦A���@�M 
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
		getXY(a,10,x,y); // �o�̭n���Ӿ�or���G���P�_ 
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
}; // �t�d�s,�쥻���r,�r���M�r�� 
vector<struct word> list_t2;

int save[51], ans[5][51], ans_num = 0;; //�s���C��node���U�@��node
int search(int num ,int count,int times)
{
	int next;
	if (count != times-1 && list_t2[0].first == list_t2[num].last)
		return 0; //��cycle,���å�Ū���Ҧ���words 
	else if (count == times - 1 && list_t2[0].first == list_t2[num].last)
	{
		save[num] = 0;
		return 2;  //�@��cycle����
	}
	for (int i = 0; i < times; i++)
	{
		if (num == i)  
			continue;
		if (save[i] == -1 && list_t2[num].last == list_t2[i].first) //�ۤv�����ڧ��@�ӥi�H���_�Ӫ��Y�A�B�����Y�S���Q���L
		{
			save[num] = i;  //�N��save[num]�U�@�ӭn���X��
			count++;
			next = search(i, count , times);
			if (num == 0 && ans_num > 0)   //��@�ӥi�వ����^���Y�n���ĤG�ӥi���count�|�h1(�]��count++�b�W���A���^��num=0�ɬOcount�w�[�@�����A)�A�]���n��@
				count--;

			if (next == 3)
				return 3;  //�N��w���F5�إi��ʤF
			else if (next == 0)  //�]���e�����A���^��,��e(save[num] = -1) 
			{
				save[num] = -1;
				continue;
			}
			else if (next == 2)  
			{
				for (int j = 0; j < times; j++)  //�w�����@���A�N���ץ��G�L�}�Cans��
					ans[ans_num][j] = save[j];
				save[i] = -1;   //�ǳƦ^�Y�A�N�{�b��m��element���s
				ans_num++;
				if (ans_num == 5)   //�����̦h5�إi��A��������
					return 3;
				return 1; //�w�����@��cycle�A���b���^�ݦ��L��L�i��άOcycle�����㩹�^��
			}
			else if (next == 1)
			{
				save[i] = -1;  //�T�w��e��m��element���X�A(�i�ର�����@��cycle��cycle������)
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
		if (line[0] >= 65 && line[0] <= 90) // �j�g���������p�g 
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
	} // �S���״N�OCNC,�]��No connection�b�e���N�H�P�_�B��X�L 
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
			int tmp = i,ex = -1,sum =0; //��l��m 
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
			}//���Ĥ@��edge�h���Ledge���,�Y��middle,�h�C�@����@�w���|�������I�b�̭�(�P�t�@���I���s��)
			 //���F�קK��J�@�Ҥ@�˪�edge,task3_3,�]�ߤFcount1�Mcount2 
		}
	}
	if( (count1 == edge - 1 || count2 == edge - 1 ) && (count1 != count2) ){
		cout<<ans<<endl;
	} // ���i�঳���middle 
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
