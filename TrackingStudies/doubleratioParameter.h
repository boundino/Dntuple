#include "uti.h"

TString weight = "1";

Double_t binwidth3prong=(0.160-0.140)/60.;
Double_t binwidth5prong=(0.160-0.140)/60.;
Double_t minmass3prong=0.142;
Double_t maxmass3prong=0.155;
Double_t minmass5prong=0.142;
Double_t maxmass5prong=0.155;

TString texData[2] = {"MC","Data"};
TString infnameData3p[2] = {"/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_noweight.root",
                            "/data/wangj/Data2015/Dntuple/pp/ntD_EvtBase_20160104_HeavyFlavor_DfinderData_pp_20151218_dPt0tkPt1_D0Dstar3p5p.root"};
TString infnameData5p[2] = {"/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpipipi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpipipi_noweight.root",
                            "/data/wangj/Data2015/Dntuple/pp/ntD_EvtBase_20160104_HeavyFlavor_DfinderData_pp_20151218_dPt0tkPt1_D0Dstar3p5p.root"};
TString infnameMC3p[2] = {"/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_noweight.root",
                          "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_noweight.root"};
TString infnameMC5p[3] = {"/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpipipi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpipipi_noweight.root",
                          "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpipipi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpipipi_noweight.root"};
TString triggerselection = "1";
TString prefilter3p = "Dtrk1Pt>1.&&DRestrk1Pt>1.&&DRestrk2Pt>1.&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>2.5";
TString prefilter5p = "Dtrk1Pt>1.&&DRestrk1Pt>1.&&DRestrk2Pt>1.&&DRestrk3Pt>1.&&DRestrk4Pt>1.&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>2.5";
TString seldata3p = Form("%s&&abs(Dy)<1.&&DtktkRes_chi2cl>0.043&&DtktkRes_alpha<0.069&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>0.&&%s",prefilter3p.Data(),triggerselection.Data());
TString seldata5p = Form("%s&&abs(Dy)<1.&&DtktkRes_chi2cl>0.049&&DtktkRes_alpha<0.053&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>3.45&&%s",prefilter5p.Data(),triggerselection.Data());
TString selmc3p = Form("%s&&Dgen==23333",seldata3p.Data());
TString selmc5p = Form("%s&&Dgen==23333",seldata5p.Data());
TString selgen3p = "abs(Gy)<1.&&(GisSignal==9||GisSignal==10)";
TString selgen5p = "abs(Gy)<1.&&(GisSignal==11||GisSignal==12)";
