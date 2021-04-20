
#include "AES.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>


using namespace std;
void Str2Hex(string str, ofstream& out)
{
	for (int i = 0; i < str.size(); i++)
	{
		out << hex << (int)(unsigned char)str[i] << "|";
	}
}

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

void ECB_Enc(ifstream& pltxt, ofstream& ciptxt, int nb, string(*encFunc)(string, string))
{
	string res, plaintext,key;
	getline(pltxt, key);

	getline(pltxt, plaintext);
	ciptxt << key << endl;
	plaintext = BytePadding(plaintext, nb);

	for (int i = 0; i < plaintext.size(); i += nb)
	{
		string tmp;

		tmp = plaintext.substr(i, nb);
		tmp = encFunc(tmp, key);

		Str2Hex(tmp, ciptxt);
		res.append(tmp);
	}

	ciptxt << endl << res;

}
void ECB_Dec(ifstream& pltxt, ofstream& out, int nb, string(*decFunc)(string, string))
{
	string res, ciphertext, key;
	getline(pltxt, key);

	getline(pltxt, ciphertext);
	getline(pltxt, ciphertext);

	int i = 0;
	for (; i < ciphertext.size() - nb; i += nb)
	{
		string tmp;

		tmp = ciphertext.substr(i, nb);
		tmp = decFunc(tmp, key);

		Str2Hex(tmp, out);
		res.append(tmp);
	}
	string tmp;

	tmp = ciphertext.substr(i, nb);
	tmp = decFunc(tmp, key);
	if (nb == tmp[nb - 1])
		return;
	tmp = tmp.substr(0, (nb - (unsigned int)tmp[nb - 1]));
	Str2Hex(tmp, out);
	res.append(tmp);
	out << endl << res;

}

int main()
{
	ifstream	fip("Ciphertext.txt");
	ofstream fop;

	fop.open("DecPlaintext.txt", ios::out);
	// Câu lệnh dùng đề mã hóa
	ECB_Dec(fip, fop, 16, AES_Decrypt);
	// Câu lệnh dùng đề mã hóa
	//CBC_Dec(fip, fop, 16, AES_Decrypt);

	fip.close();
	fop.close();
	return 0;
}