#include "bTagSF.h"
#include "TLorentzVector.h"
#include "TString.h"
#include "TMath.h"

using namespace std;




bTagSF::bTagSF(std::string SFfilename, std::string effFileName) :
    
    m_calib("CSVv2", SFfilename.c_str()) ,
    m_reader {
    BTagCalibrationReaderStandalone(&m_calib , BTagEntry::OP_LOOSE,  "comb", "central"),
    BTagCalibrationReaderStandalone(&m_calib , BTagEntry::OP_MEDIUM, "comb", "central"),
    BTagCalibrationReaderStandalone(&m_calib , BTagEntry::OP_TIGHT,  "comb", "central")} ,
    m_reader_up {
    BTagCalibrationReaderStandalone(&m_calib , BTagEntry::OP_LOOSE,  "comb", "up"),
    BTagCalibrationReaderStandalone(&m_calib , BTagEntry::OP_MEDIUM, "comb", "up"),
    BTagCalibrationReaderStandalone(&m_calib , BTagEntry::OP_TIGHT,  "comb", "up")} ,
    m_reader_do {
    BTagCalibrationReaderStandalone(&m_calib , BTagEntry::OP_LOOSE,  "comb", "down"),
    BTagCalibrationReaderStandalone(&m_calib , BTagEntry::OP_MEDIUM, "comb", "down"),
    BTagCalibrationReaderStandalone(&m_calib , BTagEntry::OP_TIGHT,  "comb", "down")} ,
    
    m_reader_c {
    BTagCalibrationReaderStandalone(&m_calib , BTagEntry::OP_LOOSE,  "comb", "central"),
    BTagCalibrationReaderStandalone(&m_calib , BTagEntry::OP_MEDIUM, "comb", "central"),
    BTagCalibrationReaderStandalone(&m_calib , BTagEntry::OP_TIGHT,  "comb", "central")} ,
    m_reader_c_up {
    BTagCalibrationReaderStandalone(&m_calib , BTagEntry::OP_LOOSE,  "comb", "up"),
    BTagCalibrationReaderStandalone(&m_calib , BTagEntry::OP_MEDIUM, "comb", "up"),
    BTagCalibrationReaderStandalone(&m_calib , BTagEntry::OP_TIGHT,  "comb", "up")} ,
    m_reader_c_do {
    BTagCalibrationReaderStandalone(&m_calib , BTagEntry::OP_LOOSE,  "comb", "down"),
    BTagCalibrationReaderStandalone(&m_calib , BTagEntry::OP_MEDIUM, "comb", "down"),
    BTagCalibrationReaderStandalone(&m_calib , BTagEntry::OP_TIGHT,  "comb", "down")} ,

    m_reader_udsg {
    BTagCalibrationReaderStandalone(&m_calib , BTagEntry::OP_LOOSE,  "incl", "central"),
    BTagCalibrationReaderStandalone(&m_calib , BTagEntry::OP_MEDIUM, "incl", "central"),
    BTagCalibrationReaderStandalone(&m_calib , BTagEntry::OP_TIGHT,  "incl", "central")} ,
    m_reader_udsg_up {
    BTagCalibrationReaderStandalone(&m_calib , BTagEntry::OP_LOOSE,  "incl", "up"),
    BTagCalibrationReaderStandalone(&m_calib , BTagEntry::OP_MEDIUM, "incl", "up"),
    BTagCalibrationReaderStandalone(&m_calib , BTagEntry::OP_TIGHT,  "incl", "up")} ,
    m_reader_udsg_do {
    BTagCalibrationReaderStandalone(&m_calib , BTagEntry::OP_LOOSE,  "incl", "down"),
    BTagCalibrationReaderStandalone(&m_calib , BTagEntry::OP_MEDIUM, "incl", "down"),
    BTagCalibrationReaderStandalone(&m_calib , BTagEntry::OP_TIGHT,  "incl", "down")} 
{
    // // [b, c, udsg] [central, up, down] [loose, medium, tight]        = & _up//down [loose, medium, tight]

    m_readers[0][0][0] = & (m_reader[0]) ;
    m_readers[0][0][1] = & (m_reader[1]) ;
    m_readers[0][0][2] = & (m_reader[2]) ;

    m_readers[0][1][0] = & (m_reader_up[0]) ;
    m_readers[0][1][1] = & (m_reader_up[1]) ;
    m_readers[0][1][2] = & (m_reader_up[2]) ;

    m_readers[0][2][0] = & (m_reader_do[0]) ;
    m_readers[0][2][1] = & (m_reader_do[1]) ;
    m_readers[0][2][2] = & (m_reader_do[2]) ;


    m_readers[1][0][0] = & (m_reader_c[0]) ;
    m_readers[1][0][1] = & (m_reader_c[1]) ;
    m_readers[1][0][2] = & (m_reader_c[2]) ;

    m_readers[1][1][0] = & (m_reader_c_up[0]) ;
    m_readers[1][1][1] = & (m_reader_c_up[1]) ;
    m_readers[1][1][2] = & (m_reader_c_up[2]) ;

    m_readers[1][2][0] = & (m_reader_c_do[0]) ;
    m_readers[1][2][1] = & (m_reader_c_do[1]) ;
    m_readers[1][2][2] = & (m_reader_c_do[2]) ;


    m_readers[2][0][0] = & (m_reader_udsg[0]) ;
    m_readers[2][0][1] = & (m_reader_udsg[1]) ;
    m_readers[2][0][2] = & (m_reader_udsg[2]) ;

    m_readers[2][1][0] = & (m_reader_udsg_up[0]) ;
    m_readers[2][1][1] = & (m_reader_udsg_up[1]) ;
    m_readers[2][1][2] = & (m_reader_udsg_up[2]) ;
        
    m_readers[2][2][0] = & (m_reader_udsg_do[0]) ;
    m_readers[2][2][1] = & (m_reader_udsg_do[1]) ;
    m_readers[2][2][2] = & (m_reader_udsg_do[2]) ;


    m_fileEff = new TFile (effFileName.c_str());
 
    TString flavs[3]   = {"b", "c", "udsg"};
    TString WPnames[3] = {"L", "M", "T"};
 
    for (int iWP = 0; iWP < 3; iWP++)
    {
      for (int flav = 0; flav < 3; flav++)
        {
	  TString name = Form("eff_%s_%s", flavs[flav].Data(), WPnames[iWP].Data());
	  m_hEff [iWP][flav] = (TH1F*) m_fileEff->Get(name.Data());
        }
    }
}

bTagSF::~bTagSF()
{
    if (m_fileEff) delete m_fileEff;
}

float bTagSF::getSF (WP wpt, SFsyst syst, int jetFlavor, float pt, float eta)
{
  
    float SF = 1.0;
    
    BTagEntry::JetFlavor flav;
    int myFlavIndex = -1; // indexes in the m_readers array
    int mySystIndex = (int) syst;
    int myWPIndex   = (int) wpt;

    
    if (abs(jetFlavor) == 5)
    {
        flav = BTagEntry::FLAV_B;
        myFlavIndex = 0;
    }
    else if (abs(jetFlavor) == 4)
    {
        flav = BTagEntry::FLAV_C;
        myFlavIndex = 1;
    }
    else
    {
        flav = BTagEntry::FLAV_UDSG;
        myFlavIndex = 2;
    }

    float pt_SF = pt;
    if(flav == BTagEntry::FLAV_B || flav == BTagEntry::FLAV_C){
      if(pt<30.)
	pt_SF = 30.001;
      else if(pt>670.)
	pt_SF = 669.999;
    }

    if(flav == BTagEntry::FLAV_UDSG){
      if(pt<20.)
	pt_SF = 20.001;
      else if(pt>1000.)
	pt_SF = 999.999;
    }

    SF = m_readers[myFlavIndex][mySystIndex][myWPIndex] -> eval(flav, eta, pt_SF);

    if (syst != central)
    {
        
      float SF_central = m_readers[myFlavIndex][(int)central][myWPIndex] -> eval(flav, eta, pt_SF);

        if (flav == BTagEntry::FLAV_B || flav == BTagEntry::FLAV_C)
        {
	  if (pt < 30.0 || pt > 670.0 ) SF = SF_central + 2*(SF-SF_central);
        }
        if (flav == BTagEntry::FLAV_UDSG)
        {
	  if (pt < 20.0 || pt > 1000.0 ) SF = SF_central + 2*(SF-SF_central);
        }
        
    }

    return SF;
}


float bTagSF::getEff (WP wpt, int jetFlavor, float pt, float eta)
{

  int flav;
  if (abs(jetFlavor) == 5) flav = 0;
  else if (abs(jetFlavor) == 4) flav = 1;
  else flav = 2;
  
  TH1F* h = m_hEff [(int) wpt] [flav] ;
  float aEta = TMath::Abs(eta);
  
  int binglobal = h->FindBin (pt, aEta);
  int binx, biny, binz;
  h->GetBinXYZ (binglobal, binx, biny, binz); // converts to x, y bins
  int nx = h->GetNbinsX();
  int ny = h->GetNbinsY();
  
  // under-overflows
  if (binx < 1) binx = 1;
  if (biny < 1) biny = 1;
  if (binx > nx) binx = nx;
  if (biny > ny) biny = ny;
  
  /*
    float minPt = h->GetXaxis()->GetBinLowEdge(1);
    float maxPt = h->GetXaxis()->GetBinLowEdge(nx+1);
    
    float minEta = h->GetYaxis()->GetBinLowEdge(1);
    float maxEta = h->GetYaxis()->GetBinLowEdge(ny+1);
  */

  float eff = h->GetBinContent (binx, biny);
  
  // protection againts wrongly measured efficiencies (low stat) --> reduce pT bin
  while (eff < 0.00000000001 && binx > 0)
    {
      binx-- ;
      eff = h->GetBinContent (binx, biny);
    }
  
  return eff;
}

// returns a collection of weights according to the tested WP
float bTagSF::getEvtWeight (std::vector <float> CSVscore, std::vector<TLorentzVector> jets_tlv, std::vector<int> jets_HadronFlavour, SFsyst syst)
{

  float P_MC = 1.0;
  float P_Data = 1.0;
    
  // float WPtag[3] = {0.605, 0.89, 0.97}; // L, M, T
  float WPtag[3] = {0.460, 0.800, 0.935}; // L, M, T -- 80X 4 inv fb
  
  for (unsigned int ijet = 0; ijet < jets_tlv.size(); ijet++)
    {

      TLorentzVector vJet = jets_tlv[ijet];
      
      int flav = jets_HadronFlavour[ijet];
      float SF[3];
      SF[0] = getSF (loose,  syst, flav, vJet.Pt(), vJet.Eta());
      SF[1] = getSF (medium, syst, flav, vJet.Pt(), vJet.Eta());
      SF[2] = getSF (tight,  syst, flav, vJet.Pt(), vJet.Eta());

      float effBTag[3];
      effBTag[0] = getEff (static_cast<WP> (0), flav, vJet.Pt(), vJet.Eta()) ;
      effBTag[1] = getEff (static_cast<WP> (1), flav, vJet.Pt(), vJet.Eta()) ;
      effBTag[2] = getEff (static_cast<WP> (2), flav, vJet.Pt(), vJet.Eta()) ;

      float CSV = CSVscore[ijet];
      bool tagged[3];
      tagged[0] = (CSV > WPtag[0]);
      tagged[1] = (CSV > WPtag[1]);
      tagged[2] = (CSV > WPtag[2]);

      if(tagged[1]){
	P_MC *= effBTag[1];
	P_Data *= effBTag[1]*SF[1];
      }
      else if(tagged[0]){
	P_MC *= (effBTag[0]-effBTag[1]);
	P_Data *= (effBTag[0]*SF[0]-effBTag[1]*SF[1]);
      }
      else{
	P_MC *= (1-effBTag[0]);
	P_Data *= (1-effBTag[0]*SF[0]);
      }


    }

  // return ratio
  float weight = P_Data/P_MC;

  if (weight < 0.05) 
    {
        cout << "------ NONONO Null weight!!" << endl;
    }
    return weight;


}


