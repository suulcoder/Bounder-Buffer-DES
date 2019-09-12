#include <iostream> //cout, cin, cerr
#include <unistd.h>
#include <cmath>
#include <fstream> //file processing
#include <cstdlib> //exit function
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
using namespace std;

int in, out;
bool isfree = true; 
pthread_cond_t lleno, vacio; 
pthread_mutex_t semaf;
char buffer[] = ""; 

void *WriteResult(void *threadID){
	pthread_mutex_lock(& semaf);
	if (isfree == true){
		pthread_cond_wait(& lleno, &semaf);
	}
	char character;
	character = buffer[out];
	out = (out+1);
  ofstream write("encrypted.txt",ios::app);
  if(!write)
  {
    cerr<<"Fail to create encrypted.txt"<<endl;
    exit(EXIT_FAILURE);
  }
  write<<character;
  isfree = true;
	pthread_cond_broadcast(& vacio); 
 	pthread_mutex_unlock(& semaf);   
}

void *code(void *threadID){
	pthread_mutex_lock (& semaf);  
	long ID;
	ID = long(threadID);
	if (isfree == false){
  		pthread_cond_wait(& vacio, &semaf); 
	}
	int res = int(ID);
	int i;
  for(i=0; i<16; i++){
  	if(i%4==0){
  		res = res + i;
  	}
  	else if(i%4==1){
  		res = res - i;
  	}
  	else if(i%4==2){
  		res = res + i;
  	}
  	else{
  		res = res - i;
  	}
  } 
  buffer[in] = char(res);
  in = (in+1);
  isfree = false;
  pthread_cond_broadcast(& lleno); 
	pthread_mutex_unlock(& semaf); 
}

int main(int argc, char const *argv[])
{
  ofstream infile;
  infile.open("encrypted.txt");
  infile.clear();
  int rc;
  pthread_t tid;//id
  pthread_attr_t attr;//atribute
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  int rc1;
  pthread_t tid1;//id
  pthread_attr_t attr1;//atribute
  pthread_attr_init(&attr1);
  pthread_attr_setdetachstate(&attr1, PTHREAD_CREATE_JOINABLE);
	char string[128];	
  in = out = 0;
	pthread_mutex_init(&semaf, NULL); 
  pthread_cond_init(&lleno, NULL); 
 	pthread_cond_init(&vacio, NULL);
	ifstream read("Test.txt",ios::in);
	if(!read){
		cerr<<"Fail to read Test.txt"<<endl;
		exit(EXIT_FAILURE);
	}
	int counter = 0;
	while (!read.eof()) {
	    read >> string;
	    int x = 0;
	    while(string[x] != '\0'){
	    	int chain = int(string[x]);
	    	rc = pthread_create(&tid, NULL, code, (void *)chain);//Create a thread for each number
        rc1 = pthread_create(&tid1, NULL, WriteResult, (void *)counter);//Create a thread for each number
       	if (rc) {
           printf("ERROR; return code from pthread_create() is %d\n", rc);
           exit(-1);
        }    
     	// Esperamos a que cada thread termine en orden
        rc = pthread_join(tid, NULL);    
        if (rc) {
      	 	printf("ERROR; return code from pthread_join() is %d\n", rc);
        	exit(-1);
        }
	    	x++;
	    	counter++;
	    }
      rc = pthread_create(&tid, NULL, code, (void *)int(' '));//Create a thread for each number
      rc1 = pthread_create(&tid1, NULL, WriteResult, (void *)counter);//Create a thread for each number
      counter++;
	}
  printf("The file is encrypted check encrypted.txt");
	read.close();
	exit(0);
}
