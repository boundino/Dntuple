#include "uti.h"

TString weight = "1";

Double_t binwidth3prong=(0.160-0.140)/60.;
Double_t binwidth5prong=(0.160-0.140)/60.;
Double_t minmass3prong=0.142;
Double_t maxmass3prong=0.155;
Double_t minmass5prong=0.142;
Double_t maxmass5prong=0.155;

#define SPE_NUM 4
TString texData[SPE_NUM] = {"MC","Data","MC_MB","Data_MB"};
TString infnameData3p[SPE_NUM] = {"/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_Dstarpt15p0_Pthat15_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root",
                                  "/data/wangj/Data2015/Dntuple/pp/ntD_EvtBase_20160104_HeavyFlavor_DfinderData_pp_20151218_dPt0tkPt1_D0Dstar3p5p.root",
                                  "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_Dstarpt15p0_Pthat15_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root",
                                  "/data/jisun/pp2015/ntD_pp_2015_MB0106101418_AOD_tkpt0p5_D0_Ds_Dstar3and5prong_1216_fixDs_1222.root"};
TString infnameData5p[SPE_NUM] = {"/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpipipi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpipipi_Dstarpt15p0_Pthat15_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root",
                                  "/data/wangj/Data2015/Dntuple/pp/ntD_EvtBase_20160104_HeavyFlavor_DfinderData_pp_20151218_dPt0tkPt1_D0Dstar3p5p.root",
                                  "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpipipi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpipipi_Dstarpt15p0_Pthat15_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root",
                                  "/data/jisun/pp2015/ntD_pp_2015_MB0106101418_AOD_tkpt0p5_D0_Ds_Dstar3and5prong_1216_fixDs_1222.root"};
TString infnameMC3p[SPE_NUM] = {"/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_Dstarpt15p0_Pthat15_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root",
                                "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_noweight.root",
                                "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_Dstarpt15p0_Pthat15_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root",
                                "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_noweight.root"};
TString infnameMC5p[SPE_NUM] = {"/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpipipi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpipipi_Dstarpt15p0_Pthat15_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root",
                                "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpipipi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpipipi_noweight.root",
                                "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpipipi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpipipi_Dstarpt15p0_Pthat15_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root",
                                "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpipipi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpipipi_noweight.root"};
TString triggerselection[SPE_NUM] = {"1","1","1",
                                     "(HLT_L1MinimumBiasHF1OR_part0_v1||HLT_L1MinimumBiasHF1OR_part1_v1||HLT_L1MinimumBiasHF1OR_part2_v1||HLT_L1MinimumBiasHF1OR_part3_v1||HLT_L1MinimumBiasHF1OR_part4_v1||HLT_L1MinimumBiasHF1OR_part5_v1||HLT_L1MinimumBiasHF1OR_part6_v1||HLT_L1MinimumBiasHF1OR_part7_v1||HLT_L1MinimumBiasHF1OR_part8_v1||HLT_L1MinimumBiasHF1OR_part9_v1||HLT_L1MinimumBiasHF1OR_part10_v1||HLT_L1MinimumBiasHF1OR_part11_v1||HLT_L1MinimumBiasHF1OR_part12_v1||HLT_L1MinimumBiasHF1OR_part13_v1||HLT_L1MinimumBiasHF1OR_part14_v1||HLT_L1MinimumBiasHF1OR_part15_v1||HLT_L1MinimumBiasHF1OR_part16_v1||HLT_L1MinimumBiasHF1OR_part17_v1||HLT_L1MinimumBiasHF1OR_part18_v1||HLT_L1MinimumBiasHF1OR_part19_v1)"};
TString prefilter3p = "Dtrk1Pt>1.&&DRestrk1Pt>1.&&DRestrk2Pt>1.&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>2.5";
TString prefilter5p = "Dtrk1Pt>1.&&DRestrk1Pt>1.&&DRestrk2Pt>1.&&DRestrk3Pt>1.&&DRestrk4Pt>1.&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>2.5";
TString seldata3p = Form("%s&&abs(Dy)<1.&&DtktkRes_chi2cl>0.043&&DtktkRes_alpha<0.069&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>0.",prefilter3p.Data());
TString seldata5p = Form("%s&&abs(Dy)<1.&&DtktkRes_chi2cl>0.049&&DtktkRes_alpha<0.053&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>3.45",prefilter5p.Data());
TString selmc3p = Form("%s&&Dgen==23333",seldata3p.Data());
TString selmc5p = Form("%s&&Dgen==23333",seldata5p.Data());
TString selswp3p = Form("%s&&Dgen==23344",seldata3p.Data());
TString selswp5p = Form("%s&&Dgen==23344",seldata5p.Data());
TString selgen3p = "abs(Gy)<1.&&(GisSignal==9||GisSignal==10)";
TString selgen5p = "abs(Gy)<1.&&(GisSignal==11||GisSignal==12)";
