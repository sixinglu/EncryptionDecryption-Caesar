//------------------------------------------------------------------------------------------------
//
// Author: Sixing Lu
// Date Created: 6 Febuary 2014
//
// Description: The entrance of encryption
//
//------------------------------------------------------------------------------------------------

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <stdlib.h>
#include <string>
#include "encryp.h"

//------------------------------------------------------------------------------------------------

using namespace std;

//------------------------------------------------------------------------------------------------

int
main(int argc,char* argv[])
{	
	if(argc!=2){
		cout<<"please input directory of the file!"<<endl;
		return -1;
	}

    Encryp encryp;
	if(!encryp.read_file(argv[1])){  // read file into a string
	   return -1;
	}

	vector<pair<string,float> > result_gam1;

	encryp.encryp_caesar();   // encode the readin file 
	result_gam1 =encryp.cal_freq_g1(encryp.encoded); // calculate the gam1 frequency
	encryp.cal_freq_g2(encryp.encoded); // calculate the gam2 frequency
	encryp.decode_caesar(result_gam1); // decode the encoded string



    return 0;
	
}
//------------------------------------------------------------------------------------------------

