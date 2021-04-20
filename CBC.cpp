/*
Code  Cipher-block chaining

include vào các thư viện Hàm mã hóa 



có 2 hàm main 
Có HAI cách đẻ compile code:
-------------Cách 1: thay các input và hàm để chạy


Cách 2 

------------------------------------ Nếu muốn chạy cmd :
RUN:

	g++ AES.cpp aes enc input.txt output.txt
	g++ AES.cpp aes dec input.txt output.txt

Cấu trúc tập tin khi mã hóa:
 INPUT.TXT :
line1: key
line2: plaintext

OUTPUT.TXT:
line1: Initiality vector
line2: key
line3: Ciphertext Hexa
line4: Ciphertext

Cấu trúc tập tin khi giải mã 
INPUT.TXT :
line1:IV
line2: key
line3: Ciphertext Hexa
line4: Ciphertext

OUTPUT.TXT:
plaintext đã giải mã







*/





#include "AES.h"
#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>



using namespace std;
// Tạo chuỗi nb bit ngẫu nhiên trả về kiểu string
string GenIV(int nb)
{
	string res(nb,(char)0);
	srand((int)time(0));
	int i;
	for ( i= 0; i < res.size(); i++)
	{
		res[i] = (char)(rand() % 256);
	}
	
	return res;
}
// Byte padding bằng ANSI X9.23
string BytePadding(string pltxt, int nb)
{
	int len_pad = nb - (pltxt.length() % nb), i;

	for (i = 0; i < len_pad - 1; i++)
	{
		pltxt.push_back('\0');
	}
	pltxt.push_back((char)len_pad);

	return pltxt;
}

//string StrXOR(string s1, string s2, int sz = 16)
//{
//
//	string res(sz, (char)0);
//	if (sz <= 0)
//		return string("");
//	for (int i = 0; i < sz; i++)
//	{
//		res[i] = s1[i] ^ s2[i];
//	}
//	return res;
//}
void Str2Hex(string str,ofstream & out)
{
	for (int i = 0; i < str.size(); i++)
	{
		out << hex << (int)(unsigned char)str[i] << "|";
	}
}
void CBC_Enc(ifstream& pltxt, ofstream& ciptxt,int nb, string(*encFunc)(string, string))
{
	string key, plaintext,ciphertext;	/// Lưu Key và plaintext từ file truyền vào 
	getline(pltxt, key);
	getline(pltxt, plaintext);

	if (key.size() < nb)
		for (int i = key.size(); i < nb; i++)
			key.push_back('\0');

	plaintext = BytePadding(plaintext, nb);

	int plsize, i = nb;
	plsize = plaintext.size();
	
	string initvec= GenIV(nb); // = GenIV(nb)
	string blockcip,res;
	cout << initvec;
	ciptxt << initvec << endl;
	ciptxt << key << endl;
	blockcip = encFunc(StrXOR(initvec, plaintext.substr(0, nb)), key);

	Str2Hex(blockcip,ciptxt);
	res.append(blockcip);
	while (i < plsize)
	{
		string block = plaintext.substr(i, nb);
		block = StrXOR(blockcip, block);
		blockcip = encFunc(block, key);
		Str2Hex(blockcip, ciptxt);
		res.append(blockcip);
		i += nb;
	}
	ciptxt<<endl << res;
	
}

void CBC_Dec(ifstream& ciptxt, ofstream& out , int nb, string(*decFunc)(string, string))
{
	string ciphertext , iv,key;
	getline(ciptxt, iv);
	getline(ciptxt, key);
	getline(ciptxt, ciphertext);
	getline(ciptxt, ciphertext);

	string blockcip,block,res;
	blockcip = 	ciphertext.substr(0, nb);

	int cipsize = ciphertext.size(), i = nb;
	block = decFunc(blockcip, key);

	block = StrXOR(block, iv);

	Str2Hex(block,out);
	res.append(block);

	for (; i < cipsize-nb ; i+=nb)
	{
		string tmp = blockcip;

		blockcip = ciphertext.substr(i, nb);
		block = decFunc(blockcip, key);
		block = StrXOR(block, tmp); 
		Str2Hex(block, out);
		res.append(block);
	}

	string tmp = blockcip;

	blockcip = ciphertext.substr(i, nb);
	block = decFunc(blockcip, key);
	block = StrXOR(block, tmp);
	
	if (nb == block[nb - 1])
		return;
	block = block.substr(0, (nb - (unsigned int)block[nb - 1]));
	Str2Hex(block, out);
	res.append(block);
	out <<endl <<res;



	


}


//int main()
//{
//	ifstream	fip("plaintext.txt");
//	ofstream fop;
//
//	fop.open("Ciphertext.txt", ios::out);
//	// Câu lệnh dùng đề mã hóa
//	CBC_Enc(fip, fop, 16, AES_Encrypt);
//	// Câu lệnh dùng đề mã hóa
//	//CBC_Dec(fip, fop, 16, AES_Decrypt);
//
//	fip.close();
//	fop.close();
//	return 0;
//}
//int main(int argc, char* argv[])
//{
//	if (argc > 5)
//		cout << "Too many parameter!!!";
//
//
//	ifstream fip(argv[3]);
//	ofstream fop;
//
//	fop.open(argv[4],ios::out);
//	if (strcmp(argv[1], "aes"))
//	{
//		if (strcmp(argv[2], "enc"))
//
//			CBC_Enc(fip, fop, 16, AES_Encrypt);
//		else if (strcmp(argv[2], "dec"))
//
//			CBC_Dec(fip, fop, 16, AES_Decrypt);
//		cout << "Not supported this type";
//
//	}
//	else
//		cout << "Not supported this Algorithm!!!";
//
//	fip.close();
//	fop.close();
//	return 0;
//
//}