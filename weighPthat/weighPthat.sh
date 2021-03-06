#!/bin/bash

###

###pp
#Dzero
sed '1iconst int nBins=6; float pthatBin[nBins]={0,5,10,15,30,50}; float crosssec[nBins+1]={6.885e+09,1.581e+08,9.830e+06,1.916e+06,9.793e+04,9.066e+03,0.}; int genSignal[2]={1,2};' weighPthat.C > weighPthat_tmp.C
INPUTFILE="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160229_Dfinder_20160215_pp_Pythia8_prompt_D0_dPt0tkPt0p5_noweight.root"
OUTPUTFILE="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160229_Dfinder_20160215_pp_Pythia8_prompt_D0_dPt0tkPt0p5_pthatweight.root"

#Dzero nonprompt
#sed '1iconst int nBins=6; float pthatBin[nBins]={0,5,10,15,30,50}; float crosssec[nBins+1]={1.895e+08,1.485e+07,1.424e+06,2.948e+05,1.520e+04,1.369e+03,0.}; int genSignal[2]={1,2};' weighPthat.C > weighPthat_tmp.C
#INPUTFILE="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi_nonprompt/ntD_EvtBase_20160229_Dfinder_20160215_pp_Pythia8_nonprompt_D0_dPt0tkPt0p5_noweight.root"
#OUTPUTFILE="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi_nonprompt/ntD_EvtBase_20160229_Dfinder_20160215_pp_Pythia8_nonprompt_D0_dPt0tkPt0p5_pthatweight.root"

#Dstar 3p
#sed '1iconst int nBins=5; float pthatBin[nBins]={5,10,15,30,50}; float crosssec[nBins+1]={9.440e+07,6.280e+06,1.239e+06,6.518e+04,6.115e+03,0.}; int genSignal[2]={9,10};' weighPthat.C > weighPthat_tmp.C
#INPUTFILE="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160229_Dfinder_20160215_pp_Pythia8D0kpi_Dstar_dPt0tkPt0p5_noweight.root"
#OUTPUTFILE="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160229_Dfinder_20160215_pp_Pythia8D0kpi_Dstar_dPt0tkPt0p5_pthatweight.root"

#Dstar 5p
#sed '1iconst int nBins=5; float pthatBin[nBins]={5,10,15,30,50}; float crosssec[nBins+1]={9.533e+07,6.288e+06,1.243e+06,6.528e+04,6.193e+03,0.}; int genSignal[2]={11,12};' weighPthat.C > weighPthat_tmp.C
#INPUTFILE="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpipipi/ntD_EvtBase_20160229_Dfinder_20160215_pp_Pythia8D0kpipipi_Dstar_dPt0tkPt0p5_noweight.root"
#OUTPUTFILE="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpipipi/ntD_EvtBase_20160229_Dfinder_20160215_pp_Pythia8D0kpipipi_Dstar_dPt0tkPt0p5_pthatweight.root"


###pbpb
#Dzero
#sed '1iconst int nBins=6; float pthatBin[nBins]={0,5,10,15,30,50}; float crosssec[nBins+1]={6.885e+09,1.581e+08,9.830e+06,1.916e+06,9.793e+04,9.066e+03,0.}; int genSignal[2]={1,2};' weighPthat.C > weighPthat_tmp.C
#INPUTFILE="/data/wangj/MC2015/Dntuple/PbPb/ntD_PbPb_Dzero_kpi_prompt/ntD_EvtBase_20160229_Dfinder_20160215_PbPb_Pythia8_prompt_D0_dPt1tkPt1_noweight.root"
#OUTPUTFILE="/data/wangj/MC2015/Dntuple/PbPb/ntD_PbPb_Dzero_kpi_prompt/ntD_EvtBase_20160229_Dfinder_20160215_PbPb_Pythia8_prompt_D0_dPt1tkPt1_pthatweight.root"

#Dzero nonprompt
#sed '1iconst int nBins=6; float pthatBin[nBins]={0,5,10,15,30,50}; float crosssec[nBins+1]={1.895e+08,1.485e+07,1.424e+06,2.948e+05,1.520e+04,1.369e+03,0.}; int genSignal[2]={1,2};' weighPthat.C > weighPthat_tmp.C
#INPUTFILE="/data/wangj/MC2015/Dntuple/PbPb/ntD_PbPb_Dzero_kpi_nonprompt/ntD_EvtBase_20160229_Dfinder_20160215_PbPb_Pythia8_nonprompt_D0_dPt1tkPt1_noweight.root"
#OUTPUTFILE="/data/wangj/MC2015/Dntuple/PbPb/ntD_PbPb_Dzero_kpi_nonprompt/ntD_EvtBase_20160229_Dfinder_20160215_PbPb_Pythia8_nonprompt_D0_dPt1tkPt1_pthatweight.root"

#Dstar 3p
#sed '1iconst int nBins=5; float pthatBin[nBins]={5,10,15,30,50}; float crosssec[nBins+1]={9.440e+07,6.280e+06,1.239e+06,6.518e+04,6.115e+03,0.}; int genSignal[2]={9,10};' weighPthat.C > weighPthat_tmp.C
#INPUTFILE="/data/wangj/MC2015/Dntuple/PbPb/ntD_PbPb_Dstar_D0kpi/ntD_EvtBase_20160229_Dfinder_20160215_PbPb_Pythia8D0kpi_Dstar_dPt0tkPt2p5_noweight.root";
#OUTPUTFILE="/data/wangj/MC2015/Dntuple/PbPb/ntD_PbPb_Dstar_D0kpi/ntD_EvtBase_20160229_Dfinder_20160215_PbPb_Pythia8D0kpi_Dstar_dPt0tkPt2p5_pthatweight.root";

#Dstar 5p
#sed '1iconst int nBins=5; float pthatBin[nBins]={5,10,15,30,50}; float crosssec[nBins+1]={9.533e+07,6.288e+06,1.243e+06,6.528e+04,6.193e+03,0.}; int genSignal[2]={11,12};' weighPthat.C > weighPthat_tmp.C
#INPUTFILE="/data/wangj/MC2015/Dntuple/PbPb/ntD_PbPb_Dstar_D0kpipipi/ntD_EvtBase_20160229_Dfinder_20160215_PbPb_Pythia8D0kpipipi_Dstar_dPt0tkPt2p5_noweight.root";
#OUTPUTFILE="/data/wangj/MC2015/Dntuple/PbPb/ntD_PbPb_Dstar_D0kpipipi/ntD_EvtBase_20160229_Dfinder_20160215_PbPb_Pythia8D0kpipipi_Dstar_dPt0tkPt2p5_pthatweight.root";

###

cp "$INPUTFILE" "$OUTPUTFILE"
g++ weighPthat_tmp.C $(root-config --cflags --libs) -g -o weighPthat_tmp.exe 
./weighPthat_tmp.exe "$INPUTFILE" "$OUTPUTFILE"
rm weighPthat_tmp.exe

rm weighPthat_tmp.C