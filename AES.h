#ifndef AES_H
#define AES_H
#include <string>
#include <vector>

using namespace std;

string MixColumns(string state);
string Inv_MixColumns(string state);
string SubBytes(string arr, int nB);
string Inv_SubBytes(string arr, int nB);
string ShiftRows(string& arr, int nB);
string Inv_ShiftRows(string& arr, int nB);
string StrXOR(string s1, string s2, int sz = 16);
vector<string> Key_Expand(string k, int nb);
string AES_Encrypt(string m, string key);
string AES_Decrypt(string c, string key);


#endif