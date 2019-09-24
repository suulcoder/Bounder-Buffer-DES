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
#include<bits/stdc++.h>  

/*Este metodo convierte un int en un numero hexadecimal
de tipo string*/
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
   
   return 0;
}

   