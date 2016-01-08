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
TString channel = "Dstar3pPP";
TString func = "SA";
TString cut = "(Dy>-1.0&&Dy<1.0&&Dpt>1.&&Dtrk1Pt>1.&&DRestrk1Pt>1.&&DRestrk2Pt>1.)";
TString cut_gen = "((GisSignal==9||GisSignal==10)&&(Gy>-1&&Gy<1))";
Double_t effS[100], effB[100],effSig[100];
std::vector<TString> cuts;
std::vector<Double_t> cutval[3];

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
