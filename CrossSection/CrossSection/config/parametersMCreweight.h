const int nBins=100;
double ptBins[nBins+1] = {0.,1.,2.,3.,4.,5.,6.,7.,8.,9.,10.,11.,12.,13.,14.,15.,16.,17.,18.,19.,20.,21.,22.,23.,24.,25.,26.,27.,28.,29.,30.,31.,32.,33.,34.,35.,36.,37.,38.,39.,40.,41.,42.,43.,44.,45.,46.,47.,48.,49.,50.,51.,52.,53.,54.,55.,56.,57.,58.,59.,60.,61.,62.,63.,64.,65.,66.,67.,68.,69.,70.,71.,72.,73.,74.,75.,76.,77.,78.,79.,80.,81.,82.,83.,84.,85.,86.,87.,88.,89.,90.,91.,92.,93.,94.,95.,96.,97.,98.,99.,100.};
const int ntriggers=3;
TString triggerHLTPP[ntriggers]={"HLT_DmesonPPTrackingGlobal_Dpt15_v1","HLT_DmesonPPTrackingGlobal_Dpt30_v1","HLT_DmesonPPTrackingGlobal_Dpt50_v1"};
int triggerassignmentPP[nBins]= {0,0,0,0,1,1,1,1,2,2,2};
TString triggerHLTPbPb[ntriggers]={"HLT_HIDmesonHITrackingGlobal_Dpt20_v1","HLT_HIDmesonHITrackingGlobal_Dpt40_v1","HLT_HIDmesonHITrackingGlobal_Dpt60_v1"};
int triggerassignmentPbPb[nBins]= {0,0,0,0,0,1,1,1,1,2,2};

/*
const int nBins=5;
double ptBins[nBins+1] = {10.,15.,20.,25.,30.,50};
const int ntriggers=3;
TString triggerHLTPP[ntriggers]={"HLT_DmesonPPTrackingGlobal_Dpt15_v1","HLT_DmesonPPTrackingGlobal_Dpt30_v1","HLT_DmesonPPTrackingGlobal_Dpt50_v1"};
int triggerassignmentPP[nBins]= {0,1,2};
TString triggerHLTPbPb[ntriggers]={"HLT_HIDmesonHITrackingGlobal_Dpt20_v1","HLT_HIDmesonHITrackingGlobal_Dpt40_v1","HLT_HIDmesonHITrackingGlobal_Dpt60_v1"};
int triggerassignmentPbPb[nBins]= {0,1,2};
*/
/*
const int nBins=2;
double ptBins[nBins+1] = {60.,80.,100.};
const int ntriggers=3;
TString triggerHLTPP[ntriggers]={"HLT_DmesonPPTrackingGlobal_Dpt15_v1","HLT_DmesonPPTrackingGlobal_Dpt30_v1","HLT_DmesonPPTrackingGlobal_Dpt50_v1"};
int triggerassignmentPP[nBins]= {2,2};
TString triggerHLTPbPb[ntriggers]={"HLT_HIDmesonHITrackingGlobal_Dpt20_v1","HLT_HIDmesonHITrackingGlobal_Dpt40_v1","HLT_HIDmesonHITrackingGlobal_Dpt60_v1"};
int triggerassignmentPbPb[nBins]= {2,2};
*/
/*
const int nBins=4;
double ptBins[nBins+1] = {15.,20.,30.,40.,60.};
*/
/*
const int nBins=1;
double ptBins[nBins+1] = {60.,100.};
const int ntriggers=3;
TString triggerHLTPP[ntriggers]={"HLT_DmesonPPTrackingGlobal_Dpt15_v1","HLT_DmesonPPTrackingGlobal_Dpt30_v1","HLT_DmesonPPTrackingGlobal_Dpt50_v1"};
int triggerassignmentPP[nBins]= {2};
TString triggerHLTPbPb[ntriggers]={"HLT_HIDmesonHITrackingGlobal_Dpt20_v1","HLT_HIDmesonHITrackingGlobal_Dpt40_v1","HLT_HIDmesonHITrackingGlobal_Dpt60_v1"};
int triggerassignmentPbPb[nBins]= {2};
*/
/*
//ALICE binning
const int nBins=9;
double ptBins[nBins+1] = {1.,2.,3.,4.,5.,6.,7.,8.,12.,16.};
const int ntriggers=1;
TString triggerHLTPP[ntriggers]={"HLT_DmesonPPTrackingGlobal_Dpt15_v1"};
int triggerassignmentPP[nBins]= {0,0,0,0,0,0,0,0,0};
TString triggerHLTPbPb[ntriggers]={"HLT_HIDmesonHITrackingGlobal_Dpt20_v1"};
int triggerassignmentPbPb[nBins]= {0,0,0,0,0,0,0,0,0};
*/
/*
//ATLAS binning for pp 7 TeV for D*
const int nBins=9;
double ptBins[nBins+1] = {3.5,5.0,6.5,8.0,12.0,20.0,30.,40.,60.,100.};
*/
//nothing from here on needs to be changed
const int BIN_NUM= 1196;
const int HMIN=1;
const int HMAX=300;

const double binsize=((double)(HMAX)-(double)(HMIN))/(double)(BIN_NUM);
Double_t BRchain=0.0388;
