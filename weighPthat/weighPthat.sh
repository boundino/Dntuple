#!/bin/bash

###

##pp
#Dzero
sed '1iconst int nBins=6; float pthatBin[nBins]={0,5,10,15,30,50}; float crosssec[nBins+1]={7.085e+09,1.593e+08,9.881e+06,1.975e+06,9.484e+04,9.144e+03,0.}; int genSignal[2]={1,2};' weighPthat.C > weighPthat_tmp.C
INPUTFILE="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0_noweight.root";
OUTPUTFILE="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0_pthatweight.root";

#Dstar 3p
#sed '1iconst int nBins=5; float pthatBin[nBins]={5,10,15,30,50}; float crosssec[nBins+1]={9.349e+07,6.291e+06,1.230e+06,6.469e+04,6.646e+03,0.}; int genSignal[2]={9,10};' weighPthat.C > weighPthat_tmp.C
#INPUTFILE="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_noweight.root";
#OUTPUTFILE="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_pthatweight.root";

#Dstar 5p
#sed '1iconst int nBins=5; float pthatBin[nBins]={5,10,15,30,50}; float crosssec[nBins+1]={9.481e+07,6.207e+06,1.252e+06,6.522e+04,6.072e+03,0.}; int genSignal[2]={11,12};' weighPthat.C > weighPthat_tmp.C
#INPUTFILE="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpipipi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpipipi_noweight.root";
#OUTPUTFILE="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpipipi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpipipi_pthatweight.root";

##pbpb
#Dzero
#sed '1iconst int nBins=6; float pthatBin[nBins]={0,5,10,15,30,50}; float crosssec[nBins+1]={7.085e+09,1.593e+08,9.881e+06,1.975e+06,9.484e+04,9.144e+03,0.}; int genSignal[2]={1,2};' weighPthat.C > weighPthat_tmp.C
#INPUTFILE="/data/wangj/MC2015/Dntuple/PbPb/ntD_PbPb_Dzero_kpi/ntD_EvtBase_20160127_Dfinder_20151229_Pythia8_prompt_D0_noweight.root";
#OUTPUTFILE="/data/wangj/MC2015/Dntuple/PbPb/ntD_PbPb_Dzero_kpi/ntD_EvtBase_20160127_Dfinder_20151229_Pythia8_prompt_D0_pthatweight.root";

#Dstar 3p
#sed '1iconst int nBins=5; float pthatBin[nBins]={5,10,15,30,50}; float crosssec[nBins+1]={9.349e+07,6.291e+06,1.230e+06,6.469e+04,6.646e+03,0.}; int genSignal[2]={9,10};' weighPthat.C > weighPthat_tmp.C
#INPUTFILE="/data/wangj/MC2015/Dntuple/PbPb/ntD_PbPb_Dstar_D0kpi/ntD_EvtBase_20160104_Dfinder_20151229_PbPb_Pythia8D0kpi_Dstar_noweight.root";
#OUTPUTFILE="/data/wangj/MC2015/Dntuple/PbPb/ntD_PbPb_Dstar_D0kpi/ntD_EvtBase_20160104_Dfinder_20151229_PbPb_Pythia8D0kpi_Dstar_pthatweight.root";

#Dstar 5p
#sed '1iconst int nBins=5; float pthatBin[nBins]={5,10,15,30,50}; float crosssec[nBins+1]={9.481e+07,6.207e+06,1.252e+06,6.522e+04,6.072e+03,0.}; int genSignal[2]={11,12};' weighPthat.C > weighPthat_tmp.C
#INPUTFILE="/data/wangj/MC2015/Dntuple/PbPb/ntD_PbPb_Dstar_D0kpipipi/ntD_EvtBase_20160104_Dfinder_20151229_PbPb_Pythia8D0kpipipi_Dstar_noweight.root";
#OUTPUTFILE="/data/wangj/MC2015/Dntuple/PbPb/ntD_PbPb_Dstar_D0kpipipi/ntD_EvtBase_20160104_Dfinder_20151229_PbPb_Pythia8D0kpipipi_Dstar_pthatweight.root";

###

cp "$INPUTFILE" "$OUTPUTFILE"
g++ weighPthat_tmp.C $(root-config --cflags --libs) -g -o weighPthat_tmp.exe 
./weighPthat_tmp.exe "$INPUTFILE" "$OUTPUTFILE"
rm weighPthat_tmp.exe

rm weighPthat_tmp.C