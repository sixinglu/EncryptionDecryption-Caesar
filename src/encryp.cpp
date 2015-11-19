//------------------------------------------------------------------------------------------------
// Author: Sixing Lu
// Date Created: 6 Febuary 2014
//
// Description: The defination of caesar functions
//------------------------------------------------------------------------------------------------
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <ctype.h>
#include <algorithm>
#include "encryp.h"

using namespace std;

// read from the input file
bool Encryp::read_file(char* filename)
{
   ifstream fp;
	fp.open(filename,ios::in);
    if (!fp.is_open()){
      cout<<"cannot open the file! \n"<<endl;
      return 0;
    }

    //std::ifstream openfile(filename);  
	//std::streambuf* buffer;  
	//buffer << fp.rdbuf();  
	//std::string contents(buffer.str());
    std::string str((std::istreambuf_iterator<char>(fp)),std::istreambuf_iterator<char>());  


	this->tocode.assign(str);

    return 1;
}

// calculate the gam1 frequency of string
vector<pair<string,float> > Encryp::cal_freq_g1(string tobecalu)
{
	vector<int> freq(26);
	for(unsigned int j=0;j<freq.size();j++){
		freq[j] =0;
	}

    std::transform(tobecalu.begin(), tobecalu.end(), tobecalu.begin(), ::tolower);
	for(unsigned int i=0;i<tobecalu.size();i++){    
		 if(tobecalu[i]>=97 && tobecalu[i]<=122){
			 int index =tobecalu[i]-97;
			 freq[index]++;
		 }
	}

	vector<pair<string,float> > freq_matrix(26);
	for(int i=97;i<=122;i++){
		char temper =(char)i;
		stringstream ss;
		string name;
		ss << temper;
        ss >> name;
		freq_matrix[i-97]=(make_pair(name,(float)freq[i-97]/tobecalu.size()));
	}

	// printf out
	cout<<"gram1 frequency are:"<<endl;
	for(int i=0;i<26;i++){
		if(freq_matrix[i].second>0){
		    cout<<freq_matrix[i].first<<"  "<<freq_matrix[i].second<<endl;
		}
	}

   return freq_matrix;
}

// calculate the gam2 frequency of string
vector<vector<int> > Encryp::cal_freq_g2(string tobecalu)
{
   vector<vector<int> > freq(26);
	for(unsigned int j=0;j<freq.size();j++){
		for(int i=0;i<26;i++){
		   freq[j].push_back(0);
		}
	}

    std::transform(tobecalu.begin(), tobecalu.end(),tobecalu.begin(), ::tolower);
	for(unsigned int i=0;i<tobecalu.size()-1;i++){   
		 if(tobecalu[i]>=97 && tobecalu[i]<=122 && tobecalu[i+1]>=97 && tobecalu[i+1]<=122 ){
			 int index_row =tobecalu[i]-97;
			 int index_col =tobecalu[i+1]-97;
			 freq[index_row][index_col]++;
		 }
	}

	cout<<"gram2 frequency are:"<<endl;
	for(unsigned int i=0;i<freq.size();i++){
		//bool flag=0;
		for(unsigned int j=0;j<freq[i].size();j++){
			if(freq[i][j]>0){
			   cout<<(char)(i+97)<<(char)(j+97)<<" "<<(float)freq[i][j]/tobecalu.size()<<endl;
			  // flag =1;
			}
		}
		//if(flag==1){
		//	cout<<endl;
		//}
	}
	return freq;
}

// encode the input string
void Encryp::encryp_caesar()
{
	int n =3;
	std::transform(this->tocode.begin(), this->tocode.end(),this->tocode.begin(), ::tolower);
	for(unsigned int i=0;i<this->tocode.size();i++){
		if(this->tocode[i]>=97&&this->tocode[i]<=122){
			char encode =(char)((this->tocode[i]-97+n)%26+97);
			this->encoded.append(1,encode);
		}
	}

	//printf encode 
	cout<<"the encode string is:"<<endl;
	cout<<this->encoded<<endl;


}

// decode the string
void Encryp::decode_caesar(vector<pair<string,float> > gram1)
{
    int n;
   // use frequency to find n
    vector<pair<string,float> > freq_table(26);
    freq_table[0]=(make_pair("e",12.7));
	freq_table[1]=(make_pair("t",9.1));
	freq_table[2]=(make_pair("a",8.2));
	freq_table[3]=(make_pair("o",7.5));
	freq_table[4]=(make_pair("i",7.0));
	freq_table[5]=(make_pair("n",6.7));
	freq_table[6]=(make_pair("s",6.3));
	freq_table[7]=(make_pair("h",6.1));
	freq_table[8]=(make_pair("r",6.0));
	freq_table[9]=(make_pair("d",4.3));
	freq_table[10]=(make_pair("l",4.0));
	freq_table[11]=(make_pair("u",2.8));
	freq_table[12]=(make_pair("c",2.8));
	freq_table[13]=(make_pair("m",2.4));
	freq_table[14]=(make_pair("w",2.4));
	freq_table[15]=(make_pair("f",2.2));
    freq_table[16]=(make_pair("f",2.0));
	freq_table[17]=(make_pair("g",2.0));
	freq_table[18]=(make_pair("p",1.9));
	freq_table[19]=(make_pair("b",1.5));
	freq_table[20]=(make_pair("v",1.0));
	freq_table[21]=(make_pair("k",0.8));
	freq_table[22]=(make_pair("x",0.2));
	freq_table[23]=(make_pair("j",0.2));
	freq_table[24]=(make_pair("q",0.1));
	freq_table[25]=(make_pair("z",0.1));

    this->QuickSortDiff(gram1,0,25);

	vector<int> patten;
	int patten_num =5;
	patten.push_back(0);  // the highest freq
	patten.push_back(1);  // the second highest freq
	patten.push_back(2);  // the third highest freq
	patten.push_back(3);  // the forth highest freq
    patten.push_back(4);  // the fifth highest freq

	vector<int> result_K;
	for(int i=0;i<patten_num;i++){
		result_K.push_back(GetN(gram1[patten[i]].first.at(0),freq_table[patten[i]].first.at(0)));
	}

	for(int i=0;i<patten_num-1;i++){
		if(result_K[i]==result_K[i+1] && abs(gram1[i].second-gram1[i+1].second)<0.01){
			n=result_K[i];
			break;
		}
		n =result_K[0];
	}



	for(unsigned int i=0;i<this->encoded.size();i++){
		char decoded =(char)((26+this->encoded[i]-97-n)%26+97);
		this->decoded.append(1,decoded);
	}

	//printf decode 
	cout<<"the decode string is:"<<endl;
	cout<<this->decoded<<endl;
}

int Encryp::GetN(char cyb,char tabl)
{
	for(int i=0;i<=25;i++){
		//int test1 =(ori-97)%26;
		//int test2 =(tabl-97);
		if((tabl-97+i)%26==(cyb-97)){
			return i;
		}
	}

}

// sorting function
void Encryp::QuickSortDiff(vector<pair<string,float> > &difference,int p, int r)
{
   int q=0;
   if(p>=r){
      return;
   }
   
   q =this->Partition_Diff(difference,p,r);
   this->QuickSortDiff(difference,p,q-1);
   this->QuickSortDiff(difference,q+1,r);
   
   return;
}

int Encryp::Partition_Diff(vector<pair<string,float> > &difference,int p, int r)
{
	float key =0;
	float value =0;
	int temp =(p+r)/2;
    int i =p;
	int j =r;
	pair<string,float> keynode(difference[temp]);

	key =keynode.second;  // the difference between 1&0
	while(i<j){
		value =difference[j].second;
		while(temp<j && value<=key){
		     j--;
			 value =difference[j].second;
		}
		if(i<j){
			difference[temp] =difference[j];
			temp =j;
		}

		value =difference[i].second;
		while(i<temp && value>=key){
			i++;
			value =difference[i].second;
		}
		if(i<j){
            difference[temp] =difference[i];
			temp =i;
		}       
	}
	difference[temp] =keynode;

	return temp;  
}