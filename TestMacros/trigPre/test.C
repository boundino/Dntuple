#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <iostream>
#include <TCanvas.h>
#include <TLatex.h>
#include <TMath.h>
#include <TEfficiency.h>

//TString mvatk = "((Dtrk1Quality&2)&&(Dtrk2Quality&2))";//tight
TString mvatk = "(Dtrk1highPurity&&Dtrk2highPurity)";//highpurity
TString prefilter = Form("(Dgen==23333||Dgen==23344)&&Dmaxpt&&Dtrk1Pt>8.&&Dtrk2Pt>8.&&Dchi2cl>0.05&&(DsvpvDistance/DsvpvDisErr)>2.5&&TMath::Cos(Dalpha)>0.95&&%s",mvatk.Data());
Bool_t isPbPb = false;
Float_t pthat = 15.;

void test()
{
  void plotTurnOn(TTree* inttree, TString triggerpass, TString variable, TString varname, TString varlatex, Int_t BIN_NUM, Double_t BIN_MIN, Double_t BIN_MAX, TString addcut="");
  void plotTurnOnNL1seed(TTree* inttree, TString triggerpass, Int_t BIN_NUM, Double_t BIN_MIN, Double_t BIN_MAX);
  TString infname;
  if(!isPbPb) infname = Form("/export/d00/scratch/jwang/Dmeson/ntD_20151029_DfinderMC_20151029_EvtMatching_Pythia_D0pt%.0fp0_Pthat%.0f_TuneZ2_5020GeV_GENSIM_75x_1015_20151027.root",pthat,pthat);
  else infname = Form("/export/d00/scratch/jwang/Dmeson/parameters/ntD_20151103_DfinderMC_20151103_EvtMatching_Pyquen_D0tokaonpion_D0pt%.0fp0_Pthat%.0f_TuneZ2_Unquenched_5020GeV_GENSIM_75x_v2_20151027_ZS_V11_YJfix_tkpt3p0_decaysig_alphachi2_1102.root",pthat,pthat);
  //else infname = Form("/export/d00/scratch/jwang/Dmeson/ntD_20151103_DfinderMC_20151103_EvtMatching_Pyquen_D0tokaonpion_D0pt%.0fp0_Pthat%.0f_TuneZ2_Unquenched_5020GeV_GENSIM_75x_v2_20151027_ZS_V11_YJfix_20151102.root",pthat,pthat);
  //infname = "/export/d00/scratch/jwang/Dmeson/all.root";
  TFile* infile = new TFile(infname);
  TTree* root = (TTree*)infile->Get("ntDkpi");

  if(!isPbPb)
    {
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt10_pp_v1","DsvpvDistance/DsvpvDisErr","ffls3d","3D decay length sig",10,0,30);
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt20_pp_v1","DsvpvDistance/DsvpvDisErr","ffls3d","3D decay length sig",10,0,30);
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt30_pp_v1","DsvpvDistance/DsvpvDisErr","ffls3d","3D decay length sig",10,0,30);
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt40_pp_v1","DsvpvDistance/DsvpvDisErr","ffls3d","3D decay length sig",10,0,30);
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt50_pp_v1","DsvpvDistance/DsvpvDisErr","ffls3d","3D decay length sig",10,0,30);
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt60_pp_v1","DsvpvDistance/DsvpvDisErr","ffls3d","3D decay length sig",10,0,30);

      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt10_pp_v1","DsvpvDisErr","3derr","3D decay length err",10,0,0.2);
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt20_pp_v1","DsvpvDisErr","3derr","3D decay length err",10,0,0.2);
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt30_pp_v1","DsvpvDisErr","3derr","3D decay length err",10,0,0.2);
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt40_pp_v1","DsvpvDisErr","3derr","3D decay length err",10,0,0.2);
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt50_pp_v1","DsvpvDisErr","3derr","3D decay length err",10,0,0.2);
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt60_pp_v1","DsvpvDisErr","3derr","3D decay length err",10,0,0.2);

      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt10_pp_v1","Dlxy","lxy","Lxy",10,-1,4);
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt20_pp_v1","Dlxy","lxy","Lxy",10,-1,4);
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt30_pp_v1","Dlxy","lxy","Lxy",10,-1,4);
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt40_pp_v1","Dlxy","lxy","Lxy",10,-1,4);
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt50_pp_v1","Dlxy","lxy","Lxy",10,-1,4);
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt60_pp_v1","Dlxy","lxy","Lxy",10,-1,4);

      /*
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt20_pp_v1","Dtrk1Algo","tk1algo","higher-pt track Algo",4,4,8);
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt20_pp_v1","Dtrk2Algo","tk2algo","lower-pt track Algo",4,4,8);

      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt10_pp_v1","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt20_pp_v1","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt30_pp_v1","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt40_pp_v1","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt50_pp_v1","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt60_pp_v1","Dpt","pt","p_{T} (GeV/c)",16,0,80);

      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt10_pp_v1","Dtrk1Algo","algo","track Algorithm",16,2,18,"&&Dpt>10.");
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt20_pp_v1","Dtrk1Algo","algo","track Algorithm",16,2,18,"&&Dpt>20.");
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt30_pp_v1","Dtrk1Algo","algo","track Algorithm",16,2,18,"&&Dpt>30.");
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt40_pp_v1","Dtrk1Algo","algo","track Algorithm",16,2,18,"&&Dpt>40.");
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt50_pp_v1","Dtrk1Algo","algo","track Algorithm",16,2,18,"&&Dpt>50.");
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt60_pp_v1","Dtrk1Algo","algo","track Algorithm",16,2,18,"&&Dpt>60.");
      
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt10_pp_v1","Dtrk1Dxy","trkdxy","track Dxy",10,0,0.1,"&&Dpt>10.");
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt20_pp_v1","Dtrk1Dxy","trkdxy","track Dxy",10,0,0.1,"&&Dpt>20.");
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt30_pp_v1","Dtrk1Dxy","trkdxy","track Dxy",10,0,0.1,"&&Dpt>30.");
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt40_pp_v1","Dtrk1Dxy","trkdxy","track Dxy",10,0,0.1,"&&Dpt>40.");
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt50_pp_v1","Dtrk1Dxy","trkdxy","track Dxy",10,0,0.1,"&&Dpt>50.");
      plotTurnOn(root,"HLT_DmesonTrackingGlobal_Dpt60_pp_v1","Dtrk1Dxy","trkdxy","track Dxy",10,0,0.1,"&&Dpt>60.");
      */
    }
  else
    {
      plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt20_v1","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      
      plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt20_v1","Deta","eta","#eta",12,-3,3,"&&Dpt>20.");
      plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1","Deta","eta","#eta",12,-3,3,"&&Dpt>40.");
      plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1","Deta","eta","#eta",12,-3,3,"&&Dpt>60.");
      
      plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt20_v1","Dphi","phi","#phi",16,-4,4,"&&Dpt>20.");
      plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1","Dphi","phi","#phi",16,-4,4,"&&Dpt>40.");
      plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1","Dphi","phi","#phi",16,-4,4,"&&Dpt>60.");
      
    }

}

void plotTurnOn(TTree* inttree, TString triggerpass, TString variable, TString varname, TString varlatex, Int_t BIN_NUM, Double_t BIN_MIN, Double_t BIN_MAX, TString addcut="")
{
  TLatex* tex = new TLatex(0.18,0.96,triggerpass);
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  /*
  TH1D* hall = new TH1D(Form("hall_%s_%s",triggerpass.Data(),varname.Data()),Form(";Matched reco D^{0} %s;Candidates",varlatex.Data()),10,0,1.e+7);
  inttree->Project(Form("hall_%s_%s",triggerpass.Data(),varname.Data()),"Dpt",Form("%s%s",prefilter.Data(),addcut.Data()));
  Double_t scalefac = hall->GetEntries();
  cout<<scalefac<<endl;
  */
  TH1D* hinclusive = new TH1D(Form("hinclusive_%s_%s",triggerpass.Data(),varname.Data()),Form(";Matched reco D^{0} %s;Candidates passing filters",varlatex.Data()),BIN_NUM,BIN_MIN,BIN_MAX);
  inttree->Project(Form("hinclusive_%s_%s",triggerpass.Data(),varname.Data()),variable,Form("%s%s",prefilter.Data(),addcut.Data()));
  hinclusive->Sumw2();
  if(triggerpass=="HLT_DmesonTrackingGlobal_Dpt20_pp_v1"||triggerpass=="HLT_DmesonTrackingGlobalPt8_Dpt20_v1")
    {
      TCanvas* chinclusive = new TCanvas(Form("chinclusive_%s",varname.Data()),"",500,500);      
      hinclusive->Draw();
      hinclusive->SetStats(0);
      chinclusive->SaveAs(Form("triggerturnonPlots/pthat%.0f/MBseed/chinclusive_%s.pdf",pthat,varname.Data()));
    }
  TH1D* hMBseed = new TH1D(Form("h%s_MBseed_%s",triggerpass.Data(),varname.Data()),Form(";Matched reco D^{0} %s;Candidates passing trigger",varlatex.Data()),BIN_NUM,BIN_MIN,BIN_MAX);
  inttree->Project(Form("h%s_MBseed_%s",triggerpass.Data(),varname.Data()),variable,Form("%s%s&&%s",prefilter.Data(),addcut.Data(),triggerpass.Data()));
  hMBseed->Sumw2();
  TCanvas* cMBseed = new TCanvas(Form("c%s_MBseed_%s",triggerpass.Data(),varname.Data()),"",500,500);
  hMBseed->Draw();
  tex->Draw();
  cMBseed->SaveAs(Form("triggerturnonPlots/pthat%.0f/MBseed/c%s_MBseed_%s.pdf",pthat,triggerpass.Data(),varname.Data()));
}

