#include <assert.h>
#include "TH2F.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TH2Poly.h"

float get_tauESSF(int year = 2016, int dm = 0, float shift = 0){

    if(year==2016){

      if (dm==0) return 0.994+shift*0.010;
      else if (dm==1 || dm==2) return 0.995+shift*0.009;
      else if (dm==10 || dm ==11) return 1.000+shift*0.011;

    }

    else if(year==2017){

      if (dm==0) return 1.007+shift*0.008;
      else if (dm==1 || dm==2) return 0.998+shift*0.008;
      else if (dm==10) return 1.001+shift*0.009;
      else if (dm==11) return 0.999+shift*0.010;

    }

    else if(year==2018){

      if (dm==0) return 0.987+shift*0.0111;
      else if (dm==1 || dm==2) return 0.995+shift*0.009;
      else if (dm==10 || dm==11) return 0.988+shift*0.008;

    }

    return 1;

}
