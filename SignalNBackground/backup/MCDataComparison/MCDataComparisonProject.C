#include "uti.h"
//#include "parameters.h"
using namespace std;

TString weight = "1";
TString seldata;
TString selmc;
TString collisionsystem;

//TString signalRegion = "abs(Dmass-1.8648)<0.04";
//TString sidebandRegion = "abs(Dmass-1.8648)>0.04&&abs(Dmass-1.8648)<0.08";
//float wfactor = 1;
//TString signalRegion = "abs(Dmass-1.8648)<0.06";
//TString sidebandRegion = "abs(Dmass-1.8648)>0.06&&abs(Dmass-1.8648)<0.12";
//float wfactor = 1;
TString signalRegion = "abs(Dmass-1.8648)<0.02";
TString sidebandRegion = "abs(Dmass-1.8648)>0.06&abs(Dmass-1.8648)<0.12";
float wfactor = 1./3.;

enum varType{
	_Dpt,
	_DptWeighted,
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
	{"Dpt", "DptWeighted", 50, 1, 100.,"DptWeighted", "GeV"},
	{"Dmass", "Dmass", 50, 1.7, 2.,"Dmass", "GeV"},
	{"Ddtheta","Ddtheta" ,20, 0., 0.2, "Ddtheta", ""},
//	{"Dalpha","Dalpha" ,20, 0., 0.3, "Dalpha", ""},
	{"Dalpha","Dalpha" ,20, 0., 0.12, "Dalpha", ""},
	{"Dchi2cl","Dchi2cl" ,20, 0., 1., "Dchi2cl", ""},
	{"DsvpvDistance/DsvpvDisErr","DsvpvDistance_DsvpvDisErr" ,20, 0., 20., "DsvpvDistance_DsvpvDisErr", ""},
	{"DlxyBS/DlxyBSErr","DlxyBS_DlxyBSErr" ,20, 0., 1000., "DlxyBS_DlxyBSErr",""}
};

void overlapTH1(TCanvas* c, TH1D* h1, TH1D* h2, TH1D* h3, TH1D* h4, string xTitle, TH1D* hRatio, int customize = -1);

void MCDataComparisonProject(TString inputdata="/data/dmeson2015/DataDntuple/nt_20160112_DfinderData_pp_20160111_dPt0tkPt1_D0Dstar3p5p_DCSJSON_v2.root", TString inputmc="/afs/cern.ch/work/w/wangj/public/Dmeson/ntD_20151110_DfinderMC_20151110_EvtMatching_Pythia_D0pt15p0_Pthat15_TuneZ2_5020GeV_GENSIM_75x_1015_20151110_ppGlobaTrackingPPmenuHFlowpuv11_MBseed_twang-Pythia_1107.root", TString trgselection="((HLT_DmesonPPTrackingGlobal_Dpt15_v1&&Dpt>25&&Dpt<40)||(HLT_DmesonPPTrackingGlobal_Dpt30_v1&&Dpt>40&&Dpt<60)||(HLT_DmesonPPTrackingGlobal_Dpt50_v1&&Dpt>60))",  TString cut="Dy>-1.&&Dy<1.&&(Dtrk1highPurity&&Dtrk2highPurity)&&(DsvpvDistance/DsvpvDisErr)>3.5&&Dchi2cl>0.05&&Dalpha<0.12&&Dtrk1Pt>1.5&&Dtrk2Pt>1.5", TString selmcgen="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))", int isMC=0, Double_t luminosity=26., int doweight=0, TString collsyst="PbPb", TString outputfile="mytest.root")
{

	//inputdata="/data/yjlee/dmeson/2015/trigger/mb.root";
	
	//inputmc="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_20160203_Dfinder_20160201_pp_Pythia8_prompt_D0_dPt0tkPt0p5_pthatweight.root";
	//inputmc="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi_promptNnonprompt/ntD_EvtBase_20160216_Dfinder_20160201_pp_Pythia8_promptNnonprompt_D0_dPt0tkPt0p5_pthatweight.root";
	inputmc="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi_promptNnonprompt/ntD_EvtBase_20160216_Dfinder_20160201_pp_Pythia8_promptNnonprompt_D0_dPt0tkPt0p5_pthatweight_skim_20160224.root";
	//skim
	//inputdata="/data/dmeson2015/DataDntuple/nt_20160112_DfinderData_pp_20160111_dPt0tkPt1_D0Dstar3p5p_DCSJSON_v2.root";
	inputdata="/data/wangj/Data2015/Dntuple/pp/nt_20160112_DfinderData_pp_20160111_dPt0tkPt1_D0Dstar3p5p_DCSJSON_v2_skim_20160224.root";
	
	trgselection="((HLT_DmesonPPTrackingGlobal_Dpt15_v1&&Dpt>15&&Dpt<40)||(HLT_DmesonPPTrackingGlobal_Dpt30_v1&&Dpt>40&&Dpt<60)||(HLT_DmesonPPTrackingGlobal_Dpt50_v1&&Dpt>60))";
	//cut="Dy>-1.&&Dy<1.&&(Dtrk1highPurity&&Dtrk2highPurity)&&(DsvpvDistance/DsvpvDisErr)>3.5&&Dchi2cl>0.05&&Dalpha<0.12&&Dtrk1Pt>1.5&&Dtrk2Pt>1.5";
//	cut="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>1.5&&Dchi2cl>0.05&&Dalpha<0.12&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&Dtrk1Algo>3&&Dtrk1Algo<8&&Dtrk2Algo>3&&Dtrk2Algo<8&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)";
//	cut="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>1.5&&Dchi2cl>0.05&&Dalpha<0.12&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&Dtrk1Algo>3&&Dtrk1Algo<8&&Dtrk2Algo>3&&Dtrk2Algo<8&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)&&(Dpt)>15";
	cut="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>1.5&&Dchi2cl>0.05&&Dalpha<0.12&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&Dtrk1Algo>3&&Dtrk1Algo<8&&Dtrk2Algo>3&&Dtrk2Algo<8&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)&&(Dpt)>15&&(Dpt)<40";
//	cut="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>1.5&&Dchi2cl>0.05&&Dalpha<0.12&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&Dtrk1Algo>3&&Dtrk1Algo<8&&Dtrk2Algo>3&&Dtrk2Algo<8&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)&&(Dpt)>30&&(Dpt)<50";
	selmcgen="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))";
	isMC=0;
	luminosity=26.31;
	doweight=1;
	collsyst="PP";
	outputfile="hPtSpectrumDzeroPP.root";

	collisionsystem=collsyst;
	seldata = Form("%s&&%s",trgselection.Data(),cut.Data());
	//seldata = Form("%s",cut.Data());
	selmc = Form("%s",cut.Data());
	
	gStyle->SetTextSize(0.05);
	gStyle->SetTextFont(42);
	gStyle->SetPadRightMargin(0.043);
	gStyle->SetPadLeftMargin(0.18);
	gStyle->SetPadTopMargin(0.1);
	gStyle->SetPadBottomMargin(0.145);
	gStyle->SetTitleX(.0f);

	if(!doweight) weight="1";
	TFile* inf = new TFile(inputdata.Data());
	TFile* infMC = new TFile(inputmc.Data());
	
	TTree* nt = (TTree*) inf->Get("ntDkpi");
	TTree* HltTree = (TTree*) inf->Get("ntHlt");
	HltTree->AddFriend(nt);
	nt->AddFriend(HltTree);
	
	TTree* ntMC = (TTree*)infMC->Get("ntDkpi");
	TTree* ntGen = (TTree*)infMC->Get("ntGen");
	TTree* ntHi = (TTree*)infMC->Get("ntHi");
	ntMC->AddFriend("ntHi");
	//TTree* MCHltTree;
	//if (collisionsystem=="PP") MCHltTree= (TTree*)infMC->Get("ntHlt");
	//else MCHltTree= (TTree*)infMC->Get("HltTree");
	//MCHltTree= (TTree*)infMC->Get("ntHlt");
	//ntGen->AddFriend(ntMC);
	//MCHltTree->AddFriend(ntMC);
	
	TCanvas *c[_varSize];
	TH1D *h1[_varSize];
	TH1D *h2[_varSize];
	TH1D *h3[_varSize];
	TH1D *h4[_varSize];
	TH1D *h11[_varSize];
	TH1D *h12[_varSize];
	TH1D *h13[_varSize];
	TH1D *h14[_varSize];
	TH1D *h21[_varSize];
	TH1D *h22[_varSize];
	TH1D *h23[_varSize];
	TH1D *hRatio[_varSize];
	TH1D *ptR =  new TH1D((myVars[_Dpt].title+"Ratio").c_str(), myVars[_Dpt].title.c_str(), myVars[_Dpt].nBin, myVars[_Dpt].xMin, myVars[_Dpt].xMax);
	int nentries = 1000000000;
//	nentries = 2000000;
	float pa0 = 1;	
	float pa1 = 0;	
	float pa2 = 0;	
	TString ptWeight = Form("%f+%f*Dpt+%f*Dpt*Dpt", pa0, pa1, pa2);
	for (int i = 0 ; i < _varSize; i++){
		printf("processing %s\n", myVars[i].var.c_str());
		ptWeight = Form("%f+%f*Dpt+%f*Dpt*Dpt", pa0, pa1, pa2);
		cout<<ptWeight<<endl;
//		if(i > _Dpt) continue;
		c[i] =  new TCanvas(("c"+myVars[i].var).c_str(),"",600,600);
		h1[i] =  new TH1D((myVars[i].title+"1").c_str(), myVars[i].title.c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
		h2[i] =  new TH1D((myVars[i].title+"2").c_str(), myVars[i].title.c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
		h3[i] =  new TH1D((myVars[i].title+"3").c_str(), myVars[i].title.c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
		h4[i] =  new TH1D((myVars[i].title+"4").c_str(), myVars[i].title.c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
		h11[i] = new TH1D((myVars[i].title+"11").c_str(), myVars[i].title.c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
		h12[i] = new TH1D((myVars[i].title+"12").c_str(), myVars[i].title.c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
		h13[i] = new TH1D((myVars[i].title+"13").c_str(), myVars[i].title.c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
		h14[i] = new TH1D((myVars[i].title+"14").c_str(), myVars[i].title.c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
		h21[i] = new TH1D((myVars[i].title+"21").c_str(), myVars[i].title.c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
		h22[i] = new TH1D((myVars[i].title+"22").c_str(), myVars[i].title.c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
		h23[i] = new TH1D((myVars[i].title+"23").c_str(), myVars[i].title.c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
		hRatio[i] = new TH1D((myVars[i].title+"_ratio").c_str(), (myVars[i].title+"_ratio").c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
	
		ntMC->Project((myVars[i].title+"1").c_str(), myVars[i].var.c_str(), TCut(weight)*TCut(ptWeight)*(TCut((selmc+"&&"+signalRegion).Data())), "", nentries);
		ntMC->Project((myVars[i].title+"2").c_str(), myVars[i].var.c_str(), TCut(weight)*TCut(ptWeight)*(TCut((selmc+"&&"+sidebandRegion).Data())), "", nentries);
		ntMC->Project((myVars[i].title+"4").c_str(), myVars[i].var.c_str(), TCut(weight)*TCut(ptWeight)*(TCut((selmc+"&&"+signalRegion).Data())&&"(Dgen==23333)"), "", nentries);

		ntMC->Project((myVars[i].title+"11").c_str(), myVars[i].var.c_str(), TCut("pthatweight")*TCut(ptWeight)*TCut(weight)*(TCut((selmc+"&&"+signalRegion).Data())), "", nentries);
		ntMC->Project((myVars[i].title+"12").c_str(), myVars[i].var.c_str(), TCut("pthatweight")*TCut(ptWeight)*TCut(weight)*(TCut((selmc+"&&"+sidebandRegion).Data())), "", nentries);
		ntMC->Project((myVars[i].title+"14").c_str(), myVars[i].var.c_str(), TCut("pthatweight")*TCut(ptWeight)*TCut(weight)*(TCut((selmc+"&&"+signalRegion).Data())&&"(Dgen==23333)"), "", nentries);

		nt->  Project((myVars[i].title+"21").c_str(), myVars[i].var.c_str(), TCut(weight)*(TCut((seldata+"&&"+signalRegion).Data())), "", nentries);
		nt->  Project((myVars[i].title+"22").c_str(), myVars[i].var.c_str(), TCut(weight)*(TCut((seldata+"&&"+sidebandRegion).Data())), "", nentries);

		h3[i] = (TH1D*)h1[i]->Clone();
		h3[i]->Add(h2[i],-wfactor);

		h13[i] = (TH1D*)h11[i]->Clone();
		h13[i]->Add(h12[i],-wfactor);

		h23[i] = (TH1D*)h21[i]->Clone();
		h23[i]->Add(h22[i],-wfactor);

		if(i == _Dpt){
		    h23[i]->Sumw2();
		    h13[i]->Sumw2();
		    h23[i]->Scale(1/h23[i]->Integral());
		    h13[i]->Scale(1/h13[i]->Integral());
			ptR = (TH1D*)h23[i]->Clone();
			ptR->Divide(h13[i]);
			TCanvas* cptR =  new TCanvas("cptR","",600,600);
  			TF1* f = new TF1(Form("f%d",i),"[0]+[1]*x+[2]*x*x", 15, 40);
			f->SetParameter(0,ptR->GetMaximum()*0.8);
			f->SetParLimits(0,0,ptR->GetMaximum());
			f->SetParameter(1,0.1);
			f->SetParLimits(1,-10,10);
			f->SetParameter(2,0.1);
			f->SetParLimits(1,-10,10);
			ptR->Fit(Form("f%d",i),"Lq","",15, 40);
			ptR->Fit(Form("f%d",i),"Lq","",15, 40);
			f->SetLineColor(kRed);
			f->SetLineWidth(3);
			ptR->Draw("p");
			f->Draw("l same ");
			cptR->SaveAs("plotsProject/ptR.pdf");
			pa0 = f->GetParameter(0);
			pa1 = f->GetParameter(1);
			pa2 = f->GetParameter(2);
			std::cout<<f->GetParameter(0)<<endl;
			std::cout<<f->GetParameter(1)<<endl;
			std::cout<<f->GetParameter(2)<<endl;
		}
		
		overlapTH1(c[i], h14[i], h13[i], h23[i], h21[i], myVars[i].xtitle, hRatio[i]);
		c[i]->SaveAs(("plotsProject/"+myVars[i].plotName+".pdf").c_str());
	}
	TH1D *hMCMass = new TH1D("MCDmass", "MCDmass", 100, 1.7, 2);
	TH1D *hMCMassGM = new TH1D("MCDmassGM", "MCDmassGM", 100, 1.7, 2);
	TH1D *hMCMassGMW = new TH1D("MCDmassGMW", "MCDmassGMW", 100, 1.7, 2);
	TH1D *hDataMass = new TH1D("DataDmass", "DataDmass", 100, 1.7, 2);
	TH1D *hMassRatio = new TH1D("DmassRatio", "DmassRatio", 100, 1.7, 2);
	TH1D *hempty = new TH1D("empty", "empty", 100, 1.7, 2);
    ntMC->Project("MCDmassGM", "Dmass", TCut(weight)*(TCut( (selmc) .Data())&&"(Dgen==23333)"), "", nentries);
    ntMC->Project("MCDmassGMW", "Dmass", TCut("pthatweight")*TCut(weight)*(TCut( (selmc) .Data())&&"(Dgen==23333)"), "", nentries);
    ntMC->Project("MCDmass", "Dmass", TCut(weight)*(TCut( (selmc) .Data())), "", nentries);
    nt->  Project("DataDmass", "Dmass", TCut(weight)*(TCut( (seldata).Data())), "", nentries);
    TCanvas* cMass =  new TCanvas("cMass","",600,600);
    overlapTH1(cMass, hMCMassGM, hMCMassGMW, hMCMass, hDataMass, "Dmass", hMassRatio, 1);
	cMass->SaveAs("plotsProject/mass.pdf");

	
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
  if((argc != 11))
  {
    std::cout << "Wrong number of inputs" << std::endl;
    return 1;
  }

  if(argc == 11)
    MCDataComparisonProject(argv[1], argv[2], argv[3], argv[4], argv[5], atoi(argv[6]), atof(argv[7]), atoi(argv[8]),argv[9],argv[10]);
  return 0;
}
