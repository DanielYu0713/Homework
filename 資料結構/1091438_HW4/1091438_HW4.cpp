//1091438 郁宸瑋 
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
	if (current == NULL)    //一路查到最後，如遇到NULL就回傳當前為NULL
		return NULL;
	else if (current->data == head)   //如遇到要查找之值，則直接回傳該Node
		return current;
	else
	{
		n_l = current->serch(current->left, head);   
		n_r = current->serch(current->right, head);	  //一路查到最後，從最底層開始找
		if (n_l == NULL && n_r == NULL)   //如左右child皆為NULL代表當前Node為leaf，因此回傳自身
			return current;
		if (head == n_l->data)   //如左孩子為欲查找之值，則回傳，並存於全域變數hear
			return hear = n_l;
		else if (n_l != NULL && n_r == NULL)  //這段是因為binary tree必須左child有值右child才能填值進去，因此只要判斷兩個child皆為NULL，
			return current;					  //左child不為NULL，右child為NULL，兩個child皆不為NULL三種情況即可
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
		int tmp = i; //起始位置
		int sum = 0; 
		int count = -1; //紀錄此數為幾位數 
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
				number.push_back(sum); // 將所有樹先丟進去 
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
	}   //把樹由小排到大,用來確定砍的順序 
	int currentrow = 0, currentcol = 0 , res = 0;//起始點的位置
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
				} //0在存number時,就已過濾掉ㄌ 
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
	int ex = testcase.size()%10 - 1; //計算testcase有幾位數,這裡最大設計為9位數 
	int chr = 0,test = 0;
	while(ex >= 0){
		int tmp= (int)testcase[chr]-'0';
        test = test + tmp*pow(10,ex);
        ex--;
		chr++;
	}//二位數up 的 testcase
	int testcount = test;
	Node* list[testcount];
	Node* current[testcount];
	for (int i = 0; i < testcount; i++) {
		list[i] = new Node();
		current[i] = new Node();
	} //初始化 

	int number = 0;
	while (testcount != 0) {
		getline(myFile, line);
		bool lock = false, firstele = true;
		for (int i = 0; i < line.size(); i++) {
			int tmp = i; //起始位置
			int sum = 0;
			int count = -1; //紀錄此數為幾位數 
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
	} //將list們merge起來 
	
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
	}  //檢查是否有相同的元素在element中 
	
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
	//-----判斷較例外的情況 -----//
	for(int k = 0;k <line.size();k++){
		if(line[k] == ','){
			onlyhaveroot = false;
		}
		if(line[k] == '[' && line[k+1] == ']'){
			cout<<"The binary tree is empty"<<endl;
			return 0;
		}   //此二元樹是空的
	}
	
	if(onlyhaveroot){
		cout<<"The maximum path sum is ";
		int chr = 1; //一開始為'[' 
		while(line[chr]!=']'){
			cout<<line[chr];
			chr++;
		}
		cout<<endl;
	}//只有一個root,最大路徑就是root
	//-----判斷較例外的情況 -----//
    else{
	  for(int i = 0; i < line.size();i++){
		  bool par = true;
		  while(line[i]!='['){
		  	i++;
		  }
		  i++; // 將line[i] = 'value'
		  while(line[i]!=']'){
			int tmp = i,neg = 1,ex = -1,ele = 0,sum = 0; //初始化 , for parent 
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
			i++; // 進到child 的 value 
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

	//建立一個新的tree，並將root的值丟到root中並初始化left,right
	tree* root = new tree();
	root->data = lis[0][0];
	root->left = NULL;
	root->right = NULL; 
	tree* current = root;
	for (int i = 0; i < lis_ptr; i++) /////讀取二維陣列lis，lis[0][0]代表root,lis[0][1]代表為以root作為parent的child值(左右目前未知)
	{
		current = root;
		current = current->serch(current, lis[i][0]);   //用serch尋找對應的parent
														//這段方式為依序查找測資lis[i][1]對應的parent是誰，以便於加入child
		if (current->left == NULL)  //利用上面判斷到的Node作為parent，判斷parent左右哪一個為空則丟內容進去
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
	int tmpstep[100][100] = {};  // 我的設計 : n最大只能到100 :)
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
		  i++; // 將line[i] = 'value'
		  while(line[i]!=']'){
			int tmp = i,neg = 1,ex = -1,ele = 0,a = 0; //初始化 , for parent 
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
			i++; // 進到child 的 value 
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
			tmpstep[a][b]++; //代表a,b之間有路可走 
			if(b > num){
				num = b;
			} //from 1 to n(num),圖中的點數為1~n 
			par = true;
		    }
	}
	vector<double>p(num+1); // 到達該點的機率 
	p[1] = 1.0;
	vector< vector <int> > g(num+1);
	for(int i = 0 ; i < 100 ; i++){
		for(int j = 0 ; j < 100 ; j++){
			if(tmpstep[i][j]==1){
				g[i].push_back(j);
				g[j].push_back(i); 
			}
		}	
	}	//這裡想不到有沒有比較好的方式可以把tmp改好看一點 
	vector<int>seen(num+1);
	seen[1] = 1;
	queue<int> q;
	q.push(1);  //起點從1開始 
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
			}  //先數數cur有幾個child 
			ichild = 0;
			for(int nxt = g[cur][ichild] ; ichild <g[cur].size() ; ichild++ ){
				nxt = g[cur][ichild];
				if(!seen[nxt]++){  //拜訪過了,seen[nxt] ++ 
					q.push(nxt);   //並把它放到queue中,為了在下個while找他(nxt)的child 
					p[nxt] = p[cur]/children;
				}
			}
			if(children > 0) p[cur] = 0.0;  //因為不能往回走.若往下走了,原先的點的機率 = 0 
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
