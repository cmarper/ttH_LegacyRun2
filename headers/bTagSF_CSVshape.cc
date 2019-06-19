#include "bTagSF_CSVshape.h"
#include "TLorentzVector.h"
#include "TString.h"
#include "TMath.h"

using namespace std;




bTagSF_CSVshape::bTagSF_CSVshape(std::string SFfilename) :
    
    m_calib("CSVv2", SFfilename.c_str()) ,
    m_reader(&m_calib , BTagEntry::OP_RESHAPING,  "iterativefit", "central"),
    m_reader_JESUp(&m_calib , BTagEntry::OP_RESHAPING,  "iterativefit", "up_jes"),
    m_reader_JESDown(&m_calib , BTagEntry::OP_RESHAPING,  "iterativefit", "down_jes"),
    m_reader_LFUp(&m_calib , BTagEntry::OP_RESHAPING,  "iterativefit", "up_lf"),
    m_reader_LFDown(&m_calib , BTagEntry::OP_RESHAPING,  "iterativefit", "down_lf"),
    m_reader_HFUp(&m_calib , BTagEntry::OP_RESHAPING,  "iterativefit", "up_hf"),
    m_reader_HFDown(&m_calib , BTagEntry::OP_RESHAPING,  "iterativefit", "down_hf"),
    m_reader_HFStats1Up(&m_calib , BTagEntry::OP_RESHAPING,  "iterativefit", "up_hfstats1"),
    m_reader_HFStats1Down(&m_calib , BTagEntry::OP_RESHAPING,  "iterativefit", "down_hfstats1"),
    m_reader_HFStats2Up(&m_calib , BTagEntry::OP_RESHAPING,  "iterativefit", "up_hfstats2"),
    m_reader_HFStats2Down(&m_calib , BTagEntry::OP_RESHAPING,  "iterativefit", "down_hfstats2"),
    m_reader_LFStats1Up(&m_calib , BTagEntry::OP_RESHAPING,  "iterativefit", "up_lfstats1"),
    m_reader_LFStats1Down(&m_calib , BTagEntry::OP_RESHAPING,  "iterativefit", "down_lfstats1"),
    m_reader_LFStats2Up(&m_calib , BTagEntry::OP_RESHAPING,  "iterativefit", "up_lfstats2"),
    m_reader_LFStats2Down(&m_calib , BTagEntry::OP_RESHAPING,  "iterativefit", "down_lfstats2"),
    m_reader_CFErr1Up(&m_calib , BTagEntry::OP_RESHAPING,  "iterativefit", "up_cferr1"),
    m_reader_CFErr1Down(&m_calib , BTagEntry::OP_RESHAPING,  "iterativefit", "down_cferr1"),
    m_reader_CFErr2Up(&m_calib , BTagEntry::OP_RESHAPING,  "iterativefit", "up_cferr2"),
    m_reader_CFErr2Down(&m_calib , BTagEntry::OP_RESHAPING,  "iterativefit", "down_cferr2")

{
 
}

bTagSF_CSVshape::~bTagSF_CSVshape()
{
}

float bTagSF_CSVshape::getSF (SFsyst syst, int jetFlavor, float pt, float eta, float csv)
{
  
    float SF = 1.0;
    
    BTagEntry::JetFlavor flav;
    bool isBFlav = false;
    bool isCFlav = false;
    bool isLFlav = false;
    
    if (abs(jetFlavor) == 5)
    {
        flav = BTagEntry::FLAV_B;
	isBFlav = true;
    }
    else if (abs(jetFlavor) == 4)
    {
        flav = BTagEntry::FLAV_C;
	isCFlav = true;
    }
    else
    {
        flav = BTagEntry::FLAV_UDSG;
	isLFlav = true;
    }

    float csv_SF = csv;
    if(csv < 0.0) csv = -0.05;
    else if(csv > 1.0) csv = 1.0;


    float pt_SF = pt;
    if(pt > 1000.) pt = 999.;

    if( syst == JESUp && !isCFlav) SF = m_reader_JESUp.eval(flav, eta, pt_SF, csv_SF);
    else if( syst == JESDown && !isCFlav) SF = m_reader_JESDown.eval(flav, eta, pt_SF, csv_SF);
    else if( syst == LFUp && isBFlav) SF = m_reader_LFUp.eval(flav, eta, pt_SF, csv_SF);
    else if( syst == LFDown && isBFlav) SF = m_reader_LFDown.eval(flav, eta, pt_SF, csv_SF);
    else if( syst == HFUp && isLFlav) SF = m_reader_HFUp.eval(flav, eta, pt_SF, csv_SF);
    else if( syst == HFDown && isLFlav) SF = m_reader_HFDown.eval(flav, eta, pt_SF, csv_SF);
    else if( syst == HFStats1Up && isBFlav) SF = m_reader_HFStats1Up.eval(flav, eta, pt_SF, csv_SF);
    else if( syst == HFStats1Down && isBFlav) SF = m_reader_HFStats1Down.eval(flav, eta, pt_SF, csv_SF);
    else if( syst == HFStats2Up && isBFlav) SF = m_reader_HFStats2Up.eval(flav, eta, pt_SF, csv_SF);
    else if( syst == HFStats2Down && isBFlav) SF = m_reader_HFStats2Down.eval(flav, eta, pt_SF, csv_SF);
    else if( syst == LFStats1Up && isLFlav) SF = m_reader_LFStats1Up.eval(flav, eta, pt_SF, csv_SF);
    else if( syst == LFStats1Down && isLFlav) SF = m_reader_LFStats1Down.eval(flav, eta, pt_SF, csv_SF);
    else if( syst == LFStats2Up && isLFlav) SF = m_reader_LFStats2Up.eval(flav, eta, pt_SF, csv_SF);
    else if( syst == LFStats2Down && isLFlav) SF = m_reader_LFStats2Down.eval(flav, eta, pt_SF, csv_SF);
    else if( syst == CFErr1Up && isCFlav) SF = m_reader_CFErr1Up.eval(flav, eta, pt_SF, csv_SF);
    else if( syst == CFErr1Down && isCFlav) SF = m_reader_CFErr1Down.eval(flav, eta, pt_SF, csv_SF);
    else if( syst == CFErr2Up && isCFlav) SF = m_reader_CFErr2Up.eval(flav, eta, pt_SF, csv_SF);
    else if( syst == CFErr2Down && isCFlav) SF = m_reader_CFErr2Down.eval(flav, eta, pt_SF, csv_SF);
    else SF = m_reader.eval(flav, eta, pt_SF, csv_SF);

    return SF;
}



float bTagSF_CSVshape::getEvtWeight (std::vector <float> CSVscore, std::vector<TLorentzVector> jets_tlv, std::vector<int> jets_HadronFlavour, SFsyst syst)
{

  float weight = 1.0;
  
  for (unsigned int ijet = 0; ijet < jets_tlv.size(); ijet++)
    {      
      TLorentzVector vJet = jets_tlv[ijet];      
      int flav = jets_HadronFlavour[ijet];
      float CSV = CSVscore[ijet];
      float SF = getSF (syst, flav, vJet.Pt(), vJet.Eta(), CSV);
      weight *= SF;

      /*if((int) syst==5){
	cout<<"pt="<<vJet.Pt()<<" eta="<<vJet.Eta()<<" csv="<<CSV<<" flav="<<flav<<endl;
	cout<<"SF="<<SF<<endl;
	}*/

    }

  return weight;

}


