// class to derive event weights for b tag
// for more details check https://twiki.cern.ch/twiki/bin/view/CMS/BTagSFMethods#b_tagging_efficiency_in_MC_sampl

#include <string>
#include <vector>
#include <utility>
#include "BTagCalibrationStandalone.cc"
#include "TFile.h"
#include "TH1F.h"
#include "TLorentzVector.h"


#ifndef BTagSF_H
#define BTagSF_H

class bTagSF
{
    public:
        enum WP {loose = 0, medium = 1, tight = 2};
        enum SFsyst {central = 0, up = 1, down = 2};
        //bTagSF(std::string SFfilename);
        bTagSF(std::string SFfilename, std::string effFileName);
        ~bTagSF();
        float getSF (WP wpt, SFsyst syst, int jetFlavor, float pt, float eta);
        float getEff (WP wpt, int jetFlavor, float pt, float eta); // FIXME: to do: retrieve MC efficiency from a data format
   
        float getEvtWeight (std::vector <float > CSVscore, std::vector<TLorentzVector> jets_tlv, std::vector<int> jets_HadronFlavour, SFsyst syst = central);
    private:
        // related to scale factors
        BTagCalibrationStandalone m_calib;

        // for b jets
        BTagCalibrationReaderStandalone m_reader[3]; // 0: loose, 1: medium, 2: tight
        BTagCalibrationReaderStandalone m_reader_up[3]; // 0: loose, 1: medium, 2: tight
        BTagCalibrationReaderStandalone m_reader_do[3]; // 0: loose, 1: medium, 2: tight

        // for c jets
        BTagCalibrationReaderStandalone m_reader_c[3]; // 0: loose, 1: medium, 2: tight
        BTagCalibrationReaderStandalone m_reader_c_up[3]; // 0: loose, 1: medium, 2: tight
        BTagCalibrationReaderStandalone m_reader_c_do[3]; // 0: loose, 1: medium, 2: tight

        // for udsg jets
        BTagCalibrationReaderStandalone m_reader_udsg[3]; // 0: loose, 1: medium, 2: tight
        BTagCalibrationReaderStandalone m_reader_udsg_up[3]; // 0: loose, 1: medium, 2: tight
        BTagCalibrationReaderStandalone m_reader_udsg_do[3]; // 0: loose, 1: medium, 2: tight

        BTagCalibrationReaderStandalone* m_readers [3][3][3]; // [b, c, udsg] [central, up, down] [loose, medium, tight] 

        // related to b tag efficiency
        TFile* m_fileEff;
        TH1F* m_hEff [3][3]; // [0: loose, 1: medium, 2: tight] [0: b, 1: c 2: udsg]
};


#endif
