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

    myfiles.push_back("split_Oct19v1_MC_2018_TTGJets_1_JECdown.sh.o616525");
    myfiles.push_back("split_Oct19v1_MC_2018_WZG_0_JECup.sh.o616458");
    myfiles.push_back("split_Oct19v1_MC_2017_TTTT_0_JECdown.sh.o616511");
    myfiles.push_back("split_Oct19v1_MC_2017_WGToLNuG_0_JECdown.sh.o616496");
    myfiles.push_back("split_Oct19v1_MC_2017_TTGJets_ext1_2_JECdown.sh.o616505");

    loadfiles(myfiles);

}