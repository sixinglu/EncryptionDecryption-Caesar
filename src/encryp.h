//------------------------------------------------------------------------------------------------
// Author: Sixing Lu
// Date Created: 6 Febuary 2014
//
// Description: The declarasion of class encryption
//------------------------------------------------------------------------------------------------
#include <vector>
#include <string>
#ifndef ENCRYP_H
#define ENCRYP_H
using namespace std;

class Encryp{
public:
	string tocode;
	string encoded;
	string decoded;
	bool read_file(char* filename);
	vector<pair<string,float> > cal_freq_g1(string tobecalu);
	vector<vector<int> > cal_freq_g2(string tobecalu);
	void encryp_caesar();
	void decode_caesar(vector<pair<string,float> > gram1);
	
	void QuickSortDiff(vector<pair<string,float> > &difference,int p, int r);
	int Partition_Diff(vector<pair<string,float> > &difference,int p, int r);
	int GetN(char ori,char tabl);

};



#endif