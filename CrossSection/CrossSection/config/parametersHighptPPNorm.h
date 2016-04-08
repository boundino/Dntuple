const int nBins=2;
double ptBins[nBins+1] = {10,15,20.};

const int ntriggers=2;
TString triggerHLTPP[ntriggers]={"HLT_DmesonPPTrackingGlobal_Dpt8_v1","HLT_DmesonPPTrackingGlobal_Dpt50_v1"};
int triggerHLTPPthresholds[ntriggers]={8,50};
int triggerassignmentPP[nBins]= {0,0};

TString triggerHLTPbPb[ntriggers]={"HLT_HIDmesonHITrackingGlobal_Dpt20_v1","HLT_HIDmesonHITrackingGlobal_Dpt60_v1"};
int triggerHLTPbPbthresholds[ntriggers]={20,60};
int triggerassignmentPbPb[nBins]= {0,0};

//nothing from here on needs to be changed
const int BIN_NUM= 1196;
const int HMIN=1;
const int HMAX=300;

const double binsize=((double)(HMAX)-(double)(HMIN))/(double)(BIN_NUM);
Double_t BRchain=0.0388;
