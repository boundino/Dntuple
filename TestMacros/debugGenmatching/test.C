#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TString.h>
Double_t minhisto=1.7;
Double_t maxhisto=2.0;
Double_t nbinsmasshisto=60;

Float_t pthat = 5;
Float_t cutdptmin = 0.;
Float_t cutdptmax = 100.;
void test()
{
  TFile* inf = new TFile(Form("/afs/cern.ch/work/w/wangj/public/RunII/Dmeson/ntD_EvtBase_20160127_Dfinder_20151229_Pythia8_prompt_D0pt%.0fp0_Pthat%.0f_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_PU_20151212_dPt1tkPt1_D0Ds.root",pthat,pthat));
  TTree* ntMC = (TTree*)inf->Get("ntDkpi");
  TH1D* hmassReco = new TH1D("hmassReco",";D mass (GeV/c^{2});Candidates",nbinsmasshisto,minhisto,maxhisto);
  TH1D* hmassRecoMatched = new TH1D("hmassRecoMatched","",nbinsmasshisto,minhisto,maxhisto);
  TH1D* hmassRecoMatchedAll = new TH1D("hmassRecoMatchedAll","",nbinsmasshisto,minhisto,maxhisto);
  TH1D* hmassRecoMatchedNot = new TH1D("hmassRecoMatchedNot","",nbinsmasshisto,minhisto,maxhisto);
  hmassRecoMatched->SetLineColor(kRed);
  hmassRecoMatchedAll->SetLineColor(kBlue);
  hmassRecoMatchedNot->SetLineColor(4);
  TCanvas* c = new TCanvas("c","",600,600);
  hmassReco->SetMinimum(0);
  //ntMC->Draw("Dmass>>hmassReco",Form("Dpt>%f&&Dpt<%f",cutdptmin,cutdptmax));
  ntMC->Draw("Dmass>>hmassRecoMatchedAll",Form("Dpt>%f&&Dpt<%f&&(Dgen==23333||Dgen==23344)",cutdptmin,cutdptmax));
  ntMC->Draw("Dmass>>hmassRecoMatched",Form("Dpt>%f&&Dpt<%f&&(Dgen==23333)",cutdptmin,cutdptmax),"same");
  //c->SaveAs(Form("plots/cMatching_Pthat%.0f_%s.pdf",pthat,date.Data()));
}
