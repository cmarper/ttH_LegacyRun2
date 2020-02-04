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
        CheckWord(fileset.at(i), "***FINISHED SUCCESSFULLY***");
        //CheckWord(fileset.at(i), "4l CR fake");
    }

    return 0;
}


void test(){

    vector<char*> myfiles;

    //myfiles.push_back("convert_Oct19v1_Data_2016_SingleElectron_BlockD_10.sh.o544915"); -> wont print
    myfiles.push_back("convert_Oct19v1_Data_2018_EGamma_BlockA_21.sh.o577237");
    myfiles.push_back("convert_Oct19v1_Data_2018_EGamma_BlockA_13.sh.o577236");
    myfiles.push_back("convert_Oct19v1_Data_2018_SingleMuon_BlockB_12.sh.o577293");
    myfiles.push_back("convert_Oct19v1_Data_2018_EGamma_BlockC_13.sh.o577283");
    myfiles.push_back("convert_Oct19v1_Data_2018_EGamma_BlockA_30.sh.o577274");
    myfiles.push_back("convert_Oct19v1_Data_2018_SingleMuon_BlockB_24.sh.o577292");
    myfiles.push_back("convert_Oct19v1_Data_2018_EGamma_BlockA_32.sh.o577257");
    myfiles.push_back("convert_Oct19v1_Data_2018_EGamma_BlockA_28.sh.o577262");
    myfiles.push_back("convert_Oct19v1_Data_2018_EGamma_BlockC_12.sh.o577282");
    myfiles.push_back("convert_Oct19v1_Data_2018_EGamma_BlockA_42.sh.o577266");
    myfiles.push_back("convert_Oct19v1_Data_2018_EGamma_BlockC_24.sh.o577287");
    myfiles.push_back("convert_Oct19v1_Data_2018_EGamma_BlockA_34.sh.o577263");
    
    loadfiles(myfiles);

}