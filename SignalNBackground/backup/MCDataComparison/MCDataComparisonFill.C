#include "uti.h"
#include "Dntuple.h"
#include "format.h"
using namespace std;

TString weight = "1";
TString seldata;
TString selmc;
TString collisionsystem;

float signalWidth = 0.02;
float sidebandLow = 0.06;
float sidebandHigh = 0.12;
//float wfactor = 1/3.;
float wfactor = signalWidth/(sidebandHigh-sidebandLow);

enum varType{
	_Dpt,
	_Dmass,
	_Ddtheta,
	_Dalpha,
	_Dchi2cl,
	_DsvpvDistance_DsvpvDisErr,
	_DlxyBS_DlxyBSErr,
	_varSize
};

struct varStruct{
	string var;
	string title;
	int nBin;
	double xMin;
	double xMax;
	string plotName;
	string xtitle;
};

struct varStruct myVars[_varSize] = {
	{"Dpt", "Dpt", 50, 1, 100.,"Dpt", "GeV"},
	{"Dmass", "Dmass", 50, 1.7, 2.,"Dmass", "GeV"},
	{"Ddtheta","Ddtheta" ,20, 0., 0.2, "Ddtheta", ""},
//	{"Dalpha","Dalpha" ,20, 0., 0.3, "Dalpha", ""},
	{"Dalpha","Dalpha" ,20, 0., 0.12, "Dalpha", ""},
	{"Dchi2cl","Dchi2cl" ,20, 0., 1., "Dchi2cl", ""},
	{"DsvpvDistance/DsvpvDisErr","DsvpvDistance_DsvpvDisErr" ,20, 0., 20., "DsvpvDistance_DsvpvDisErr", ""},
	{"DlxyBS/DlxyBSErr","DlxyBS_DlxyBSErr" ,20, 0., 1000., "DlxyBS_DlxyBSErr",""}
};

class HLTBranches
{
    public:
        int HLT_DmesonPPTrackingGlobal_Dpt15_v1;
        int HLT_DmesonPPTrackingGlobal_Dpt30_v1;
        int HLT_DmesonPPTrackingGlobal_Dpt50_v1;
        void setHLTBranches(TTree* t1){
            t1->SetBranchAddress("HLT_DmesonPPTrackingGlobal_Dpt15_v1" ,&HLT_DmesonPPTrackingGlobal_Dpt15_v1);
            t1->SetBranchAddress("HLT_DmesonPPTrackingGlobal_Dpt30_v1" ,&HLT_DmesonPPTrackingGlobal_Dpt30_v1);
            t1->SetBranchAddress("HLT_DmesonPPTrackingGlobal_Dpt50_v1" ,&HLT_DmesonPPTrackingGlobal_Dpt50_v1);
        };
};

const int nBins=3; 
float ptBins[nBins+1]={15,40,60,100};
float pa0[nBins] = {1, 1, 1};	
float pa1[nBins] = {0, 0, 0};	
float pa2[nBins] = {0, 0, 0};	

void overlapTH1(TCanvas* c, TH1D* h1, TH1D* h2, TH1D* h3, TH1D* h4, string xTitle, TH1D* hRatio, int customize = -1);
void setBranches(TTree* t1, DntupleBranches &Dntuple);
void setGenBranches(TTree* t1, DntupleBranches &Dntuple);

void DoAnalysis(TFile* inf, TFile* infMC, TString outputfile="mytest.root", bool DoPtWeight = true)
{
	string wPrefix = "";
	if(!DoPtWeight){	
		wPrefix = "UnWeighted";
	}
	
	gStyle->SetTextSize(0.05);
	gStyle->SetTextFont(42);
	gStyle->SetPadRightMargin(0.043);
	gStyle->SetPadLeftMargin(0.18);
	gStyle->SetPadTopMargin(0.1);
	gStyle->SetPadBottomMargin(0.145);
	gStyle->SetTitleX(.0f);

	TTree* nt = (TTree*) inf->Get("ntDkpi");
	TTree* HltTree = (TTree*) inf->Get("ntHlt");
	
	TTree* ntMC = (TTree*)infMC->Get("ntDkpi");
	TTree* ntGen = (TTree*)infMC->Get("ntGen");
	TTree* ntHi = (TTree*)infMC->Get("ntHi");
	//TTree* MCHltTree;
	//MCHltTree= (TTree*)infMC->Get("ntHlt");
	
	TCanvas *c[_varSize][nBins];
	TH1D *h1[_varSize][nBins];
	TH1D *h2[_varSize][nBins];
	TH1D *h3[_varSize][nBins];
	TH1D *h4[_varSize][nBins];
	TH1D *h11[_varSize][nBins];
	TH1D *h12[_varSize][nBins];
	TH1D *h13[_varSize][nBins];
	TH1D *h14[_varSize][nBins];
	TH1D *h21[_varSize][nBins];
	TH1D *h22[_varSize][nBins];
	TH1D *h23[_varSize][nBins];
	TH1D *hRatio[_varSize][nBins];
	TH1D *ptR[nBins];

	for (int p = 0; p < nBins; p++){
		ptR[p] =  new TH1D((myVars[_Dpt].title+"Ratio"+Form("%d%s", p, wPrefix.c_str())).c_str(), myVars[_Dpt].title.c_str(), myVars[_Dpt].nBin, myVars[_Dpt].xMin, myVars[_Dpt].xMax);
		for (int i = 0 ; i < _varSize; i++){
			c[i][p] =  new TCanvas(("c"+myVars[i].title+Form("%d%s", p, wPrefix.c_str())).c_str(),"",600,600);
			h1[i][p] =  new TH1D((myVars[i].title+"1"+Form("%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
			h2[i][p] =  new TH1D((myVars[i].title+"2"+Form("%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
			h3[i][p] =  new TH1D((myVars[i].title+"3"+Form("%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
			h4[i][p] =  new TH1D((myVars[i].title+"4"+Form("%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
			h11[i][p] = new TH1D((myVars[i].title+"11"+Form("%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
			h12[i][p] = new TH1D((myVars[i].title+"12"+Form("%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
			h13[i][p] = new TH1D((myVars[i].title+"13"+Form("%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
			h14[i][p] = new TH1D((myVars[i].title+"14"+Form("%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
			h21[i][p] = new TH1D((myVars[i].title+"21"+Form("%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
			h22[i][p] = new TH1D((myVars[i].title+"22"+Form("%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
			h23[i][p] = new TH1D((myVars[i].title+"23"+Form("%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
			hRatio[i][p] = new TH1D((myVars[i].title+"_ratio"+Form("%d%s", p, wPrefix.c_str())).c_str(), (myVars[i].title+"_ratio").c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
		}
	}
	TH1D *hMCMass =    new TH1D(Form("MCDmass%s", wPrefix.c_str()), "MCDmass", 100, 1.7, 2);
	TH1D *hMCMassGM =  new TH1D(Form("MCDmassGM%s", wPrefix.c_str()), "MCDmassGM", 100, 1.7, 2);
	TH1D *hMCMassGMW = new TH1D(Form("MCDmassGMW%s", wPrefix.c_str()), "MCDmassGMW", 100, 1.7, 2);
	TH1D *hDataMass =  new TH1D(Form("DataDmass%s", wPrefix.c_str()), "DataDmass", 100, 1.7, 2);
	TH1D *hMassRatio = new TH1D(Form("DmassRatio%s", wPrefix.c_str()), "DmassRatio", 100, 1.7, 2);
	TH1D *hempty =     new TH1D(Form("empty%s", wPrefix.c_str()), "empty", 100, 1.7, 2);
    TCanvas* cMass =   new TCanvas(Form("cMass%s", wPrefix.c_str()),"",600,600);

	DntupleBranches Dntuple;
	HLTBranches HLTBh;

	setBranches(ntMC, Dntuple);
    ntMC->SetBranchAddress("Dgen" ,Dntuple.Dgen);

	float pthatweight;
	ntHi->SetBranchAddress("pthatweight" ,&pthatweight);
	float ptWeight = 1;
	int nEntries = ntMC->GetEntries();
	//nEntries = 1000000;
	for(int i=0;i<nEntries;i++){
		ntMC->GetEntry(i);
		ntHi->GetEntry(i);
		//cout<<Dntuple.Dsize<<endl;
		//cout<<HLTBh.HLT_DmesonPPTrackingGlobal_Dpt15_v1<<endl;
		for (int s = 0; s < Dntuple.Dsize; s++){
			//cout<<Dntuple.Dmass[s]<<endl;
			//printf("%f, %f\n", Dntuple.Dtrk1Pt[s], Dntuple.Dtrk2Pt[s]);
			bool boolCut = false;
			bool boolGenCut = false;
			bool boolHLTCut = false;
			bool boolSignalRG = false;
			bool boolSidebandRG = false;
			if (Dntuple.Dy[s]>-1.&&Dntuple.Dy[s]<1.
				&&Dntuple.Dtrk1highPurity[s]&&Dntuple.Dtrk2highPurity[s]
				&&Dntuple.Dtrk1Pt[s]>2.0&&Dntuple.Dtrk2Pt[s]>2.0
				&&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>3.5&&(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s])>1.5
				&&Dntuple.Dchi2cl[s]>0.05&&Dntuple.Dalpha[s]<0.12
				&&Dntuple.Dtrk1PtErr[s]/Dntuple.Dtrk1Pt[s]<0.1&&Dntuple.Dtrk2PtErr[s]/Dntuple.Dtrk2Pt[s]<0.1
				&&abs(Dntuple.Dtrk1Eta[s])<2.0&&abs(Dntuple.Dtrk2Eta[s])<2.0
				&&Dntuple.Dtrk1Algo[s]>3&&Dntuple.Dtrk1Algo[s]<8&&Dntuple.Dtrk2Algo[s]>3&&Dntuple.Dtrk2Algo[s]<8
				&&(Dntuple.Dtrk1PixelHit[s]+Dntuple.Dtrk1StripHit[s])>=11
				&&(Dntuple.Dtrk1Chi2ndf[s]/(Dntuple.Dtrk1nStripLayer[s]+Dntuple.Dtrk1nPixelLayer[s])<0.15)&&(Dntuple.Dtrk2Chi2ndf[s]/(Dntuple.Dtrk2nStripLayer[s]+Dntuple.Dtrk2nPixelLayer[s])<0.15)
			){
				boolCut = true;
			}
			if (!boolCut) continue;

			if (Dntuple.Dgen[s]==23333){
				boolGenCut = true;
			}
			if (fabs(Dntuple.Dmass[s]-1.8648)<signalWidth){
  	          boolSignalRG = true;
			}
			if (fabs(Dntuple.Dmass[s]-1.8648)>sidebandLow&fabs(Dntuple.Dmass[s]-1.8648)<sidebandHigh){
            	boolSidebandRG = true;
			}
		
			if(Dntuple.Dpt[s] > 15 && Dntuple.Dpt[s] < 40){
				hMCMass->Fill(Dntuple.Dmass[s]);
				if(boolGenCut){
					hMCMassGM->Fill(Dntuple.Dmass[s]);
					hMCMassGMW->Fill(Dntuple.Dmass[s], pthatweight);
				}
			}
			for (int p = 0; p < nBins; p++){
				ptWeight = pa0[p] + pa1[p]*Dntuple.Dpt[s] + pa2[p]*Dntuple.Dpt[s]*Dntuple.Dpt[s];
				if(Dntuple.Dpt[s]>ptBins[p]&&Dntuple.Dpt[s]<ptBins[p+1]){
					if(boolSignalRG){
						h1 [_Dpt][p]->Fill(Dntuple.Dpt[s], ptWeight);
						h11[_Dpt][p]->Fill(Dntuple.Dpt[s], pthatweight*ptWeight);
						h1 [_Dmass][p]->Fill(Dntuple.Dmass[s], ptWeight);
						h11[_Dmass][p]->Fill(Dntuple.Dmass[s], pthatweight*ptWeight);
						h1 [_Ddtheta][p]->Fill(Dntuple.Ddtheta[s], ptWeight);
						h11[_Ddtheta][p]->Fill(Dntuple.Ddtheta[s], pthatweight*ptWeight);
						h1 [_Dalpha][p]->Fill(Dntuple.Dalpha[s], ptWeight);
						h11[_Dalpha][p]->Fill(Dntuple.Dalpha[s], pthatweight*ptWeight);
						h1 [_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s], ptWeight);
						h11[_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s], pthatweight*ptWeight);
						h1 [_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s], ptWeight);
						h11[_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s], pthatweight*ptWeight);
						h1 [_DlxyBS_DlxyBSErr][p]->Fill(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s], ptWeight);
						h11[_DlxyBS_DlxyBSErr][p]->Fill(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s], pthatweight*ptWeight);
						if(boolGenCut){
							h4 [_Dpt][p]->Fill(Dntuple.Dpt[s], ptWeight);
							h14[_Dpt][p]->Fill(Dntuple.Dpt[s], pthatweight*ptWeight);
							h4 [_Dmass][p]->Fill(Dntuple.Dmass[s], ptWeight);
							h14[_Dmass][p]->Fill(Dntuple.Dmass[s], pthatweight*ptWeight);
							h4 [_Ddtheta][p]->Fill(Dntuple.Ddtheta[s], ptWeight);
							h14[_Ddtheta][p]->Fill(Dntuple.Ddtheta[s], pthatweight*ptWeight);
							h4 [_Dalpha][p]->Fill(Dntuple.Dalpha[s], ptWeight);
							h14[_Dalpha][p]->Fill(Dntuple.Dalpha[s], pthatweight*ptWeight);
							h4 [_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s], ptWeight);
							h14[_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s], pthatweight*ptWeight);
							h4 [_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s], ptWeight);
							h14[_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s], pthatweight*ptWeight);
							h4 [_DlxyBS_DlxyBSErr][p]->Fill(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s], ptWeight);
							h14[_DlxyBS_DlxyBSErr][p]->Fill(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s], pthatweight*ptWeight);
						}
					}
					if(boolSidebandRG){
						h2 [_Dpt][p]->Fill(Dntuple.Dpt[s], ptWeight);
						h12[_Dpt][p]->Fill(Dntuple.Dpt[s], pthatweight*ptWeight);
						h2 [_Dmass][p]->Fill(Dntuple.Dmass[s], ptWeight);
						h12[_Dmass][p]->Fill(Dntuple.Dmass[s], pthatweight*ptWeight);
						h2 [_Ddtheta][p]->Fill(Dntuple.Ddtheta[s], ptWeight);
						h12[_Ddtheta][p]->Fill(Dntuple.Ddtheta[s], pthatweight*ptWeight);
						h2 [_Dalpha][p]->Fill(Dntuple.Dalpha[s], ptWeight);
						h12[_Dalpha][p]->Fill(Dntuple.Dalpha[s], pthatweight*ptWeight);
						h2 [_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s], ptWeight);
						h12[_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s], pthatweight*ptWeight);
						h2 [_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s], ptWeight);
						h12[_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s], pthatweight*ptWeight);
						h2 [_DlxyBS_DlxyBSErr][p]->Fill(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s], ptWeight);
						h12[_DlxyBS_DlxyBSErr][p]->Fill(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s], pthatweight*ptWeight);
					}
				}
			}
		}
	}

	setBranches(nt, Dntuple);
	HLTBh.setHLTBranches(HltTree);
	ptWeight = 1;
	nEntries = nt->GetEntries();
	for(int i=0;i<nEntries;i++){
		nt->GetEntry(i);
		HltTree->GetEntry(i);
		for (int s = 0; s < Dntuple.Dsize; s++){
			bool boolCut = false;
			bool boolGenCut = false;
			bool boolHLTCut = false;
			bool boolSignalRG = false;
			bool boolSidebandRG = false;
			if (Dntuple.Dy[s]>-1.&&Dntuple.Dy[s]<1.
				&&Dntuple.Dtrk1highPurity[s]&&Dntuple.Dtrk2highPurity[s]
				&&Dntuple.Dtrk1Pt[s]>2.0&&Dntuple.Dtrk2Pt[s]>2.0
				&&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>3.5&&(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s])>1.5
				&&Dntuple.Dchi2cl[s]>0.05&&Dntuple.Dalpha[s]<0.12
				&&Dntuple.Dtrk1PtErr[s]/Dntuple.Dtrk1Pt[s]<0.1&&Dntuple.Dtrk2PtErr[s]/Dntuple.Dtrk2Pt[s]<0.1
				&&abs(Dntuple.Dtrk1Eta[s])<2.0&&abs(Dntuple.Dtrk2Eta[s])<2.0
				&&Dntuple.Dtrk1Algo[s]>3&&Dntuple.Dtrk1Algo[s]<8&&Dntuple.Dtrk2Algo[s]>3&&Dntuple.Dtrk2Algo[s]<8
				&&(Dntuple.Dtrk1PixelHit[s]+Dntuple.Dtrk1StripHit[s])>=11
				&&(Dntuple.Dtrk1Chi2ndf[s]/(Dntuple.Dtrk1nStripLayer[s]+Dntuple.Dtrk1nPixelLayer[s])<0.15)&&(Dntuple.Dtrk2Chi2ndf[s]/(Dntuple.Dtrk2nStripLayer[s]+Dntuple.Dtrk2nPixelLayer[s])<0.15)
			){
				boolCut = true;
			}
			if (!boolCut) continue;

			if ((HLTBh.HLT_DmesonPPTrackingGlobal_Dpt15_v1&&Dntuple.Dpt[s]>15&&Dntuple.Dpt[s]<40)
				||(HLTBh.HLT_DmesonPPTrackingGlobal_Dpt30_v1&&Dntuple.Dpt[s]>40&&Dntuple.Dpt[s]<60)
				||(HLTBh.HLT_DmesonPPTrackingGlobal_Dpt50_v1&&Dntuple.Dpt[s]>60)){
				boolHLTCut = true;
			}
			if (!boolHLTCut) continue;

			if (fabs(Dntuple.Dmass[s]-1.8648)<signalWidth){
  	          boolSignalRG = true;
			}
			if (fabs(Dntuple.Dmass[s]-1.8648)>sidebandLow&fabs(Dntuple.Dmass[s]-1.8648)<sidebandHigh){
            	boolSidebandRG = true;
			}
			hDataMass->Fill(Dntuple.Dmass[s]);
			for (int p = 0; p < nBins; p++){
				if(Dntuple.Dpt[s]>ptBins[p]&&Dntuple.Dpt[s]<ptBins[p+1]){
					if(boolSignalRG){
						h21 [_Dpt][p]->Fill(Dntuple.Dpt[s]);
						h21 [_Dmass][p]->Fill(Dntuple.Dmass[s]);
						h21 [_Ddtheta][p]->Fill(Dntuple.Ddtheta[s]);
						h21 [_Dalpha][p]->Fill(Dntuple.Dalpha[s]);
						h21 [_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s]);
						h21 [_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s]);
						h21 [_DlxyBS_DlxyBSErr][p]->Fill(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s]);
					}
					if(boolSidebandRG){
						h22 [_Dpt][p]->Fill(Dntuple.Dpt[s]);
						h22 [_Dmass][p]->Fill(Dntuple.Dmass[s]);
						h22 [_Ddtheta][p]->Fill(Dntuple.Ddtheta[s]);
						h22 [_Dalpha][p]->Fill(Dntuple.Dalpha[s]);
						h22 [_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s]);
						h22 [_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s]);
						h22 [_DlxyBS_DlxyBSErr][p]->Fill(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s]);
					}
				}
			}
		}
	}

    for (int i = 0 ; i < _varSize; i++){
	for (int p = 0 ; p < nBins; p++){
		h3[i][p] = (TH1D*)h1[i][p]->Clone();
		h3[i][p]->Add(h2[i][p],-wfactor);

		h13[i][p] = (TH1D*)h11[i][p]->Clone();
		h13[i][p]->Add(h12[i][p],-wfactor);

		h23[i][p] = (TH1D*)h21[i][p]->Clone();
		h23[i][p]->Add(h22[i][p],-wfactor);
		overlapTH1(c[i][p], h14[i][p], h13[i][p], h23[i][p], h21[i][p], myVars[i].xtitle, hRatio[i][p]);
		c[i][p]->SaveAs(("plotsFill/"+myVars[i].plotName+Form("ptBin%d%s", p, wPrefix.c_str())+".pdf").c_str());
	}}
	if (DoPtWeight){
	    overlapTH1(cMass, hMCMassGM, hMCMassGMW, hMCMass, hDataMass, "Dmass", hMassRatio, 1);
		cMass->SaveAs("plotsFill/mass.pdf");
	}

	if (!DoPtWeight){
		for (int p = 0; p < nBins; p++){
			h23[_Dpt][p]->Sumw2();
			h13[_Dpt][p]->Sumw2();
			h23[_Dpt][p]->Scale(1/h23[_Dpt][p]->Integral());
			h13[_Dpt][p]->Scale(1/h13[_Dpt][p]->Integral());
			ptR[p] = (TH1D*)h23[_Dpt][p]->Clone();
			ptR[p]->Divide(h13[_Dpt][p]);
			TCanvas* cptR =  new TCanvas(Form("cptR%d", p),"",600,600);
	  		TF1* f = new TF1(Form("f%d", p),"[0]+[1]*x+[2]*x*x", ptBins[p], ptBins[p+1]);
			f->SetParameter(0,ptR[p]->GetMaximum()*0.8);
			f->SetParLimits(0,0,ptR[p]->GetMaximum());
			f->SetParameter(1,0.1);
			f->SetParLimits(1,-10,10);
			f->SetParameter(2,0.1);
			f->SetParLimits(1,-10,10);
			ptR[p]->Fit(Form("f%d",p),"Lq","",ptBins[p], ptBins[p+1]);
			ptR[p]->Fit(Form("f%d",p),"Lq","",ptBins[p], ptBins[p+1]);
			f->SetLineColor(kRed);
			f->SetLineWidth(3);
			ptR[p]->Draw("p");
			f->Draw("l same ");
			cptR->SaveAs(Form("plotsFill/ptRptBin%d.pdf",p));
			pa0[p] = f->GetParameter(0);
			pa1[p] = f->GetParameter(1);
			pa2[p] = f->GetParameter(2);
			std::cout<<f->GetParameter(0)<<endl;
			std::cout<<f->GetParameter(1)<<endl;
			std::cout<<f->GetParameter(2)<<endl;
		}
	}

}

void MCDataComparisonFill(TString inputdata="/data/dmeson2015/DataDntuple/nt_20160112_DfinderData_pp_20160111_dPt0tkPt1_D0Dstar3p5p_DCSJSON_v2.root", TString inputmc="/afs/cern.ch/work/w/wangj/public/Dmeson/ntD_20151110_DfinderMC_20151110_EvtMatching_Pythia_D0pt15p0_Pthat15_TuneZ2_5020GeV_GENSIM_75x_1015_20151110_ppGlobaTrackingPPmenuHFlowpuv11_MBseed_twang-Pythia_1107.root", TString outputfile="mytest.root"){
	//inputdata="/data/yjlee/dmeson/2015/trigger/mb.root";
	
	//inputmc="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_20160203_Dfinder_20160201_pp_Pythia8_prompt_D0_dPt0tkPt0p5_pthatweight.root";
	//inputmc="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi_promptNnonprompt/ntD_EvtBase_20160216_Dfinder_20160201_pp_Pythia8_promptNnonprompt_D0_dPt0tkPt0p5_pthatweight.root";
	inputmc="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi_promptNnonprompt/ntD_EvtBase_20160216_Dfinder_20160201_pp_Pythia8_promptNnonprompt_D0_dPt0tkPt0p5_pthatweight_skim_20160224.root";
	//skim
	//inputdata="/data/dmeson2015/DataDntuple/nt_20160112_DfinderData_pp_20160111_dPt0tkPt1_D0Dstar3p5p_DCSJSON_v2.root";
	inputdata="/data/wangj/Data2015/Dntuple/pp/nt_20160112_DfinderData_pp_20160111_dPt0tkPt1_D0Dstar3p5p_DCSJSON_v2_skim_20160224.root";

	TFile* inf = new TFile(inputdata.Data());
	TFile* infMC = new TFile(inputmc.Data());
	
	DoAnalysis(inf, infMC, outputfile, false);
	DoAnalysis(inf, infMC, outputfile, true);
}
	
void overlapTH1(TCanvas* c, TH1D* h1, TH1D* h2, TH1D*h3, TH1D* h4, string xTitle, TH1D* hRatio, int customize){
	c->cd();
	h1->GetXaxis()->SetTitle(xTitle.c_str());
	h1->Sumw2();
	h2->Sumw2();
	h3->Sumw2();
	h4->Sumw2();
	h1->Scale(1/h1->Integral());
	h2->Scale(1/h2->Integral());
	h3->Scale(1/h3->Integral());
	h4->Scale(1/h4->Integral());
//	h1->Scale(1/h1->GetEntries());
//	h2->Scale(1/h2->GetEntries());
//	h3->Scale(1/h3->GetEntries());
//	h4->Scale(1/h4->GetEntries());
	h1->SetMaximum(max(h1->GetMaximum(), max(h2->GetMaximum(), max(h3->GetMaximum(), h4->GetMaximum())))*1.8);
//	h1->SetMaximum(max(h1->GetMaximum(), max(h3->GetMaximum(), h4->GetMaximum()))*1.2);
	h1->SetMinimum(h3->GetMinimum()*1.2);
	h1->SetMarkerColor(2);
	h2->SetMarkerColor(3);
	h3->SetMarkerColor(4);
	h4->SetMarkerColor(kMagenta+3);
	h1->SetLineWidth(3);
	h2->SetLineWidth(3);
	h3->SetLineWidth(3);
	h4->SetLineWidth(3);
	h1->SetLineColor(2);
	h2->SetLineColor(3);
	h3->SetLineColor(4);
	h4->SetLineColor(kMagenta+3);
	if (customize == 1){
		h1->Draw("Hist e");
		h2->Draw("same pe");
		h3->Draw("same pe");
		h4->Draw("same pe");
		TLegend* leg = myLegend(0.5, 0.65, 0.86, 0.86);
  		leg->SetTextFont(42);
  		leg->SetTextSize(0.045);
		leg->AddEntry(h1, "MC gen matched", "l");
		leg->AddEntry(h2, "MC gen matched weighted", "p");
		leg->AddEntry(h3, "MC no gen matched", "p");
		leg->AddEntry(h4, "data", "p");
		leg->Draw();
	}
	else{
    	hRatio = (TH1D*)h3->Clone();
		hRatio->Divide(h2);
		hRatio->GetXaxis()->SetTitle(xTitle.c_str());
		hRatio->GetYaxis()->SetTitle("Data/MC");
		TPad* pad1;
		static int pcount = 0;
        pad1 = new TPad(Form("p%d", pcount), Form("p%d", pcount), 0.01, 0.35, 0.99, 0.99); pcount++;
		pad1->Draw();
		pad1->cd();
		h1->Draw("Hist e");
		h2->Draw("same pe");
		h3->Draw("same pe");
		h4->Draw("same pe");
//		h1->Draw("l");
//		h2->Draw("same l");
//		h3->Draw("same l");
		TLegend* leg = myLegend(0.5, 0.65, 0.86, 0.86);
  		leg->SetTextFont(42);
  		leg->SetTextSize(0.045);
		leg->AddEntry(h1, "MC gen matched", "l");
		leg->AddEntry(h2, "MC sideband sub.", "p");
		leg->AddEntry(h3, "data sideband sub.", "p");
		leg->AddEntry(h4, "data signal region", "p");
		leg->Draw();
		TPad* pad2;
        pad2 = new TPad(Form("p%d", pcount), Form("p%d", pcount), 0.01, 0.01, 0.99, 0.35);
	    c->cd();
		pad2->Draw();
		pad2->cd();
		hRatio->Draw("p");
	}
}

void clean0(TH1D* h){
  for (int i=1;i<=h->GetNbinsX();i++)
    {
      if(h->GetBinContent(i)==0) h->SetBinError(i,1);
    }
}

int main(int argc, char *argv[])
{
  if((argc != 4))
  {
    std::cout << "Wrong number of inputs" << std::endl;
    return 1;
  }

  if(argc == 4)
    MCDataComparisonFill(argv[1], argv[2], argv[3]);
  return 0;
}

void setBranches(TTree* t1, DntupleBranches &Dntuple){
    t1->SetBranchAddress("Dsize" ,&Dntuple.Dsize);
    t1->SetBranchAddress("Dpt" ,Dntuple.Dpt);
    t1->SetBranchAddress("Dmass" ,Dntuple.Dmass);
    t1->SetBranchAddress("Ddtheta" ,Dntuple.Ddtheta);
    t1->SetBranchAddress("Dalpha" ,Dntuple.Dalpha);
    t1->SetBranchAddress("Dchi2cl" ,Dntuple.Dchi2cl);
    t1->SetBranchAddress("DsvpvDistance" ,Dntuple.DsvpvDistance);
    t1->SetBranchAddress("DsvpvDisErr" ,Dntuple.DsvpvDisErr);
    t1->SetBranchAddress("DlxyBS" ,Dntuple.DlxyBS);
    t1->SetBranchAddress("DlxyBSErr" ,Dntuple.DlxyBSErr);
    t1->SetBranchAddress("Dy" ,Dntuple.Dy);
    t1->SetBranchAddress("Dtrk1highPurity" ,Dntuple.Dtrk1highPurity);
    t1->SetBranchAddress("Dtrk2highPurity" ,Dntuple.Dtrk2highPurity);
    t1->SetBranchAddress("Dtrk1Pt" ,Dntuple.Dtrk1Pt);
    t1->SetBranchAddress("Dtrk1PtErr" ,Dntuple.Dtrk1PtErr);
    t1->SetBranchAddress("Dtrk2Pt" ,Dntuple.Dtrk2Pt);
    t1->SetBranchAddress("Dtrk2PtErr" ,Dntuple.Dtrk2PtErr);
    t1->SetBranchAddress("Dtrk1Eta" ,Dntuple.Dtrk1Eta);
    t1->SetBranchAddress("Dtrk2Eta" ,Dntuple.Dtrk2Eta);
    t1->SetBranchAddress("Dtrk1Algo" ,Dntuple.Dtrk1Algo);
    t1->SetBranchAddress("Dtrk2Algo" ,Dntuple.Dtrk2Algo);
    t1->SetBranchAddress("Dtrk1PixelHit" ,Dntuple.Dtrk1PixelHit);
    t1->SetBranchAddress("Dtrk1StripHit" ,Dntuple.Dtrk1StripHit);
    t1->SetBranchAddress("Dtrk2PixelHit" ,Dntuple.Dtrk2PixelHit);
    t1->SetBranchAddress("Dtrk2StripHit" ,Dntuple.Dtrk2StripHit);
    t1->SetBranchAddress("Dtrk1Chi2ndf" ,Dntuple.Dtrk1Chi2ndf);
    t1->SetBranchAddress("Dtrk2Chi2ndf" ,Dntuple.Dtrk2Chi2ndf);
    t1->SetBranchAddress("Dtrk1nStripLayer" ,Dntuple.Dtrk1nStripLayer);
    t1->SetBranchAddress("Dtrk1nPixelLayer" ,Dntuple.Dtrk1nPixelLayer);
    t1->SetBranchAddress("Dtrk2nStripLayer" ,Dntuple.Dtrk2nStripLayer);
    t1->SetBranchAddress("Dtrk2nPixelLayer" ,Dntuple.Dtrk2nPixelLayer);
    //t1->SetBranchAddress("" ,Dntuple.);
    t1->SetBranchAddress("Dtrk1MassHypo" ,Dntuple.Dtrk1MassHypo);
    t1->SetBranchAddress("Dtrk2MassHypo" ,Dntuple.Dtrk2MassHypo);
}
void setGenBranches(TTree* t1, DntupleBranches &Dntuple){
    t1->SetBranchAddress("GisSignal" ,Dntuple.GisSignal);
    t1->SetBranchAddress("Gy" ,Dntuple.Gy);
}
