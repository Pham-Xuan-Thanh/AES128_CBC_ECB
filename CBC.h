#ifndef CBC_H
#define CBC_H



using namespace std;

string GenIV(int nb);
string BytePadding(string pltxt, int nb);
void CBC_Enc(ifstream& pltxt, ofstream& ciptxt, int nb, string(*encFunc)(string, string));
void Str2Hex(string str, ofstream& out);


#endif
