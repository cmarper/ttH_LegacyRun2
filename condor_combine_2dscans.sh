#!/bin/sh
ulimit -s unlimited
set -e
cd /afs/cern.ch/user/c/cmartinp/Legacy/combine/CMSSW_10_2_13/src
export SCRAM_ARCH=slc7_amd64_gcc700
source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scramv1 runtime -sh`
cd /afs/cern.ch/user/c/cmartinp/Legacy/combine/CMSSW_10_2_13/src/CombineHarvester/fits/MA_10May_step3/

if [ $1 -eq 0 ]; then
  combine -M MultiDimFit combo_ttHmultilep_WS.root --cminDefaultMinimizerStrategy 0 -n For2D_ttH_tH_68 --fastScan --cl=0.68 --algo contour2d --points=100 --redefineSignalPOIs r_ttH,r_tH --setParameterRanges r_ttH=0,2:r_tH=-8,18 --setParameters r_ttZ=1.0,r_ttW=1.0
fi

if [ $1 -eq 1 ]; then
  combine -M MultiDimFit combo_ttHmultilep_WS.root --cminDefaultMinimizerStrategy 0 -n For2D_ttH_tH_95 --fastScan --cl=0.95 --algo contour2d --points=100 --redefineSignalPOIs r_ttH,r_tH --setParameterRanges r_ttH=0,2:r_tH=-8,18 --setParameters r_ttZ=1.0,r_ttW=1.0
fi

if [ $1 -eq 2 ]; then
  combine -M MultiDimFit combo_ttHmultilep_WS.root --cminDefaultMinimizerStrategy 0 -n For2D_ttH_ttZ_68 --fastScan --cl=0.68 --algo contour2d --points=100 --redefineSignalPOIs r_ttH,r_ttZ --setParameterRanges r_ttH=0,2:r_ttZ=0,2 --setParameters r_tH=1.0,r_ttW=1.0
fi

if [ $1 -eq 3 ]; then
  combine -M MultiDimFit combo_ttHmultilep_WS.root --cminDefaultMinimizerStrategy 0 -n For2D_ttH_ttZ_95 --fastScan --cl=0.95 --algo contour2d --points=100 --redefineSignalPOIs r_ttH,r_ttZ --setParameterRanges r_ttH=0,2:r_ttZ=0,2 --setParameters r_tH=1.0,r_ttW=1.0
fi

if [ $1 -eq 4 ]; then
  combine -M MultiDimFit combo_ttHmultilep_WS.root --cminDefaultMinimizerStrategy 0 -n For2D_ttH_ttW_68 --fastScan --cl=0.68 --algo contour2d --points=100 --redefineSignalPOIs r_ttH,r_ttW --setParameterRanges r_ttH=0,2:r_ttW=0,3 --setParameters r_tH=1.0,r_ttZ=1.0
fi

if [ $1 -eq 5 ]; then
  combine -M MultiDimFit combo_ttHmultilep_WS.root --cminDefaultMinimizerStrategy 0 -n For2D_ttH_ttW_95 --fastScan --cl=0.95 --algo contour2d --points=100 --redefineSignalPOIs r_ttH,r_ttW --setParameterRanges r_ttH=0,2:r_ttW=0,3 --setParameters r_tH=1.0,r_ttZ=1.0
fi

if [ $1 -eq 6 ]; then
  combine -M MultiDimFit combo_ttHmultilep_WS.root --cminDefaultMinimizerStrategy 0 -n For2D_ttZ_ttW_68 --fastScan --cl=0.68 --algo contour2d --points=100 --redefineSignalPOIs r_ttZ,r_ttW --setParameterRanges r_ttZ=0,2:r_ttW=0,3 --setParameters r_ttH=1.0,r_tH=1.0
fi

if [ $1 -eq 7 ]; then
  combine -M MultiDimFit combo_ttHmultilep_WS.root --cminDefaultMinimizerStrategy 0 -n For2D_ttZ_ttW_95 --fastScan --cl=0.95 --algo contour2d --points=100 --redefineSignalPOIs r_ttZ,r_ttW --setParameterRanges r_ttZ=0,2:r_ttW=0,3 --setParameters r_ttH=1.0,r_tH=1.0
fi
