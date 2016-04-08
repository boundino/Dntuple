
const int nBins=2;
double ptBins[nBins+1] = {10,15,20.};
const int nBinsReweight=50;
double ptBinsReweight[nBinsReweight+1] = {0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100};

const int ntriggers=4;
TString triggerHLTPP[ntriggers]={"HLT_DmesonPPTrackingGlobal_Dpt8_v1","HLT_DmesonPPTrackingGlobal_Dpt15_v1","HLT_DmesonPPTrackingGlobal_Dpt30_v1","HLT_DmesonPPTrackingGlobal_Dpt50_v1"};
int triggerHLTPPthresholds[ntriggers]={8,15,30,50};
int triggerassignmentPP[nBins]= {0,0};
TString triggerHLTPbPb[ntriggers]={"HLT_HIDmesonHITrackingGlobal_Dpt20_v1","HLT_HIDmesonHITrackingGlobal_Dpt40_v1","HLT_HIDmesonHITrackingGlobal_Dpt60_v1"};
int triggerHLTPbPbthresholds[ntriggers]={20,40,60};
int triggerassignmentPbPb[nBins]= {0,0};

/*
const int nBins=9;
double ptBins[nBins+1] = {10,15,20.,25,30.,40.,50.,60.,80,100};
const int nBinsReweight=50;
double ptBinsReweight[nBinsReweight+1] = {0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100};

const int ntriggers=4;
TString triggerHLTPP[ntriggers]={"HLT_DmesonPPTrackingGlobal_Dpt8_v1","HLT_DmesonPPTrackingGlobal_Dpt15_v1","HLT_DmesonPPTrackingGlobal_Dpt30_v1","HLT_DmesonPPTrackingGlobal_Dpt50_v1"};
int triggerHLTPPthresholds[ntriggers]={8,15,30,50};
int triggerassignmentPP[nBins]= {0,0,1,1,1,2,2,3,3};
TString triggerHLTPbPb[ntriggers]={"HLT_HIDmesonHITrackingGlobal_Dpt20_v1","HLT_HIDmesonHITrackingGlobal_Dpt40_v1","HLT_HIDmesonHITrackingGlobal_Dpt60_v1"};
int triggerHLTPbPbthresholds[ntriggers]={20,40,60};
int triggerassignmentPbPb[nBins]= {0,0,0,1,1,2,2};



*/
//nothing from here on needs to be changed
const int BIN_NUM= 1196;
const int HMIN=1;
const int HMAX=300;

const double binsize=((double)(HMAX)-(double)(HMIN))/(double)(BIN_NUM);
Double_t BRchain=0.0388;
