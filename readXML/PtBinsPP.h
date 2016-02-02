#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <string>
#include <cmath>
#include <vector>
#include "TH1F.h"
#include "TMath.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TXMLEngine.h"
#include "Tools.h"
#include "TGaxis.h"
#include "TLegend.h"
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "Rtypes.h"
#include "TF1.h"

#define BIN_NUM 100
#define Nsigma 2
Bool_t verbose = false;
const int Nmax = 1000;
Float_t central[Nmax],pt[Nmax];
TString func = "CutsSA";
Double_t effS[100], effB[100],effSig[100];
std::vector<TString> cuts;
std::vector<Double_t> cutval[3];

const int nChannel = 2;
TString chname[nChannel] = {"D* D0(kpi)pi",
                            "D* D0(kpipipi)pi"};
TString ntDtr[nChannel] = {"ntDD0kpipi",
                           "ntDD0kpipipipi"};
TString cut_bsc[nChannel] = {"(Dy>-1.0&&Dy<1.0&&Dtrk1Pt>1.&&DRestrk1Pt>1.&&DRestrk2Pt>1.)",
                             "(Dy>-1.0&&Dy<1.0&&Dtrk1Pt>1.&&DRestrk1Pt>1.&&DRestrk2Pt>1.&&DRestrk3Pt>1.&&DRestrk4Pt>1.)"};
TString cut_sig[nChannel] = {Form("%s&&Dgen==23333",cut_bsc[0].Data()),
                             Form("%s&&Dgen==23333",cut_bsc[1].Data())};
TString cut_bkg[nChannel] = {Form("%s&&TMath::Abs(Dmass-2.01)>0.1&&TMath::Abs(Dmass-2.01)<0.15",cut_bsc[0].Data()),
                             Form("%s&&TMath::Abs(Dmass-2.01)>0.1&&TMath::Abs(Dmass-2.01)<0.15",cut_bsc[1].Data())};
//TString cutB = Form("%s&&Dpt>%f&&Dpt<%f&&TMath::Abs(DtktkResmass-1.864)>0.1&&TMath::Abs(DtktkResmass-1.864)<0.15",cut.Data(),ptmin,ptmax);
TString cut_gen[nChannel] = {"((GisSignal==9||GisSignal==10)&&(Gy>-1&&Gy<1))",
                             "((GisSignal==11||GisSignal==12)&&(Gy>-1&&Gy<1))"};
TString inputSname[nChannel] = {"/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20151231_Dfinder_20151229_pp_Pythia8D0kpi_noweight.root",
                                "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpipipi/ntD_EvtBase_20151231_Dfinder_20151229_pp_Pythia8D0kpipipi_noweight.root"};
TString inputBname[nChannel] = {"/data/wangj/Data2015/Dntuple/pp/ntD_EvtBase_20160104_HeavyFlavor_DfinderData_pp_20151218_dPt0tkPt1_D0Dstar3p5p.root",
                                "/data/wangj/Data2015/Dntuple/pp/ntD_EvtBase_20160104_HeavyFlavor_DfinderData_pp_20151218_dPt0tkPt1_D0Dstar3p5p.root"};
TString inputFonll[nChannel] = {"fonlls/fo_Dstar_pp_5p02_y1.dat",
                                "fonlls/fo_Dstar_pp_5p02_y1.dat"};
Double_t dCntDD0kpipi = 0.677*0.0388;
Double_t dCntDD0kpipipipi = 0.677*0.0807;
Double_t decayChain[nChannel] = {dCntDD0kpipi,dCntDD0kpipipipi};


/*
#define NPT  12
Double_t ptbins[NPT+1] = {0,3.5,4.5,5.5,7,9,11,13,16,20,28,40,100};
//Raa[i] corresponds to ptbins[i+1] and ptbins[i+2]
Double_t RaaValues[NPT] = {1., 0.395316, 0.431103, 0.374816, 0.38176, 0.477819, 0.437075, 0.474356, 0.731914, 1.05754, 1.};
  //SA cuts alpha         3.5-4.5  4.5-5.5 5.5-7   7-9     9-11    11-13   13-16   16-20   20-28   28-40   40-100
Double_t ffls3dcut[NPT] =   {4.,     3.98,   4.14,   3.87,   4.36,   3.68,   3.59,   3.25,   2.76,   3.18,   2.};//5.5-7:5.06;4.5-5.5:6.21
Double_t alphacut[NPT] =    {0.975,  0.065,  0.069,  0.053,  0.066,  0.075,  0.060,  0.061,  0.055,  0.133,  0.975};//0.047;0.046
Double_t fprobcut[NPT] =    {0.08,   0.082,  0.209,  0.113,  0.093,  0.057,  0.107,  0.025,  0.068,  0.022,  0.08};//0.122;0.165
Double_t fchi2cut[NPT] =    {3.,     3.,     1.e+6,  1.e+6,  1.e+6,  1.e+6,  1.e+6,  1.e+6,  1.e+6,  1.e+6,  3.};
Double_t cosalphacut[NPT] = {0.975,  0.975,  0.975,  0.997,  0.997,  0.998,  0.997,  0.998,  0.998,  0.999,  0.975};//
*/
