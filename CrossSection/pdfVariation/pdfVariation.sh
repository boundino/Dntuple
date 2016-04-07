#!/bin/bash

#
DOSAVEHISTPP=0
DOSAVEHISTPbPb=0
DOSAVEHISTPPMB=0
DOSAVEHISTPbPbMB=0

#
DOFITDEFAULTNEWPP=0
DOFITDEFAULTNEWPbPb=0
DOFITDEFAULTNEWPPMB=0
DOFITDEFAULTNEWPbPbMB=0

DOFITINCREASEWIDPP=0
DOFITINCREASEWIDPbPb=0
DOFITINCREASEWIDPPMB=0
DOFITINCREASEWIDPbPbMB=0

DOFITDECREASEWIDPP=0
DOFITDECREASEWIDPbPb=0
DOFITDECREASEWIDPPMB=0
DOFITDECREASEWIDPbPbMB=0

DOFITPOLY2PP=0
DOFITPOLY2PbPb=0
DOFITPOLY2PPMB=0
DOFITPOLY2PbPbMB=0

DOFITEXPO2PP=1
DOFITEXPO2PbPb=1
DOFITEXPO2PPMB=1
DOFITEXPO2PbPbMB=1

#
DOFITPOLY1PP=0
DOFITPOLY1PbPb=0
DOFITPOLY1PPMB=0
DOFITPOLY1PbPbMB=0

DOFITEXPOPP=0
DOFITEXPOPbPb=0
DOFITEXPOPPMB=0
DOFITEXPOPbPbMB=0

DOFITDEFAULTPP=0
DOFITDEFAULTPbPb=0
DOFITDEFAULTPPMB=0
DOFITDEFAULTPbPbMB=0

DOFITFLOATWIDPP=0
DOFITFLOATWIDPbPb=0
DOFITFLOATWIDPPMB=0
DOFITFLOATWIDPbPbMB=0


##

INPUTMCPP="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_prompt_D0_dPt0tkPt0p5_pthatweight.root"
INPUTDATAPP="/data/dmeson2015/DataDntuple/ntD_EvtBase_20160330_HeavyFlavor_DfinderData_pp_20160329_dPt0tkPt1_D0Dstar3p5p_goldenjson_skim_myskim.root"
ISMCPP=0
ISDOWEIGHTPP=0
SELGENPP="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))"
CUTPP="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05&&Dalpha<0.12&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&Dtrk1OriginalAlgo>3&&Dtrk1OriginalAlgo<=8&&Dtrk2OriginalAlgo>3&&Dtrk2OriginalAlgo<=8&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk2PixelHit+Dtrk2StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)"
TRGPP="((HLT_DmesonPPTrackingGlobal_Dpt15_v1&&Dpt>20&&Dpt<40)||(HLT_DmesonPPTrackingGlobal_Dpt30_v1&&Dpt>40&&Dpt<60)||(HLT_DmesonPPTrackingGlobal_Dpt50_v1&&Dpt>60))"
LABELPP="PP"

INPUTMCPbPb="/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_PbPb_Pythia8_prompt_D0_dPt1tkPt1_pthatweight.root"
INPUTDATAPbPb="/data/dmeson2015/DataDntuple/nt_skimmed_DfinderData_PbPb_20160126_dPt0tkPt2p5_D0Dstar3p5p_FINALJSON_v6_partialstats_v2_skimmed.root"
ISMCPbPb=0
ISDOWEIGHTPbPb=0
SELGENPbPb="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))"
CUTPbPb="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>8.5&&Dtrk2Pt>8.5&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk2PixelHit+Dtrk2StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)&&((DlxyBS/DlxyBSErr)>1.5&&Dalpha<0.12&&((Dpt>2&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>5.86&&Dchi2cl>0.224)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>5.46&&Dchi2cl>0.196)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.86&&Dchi2cl>0.170)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.54&&Dchi2cl>0.125)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.42&&Dchi2cl>0.091)||(Dpt>10&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>4.06&&Dchi2cl>0.069)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.71&&Dchi2cl>0.056)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))"
TRGPbPb="((HLT_HIDmesonHITrackingGlobal_Dpt20_v1&&Dpt>20&&Dpt<40)||(HLT_HIDmesonHITrackingGlobal_Dpt40_v1&&Dpt>40&&Dpt<60)||(HLT_HIDmesonHITrackingGlobal_Dpt60_v1&&Dpt>60))"
LABELPbPb="PbPb"


cp config/parametersHighpt.h parameters.h

if [ $DOSAVEHISTPP -eq 1 ]; then
g++ saveMasshisto.C $(root-config --cflags --libs) -g -o saveMasshisto.exe 
./saveMasshisto.exe "$INPUTDATAPP" "$INPUTMCPP" "$TRGPP" "$CUTPP" "$ISMCPP" "$ISDOWEIGHTPP" "$LABELPP"
rm saveMasshisto.exe
fi

if [ $DOSAVEHISTPbPb -eq 1 ]; then
g++ saveMasshisto.C $(root-config --cflags --libs) -g -o saveMasshisto.exe 
./saveMasshisto.exe "$INPUTDATAPbPb" "$INPUTMCPbPb" "$TRGPbPb" "$CUTPbPb" "$ISMCPbPb" "$ISDOWEIGHTPbPb" "$LABELPbPb"
rm saveMasshisto.exe
fi

if [ $DOFITDEFAULTPP -eq 1 ]; then
g++ fitDdefault.C $(root-config --cflags --libs) -g -o fitDdefault.exe 
./fitDdefault.exe "$LABELPP"
rm fitDdefault.exe
fi

if [ $DOFITDEFAULTPbPb -eq 1 ]; then
g++ fitDdefault.C $(root-config --cflags --libs) -g -o fitDdefault.exe 
./fitDdefault.exe "$LABELPbPb"
rm fitDdefault.exe
fi

if [ $DOFITDEFAULTNEWPP -eq 1 ]; then
g++ fitDdefaultnew.C $(root-config --cflags --libs) -g -o fitDdefaultnew.exe 
./fitDdefaultnew.exe "$LABELPP"
rm fitDdefaultnew.exe
fi

if [ $DOFITDEFAULTNEWPbPb -eq 1 ]; then
g++ fitDdefaultnew.C $(root-config --cflags --libs) -g -o fitDdefaultnew.exe 
./fitDdefaultnew.exe "$LABELPbPb"
rm fitDdefaultnew.exe
fi

if [ $DOFITFLOATWIDPP -eq 1 ]; then
g++ fitDfloatwid.C $(root-config --cflags --libs) -g -o fitDfloatwid.exe 
./fitDfloatwid.exe "$LABELPP"
rm fitDfloatwid.exe
fi

if [ $DOFITFLOATWIDPbPb -eq 1 ]; then
g++ fitDfloatwid.C $(root-config --cflags --libs) -g -o fitDfloatwid.exe 
./fitDfloatwid.exe "$LABELPbPb"
rm fitDfloatwid.exe
fi

if [ $DOFITINCREASEWIDPP -eq 1 ]; then
g++ fitDincreasewid.C $(root-config --cflags --libs) -g -o fitDincreasewid.exe 
./fitDincreasewid.exe "$LABELPP"
rm fitDincreasewid.exe
fi

if [ $DOFITINCREASEWIDPbPb -eq 1 ]; then
g++ fitDincreasewid.C $(root-config --cflags --libs) -g -o fitDincreasewid.exe 
./fitDincreasewid.exe "$LABELPbPb"
rm fitDincreasewid.exe
fi

if [ $DOFITDECREASEWIDPP -eq 1 ]; then
g++ fitDdecreasewid.C $(root-config --cflags --libs) -g -o fitDdecreasewid.exe 
./fitDdecreasewid.exe "$LABELPP"
rm fitDdecreasewid.exe
fi

if [ $DOFITDECREASEWIDPbPb -eq 1 ]; then
g++ fitDdecreasewid.C $(root-config --cflags --libs) -g -o fitDdecreasewid.exe 
./fitDdecreasewid.exe "$LABELPbPb"
rm fitDdecreasewid.exe
fi

if [ $DOFITPOLY2PP -eq 1 ]; then
g++ fitDpoly2.C $(root-config --cflags --libs) -g -o fitDpoly2.exe 
./fitDpoly2.exe "$LABELPP"
rm fitDpoly2.exe
fi

if [ $DOFITPOLY2PbPb -eq 1 ]; then
g++ fitDpoly2.C $(root-config --cflags --libs) -g -o fitDpoly2.exe 
./fitDpoly2.exe "$LABELPbPb"
rm fitDpoly2.exe
fi

if [ $DOFITPOLY1PP -eq 1 ]; then
g++ fitDpoly1.C $(root-config --cflags --libs) -g -o fitDpoly1.exe 
./fitDpoly1.exe "$LABELPP"
rm fitDpoly1.exe
fi

if [ $DOFITPOLY1PbPb -eq 1 ]; then
g++ fitDpoly1.C $(root-config --cflags --libs) -g -o fitDpoly1.exe 
./fitDpoly1.exe "$LABELPbPb"
rm fitDpoly1.exe
fi

if [ $DOFITEXPOPP -eq 1 ]; then
g++ fitDexpo.C $(root-config --cflags --libs) -g -o fitDexpo.exe 
./fitDexpo.exe "$LABELPP"
rm fitDexpo.exe
fi

if [ $DOFITEXPOPbPb -eq 1 ]; then
g++ fitDexpo.C $(root-config --cflags --libs) -g -o fitDexpo.exe 
./fitDexpo.exe "$LABELPbPb"
rm fitDexpo.exe
fi

if [ $DOFITEXPO2PP -eq 1 ]; then
g++ fitDexpo2.C $(root-config --cflags --libs) -g -o fitDexpo2.exe 
./fitDexpo2.exe "$LABELPP"
rm fitDexpo2.exe
fi

if [ $DOFITEXPO2PbPb -eq 1 ]; then
g++ fitDexpo2.C $(root-config --cflags --libs) -g -o fitDexpo2.exe 
./fitDexpo2.exe "$LABELPbPb"
rm fitDexpo2.exe
fi

#
rm parameters.h

##
INPUTDATAPPMB="/data/dmeson2015/DataDntuple/skim_ncand_D0Dntuple_crab_pp_ALLMinimumBias_AOD_D0_tkpt0p5_Ds_01212016_skimmedPt1.root"
INPUTMCPPMB="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_prompt_D0_dPt0tkPt0p5_pthatweight.root"
ISMCPPMB=0
ISDOWEIGHTPPMB=0
SELGENPPMB="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))"
CUTPPMB="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05&&Dalpha<0.12"
TRGPPMB="(HLT_L1MinimumBiasHF1OR_part1_v1||HLT_L1MinimumBiasHF1OR_part2_v1||HLT_L1MinimumBiasHF1OR_part3_v1||HLT_L1MinimumBiasHF1OR_part4_v1||HLT_L1MinimumBiasHF1OR_part5_v1||HLT_L1MinimumBiasHF1OR_part6_v1||HLT_L1MinimumBiasHF1OR_part7_v1||HLT_L1MinimumBiasHF1OR_part8_v1||HLT_L1MinimumBiasHF1OR_part9_v1||HLT_L1MinimumBiasHF1OR_part10_v1||HLT_L1MinimumBiasHF1OR_part11_v1||HLT_L1MinimumBiasHF1OR_part12_v1||HLT_L1MinimumBiasHF1OR_part13_v1||HLT_L1MinimumBiasHF1OR_part14_v1||HLT_L1MinimumBiasHF1OR_part15_v1||HLT_L1MinimumBiasHF1OR_part16_v1||HLT_L1MinimumBiasHF1OR_part17_v1||HLT_L1MinimumBiasHF1OR_part18_v1||HLT_L1MinimumBiasHF1OR_part19_v1)"
LABELPPMB="PPMB"

INPUTDATAPbPbMB="/data/jisun/PbPb2015/HF2and_tk1p0_skim_Dntuple_crab_PbPb_HIMinimumBias1to7_ForestAOD_highpuritytk_D0_tkpt0p7eta1p5_goldenjson_02222016.root"
INPUTMCPbPbMB="/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_PbPb_Pythia8_prompt_D0_dPt1tkPt1_pthatweight.root"
ISMCPbPbMB=0
ISDOWEIGHTPbPbMB=0
SELGENPbPbMB="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))"
CUTPbPbMB="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&((DlxyBS/DlxyBSErr)>1.5&&Dalpha<0.12&&((Dpt>1&&Dpt<2&&(DsvpvDistance/DsvpvDisErr)>6.0&&Dchi2cl>0.25)||(Dpt>2&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>5.86&&Dchi2cl>0.224)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>5.46&&Dchi2cl>0.196)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.86&&Dchi2cl>0.170)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.54&&Dchi2cl>0.125)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.42&&Dchi2cl>0.091)||(Dpt>10&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>4.06&&Dchi2cl>0.069)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.71&&Dchi2cl>0.056)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))"
TRGPbPbMB="(HLT_HIL1MinimumBiasHF2AND_part1_v1||HLT_HIL1MinimumBiasHF2AND_part2_v1||HLT_HIL1MinimumBiasHF2AND_part3_v1)"
LABELPbPbMB="PbPbMB"

cp config/parametersLowpt.h parameters.h

if [ $DOSAVEHISTPPMB -eq 1 ]; then
g++ saveMasshisto.C $(root-config --cflags --libs) -g -o saveMasshisto.exe 
./saveMasshisto.exe "$INPUTDATAPPMB" "$INPUTMCPPMB" "$TRGPPMB" "$CUTPPMB" "$ISMCPPMB" "$ISDOWEIGHTPPMB" "$LABELPPMB"
rm saveMasshisto.exe
fi

if [ $DOSAVEHISTPbPbMB -eq 1 ]; then
g++ saveMasshisto.C $(root-config --cflags --libs) -g -o saveMasshisto.exe 
./saveMasshisto.exe "$INPUTDATAPbPbMB" "$INPUTMCPbPbMB" "$TRGPbPbMB" "$CUTPbPbMB" "$ISMCPbPbMB" "$ISDOWEIGHTPbPbMB" "$LABELPbPbMB"
rm saveMasshisto.exe
fi

if [ $DOFITDEFAULTPPMB -eq 1 ]; then
g++ fitDdefault.C $(root-config --cflags --libs) -g -o fitDdefault.exe 
./fitDdefault.exe "$LABELPPMB"
rm fitDdefault.exe
fi

if [ $DOFITDEFAULTPbPbMB -eq 1 ]; then
g++ fitDdefault.C $(root-config --cflags --libs) -g -o fitDdefault.exe 
./fitDdefault.exe "$LABELPbPbMB"
rm fitDdefault.exe
fi

if [ $DOFITDEFAULTNEWPPMB -eq 1 ]; then
g++ fitDdefaultnew.C $(root-config --cflags --libs) -g -o fitDdefaultnew.exe 
./fitDdefaultnew.exe "$LABELPPMB"
rm fitDdefaultnew.exe
fi

if [ $DOFITDEFAULTNEWPbPbMB -eq 1 ]; then
g++ fitDdefaultnew.C $(root-config --cflags --libs) -g -o fitDdefaultnew.exe 
./fitDdefaultnew.exe "$LABELPbPbMB"
rm fitDdefaultnew.exe
fi

if [ $DOFITFLOATWIDPPMB -eq 1 ]; then
g++ fitDfloatwid.C $(root-config --cflags --libs) -g -o fitDfloatwid.exe 
./fitDfloatwid.exe "$LABELPPMB"
rm fitDfloatwid.exe
fi

if [ $DOFITFLOATWIDPbPbMB -eq 1 ]; then
g++ fitDfloatwid.C $(root-config --cflags --libs) -g -o fitDfloatwid.exe 
./fitDfloatwid.exe "$LABELPbPbMB"
rm fitDfloatwid.exe
fi

if [ $DOFITINCREASEWIDPPMB -eq 1 ]; then
g++ fitDincreasewid.C $(root-config --cflags --libs) -g -o fitDincreasewid.exe 
./fitDincreasewid.exe "$LABELPPMB"
rm fitDincreasewid.exe
fi

if [ $DOFITINCREASEWIDPbPbMB -eq 1 ]; then
g++ fitDincreasewid.C $(root-config --cflags --libs) -g -o fitDincreasewid.exe 
./fitDincreasewid.exe "$LABELPbPbMB"
rm fitDincreasewid.exe
fi

if [ $DOFITDECREASEWIDPPMB -eq 1 ]; then
g++ fitDdecreasewid.C $(root-config --cflags --libs) -g -o fitDdecreasewid.exe 
./fitDdecreasewid.exe "$LABELPPMB"
rm fitDdecreasewid.exe
fi

if [ $DOFITDECREASEWIDPbPbMB -eq 1 ]; then
g++ fitDdecreasewid.C $(root-config --cflags --libs) -g -o fitDdecreasewid.exe 
./fitDdecreasewid.exe "$LABELPbPbMB"
rm fitDdecreasewid.exe
fi

if [ $DOFITPOLY2PPMB -eq 1 ]; then
g++ fitDpoly2.C $(root-config --cflags --libs) -g -o fitDpoly2.exe 
./fitDpoly2.exe "$LABELPPMB"
rm fitDpoly2.exe
fi

if [ $DOFITPOLY2PbPbMB -eq 1 ]; then
g++ fitDpoly2.C $(root-config --cflags --libs) -g -o fitDpoly2.exe 
./fitDpoly2.exe "$LABELPbPbMB"
rm fitDpoly2.exe
fi

if [ $DOFITPOLY1PPMB -eq 1 ]; then
g++ fitDpoly1.C $(root-config --cflags --libs) -g -o fitDpoly1.exe 
./fitDpoly1.exe "$LABELPPMB"
rm fitDpoly1.exe
fi

if [ $DOFITPOLY1PbPbMB -eq 1 ]; then
g++ fitDpoly1.C $(root-config --cflags --libs) -g -o fitDpoly1.exe 
./fitDpoly1.exe "$LABELPbPbMB"
rm fitDpoly1.exe
fi

if [ $DOFITEXPOPPMB -eq 1 ]; then
g++ fitDexpo.C $(root-config --cflags --libs) -g -o fitDexpo.exe 
./fitDexpo.exe "$LABELPPMB"
rm fitDexpo.exe
fi

if [ $DOFITEXPOPbPbMB -eq 1 ]; then
g++ fitDexpo.C $(root-config --cflags --libs) -g -o fitDexpo.exe 
./fitDexpo.exe "$LABELPbPbMB"
rm fitDexpo.exe
fi

if [ $DOFITEXPO2PPMB -eq 1 ]; then
g++ fitDexpo2.C $(root-config --cflags --libs) -g -o fitDexpo2.exe 
./fitDexpo2.exe "$LABELPPMB"
rm fitDexpo2.exe
fi

if [ $DOFITEXPO2PbPbMB -eq 1 ]; then
g++ fitDexpo2.C $(root-config --cflags --libs) -g -o fitDexpo2.exe 
./fitDexpo2.exe "$LABELPbPbMB"
rm fitDexpo2.exe
fi

#
rm parameters.h

##