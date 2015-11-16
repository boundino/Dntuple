#include "uti.h"

Double_t setparam0=100.;
Double_t setparam1=1.865;
Double_t setparam2=0.03;
Double_t setparam10=0.005;
Double_t setparam8=0.1;
Double_t setparam9=0.1;
Double_t fixparam1=1.865;

//TString mvatk = "((Dtrk1Quality&2)&&(Dtrk2Quality&2))";//tight
TString mvatk = "(Dtrk1highPurity&&Dtrk2highPurity)";//highpurity
TString prefilter = Form("DmaxptMatched&&Dtrk1Pt>1.&&Dtrk2Pt>1.&&Dchi2cl>0.05&&(DsvpvDistance/DsvpvDisErr)>2.5&&TMath::Cos(Dalpha)>0.95&&%s",mvatk.Data());
TString prefilterMC = Form("Dgen==23333&&DmaxptMatched&&Dtrk1Pt>1.&&Dtrk2Pt>1.&&Dchi2cl>0.05&&(DsvpvDistance/DsvpvDisErr)>2.5&&TMath::Cos(Dalpha)>0.95&&%s",mvatk.Data());
TString prefilterSW = Form("Dgen==23344&&DmaxptMatched&&Dtrk1Pt>1.&&Dtrk2Pt>1.&&Dchi2cl>0.05&&(DsvpvDistance/DsvpvDisErr)>2.5&&TMath::Cos(Dalpha)>0.95&&%s",mvatk.Data());
Bool_t isPbPb = false;
Float_t pthat = 5.;

void triggerturnondata()
{
  TH1D* plotInclusive(TTree* nt, TTree* ntMC, TString variable, TString varname, TString varlatex, Int_t BIN_NUM, Double_t BIN_MIN, Double_t BIN_MAX, TString addcut="");
  TH1D* plotTurnOn(TTree* nt, TTree* ntMC, TH1D* hinclusive, TString triggerpass, TString variable, TString varname, TString varlatex, Int_t BIN_NUM, Double_t BIN_MIN, Double_t BIN_MAX, TString addcut="");
  void plotTurnOnNL1seed(TTree* inttree, TString triggerpass, Int_t BIN_NUM, Double_t BIN_MIN, Double_t BIN_MAX);
  TString infnameMC,infname;
  if(!isPbPb) 
    {
      infnameMC = Form("/export/d00/scratch/jwang/Dmeson/ntD_20151115_DfinderMC_20151115_EvtMatching_Pythia_D0pt%.0fp0_Pthat%.0f_TuneZ2_5020GeV_GENSIM_75x_1015_20151110_ppGlobaTrackingPPmenuHFlowpuv11_MBseed_twang-Pythia_755patch2_v20_MBseed_1116.root",pthat,pthat);
      infname = Form("/export/d00/scratch/jwang/Dmeson/ntD_20151115_DfinderMC_20151115_EvtMatching_Pythia_D0pt%.0fp0_Pthat%.0f_TuneZ2_5020GeV_GENSIM_75x_1015_20151110_ppGlobaTrackingPPmenuHFlowpuv11_MBseed_twang-Pythia_755patch2_v20_MBseed_1116.root",pthat,pthat);
    }
  else
    {
      infnameMC = Form("/export/d00/scratch/jwang/Dmeson/ntD_20151110_DfinderMC_20151110_EvtMatching_Pyquen_D0tokaonpion_D0pt%.0fp0_Pthat%.0f_TuneZ2_Unquenched_5020GeV_GENSIM_75x_v2_20151110_50k_L1v4_v15_loosecuts_MBseed_1108.root",pthat,pthat);
      infname = Form("/export/d00/scratch/jwang/Dmeson/ntD_20151110_DfinderMC_20151110_EvtMatching_Pyquen_D0tokaonpion_D0pt%.0fp0_Pthat%.0f_TuneZ2_Unquenched_5020GeV_GENSIM_75x_v2_20151110_50k_L1v4_v15_loosecuts_MBseed_1108.root",pthat,pthat);
    }
  TFile* infile = new TFile(infname);
  TTree* root = (TTree*)infile->Get("ntDkpi");
  root->AddFriend("HltTree");
  TFile* infileMC = new TFile(infnameMC);
  TTree* rootMC = (TTree*)infileMC->Get("ntDkpi");
  rootMC->AddFriend("HltTree");

  TH1D* hdenominator = plotInclusive(root,rootMC,"Dpt","pt","p_{T} (GeV/c)",4,0,40);
  
  if(!isPbPb)
    {
      plotTurnOn(root,rootMC,hdenominator,"HLT_DmesonPPTrackingGlobal_Dpt20_v1","Dpt","pt","p_{T} (GeV/c)",4,0,40);
      /*
      plotTurnOn(root,rootMC,hdenominator,"HLT_DmesonPPTrackingGlobal_Dpt10_v1","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      plotTurnOn(root,rootMC,hdenominator,"HLT_DmesonPPTrackingGlobal_Dpt20_v1","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      plotTurnOn(root,rootMC,hdenominator,"HLT_DmesonPPTrackingGlobal_Dpt30_v1","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      plotTurnOn(root,rootMC,hdenominator,"HLT_DmesonPPTrackingGlobal_Dpt40_v1","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      plotTurnOn(root,rootMC,hdenominator,"HLT_DmesonPPTrackingGlobal_Dpt50_v1","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      plotTurnOn(root,rootMC,hdenominator,"HLT_DmesonPPTrackingGlobal_Dpt60_v1","Dpt","pt","p_{T} (GeV/c)",16,0,80);      
      */
    }
  else
    {
      plotTurnOn(root,rootMC,hdenominator,"HLT_DmesonTrackingGlobalPt8_Dpt20_v1","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      plotTurnOn(root,rootMC,hdenominator,"HLT_DmesonTrackingGlobalPt8_Dpt30_v1","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      plotTurnOn(root,rootMC,hdenominator,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      plotTurnOn(root,rootMC,hdenominator,"HLT_DmesonTrackingGlobalPt8_Dpt50_v1","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      plotTurnOn(root,rootMC,hdenominator,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1","Dpt","pt","p_{T} (GeV/c)",16,0,80);
    }
}

TH1D* plotInclusive(TTree* nt, TTree* ntMC, TString variable, TString varname, TString varlatex, Int_t BIN_NUM, Double_t BIN_MIN, Double_t BIN_MAX, TString addcut="")
{
  TH1D* hinclusive = new TH1D(Form("hinclusive_%s",varname.Data()),Form(";Data reco D^{0} %s;Candidates",varlatex.Data()),BIN_NUM,BIN_MIN,BIN_MAX);
  for(float ivar=0;ivar<BIN_NUM;ivar++)
    {
      TCanvas* c = new TCanvas(Form("c_%s_%.0f",varname.Data(),ivar),"",500,500);
      TH1D* h = new TH1D(Form("h_%s_%.0f",varname.Data(),ivar),";D^{0} mass (GeV/c^{2});Candidates",60,1.7,2.0);
      TH1D* hMC = new TH1D(Form("hMC_%s_%.0f",varname.Data(),ivar),"",60,1.7,2.0);
      TH1D* hSW = new TH1D(Form("hSW_%s_%.0f",varname.Data(),ivar),"",60,1.7,2.0);
      Float_t varmin = BIN_MIN+ivar*((BIN_MAX-BIN_MIN)/BIN_NUM);
      Float_t varmax = BIN_MIN+(ivar+1)*((BIN_MAX-BIN_MIN)/BIN_NUM);
      nt->Project(Form("h_%s_%.0f",varname.Data(),ivar),"Dmass",Form("%s%s&&(%s>%f&&%s<%f)",prefilter.Data(),addcut.Data(),variable.Data(),varmin,variable.Data(),varmax));
      ntMC->Project(Form("hMC_%s_%.0f",varname.Data(),ivar),"Dmass",Form("%s%s&&(%s>%f&&%s<%f)",prefilterMC.Data(),addcut.Data(),variable.Data(),varmin,variable.Data(),varmax));
      ntMC->Project(Form("hSW_%s_%.0f",varname.Data(),ivar),"Dmass",Form("%s%s&&(%s>%f&&%s<%f)",prefilterSW.Data(),addcut.Data(),variable.Data(),varmin,variable.Data(),varmax));
      h->SetMaximum(h->GetMaximum()*1.20);
      h->Draw();

      TF1* f = new TF1(Form("f_%s_%.0f",varname.Data(),ivar),"[0]*([7]*([9]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[9])*Gaus(x,[1],[10])/(sqrt(2*3.14159)*[10]))+(1-[7])*Gaus(x,[1],[8])/(sqrt(2*3.14159)*[8]))+[3]+[4]*x+[5]*x*x+[6]*x*x*x");
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
  
      hMC->Fit(Form("f_%s_%.0f",varname.Data(),ivar),"q","",1.7,2.0);
      hMC->Fit(Form("f_%s_%.0f",varname.Data(),ivar),"q","",1.7,2.0);
      f->ReleaseParameter(1);
      hMC->Fit(Form("f_%s_%.0f",varname.Data(),ivar),"L q","",1.7,2.0);
      hMC->Fit(Form("f_%s_%.0f",varname.Data(),ivar),"L q","",1.7,2.0);
      hMC->Fit(Form("f_%s_%.0f",varname.Data(),ivar),"L m","",1.7,2.0);
  
      // Extract k-pi Swapped PDF
      f->FixParameter(1,f->GetParameter(1));
      f->FixParameter(2,f->GetParameter(2));
      f->FixParameter(10,f->GetParameter(10));
      f->FixParameter(9,f->GetParameter(9));
      f->FixParameter(7,0);
      f->ReleaseParameter(8);
      f->SetParameter(8,setparam8);
  
      hSW->Fit(Form("f_%s_%.0f",varname.Data(),ivar),"L q","",1.7,2.0);
      hSW->Fit(Form("f_%s_%.0f",varname.Data(),ivar),"L q","",1.7,2.0);
      hSW->Fit(Form("f_%s_%.0f",varname.Data(),ivar),"L q","",1.7,2.0);
      hSW->Fit(Form("f_%s_%.0f",varname.Data(),ivar),"L m","",1.7,2.0);
  
      f->FixParameter(7,hMC->Integral(0,1000)/(hSW->Integral(0,1000)+hMC->Integral(0,1000)));
      f->FixParameter(8,f->GetParameter(8));
      f->ReleaseParameter(3);
      f->ReleaseParameter(4);
      f->ReleaseParameter(5);
      f->ReleaseParameter(6);
  
      // Fit on data
      h->Fit(Form("f_%s_%.0f",varname.Data(),ivar),"q","",1.7,2.0);
      h->Fit(Form("f_%s_%.0f",varname.Data(),ivar),"q","",1.7,2.0);
      f->ReleaseParameter(1);
      h->Fit(Form("f_%s_%.0f",varname.Data(),ivar),"L q","",1.7,2.0);
      h->Fit(Form("f_%s_%.0f",varname.Data(),ivar),"L q","",1.7,2.0);
      h->Fit(Form("f_%s_%.0f",varname.Data(),ivar),"L q","",1.7,2.0);
      h->Fit(Form("f_%s_%.0f",varname.Data(),ivar),"L m","",1.7,2.0);
      h->SetMarkerSize(0.8);
      h->SetMarkerStyle(20);
  
      // function for background shape plotting. take the fit result from f
      TF1* background = new TF1(Form("background_%s_%.0f",varname.Data(),ivar),"[0]+[1]*x+[2]*x*x+[3]*x*x*x");
      background->SetParameter(0,f->GetParameter(3));
      background->SetParameter(1,f->GetParameter(4));
      background->SetParameter(2,f->GetParameter(5));
      background->SetParameter(3,f->GetParameter(6));
      background->SetLineColor(4);
      background->SetRange(1.7,2.0);
      background->SetLineStyle(2);
  
      // function for signal shape plotting. take the fit result from f
      TF1* mass = new TF1(Form("fmass_%s_%.0f",varname.Data(),ivar),"[0]*([3]*([4]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[4])*Gaus(x,[1],[5])/(sqrt(2*3.14159)*[5])))");
      mass->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2),f->GetParameter(7),f->GetParameter(9),f->GetParameter(10));
      mass->SetParError(0,f->GetParError(0));
      mass->SetParError(1,f->GetParError(1));
      mass->SetParError(2,f->GetParError(2));
      mass->SetParError(3,f->GetParError(7));
      mass->SetParError(4,f->GetParError(9));
      mass->SetParError(5,f->GetParError(10));
      mass->SetLineColor(2);
      mass->SetLineStyle(2);
  
      TF1* massSwap = new TF1(Form("fmassSwap_%s_%.0f",varname.Data(),ivar),"[0]*(1-[2])*Gaus(x,[1],[3])/(sqrt(2*3.14159)*[3])");
      massSwap->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(7),f->GetParameter(8));
      massSwap->SetParError(0,f->GetParError(0));
      massSwap->SetParError(1,f->GetParError(1));
      massSwap->SetParError(2,f->GetParError(7));
      massSwap->SetParError(3,f->GetParError(8));
      massSwap->SetLineColor(2);
      massSwap->SetLineStyle(2);
  
      h->SetMarkerStyle(24);
      h->SetStats(0);
      h->Draw("e");
      h->SetXTitle("M_{D} (GeV/c^{2})");
      h->SetYTitle("Entries / (5 MeV/c^{2})");
      h->GetXaxis()->CenterTitle();
      h->GetYaxis()->CenterTitle();
      h->SetTitleOffset(1.,"Y");
      h->SetAxisRange(0,h->GetMaximum()*1.2,"Y");
  
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
  
      TF1* massAll = new TF1(Form("fmassAll_%s_%.0f",varname.Data(),ivar),"[0]*([3]*([4]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[4])*Gaus(x,[1],[5])/(sqrt(2*3.14159)*[5]))+(1-[3])*Gaus(x,[1],[6])/(sqrt(2*3.14159)*[6]))");
      massAll->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2),f->GetParameter(7),f->GetParameter(9),f->GetParameter(10),f->GetParameter(8));
      massAll->SetParError(0,f->GetParError(0));
      massAll->SetParError(1,f->GetParError(1));
      massAll->SetParError(2,f->GetParError(2));
      massAll->SetParError(3,f->GetParError(7));
      massAll->SetParError(4,f->GetParError(9));
      massAll->SetParError(5,f->GetParError(10));
      massAll->SetParError(6,f->GetParError(8));

      Double_t yield = massAll->Integral(1.7,2.0)/0.005;
      Double_t yieldErr = (massAll->Integral(1.7,2.0)/0.005)*(massAll->GetParError(0)/massAll->GetParameter(0));

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

      hinclusive->SetBinContent(ivar+1,yield);
      hinclusive->SetBinError(ivar+1,yieldErr);

      if(isPbPb) c->SaveAs(Form("triggerturnonData/pthat%.0f/MBseed/pbpb/c_%s_%.0f.pdf",pthat,varname.Data(),ivar));
      else c->SaveAs(Form("triggerturnonData/pthat%.0f/MBseed/pp/c_%s_%.0f.pdf",pthat,varname.Data(),ivar));
    }
  TCanvas* chinclusive = new TCanvas(Form("chinclusive_%s",varname.Data()),"",500,500);
  hinclusive->Draw();
  hinclusive->SetStats(0);
  if(isPbPb) chinclusive->SaveAs(Form("triggerturnonData/pthat%.0f/MBseed/pbpb/chinclusive_%s.pdf",pthat,varname.Data()));
  else chinclusive->SaveAs(Form("triggerturnonData/pthat%.0f/MBseed/pp/chinclusive_%s.pdf",pthat,varname.Data()));
  return hinclusive;
}


TH1D* plotTurnOn(TTree* nt, TTree* ntMC, TH1D* hinclusive, TString triggerpass, TString variable, TString varname, TString varlatex, Int_t BIN_NUM, Double_t BIN_MIN, Double_t BIN_MAX, TString addcut="")
{
  TLatex* tex = new TLatex(0.18,0.96,triggerpass);
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);

  TH1D* hMBseed = new TH1D(Form("h_%s_MBseed_%s",triggerpass.Data(),varname.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
  for(float ivar=0;ivar<BIN_NUM;ivar++)
    {
      TCanvas* c = new TCanvas(Form("c_%s_MBseed_%s_%.0f",triggerpass.Data(),varname.Data(),ivar),"",500,500);
      TH1D* h = new TH1D(Form("h_%s_MBseed_%s_%.0f",triggerpass.Data(),varname.Data(),ivar),";D^{0} mass (GeV/c^{2});Candidates",60,1.7,2.0);
      TH1D* hMC = new TH1D(Form("hMC_%s_MBseed_%s_%.0f",triggerpass.Data(),varname.Data(),ivar),"",60,1.7,2.0);
      TH1D* hSW = new TH1D(Form("hSW_%s_MBseed_%s_%.0f",triggerpass.Data(),varname.Data(),ivar),"",60,1.7,2.0);
      Float_t varmin = BIN_MIN+ivar*((BIN_MAX-BIN_MIN)/BIN_NUM);
      Float_t varmax = BIN_MIN+(ivar+1)*((BIN_MAX-BIN_MIN)/BIN_NUM);
      nt->Project(Form("h_%s_MBseed_%s_%.0f",triggerpass.Data(),varname.Data(),ivar),"Dmass",Form("%s%s&&(%s>%f&&%s<%f)&&%s",prefilter.Data(),addcut.Data(),variable.Data(),varmin,variable.Data(),varmax,triggerpass.Data()));
      ntMC->Project(Form("hMC_%s_MBseed_%s_%.0f",triggerpass.Data(),varname.Data(),ivar),"Dmass",Form("%s%s&&(%s>%f&&%s<%f)&&%s",prefilterMC.Data(),addcut.Data(),variable.Data(),varmin,variable.Data(),varmax,triggerpass.Data()));
      ntMC->Project(Form("hSW_%s_MBseed_%s_%.0f",triggerpass.Data(),varname.Data(),ivar),"Dmass",Form("%s%s&&(%s>%f&&%s<%f)&&%s",prefilterSW.Data(),addcut.Data(),variable.Data(),varmin,variable.Data(),varmax,triggerpass.Data()));
      h->SetMaximum(h->GetMaximum()*1.20);
      h->Draw();

      TF1* f = new TF1(Form("f_%s_MBseed_%s_%.0f",triggerpass.Data(),varname.Data(),ivar),"[0]*([7]*([9]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[9])*Gaus(x,[1],[10])/(sqrt(2*3.14159)*[10]))+(1-[7])*Gaus(x,[1],[8])/(sqrt(2*3.14159)*[8]))+[3]+[4]*x+[5]*x*x+[6]*x*x*x");
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
  
      hMC->Fit(Form("f_%s_MBseed_%s_%.0f",triggerpass.Data(),varname.Data(),ivar),"q","",1.7,2.0);
      hMC->Fit(Form("f_%s_MBseed_%s_%.0f",triggerpass.Data(),varname.Data(),ivar),"q","",1.7,2.0);
      f->ReleaseParameter(1);
      hMC->Fit(Form("f_%s_MBseed_%s_%.0f",triggerpass.Data(),varname.Data(),ivar),"L q","",1.7,2.0);
      hMC->Fit(Form("f_%s_MBseed_%s_%.0f",triggerpass.Data(),varname.Data(),ivar),"L q","",1.7,2.0);
      hMC->Fit(Form("f_%s_MBseed_%s_%.0f",triggerpass.Data(),varname.Data(),ivar),"L m","",1.7,2.0);
  
      // Extract k-pi Swapped PDF
      f->FixParameter(1,f->GetParameter(1));
      f->FixParameter(2,f->GetParameter(2));
      f->FixParameter(10,f->GetParameter(10));
      f->FixParameter(9,f->GetParameter(9));
      f->FixParameter(7,0);
      f->ReleaseParameter(8);
      f->SetParameter(8,setparam8);
  
      hSW->Fit(Form("f_%s_MBseed_%s_%.0f",triggerpass.Data(),varname.Data(),ivar),"L q","",1.7,2.0);
      hSW->Fit(Form("f_%s_MBseed_%s_%.0f",triggerpass.Data(),varname.Data(),ivar),"L q","",1.7,2.0);
      hSW->Fit(Form("f_%s_MBseed_%s_%.0f",triggerpass.Data(),varname.Data(),ivar),"L q","",1.7,2.0);
      hSW->Fit(Form("f_%s_MBseed_%s_%.0f",triggerpass.Data(),varname.Data(),ivar),"L m","",1.7,2.0);
  
      f->FixParameter(7,hMC->Integral(0,1000)/(hSW->Integral(0,1000)+hMC->Integral(0,1000)));
      f->FixParameter(8,f->GetParameter(8));
      f->ReleaseParameter(3);
      f->ReleaseParameter(4);
      f->ReleaseParameter(5);
      f->ReleaseParameter(6);
  
      // Fit on data
      h->Fit(Form("f_%s_MBseed_%s_%.0f",triggerpass.Data(),varname.Data(),ivar),"q","",1.7,2.0);
      h->Fit(Form("f_%s_MBseed_%s_%.0f",triggerpass.Data(),varname.Data(),ivar),"q","",1.7,2.0);
      f->ReleaseParameter(1);
      h->Fit(Form("f_%s_MBseed_%s_%.0f",triggerpass.Data(),varname.Data(),ivar),"L q","",1.7,2.0);
      h->Fit(Form("f_%s_MBseed_%s_%.0f",triggerpass.Data(),varname.Data(),ivar),"L q","",1.7,2.0);
      h->Fit(Form("f_%s_MBseed_%s_%.0f",triggerpass.Data(),varname.Data(),ivar),"L q","",1.7,2.0);
      h->Fit(Form("f_%s_MBseed_%s_%.0f",triggerpass.Data(),varname.Data(),ivar),"L m","",1.7,2.0);
      h->SetMarkerSize(0.8);
      h->SetMarkerStyle(20);
  
      // function for background shape plotting. take the fit result from f
      TF1* background = new TF1(Form("background_%s_MBseed_%s_%.0f",triggerpass.Data(),varname.Data(),ivar),"[0]+[1]*x+[2]*x*x+[3]*x*x*x");
      background->SetParameter(0,f->GetParameter(3));
      background->SetParameter(1,f->GetParameter(4));
      background->SetParameter(2,f->GetParameter(5));
      background->SetParameter(3,f->GetParameter(6));
      background->SetLineColor(4);
      background->SetRange(1.7,2.0);
      background->SetLineStyle(2);
  
      // function for signal shape plotting. take the fit result from f
      TF1* mass = new TF1(Form("fmass_%s_MBseed_%s_%.0f",triggerpass.Data(),varname.Data(),ivar),"[0]*([3]*([4]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[4])*Gaus(x,[1],[5])/(sqrt(2*3.14159)*[5])))");
      mass->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2),f->GetParameter(7),f->GetParameter(9),f->GetParameter(10));
      mass->SetParError(0,f->GetParError(0));
      mass->SetParError(1,f->GetParError(1));
      mass->SetParError(2,f->GetParError(2));
      mass->SetParError(3,f->GetParError(7));
      mass->SetParError(4,f->GetParError(9));
      mass->SetParError(5,f->GetParError(10));
      mass->SetLineColor(2);
      mass->SetLineStyle(2);
  
      TF1* massSwap = new TF1(Form("fmassSwap_%s_MBseed_%s_%.0f",triggerpass.Data(),varname.Data(),ivar),"[0]*(1-[2])*Gaus(x,[1],[3])/(sqrt(2*3.14159)*[3])");
      massSwap->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(7),f->GetParameter(8));
      massSwap->SetParError(0,f->GetParError(0));
      massSwap->SetParError(1,f->GetParError(1));
      massSwap->SetParError(2,f->GetParError(7));
      massSwap->SetParError(3,f->GetParError(8));
      massSwap->SetLineColor(2);
      massSwap->SetLineStyle(2);
  
      h->SetMarkerStyle(24);
      h->SetStats(0);
      h->Draw("e");
      h->SetXTitle("M_{D} (GeV/c^{2})");
      h->SetYTitle("Entries / (5 MeV/c^{2})");
      h->GetXaxis()->CenterTitle();
      h->GetYaxis()->CenterTitle();
      h->SetTitleOffset(1.,"Y");
      h->SetAxisRange(0,h->GetMaximum()*1.2,"Y");
  
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
  
      TF1* massAll = new TF1(Form("fmassAll_%s_MBseed_%s_%.0f",triggerpass.Data(),varname.Data(),ivar),"[0]*([3]*([4]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[4])*Gaus(x,[1],[5])/(sqrt(2*3.14159)*[5]))+(1-[3])*Gaus(x,[1],[6])/(sqrt(2*3.14159)*[6]))");
      massAll->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2),f->GetParameter(7),f->GetParameter(9),f->GetParameter(10),f->GetParameter(8));
      massAll->SetParError(0,f->GetParError(0));
      massAll->SetParError(1,f->GetParError(1));
      massAll->SetParError(2,f->GetParError(2));
      massAll->SetParError(3,f->GetParError(7));
      massAll->SetParError(4,f->GetParError(9));
      massAll->SetParError(5,f->GetParError(10));
      massAll->SetParError(6,f->GetParError(8));

      Double_t yield = massAll->Integral(1.7,2.0)/0.005;
      Double_t yieldErr = (massAll->Integral(1.7,2.0)/0.005)*(massAll->GetParError(0)/massAll->GetParameter(0));

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

      hMBseed->SetBinContent(ivar+1,yield);
      hMBseed->SetBinError(ivar+1,yieldErr);

      if(isPbPb) c->SaveAs(Form("triggerturnonData/pthat%.0f/MBseed/pbpb/c_%s_MBseed_%s_%.0f.pdf",pthat,triggerpass.Data(),varname.Data(),ivar));
      else c->SaveAs(Form("triggerturnonData/pthat%.0f/MBseed/pp/c_%s_MBseed_%s_%.0f.pdf",pthat,triggerpass.Data(),varname.Data(),ivar));
    }

  TH2D* hempty = new TH2D(Form("hempty_%s_MBseed_%s",triggerpass.Data(),varname.Data()),Form(";Matched reco D^{0} %s;Pass efficiency (MB seed)",varlatex.Data()),BIN_NUM,BIN_MIN,BIN_MAX,10,0,1.2);
  hempty->SetStats(0);
  TEfficiency* pEffMBseed = new TEfficiency(*hMBseed,*hinclusive);
  TCanvas* cMBseed = new TCanvas(Form("c_%s_MBseed_%s",triggerpass.Data(),varname.Data()),"",500,500);
  hempty->Draw();
  pEffMBseed->Draw("PSAME");
  tex->Draw();
  if(isPbPb) cMBseed->SaveAs(Form("triggerturnonData/pthat%.0f/MBseed/pbpb/c_%s_MBseed_%s.pdf",pthat,triggerpass.Data(),varname.Data()));
  else cMBseed->SaveAs(Form("triggerturnonData/pthat%.0f/MBseed/pp/c_%s_MBseed_%s.pdf",pthat,triggerpass.Data(),varname.Data()));

  return hMBseed;
}
