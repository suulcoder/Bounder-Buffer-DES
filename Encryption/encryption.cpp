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
int main(){ 
	string plainText, key; 

	/*cout<<"Ingrese una texto de 16 caracteres (en hexadecimal): "; 
	cin>>plainText; 
	cout<<"Ingrese una llave inicial de 16 caracteres (en hexadecimal): "; 
	cin>>key;*/
	
	plainText= "123456ABCD132536"; 
	key= "AABB09182736CCDD"; 


	// key must be in binary	
	// apply hexToBin to the Hex key 
	key= hexToBin(key); 
	
	// table 0 - table without the 8i-th bit 
	int parityBitDropTable[56]= 
	{ 57,49,41,33,25,17,9, 
		1,58,50,42,34,26,18, 
		10,2,59,51,43,35,27, 
		19,11,3,60,52,44,36,		 
		63,55,47,39,31,23,15, 
		7,62,54,46,38,30,22, 
		14,6,61,53,45,37,29, 
		21,13,5,28,20,12,4 
	}; 
	
	// getting 56 bit key from 64 bit without the parity bits 
	key= permute(key, parityBitDropTable, 56); // new key without parity 
	
	// table 1- number of shifts per round table 
	int shift_table[16]= 
	{ 1, 1, 2, 2, 
		2, 2, 2, 2, 
		1, 2, 2, 2, 
		2, 2, 2, 1 
	}; 
	
	// key compression table
	int keyCompressionTable[48]= 
	{ 14,17,11,24,1,5, 
		3,28,15,6,21,10, 
		23,19,12,4,26,8, 
		16,7,27,20,13,2, 
		41,52,31,37,47,55, 
		30,40,51,45,33,48, 
		44,49,39,56,34,53, 
		46,42,50,36,29,32 
	}; 
	
	// split the 56 bit key into to halves
	string left= key.substr(0, 28); 
	string right= key.substr(28, 28); 
	
	vector<string> roundKeysBin;//roundKeysBin for RoundKeys in binary 
	vector<string> roundKeysHex;//roundKeysHex for RoundKeys in hexadecimal 

	for(int i=0; i<16; i++){ 
		// shift the halves according to table 1
		left= shift_left(left, shift_table[i]); 
		right= shift_left(right, shift_table[i]); 
		
		// combine halves to get a 56 bit string
		string combine= left + right; 
		
		// key compression to 48 bits
		string RoundKey= permute(combine, keyCompressionTable, 48); 
		
        // push the key to the last position of both vectors
		roundKeysBin.push_back(RoundKey); 
		roundKeysHex.push_back(binToHex(RoundKey)); 
	}
} 
