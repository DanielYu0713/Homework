#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>


#include<sys/file.h>
#include<sys/mman.h>
#include<sys/wait.h>
#include<string.h>
#include<iostream>

#include<stdio.h>  //random
#include<time.h>   //random

using namespace std;

void error_and_die(const char *msg){
     perror(msg);
     exit(EXIT_FAILURE);
}

void point(int x,int y){
  cout<<"("<<x<<","<<y<<")";
}

void anotherpoint(int x,int y,int &x1,int &y1){
   if(rand()%2==1){ //means boat is parallels,y is the same,I want
	     if(x==0){      // 0<=x<=3
	        point(x+1,y);
	        x1 = x + 1;
	        y1 = y;
	     }
	     else if(x==3){
	        point(x-1,y);
	        x1 = x - 1;
	        y1 = y;
	     }
	     else{
	       if(rand()%2==1){
	         point(x+1,y); //When rand()=1
	         x1 = x + 1;
	         y1 = y;
	       }
	       else{
	         point(x-1,y);
	        x1 = x - 1;
	        y1 = y;
	       }
	     }
    }
    else{  //means boat is vertical,x is the same,I want
	    if(y==0){      // 0<=y<=3
	        point(x,y+1);
	        x1=x;
	        y1=y+1;
	     }
	     else if(y==3){
	        point(x,y-1);
	        x1=x;
	        y1=y-1;
	     }
	     else{
	       if(rand()%2==1){
	        point(x,y+1); //When rand()=1
	        x1=x;
	        y1=y+1;
	       }
	       else{
	        point(x,y-1);
	        x1=x;
	        y1=y-1;
	       }
	     }
    }
}

void attacked(int bombx,int bomby,int x,int y,int x1,int y1,int &num, int &atked_x,int &atked_y){     
     if((bombx==x && bomby==y) || (bombx==x1 && bomby==y1)){
        if(atked_x == bombx && atked_y == bomby){   // For 3-c
           
        }
        else{
        	num--;
        }
        atked_x = bombx;
        atked_y = bomby;
      
       if(num!=0){
       	cout << "hit"<<endl;
       }
       else{
        cout<<"hit and sinking"<<endl;
       }
       
     }
     else{
       cout << "missing"<<endl;
     }
}

int ran(){
  return rand() % 4;
}

int main(int argc,char *argv[]){
	
	         
	int r;      
        const char *memname="sample";
        const size_t region_size = sysconf(_SC_PAGE_SIZE);
        
        int fd = shm_open(memname, O_CREAT|O_TRUNC|O_RDWR,0666);
 	if(fd==-1) error_and_die("shm_open");
 
	r=ftruncate(fd,region_size);
 	if(r!=0)  error_and_die("ftruncate");
 
 	int *ptr=(int *)mmap(0,region_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    	if(ptr == MAP_FAILED) error_and_die("mmap");
    	close(fd); 
    	ptr[3] = -1; //initial, the num of the enemy's
    	ptr[4] = -1;  //initial, lock the next step if ptr[4] != 1
    	ptr[5] = 0;
    	ptr[6] = 0; //Winner's pid
    	ptr[7] = 0; //Winner's bomb
        ptr[9] = 0; //cout who is win
    	char tmp1 = *argv[1],tmp2 = *argv[2];
    	// parent's and child's random seed
    	int pseed = tmp1 - '0', childseed = tmp2 - '0';
    	
	if(fork()==0){  //child
           srand((unsigned)time(NULL)^childseed);
           int x=ran(),y=ran(),x1,y1,pid_tmp = getpid(),atked_x = -1,atked_y = -1;
	   while(true){
	   	if(ptr[5] == 2){
	  	 cout<<"["<<getpid()<<" Child]:Random Seed "<< argv[2];
	         cout<<endl;   	
	   	 cout<<"["<<getpid()<<" Child]:The gunboat:";

	  	 point(x,y);
	  	 anotherpoint(x,y,x1,y1);
	   	 cout<<endl;
	   	 ptr[4] = 1;  // start attack
	   	 ptr[5] = 3;
		}
		if(ptr[5] == 3){
		   ptr[5] = 0;
	           break;
		}
	   }
	   
	   int num = 2;    // the point of the boat (initial num)
	   int bombnum = 0;
	   while(true){
	   	if(ptr[4] == 1){
	   		if(ptr[3] != 0 && num != 0 && ptr[5] == 1){
	    			//-----------shootted-----------//
		    		cout<<"["<<getpid()<<" Child]:";
		    		attacked(ptr[1],ptr[2],x,y,x1,y1,num,atked_x,atked_y);
	    			ptr[3] = num;
	    
	    			if(num!=0){  //child isn't sinking
	    			//------------shooting-----------//   
	    			cout<<"["<<getpid()<<" Child]:bombing";
	    			ptr[1] = ran();  //x
	    			ptr[2] = ran();  //y
	    			point(ptr[1],ptr[2]); 
	    			cout<<endl;
	    			bombnum++;
	    			}
	    			else{   
  	    		                // child is sinking
	    		       		break;
	    			} 
	    			ptr[5] = 2;
	    		}
	    		else if(ptr[3] == 0){
	    	   		ptr[6] = pid_tmp;
	    	   		ptr[7] = bombnum;
	  	   		ptr[9] = 1;
	    	   		break;
	    		}	//enemy is loss
	    			    		
          	}
	  }
	   exit(0);
	}
	
	else{  //parent process
	  srand((unsigned)time(NULL)^pseed);
	  int x=ran(),y=ran(),x1,y1,pid_tmp = getpid(),atked_x = -1,atked_y = -1;
	  while(true){
	   if(ptr[5] == 0){
	   	cout<<"["<<getpid()<<" Parent]:Random Seed "<< argv[1];
	   	cout<<endl;
	  	cout<<"["<<getpid()<<" Parent]:The gunboat:";        
	   	point(x,y);
	   	anotherpoint(x,y,x1,y1);
	   	cout<<endl;
	   	ptr[5] = 1;
	   }
	   if(ptr[5] == 1){
	        ptr[5] = 2;
	   	break;
	   }
	  }
	  
	   int num = 2; //The count of boat's point (initial)
           int bombnum = 0;
           while(true){
                if(ptr[4] ==1){
	   	  //------------shooting-----------//
	     	  if(ptr[3] != 0 && num != 0 && ptr[5] == 0){
	   		cout<<"["<<getpid()<<" Parent]:bombing";
	   		ptr[1] = ran();  //x
	   		ptr[2] = ran();  //y
	   		point(ptr[1],ptr[2]);
	   		cout<<endl;
	   		ptr[5] = 1;
	   		bombnum++;
	   	  }
	   	  else if(ptr[3] == 0 ){  //enemy loss
	   	        ptr[7] = bombnum;
	   	        ptr[6] = pid_tmp;
	 	        ptr[9] = 1;
	   	        break;
	   	  }
	   	  if(ptr[3] != 0  && ptr[5] == 2){ // The enemy isn't loss
	   	  //-----------shootted-----------//
           	 	cout<<"["<<getpid()<<" Parent]:";
          	 	attacked(ptr[1],ptr[2],x,y,x1,y1,num,atked_x,atked_y); 
   	        	ptr[3] = num;
   	        	ptr[5] = 0;
	   	  }
         	  if(num == 0){ //Parent loss
	   	        break;
	   	  }
	   	}
	   }
	   while(true){
   		if(ptr[9] == 1){
	      	cout<<"["<<getpid()<<" Parent]:"<<ptr[6];
	      	cout<<" wins with "<<ptr[7]<<" bombs"<<endl;
	      	break;
	   	}
	   }
	           
	}
	r = munmap(ptr,region_size);
     	if(r!=0) error_and_die("shm_unlink");
}
