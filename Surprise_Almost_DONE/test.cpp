#include <iostream> //cout, cin, cerr
#include <unistd.h>
#include <cmath>
#include <fstream> //file processingy
#include <cstdlib> //exit function
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
using namespace std;
#define byte uint8_t
#include<bits/stdc++.h>  

string decimalToHex(int num){
   stringstream my_ss;
   my_ss << hex << num;
   string res = my_ss.str();
   if(res.size()==1){
   	return ('0'+res);	
   }   	
   return res;
 }

int main(int argc, char const *argv[])
{
	string str1;
    int chain = int('\0');
    str1 = decimalToHex(chain);
    cout<<"DECIMAL:"<<chain<<"HEX:"<<str1;

}
	

 