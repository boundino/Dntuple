#include "uti.h"

Double_t setparam0=100.;
Double_t setparam1=1.865;
Double_t setparam2=0.03;
Double_t setparam10=0.005;
Double_t setparam8=0.1;
Double_t setparam9=0.1;
Double_t fixparam1=1.865;
int NBIN = 4;
float BINMIN = 10;
float BINMAX = 50;

//TString mvatk = "((Dtrk1Quality&2)&&(Dtrk2Quality&2))";//tight
TString mvatk = "(Dtrk1highPurity&&Dtrk2highPurity)";//highpurity
//TString prefilter = Form("DmaxptMatched&&Dtrk1Pt>1.&&Dtrk2Pt>1.&&Dchi2cl>0.05&&(DsvpvDistance/DsvpvDisErr)>2.5&&TMath::Cos(Dalpha)>0.95&&%s",mvatk.Data());
//TString prefilter = Form("Dtrk1Pt>1.&&Dtrk2Pt>1.&&TMath::Cos(Dalpha)>0.8&&(DsvpvDistance/DsvpvDisErr)>1.&&%s",mvatk.Data());
//TString prefilter = Form("Dtrk1Pt>1.&&Dtrk2Pt>1.&&Dchi2cl>0.05&&TMath::Cos(Dalpha)>0.8&&(DsvpvDistance/DsvpvDisErr)>1.&&%s",mvatk.Data());
TString prefilter = Form("Dtrk1Pt>1.&&Dtrk2Pt>1.&&Dchi2cl>0.05&&TMath::Cos(Dalpha)>0.8&&(DlxyBS/DlxyBSErr)>1.&&%s",mvatk.Data());
TString prefilterMC = Form("Dgen==23333&&DmaxptMatched&&Dtrk1Pt>1.&&Dtrk2Pt>1.&&Dchi2cl>0.05&&(DsvpvDistance/DsvpvDisErr)>2.5&&TMath::Cos(Dalpha)>0.95&&%s",mvatk.Data());
TString prefilterSW = Form("Dgen==23344&&DmaxptMatched&&Dtrk1Pt>1.&&Dtrk2Pt>1.&&Dchi2cl>0.05&&(DsvpvDistance/DsvpvDisErr)>2.5&&TMath::Cos(Dalpha)>0.95&&%s",mvatk.Data());
//TString prefilter = Form("Dtrk1Pt>1.&&Dtrk2Pt>1.");
//TString prefilterMC = Form("Dgen==23333&&Dtrk1Pt>1.&&Dtrk2Pt>1.");
//TString prefilterSW = Form("Dgen==23344&&Dtrk1Pt>1.&&Dtrk2Pt>1.");
Bool_t isPbPb = false;
//Float_t pthat = 5.;
Float_t pthat = 15.;
//Float_t pthat = 35.;
//string outfname = "triggerturnondata_5.root";
//string outfname = "triggerturnondata_15.root";
//string outfname = "triggerturnondata_35.root";
string outfname = "triggerturnondata.root";
TString MBOR = "&&(HLT_L1MinimumBiasHF1OR_part0_v1||HLT_L1MinimumBiasHF1OR_part1_v1||HLT_L1MinimumBiasHF1OR_part2_v1||HLT_L1MinimumBiasHF1OR_part3_v1||HLT_L1MinimumBiasHF1OR_part4_v1||HLT_L1MinimumBiasHF1OR_part5_v1||HLT_L1MinimumBiasHF1OR_part6_v1||HLT_L1MinimumBiasHF1OR_part7_v1||HLT_L1MinimumBiasHF1OR_part8_v1||HLT_L1MinimumBiasHF1OR_part9_v1||HLT_L1MinimumBiasHF1OR_part10_v1||HLT_L1MinimumBiasHF1OR_part11_v1||HLT_L1MinimumBiasHF1OR_part12_v1||HLT_L1MinimumBiasHF1OR_part13_v1||HLT_L1MinimumBiasHF1OR_part14_v1||HLT_L1MinimumBiasHF1OR_part15_v1||HLT_L1MinimumBiasHF1OR_part16_v1||HLT_L1MinimumBiasHF1OR_part17_v1||HLT_L1MinimumBiasHF1OR_part18_v1||HLT_L1MinimumBiasHF1OR_part19_v1)";

void triggerturnondata_prescale()
{
  TH1D* getYield(TTree* nt, TTree* ntMC, TString triggerpass, TString triggername, TString prescale, TString variable, TString varname, TString varlatex, Int_t BIN_NUM, Double_t BIN_MIN, Double_t BIN_MAX, TString addcut="", bool fit = true);
  void plotTurnOn(TH1D* hnominator, TH1D* hdenominator, TString triggerlegend, TString triggername, TString varname, TString varlatex, Int_t BIN_NUM, Double_t BIN_MIN, Double_t BIN_MAX);

  TString infnameMC,infname;
  if(!isPbPb) 
    {
      //infnameMC = Form("/export/d00/scratch/jwang/Dmeson/ntD_20151115_DfinderMC_20151115_EvtMatching_Pythia_D0pt%.0fp0_Pthat%.0f_TuneZ2_5020GeV_GENSIM_75x_1015_20151110_ppGlobaTrackingPPmenuHFlowpuv11_MBseed_twang-Pythia_755patch2_v20_MBseed_1116.root",pthat,pthat);
      //infname = Form("/export/d00/scratch/jwang/Dmeson/ntD_20151115_DfinderMC_20151115_EvtMatching_Pythia_D0pt%.0fp0_Pthat%.0f_TuneZ2_5020GeV_GENSIM_75x_1015_20151110_ppGlobaTrackingPPmenuHFlowpuv11_MBseed_twang-Pythia_755patch2_v20_MBseed_1116.root",pthat,pthat);
      infnameMC = Form("/afs/cern.ch/work/w/wangj/public/Dmeson/ntD_20151115_DfinderMC_20151115_EvtMatching_Pythia_D0pt%.0fp0_Pthat%.0f_TuneZ2_5020GeV_GENSIM_75x_1015_20151110_ppGlobaTrackingPPmenuHFlowpuv11_MBseed_twang-Pythia_755patch2_v20_MBseed_1116.root",pthat,pthat);
      //infname = Form("/afs/cern.ch/work/w/wangj/public/Dmeson/ntD_20151115_DfinderMC_20151115_EvtMatching_Pythia_D0pt%.0fp0_Pthat%.0f_TuneZ2_5020GeV_GENSIM_75x_1015_20151110_ppGlobaTrackingPPmenuHFlowpuv11_MBseed_twang-Pythia_755patch2_v20_MBseed_1116.root",pthat,pthat);
	  infname = Form("/afs/cern.ch/user/t/twang/public/ExpressPpData/Dntuple_ExpressHiForest_run262163-262165_300k.root");
    }
  else
    {
      //infnameMC = Form("/export/d00/scratch/jwang/Dmeson/ntD_20151110_DfinderMC_20151110_EvtMatching_Pyquen_D0tokaonpion_D0pt%.0fp0_Pthat%.0f_TuneZ2_Unquenched_5020GeV_GENSIM_75x_v2_20151110_50k_L1v4_v15_loosecuts_MBseed_1108.root",pthat,pthat);
      //infname = Form("/export/d00/scratch/jwang/Dmeson/ntD_20151110_DfinderMC_20151110_EvtMatching_Pyquen_D0tokaonpion_D0pt%.0fp0_Pthat%.0f_TuneZ2_Unquenched_5020GeV_GENSIM_75x_v2_20151110_50k_L1v4_v15_loosecuts_MBseed_1108.root",pthat,pthat);
      infnameMC = Form("/afs/cern.ch/work/w/wangj/public/Dmeson/ntD_20151110_DfinderMC_20151110_EvtMatching_Pyquen_D0tokaonpion_D0pt%.0fp0_Pthat%.0f_TuneZ2_Unquenched_5020GeV_GENSIM_75x_v2_20151110_50k_L1v4_v15_loosecuts_MBseed_1108.root",pthat,pthat);
      infname = Form("/afs/cern.ch/work/w/wangj/public/Dmeson/ntD_20151110_DfinderMC_20151110_EvtMatching_Pyquen_D0tokaonpion_D0pt%.0fp0_Pthat%.0f_TuneZ2_Unquenched_5020GeV_GENSIM_75x_v2_20151110_50k_L1v4_v15_loosecuts_MBseed_1108.root",pthat,pthat);
//      infname = Form("/afs/cern.ch/work/w/wangj/public/Dmeson/");
    }
  TFile* infile = new TFile(infname);
  TTree* root = (TTree*)infile->Get("ntDkpi");
  root->AddFriend("HltTree");
  TFile* infileMC = new TFile(infnameMC);
  TTree* rootMC = (TTree*)infileMC->Get("ntDkpi");
  rootMC->AddFriend("HltTree");

  TFile *outf = new TFile(outfname.c_str(),"recreate");
  
  if(!isPbPb)
    {
      TH1D* hpp_pt = getYield(root,rootMC,""+MBOR,"","","Dpt","pt","p_{T} (GeV/c)",NBIN,BINMIN,BINMAX, "", false);
      TH1D* hpp_pt_HltDpt8 = getYield(root,rootMC,"&&HLT_DmesonPPTrackingGlobal_Dpt8_v1"+MBOR,"_HLT_DmesonPPTrackingGlobal_Dpt8_v1","HLT_DmesonPPTrackingGlobal_Dpt8_v1_Prescl","Dpt","pt","p_{T} (GeV/c)",NBIN,BINMIN,BINMAX, "", false);
      plotTurnOn(hpp_pt_HltDpt8,hpp_pt,"HLT_DmesonPPTrackingGlobal_Dpt8_v1","_HLT_DmesonPPTrackingGlobal_Dpt8_v1","pt","p_{T} (GeV/c)",NBIN,BINMIN,BINMAX);
      TH1D* hpp_pt_HltDpt15 = getYield(root,rootMC,"&&HLT_DmesonPPTrackingGlobal_Dpt15_v1"+MBOR,"_HLT_DmesonPPTrackingGlobal_Dpt15_v1","HLT_DmesonPPTrackingGlobal_Dpt15_v1_Prescl","Dpt","pt","p_{T} (GeV/c)",NBIN,BINMIN,BINMAX, "", false);
      plotTurnOn(hpp_pt_HltDpt15,hpp_pt,"HLT_DmesonPPTrackingGlobal_Dpt15_v1","_HLT_DmesonPPTrackingGlobal_Dpt15_v1","pt","p_{T} (GeV/c)",NBIN,BINMIN,BINMAX);
      TH1D* hpp_pt_HltDpt20 = getYield(root,rootMC,"&&HLT_DmesonPPTrackingGlobal_Dpt20_v1"+MBOR,"_HLT_DmesonPPTrackingGlobal_Dpt20_v1","HLT_DmesonPPTrackingGlobal_Dpt20_v1_Prescl","Dpt","pt","p_{T} (GeV/c)",NBIN,BINMIN,BINMAX, "", false);
      plotTurnOn(hpp_pt_HltDpt20,hpp_pt,"HLT_DmesonPPTrackingGlobal_Dpt20_v1","_HLT_DmesonPPTrackingGlobal_Dpt20_v1","pt","p_{T} (GeV/c)",NBIN,BINMIN,BINMAX);
      TH1D* hpp_pt_HltDpt30 = getYield(root,rootMC,"&&HLT_DmesonPPTrackingGlobal_Dpt30_v1"+MBOR,"_HLT_DmesonPPTrackingGlobal_Dpt30_v1","HLT_DmesonPPTrackingGlobal_Dpt30_v1_Prescl","Dpt","pt","p_{T} (GeV/c)",NBIN,BINMIN,BINMAX, "", false);
      plotTurnOn(hpp_pt_HltDpt30,hpp_pt,"HLT_DmesonPPTrackingGlobal_Dpt30_v1","_HLT_DmesonPPTrackingGlobal_Dpt30_v1","pt","p_{T} (GeV/c)",NBIN,BINMIN,BINMAX);
      TH1D* hpp_pt_HltDpt40 = getYield(root,rootMC,"&&HLT_DmesonPPTrackingGlobal_Dpt40_v1"+MBOR,"_HLT_DmesonPPTrackingGlobal_Dpt40_v1","HLT_DmesonPPTrackingGlobal_Dpt40_v1_Prescl","Dpt","pt","p_{T} (GeV/c)",NBIN,BINMIN,BINMAX, "", false);
      plotTurnOn(hpp_pt_HltDpt40,hpp_pt,"HLT_DmesonPPTrackingGlobal_Dpt40_v1","_HLT_DmesonPPTrackingGlobal_Dpt40_v1","pt","p_{T} (GeV/c)",NBIN,BINMIN,BINMAX);

      //TH1D* hpp_pt = getYield(root,rootMC,"","","","Dpt","pt","p_{T} (GeV/c)",NBIN,BINMIN,BINMAX);
      //TH1D* hpp_pt_HltDpt8 = getYield(root,rootMC,"&&HLT_DmesonPPTrackingGlobal_Dpt8_v1","_HLT_DmesonPPTrackingGlobal_Dpt8_v1","HLT_DmesonPPTrackingGlobal_Dpt8_v1_Prescl","Dpt","pt","p_{T} (GeV/c)",NBIN,BINMIN,BINMAX);
      //plotTurnOn(hpp_pt_HltDpt8,hpp_pt,"HLT_DmesonPPTrackingGlobal_Dpt8_v1","_HLT_DmesonPPTrackingGlobal_Dpt8_v1","pt","p_{T} (GeV/c)",NBIN,BINMIN,BINMAX);
      //TH1D* hpp_pt_HltDpt15 = getYield(root,rootMC,"&&HLT_DmesonPPTrackingGlobal_Dpt15_v1","_HLT_DmesonPPTrackingGlobal_Dpt15_v1","HLT_DmesonPPTrackingGlobal_Dpt15_v1_Prescl","Dpt","pt","p_{T} (GeV/c)",NBIN,BINMIN,BINMAX);
      //plotTurnOn(hpp_pt_HltDpt15,hpp_pt,"HLT_DmesonPPTrackingGlobal_Dpt15_v1","_HLT_DmesonPPTrackingGlobal_Dpt15_v1","pt","p_{T} (GeV/c)",NBIN,BINMIN,BINMAX);
      //TH1D* hpp_pt_HltDpt20 = getYield(root,rootMC,"&&HLT_DmesonPPTrackingGlobal_Dpt20_v1","_HLT_DmesonPPTrackingGlobal_Dpt20_v1","HLT_DmesonPPTrackingGlobal_Dpt20_v1_Prescl","Dpt","pt","p_{T} (GeV/c)",NBIN,BINMIN,BINMAX);
      //plotTurnOn(hpp_pt_HltDpt20,hpp_pt,"HLT_DmesonPPTrackingGlobal_Dpt20_v1","_HLT_DmesonPPTrackingGlobal_Dpt20_v1","pt","p_{T} (GeV/c)",NBIN,BINMIN,BINMAX);
      //TH1D* hpp_pt_HltDpt30 = getYield(root,rootMC,"&&HLT_DmesonPPTrackingGlobal_Dpt30_v1","_HLT_DmesonPPTrackingGlobal_Dpt30_v1","HLT_DmesonPPTrackingGlobal_Dpt30_v1_Prescl","Dpt","pt","p_{T} (GeV/c)",NBIN,BINMIN,BINMAX);
      //plotTurnOn(hpp_pt_HltDpt30,hpp_pt,"HLT_DmesonPPTrackingGlobal_Dpt30_v1","_HLT_DmesonPPTrackingGlobal_Dpt30_v1","pt","p_{T} (GeV/c)",NBIN,BINMIN,BINMAX);
      //TH1D* hpp_pt_HltDpt40 = getYield(root,rootMC,"&&HLT_DmesonPPTrackingGlobal_Dpt40_v1","_HLT_DmesonPPTrackingGlobal_Dpt40_v1","HLT_DmesonPPTrackingGlobal_Dpt40_v1_Prescl","Dpt","pt","p_{T} (GeV/c)",NBIN,BINMIN,BINMAX);
      //plotTurnOn(hpp_pt_HltDpt40,hpp_pt,"HLT_DmesonPPTrackingGlobal_Dpt40_v1","_HLT_DmesonPPTrackingGlobal_Dpt40_v1","pt","p_{T} (GeV/c)",NBIN,BINMIN,BINMAX);
    }
  else
    {
      TH1D* hpbpb_pt = getYield(root,rootMC,"","","","Dpt","pt","p_{T} (GeV/c)",NBIN,BINMIN,BINMAX);
      TH1D* hpbpb_pt_HltDpt20 = getYield(root,rootMC,"&&HLT_DmesonTrackingGlobalPt8_Dpt20_v1","_HLT_DmesonTrackingGlobalPt8_Dpt20_v1","","Dpt","pt","p_{T} (GeV/c)",NBIN,BINMIN,BINMAX);
    }
  outf->Write();
  cout<<"--- Writing finished"<<endl;
  outf->Close();
}

TH1D* getYield(TTree* nt, TTree* ntMC, TString triggerpass, TString triggername, TString prescale, TString variable, TString varname, TString varlatex, Int_t BIN_NUM, Double_t BIN_MIN, Double_t BIN_MAX, TString addcut="", bool fit = true)
{
  TH1D* hDistrib = new TH1D(Form("h%s_Distrib_%s",triggername.Data(),varname.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
  for(float ivar=0;ivar<BIN_NUM;ivar++)
    {
      TCanvas* c = new TCanvas(Form("c%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"",500,500);
      TH1D* h = new TH1D(Form("h%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),";D^{0} mass (GeV/c^{2});Candidates",60,1.7,2.0);
      TH1D* hMC = new TH1D(Form("hMC%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"",60,1.7,2.0);
      TH1D* hSW = new TH1D(Form("hSW%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"",60,1.7,2.0);
      Float_t varmin = BIN_MIN+ivar*((BIN_MAX-BIN_MIN)/BIN_NUM);
      Float_t varmax = BIN_MIN+(ivar+1)*((BIN_MAX-BIN_MIN)/BIN_NUM);
	  if(prescale==""){
        nt->Project(Form("h%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"Dmass",Form("%s%s&&(%s>%f&&%s<%f)%s",prefilter.Data(),addcut.Data(),variable.Data(),varmin,variable.Data(),varmax,triggerpass.Data()));
	  }
	  else{
        nt->Project(Form("h%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),Form("Dmass*%s",prescale.Data()),Form("%s%s&&(%s>%f&&%s<%f)%s",prefilter.Data(),addcut.Data(),variable.Data(),varmin,variable.Data(),varmax,triggerpass.Data()));
	  }

      h->SetMaximum(h->GetMaximum()*1.20);
      h->SetMarkerStyle(24);
      h->SetStats(0);
      h->Draw("e");
      h->SetXTitle("M_{D} (GeV/c^{2})");
      h->SetYTitle("Entries / (5 MeV/c^{2})");
      h->GetXaxis()->CenterTitle();
      h->GetYaxis()->CenterTitle();
      h->SetTitleOffset(1.,"Y");
      h->SetAxisRange(0,h->GetMaximum()*1.2,"Y");
      h->SetMarkerSize(0.8);
      h->SetMarkerStyle(20);
    
      Double_t yield;
      Double_t yieldErr;
      if(fit){
	    if(prescale==""){
          ntMC->Project(Form("hMC%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"Dmass",Form("%s%s&&(%s>%f&&%s<%f)%s",prefilterMC.Data(),addcut.Data(),variable.Data(),varmin,variable.Data(),varmax,triggerpass.Data()));
          ntMC->Project(Form("hSW%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"Dmass",Form("%s%s&&(%s>%f&&%s<%f)%s",prefilterSW.Data(),addcut.Data(),variable.Data(),varmin,variable.Data(),varmax,triggerpass.Data()));
	    }
	    else{
          ntMC->Project(Form("hMC%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),Form("Dmass*%s",prescale.Data()),Form("%s%s&&(%s>%f&&%s<%f)%s",prefilterMC.Data(),addcut.Data(),variable.Data(),varmin,variable.Data(),varmax,triggerpass.Data()));
          ntMC->Project(Form("hSW%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),Form("Dmass*%s",prescale.Data()),Form("%s%s&&(%s>%f&&%s<%f)%s",prefilterSW.Data(),addcut.Data(),variable.Data(),varmin,variable.Data(),varmax,triggerpass.Data()));
	    }
        TF1* f = new TF1(Form("f%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"[0]*([7]*([9]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[9])*Gaus(x,[1],[10])/(sqrt(2*3.14159)*[10]))+(1-[7])*Gaus(x,[1],[8])/(sqrt(2*3.14159)*[8]))+[3]+[4]*x+[5]*x*x+[6]*x*x*x");
        f->SetParLimits(0,0,1e7);
        f->SetParLimits(4,-1000,1000);
        f->SetParLimits(10,0.001,0.05);
        f->SetParLimits(2,0.01,0.1);
        f->SetParLimits(8,0.02,0.2);
        f->SetParLimits(7,0,1);
        f->SetParLimits(9,0,1);
    
        f->SetParameter(0,setparam0);
        f->SetParameter(1,setparam1);
        f->SetParameter(2,setparam2);
        f->SetParameter(10,setparam10);
        f->SetParameter(9,setparam9);
  
        f->FixParameter(8,setparam8);
        f->FixParameter(7,1);
        f->FixParameter(1,fixparam1);
        f->FixParameter(3,0);
        f->FixParameter(4,0);
        f->FixParameter(5,0);
        f->FixParameter(6,0);
        h->GetEntries();
    
        hMC->Fit(Form("f%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"q","",1.7,2.0);
        hMC->Fit(Form("f%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"q","",1.7,2.0);
        f->ReleaseParameter(1);
        hMC->Fit(Form("f%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"L q","",1.7,2.0);
        hMC->Fit(Form("f%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"L q","",1.7,2.0);
        hMC->Fit(Form("f%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"L m","",1.7,2.0);
    
        f->FixParameter(1,f->GetParameter(1));
        f->FixParameter(2,f->GetParameter(2));
        f->FixParameter(10,f->GetParameter(10));
        f->FixParameter(9,f->GetParameter(9));
        f->FixParameter(7,0);
        f->ReleaseParameter(8);
        f->SetParameter(8,setparam8);
    
        hSW->Fit(Form("f%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"L q","",1.7,2.0);
        hSW->Fit(Form("f%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"L q","",1.7,2.0);
        hSW->Fit(Form("f%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"L q","",1.7,2.0);
        hSW->Fit(Form("f%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"L m","",1.7,2.0);
    
        f->FixParameter(7,hMC->Integral(0,1000)/(hSW->Integral(0,1000)+hMC->Integral(0,1000)));
        f->FixParameter(8,f->GetParameter(8));
        f->ReleaseParameter(3);
        f->ReleaseParameter(4);
        f->ReleaseParameter(5);
        f->ReleaseParameter(6);
    
        h->Fit(Form("f%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"q","",1.7,2.0);
        h->Fit(Form("f%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"q","",1.7,2.0);
        f->ReleaseParameter(1);
        h->Fit(Form("f%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"L q","",1.7,2.0);
        h->Fit(Form("f%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"L q","",1.7,2.0);
        h->Fit(Form("f%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"L q","",1.7,2.0);
        h->Fit(Form("f%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"L m","",1.7,2.0);
    
        TF1* background = new TF1(Form("background%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"[0]+[1]*x+[2]*x*x+[3]*x*x*x");
        background->SetParameter(0,f->GetParameter(3));
        background->SetParameter(1,f->GetParameter(4));
        background->SetParameter(2,f->GetParameter(5));
        background->SetParameter(3,f->GetParameter(6));
        background->SetLineColor(4);
        background->SetRange(1.7,2.0);
        background->SetLineStyle(2);
    
        TF1* mass = new TF1(Form("fmass%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"[0]*([3]*([4]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[4])*Gaus(x,[1],[5])/(sqrt(2*3.14159)*[5])))");
        mass->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2),f->GetParameter(7),f->GetParameter(9),f->GetParameter(10));
        mass->SetParError(0,f->GetParError(0));
        mass->SetParError(1,f->GetParError(1));
        mass->SetParError(2,f->GetParError(2));
        mass->SetParError(3,f->GetParError(7));
        mass->SetParError(4,f->GetParError(9));
        mass->SetParError(5,f->GetParError(10));
        mass->SetLineColor(2);
        mass->SetLineStyle(2);
    
        TF1* massSwap = new TF1(Form("fmassSwap%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"[0]*(1-[2])*Gaus(x,[1],[3])/(sqrt(2*3.14159)*[3])");
        massSwap->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(7),f->GetParameter(8));
        massSwap->SetParError(0,f->GetParError(0));
        massSwap->SetParError(1,f->GetParError(1));
        massSwap->SetParError(2,f->GetParError(7));
        massSwap->SetParError(3,f->GetParError(8));
        massSwap->SetLineColor(2);
        massSwap->SetLineStyle(2);
    
        background->Draw("same");
        mass->SetRange(1.7,2.0);
        mass->Draw("same");
        mass->SetLineStyle(2);
        mass->SetFillStyle(3004);
        mass->SetFillColor(2);
        massSwap->SetRange(1.7,2.0);
        massSwap->SetLineStyle(4);
        massSwap->SetLineColor(kGreen+2);
        massSwap->SetFillStyle(3005);
        massSwap->SetFillColor(kGreen+2);
        massSwap->Draw("same");
        f->Draw("same");
    
        TF1* massAll = new TF1(Form("fmassAll%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"[0]*([3]*([4]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[4])*Gaus(x,[1],[5])/(sqrt(2*3.14159)*[5]))+(1-[3])*Gaus(x,[1],[6])/(sqrt(2*3.14159)*[6]))");
        massAll->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2),f->GetParameter(7),f->GetParameter(9),f->GetParameter(10),f->GetParameter(8));
        massAll->SetParError(0,f->GetParError(0));
        massAll->SetParError(1,f->GetParError(1));
        massAll->SetParError(2,f->GetParError(2));
        massAll->SetParError(3,f->GetParError(7));
        massAll->SetParError(4,f->GetParError(9));
        massAll->SetParError(5,f->GetParError(10));
        massAll->SetParError(6,f->GetParError(8));

        yield = massAll->Integral(1.7,2.0)/0.005;
        yieldErr = (massAll->Integral(1.7,2.0)/0.005)*(massAll->GetParError(0)/massAll->GetParameter(0));

        // Draw the legend:)   
        TLegend* leg = myLegend(0.20,0.60,0.53,0.94);
        leg->SetFillColor(0);
        leg->SetBorderSize(0);
        leg->AddEntry((TObject*)0,"CMS Preliminary","");
        if(isPbPb) leg->AddEntry((TObject*)0,"PbPb #sqrt{s_{NN}}= 5.02 TeV","");
        else leg->AddEntry((TObject*)0,"pp #sqrt{s_{NN}}= 5.02 TeV","");
        leg->AddEntry((TObject*)0,Form("%.1f<%s<%.1f",varmin,varlatex.Data(),varmax),"");
        leg->AddEntry(h,"Data","pl");
        leg->AddEntry(f,"Fit","l");
        leg->AddEntry(mass,"Signal","f");
        leg->AddEntry(massSwap,"K-#pi swapped","f");
        leg->AddEntry(background,"Combinatorial Background","l");
        leg->Draw();
        TLegend* leg2 = myLegend(0.45,0.80,0.90,0.94);
        leg2->SetFillColor(0);
        leg2->SetBorderSize(0);
        leg2->AddEntry(h,"D meson","");
        leg2->AddEntry(h,Form("M_{D}=%.2f #pm %.2f MeV/c^{2}",mass->GetParameter(1)*1000.,mass->GetParError(1)*1000.),"");
        leg2->AddEntry(h,Form("N_{D}=%.0f #pm %.0f", yield, yieldErr),"");
        leg2->Draw();
      }
	  else{
        yield = h->Integral();
		yieldErr = sqrt(yield);

        TLegend* leg = myLegend(0.20,0.60,0.53,0.94);
        leg->SetFillColor(0);
        leg->SetBorderSize(0);
        leg->AddEntry((TObject*)0,"CMS Preliminary","");
        if(isPbPb) leg->AddEntry((TObject*)0,"PbPb #sqrt{s_{NN}}= 5.02 TeV","");
        else leg->AddEntry((TObject*)0,"pp #sqrt{s_{NN}}= 5.02 TeV","");
        leg->AddEntry((TObject*)0,Form("%.1f<%s<%.1f",varmin,varlatex.Data(),varmax),"");
        leg->AddEntry(h,"Data","pl");
        leg->Draw();
        TLegend* leg2 = myLegend(0.45,0.80,0.90,0.94);
        leg2->SetFillColor(0);
        leg2->SetBorderSize(0);
        leg2->AddEntry(h,"D meson","");
        leg2->AddEntry(h,Form("N_{D}=%.0f #pm %.0f", yield, yieldErr),"");
        leg2->Draw();
      }

      hDistrib->SetBinContent(ivar+1,yield);
      hDistrib->SetBinError(ivar+1,yieldErr);

      //if(isPbPb) c->SaveAs(Form("triggerturnonPlots/data/pbpb/pthat%.0f/c%s_Fit_%s_%.0f.pdf",pthat,triggername.Data(),varname.Data(),ivar));
      //else c->SaveAs(Form("triggerturnonPlots/data/pp/pthat%.0f/c%s_Fit_%s_%.0f.pdf",pthat,triggername.Data(),varname.Data(),ivar));
      if(isPbPb) c->SaveAs(Form("triggerturnonPlots/data/pbpb/%s/c%s_Fit_%s_%.0f.pdf","Express",triggername.Data(),varname.Data(),ivar));
      else c->SaveAs(Form("triggerturnonPlots/data/pp/%s/c%s_Fit_%s_%.0f.pdf","Express",triggername.Data(),varname.Data(),ivar));
    }
  TCanvas* cDistrib = new TCanvas(Form("c%s_Distrib_%s",triggername.Data(),varname.Data()),"",500,500);
  hDistrib->Draw();
  hDistrib->SetStats(0);
  //if(isPbPb) cDistrib->SaveAs(Form("triggerturnonPlots/data/pbpb/pthat%.0f/c%s_Distrib_%s.pdf",pthat,triggername.Data(),varname.Data()));
  //else cDistrib->SaveAs(Form("triggerturnonPlots/data/pp/pthat%.0f/c%s_Distrib_%s.pdf",pthat,triggername.Data(),varname.Data()));
  if(isPbPb) cDistrib->SaveAs(Form("triggerturnonPlots/data/pbpb/%s/c%s_Distrib_%s.pdf","Express",triggername.Data(),varname.Data()));
  else cDistrib->SaveAs(Form("triggerturnonPlots/data/pp/%s/c%s_Distrib_%s.pdf","Express",triggername.Data(),varname.Data()));

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
  //if(isPbPb) cEff->SaveAs(Form("triggerturnonPlots/data/pbpb/pthat%.0f/c%s_Eff_%s.pdf",pthat,triggername.Data(),varname.Data()));
  //else cEff->SaveAs(Form("triggerturnonPlots/data/pp/pthat%.0f/c%s_Eff_%s.pdf",pthat,triggername.Data(),varname.Data()));
  if(isPbPb) cEff->SaveAs(Form("triggerturnonPlots/data/pbpb/%s/c%s_Eff_%s.pdf","Express",triggername.Data(),varname.Data()));
  else cEff->SaveAs(Form("triggerturnonPlots/data/pp/%s/c%s_Eff_%s.pdf","Express",triggername.Data(),varname.Data()));
}
