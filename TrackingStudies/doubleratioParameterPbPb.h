#include "uti.h"

TString weight = "1";

Double_t binwidth3prong=(0.160-0.140)/60.;
Double_t binwidth5prong=(0.160-0.140)/60.;
Double_t minmass3prong=0.142;
Double_t maxmass3prong=0.155;
Double_t minmass5prong=0.142;
Double_t maxmass5prong=0.155;

TString texData[2] = {"MC","Data"};
TString infnameData3p[2] = {"/data/wangj/MC2015/Dntuple/PbPb/ntD_PbPb_Dstar_D0kpi/ntD_EvtBase_20160104_Dfinder_20151229_PbPb_Pythia8D0kpi_Dstar_noweight.root",
                            "/data/wangj/Data2015/Dntuple/PbPb/ntD_EvtBase_20160108_HIHardProbes_DfinderData_PbPb_20151227_dPt10tkPt2p5_D0Dstar3p5p_CameliaJSON.root"};
TString infnameData5p[2] = {"/data/wangj/MC2015/Dntuple/PbPb/ntD_PbPb_Dstar_D0kpipipi/ntD_EvtBase_20160104_Dfinder_20151229_PbPb_Pythia8D0kpipipi_Dstar_noweight.root",
                            "/data/wangj/Data2015/Dntuple/PbPb/ntD_EvtBase_20160108_HIHardProbes_DfinderData_PbPb_20151227_dPt10tkPt2p5_D0Dstar3p5p_CameliaJSON.root"};
TString infnameMC3p[2] = {"/data/wangj/MC2015/Dntuple/PbPb/ntD_PbPb_Dstar_D0kpi/ntD_EvtBase_20160104_Dfinder_20151229_PbPb_Pythia8D0kpi_Dstar_noweight.root",
                          "/data/wangj/MC2015/Dntuple/PbPb/ntD_PbPb_Dstar_D0kpi/ntD_EvtBase_20160104_Dfinder_20151229_PbPb_Pythia8D0kpi_Dstar_noweight.root"};
TString infnameMC5p[3] = {"/data/wangj/MC2015/Dntuple/PbPb/ntD_PbPb_Dstar_D0kpipipi/ntD_EvtBase_20160104_Dfinder_20151229_PbPb_Pythia8D0kpipipi_Dstar_noweight.root",
                          "/data/wangj/MC2015/Dntuple/PbPb/ntD_PbPb_Dstar_D0kpipipi/ntD_EvtBase_20160104_Dfinder_20151229_PbPb_Pythia8D0kpipipi_Dstar_noweight.root"};
TString triggerselection = "1";
TString prefilter3p = "Dtrk1Pt>2.5&&DRestrk1Pt>2.5&&DRestrk2Pt>2.5&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>2.5";
TString prefilter5p = "Dtrk1Pt>2.5&&DRestrk1Pt>2.5&&DRestrk2Pt>2.5&&DRestrk3Pt>2.5&&DRestrk4Pt>2.5&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>2.5";
TString seldata3p = Form("%s&&abs(Dy)<1.&&DtktkRes_chi2cl>0.042&&DtktkRes_alpha<0.038&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>2.26&&%s",prefilter3p.Data(),triggerselection.Data());
TString seldata5p = Form("%s&&abs(Dy)<1.&&DtktkRes_chi2cl>0.067&&DtktkRes_alpha<0.035&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>3.31&&%s",prefilter5p.Data(),triggerselection.Data());
TString selmc3p = Form("%s&&Dgen==23333",seldata3p.Data());
TString selmc5p = Form("%s&&Dgen==23333",seldata5p.Data());
TString selgen3p = "abs(Gy)<1.&&(GisSignal==9||GisSignal==10)";
TString selgen5p = "abs(Gy)<1.&&(GisSignal==11||GisSignal==12)";
