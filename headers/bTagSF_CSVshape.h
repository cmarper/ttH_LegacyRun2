// class to derive event weights for b tag
// for more details check https://twiki.cern.ch/twiki/bin/view/CMS/BTagSFMethods#b_tagging_efficiency_in_MC_sampl

#include <string>
#include <vector>
#include <utility>
#include "BTagCalibrationStandalone.cc"
#include "TFile.h"
#include "TH1F.h"
#include "TLorentzVector.h"


#ifndef BTagSF_CSVshape_H
#define BTagSF_CSVshape_H

class bTagSF_CSVshape
{

     public:
        enum SFsyst {central = 0, JESUp = 1, JESDown = 2, LFUp = 3, LFDown = 4, HFUp = 5, HFDown = 6, HFStats1Up = 7, HFStats1Down = 8, HFStats2Up = 9, HFStats2Down = 10, LFStats1Up = 11, LFStats1Down = 12, LFStats2Up = 13, LFStats2Down = 14, CFErr1Up = 15, CFErr1Down = 16, CFErr2Up = 17, CFErr2Down = 18};
        bTagSF_CSVshape(std::string SFfilename);
        ~bTagSF_CSVshape();
        float getSF (SFsyst syst, int jetFlavor, float pt, float eta, float csv);   
        float getEvtWeight (std::vector <float> CSVscore, std::vector<TLorentzVector> jets_tlv, std::vector<int> jets_HadronFlavour, SFsyst syst = central);
     
     private:
        // related to scale factors
        BTagCalibrationStandalone m_calib;

        BTagCalibrationReaderStandalone m_reader;
        BTagCalibrationReaderStandalone m_reader_JESUp;
        BTagCalibrationReaderStandalone m_reader_JESDown;
	BTagCalibrationReaderStandalone m_reader_LFUp;
	BTagCalibrationReaderStandalone m_reader_LFDown;
	BTagCalibrationReaderStandalone m_reader_HFUp;
	BTagCalibrationReaderStandalone m_reader_HFDown;
	BTagCalibrationReaderStandalone m_reader_HFStats1Up;
	BTagCalibrationReaderStandalone m_reader_HFStats1Down;
	BTagCalibrationReaderStandalone m_reader_HFStats2Up;
	BTagCalibrationReaderStandalone m_reader_HFStats2Down;
	BTagCalibrationReaderStandalone m_reader_LFStats1Up;
	BTagCalibrationReaderStandalone m_reader_LFStats1Down;
	BTagCalibrationReaderStandalone m_reader_LFStats2Up;
	BTagCalibrationReaderStandalone m_reader_LFStats2Down;
	BTagCalibrationReaderStandalone m_reader_CFErr1Up;
	BTagCalibrationReaderStandalone m_reader_CFErr1Down;
	BTagCalibrationReaderStandalone m_reader_CFErr2Up;
	BTagCalibrationReaderStandalone m_reader_CFErr2Down;

};


#endif
