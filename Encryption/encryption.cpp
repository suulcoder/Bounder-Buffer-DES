#include<bits/stdc++.h> 
using namespace std; 

// converts hexadecimal to binary
// @params
// hexString: hexadecimal format string of length 16
// return: binary format string of length 64
string hexToBin(string hexString){ 
	unordered_map<char, string> mp; 
	mp['0']= "0000"; 
	mp['1']= "0001"; 
	mp['2']= "0010"; 
	mp['3']= "0011"; 
	mp['4']= "0100"; 
	mp['5']= "0101"; 
	mp['6']= "0110"; 
	mp['7']= "0111"; 
	mp['8']= "1000"; 
	mp['9']= "1001"; 
	mp['A']= "1010"; 
	mp['B']= "1011"; 
	mp['C']= "1100"; 
	mp['D']= "1101"; 
	mp['E']= "1110"; 
	mp['F']= "1111"; 
	string binString=""; 
	for(int i=0; i<hexString.size(); i++){ 
		binString+= mp[hexString[i]]; 
	} 
	return binString;  
	// returns the string in binary, as a string
} 

// converts binary to hexadecimal format
// @params
// binString: binary format string of length 64
// return: hexadecimal format string of length 16
string binToHex(string binString){ 
	unordered_map<string, string> mp; 
	mp["0000"]= "0"; 
	mp["0001"]= "1"; 
	mp["0010"]= "2"; 
	mp["0011"]= "3"; 
	mp["0100"]= "4"; 
	mp["0101"]= "5"; 
	mp["0110"]= "6"; 
	mp["0111"]= "7"; 
	mp["1000"]= "8"; 
	mp["1001"]= "9"; 
	mp["1010"]= "A"; 
	mp["1011"]= "B"; 
	mp["1100"]= "C"; 
	mp["1101"]= "D"; 
	mp["1110"]= "E"; 
	mp["1111"]= "F"; 
	string hex=""; 
	for(int i=0; i<binString.length(); i+=4){ 
		string ch=""; 
		ch+= binString[i]; 
		ch+= binString[i+1]; 
		ch+= binString[i+2]; 
		ch+= binString[i+3]; 
		hex+= mp[ch]; 
	} 
	return hex; 
} 

// permutes a (binary format) string with a given array
// @params
// k: the binary string to permute
// arr: array to permute
// n: number of times to permute
// return: the permuted string in binary format
string permute(string k, int* arr, int n){ 
	string per=""; 
	for(int i=0; i<n ; i++){ 
		per+= k[arr[i]-1]; 
	} 
	return per; 
} 

// shifts left a string a given number of times
// @params
// key: binary string key to shift left
// shifts: number of times to shift
// return: shifted string
string shift_left(string key, int shifts){ 
	string s=""; 
	for(int i=0; i<shifts; i++){ 
		for(int j=1; j<28; j++){ 
			s+= key[j]; 
		} 
		s+= key[0]; 
		key= s; 
		s=""; 
	} 
	return key; 
} 
// performs logical XOR between two binary format strings
// @params
// firstBinString: first binary string
// secondBinString: second binary string
// return: final string with xor applied
string xor_(string firstBinString, string secondBinString){ 
	string ans= ""; 
	for(int i=0; i<firstBinString.size(); i++){ 
		if(firstBinString[i]==secondBinString[i]){ 
			ans+= "0"; 
		}else{ 
			ans+= "1"; 
		} 
	} 
	return ans;
} 
// encrypt method
// params
// pt: the string of the plain text
// rkb: vector of the roundKeys in binary
// rk: vector of the rounKeys in hex
