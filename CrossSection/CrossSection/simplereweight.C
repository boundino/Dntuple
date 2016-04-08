#include "uti.h"

Double_t setparam0=100.;
Double_t setparam1=1.865;
Double_t setparam2=0.03;
Double_t setparam10=0.005;
Double_t setparam8=0.1;
Double_t setparam9=0.1;
Double_t fixparam1=1.865;
Double_t minhisto=	1.7;
Double_t maxhisto=2.0;
Double_t nbinsmasshisto=60;
Double_t binwidthmass=(maxhisto-minhisto)/nbinsmasshisto;

TString cut_recoonly="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0";
TString selmcgen="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))";
TString selmcgenacceptance="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))&&abs(Gtk1eta)<2.0&&abs(Gtk2eta)<2.0&&Gtk1pt>1.0&&Gtk2pt>1.0";
TString selmc="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>1.5&&Dchi2cl>0.05&&Dalpha<0.12";

void test(int MCsample=0, bool doreweighting=true){

  TString weight="1";
 
  TString inputFONLL="/afs/cern.ch/work/g/ginnocen/public/output_pp_d0meson_5TeV_y1.root";

  TString inputmc="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_prompt_D0_dPt0tkPt0p5_pthatweight.root";
  TString outputfile;
  
  TFile* infMC = new TFile(inputmc.Data());
  TTree* ntMC = (TTree*)infMC->Get("ntDkpi");
  TTree* ntGen = (TTree*)infMC->Get("ntGen");
  TTree* ntHi = (TTree*)infMC->Get("ntHi");
  ntMC->AddFriend(ntGen);
  ntMC->AddFriend(ntHi);

  TH1D* hPtGen = new TH1D("hPtGen","",nBins,ptBins);
    
  ntMC->Project("hPtGen","Gpt",TCut(weight)*(TCut(selmcgen.Data())));
  divideBinWidth(hPtGen);

  TFile* filePPReference = new TFile(inputFONLL.Data());  
  TGraphAsymmErrors* gaeBplusReference = (TGraphAsymmErrors*)filePPReference->Get("gaeSigmaDzero");

  TH1D* hFONLL = new TH1D("hFONLL","",nBins,ptBins);
  double x,y;
  for(int i=0;i<nBins;i++){
    gaeBplusReference->GetPoint(i,x,y);
    hFONLL->SetBinContent(i+1,y);
  }
  TH1D* hFONLLOverPt=(TH1D*)hFONLL->Clone("hFONLLOverPt");
  TH1D* hFONLLOverPtWeight=(TH1D*)hFONLL->Clone("hFONLLOverPtWeight");

  hFONLLOverPt->Divide(hPtGen);
  
  
  TF1 *myfit = new TF1("myfit","pow(10,[0]*x+[1]+x*x*[2])+pow(10,[3]*x+[4]+x*x*[5])", 2, 100);
  hFONLLOverPt->Fit("myfit","","",2,100);
  double par0=myfit->GetParameter(0);
  double par1=myfit->GetParameter(1);
  double par2=myfit->GetParameter(2);
  double par3=myfit->GetParameter(3);
  double par4=myfit->GetParameter(4);
  double par5=myfit->GetParameter(5);

  
  TString weightfunction=Form("pow(10,%f*Gpt+%f+Gpt*Gpt*%f)+pow(10,%f*Gpt+%f+Gpt*Gpt*%f)",par0,par1,par2,par3,par4,par5);
  cout<<weightfunction<<endl;

  TCanvas*canvas=new TCanvas("canvas","canvas",1000.,400);
  
  canvas->Divide(3,1);
  canvas->cd(1);
  gPad->SetLogy();
  hPtGen->SetXTitle("Gen p_{T}");
  hPtGen->SetYTitle("#entries");
  hPtGen->SetMinimum(0.01);  
  hPtGen->Draw();
  canvas->cd(2);
  gPad->SetLogy();
  hFONLL->SetXTitle("p_{T}");
  hFONLL->SetYTitle("FONLL, #entries");
  hFONLL->Draw("p");
  canvas->cd(3);
  gPad->SetLogy();
  hFONLLOverPt->SetXTitle("Gen p_{T}");
  hFONLLOverPt->SetYTitle("FONLL/PYTHIA ");
  hFONLLOverPt->Draw();
  canvas->SaveAs(Form("MCreweighting_%d.pdf",MCsample));  
}

void simplereweight(int isdoweight=3){

  TString myweight;
  TString myweightreco;
  if (isdoweight==0){
    myweight="(pow(10,-0.168499*Gpt+3.872855+Gpt*Gpt*0.000556)+pow(10,-0.068599*Gpt+2.512265+Gpt*Gpt*0.000331))";
    myweightreco="(pow(10,-0.168499*Dgenpt+3.872855+Dgenpt*Dgenpt*0.000556)+pow(10,-0.068599*Dgenpt+2.512265+Dgenpt*Dgenpt*0.000331))";
  }
if (isdoweight==1){
    myweight="pthatweight";
    myweightreco="pthatweight";
  }
if (isdoweight==2){
    myweight="1";
    myweightreco="1";
  }
if (isdoweight==3){
    myweight="pthatweight*(pow(10,0.095118*Gpt+-1.133104+Gpt*Gpt*-0.000788)+pow(10,4.273087*Gpt+-9.873373+Gpt*Gpt*-0.474733))";
    myweightreco="pthatweight*(pow(10,0.095118*Dgenpt+-1.133104+Dgenpt*Dgenpt*-0.000788)+pow(10,4.273087*Dgenpt+-9.873373+Dgenpt*Dgenpt*-0.474733))";
 }

  
  TString inputmc="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_prompt_D0_dPt0tkPt0p5_pthatweight.root";
  
  TFile* infMC = new TFile(inputmc.Data());
  TTree* ntMC = (TTree*)infMC->Get("ntDkpi");
  TTree* ntGen = (TTree*)infMC->Get("ntGen");
  TTree* ntHi = (TTree*)infMC->Get("ntHi");
  ntMC->AddFriend(ntGen);
  ntMC->AddFriend(ntHi);

  ntGen->AddFriend(ntHi);

  TH1D* myhPtMC = new TH1D("myhPtMC","",nBins,ptBins);
  TH1D* myhPtGen = new TH1D("myhPtGen","",nBins,ptBins);
  TH1D* myhPtMCrecoonly = new TH1D("myhPtMCrecoonly","",nBins,ptBins);
  TH1D* myhPtGenAcc = new TH1D("myhPtGenAcc","",nBins,ptBins);

  ntMC->Project("myhPtMCrecoonly","Dpt",TCut(myweightreco)*(TCut(cut_recoonly.Data())&&"(Dgen==23333)"));
  divideBinWidth(myhPtMCrecoonly);
  ntMC->Project("myhPtMC","Dpt",TCut(myweightreco)*(TCut(selmc.Data())&&"(Dgen==23333)"));
  divideBinWidth(myhPtMC);
  ntGen->Project("myhPtGen","Gpt",TCut(myweight)*(TCut(selmcgen.Data())));
  divideBinWidth(myhPtGen);
  ntGen->Project("myhPtGenAcc","Gpt",TCut(myweight)*(TCut(selmcgenacceptance.Data())));
  divideBinWidth(myhPtGenAcc);


  myhPtMC->Sumw2();
  TH1D* hEff = (TH1D*)myhPtMC->Clone("hEff");
  hEff->Divide(myhPtGen);
  TH1D* hEffReco = (TH1D*)myhPtMCrecoonly->Clone("hEffReco");
  hEffReco->Sumw2();
  hEffReco->Divide(myhPtGen);

  TH1D* hEffAcc = (TH1D*)myhPtGenAcc->Clone("hEffAcc");
  hEffAcc->Sumw2();
  hEffAcc->Divide(hEffAcc,myhPtGen,1,1,"b");
  
  TH1D* hEffSelection = (TH1D*)myhPtMC->Clone("hEffSelection");
  hEffSelection->Sumw2();
  hEffSelection->Divide(hEffSelection,myhPtMCrecoonly,1,1,"b");

  TCanvas*canvas=new TCanvas("canvas","canvas",1000.,400);
  
  canvas->Divide(3,1);
  canvas->cd(1);
  gPad->SetLogy();
  myhPtGen->Draw();
  canvas->cd(2);
  gPad->SetLogy();
  myhPtMC->Draw();
  canvas->cd(3);
  hEff->Draw();
  
  TString outputname;
  if (isdoweight==0) outputname="effreweightpt.root";
  if (isdoweight==1) outputname="effreweightpthat.root";
  if (isdoweight==2) outputname="effnoreweight.root";
  if (isdoweight==3) outputname="effpthatANDFONLL.root";
  
  TFile*f=new TFile(outputname.Data(),"recreate");
  f->cd();
  hEff->Write();
  hEffReco->Write();
  hEffSelection->Write();
  hEffAcc->Write();
}
