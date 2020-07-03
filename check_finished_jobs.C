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
        CheckWord(fileset.at(i), "4l CR fake");
    }

    return 0;
}


void test(){

    vector<char*> myfiles;

    //myfiles.push_back("split_Oct19v1_MC_2016_THQ_ctcvcp_1_JECup.sh.o617002");

    myfiles.push_back("split_Oct19v1_MC_2016_TTJets_DiLept_ext1_0_JECup.sh.o625204");
    myfiles.push_back("split_Oct19v3_MC_2016_TTJets_SingleLeptFromTbar_ext1_0_JECdown.sh.o625207");
    myfiles.push_back("split_Oct19v3_MC_2016_TTJets_SingleLeptFromTbar_ext1_0_JECup.sh.o625205");
    myfiles.push_back("split_Oct19v1_MC_2016_TTJets_DiLept_ext1_0_JECdown.sh.o625206");
    
    loadfiles(myfiles);

}
