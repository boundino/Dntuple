#include "uti.h"

Double_t setparam0=100.;
Double_t setparam1=1.865;
Double_t setparam2=0.03;
Double_t setparam10=0.005;
Double_t setparam8=0.1;
Double_t setparam9=0.1;
Double_t fixparam1=1.865;

//TString mvatk = "(Dtrk1highPurity&&Dtrk2highPurity)";//highpurity
TString mvatk = "(Dtrk1highPurity&&Dtrk2highPurity)&&(Dmass>1.7&&Dmass<2.0)";//highpurity
TString mbtrg = "(HLT_L1MinimumBiasHF1OR_part0_v1||HLT_L1MinimumBiasHF1OR_part1_v1||HLT_L1MinimumBiasHF1OR_part2_v1||HLT_L1MinimumBiasHF1OR_part3_v1||HLT_L1MinimumBiasHF1OR_part4_v1||HLT_L1MinimumBiasHF1OR_part5_v1||HLT_L1MinimumBiasHF1OR_part6_v1||HLT_L1MinimumBiasHF1OR_part7_v1||HLT_L1MinimumBiasHF1OR_part8_v1||HLT_L1MinimumBiasHF1OR_part9_v1||HLT_L1MinimumBiasHF1OR_part10_v1||HLT_L1MinimumBiasHF1OR_part11_v1||HLT_L1MinimumBiasHF1OR_part12_v1||HLT_L1MinimumBiasHF1OR_part13_v1||HLT_L1MinimumBiasHF1OR_part14_v1||HLT_L1MinimumBiasHF1OR_part15_v1||HLT_L1MinimumBiasHF1OR_part16_v1||HLT_L1MinimumBiasHF1OR_part17_v1||HLT_L1MinimumBiasHF1OR_part18_v1||HLT_L1MinimumBiasHF1OR_part19_v1)";
TString prefilter = Form("(DlxyBS/DlxyBSErr)>1.&&Dtrk1Pt>1.&&Dtrk2Pt>1.&&Dchi2cl>0.05&&TMath::Cos(Dalpha)>0.8&&%s&&%s",mvatk.Data(),mbtrg.Data());
//TString prefilter = Form("DmaxptMatched&&(DlxyBS/DlxyBSErr)>1.&&Dtrk1Pt>1.&&Dtrk2Pt>1.&&Dchi2cl>0.05&&(DsvpvDistance/DsvpvDisErr)>2.5&&TMath::Cos(Dalpha)>0.8&&%s&&%s",mvatk.Data(),mbtrg.Data());
Bool_t isPbPb = false;
Float_t pthat = 15.;

void triggerturnonFast()
{
  TH1D* getYield(TTree* nt, TString triggerpass, TString triggername, TString prescale, TString variable, TString varname, TString varlatex, Int_t BIN_NUM, Double_t BIN_MIN, Double_t BIN_MAX, TString addcut="");
  void plotTurnOn(TH1D* hnominator, TH1D* hdenominator, TString triggerlegend, TString triggername, TString varname, TString varlatex, Int_t BIN_NUM, Double_t BIN_MIN, Double_t BIN_MAX);

  TString infname;
  infname = "/data/wangj/Data2015/Dntuple/ntD_HiForest_262163-262165_300k.root";
  //infname = "/afs/cern.ch/user/t/twang/public/ExpressPpData/Dntuple_ExpressHiForest_run262163-262165_300k.root";
  TFile* infile = new TFile(infname);
  TTree* root = (TTree*)infile->Get("ntDkpi");
  root->AddFriend("HltTree",infname);

  TH1D* hpp_pt = getYield(root,"","","","Dpt","pt","p_{T} (GeV/c)",4,10,50);
  TH1D* hpp_pt_HltDpt8 = getYield(root,"&&HLT_DmesonPPTrackingGlobal_Dpt8_v1","_HLT_DmesonPPTrackingGlobal_Dpt8_v1","HLT_DmesonPPTrackingGlobal_Dpt8_v1_Prescl","Dpt","pt","p_{T} (GeV/c)",4,10,50);
  plotTurnOn(hpp_pt_HltDpt8,hpp_pt,"HLT_DmesonPPTrackingGlobal_Dpt8_v1","_HLT_DmesonPPTrackingGlobal_Dpt8_v1","pt","p_{T} (GeV/c)",4,10,50);

}

TH1D* getYield(TTree* nt, TString triggerpass, TString triggername, TString prescale, TString variable, TString varname, TString varlatex, Int_t BIN_NUM, Double_t BIN_MIN, Double_t BIN_MAX, TString addcut="")
{
  TH1D* hDistrib = new TH1D(Form("h%s_Distrib_%s",triggername.Data(),varname.Data()),Form(";D %s;Event",varlatex.Data()),BIN_NUM,BIN_MIN,BIN_MAX);
  if(prescale=="") nt->Project(Form("h%s_Distrib_%s",triggername.Data(),varname.Data()),variable,Form("%s%s%s",prefilter.Data(),addcut.Data(),triggerpass.Data()));
  else nt->Project(Form("h%s_Distrib_%s",triggername.Data(),varname.Data()),Form("%s*%s",variable.Data(),prescale.Data()),Form("%s%s%s",prefilter.Data(),addcut.Data(),triggerpass.Data()));
  hDistrib->Sumw2();
  TCanvas* cDistrib = new TCanvas(Form("c%s_Distrib_%s",triggername.Data(),varname.Data()),"",500,500);
  hDistrib->Draw();
  hDistrib->SetStats(0);
  if(isPbPb) cDistrib->SaveAs(Form("triggerturnonPlots/data/pbpb/pthat%.0f/c%s_Distrib_%s.pdf",pthat,triggername.Data(),varname.Data()));
  else cDistrib->SaveAs(Form("triggerturnonPlots/data/pp/pthat%.0f/c%s_Distrib_%s.pdf",pthat,triggername.Data(),varname.Data()));

  return hDistrib;
}

void plotTurnOn(TH1D* hnominator, TH1D* hdenominator, TString triggerlegend, TString triggername, TString varname, TString varlatex, Int_t BIN_NUM, Double_t BIN_MIN, Double_t BIN_MAX)
{
  TEfficiency* pEff = new TEfficiency(*hnominator,*hdenominator);
  TCanvas* cEff = new TCanvas(Form("c%s_Eff_%s",triggername.Data(),varname.Data()),"",500,500);
  TH2D* hempty = new TH2D(Form("hempty_%s_Eff_%s",triggername.Data(),varname.Data()),Form(";D^{0} %s;Pass efficiency",varlatex.Data()),BIN_NUM,BIN_MIN,BIN_MAX,10,0,1.2);
  hempty->SetStats(0);
  hempty->Draw();
  pEff->Draw("PSAME");
  TLatex* tex = new TLatex(0.18,0.96,triggerlegend);
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->Draw();
  if(isPbPb) cEff->SaveAs(Form("triggerturnonPlots/data/pbpb/pthat%.0f/c%s_Eff_%s.pdf",pthat,triggername.Data(),varname.Data()));
  else cEff->SaveAs(Form("triggerturnonPlots/data/pp/pthat%.0f/c%s_Eff_%s.pdf",pthat,triggername.Data(),varname.Data()));
}





//backup

/*
  TH1D* hpp_pt = getYield(root,"","","(DlxyBS/DlxyBSErr)","lxylxyerr","lxy/lxyerr",10,0,10,"&&Dpt>15.");
  TH1D* hpp_pt_HltDpt15 = getYield(root,"&&HLT_DmesonPPTrackingGlobal_Dpt15_v1","_HLT_DmesonPPTrackingGlobal_Dpt15_v1","(DlxyBS/DlxyBSErr)","lxylxyerr","lxy/lxyerr",10,0,10,"&&Dpt>15.");
  plotTurnOn(hpp_pt_HltDpt15,hpp_pt,"HLT_DmesonPPTrackingGlobal_Dpt15_v1","_HLT_DmesonPPTrackingGlobal_Dpt15_v1","lxylxyerr","lxy/lxyerr",10,0,10);
  TH1D* hpp_pt = getYield(root,"","","(DsvpvDistance/DsvpvDisErr)","d0d0err","d0/d0Err",10,0,10,"&&Dpt>15.");
  TH1D* hpp_pt_HltDpt15 = getYield(root,"&&HLT_DmesonPPTrackingGlobal_Dpt15_v1","_HLT_DmesonPPTrackingGlobal_Dpt15_v1","(DsvpvDistance/DsvpvDisErr)","d0d0err","d0/d0err",10,0,10,"&&Dpt>15.");
  plotTurnOn(hpp_pt_HltDpt15,hpp_pt,"HLT_DmesonPPTrackingGlobal_Dpt15_v1","_HLT_DmesonPPTrackingGlobal_Dpt15_v1","d0d0err","d0/d0err",10,0,10);
  TH1D* hpp_pt = getYield(root,"","","Dtrk1Pt","trk1pt","trk1 p_{T} (GeV/c)",8,0,80,"&&Dpt>15.");
  TH1D* hpp_pt_HltDpt15 = getYield(root,"&&HLT_DmesonPPTrackingGlobal_Dpt15_v1","_HLT_DmesonPPTrackingGlobal_Dpt15_v1","Dtrk1Pt","trk1pt","trk1 p_{T} (GeV/c)",8,0,80,"&&Dpt>15.");
  plotTurnOn(hpp_pt_HltDpt15,hpp_pt,"HLT_DmesonPPTrackingGlobal_Dpt15_v1","_HLT_DmesonPPTrackingGlobal_Dpt15_v1","trk1pt","trk1 p_{T} (GeV/c)",8,0,80);
  TH1D* hpp_pt = getYield(root,"","","Deta","eta","#eta",8,-2,2,"&&Dpt>15.");
  TH1D* hpp_pt_HltDpt15 = getYield(root,"&&HLT_DmesonPPTrackingGlobal_Dpt15_v1","_HLT_DmesonPPTrackingGlobal_Dpt15_v1","Deta","eta","#eta",8,-2,2,"&&Dpt>15.");
  plotTurnOn(hpp_pt_HltDpt15,hpp_pt,"HLT_DmesonPPTrackingGlobal_Dpt15_v1","_HLT_DmesonPPTrackingGlobal_Dpt15_v1","eta","#eta",8,-2,2);
  TH1D* hpp_pt = getYield(root,"","","Dphi","phi","#phi",8,-2,2,"&&Dpt>15.");
  TH1D* hpp_pt_HltDpt15 = getYield(root,"&&HLT_DmesonPPTrackingGlobal_Dpt15_v1","_HLT_DmesonPPTrackingGlobal_Dpt15_v1","Dphi","phi","#phi",8,-2,2,"&&Dpt>15.");
  plotTurnOn(hpp_pt_HltDpt15,hpp_pt,"HLT_DmesonPPTrackingGlobal_Dpt15_v1","_HLT_DmesonPPTrackingGlobal_Dpt15_v1","eta","#eta",8,-2,2);
*/
