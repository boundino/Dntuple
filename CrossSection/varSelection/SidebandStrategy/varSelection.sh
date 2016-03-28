#!/bin/bash

DOSAVEHISTPP_ALPHA=0
DOSAVEHISTPbPb_ALPHA=0
DOSAVEHISTPPMB_ALPHA=0
DOSAVEHISTPbPbMB_ALPHA=0

DOSAVEHISTPP_DECAYLENGTH=0
DOSAVEHISTPbPb_DECAYLENGTH=0
DOSAVEHISTPPMB_DECAYLENGTH=0
DOSAVEHISTPbPbMB_DECAYLENGTH=0

DOSAVEHISTPP_CHI2=0
DOSAVEHISTPbPb_CHI2=0
DOSAVEHISTPPMB_CHI2=0
DOSAVEHISTPbPbMB_CHI2=0

#
DOFITPP_ALPHA=1
DOFITPbPb_ALPHA=1
DOFITPPMB_ALPHA=1
DOFITPbPbMB_ALPHA=1

DOFITPP_DECAYLENGTH=1
DOFITPbPb_DECAYLENGTH=1
DOFITPPMB_DECAYLENGTH=1
DOFITPbPbMB_DECAYLENGTH=1

DOFITPP_CHI2=1
DOFITPbPb_CHI2=1
DOFITPPMB_CHI2=1
DOFITPbPbMB_CHI2=1

#
DORATIO_ALPHA=1
DORATIO_DECAYLENGTH=1
DORATIO_CHI2=1

###

LABEL_ALPHA="Alpha"
LABEL_DECAYLENGTH="Decaylength"
LABEL_CHI2="Chi2"
VAR_ALPHA="Dalpha"
VAR_DECAYLENGTH="(DsvpvDistance/DsvpvDisErr)"
VAR_CHI2="Dchi2cl"
TEX_ALPHA="#alpha"
TEX_DECAYLENGTH="Decay length sig"
TEX_CHI2="Vtx prob"

VARBINS=5
VARMIN_ALPHA=0.04
VARMAX_ALPHA=0.2
VARMIN_DECAYLENGTH=3.5
VARMAX_DECAYLENGTH=5.5
VARMIN_CHI2=0.05
VARMAX_CHI2=0.45
VARSIGN_ALPHA=0
VARSIGN_DECAYLENGTH=1
VARSIGN_CHI2=1

###

INPUTDATAPP="/data/dmeson2015/DataDntuple/nt_20160112_DfinderData_pp_20160111_dPt0tkPt1_D0Dstar3p5p_DCSJSON_v2_skimmed.root"
INPUTMCPP="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_prompt_D0_dPt0tkPt0p5_pthatweight.root"
INPUTMCPNPPP="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_promptNnonprompt_D0_dPt0tkPt0p5_pthatweight.root"
ISMCPP=0
WEIGHTPP="pthatweight"
#WEIGHTPP="(pow(10,-0.168499*Dgenpt+3.872855+Dgenpt*Dgenpt*0.000556)+pow(10,-0.068599*Dgenpt+2.512265+Dgenpt*Dgenpt*0.000331))"
FILTERCUTPP="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>8.5&&Dtrk2Pt>8.5&&(DlxyBS/DlxyBSErr)>2.5&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&Dtrk1Algo>3&&Dtrk1Algo<8&&Dtrk2Algo>3&&Dtrk2Algo<8&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk2PixelHit+Dtrk2StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)"
#FILTERCUTPP="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(DlxyBS/DlxyBSErr)>1.5&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&Dtrk1Algo>3&&Dtrk1Algo<8&&Dtrk2Algo>3&&Dtrk2Algo<8&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk2PixelHit+Dtrk2StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)"
MATCHEDCUTPP="Dgen==23333"
ADDCUTPP_ALPHA="(DsvpvDistance/DsvpvDisErr)>3.5&&Dchi2cl>0.05"
ADDCUTPP_DECAYLENGTH="Dalpha<0.12&&Dchi2cl>0.05"
ADDCUTPP_CHI2="Dalpha<0.12&&(DsvpvDistance/DsvpvDisErr)>3.5"
TRGPP="((HLT_DmesonPPTrackingGlobal_Dpt15_v1&&Dpt>20&&Dpt<40)||(HLT_DmesonPPTrackingGlobal_Dpt30_v1&&Dpt>40&&Dpt<60)||(HLT_DmesonPPTrackingGlobal_Dpt50_v1&&Dpt>60))"
LABELPP="PP"
PTTHRESHOLDPP=20

INPUTMCPbPb="/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_PbPb_Pythia8_prompt_D0_dPt1tkPt1_pthatweight.root"
INPUTDATAPbPb="/data/dmeson2015/DataDntuple/nt_skimmed_DfinderData_PbPb_20160126_dPt0tkPt2p5_D0Dstar3p5p_FINALJSON_v6_partialstats_v2_skimmed.root"
INPUTMCPNPPbPb="/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi/ntD_EvtBase_20160303_Dfinder_20160302_PbPb_Pythia8_promptNnonprompt_D0_dPt1tkPt1_pthatweight.root"
ISMCPbPb=0
WEIGHTPbPb="pthatweight"
FILTERCUTPbPb="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>8.5&&Dtrk2Pt>8.5&&(DlxyBS/DlxyBSErr)>2.5&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk2PixelHit+Dtrk2StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)"
MATCHEDCUTPbPb="Dgen==23333"
ADDCUTPbPb_ALPHA="(DsvpvDistance/DsvpvDisErr)>3.5&&Dchi2cl>0.05"
ADDCUTPbPb_DECAYLENGTH="Dalpha<0.12&&Dchi2cl>0.05"
ADDCUTPbPb_CHI2="Dalpha<0.12&&(DsvpvDistance/DsvpvDisErr)>3.5"
TRGPbPb="((HLT_HIDmesonHITrackingGlobal_Dpt20_v1&&Dpt>20&&Dpt<45)||(HLT_HIDmesonHITrackingGlobal_Dpt40_v1&&Dpt>45&&Dpt<70)||(HLT_HIDmesonHITrackingGlobal_Dpt60_v1&&Dpt>70))"
LABELPbPb="PbPb"
PTTHRESHOLDPbPb=20

#

INPUTDATAPPMB="/data/dmeson2015/DataDntuple/skim_ncand_D0Dntuple_crab_pp_ALLMinimumBias_AOD_D0_tkpt0p5_Ds_01212016_skimmed.root"
INPUTMCPPMB="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_prompt_D0_dPt0tkPt0p5_pthatweight.root"
INPUTMCPNPPPMB="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_promptNnonprompt_D0_dPt0tkPt0p5_pthatweight.root"
ISMCPPMB=0
WEIGHTPPMB="pthatweight"
#WEIGHTPPMB="(pow(10,-0.168499*Dgenpt+3.872855+Dgenpt*Dgenpt*0.000556)+pow(10,-0.068599*Dgenpt+2.512265+Dgenpt*Dgenpt*0.000331))"
FILTERCUTPPMB="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&(DlxyBS/DlxyBSErr)>1.5"
MATCHEDCUTPPMB="Dgen==23333"
ADDCUTPPMB_ALPHA="(DsvpvDistance/DsvpvDisErr)>5.&&Dchi2cl>0.2"
ADDCUTPPMB_DECAYLENGTH="Dalpha<0.08&&Dchi2cl>0.2"
ADDCUTPPMB_CHI2="Dalpha<0.08&&(DsvpvDistance/DsvpvDisErr)>5."
TRGPPMB="(HLT_L1MinimumBiasHF1OR_part1_v1||HLT_L1MinimumBiasHF1OR_part2_v1||HLT_L1MinimumBiasHF1OR_part3_v1||HLT_L1MinimumBiasHF1OR_part4_v1||HLT_L1MinimumBiasHF1OR_part5_v1||HLT_L1MinimumBiasHF1OR_part6_v1||HLT_L1MinimumBiasHF1OR_part7_v1||HLT_L1MinimumBiasHF1OR_part8_v1||HLT_L1MinimumBiasHF1OR_part9_v1||HLT_L1MinimumBiasHF1OR_part10_v1||HLT_L1MinimumBiasHF1OR_part11_v1||HLT_L1MinimumBiasHF1OR_part12_v1||HLT_L1MinimumBiasHF1OR_part13_v1||HLT_L1MinimumBiasHF1OR_part14_v1||HLT_L1MinimumBiasHF1OR_part15_v1||HLT_L1MinimumBiasHF1OR_part16_v1||HLT_L1MinimumBiasHF1OR_part17_v1||HLT_L1MinimumBiasHF1OR_part18_v1||HLT_L1MinimumBiasHF1OR_part19_v1)"
LABELPPMB="PPMB"
PTTHRESHOLDPPMB=3

INPUTDATAPbPbMB="/data/dmeson2015/DataDntuple/Dntuple_crab_PbPb_HIMinimumBias3_ForestAOD_D0_tkpt0p7eta1p5_goldenjson_01292016_skim.root"
INPUTMCPbPbMB="/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_PbPb_Pythia8_prompt_D0_dPt1tkPt1_pthatweight.root"
INPUTMCPNPPbPbMB="/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi/ntD_EvtBase_20160303_Dfinder_20160302_PbPb_Pythia8_promptNnonprompt_D0_dPt1tkPt1_pthatweight.root"
ISMCPbPbMB=0
WEIGHTPbPbMB="pthatweight"
FILTERCUTPbPbMB="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&(DlxyBS/DlxyBSErr)>1.5"
MATCHEDCUTPbPbMB="Dgen==23333"
ADDCUTPbPbMB_ALPHA="(DsvpvDistance/DsvpvDisErr)>5.&&Dchi2cl>0.2"
ADDCUTPbPbMB_DECAYLENGTH="Dalpha<0.08&&Dchi2cl>0.2"
ADDCUTPbPbMB_CHI2="Dalpha<0.08&&(DsvpvDistance/DsvpvDisErr)>5."
TRGPbPbMB="(HLT_HIL1MinimumBiasHF2AND_part1_v1||HLT_HIL1MinimumBiasHF2AND_part2_v1||HLT_HIL1MinimumBiasHF2AND_part3_v1)"
LABELPbPbMB="PbPbMB"
PTTHRESHOLDPbPbMB=3

###

if [ $DOSAVEHISTPP_ALPHA -eq 1 ]; then
g++ saveMasshisto.C $(root-config --cflags --libs) -g -o saveMasshisto.exe 
./saveMasshisto.exe "$INPUTDATAPP" "$INPUTMCPP" "$TRGPP" "${FILTERCUTPP}&&${ADDCUTPP_ALPHA}" "$ISMCPP" "1" "$LABELPP" "$LABEL_ALPHA" "$VAR_ALPHA" "$VARBINS" "$VARMIN_ALPHA" "$VARMAX_ALPHA" "$VARSIGN_ALPHA" "$PTTHRESHOLDPP"
./saveMasshisto.exe "$INPUTMCPP" "$INPUTMCPP" "1" "${FILTERCUTPP}&&${MATCHEDCUTPP}&&${ADDCUTPP_ALPHA}" "1" "$WEIGHTPP" "$LABELPP" "$LABEL_ALPHA" "$VAR_ALPHA" "$VARBINS" "$VARMIN_ALPHA" "$VARMAX_ALPHA" "$VARSIGN_ALPHA" "$PTTHRESHOLDPP"
rm saveMasshisto.exe
fi

if [ $DOSAVEHISTPbPb_ALPHA -eq 1 ]; then
g++ saveMasshisto.C $(root-config --cflags --libs) -g -o saveMasshisto.exe 
./saveMasshisto.exe "$INPUTDATAPbPb" "$INPUTMCPbPb" "$TRGPbPb" "${FILTERCUTPbPb}&&${ADDCUTPbPb_ALPHA}" "$ISMCPbPb" "1" "$LABELPbPb" "$LABEL_ALPHA" "$VAR_ALPHA" "$VARBINS" "$VARMIN_ALPHA" "$VARMAX_ALPHA" "$VARSIGN_ALPHA" "$PTTHRESHOLDPbPb"
./saveMasshisto.exe "$INPUTMCPbPb" "$INPUTMCPbPb" "1" "${FILTERCUTPbPb}&&${MATCHEDCUTPbPb}&&${ADDCUTPbPb_ALPHA}" "1" "$WEIGHTPbPb" "$LABELPbPb" "$LABEL_ALPHA" "$VAR_ALPHA" "$VARBINS" "$VARMIN_ALPHA" "$VARMAX_ALPHA" "$VARSIGN_ALPHA" "$PTTHRESHOLDPbPb"
rm saveMasshisto.exe
fi

if [ $DOSAVEHISTPPMB_ALPHA -eq 1 ]; then
g++ saveMasshisto.C $(root-config --cflags --libs) -g -o saveMasshisto.exe 
./saveMasshisto.exe "$INPUTDATAPPMB" "$INPUTMCPPMB" "$TRGPPMB" "${FILTERCUTPPMB}&&${ADDCUTPPMB_ALPHA}" "$ISMCPPMB" "1" "$LABELPPMB" "$LABEL_ALPHA" "$VAR_ALPHA" "$VARBINS" "$VARMIN_ALPHA" "$VARMAX_ALPHA" "$VARSIGN_ALPHA" "$PTTHRESHOLDPPMB"
./saveMasshisto.exe "$INPUTMCPPMB" "$INPUTMCPPMB" "1" "${FILTERCUTPPMB}&&${MATCHEDCUTPPMB}&&${ADDCUTPPMB_ALPHA}" "1" "$WEIGHTPPMB" "$LABELPPMB" "$LABEL_ALPHA" "$VAR_ALPHA" "$VARBINS" "$VARMIN_ALPHA" "$VARMAX_ALPHA" "$VARSIGN_ALPHA" "$PTTHRESHOLDPPMB"
rm saveMasshisto.exe
fi

if [ $DOSAVEHISTPbPbMB_ALPHA -eq 1 ]; then
g++ saveMasshisto.C $(root-config --cflags --libs) -g -o saveMasshisto.exe 
./saveMasshisto.exe "$INPUTDATAPbPbMB" "$INPUTMCPbPbMB" "$TRGPbPbMB" "${FILTERCUTPbPbMB}&&${ADDCUTPbPbMB_ALPHA}" "$ISMCPbPbMB" "1" "$LABELPbPbMB" "$LABEL_ALPHA" "$VAR_ALPHA" "$VARBINS" "$VARMIN_ALPHA" "$VARMAX_ALPHA" "$VARSIGN_ALPHA" "$PTTHRESHOLDPbPbMB"
./saveMasshisto.exe "$INPUTMCPbPbMB" "$INPUTMCPbPbMB" "1" "${FILTERCUTPbPbMB}&&${MATCHEDCUTPbPbMB}&&${ADDCUTPbPbMB_ALPHA}" "1" "$WEIGHTPbPbMB" "$LABELPbPbMB" "$LABEL_ALPHA" "$VAR_ALPHA" "$VARBINS" "$VARMIN_ALPHA" "$VARMAX_ALPHA" "$VARSIGN_ALPHA" "$PTTHRESHOLDPbPbMB"
rm saveMasshisto.exe
fi

#

if [ $DOSAVEHISTPP_DECAYLENGTH -eq 1 ]; then
g++ saveMasshisto.C $(root-config --cflags --libs) -g -o saveMasshisto.exe 
./saveMasshisto.exe "$INPUTDATAPP" "$INPUTMCPP" "$TRGPP" "${FILTERCUTPP}&&${ADDCUTPP_DECAYLENGTH}" "$ISMCPP" "1" "$LABELPP" "$LABEL_DECAYLENGTH" "$VAR_DECAYLENGTH" "$VARBINS" "$VARMIN_DECAYLENGTH" "$VARMAX_DECAYLENGTH" "$VARSIGN_DECAYLENGTH" "$PTTHRESHOLDPP"
./saveMasshisto.exe "$INPUTMCPP" "$INPUTMCPP" "1" "${FILTERCUTPP}&&${MATCHEDCUTPP}&&${ADDCUTPP_DECAYLENGTH}" "1" "$WEIGHTPP" "$LABELPP" "$LABEL_DECAYLENGTH" "$VAR_DECAYLENGTH" "$VARBINS" "$VARMIN_DECAYLENGTH" "$VARMAX_DECAYLENGTH" "$VARSIGN_DECAYLENGTH" "$PTTHRESHOLDPP"
rm saveMasshisto.exe
fi

if [ $DOSAVEHISTPbPb_DECAYLENGTH -eq 1 ]; then
g++ saveMasshisto.C $(root-config --cflags --libs) -g -o saveMasshisto.exe 
./saveMasshisto.exe "$INPUTDATAPbPb" "$INPUTMCPbPb" "$TRGPbPb" "${FILTERCUTPbPb}&&${ADDCUTPbPb_DECAYLENGTH}" "$ISMCPbPb" "1" "$LABELPbPb" "$LABEL_DECAYLENGTH" "$VAR_DECAYLENGTH" "$VARBINS" "$VARMIN_DECAYLENGTH" "$VARMAX_DECAYLENGTH" "$VARSIGN_DECAYLENGTH" "$PTTHRESHOLDPbPb"
./saveMasshisto.exe "$INPUTMCPbPb" "$INPUTMCPbPb" "1" "${FILTERCUTPbPb}&&${MATCHEDCUTPbPb}&&${ADDCUTPbPb_DECAYLENGTH}" "1" "$WEIGHTPbPb" "$LABELPbPb" "$LABEL_DECAYLENGTH" "$VAR_DECAYLENGTH" "$VARBINS" "$VARMIN_DECAYLENGTH" "$VARMAX_DECAYLENGTH" "$VARSIGN_DECAYLENGTH" "$PTTHRESHOLDPbPb"
rm saveMasshisto.exe
fi

if [ $DOSAVEHISTPPMB_DECAYLENGTH -eq 1 ]; then
g++ saveMasshisto.C $(root-config --cflags --libs) -g -o saveMasshisto.exe 
./saveMasshisto.exe "$INPUTDATAPPMB" "$INPUTMCPPMB" "$TRGPPMB" "${FILTERCUTPPMB}&&${ADDCUTPPMB_DECAYLENGTH}" "$ISMCPPMB" "1" "$LABELPPMB" "$LABEL_DECAYLENGTH" "$VAR_DECAYLENGTH" "$VARBINS" "$VARMIN_DECAYLENGTH" "$VARMAX_DECAYLENGTH" "$VARSIGN_DECAYLENGTH" "$PTTHRESHOLDPPMB"
./saveMasshisto.exe "$INPUTMCPPMB" "$INPUTMCPPMB" "1" "${FILTERCUTPPMB}&&${MATCHEDCUTPPMB}&&${ADDCUTPPMB_DECAYLENGTH}" "1" "$WEIGHTPPMB" "$LABELPPMB" "$LABEL_DECAYLENGTH" "$VAR_DECAYLENGTH" "$VARBINS" "$VARMIN_DECAYLENGTH" "$VARMAX_DECAYLENGTH" "$VARSIGN_DECAYLENGTH" "$PTTHRESHOLDPPMB"
rm saveMasshisto.exe
fi

if [ $DOSAVEHISTPbPbMB_DECAYLENGTH -eq 1 ]; then
g++ saveMasshisto.C $(root-config --cflags --libs) -g -o saveMasshisto.exe 
./saveMasshisto.exe "$INPUTDATAPbPbMB" "$INPUTMCPbPbMB" "$TRGPbPbMB" "${FILTERCUTPbPbMB}&&${ADDCUTPbPbMB_DECAYLENGTH}" "$ISMCPbPbMB" "1" "$LABELPbPbMB" "$LABEL_DECAYLENGTH" "$VAR_DECAYLENGTH" "$VARBINS" "$VARMIN_DECAYLENGTH" "$VARMAX_DECAYLENGTH" "$VARSIGN_DECAYLENGTH" "$PTTHRESHOLDPbPbMB"
./saveMasshisto.exe "$INPUTMCPbPbMB" "$INPUTMCPbPbMB" "1" "${FILTERCUTPbPbMB}&&${MATCHEDCUTPbPbMB}&&${ADDCUTPbPbMB_DECAYLENGTH}" "1" "$WEIGHTPbPbMB" "$LABELPbPbMB" "$LABEL_DECAYLENGTH" "$VAR_DECAYLENGTH" "$VARBINS" "$VARMIN_DECAYLENGTH" "$VARMAX_DECAYLENGTH" "$VARSIGN_DECAYLENGTH" "$PTTHRESHOLDPbPbMB"
rm saveMasshisto.exe
fi

#

if [ $DOSAVEHISTPP_CHI2 -eq 1 ]; then
g++ saveMasshisto.C $(root-config --cflags --libs) -g -o saveMasshisto.exe 
./saveMasshisto.exe "$INPUTDATAPP" "$INPUTMCPP" "$TRGPP" "${FILTERCUTPP}&&${ADDCUTPP_CHI2}" "$ISMCPP" "1" "$LABELPP" "$LABEL_CHI2" "$VAR_CHI2" "$VARBINS" "$VARMIN_CHI2" "$VARMAX_CHI2" "$VARSIGN_CHI2" "$PTTHRESHOLDPP"
./saveMasshisto.exe "$INPUTMCPP" "$INPUTMCPP" "1" "${FILTERCUTPP}&&${MATCHEDCUTPP}&&${ADDCUTPP_CHI2}" "1" "$WEIGHTPP" "$LABELPP" "$LABEL_CHI2" "$VAR_CHI2" "$VARBINS" "$VARMIN_CHI2" "$VARMAX_CHI2" "$VARSIGN_CHI2" "$PTTHRESHOLDPP"
rm saveMasshisto.exe
fi

if [ $DOSAVEHISTPbPb_CHI2 -eq 1 ]; then
g++ saveMasshisto.C $(root-config --cflags --libs) -g -o saveMasshisto.exe 
./saveMasshisto.exe "$INPUTDATAPbPb" "$INPUTMCPbPb" "$TRGPbPb" "${FILTERCUTPbPb}&&${ADDCUTPbPb_CHI2}" "$ISMCPbPb" "1" "$LABELPbPb" "$LABEL_CHI2" "$VAR_CHI2" "$VARBINS" "$VARMIN_CHI2" "$VARMAX_CHI2" "$VARSIGN_CHI2" "$PTTHRESHOLDPbPb"
./saveMasshisto.exe "$INPUTMCPbPb" "$INPUTMCPbPb" "1" "${FILTERCUTPbPb}&&${MATCHEDCUTPbPb}&&${ADDCUTPbPb_CHI2}" "1" "$WEIGHTPbPb" "$LABELPbPb" "$LABEL_CHI2" "$VAR_CHI2" "$VARBINS" "$VARMIN_CHI2" "$VARMAX_CHI2" "$VARSIGN_CHI2" "$PTTHRESHOLDPbPb"
rm saveMasshisto.exe
fi

if [ $DOSAVEHISTPPMB_CHI2 -eq 1 ]; then
g++ saveMasshisto.C $(root-config --cflags --libs) -g -o saveMasshisto.exe 
./saveMasshisto.exe "$INPUTDATAPPMB" "$INPUTMCPPMB" "$TRGPPMB" "${FILTERCUTPPMB}&&${ADDCUTPPMB_CHI2}" "$ISMCPPMB" "1" "$LABELPPMB" "$LABEL_CHI2" "$VAR_CHI2" "$VARBINS" "$VARMIN_CHI2" "$VARMAX_CHI2" "$VARSIGN_CHI2" "$PTTHRESHOLDPPMB"
./saveMasshisto.exe "$INPUTMCPPMB" "$INPUTMCPPMB" "1" "${FILTERCUTPPMB}&&${MATCHEDCUTPPMB}&&${ADDCUTPPMB_CHI2}" "1" "$WEIGHTPPMB" "$LABELPPMB" "$LABEL_CHI2" "$VAR_CHI2" "$VARBINS" "$VARMIN_CHI2" "$VARMAX_CHI2" "$VARSIGN_CHI2" "$PTTHRESHOLDPPMB"
rm saveMasshisto.exe
fi

if [ $DOSAVEHISTPbPbMB_CHI2 -eq 1 ]; then
g++ saveMasshisto.C $(root-config --cflags --libs) -g -o saveMasshisto.exe 
./saveMasshisto.exe "$INPUTDATAPbPbMB" "$INPUTMCPbPbMB" "$TRGPbPbMB" "${FILTERCUTPbPbMB}&&${ADDCUTPbPbMB_CHI2}" "$ISMCPbPbMB" "1" "$LABELPbPbMB" "$LABEL_CHI2" "$VAR_CHI2" "$VARBINS" "$VARMIN_CHI2" "$VARMAX_CHI2" "$VARSIGN_CHI2" "$PTTHRESHOLDPbPbMB"
./saveMasshisto.exe "$INPUTMCPbPbMB" "$INPUTMCPbPbMB" "1" "${FILTERCUTPbPbMB}&&${MATCHEDCUTPbPbMB}&&${ADDCUTPbPbMB_CHI2}" "1" "$WEIGHTPbPbMB" "$LABELPbPbMB" "$LABEL_CHI2" "$VAR_CHI2" "$VARBINS" "$VARMIN_CHI2" "$VARMAX_CHI2" "$VARSIGN_CHI2" "$PTTHRESHOLDPbPbMB"
rm saveMasshisto.exe
fi


##

if [ $DOFITPP_ALPHA -eq 1 ]; then
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe "$LABELPP" "$LABEL_ALPHA" "$VARBINS" "$VARMIN_ALPHA" "$VARMAX_ALPHA" "$TEX_ALPHA" "$VARSIGN_ALPHA"
rm fitD.exe
fi

if [ $DOFITPbPb_ALPHA -eq 1 ]; then
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe "$LABELPbPb" "$LABEL_ALPHA" "$VARBINS" "$VARMIN_ALPHA" "$VARMAX_ALPHA" "$TEX_ALPHA" "$VARSIGN_ALPHA"
rm fitD.exe
fi

if [ $DOFITPPMB_ALPHA -eq 1 ]; then
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe "$LABELPPMB" "$LABEL_ALPHA" "$VARBINS" "$VARMIN_ALPHA" "$VARMAX_ALPHA" "$TEX_ALPHA" "$VARSIGN_ALPHA"
rm fitD.exe
fi

if [ $DOFITPbPbMB_ALPHA -eq 1 ]; then
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe "$LABELPbPbMB" "$LABEL_ALPHA" "$VARBINS" "$VARMIN_ALPHA" "$VARMAX_ALPHA" "$TEX_ALPHA" "$VARSIGN_ALPHA"
rm fitD.exe
fi

if [ $DOFITPP_DECAYLENGTH -eq 1 ]; then
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe "$LABELPP" "$LABEL_DECAYLENGTH" "$VARBINS" "$VARMIN_DECAYLENGTH" "$VARMAX_DECAYLENGTH" "$TEX_DECAYLENGTH" "$VARSIGN_DECAYLENGTH"
rm fitD.exe
fi

if [ $DOFITPbPb_DECAYLENGTH -eq 1 ]; then
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe "$LABELPbPb" "$LABEL_DECAYLENGTH" "$VARBINS" "$VARMIN_DECAYLENGTH" "$VARMAX_DECAYLENGTH" "$TEX_DECAYLENGTH" "$VARSIGN_DECAYLENGTH"
rm fitD.exe
fi

if [ $DOFITPPMB_DECAYLENGTH -eq 1 ]; then
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe "$LABELPPMB" "$LABEL_DECAYLENGTH" "$VARBINS" "$VARMIN_DECAYLENGTH" "$VARMAX_DECAYLENGTH" "$TEX_DECAYLENGTH" "$VARSIGN_DECAYLENGTH"
rm fitD.exe
fi

if [ $DOFITPbPbMB_DECAYLENGTH -eq 1 ]; then
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe "$LABELPbPbMB" "$LABEL_DECAYLENGTH" "$VARBINS" "$VARMIN_DECAYLENGTH" "$VARMAX_DECAYLENGTH" "$TEX_DECAYLENGTH" "$VARSIGN_DECAYLENGTH"
rm fitD.exe
fi

if [ $DOFITPP_CHI2 -eq 1 ]; then
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe "$LABELPP" "$LABEL_CHI2" "$VARBINS" "$VARMIN_CHI2" "$VARMAX_CHI2" "$TEX_CHI2" "$VARSIGN_CHI2"
rm fitD.exe
fi

if [ $DOFITPbPb_CHI2 -eq 1 ]; then
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe "$LABELPbPb" "$LABEL_CHI2" "$VARBINS" "$VARMIN_CHI2" "$VARMAX_CHI2" "$TEX_CHI2" "$VARSIGN_CHI2"
rm fitD.exe
fi

if [ $DOFITPPMB_CHI2 -eq 1 ]; then
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe "$LABELPPMB" "$LABEL_CHI2" "$VARBINS" "$VARMIN_CHI2" "$VARMAX_CHI2" "$TEX_CHI2" "$VARSIGN_CHI2"
rm fitD.exe
fi

if [ $DOFITPbPbMB_CHI2 -eq 1 ]; then
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe "$LABELPbPbMB" "$LABEL_CHI2" "$VARBINS" "$VARMIN_CHI2" "$VARMAX_CHI2" "$TEX_CHI2" "$VARSIGN_CHI2"
rm fitD.exe
fi

##

if [ $DORATIO_ALPHA -eq 1 ]; then
g++ plotRatioDoubleratio.C $(root-config --cflags --libs) -g -o plotRatioDoubleratio.exe 
./plotRatioDoubleratio.exe "$LABEL_ALPHA" "$TEX_ALPHA"
rm plotRatioDoubleratio.exe
fi

if [ $DORATIO_DECAYLENGTH -eq 1 ]; then
g++ plotRatioDoubleratio.C $(root-config --cflags --libs) -g -o plotRatioDoubleratio.exe 
./plotRatioDoubleratio.exe "$LABEL_DECAYLENGTH" "$TEX_DECAYLENGTH"
rm plotRatioDoubleratio.exe
fi

if [ $DORATIO_CHI2 -eq 1 ]; then
g++ plotRatioDoubleratio.C $(root-config --cflags --libs) -g -o plotRatioDoubleratio.exe 
./plotRatioDoubleratio.exe "$LABEL_CHI2" "$TEX_CHI2"
rm plotRatioDoubleratio.exe
fi
