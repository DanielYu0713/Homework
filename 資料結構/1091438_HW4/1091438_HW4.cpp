//1091438 ���f޳ 
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <string>
#include <cmath>

using namespace std;
//for task1 and task3
struct Node {
	int data;
	Node* next;
	Node* Merge(Node* h1, Node* h2);
};

Node* Node::Merge(Node* h1, Node* h2) {
	if (h1 == NULL) return h2;
	if (h2 == NULL) return h1;
	if (h1->data < h2->data) {
		h1->next = Merge(h1->next, h2);
		return h1;
	}
	else {
		h2->next = Merge(h1, h2->next);
		return h2;
	}

}
//for task1 and task3

//for task2
int BFS(vector< vector<int> >& forest, int row, int col, int treeRow, int treeCol){
	if(row ==treeRow && col == treeCol) return 0;
	int m = forest.size(), n = forest[0].size(), cnt = 0;
	queue< int > q;
	q.push(row*n+col);
	vector< vector <int> >visited(m,vector<int>(n));
	vector<int>dir;
	dir.push_back(-1);dir.push_back(0);dir.push_back(1);dir.push_back(0);dir.push_back(-1);
	while (!q.empty()) {
            ++cnt;
            for (int i = q.size(); i > 0; --i) {
                int r = q.front() / n, c = q.front() % n; q.pop();
                for (int k = 0; k < 4; ++k) {
					int x = r + dir[k], y = c + dir[k + 1];
                    if (x < 0 || x >= m || y < 0 || y >= n || visited[x][y] == 1 || forest[x][y] == 0)	continue;	
                    if (x == treeRow && y == treeCol) {
						return cnt;
					}
                    visited[x][y] = 1;
                    q.push(x * n + y);
                }
            }
    }
        return -1;
}
//for task2

//for task4
struct tree{
	int data;
	tree* left;
	tree* right;
	tree* serch(tree* current,int head);
};

tree* hear;

tree* tree::serch(tree* current , int head)
{
	tree* n_l;
	tree* n_r;
	if (current == NULL)    //�@���d��̫�A�p�J��NULL�N�^�Ƿ�e��NULL
		return NULL;
	else if (current->data == head)   //�p�J��n�d�䤧�ȡA�h�����^�Ǹ�Node
		return current;
	else
	{
		n_l = current->serch(current->left, head);   
		n_r = current->serch(current->right, head);	  //�@���d��̫�A�q�̩��h�}�l��
		if (n_l == NULL && n_r == NULL)   //�p���kchild�Ҭ�NULL�N���eNode��leaf�A�]���^�Ǧۨ�
			return current;
		if (head == n_l->data)   //�p���Ĥl�����d�䤧�ȡA�h�^�ǡA�æs������ܼ�hear
			return hear = n_l;
		else if (n_l != NULL && n_r == NULL)  //�o�q�O�]��binary tree������child���ȥkchild�~���ȶi�h�A�]���u�n�P�_���child�Ҭ�NULL�A
			return current;					  //��child����NULL�A�kchild��NULL�A���child�Ҥ���NULL�T�ر��p�Y�i
		else if (n_r->data == head)
			return hear = n_r;
		else
			return current;
	}
}

int maxnum(int num1, int num2){
	if (num1 >= num2)
		return num1;
	else
		return num2;
}

int find(tree* current,int &sum)
{
	if (current == NULL)
		return 0;
	int left = find(current->left, sum);
	int right = find(current->right, sum);
	int max_road = maxnum(left, right) + current->data;
	int max_road1 = maxnum(max_road, left + right + current->data);
	sum = maxnum(sum, max_road1);
	return max_road;
}
// for task4


int task1(char* fname)
{
	string line;
	ifstream myFile;
	myFile.open(fname);
	getline(myFile,line);
	Node* even = new Node();
	Node* odd = new Node();
	Node* current1;
	Node* current2;
	bool firsteven = true , firstodd = true, lock = false;
	for(int i = 0 ; i < line.size() ; i++){
		int tmp = i; //�_�l��m
		int sum = 0; 
		int count = -1; //�������Ƭ��X��� 
		while(line[tmp]!=',' && !lock){
			if(tmp == line.size()){
				lock = true;
				break;
			}
			count++;
			tmp++;
		}
		for(int j = i ; j < tmp;j++){
			int ele = (int)line[j]-'0';
			sum = sum + ele * pow(10,count);
			count--;	
		} 
		i = tmp;
	if(sum % 2 == 0){ //even
			if(firsteven){
				even->data = sum;
				even->next = NULL;
				firsteven = false;
				current1 = even;
			}  //first element of evenlist
			else{
				current1->next = new Node();
				current1= current1->next;
				current1->data = sum;
				current1->next = NULL;
			}
		}
		else{
			if(firstodd){
				odd->data = sum;
				odd->next = NULL;
				firstodd = false;
				current2 = odd;
			}  //first element of oddlist
			else{
				current2->next = new Node();
				current2= current2->next;
				current2->data = sum;
				current2->next = NULL;
			}	
		}
	}
	current2 = odd;
	current1 = even;
	if(firstodd && !firsteven){ // no odd list
		while(current1!=NULL){
			cout<<current1->data;
			if(current1->next !=NULL){
				cout<<",";
			}
		current1 = current1->next;
		}
	cout<<endl;
	}
	else if(!firstodd && firsteven){ // no even list
		while(current2!=NULL){
			cout<<current2->data;
			if(current2->next !=NULL){
				cout<<",";
			}
		current2 = current2->next;
		}
	cout<<endl;
	}
	else{    //have even and odd list
		while (current2!=NULL){
				current2 = current2->next;
				if(current2->next == NULL){
					current2->next = even;
					break;
				}
    	}
		current2 = odd;
		while(current2!=NULL){
			cout<<current2->data;
			if(current2->next !=NULL){
				cout<<",";
			}
		    current2 = current2->next;
		}
		cout<<endl;
	}
}
int task2(char* fname)
{
	string line;
	ifstream myFile;
	myFile.open(fname);
	int count = 0;
	vector<int>number;
	vector< vector<int> >forest;
	vector< vector<int> >neighbor;
	while(getline(myFile,line)!=NULL){
		vector<int>row;
		for(int i = 0 ; i < line.size() ; i++){
			int tmp = i,ex = -1 , sum = 0;
			while(line[i]!=','){
					ex++;
					if(i == line.size() - 1){
						i++;
						break;
					}
					i++;
			}
			for(int j = tmp ; j < i ; j++){
				int tmp2 =(int)line[j] - '0';
				sum = sum + tmp2 * pow (10,ex);
				ex--;
			}
			row.push_back(sum);
		
			if(sum!=0){
				number.push_back(sum); // �N�Ҧ������i�h 
			}
		}
		forest.push_back(row);
	}
	for(int i = 0 ; i< number.size() ; i++){
		for(int j = i ; j < number.size() ; j++){
			if(number[j] < number[i] ){
				int swp = number[j];
				number[j] = number[i];
				number[i] = swp;
			}
		}
	}   //���Ѥp�ƨ�j,�ΨӽT�w�媺���� 
	int currentrow = 0, currentcol = 0 , res = 0;//�_�l�I����m
	for(int k = 0; k < number.size();k++){
		for(int i = 0 ; i< forest.size() ; i++){
			for(int j = 0 ; j < forest[i].size() ; j++){
				if(number[k] == forest[i][j]){
					int cnt = BFS(forest,currentrow,currentcol,i,j);
					if(cnt == -1){
						cout<<"-1"<<endl;
						return 0;
					}

					res+=cnt;
					currentrow = i;
					currentcol = j;
				} //0�b�snumber��,�N�w�L�o���{ 
			}
		}
	}

	cout<<res<<endl;
}
int task3(char* fname)
{
string testcase, line;
	ifstream myFile;
	myFile.open(fname);
	getline(myFile, testcase);
	int ex = testcase.size()%10 - 1; //�p��testcase���X���,�o�̳̤j�]�p��9��� 
	int chr = 0,test = 0;
	while(ex >= 0){
		int tmp= (int)testcase[chr]-'0';
        test = test + tmp*pow(10,ex);
        ex--;
		chr++;
	}//�G���up �� testcase
	int testcount = test;
	Node* list[testcount];
	Node* current[testcount];
	for (int i = 0; i < testcount; i++) {
		list[i] = new Node();
		current[i] = new Node();
	} //��l�� 

	int number = 0;
	while (testcount != 0) {
		getline(myFile, line);
		bool lock = false, firstele = true;
		for (int i = 0; i < line.size(); i++) {
			int tmp = i; //�_�l��m
			int sum = 0;
			int count = -1; //�������Ƭ��X��� 
			while (line[tmp] != ',' && !lock) {
				if (tmp == line.size()) {
					lock = true;
					break;
				}
				count++;
				tmp++;
			}
			for (int j = i; j < tmp; j++) {
				int ele = (int)line[j] - '0';
				sum = sum + ele * pow(10, count);
				count--;
			}
			i = tmp;
			if (firstele) {
				list[number]->data = sum;
				list[number]->next = NULL;
				firstele = false;
				current[number] = list[number];
			} // first number of list[number]
			else {
				current[number]->next = new Node();
				current[number] = current[number]->next;
				current[number]->data = sum;
				current[number]->next = NULL;
			}
			//cout<<"current ["<<number<<"] = "<<current[number]->data<<endl;
		}
		number++;
		testcount--;
	}
	Node* current2 = list[0];
	for (int i = 1; i < number; i++) {
		current2->Merge(current2, list[i]);
	} //�Nlist��merge�_�� 
	
	Node* check1 = list[0];
	bool error = false;
	while(check1!=NULL){
		Node* check2 = check1->next;
		while(check2!=NULL){
			if((check1->data) == (check2->data)){
				error = true;
				break;
			}
			check2 = check2->next;
		}
		check1 = check1 -> next;
	}  //�ˬd�O�_���ۦP�������belement�� 
	
	if(error){
		cout<<"Error! There are identical elements in the list"<<endl;
	}
	else{
		while(current2!=NULL)
		{
			cout << current2->data;
			if(current2->next != NULL){
				cout<<" -> ";
			}
			current2 = current2->next;
		}
		cout<<endl;
	}
}
int task4(char* fname)
{
	string line;
	ifstream myFile;
	myFile.open(fname);
	getline(myFile,line);
	int sum = INT_MIN;
	int lis[3072][2];
	bool onlyhaveroot = true;
	int lis_ptr = 0,lis_ptr2 = 0;
	//-----�P�_���ҥ~�����p -----//
	for(int k = 0;k <line.size();k++){
		if(line[k] == ','){
			onlyhaveroot = false;
		}
		if(line[k] == '[' && line[k+1] == ']'){
			cout<<"The binary tree is empty"<<endl;
			return 0;
		}   //���G����O�Ū�
	}
	
	if(onlyhaveroot){
		cout<<"The maximum path sum is ";
		int chr = 1; //�@�}�l��'[' 
		while(line[chr]!=']'){
			cout<<line[chr];
			chr++;
		}
		cout<<endl;
	}//�u���@��root,�̤j���|�N�Oroot
	//-----�P�_���ҥ~�����p -----//
    else{
	  for(int i = 0; i < line.size();i++){
		  bool par = true;
		  while(line[i]!='['){
		  	i++;
		  }
		  i++; // �Nline[i] = 'value'
		  while(line[i]!=']'){
			int tmp = i,neg = 1,ex = -1,ele = 0,sum = 0; //��l�� , for parent 
			while(line[i]!=',' && par){
				if(line[i] == '-' ){
					neg = -1;
				}
				else{
					ex++;
				}
				i++;
			} // parent
			par = false;
			for(int j = tmp ; j < i ; j++ ){
			    if(line[j]!='-'){
					ele = (int)line[j] - '0';
					sum = sum + ele * pow(10,ex);
					ex--; 
				}
			}
			sum*=neg;
			lis[lis_ptr][lis_ptr2] = sum;
			lis_ptr2++;
			i++; // �i��child �� value 
			tmp = i,neg = 1,ex = -1,ele = 0 , sum = 0;
			if(!par){
				while(line[i]!=']'){
					if(line[i] == '-' ){
						neg = -1;
					}
					else{
						ex++;
					}
					i++;
				}
				for(int j = tmp ; j < i ; j++ ){
					if(line[j]!='-'){
						ele = (int)line[j] - '0';
						sum = sum + ele * pow(10,ex);
						ex--; 
					}
				}			
			}
			sum*=neg;
			lis[lis_ptr][lis_ptr2] = sum;
			lis_ptr2 = 0;
			lis_ptr++;
			
			par = true;
		  }
	    }
    }

	//�إߤ@�ӷs��tree�A�ñNroot���ȥ��root���ê�l��left,right
	tree* root = new tree();
	root->data = lis[0][0];
	root->left = NULL;
	root->right = NULL; 
	tree* current = root;
	for (int i = 0; i < lis_ptr; i++) /////Ū���G���}�Clis�Alis[0][0]�N��root,lis[0][1]�N���Hroot�@��parent��child��(���k�ثe����)
	{
		current = root;
		current = current->serch(current, lis[i][0]);   //��serch�M�������parent
														//�o�q�覡���̧Ǭd�����lis[i][1]������parent�O�֡A�H�K��[�Jchild
		if (current->left == NULL)  //�Q�ΤW���P�_�쪺Node�@��parent�A�P�_parent���k���@�Ӭ��ūh�᤺�e�i�h
		{
			current->left = new tree();
			current = current->left;
			current->data = lis[i][1];
			current->left = NULL;
			current->right = NULL;
		}
		else
		{
			current->right = new tree();
			current = current->right;
			current->data = lis[i][1];
			current->left = NULL;
			current->right = NULL;
		}
	}
	current = root;
	find(current, sum);
	cout << "The maximum path sum is "<< sum <<endl;
}
int task5(char* fname)
{
	string line;
	ifstream myFile;
	myFile.open(fname);
	getline(myFile,line); //Time Limit
	int t = 0,ex = line.size() - 1,target = 0;
	int num = INT_MIN; 
	int tmpstep[100][100] = {};  // �ڪ��]�p : n�̤j�u���100 :)
	for(int i = 0;i < 100;i++){
		for(int j = 0 ;j < 100;j++){
			tmpstep[i][j] = 0;
		}
	}
	for(int i = 0;i<line.size();i++){
		int tmp = (int)line[i] - '0';
		t = t + tmp * pow(10,ex);
		ex--;
	}
	
	getline(myFile,line); //Target
	ex = line.size() - 1;
	for(int i = 0;i<line.size();i++){
		int tmp = (int)line[i] - '0';
		target = target + tmp * pow(10,ex);
		ex--;
	}

	getline(myFile,line);
	for(int i = 0; i < line.size();i++){
		  bool par = true;
		  while(line[i]!='['){
		  	i++;
		  }
		  i++; // �Nline[i] = 'value'
		  while(line[i]!=']'){
			int tmp = i,neg = 1,ex = -1,ele = 0,a = 0; //��l�� , for parent 
			while(line[i]!=',' && par){
				if(line[i] == '-' ){
					neg = -1;
				}
				else{
					ex++;
				}
				i++;
			} // parent
			par = false;
			for(int j = tmp ; j < i ; j++ ){
			    if(line[j]!='-'){
					ele = (int)line[j] - '0';
					a = a + ele * pow(10,ex);
					ex--; 
				}
			}
			a *= neg;
			if(a > num){
				num = a;
			}
			i++; // �i��child �� value 
			tmp = i,neg = 1,ex = -1,ele = 0 ;
			int b = 0;
			if(!par){
				while(line[i]!=']'){
					if(line[i] == '-' ){
						neg = -1;
					}
					else{
						ex++;
					}
					i++;
				}
				for(int j = tmp ; j < i ; j++ ){
					if(line[j]!='-'){
						ele = (int)line[j] - '0';
						b = b + ele * pow(10,ex);
						ex--; 
					}
				}			
			}
			b *= neg;
			tmpstep[a][b]++; //�N��a,b���������i�� 
			if(b > num){
				num = b;
			} //from 1 to n(num),�Ϥ����I�Ƭ�1~n 
			par = true;
		    }
	}
	vector<double>p(num+1); // ��F���I�����v 
	p[1] = 1.0;
	vector< vector <int> > g(num+1);
	for(int i = 0 ; i < 100 ; i++){
		for(int j = 0 ; j < 100 ; j++){
			if(tmpstep[i][j]==1){
				g[i].push_back(j);
				g[j].push_back(i); 
			}
		}	
	}	//�o�̷Q���즳�S������n���覡�i�H��tmp��n�ݤ@�I 
	vector<int>seen(num+1);
	seen[1] = 1;
	queue<int> q;
	q.push(1);  //�_�I�q1�}�l 
	while(t--){
		int size = q.size();
		while(size--){
			int cur = q.front(); q.pop();
			int ichild = 0,children = 0;
			for(int nxt = g[cur][ichild] ; ichild <g[cur].size() ; ichild++ ){
				nxt = g[cur][ichild];
				if(!seen[nxt]){
				 	++children;
				 }
			}  //���Ƽ�cur���X��child 
			ichild = 0;
			for(int nxt = g[cur][ichild] ; ichild <g[cur].size() ; ichild++ ){
				nxt = g[cur][ichild];
				if(!seen[nxt]++){  //���X�L�F,seen[nxt] ++ 
					q.push(nxt);   //�ç⥦���queue��,���F�b�U��while��L(nxt)��child 
					p[nxt] = p[cur]/children;
				}
			}
			if(children > 0) p[cur] = 0.0;  //�]�����੹�^��.�Y���U���F,������I�����v = 0 
		}
	}
	if(p[target] == 0){
		cout<<"Not Enough Time"<<endl;
	}
	else{
		cout<<p[target]<<endl;
	}
}

int main()
{
	mmenu:
	int menu=0;
	cout <<"ID:<1091438>"<< endl;
	cout <<"Homework 4"<< endl;
	cout <<"----------------"<< endl;
	cout <<"Choose to access"<< endl;
	cout <<"1.<Task1>"<< endl;
	cout <<"2.<Task2>"<< endl;
	cout <<"3.<Task3>"<< endl;
	cout <<"4.<Task4>"<< endl;
	cout <<"5.<Task5>"<< endl ;
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
	  
	  case 4:
	  	system("cls");
	  	cout <<"Task 4"<< endl;
	  	cout <<"----------------"<< endl;
	  	
		task4("task4_1.txt");
		task4("task4_2.txt");
		task4("task4_3.txt");
		task4("task4_4.txt");		
	    
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
	  
	  case 5:
	  	system("cls");
	  	cout <<"Task 5"<< endl;
	  	cout <<"----------------"<< endl;
	  	
		task5("task5_1.txt");
		task5("task5_2.txt");
		task5("task5_3.txt");
		task5("task5_4.txt");	
	    
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
	}
	  
	return 0;
}
