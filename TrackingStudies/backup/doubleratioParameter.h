#include "uti.h"

const int BINNUM=50;
Double_t BINMIN=0.140;
Double_t BINMAX=0.160;
Double_t BINWID=(BINMAX-BINMIN)/BINNUM;
Double_t minmass=0.14300;
Double_t maxmass=0.148;

#define SPE_NUM 4
TString texData[SPE_NUM] = {"MC","Data","MC_MB","Data_MB"};
TString weightdata[SPE_NUM] = {"1","1","pthatweight","1"};
TString weightmc[SPE_NUM] = {"1","1","pthatweight","pthatweight"};
TString infnameData3p[SPE_NUM] = {"/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_Dstarpt15p0_Pthat15_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root",
                                  "/data/wangj/Data2015/Dntuple/pp/ntD_EvtBase_20160104_HeavyFlavor_DfinderData_pp_20151218_dPt0tkPt1_D0Dstar3p5p.root",
                                  "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160203_Dfinder_20160201_pp_Pythia8D0kpi_dPt0tkPt0p5_pthatweight.root",
                                  "/data/jisun/pp2015/ntD_pp_2015_MB0106101418_AOD_tkpt0p5_D0_Ds_Dstar3and5prong_1216_fixDs_1222.root"};
TString infnameData5p[SPE_NUM] = {"/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpipipi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpipipi_Dstarpt15p0_Pthat15_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root",
                                  "/data/wangj/Data2015/Dntuple/pp/ntD_EvtBase_20160104_HeavyFlavor_DfinderData_pp_20151218_dPt0tkPt1_D0Dstar3p5p.root",
                                  "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpipipi/ntD_EvtBase_20160210_Dfinder_20160209_pp_Pythia8D0kpipipi_dPt0tkPt0p5_pthatweight.root",
                                  "/data/jisun/pp2015/ntD_pp_2015_MB0106101418_AOD_tkpt0p5_D0_Ds_Dstar3and5prong_1216_fixDs_1222.root"};
TString infnameMC3p[SPE_NUM] = {"/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_Dstarpt15p0_Pthat15_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root",
                                "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_noweight.root",
                                "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160203_Dfinder_20160201_pp_Pythia8D0kpi_dPt0tkPt0p5_pthatweight.root",
                                "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160203_Dfinder_20160201_pp_Pythia8D0kpi_dPt0tkPt0p5_pthatweight.root"};
TString infnameMC5p[SPE_NUM] = {"/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpipipi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpipipi_Dstarpt15p0_Pthat15_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root",
                                "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpipipi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpipipi_noweight.root",
                                "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpipipi/ntD_EvtBase_20160210_Dfinder_20160209_pp_Pythia8D0kpipipi_dPt0tkPt0p5_pthatweight.root",
                                "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpipipi/ntD_EvtBase_20160210_Dfinder_20160209_pp_Pythia8D0kpipipi_dPt0tkPt0p5_pthatweight.root"};
Float_t scaleMC3p[SPE_NUM] = {57175./0.0388,1.,279426./0.0388,1.};
Float_t scaleMC5p[SPE_NUM] = {49938./0.0807,1.,303663./0.0807,1.};
TString triggerselectiondata[SPE_NUM] = {"1","1","1",
                                     "(HLT_L1MinimumBiasHF1OR_part0_v1||HLT_L1MinimumBiasHF1OR_part1_v1||HLT_L1MinimumBiasHF1OR_part2_v1||HLT_L1MinimumBiasHF1OR_part3_v1||HLT_L1MinimumBiasHF1OR_part4_v1||HLT_L1MinimumBiasHF1OR_part5_v1||HLT_L1MinimumBiasHF1OR_part6_v1||HLT_L1MinimumBiasHF1OR_part7_v1||HLT_L1MinimumBiasHF1OR_part8_v1||HLT_L1MinimumBiasHF1OR_part9_v1||HLT_L1MinimumBiasHF1OR_part10_v1||HLT_L1MinimumBiasHF1OR_part11_v1||HLT_L1MinimumBiasHF1OR_part12_v1||HLT_L1MinimumBiasHF1OR_part13_v1||HLT_L1MinimumBiasHF1OR_part14_v1||HLT_L1MinimumBiasHF1OR_part15_v1||HLT_L1MinimumBiasHF1OR_part16_v1||HLT_L1MinimumBiasHF1OR_part17_v1||HLT_L1MinimumBiasHF1OR_part18_v1||HLT_L1MinimumBiasHF1OR_part19_v1)"};
TString triggerselectionmc[SPE_NUM] = {"1","1","1","1"};

TString prefilter3p[SPE_NUM] = {"Dtrk1Pt>1.&&DRestrk1Pt>1.&&DRestrk2Pt>1.&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>2.5",
                                "Dtrk1Pt>1.&&DRestrk1Pt>1.&&DRestrk2Pt>1.&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>2.5",
                                "Dtrk1Pt>0.5&&DRestrk1Pt>0.5&&DRestrk2Pt>0.5&&(((DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>4.&&DtktkRespt<8.)||((DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>1.5&&DtktkRespt>8.))&&abs(DtktkResmass-1.86486)<0.05",
                                "Dtrk1Pt>0.5&&DRestrk1Pt>0.5&&DRestrk2Pt>0.5&&(((DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>4.&&DtktkRespt<8.)||((DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>1.5&&DtktkRespt>8.))&&abs(DtktkResmass-1.86486)<0.05"};
TString prefilter5p[SPE_NUM] = {"Dtrk1Pt>1.&&DRestrk1Pt>1.&&DRestrk2Pt>1.&&DRestrk3Pt>1.&&DRestrk4Pt>1.&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>2.5",
                                "Dtrk1Pt>1.&&DRestrk1Pt>1.&&DRestrk2Pt>1.&&DRestrk3Pt>1.&&DRestrk4Pt>1.&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>2.5",
                                "Dtrk1Pt>0.5&&DRestrk1Pt>0.5&&DRestrk2Pt>0.5&&DRestrk3Pt>0.5&&DRestrk4Pt>0.5&&(((DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>4.&&DtktkRespt<8.)||((DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>1.5&&DtktkRespt>8.))&&abs(DtktkResmass-1.86486)<0.05",
                                "Dtrk1Pt>0.5&&DRestrk1Pt>0.5&&DRestrk2Pt>0.5&&DRestrk3Pt>0.5&&DRestrk4Pt>0.5&&(((DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>4.&&DtktkRespt<8.)||((DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>1.5&&DtktkRespt>8.))&&abs(DtktkResmass-1.86486)<0.05"};
TString seldata3p[SPE_NUM] = {Form("%s&&abs(Dy)<1.&&DtktkRes_chi2cl>0.043&&DtktkRes_alpha<0.069&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>0.",prefilter3p[0].Data()),
                              Form("%s&&abs(Dy)<1.&&DtktkRes_chi2cl>0.043&&DtktkRes_alpha<0.069&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>0.",prefilter3p[1].Data()),
                              Form("%s&&abs(Dy)<1.",prefilter3p[2].Data()),
                              Form("%s&&abs(Dy)<1.",prefilter3p[3].Data())};
TString seldata5p[SPE_NUM] = {Form("%s&&abs(Dy)<1.&&DtktkRes_chi2cl>0.049&&DtktkRes_alpha<0.053&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>3.45",prefilter5p[0].Data()),
                              Form("%s&&abs(Dy)<1.&&DtktkRes_chi2cl>0.049&&DtktkRes_alpha<0.053&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>3.45",prefilter5p[1].Data()),
                              Form("%s&&abs(Dy)<1.",prefilter5p[2].Data()),
                              Form("%s&&abs(Dy)<1.",prefilter5p[3].Data())};
TString selmc3p[SPE_NUM] = {Form("%s&&Dgen==23333",seldata3p[0].Data()),
                            Form("%s&&Dgen==23333",seldata3p[1].Data()),
                            Form("%s&&Dgen==23333",seldata3p[2].Data()),
                            Form("%s&&Dgen==23333",seldata3p[3].Data())};
TString selmc5p[SPE_NUM] = {Form("%s&&Dgen==23333",seldata5p[0].Data()),
                            Form("%s&&Dgen==23333",seldata5p[1].Data()),
                            Form("%s&&Dgen==23333",seldata5p[2].Data()),
                            Form("%s&&Dgen==23333",seldata5p[3].Data())};
TString selswp3p[SPE_NUM] = {Form("%s&&Dgen==23344",seldata3p[0].Data()),
                             Form("%s&&Dgen==23344",seldata3p[1].Data()),
                             Form("%s&&Dgen==23344",seldata3p[2].Data()),
                             Form("%s&&Dgen==23344",seldata3p[3].Data())};
TString selswp5p[SPE_NUM] = {Form("%s&&Dgen==23344",seldata5p[0].Data()),
                             Form("%s&&Dgen==23344",seldata5p[1].Data()),
                             Form("%s&&Dgen==23344",seldata5p[2].Data()),
                             Form("%s&&Dgen==23344",seldata5p[3].Data())};
TString selgen3p = "abs(Gy)<1.&&(GisSignal==9||GisSignal==10)";
TString selgen5p = "abs(Gy)<1.&&(GisSignal==11||GisSignal==12)";
