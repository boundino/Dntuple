#include "uti.h"

#define SPE_NUM 6
TString texNtuple[SPE_NUM] = {"ntDkpi","ntDD0kpipi","ntDD0kpipipipi","ntDkpi","ntDD0kpipi","ntDD0kpipipipi"};
TString texPP[SPE_NUM] = {"pp","pp","pp","PbPb","PbPb","PbPb"};
TString texDecay[SPE_NUM] = {"D^{0}(K#pi)","D^{*} D^{0}(K#pi)#pi","D^{*} D^{0}(K3#pi)#pi","D^{0}(K#pi)","D^{*} D^{0}(K#pi)#pi","D^{*} D^{0}(K3#pi)#pi"};
TString infnameSgl[SPE_NUM] = {"/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_prompt_D0pt0p0_Pthat080_dPt0tkPt0p5_pthatweight.root",
                               "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160229_Dfinder_20160215_pp_Pythia8D0kpi_Dstar_dPt0tkPt0p5_pthatweight.root",
                               "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpipipi/ntD_EvtBase_20160229_Dfinder_20160215_pp_Pythia8D0kpipipi_Dstar_dPt0tkPt0p5_pthatweight.root",
                               "",
                               "/data/wangj/MC2015/Dntuple/PbPb/ntD_PbPb_Dstar_D0kpi/ntD_EvtBase_20160229_Dfinder_20160215_PbPb_Pythia8D0kpi_Dstar_dPt0tkPt2p5_pthatweight.root",
                               "/data/wangj/MC2015/Dntuple/PbPb/ntD_PbPb_Dstar_D0kpipipi/ntD_EvtBase_20160229_Dfinder_20160215_PbPb_Pythia8D0kpipipi_Dstar_dPt0tkPt2p5_pthatweight.root"};
TString infnameBkg[SPE_NUM] = {"/data/wangj/Data2015/Dntuple/pp/nt_20160112_DfinderData_pp_20160111_dPt0tkPt1_D0Dstar3p5p_DCSJSON_v2_skim_20160224.root",
                               "",
                               "",
                               "/data/dmeson2015/DataDntuple/nt_skimmed_DfinderData_PbPb_20160126_dPt0tkPt2p5_D0Dstar3p5p_FINALJSON_v6_partialstats_v2.root",
                               "",
                               ""};
TString selTriggerSgl[SPE_NUM] = {"1",
                                  "1",
                                  "1",
                                  "1",
                                  "1",
                                  "1"};
TString selTriggerBkg[SPE_NUM] = {"((HLT_DmesonPPTrackingGlobal_Dpt15_v1&&Dpt>20&&Dpt<40)||(HLT_DmesonPPTrackingGlobal_Dpt30_v1&&Dpt>40&&Dpt<60)||(HLT_DmesonPPTrackingGlobal_Dpt50_v1&&Dpt>60))",
                                  "1",
                                  "1",
                                  "((HLT_HIDmesonHITrackingGlobal_Dpt20_v1&&Dpt>20&&Dpt<45)||(HLT_HIDmesonHITrackingGlobal_Dpt40_v1&&Dpt>45&&Dpt<70)||(HLT_HIDmesonHITrackingGlobal_Dpt60_v1&&Dpt>70))",
                                  "1",
                                  "1"};
TString weight[SPE_NUM] = {"pthatweight",
                           "pthatweight",
                           "pthatweight",
                           "pthatweight",
                           "pthatweight",
                           "pthatweight"};
//(DsvpvDistance/DsvpvDisErr)>3.5&&Dchi2cl>0.05&&Dalpha<0.12
TString prefilter[SPE_NUM] = {"Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(Dtrk1PtErr/Dtrk1Pt)<0.1&&(Dtrk2PtErr/Dtrk2Pt)<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&Dtrk1Algo>3&&Dtrk1Algo<8&&Dtrk2Algo>3&&Dtrk2Algo<8&&(Dtrk1PixelHit+Dtrk1S\
tripHit)>=11&&(Dtrk2PixelHit+Dtrk2StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer))<0.15&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer))<0.15&&(DlxyBS/DlxyBSErr)>1.5",
                              "Dy>-1.0&&Dy<1.0&&Dtrk1Pt>0.5&&DRestrk1Pt>0.5&&DRestrk2Pt>0.5",
                              "Dy>-1.0&&Dy<1.0&&Dtrk1Pt>0.5&&DRestrk1Pt>0.5&&DRestrk2Pt>0.5",
                              "Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>8.5&&Dtrk2Pt>8.5&&(Dtrk1PtErr/Dtrk1Pt)<0.1&&(Dtrk2PtErr/Dtrk2Pt)<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk2PixelHit+Dtrk2StripHit)>=11&&(Dt\
rk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer))<0.15&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer))<0.15&&(DlxyBS/DlxyBSErr)>2.5",
                              "Dy>-1.0&&Dy<1.0&&Dtrk1Pt>1.&&DRestrk1Pt>0.5&&DRestrk2Pt>0.5&&DRestrk3Pt>0.5&&DRestrk4Pt>0.5",
                              "Dy>-1.0&&Dy<1.0&&Dtrk1Pt>1.&&DRestrk1Pt>0.5&&DRestrk2Pt>0.5&&DRestrk3Pt>0.5&&DRestrk4Pt>0.5"};
TString selSgl[SPE_NUM] = {Form("%s&&Dgen==23333",prefilter[0].Data()),
                           Form("%s&&Dgen==23333",prefilter[1].Data()),
                           Form("%s&&Dgen==23333",prefilter[2].Data()),
                           Form("%s&&Dgen==23333",prefilter[3].Data()),
                           Form("%s&&Dgen==23333",prefilter[4].Data()),
                           Form("%s&&Dgen==23333",prefilter[5].Data())};
TString selBkg[SPE_NUM] = {Form("%s&&TMath::Abs(Dmass-1.86486)>0.06&&TMath::Abs(Dmass-1.86486)<0.12",prefilter[0].Data()),
                           Form("%s&&TMath::Abs(Dmass-2.01028)>0.10&&TMath::Abs(Dmass-2.01028)<0.15",prefilter[1].Data()),
                           Form("%s&&TMath::Abs(Dmass-2.01028)>0.10&&TMath::Abs(Dmass-2.01028)<0.15",prefilter[2].Data()),
                           Form("%s&&TMath::Abs(Dmass-1.86486)>0.06&&TMath::Abs(Dmass-1.86486)<0.12",prefilter[3].Data()),
                           Form("%s&&TMath::Abs(Dmass-2.01028)>0.10&&TMath::Abs(Dmass-2.01028)<0.15",prefilter[4].Data()),
                           Form("%s&&TMath::Abs(Dmass-2.01028)>0.10&&TMath::Abs(Dmass-2.01028)<0.15",prefilter[5].Data())};
