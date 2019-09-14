#include<bits/stdc++.h> 
using namespace std; 

// convierte de hexadecimal a binario
// @parametros
// hexString: string en formato hexadecimal con tamaño 16
// return: string con formato binario de tamaño 64
string hexToBin(string hexString){ 
	unordered_map<char, string> mp;
	//Equivalencias de cada caracter de HEX a BIN
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
		//Concatenacion de los caracteres transformados segun equivalencias
		binString+= mp[hexString[i]]; 
	} 
	return binString;  
	// devuelve el string en binario en formato string
} 

// convierte del formato binario a hexadecimal 
// @parametros
// binString: string en formato binario de tamaño 64
// return: string en formato hexadecimal format de tamaño 16
string binToHex(string binString){ 
	unordered_map<string, string> mp; 
	//Equivalencias de cada caracter de BIN a HEX
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
		//Se recorre el string en formato binario en bloque de 4 caracteres
		//para buscar el bloque en las equivalencias
		string ch=""; 
		ch+= binString[i]; 
		ch+= binString[i+1]; 
		ch+= binString[i+2]; 
		ch+= binString[i+3]; 
		//Concatenacion de los caracteres transformados segun equivalencias
		hex+= mp[ch]; 
	} 
	return hex;
	// devuelve el string en hexadecimal en formato string 
} 

// permutacion de un (formato binario) string con un arreglo dado
// @parametros
// k: el string binario a permutar
// arr: arreglo a permutar
// n: veces a permutar
// return: String en formato binario permutado
string permute(string k, int* arr, int n){ 
	string per=""; 
	for(int i=0; i<n ; i++){ 
		per+= k[arr[i]-1]; 
	} 
	return per; 
} 

// corre a la izquierda un string un numero de veces determiando
// @parametros
// key: String en binario que se correra a la izquierda
// shifts: numero de veces que se correra
// return: string corrido
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
// 	METODO DE ENCRIPTACION
// parametros
// plainText: el string del texto vacio
// roundKeysBin: vector de los roundKeys en binario
string encrypt(string plainText, vector<string> roundKeysBin){ 
	// convertir 16 hexadecimal caracteres a string de 64 bits
	plainText= hexToBin(plainText); 
	
	// tabla 2 - Tabla Inicial de Permutacion
	int initial_perm[64]= 
	{ 58,50,42,34,26,18,10,2, 
		60,52,44,36,28,20,12,4, 
		62,54,46,38,30,22,14,6, 
		64,56,48,40,32,24,16,8, 
		57,49,41,33,25,17,9,1, 
		59,51,43,35,27,19,11,3, 
		61,53,45,37,29,21,13,5, 
		63,55,47,39,31,23,15,7 
	}; 
	// ejecutar la permutacion inicial
	plainText= permute(plainText, initial_perm, 64); 
	cout<<"String en HEX Despues de Permutacion Inicial: "<<binToHex(plainText)<<endl; 
	
	// split the 64 bit permuted string in two halves
	string left= plainText.substr(0, 32); 
	string right= plainText.substr(32, 32); 
	cout<<"After splitting: L0="<<binToHex(left) <<" R0="<<binToHex(right)<<endl; 
	
	// table 3 - expansion D-box table  or expansion permutation
	int exp_d[48]= 
	{ 32,1,2,3,4,5,4,5, 
		6,7,8,9,8,9,10,11, 
		12,13,12,13,14,15,16,17, 
		16,17,18,19,20,21,20,21, 
		22,23,24,25,24,25,26,27, 
		28,29,28,29,30,31,32,1 
	}; 
	
	// table 4 - S-box table 
	int sBox[8][4][16]= 
	{{ 
		14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7, 
		0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8, 
		4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0, 
		15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 
	}, 
	{ 
		15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10, 
		3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5, 
		0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15, 
		13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 
	}, 
	{ 
		10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8, 
		13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1, 
		13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7, 
		1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 
	}, 
	{ 
		7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15, 
		13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9, 
		10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4, 
		3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 
	}, 
	{ 
		2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9, 
		14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6, 
		4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14, 
		11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 
	}, 
	{ 
		12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11, 
		10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8, 
		9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6, 
		4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 
	}, 
	{ 
		4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1, 
		13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6, 
		1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2, 
		6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 
	}, 
	{ 
		13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7, 
		1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2, 
		7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8, 
		2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 
	}}; 
	
	//table 4 - straight permutation table 
	int straightPermutationTable[32]= 
	{ 16,7,20,21, 
		29,12,28,17, 
		1,15,23,26, 
		5,18,31,10, 
		2,8,24,14, 
		32,27,3,9, 
		19,13,30,6, 
		22,11,4,25 
	}; 
	
	cout<<endl; 
    // starts the process of the 16 rounds
	for(int i=0; i<16; i++){ 
		//Expansion D-box
		// expands the right 32bit string to a 48 bit string 
		string right_expanded= permute(right, exp_d, 48); 
		
		// XOR RoundKey[i] and right_expanded  (48 bits both)
        // this is just used to control the process of the s-boxes
		string x= xor_(roundKeysBin[i], right_expanded); 
		
		//S-boxes 
		string op=""; 
		for(int i=0;i<8; i++){ 
			int row= 2*int(x[i*6]-'0')+ int(x[i*6 +5]-'0'); 
			int col= 8*int(x[i*6 +1 ]-'0')+ 4*int(x[i*6 +2]-'0')+ 
								2*int(x[i*6 +3]-'0')+ int(x[i*6 +4]-'0'); 
			int val= sBox[i][row][col]; 
			op+= char(val/8+ '0'); 
			val= val%8; 
			op+= char(val/4+ '0'); 
			val= val%4; 
			op+= char(val/2+ '0'); 
			val= val%2; 
			op+= char(val+ '0'); 
		} 
		//Straight D-box 
		// converts op, to 32 bits again using the straight permutation table
		op= permute(op, straightPermutationTable, 32); 
		
		//XOR left and op 
		x= xor_(op, left); 
		
		// now left is the 32 previous xor_ result
		left= x; 
		
		//Swapper
		// 
		if(i!= 15){ 
			// left contains the (i-1)-th 32 bit right side
			// right has the i-th 32 bit transformed side 
			swap(left, right); 
		} 
		cout<<"Round "<<i+1<<" "<<binToHex(left)<<" "<<binToHex(right)<<endl; 
	} 
	
	// combine both halves 
	string combine= left+right; 
	
	// table 5 - final permutation table 
	int finalPermutationTable[64]= 
	{ 40,8,48,16,56,24,64,32, 
		39,7,47,15,55,23,63,31, 
		38,6,46,14,54,22,62,30, 
		37,5,45,13,53,21,61,29, 
		36,4,44,12,52,20,60,28, 
		35,3,43,11,51,19,59,27, 
		34,2,42,10,50,18,58,26, 
		33,1,41,9,49,17,57,25 
	}; 
	
	// apply final permutation 
	string cipher= binToHex(permute(combine, finalPermutationTable, 64)); 
	return cipher;
}
int main(){ 
	string plainText, key; 

	/*cout<<"Ingrese una texto de 16 caracteres (en hexadecimal): "; 
	cin>>plainText; 
	cout<<"Ingrese una llave inicial de 16 caracteres (en hexadecimal): "; 
	cin>>key;*/
	
	// plainText= "123456ABCD132536"; 
	// key= "AABB09182736CCDD"; 

    plainText= "6942069420694206"; 
	key= "DDCC63728190BABA"; 


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
	}
    cout<<"\nEncryption:\n\n"; 
	string cipher= encrypt(plainText, roundKeysBin); 
	cout<<"\nCipher Text: "<<cipher<<endl; 
	
	cout<<"\nDecryption\n\n"; 
	reverse(roundKeysBin.begin(), roundKeysBin.end()); 
	string text= encrypt(cipher, roundKeysBin); 
	cout<<"\nPlain Text: "<<text<<endl;
} 
