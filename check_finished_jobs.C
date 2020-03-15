#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;


bool CheckWord(char* filename, char* search){
    int offset; 
    string line;
    ifstream Myfile;
    Myfile.open(filename);

    if(Myfile.is_open()){
        while(!Myfile.eof()){
            getline(Myfile,line);
            if ((offset = line.find(search, 0)) != string::npos) {
                cout << "mv "<<filename <<" done/"<< endl;
                return true;
                break;
            }
        }
        Myfile.close();
    }
    else
        cout<<"Unable to open file "<<filename<<endl;

    return false;
}


int loadfiles (vector<char*> fileset){

    for(unsigned int i=0; i<fileset.size(); i++){
        //CheckWord(fileset.at(i), "FINISHED");
        //CheckWord(fileset.at(i), "***FINISHED SUCCESSFULLY***");
        CheckWord(fileset.at(i), "4l CR fake");
    }

    return 0;
}


void test(){

    vector<char*> myfiles;

    //myfiles.push_back("convert_Oct19v1_Data_2016_SingleElectron_BlockD_10.sh.o544915"); 

    myfiles.push_back("split_Oct19v1_MC_2017_ZZTo4L_ext1_11_JECdown.sh.o616007");
    myfiles.push_back("split_Oct19v1_MC_2017_ZZTo4L_ext1_10_JECdown.sh.o616006");
    myfiles.push_back("split_Oct19v1_MC_2017_ZZTo4L_ext1_5_JECdown.sh.o616001");
    myfiles.push_back("split_Oct19v1_MC_2017_ZZTo4L_ext1_7_JECdown.sh.o616003");
    myfiles.push_back("split_Oct19v1_MC_2017_ZZTo4L_ext1_6_JECdown.sh.o616002");
    myfiles.push_back("split_Oct19v1_MC_2017_ZZTo4L_ext1_4_JECdown.sh.o616000");
    myfiles.push_back("split_Oct19v1_MC_2017_ZZTo4L_ext1_9_JECdown.sh.o616005");
    myfiles.push_back("split_Oct19v1_MC_2017_ZZTo4L_ext1_3_JECdown.sh.o615999");
    myfiles.push_back("split_Oct19v1_MC_2017_ZZTo4L_ext1_8_JECdown.sh.o616004");
    myfiles.push_back("split_Oct19v1_MC_2017_ZZTo4L_ext1_2_JECdown.sh.o615998");
    myfiles.push_back("split_Oct19v1_MC_2017_ZZTo4L_ext1_0_JECdown.sh.o615996");
    myfiles.push_back("split_Oct19v1_MC_2017_ZZTo4L_ext1_1_JECdown.sh.o615997");

    loadfiles(myfiles);

}