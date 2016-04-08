#include <TTree.h>
#include <TH1D.h>
#include <TH2F.h>
#include <TFile.h>
#include <TString.h>
#include <TCut.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TLegend.h>

TString weight = "1";
TString seldata;
TString selmc;
TString collisionsystem;
TString mass="(Dmass>1.85&&Dmass<1.88)";
TString cut="Dpt>40&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>1.5&&Dchi2cl>0.05&&Dalpha<0.12&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&(Dtrk1PixelHit+Dtrk1StripHit)>=11";
//TString cut="Dpt>80&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>8.5&&Dtrk2Pt>8.5&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05&&Dalpha<0.12&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0";
TString inputData="/data/dmeson2015/DataDntuple/nt_skimmed_DfinderData_PbPb_20160126_dPt0tkPt2p5_D0Dstar3p5p_FINALJSON_v6_partialstats_v2.root";
TString trgselectionData="HLT_HIDmesonHITrackingGlobal_Dpt60_v1";
TString inputMC="/data/wangj/MC2015/Dntuple/PbPb/ntD_PbPb_Dzero_kpi/ntD_EvtBase_20160127_Dfinder_20151229_Pythia8_prompt_D0_pthatweight.root";
TString trgselectionMC="1";

void TrackingStudiesMCData(int variable=3, int isMC=1){

TString va,title,titleplot;
int nBin,BinL,BinH;
double minplot,maxplot;
bool logx,logy;


  if(variable==0){
    va="Dtrk1PtErr/Dtrk1Pt";
    title="Dtrk1PtErr/Dtrk1Pt";
    titleplot ="Dtr1pterr";
    nBin=200;
    BinL=0;
    BinH=2;
    minplot=0.00001;
    maxplot=1;
    logx=true;
    logy=true;
  }

  if(variable==1){
    va="Dtrk2PtErr/Dtrk2Pt";
    title="Dtrk2PtErr/Dtrk2Pt";
    titleplot ="Dtr2pterr";
    nBin=200;
    BinL=0;
    BinH=2;
    minplot=0.00001;
    maxplot=1;
    logx=true;
    logy=true;
  }

  if(variable==2){
    va="(Dtrk1PixelHit+Dtrk1StripHit)";
    title="Dtrk1PixelHit+Dtrk1StripHit";
    titleplot ="Nhits";
    nBin=40;
    BinL=0;
    BinH=40;
    minplot=0.00001;
    maxplot=1;
    logx=true;
    logy=true;
  }

  if(variable==3){
    va="(Dtrk1Algo)";
    title="Dtrk1Algo";
    titleplot ="Dtrk1Algo";
    nBin=20;
    BinL=0;
    BinH=20;
    minplot=0.00001;
    maxplot=1;
    logx=false;
    logy=true;
  }

  if(variable==4){
    va="(Dtrk2Algo)";
    title="Dtrk2Algo";
    titleplot ="Dtrk2Algo";
    nBin=20;
    BinL=0;
    BinH=20;
    minplot=0.00001;
    maxplot=1;
    logx=false;
    logy=true;
  }

  if(variable==5){
    va="Dtrk1Eta";
    title="Dtrk1Eta";
    titleplot ="Dtrk1Eta";
    nBin=100;
    BinL=-3;
    BinH=3;
    minplot=0.00001;
    maxplot=1;
    logx=false;
    logy=true;
  }

  if(variable==6){
    va="Dtrk2Eta";
    title="Dtrk2Eta";
    titleplot ="Dtrk2Eta";
    nBin=100;
    BinL=-3;
    BinH=3;
    minplot=0.00001;
    maxplot=1;
    logx=false;
    logy=true;
  }

  if(variable==7){
    va="Dtrk1nStripLayer+Dtrk1nPixelLayer";
    title="Dtrk1nStripLayer+Dtrk1nPixelLayer";
    titleplot ="nlayerstk1";
    nBin=20;
    BinL=0;
    BinH=20;
    minplot=0.00001;
    maxplot=1;
    logx=false;
    logy=true;
  }

  if(variable==8){
    va="Dtrk2nStripLayer+Dtrk2nPixelLayer";
    title="Dtrk2nStripLayer+Dtrk2nPixelLayer";
    titleplot ="nlayerstk2";
    nBin=20;
    BinL=0;
    BinH=20;
    minplot=0.00001;
    maxplot=1;
    logx=false;
    logy=true;
  }


  TFile* infData = new TFile(inputData.Data());
  TTree* ntData = (TTree*)infData->Get("ntDkpi");
  TTree* nthiData = (TTree*)infData->Get("ntHi");
  TTree* HltTree= (TTree*) infData->Get("ntHlt");
  ntData->AddFriend(nthiData);
  ntData->AddFriend(HltTree);
  
  TFile* infMC = new TFile(inputMC.Data());
  TTree* ntMC = (TTree*)infMC->Get("ntDkpi");
  TTree* nthiMC = (TTree*)infMC->Get("ntHi");
  TTree* ntGen= (TTree*) infMC->Get("ntGen");
  ntMC->AddFriend(nthiMC);
  ntMC->AddFriend(ntGen);
  
  seldata = Form("%s&&%s&&%s",trgselectionData.Data(),cut.Data(),mass.Data());
  selmc = Form("%s&&%s&&%s&&Dgen==23333",trgselectionMC.Data(),cut.Data(),mass.Data());

  TH1D *hData = new TH1D("hData","",nBin,BinL,BinH);
  hData->Sumw2();
  ntData->Project("hData",va.Data(),TCut(seldata));
  hData->Scale(1./hData->Integral(1,nBin));

  TH1D *hMC = new TH1D("hMC","",nBin,BinL,BinH);
  hMC->Sumw2();
  ntMC->Project("hMC",va.Data(),TCut(weight)*TCut(selmc));
  hMC->Scale(1./hMC->Integral(1,nBin));

  TH2F* hempty=new TH2F("hempty","",nBin,BinL,BinH,10,0.00000001,10);  
  hempty->GetXaxis()->CenterTitle();
  hempty->GetYaxis()->CenterTitle();
  hempty->GetYaxis()->SetTitle("Entries");
  hempty->GetXaxis()->SetTitle(title.Data());
  hempty->GetXaxis()->SetTitleOffset(1.0);
  hempty->GetYaxis()->SetTitleOffset(1.2);
  hempty->GetXaxis()->SetTitleSize(0.045);
  hempty->GetYaxis()->SetTitleSize(0.045);
  hempty->GetXaxis()->SetTitleFont(42);
  hempty->GetYaxis()->SetTitleFont(42);
  hempty->GetXaxis()->SetLabelFont(42);
  hempty->GetYaxis()->SetLabelFont(42);
  hempty->GetXaxis()->SetLabelSize(0.035);
  hempty->GetYaxis()->SetLabelSize(0.035);  

  TCanvas *canvas = new TCanvas("canvas","",600,600);
  canvas->cd();
  if (logx)gPad->SetLogx();
  if (logy)gPad->SetLogy();
  hempty->Draw();
  hData->SetLineWidth(2);
  hData->SetLineColor(1);
  hData->SetMarkerColor(1);
  hData->Draw("same");
  hMC->SetLineColor(2);
  hMC->SetMarkerColor(2);
  hMC->Draw("same");
  canvas->SaveAs(Form("canvas%s.pdf",titleplot.Data()));

}
