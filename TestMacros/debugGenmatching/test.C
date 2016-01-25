#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TString.h>
Double_t minhisto=1.7;
Double_t maxhisto=2.0;
Double_t nbinsmasshisto=60;

TString date = "0124";//0118,0124
Float_t pthat = 10;
void test()
{
  TFile* inf = new TFile(Form("/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_2016%s_Dfinder_20151229_pp_Pythia8_prompt_D0pt%.0fp0_Pthat%.0f_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20151212_dPt1tkPt1_D0Ds.root",date.Data(),pthat,pthat));
  TTree* ntMC = (TTree*)inf->Get("ntDkpi");
  TH1D* hmassReco = new TH1D("hmassReco",";D mass (GeV/c^{2});Candidates",nbinsmasshisto,minhisto,maxhisto);
  TH1D* hmassRecoMatched = new TH1D("hmassRecoMatched","",nbinsmasshisto,minhisto,maxhisto);
  TH1D* hmassRecoMatchedAll = new TH1D("hmassRecoMatchedAll","",nbinsmasshisto,minhisto,maxhisto);
  hmassRecoMatched->SetLineColor(kRed);
  hmassRecoMatchedAll->SetLineColor(kBlue);
  TCanvas* c = new TCanvas("c","",600,600);
  ntMC->Draw("Dmass>>hmassReco",Form("Dpt>%f",pthat));
  ntMC->Draw("Dmass>>hmassRecoMatched",Form("Dpt>%f&&(Dgen==23333)",pthat),"same");
  ntMC->Draw("Dmass>>hmassRecoMatchedAll",Form("Dpt>%f&&(Dgen==23333||Dgen==23344)",pthat),"same");
  c->SaveAs(Form("plots/cMatching_Pthat%.0f_%s.pdf",pthat,date.Data()));
}
