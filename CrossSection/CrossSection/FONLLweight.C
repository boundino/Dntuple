#include "uti.h"
#include "parameters.h"

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

TString weightfunctiongen = "1";
TString weightfunctionreco = "1";
TString selmc;

void FONLLweight(int isPbPb=1,TString inputmc="/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_PbPb_Pythia8_prompt_D0_dPt1tkPt1_pthatweight.root", int minfit=2,int maxfit=100,TString pthat="pthatall")
{
  TString label;
  TString selmcgen="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))";
  
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);
 
  TFile* infMC = new TFile(inputmc.Data());
  TTree* ntGen = (TTree*)infMC->Get("ntGen");
  
  TH1D* hPtGenFONLL = new TH1D("hPtGenFONLL","",nBinsReweight,ptBinsReweight);
  ntGen->Project("hPtGenFONLL","Gpt",(TCut(selmcgen.Data())));
  divideBinWidth(hPtGenFONLL);
    
  TString fonll="/afs/cern.ch/work/g/ginnocen/public/output_pp_d0meson_5TeV_y1.root";
  TFile* filePPReference = new TFile(fonll.Data());  
  TGraphAsymmErrors* gaeBplusReference = (TGraphAsymmErrors*)filePPReference->Get("gaeSigmaDzero");

  TH1D* hFONLL = new TH1D("hFONLL","",nBinsReweight,ptBinsReweight);
  double x,y;
  for(int i=0;i<nBinsReweight;i++){
    gaeBplusReference->GetPoint(i,x,y);
    hFONLL->SetBinContent(i+1,y);
  }
  TH1D* hFONLLOverPt=(TH1D*)hFONLL->Clone("hFONLLOverPt");
  TH1D* hFONLLOverPtWeight=(TH1D*)hFONLL->Clone("hFONLLOverPtWeight");

  hFONLLOverPt->Divide(hPtGenFONLL);
  
  TString myweightfunctiongen,myweightfunctionreco;
  if(isPbPb==1){
    TF1 *myfit = new TF1("myfit","pow(10,[0]*x+[1]+x*x*[2])+pow(10,[3]*x+[4]+x*x*[5])+[6]+[7]*x+[8]*x*x", 2, 100);
    hFONLLOverPt->Fit("myfit","","",minfit,maxfit);
    double par0=myfit->GetParameter(0);
    double par1=myfit->GetParameter(1);
    double par2=myfit->GetParameter(2);
    double par3=myfit->GetParameter(3);
    double par4=myfit->GetParameter(4);
    double par5=myfit->GetParameter(5);
    double par6=myfit->GetParameter(6);
    double par7=myfit->GetParameter(7);
    double par8=myfit->GetParameter(8);

   myweightfunctiongen=Form("pow(10,%f*Gpt+%f+Gpt*Gpt*%f)+pow(10,%f*Gpt+%f+Gpt*Gpt*%f) +%f+%f*Gpt+%f*Gpt*Gpt",par0,par1,par2,par3,par4,par5,par6,par7,par8);
   myweightfunctionreco=Form("pow(10,%f*Dgenpt+%f+Dgenpt*Dgenpt*%f)+pow(10,%f*Dgenpt+%f+Dgenpt*Dgenpt*%f) +%f+%f*Dgenpt+%f*Dgenpt*Dgenpt",par0,par1,par2,par3,par4,par5,par6,par7,par8);
   label="PbPb"+pthat;
  }
  else {
  
  TF1 *myfit = new TF1("myfit","pow(10,[0]*x+[1]+x*x*[2])+pow(10,[3]*x+[4]+x*x*[5])", 2, 100);
  hFONLLOverPt->Fit("myfit","","",minfit,maxfit);
  double par0=myfit->GetParameter(0);
  double par1=myfit->GetParameter(1);
  double par2=myfit->GetParameter(2);
  double par3=myfit->GetParameter(3);
  double par4=myfit->GetParameter(4);
  double par5=myfit->GetParameter(5);

  myweightfunctiongen=Form("pow(10,%f*Gpt+%f+Gpt*Gpt*%f)+pow(10,%f*Gpt+%f+Gpt*Gpt*%f)",par0,par1,par2,par3,par4,par5);
  myweightfunctionreco=Form("pow(10,%f*Dgenpt+%f+Dgenpt*Dgenpt*%f)+pow(10,%f*Dgenpt+%f+Dgenpt*Dgenpt*%f)",par0,par1,par2,par3,par4,par5);
  label="PP"+pthat;

  }
  
  std::cout<<myweightfunctiongen<<std::endl;
  std::cout<<myweightfunctionreco<<std::endl;
  std::cout<<"fit function parameters="<<weightfunctiongen<<std::endl;

  TCanvas*canvasPtReweight=new TCanvas("canvasPtReweight","canvasPtReweight",1000.,500.); 
  canvasPtReweight->Divide(3,1);
  canvasPtReweight->cd(1);
  gPad->SetLogy();
  hPtGenFONLL->SetXTitle("Gen p_{T}");
  hPtGenFONLL->SetYTitle("#entries");
  hPtGenFONLL->SetMinimum(1e-4);  
  hPtGenFONLL->SetMaximum(1e11);  
  hPtGenFONLL->GetYaxis()->SetTitleOffset(1.4);
  hPtGenFONLL->Draw();
  canvasPtReweight->cd(2);
  gPad->SetLogy();
  hFONLL->SetXTitle("p_{T}");
  hFONLL->SetYTitle("FONLL, #entries");
  hFONLL->SetMinimum(1e-4);  
  hFONLL->SetMaximum(1e11);  
  hFONLL->GetYaxis()->SetTitleOffset(1.4);
  hFONLL->Draw();
  canvasPtReweight->cd(3);
  gPad->SetLogy();
  hFONLLOverPt->SetXTitle("Gen p_{T}");
  hFONLLOverPt->SetYTitle("FONLL/PYTHIA ");
  hFONLLOverPt->SetMinimum(1e-4);  
  hFONLLOverPt->SetMaximum(1e11);  
  hFONLLOverPt->GetYaxis()->SetTitleOffset(1.4);
  hFONLLOverPt->Draw();
  canvasPtReweight->SaveAs(Form("canvasPtReweight%s.pdf",Form(label.Data())));

}

int main(int argc, char *argv[])
{
  if((argc !=6))
  {
    std::cout << "Wrong number of inputs" << std::endl;
    return 1;
  }
  
  if(argc == 6)
    FONLLweight(atoi(argv[1]),argv[2], atoi(argv[3]),atoi(argv[4]),argv[5]);
  return 0;
}

