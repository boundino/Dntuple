#!/bin/bash
#source clean.sh
CENTPbPbMIN=0
CENTPbPbMAX=100
#Central point of the analysis

DOANALYSISPP_FONLL=0
DOANALYSISPP_TRGCOMBINATION=0
DOANALYSISPP_FIT=0
DOANALYSISPP_CROSS=1
DOANALYSISPP_MCSTUDY=1

DOANALYSISPbPb_FONLL=0
DOANALYSISPbPb_TRGCOMBINATION=0
DOANALYSISPbPb_FIT=0
DOANALYSISPbPb_CROSS=1
DOANALYSISPbPb_MCSTUDY=1

DOANALYSISPPMB_FONLL=0
DOANALYSISPPMB_FIT=0
DOANALYSISPPMB_CROSS=1
DOANALYSISPPMB_MCSTUDY=1

DOANALYSISPbPbMB_FONLL=0
DOANALYSISPbPbMB_FIT=0
DOANALYSISPbPbMB_CROSS=1
DOANALYSISPbPbMB_MCSTUDY=1

DONORMPP=0
DONORMPPMB=0
DONORMPbPb=0
DONORMPbPbMB=0

DORAA=1
DORAAMB=1

DOCombineCrossSectionPP=1
DOCombineCrossSectionPbPb=1
DOCombineRAA=1

#systematic section

DOFITSPPMCClosure=0
DOFITSPbPbMCClosure=0
DOFITSPPMBMCClosure=0
DOFITSPbPbMBMCClosure=0

DOsystematicPtshape=0

DOsystematicPthatstudyPP=0
DOsystematicPthatstudyPbPb=0

UNITY=1
NULL=0

MINIMUMFIT=2
MAXIMUMFIT=100

FONLLDATINPUT="pp_d0meson_5TeV_y1"
FONLLDATINPUTBtoD="pp_Btod0meson_5TeV_y1"
FONLLDATINPUTB="pp_Bmeson_5TeV_y1"

## PP MONTE CARLO

NTUPLAPYTHIA="/data/HeavyFlavourRun2/BtoDPythia/treefile_ptall_11january2016.root"
INPUTMCPP="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_prompt_D0_dPt0tkPt0p5_pthatweight.root"  
INPUTMCPPMB="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_prompt_D0pt0p0_Pthat10_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20160229_dPt0tkPt0p5_D0Dstar.root"  
INPUTMCNPPP="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_nonprompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_nonprompt_D0_dPt0tkPt0p5_pthatweight.root"
INPUTMCPPPthat10="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_prompt_D0pt0p0_Pthat10_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20160229_dPt0tkPt0p5_D0Dstar.root"
INPUTMCPPPthat30="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_prompt_D0pt0p0_Pthat30_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20160229_dPt0tkPt0p5_D0Dstar.root"
INPUTMCPPPthat50="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_prompt_D0pt0p0_Pthat50_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20160229_dPt0tkPt0p5_D0Dstar.root"
INPUTMCPPPthat70="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_prompt_D0pt0p0_Pthat70_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20160229_dPt0tkPt0p5_D0Dstar.root"

## PP DATA 

INPUTDATAPPSKIMMED="/data/dmeson2015/DataDntuple/ntD_EvtBase_20160330_HeavyFlavor_DfinderData_pp_20160329_dPt0tkPt1_D0Dstar3p5p_goldenjson_skim_myskim.root"
INPUTDATAPPUNSKIMMED="/data/wangj/Data2015/Dntuple/pp/ntD_EvtBase_20160330_HeavyFlavor_DfinderData_pp_20160329_dPt0tkPt1_D0Dstar3p5p_goldenjson.root"
INPUTDATAPPMBUNSKIMMED="/data/jisun/ppMB2015fullstats/skim_ncand_D0Dntuple_crab_pp_ALLMinimumBias_AOD_D0_tkpt0p5_Ds_01212016.root"
INPUTDATAPPMBSKIMMED="/data/dmeson2015/DataDntuple/skim_ncand_D0Dntuple_crab_pp_ALLMinimumBias_AOD_D0_tkpt0p5_Ds_01212016_skimmedPt1.root"

## PbPb MONTE CARLO

INPUTMCPbPb="/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_PbPb_Pythia8_prompt_D0_dPt1tkPt1_pthatweight.root"
INPUTMCPbPbMB="/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_PbPb_Pythia8_prompt_D0pt0p0_Pthat10_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20160229_dPt1tkPt1_D0Ds.root"
INPUTMCNPPbPb="/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi_nonprompt/ntD_EvtBase_20160303_Dfinder_20160302_PbPb_Pythia8_nonprompt_D0_dPt1tkPt1_pthatweight.root"
INPUTMCPbPbPthat10="/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_PbPb_Pythia8_prompt_D0pt0p0_Pthat10_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20160229_dPt1tkPt1_D0Ds.root"
INPUTMCPbPbPthat30="/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_PbPb_Pythia8_prompt_D0pt0p0_Pthat30_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20160229_dPt1tkPt1_D0Ds.root"
INPUTMCPbPbPthat50="/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_PbPb_Pythia8_prompt_D0pt0p0_Pthat50_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20160229_dPt1tkPt1_D0Ds.root"
INPUTMCPbPbPthat70="/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_PbPb_Pythia8_prompt_D0pt0p0_Pthat70_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20160229_dPt1tkPt1_D0Ds.root"

## PbPb DATA 

INPUTDATAPbPbSKIMMED="/data/dmeson2015/DataDntuple/nt_skimmed_DfinderData_PbPb_20160126_dPt0tkPt2p5_D0Dstar3p5p_FINALJSON_v6_partialstats_v2_skimmed.root"
#INPUTDATAPbPbSKIMMED="/data/dmeson2015/DataDntuple/ntD_EvtBase_20160331_DfinderData_PbPb_20160126_dPt0tkPt2p5_D0_FINALJSON_v6_skimmed.root"
INPUTDATAPbPbUNSKIMMED="/data/dmeson2015/DataDntuple/nt_skimmed_DfinderData_PbPb_20160126_dPt0tkPt2p5_D0Dstar3p5p_FINALJSON_v6_partialstats_v2.root"
INPUTDATAPbPbMBUNSKIMMED="/data/jisun/PbPb2015/HF2and_skim_MB1to7_highpuritytk_D0_tkpt0p7eta1p5_goldenjson_02222016.root"
INPUTDATAPbPbMBSKIMMED="/data/jisun/PbPb2015/HF2and_tk1p0_skim_Dntuple_crab_PbPb_HIMinimumBias1to7_ForestAOD_highpuritytk_D0_tkpt0p7eta1p5_goldenjson_02222016.root"

## CHARGED RAA
CHARGEDHADRON="/afs/cern.ch/work/g/ginnocen/public/PlotRAA.root" 

## ANALYSIS PP TRIGGERED

FONLLOUTPUTFILE="ROOTfiles/output_pp_d0meson_5TeV_y1.root"
FONLLOUTPUTFILEBtoD="ROOTfiles/output_pp_Btod0meson_5TeV_y1.root"
FONLLOUTPUTFILEInclusiveD="ROOTfiles/output_inclusiveDd0meson_5TeV_y1.root"
FONLLOUTPUTFILEB="ROOTfiles/output_pp_Bmeson_5TeV_y1.root"
OUTPUTFILEPP="ROOTfiles/hPtSpectrumDzeroPP.root"
OUTPUTFILEPlotPP="ROOTfiles/CrossSectionFONLLPP.root"
OUTPUTFILEMCSTUDYPP="ROOTfiles/MCstudiesPP.root"
OUTPUTFILEMCSTUDYNPPP="ROOTfiles/MCstudiesNPPP.root"
OUTPUTPrescalePP="ROOTfiles/prescalePP.root"

LUMIPP=25.8
ISMCPP=0
ISDOWEIGHTPP=0
SELGENPP="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))"
SELGENPPACCPP="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))&&abs(Gtk1eta)<2.0&&abs(Gtk2eta)<2.0&&Gtk1pt>2.0&&Gtk2pt>2.0"
RECOONLYPP="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&Dtrk1OriginalAlgo>3&&Dtrk1OriginalAlgo<=8&&Dtrk2OriginalAlgo>3&&Dtrk2OriginalAlgo<=8&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk2PixelHit+Dtrk2StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)"
CUTPP="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05&&Dalpha<0.12&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&Dtrk1OriginalAlgo>3&&Dtrk1OriginalAlgo<=8&&Dtrk2OriginalAlgo>3&&Dtrk2OriginalAlgo<=8&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk2PixelHit+Dtrk2StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)"
TRGPP="((HLT_DmesonPPTrackingGlobal_Dpt8_v1&&Dpt>10&&Dpt<20)||(HLT_DmesonPPTrackingGlobal_Dpt15_v1&&Dpt>20&&Dpt<40)||(HLT_DmesonPPTrackingGlobal_Dpt30_v1&&Dpt>40&&Dpt<60)||(HLT_DmesonPPTrackingGlobal_Dpt50_v1&&Dpt>60))"
LABELPP="PP"
LABELNPPP="NPPP"
USEPRESCALEPP=1
CUTFORTRIGGERPRESCALEPP=0

ISHADDUPL=1                                  

cp config/parametersHighpt.h parameters.h

if [ $DONORMPP -eq 1 ]; then      
cp config/parametersHighptPPNorm.h parameters.h
OUTPUTFILEPlotPP="ROOTfiles/CrossSectionFONLLPPNorm.root"
OUTPUTPrescalePP="ROOTfiles/prescalePPNorm.root"
LUMIPP=1
fi

if [ $DOANALYSISPP_FONLL -eq 1 ]; then      
g++ Dzerodsigmadpt.cc $(root-config --cflags --libs) -g -o Dzerodsigmadpt.exe 
./Dzerodsigmadpt.exe "$FONLLDATINPUT"  "$FONLLOUTPUTFILE" "$LABELPP"
./Dzerodsigmadpt.exe "$FONLLDATINPUTBtoD"  "$FONLLOUTPUTFILEBtoD" "$LABELPP"
rm Dzerodsigmadpt.exe

g++ BplusAlldsigmadpt.cc $(root-config --cflags --libs) -g -o BplusAlldsigmadpt.exe 
./BplusAlldsigmadpt.exe "$FONLLDATINPUTB"  "$FONLLOUTPUTFILEB" "$LABELPP"
rm BplusAlldsigmadpt.exe

g++ RatioFeedDown.cc $(root-config --cflags --libs) -g -o RatioFeedDown.exe 
./RatioFeedDown.exe "$FONLLOUTPUTFILE"  "$FONLLOUTPUTFILEBtoD" "$FONLLOUTPUTFILEInclusiveD" "$LABELPP"
rm RatioFeedDown.exe

g++ plotFeedDown.C $(root-config --cflags --libs) -g -o plotFeedDown.exe 
./plotFeedDown.exe "$FONLLOUTPUTFILE"  "$FONLLOUTPUTFILEB" "$NTUPLAPYTHIA" 1 0 100 
rm plotFeedDown.exe
fi 

if [ $DOANALYSISPP_TRGCOMBINATION -eq 1 ]; then      
g++ triggercombination.cc $(root-config --cflags --libs) -g -o triggercombination.exe 
./triggercombination.exe "$LABELPP"  "$INPUTDATAPPUNSKIMMED" "$INPUTDATAPPMBUNSKIMMED" "$CUTFORTRIGGERPRESCALEPP" "$OUTPUTPrescalePP"
rm triggercombination.exe
fi 

if [ $DOANALYSISPP_FIT -eq 1 ]; then      
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe "$INPUTDATAPPSKIMMED"  "$INPUTMCPP"  "$TRGPP" "$CUTPP"   "$SELGENPP"   "$ISMCPP"   1   "$ISDOWEIGHTPP"   "$LABELPP"  "$OUTPUTFILEPP"
rm fitD.exe
fi 

if [ $DOANALYSISPP_CROSS -eq 1 ]; then      
g++ CrossSectionRatio.C $(root-config --cflags --libs) -g -o CrossSectionRatio.exe 
./CrossSectionRatio.exe "$FONLLOUTPUTFILE"  "$OUTPUTFILEPP" "$OUTPUTPrescalePP" "$USEPRESCALEPP" "$OUTPUTFILEPlotPP" "$LABELPP" "$LUMIPP" 
rm CrossSectionRatio.exe
fi

if [ $DOANALYSISPP_MCSTUDY -eq 1 ]; then      
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 
./MCefficiency.exe "$INPUTMCPP"  "$SELGENPP" "$SELGENPPACCPP"  "$RECOONLYPP" "$CUTPP"  "$LABELPP" "$OUTPUTFILEMCSTUDYPP" "$ISDOWEIGHTPP" "$MINIMUMFIT" "$MAXIMUMFIT"
./MCefficiency.exe "$INPUTMCNPPP"  "$SELGENPP" "$SELGENPPACCPP"  "$RECOONLYPP" "$CUTPP"  "$LABELNPPP" "$OUTPUTFILEMCSTUDYNPPP" "$ISDOWEIGHTPP" "$MINIMUMFIT" "$MAXIMUMFIT"
rm MCefficiency.exe

g++ plotPnNP.C $(root-config --cflags --libs) -g -o plotPnNP.exe 
./plotPnNP.exe "$LABELPP" "$OUTPUTFILEMCSTUDYPP" "$OUTPUTFILEMCSTUDYNPPP"
rm plotPnNP.exe
fi

## ANALYSIS PbPb TRIGGERED

cp config/parametersHighpt.h parameters.h

OUTPUTPrescalePbPb="ROOTfiles/prescalePbPb.root"
OUTPUTFILEMCSTUDYPbPb="ROOTfiles/MCstudiesPbPb.root"
OUTPUTFILEMCSTUDYNPPbPb="ROOTfiles/MCstudiesNPPbPb.root"
OUTPUTFILEPbPb="ROOTfiles/hPtSpectrumDzeroPbPb.root"
OUTPUTFILEPlotPbPb="ROOTfiles/CrossSectionFONLLPbPb.root"
OUTPUTFILERAA="ROOTfiles/outputRAA.root"

LUMIPbPb=18.4115 
ISMCPbPb=0
ISDOWEIGHTPbPb=0
SELGENPbPb="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))"
SELGENPPACCPbPb="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))&&abs(Gtk1eta)<2.0&&abs(Gtk2eta)<2.0&&Gtk1pt>2.0&&Gtk2pt>2.0"
RECOONLYPbPb="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>8.5&&Dtrk2Pt>8.5&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk2PixelHit+Dtrk2StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)&&Dtrk1Algo>3&&Dtrk1Algo<8&&Dtrk2Algo>3&&Dtrk2Algo<8"
CUTPbPb="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>8.5&&Dtrk2Pt>8.5&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk2PixelHit+Dtrk2StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)&&((DlxyBS/DlxyBSErr)>1.5&&Dalpha<0.12&&((Dpt>2&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>5.86&&Dchi2cl>0.224)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>5.46&&Dchi2cl>0.196)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.86&&Dchi2cl>0.170)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.54&&Dchi2cl>0.125)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.42&&Dchi2cl>0.091)||(Dpt>10&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>4.06&&Dchi2cl>0.069)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.71&&Dchi2cl>0.056)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))"
TRGPbPb="((HLT_HIDmesonHITrackingGlobal_Dpt20_v1&&Dpt>20&&Dpt<40)||(HLT_HIDmesonHITrackingGlobal_Dpt40_v1&&Dpt>40&&Dpt<60)||(HLT_HIDmesonHITrackingGlobal_Dpt60_v1&&Dpt>60))"
LABELPbPb="PbPb"
LABELNPPbPb="NPPbPb"
USEPRESCALEPbPb=1
CUTFORTRIGGERPRESCALEPbPb=0

if [ $DONORMPbPb -eq 1 ]; then      
cp config/parametersHighptPbPbNorm.h parameters.h
OUTPUTFILEPlotPbPb="ROOTfiles/CrossSectionFONLLPbPbNorm.root"
OUTPUTPrescalePbPb="ROOTfiles/prescalePbPbNorm.root"
LUMIPbPb=1
fi

if [ $DOANALYSISPbPb_FONLL -eq 1 ]; then      
g++ Dzerodsigmadpt.cc $(root-config --cflags --libs) -g -o Dzerodsigmadpt.exe 
./Dzerodsigmadpt.exe "$FONLLDATINPUT"  "$FONLLOUTPUTFILE" "$LABELPP"
rm Dzerodsigmadpt.exe
fi

if [ $DOANALYSISPbPb_TRGCOMBINATION -eq 1 ]; then      
g++ triggercombination.cc $(root-config --cflags --libs) -g -o triggercombination.exe 
./triggercombination.exe "$LABELPbPb"  "$INPUTDATAPbPbUNSKIMMED" "$INPUTDATAPbPbMBUNSKIMMED" "$CUTFORTRIGGERPRESCALEPbPb" "$OUTPUTPrescalePbPb"
rm triggercombination.exe
fi

if [ $DOANALYSISPbPb_FIT -eq 1 ]; then      
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe "$INPUTDATAPbPbSKIMMED"  "$INPUTMCPbPb"  "$TRGPbPb" "$CUTPbPb"   "$SELGENPbPb"   "$ISMCPbPb"   1   "$ISDOWEIGHTPbPb"  "$LABELPbPb"  "$OUTPUTFILEPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm fitD.exe
fi

if [ $DOANALYSISPbPb_CROSS -eq 1 ]; then      
g++ CrossSectionRatio.C $(root-config --cflags --libs) -g -o CrossSectionRatio.exe 
./CrossSectionRatio.exe "$FONLLOUTPUTFILE"  "$OUTPUTFILEPbPb" "$OUTPUTPrescalePbPb" "$USEPRESCALEPbPb" "$OUTPUTFILEPlotPbPb" "$LABELPbPb" "$LUMIPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm CrossSectionRatio.exe
fi

if [ $DOANALYSISPbPb_MCSTUDY -eq 1 ]; then      
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 
./MCefficiency.exe "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPPACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "$ISDOWEIGHTPbPb" "$MINIMUMFIT" "$MAXIMUMFIT"
./MCefficiency.exe "$INPUTMCNPPbPb"  "$SELGENPbPb" "$SELGENPPACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb"  "$LABELNPPbPb" "$OUTPUTFILEMCSTUDYNPPbPb" "$ISDOWEIGHTPbPb" "$MINIMUMFIT" "$MAXIMUMFIT"
rm MCefficiency.exe

g++ plotPnNP.C $(root-config --cflags --libs) -g -o plotPnNP.exe 
./plotPnNP.exe "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "$OUTPUTFILEMCSTUDYNPPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm plotPnNP.exe
fi


if [ $DORAA -eq 1 ]; then      
g++ NuclearModificationFactor.C $(root-config --cflags --libs) -g -o NuclearModificationFactor.exe 
./NuclearModificationFactor.exe "$OUTPUTFILEPlotPP" "$OUTPUTFILEPlotPbPb"  "$LABELPbPb" "$OUTPUTFILERAA" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm NuclearModificationFactor.exe
fi


## ANALYSIS PP MB

FONLLOUTPUTFILEMB="ROOTfiles/output_pp_d0meson_5TeV_y1MB.root"
FONLLOUTPUTFILEBtoDMB="ROOTfiles/output_pp_Btod0meson_5TeV_y1MB.root"
FONLLOUTPUTFILEInclusiveDMB="ROOTfiles/output_inclusiveDd0meson_5TeV_y1MB.root"
FONLLOUTPUTFILEBMB="ROOTfiles/output_pp_Bmeson_5TeV_y1MB.root"
OUTPUTFILEPPMB="ROOTfiles/hPtSpectrumDzeroPPMB.root"
OUTPUTFILEPlotPPMB="ROOTfiles/CrossSectionFONLLPPMB.root"
OUTPUTFILEMCSTUDYPPMB="ROOTfiles/MCstudiesPPMB.root"
OUTPUTFILEMCSTUDYNPPPMB="ROOTfiles/MCstudiesNPPPMB.root"

LUMIPPMB=0.0378131
ISMCPPMB=0
ISDOWEIGHTPPMB=1
SELGENPPMB="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))"
SELGENACCPPMB="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))&&abs(Gtk1eta)<2.0&&abs(Gtk2eta)<2.0&&Gtk1pt>1.0&&Gtk2pt>1.0"
RECOONLYPPMB="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0"
CUTPPMB="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05&&Dalpha<0.12"
TRGPPMB="(HLT_L1MinimumBiasHF1OR_part1_v1||HLT_L1MinimumBiasHF1OR_part2_v1||HLT_L1MinimumBiasHF1OR_part3_v1||HLT_L1MinimumBiasHF1OR_part4_v1||HLT_L1MinimumBiasHF1OR_part5_v1||HLT_L1MinimumBiasHF1OR_part6_v1||HLT_L1MinimumBiasHF1OR_part7_v1||HLT_L1MinimumBiasHF1OR_part8_v1||HLT_L1MinimumBiasHF1OR_part9_v1||HLT_L1MinimumBiasHF1OR_part10_v1||HLT_L1MinimumBiasHF1OR_part11_v1||HLT_L1MinimumBiasHF1OR_part12_v1||HLT_L1MinimumBiasHF1OR_part13_v1||HLT_L1MinimumBiasHF1OR_part14_v1||HLT_L1MinimumBiasHF1OR_part15_v1||HLT_L1MinimumBiasHF1OR_part16_v1||HLT_L1MinimumBiasHF1OR_part17_v1||HLT_L1MinimumBiasHF1OR_part18_v1||HLT_L1MinimumBiasHF1OR_part19_v1)"
LABELPPMB="PPMB"
LABELNPPPMB="NPPPMB"
USEPRESCALEPPMB=0


cp config/parametersLowpt.h parameters.h


if [ $DONORMPPMB -eq 1 ]; then      
LUMIPPMB=1
cp config/parametersMBPPNorm.h parameters.h
OUTPUTFILEPlotPPMB="ROOTfiles/CrossSectionFONLLPPMBNorm.root"
fi 

if [ $DOANALYSISPPMB_FONLL -eq 1 ]; then
g++ Dzerodsigmadpt.cc $(root-config --cflags --libs) -g -o Dzerodsigmadpt.exe 
./Dzerodsigmadpt.exe "$FONLLDATINPUT"  "$FONLLOUTPUTFILEMB" "$LABELPPMB"
./Dzerodsigmadpt.exe "$FONLLDATINPUTBtoD"  "$FONLLOUTPUTFILEBtoDMB" "$LABELPPMB"
rm Dzerodsigmadpt.exe

g++ BplusAlldsigmadpt.cc $(root-config --cflags --libs) -g -o BplusAlldsigmadpt.exe 
./BplusAlldsigmadpt.exe "$FONLLDATINPUTB"  "$FONLLOUTPUTFILEBMB" "$LABELPPMB"
rm BplusAlldsigmadpt.exe

g++ RatioFeedDown.cc $(root-config --cflags --libs) -g -o RatioFeedDown.exe 
./RatioFeedDown.exe "$FONLLOUTPUTFILEMB"  "$FONLLOUTPUTFILEBtoDMB" "$FONLLOUTPUTFILEInclusiveDMB" "$LABELPPMB"
rm RatioFeedDown.exe

g++ plotFeedDown.C $(root-config --cflags --libs) -g -o plotFeedDown.exe 
./plotFeedDown.exe "$FONLLOUTPUTFILEMB"  "$FONLLOUTPUTFILEBMB" "$NTUPLAPYTHIA" 1 0 100 
rm plotFeedDown.exe
fi

if [ $DOANALYSISPPMB_FIT -eq 1 ]; then      
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe "$INPUTDATAPPMBSKIMMED"  "$INPUTMCPP"  "$TRGPPMB" "$CUTPPMB"   "$SELGENPPMB"   "$ISMCPPMB"   1   "$ISDOWEIGHTPPMB"   "$LABELPPMB"  "$OUTPUTFILEPPMB"
rm fitD.exe
fi

if [ $DOANALYSISPPMB_MCSTUDY -eq 1 ]; then      
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 
./MCefficiency.exe "$INPUTMCPP"  "$SELGENPPMB" "$SELGENACCPPMB"  "$RECOONLYPPMB" "$CUTPPMB"  "$LABELPPMB" "$OUTPUTFILEMCSTUDYPPMB" "$ISDOWEIGHTPPMB" "$MINIMUMFIT" "$MAXIMUMFIT"
./MCefficiency.exe "$INPUTMCNPPP"  "$SELGENPPMB" "$SELGENACCPPMB"  "$RECOONLYPPMB" "$CUTPPMB"  "$LABELNPPPMB" "$OUTPUTFILEMCSTUDYNPPPMB" "$ISDOWEIGHTPPMB" "$MINIMUMFIT" "$MAXIMUMFIT"
rm MCefficiency.exe

g++ plotPnNP.C $(root-config --cflags --libs) -g -o plotPnNP.exe 
./plotPnNP.exe "$LABELPPMB" "$OUTPUTFILEMCSTUDYPPMB" "$OUTPUTFILEMCSTUDYNPPPMB"
rm plotPnNP.exe
fi

if [ $DOANALYSISPPMB_CROSS -eq 1 ]; then      
g++ CrossSectionRatio.C $(root-config --cflags --libs) -g -o CrossSectionRatio.exe 
./CrossSectionRatio.exe "$FONLLOUTPUTFILEMB"  "$OUTPUTFILEPPMB" "$OUTPUTPrescalePP" "$USEPRESCALEPPMB" "$OUTPUTFILEPlotPPMB" "$LABELPPMB" "$LUMIPPMB"
rm CrossSectionRatio.exe
fi


## ANALYSIS PbPb MB

OUTPUTFILEPbPbMB="ROOTfiles/hPtSpectrumDzeroPbPbMB.root"
OUTPUTFILEPlotPbPbMB="ROOTfiles/CrossSectionFONLLPbPbMB.root"
OUTPUTFILEMCSTUDYPbPbMB="ROOTfiles/MCstudiesPbPbMB.root"
OUTPUTFILEMCSTUDYNPPbPbMB="ROOTfiles/MCstudiesNPPbPbMB.root"
OUTPUTFILERAAMB="ROOTfiles/outputRAAMB.root"

LUMIPbPbMB=0.831646 
ISMCPbPbMB=0
ISDOWEIGHTPbPbMB=0
SELGENPbPbMB="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))"
SELGENACCPbPbMB="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))&&abs(Gtk1eta)<1.5&&abs(Gtk2eta)<1.5&&Gtk1pt>1.0&&Gtk2pt>1.0"
RECOONLYPbPbMB="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5"
CUTPbPbMB="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&((DlxyBS/DlxyBSErr)>1.5&&Dalpha<0.12&&((Dpt>1&&Dpt<2&&(DsvpvDistance/DsvpvDisErr)>6.0&&Dchi2cl>0.25)||(Dpt>2&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>5.86&&Dchi2cl>0.224)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>5.46&&Dchi2cl>0.196)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.86&&Dchi2cl>0.170)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.54&&Dchi2cl>0.125)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.42&&Dchi2cl>0.091)||(Dpt>10&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>4.06&&Dchi2cl>0.069)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.71&&Dchi2cl>0.056)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))"
TRGPbPbMB="(HLT_HIL1MinimumBiasHF2AND_part1_v1||HLT_HIL1MinimumBiasHF2AND_part2_v1||HLT_HIL1MinimumBiasHF2AND_part3_v1)"
LABELPbPbMB="PbPbMB"
LABELNPPbPbMB="NPPbPbMB"
USEPRESCALEPbPbMB=0

if [ $DONORMPbPbMB -eq 1 ]; then      
LUMIPbPbMB=1
cp config/parametersMBPbPbNorm.h parameters.h
OUTPUTFILEPlotPbPbMB="ROOTfiles/CrossSectionFONLLPbPbMBNorm.root"
fi

if [ $DOANALYSISPbPbMB_FONLL -eq 1 ]; then      
g++ Dzerodsigmadpt.cc $(root-config --cflags --libs) -g -o Dzerodsigmadpt.exe 
./Dzerodsigmadpt.exe "$FONLLDATINPUT"  "$FONLLOUTPUTFILEMB" "$LABELPPMB"
rm Dzerodsigmadpt.exe
fi

if [ $DOANALYSISPbPbMB_FIT -eq 1 ]; then      
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe "$INPUTDATAPbPbMBSKIMMED"  "$INPUTMCPbPb"  "$TRGPbPbMB" "$CUTPbPbMB"   "$SELGENPbPbMB"   "$ISMCPbPbMB"   1   "$ISDOWEIGHTPbPbMB"   "$LABELPbPbMB"  "$OUTPUTFILEPbPbMB" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm fitD.exe
fi

if [ $DOANALYSISPbPbMB_CROSS -eq 1 ]; then      
g++ CrossSectionRatio.C $(root-config --cflags --libs) -g -o CrossSectionRatio.exe 
./CrossSectionRatio.exe "$FONLLOUTPUTFILEMB"  "$OUTPUTFILEPbPbMB" "$OUTPUTPrescalePbPb" "$USEPRESCALEPbPbMB" "$OUTPUTFILEPlotPbPbMB" "$LABELPbPbMB" "$LUMIPbPbMB" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm CrossSectionRatio.exe
fi

if [ $DOANALYSISPbPbMB_MCSTUDY -eq 1 ]; then      
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 
./MCefficiency.exe "$INPUTMCPbPb"  "$SELGENPbPbMB" "$SELGENACCPbPbMB"  "$RECOONLYPbPbMB" "$CUTPbPbMB"  "$LABELPbPbMB" "$OUTPUTFILEMCSTUDYPbPbMB" "$ISDOWEIGHTPbPbMB" "$MINIMUMFIT" "$MAXIMUMFIT"
./MCefficiency.exe "$INPUTMCNPPbPb"  "$SELGENPbPbMB" "$SELGENACCPbPbMB"  "$RECOONLYPbPbMB" "$CUTPbPbMB"  "$LABELNPPbPbMB" "$OUTPUTFILEMCSTUDYNPPbPbMB" "$ISDOWEIGHTPbPbMB" "$MINIMUMFIT" "$MAXIMUMFIT"
rm MCefficiency.exe

g++ plotPnNP.C $(root-config --cflags --libs) -g -o plotPnNP.exe 
./plotPnNP.exe "$LABELPbPbMB" "$OUTPUTFILEMCSTUDYPbPbMB" "$OUTPUTFILEMCSTUDYNPPbPbMB" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm plotPnNP.exe
fi

if [ $DORAAMB -eq 1 ]; then      
g++ NuclearModificationFactor.C $(root-config --cflags --libs) -g -o NuclearModificationFactor.exe 
./NuclearModificationFactor.exe "$OUTPUTFILEPlotPPMB" "$OUTPUTFILEPlotPbPbMB" "$LABELPbPbMB" "$OUTPUTFILERAAMB" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm NuclearModificationFactor.exe
fi

## COMBINE RESULTS

if [ $DOCombineCrossSectionPP -eq 1 ]; then      
g++ CombineCrossSections.C $(root-config --cflags --libs) -g -o CombineCrossSections.exe 
./CombineCrossSections.exe "$OUTPUTFILEPlotPPMB" "$OUTPUTFILEPlotPP" "0"
rm CombineCrossSections.exe
fi

if [ $DOCombineCrossSectionPbPb -eq 1 ]; then      
g++ CombineCrossSections.C $(root-config --cflags --libs) -g -o CombineCrossSections.exe 
./CombineCrossSections.exe "$OUTPUTFILEPlotPbPbMB" "$OUTPUTFILEPlotPbPb" "1" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm CombineCrossSections.exe
fi

if [ $DOCombineRAA -eq 1 ]; then      
g++ CombineRAA.C $(root-config --cflags --libs) -g -o CombineRAA.exe 
./CombineRAA.exe "$OUTPUTFILERAAMB" "$OUTPUTFILERAA" "$CHARGEDHADRON" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm CombineRAA.exe
fi

## SYSTEMATIC RESULTS


if [ $DOsystematicPtshape -eq 1 ]; then      
g++ PtShapeSystematic.C $(root-config --cflags --libs) -g -o PtShapeSystematic.exe 
./PtShapeSystematic.exe 
fi

cp config/parametersAllpt.h parameters.h

if [ $DOsystematicPthatstudyPP -eq 1 ]; then   

 LABELPTHATALL="pthatallPP"
 FILEOUTPTHATALL="ROOTfiles/pthatallPP.root" 
 LABELPTHATALLPTHATREWEIGHT="pthatallPPpthatreweighted"
 FILEOUTPTHATALLPTHATREWEIGHT="ROOTfiles/pthatallPPpthatreweighted.root" 
 LABELPTHATALLPTWEIGHT="pthatallPPptreweighted"
 FILEOUTPTHATALLPTWEIGHT="ROOTfiles/pthatallPPptreweighted.root" 

g++ FONLLweight.C $(root-config --cflags --libs) -g -o FONLLweight.exe 
#./FONLLweight.exe 0 "$INPUTMCPP" 2 100 "$LABELPTHATALL"
#./FONLLweight.exe 0 "$INPUTMCPPPthat10" 2 30 "$LABELPTHAT10"
#./FONLLweight.exe 0 "$INPUTMCPPPthat30" 2 70 "$LABELPTHAT30"
#./FONLLweight.exe 0 "$INPUTMCPPPthat50" 2 100 "$LABELPTHAT50"
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 
./MCefficiency.exe "$INPUTMCPP"  "$SELGENPPMB" "$SELGENACCPPMB"  "$RECOONLYPPMB" "$CUTPPMB"  "$LABELPTHATALL" "$FILEOUTPTHATALL" 0  2 100
./MCefficiency.exe "$INPUTMCPP"  "$SELGENPPMB" "$SELGENACCPPMB"  "$RECOONLYPPMB" "$CUTPPMB"  "$LABELPTHATALLPTHATREWEIGHT" "$FILEOUTPTHATALLPTHATREWEIGHT" 1  2 100
./MCefficiency.exe "$INPUTMCPP"  "$SELGENPPMB" "$SELGENACCPPMB"  "$RECOONLYPPMB" "$CUTPPMB"  "$LABELPTHATALLPTWEIGHT" "$FILEOUTPTHATALLPTWEIGHT" 2  2 100
fi

if [ $DOsystematicPthatstudyPbPb -eq 1 ]; then   
g++ FONLLweight.C $(root-config --cflags --libs) -g -o FONLLweight.exe 

 LABELPTHATALL="pthatallPbPb"
 FILEOUTPTHATALL="ROOTfiles/pthatallPbPb.root" 
 LABELPTHATALLPTHATREWEIGHT="pthatallPbPbpthatreweighted"
 FILEOUTPTHATALLPTHATREWEIGHT="ROOTfiles/pthatallPbPbpthatreweighted.root" 
 LABELPTHATALLPTWEIGHT="pthatallPbPbptreweighted"
 FILEOUTPTHATALLPTWEIGHT="ROOTfiles/pthatallPbPbptreweighted.root" 
 LABELPTHATALLPTWEIGHTPPMC="pthatallPbPbptreweightedPPMC"
 FILEOUTPTHATALLPTWEIGHTPPMC="ROOTfiles/pthatallPbPbptreweightedPPMC.root" 

#./FONLLweight.exe 0 "$INPUTMCPbPb" 2 100 "$LABELPTHATALL"
#./FONLLweight.exe 0 "$INPUTMCPbPbPthat10" 2 30 "$LABELPTHAT10"
#./FONLLweight.exe 0 "$INPUTMCPbPbPthat30" 2 70 "$LABELPTHAT30"
#./FONLLweight.exe 0 "$INPUTMCPbPbPthat50" 2 100 "$LABELPTHAT50"
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 

./MCefficiency.exe "$INPUTMCPbPb"  "$SELGENPbPbMB" "$SELGENACCPbPbMB"  "$RECOONLYPbPbMB" "$CUTPbPbMB" "$LABELPTHATALL" "$FILEOUTPTHATALL" 0  2 100
./MCefficiency.exe "$INPUTMCPbPb"  "$SELGENPbPbMB" "$SELGENACCPbPbMB"  "$RECOONLYPbPbMB" "$CUTPbPbMB" "$LABELPTHATALLPTHATREWEIGHT" "$FILEOUTPTHATALLPTHATREWEIGHT" 1  2 100
./MCefficiency.exe "$INPUTMCPbPb"  "$SELGENPbPbMB" "$SELGENACCPbPbMB"  "$RECOONLYPbPbMB" "$CUTPbPbMB" "$LABELPTHATALLPTWEIGHT" "$FILEOUTPTHATALLPTWEIGHT" 3  2 100
./MCefficiency.exe "$INPUTMCPP"  "$SELGENPbPbMB" "$SELGENACCPbPbMB"  "$RECOONLYPbPbMB" "$CUTPbPbMB" "$LABELPTHATALLPTWEIGHTPPMC" "$FILEOUTPTHATALLPTWEIGHTPPMC" 0  2 100
fi


cp config/parametersHighpt.h parameters.h

OUTPUTFILEPPMCClosure="ROOTfiles/hPtSpectrumDzeroPPMCClosure.root"
OUTPUTFILEPbPbMCClosure="ROOTfiles/hPtSpectrumDzeroPbPbMCClosure.root"
LUMIPPMCClosure=1
ISMCPPMCClosure=1
ISDOWEIGHTPPMCClosure=0
TRGPPMCClosure="1"
LABELPPMCClosure="PPMCClosure"

LUMIPbPbMCClosure=1
ISMCPbPbMCClosure=1
ISDOWEIGHTPbPbMCClosure=0
TRGPbPbMCClosure="1"
LABELPbPbMCClosure="PbPbMCClosure"

if [ $DOFITSPPMCClosure -eq 1 ]; then      
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe "$INPUTMCPP"  "$INPUTMCPP"  "$TRGPPMCClosure" "$CUTPP"   "$SELGENPP"   "$ISMCPPMCClosure"   "$LUMIPPMCClosure"   "$ISDOWEIGHTPPMCClosure"   "$LABELPPMCClosure"  "$OUTPUTFILEPPMCClosure"
g++ ClosureTest.C $(root-config --cflags --libs) -g -o ClosureTest.exe 
./ClosureTest.exe "$OUTPUTFILEPPMCClosure" "$LABELPP"
fi

if [ $DOFITSPbPbMCClosure -eq 1 ]; then      
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe "$INPUTMCPbPb"  "$INPUTMCPbPb"  "$TRGPbPbMCClosure" "$CUTPbPb"   "$SELGENPbPb"   "$ISMCPbPbMCClosure"   "$LUMIPbPbMCClosure"   "$ISDOWEIGHTPbPbMCClosure"   "$LABELPbPbMCClosure"  "$OUTPUTFILEPbPbMCClosure"
g++ ClosureTest.C $(root-config --cflags --libs) -g -o ClosureTest.exe 
./ClosureTest.exe "$OUTPUTFILEPbPbMCClosure" "$LABELPbPb"
fi

cp config/parametersLowpt.h parameters.h

OUTPUTFILEPPMBMCClosure="ROOTfiles/hPtSpectrumDzeroPPMBMCClosure.root"
OUTPUTFILEPbPbMBMCClosure="ROOTfiles/hPtSpectrumDzeroPbPbMBMCClosure.root"
LUMIPPMBMCClosure=1
ISMCPPMBMCClosure=1
ISDOWEIGHTPPMBMCClosure=0
TRGPPMBMCClosure="1"
LABELPPMBMCClosure="PPMBMCClosure"

LUMIPbPbMBMCClosure=1
ISMCPbPbMBMCClosure=1
ISDOWEIGHTPbPbMBMCClosure=0
TRGPbPbMBMCClosure="1"
LABELPbPbMBMCClosure="PbPbMBMCClosure"

if [ $DOFITSPPMBMCClosure -eq 1 ]; then      
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe "$INPUTMCPP"  "$INPUTMCPP"  "$TRGPPMBMCClosure" "$CUTPPMB"   "$SELGENPPMB"   "$ISMCPPMBMCClosure"   "$LUMIPPMBMCClosure"   "$ISDOWEIGHTPPMBMCClosure"   "$LABELPPMBMCClosure"  "$OUTPUTFILEPPMBMCClosure"
g++ ClosureTest.C $(root-config --cflags --libs) -g -o ClosureTest.exe 
./ClosureTest.exe "$OUTPUTFILEPPMBMCClosure" "$LABELPPMB"
fi

if [ $DOFITSPbPbMBMCClosure -eq 1 ]; then      
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe "$INPUTMCPbPb"  "$INPUTMCPbPb"  "$TRGPbPbMBMCClosure" "$CUTPbPbMB"   "$SELGENPbPb"   "$ISMCPbPbMBMCClosure"   "$LUMIPbPbMBMCClosure"   "$ISDOWEIGHTPbPbMBMCClosure"   "$LABELPbPbMBMCClosure"  "$OUTPUTFILEPbPbMBMCClosure"
g++ ClosureTest.C $(root-config --cflags --libs) -g -o ClosureTest.exe 
./ClosureTest.exe "$OUTPUTFILEPbPbMBMCClosure" "$LABELPbPbMB"
fi
