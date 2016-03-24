// Yen-Jie: extraction of the feed-down fraction
using namespace std;
#include "uti.h"

TF1* bFeedDownFractionPbPbMB(Float_t ptMin=4, Float_t ptMax=6)
{
  void normalize(TH1D* h,int color);
  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.043);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.145);
  gStyle->SetTitleX(.0f);

  TFile* infMCP = new TFile("/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_PbPb_Pythia8_prompt_D0_dPt1tkPt1_pthatweight.root");
  TFile* infMCNP = new TFile("/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi_nonprompt/ntD_EvtBase_20160303_Dfinder_20160302_PbPb_Pythia8_nonprompt_D0_dPt1tkPt1_pthatweight.root");
  TFile* infData = new TFile("/data/dmeson2015/DataDntuple/Dntuple_crab_PbPb_HIMinimumBias3_ForestAOD_D0_tkpt0p7eta1p5_goldenjson_01292016_skim.root");
  
   TTree* tMCP = (TTree*)infMCP->Get("ntDkpi");
   TTree* tMCNP = (TTree*)infMCNP->Get("ntDkpi");
   TTree* tMCPHI = (TTree*)infMCP->Get("ntHi");
   TTree* tMCNPHI = (TTree*)infMCNP->Get("ntHi");
   TTree* tData = (TTree*)infData->Get("ntDkpi");
   tMCP->AddFriend(tMCPHI);
   tMCNP->AddFriend(tMCNPHI);   
   
   TFile* outf = new TFile(Form("outfiles/outputPbPbMB_%.0f_%.0f.root",ptMin,ptMax),"recreate");
   TNtuple* nt = new TNtuple("nt","","ptMin:ptMax:Frac:FracErr");
   TCanvas* cSideband = new TCanvas("cSideband","",1200,1200);
   cSideband->Divide(2,2);
   cSideband->cd(1);

   TCut cutPbPbMB = "Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&((DlxyBS/DlxyBSErr)>1.5&&Dalpha<0.12&&((Dpt>1&&Dpt<2&&(DsvpvDistance/DsvpvDisErr)>6.0&&Dchi2cl>0.25)||(Dpt>2&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>5.86&&Dchi2cl>0.224)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>5.46&&Dchi2cl>0.196)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.86&&Dchi2cl>0.170)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.54&&Dchi2cl>0.125)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.42&&Dchi2cl>0.091)||(Dpt>10&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>4.06&&Dchi2cl>0.069)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.71&&Dchi2cl>0.056)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))";

   TCut cutmc=Form("(Dgen==23333||Dgen==23344)&&pthat>(1.5*%f)",ptMin);
   TCut cutpt=Form("Dpt>%f&&Dpt<%f",ptMin,ptMax);
   TCut cutSignal = "abs(Dmass-1.8649)<0.025";
   TCut cutSideband = "abs(Dmass-1.8649)>0.075&&abs(Dmass-1.8649)<0.1";

   TCut weightfunctionreco = "pthatweight";
   int nBin=20;
   Float_t binL=3.5;
   Float_t binH=103.5;
   Float_t fitRangeL=3.5;
   Float_t fitRangeH=100.5;
   if(ptMax<=6) 
     {
       fitRangeH=43.5;
       binH=43.5;
     }
   
   TH1D* hSideband = new TH1D("hSideband",";Flight Distance Significance;Event Fraction",nBin,binL,binH);
   TH1D* hData = new TH1D("hData",";Flight Distance Significance;Event Fraction",nBin,binL,binH);
   TH1D* hMCPSignal = new TH1D("hMCPSignal",";Flight Distance Significance;Event Fraction",nBin,binL,binH);
   TH1D* hMCNPSignal = new TH1D("hMCNPSignal",";Flight Distance Significance;Event Fraction",nBin,binL,binH);
   //TH1D* hMCPSideband = new TH1D("hMCPSideband","",nBin,binL,binH);
   //TH1D* hMCNPSideband = new TH1D("hMCNPSideband","",nBin,binL,binH);
   hSideband->Sumw2();
   hData->Sumw2();
   hMCPSignal->Sumw2();
   hMCNPSignal->Sumw2();

   
   tData->Draw("(DsvpvDistance/DsvpvDisErr)>>hSideband",cutpt&&cutPbPbMB&&cutSideband);
   tData->Draw("(DsvpvDistance/DsvpvDisErr)>>hData",cutpt&&cutPbPbMB&&cutSignal);
   tMCP->Draw("(DsvpvDistance/DsvpvDisErr)>>hMCPSignal",weightfunctionreco*(cutpt&&cutPbPbMB&&cutSignal&&cutmc));
   tMCNP->Draw("(DsvpvDistance/DsvpvDisErr)>>hMCNPSignal",weightfunctionreco*(cutpt&&cutPbPbMB&&cutSignal&&cutmc));
   //tMCP->Draw("(DsvpvDistance/DsvpvDisErr)>>hMCPSideband",cutpt&&cutPbPbMB&&cutSideband);
   //tMCNP->Draw("(DsvpvDistance/DsvpvDisErr)>>hMCNPSideband",cutpt&&cutPbPbMB&&cutSideband);
   
   //hSideband->Scale(1./1.);
   hData->Add(hSideband,-1);
   normalize(hData,1);
   normalize(hMCPSignal,2);
   normalize(hMCNPSignal,4);
   normalize(hSideband,kGreen+2);
   
   TF1* fSideband = new TF1("fSideband","[0]*(exp([1]*x+[2])+[3]*exp([4]*x+[5])+[6]*exp([7]*x+[8]))");      fSideband->SetLineColor(kBlack);    fSideband->SetLineWidth(2);
   TF1* fMCPSignal = new TF1("fMCPSignal","[0]*(exp([1]*x+[2])+[3]*exp([4]*x+[5])+[6]*exp([7]*x+[8]))");    fMCPSignal->SetLineColor(kBlack);   fMCPSignal->SetLineWidth(2);
   TF1* fMCNPSignal = new TF1("fMCNPSignal","[0]*(exp([1]*x+[2])+[3]*exp([4]*x+[5])+[6]*exp([7]*x+[8]))");  fMCNPSignal->SetLineColor(kBlack);  fMCNPSignal->SetLineWidth(2);
   
   fSideband->SetParameters(0,-0.1,0.2,-0,-2,0.006,-0.01,-0.11,-0.04,0,0.001);
   fMCNPSignal->SetParameters(0,-0.1,0.1,-0,-0.02,0.006,-0.01,-0.11,-0.04,0,0.001);
   fMCPSignal->SetParameters(0,-0.1,0.1,-0,-0.02,0.006,-0.01,-0.11,-0.04,0,0.001);

   fMCPSignal->SetParLimits(1,-100,0);   
   fMCPSignal->SetParLimits(4,-100,0);   
   fMCPSignal->SetParLimits(7,-100,0);   
   fMCNPSignal->SetParLimits(1,-100,0);   
   fMCNPSignal->SetParLimits(4,-100,0);   
   fMCNPSignal->SetParLimits(7,-100,0);   
   fMCPSignal->SetParLimits(0,0,1e10);   
   fMCPSignal->SetParLimits(3,0,1e10);   
   fMCPSignal->SetParLimits(6,0,1e10);   
   fMCNPSignal->SetParLimits(0,0,1e10);   
   fMCNPSignal->SetParLimits(3,0,1e10);   
   fMCNPSignal->SetParLimits(6,0,1e10);   

   hSideband->Fit("fMCPSignal","LL q","",fitRangeL,fitRangeH);
   hSideband->Fit("fMCPSignal","LL q","",fitRangeL,fitRangeH);
   hSideband->Fit("fMCPSignal","LL q","",fitRangeL,fitRangeH);
   hSideband->Fit("fMCPSignal","LL q","",fitRangeL,fitRangeH);
   hSideband->Fit("fMCPSignal","LL q","",fitRangeL,fitRangeH);
   hSideband->Fit("fMCNPSignal","LL q","",fitRangeL,fitRangeH);
   hSideband->Fit("fMCNPSignal","LL q","",fitRangeL,fitRangeH);
   hSideband->Fit("fMCNPSignal","LL q","",fitRangeL,fitRangeH);
   hSideband->Fit("fMCNPSignal","LL q","",fitRangeL,fitRangeH);
   hSideband->Fit("fMCNPSignal","LL q","",fitRangeL,fitRangeH);
   
   
   hSideband->Fit("fSideband","LL q","",fitRangeL,fitRangeH);
   hSideband->Fit("fSideband","LL q","",fitRangeL,fitRangeH);
   hSideband->Fit("fSideband"," q","",fitRangeL,fitRangeH);
   hSideband->Fit("fSideband"," q","",fitRangeL,fitRangeH);
   hSideband->Fit("fSideband","LL q","",fitRangeL,fitRangeH);
   hSideband->Fit("fSideband","LL q","",fitRangeL,fitRangeH);
   hSideband->Fit("fSideband"," q","",fitRangeL,fitRangeH);
   hSideband->Fit("fSideband"," q","",fitRangeL,fitRangeH);
   hSideband->Fit("fSideband","m q","",fitRangeL,fitRangeH);
   hSideband->Fit("fSideband","m q","",fitRangeL,fitRangeH);
   hSideband->Fit("fSideband","m q","",fitRangeL,fitRangeH);
   hSideband->Fit("fSideband"," ","",fitRangeL,fitRangeH);

   TLegend* leg1 = new TLegend(0.54,0.76,0.90,0.88,NULL,"brNDC");
   leg1->SetBorderSize(0);
   leg1->SetTextSize(0.04);
   leg1->SetTextFont(42);
   leg1->SetFillStyle(0);
   leg1->AddEntry(hSideband,"Data sideband","pl");
   leg1->AddEntry(fSideband,"Fit","l");
   leg1->Draw("same");

   TLatex* texCms = new TLatex(0.18,0.93, "#scale[1.25]{CMS} Preliminary");
   texCms->SetNDC();
   texCms->SetTextAlign(12);
   texCms->SetTextSize(0.04);
   texCms->SetTextFont(42);
   texCms->Draw();

   TLatex* texCol = new TLatex(0.96,0.93, "PbPbMB #sqrt{s_{NN}} = 5.02 TeV");
   texCol->SetNDC();
   texCol->SetTextAlign(32);
   texCol->SetTextSize(0.04);
   texCol->SetTextFont(42);
   texCol->Draw();

   TLatex* texPt = new TLatex(0.56,0.70,Form("%.1f < p_{T} < %.1f GeV/c",ptMin,ptMax));
   texPt->SetNDC();
   texPt->SetTextFont(42);
   texPt->SetTextSize(0.04);
   texPt->SetLineWidth(2);
   texPt->Draw();

   TLatex* texY = new TLatex(0.56,0.65,"|y| < 1.0");
   texY->SetNDC();
   texY->SetTextFont(42);
   texY->SetTextSize(0.04);
   texY->SetLineWidth(2);
   texY->Draw();
   
   cSideband->cd(2);
   hMCPSignal->Fit("fMCPSignal","LL q","",fitRangeL*2,fitRangeH);
   hMCPSignal->Fit("fMCPSignal","LL q","",fitRangeL*2,fitRangeH);
   hMCPSignal->Fit("fMCPSignal"," q","",fitRangeL*2,fitRangeH);
   hMCPSignal->Fit("fMCPSignal"," q","",fitRangeL*2,fitRangeH);
   hMCPSignal->Fit("fMCPSignal","LL q","",fitRangeL,fitRangeH);
   hMCPSignal->Fit("fMCPSignal","LL q","",fitRangeL,fitRangeH);
   hMCPSignal->Fit("fMCPSignal"," q","",fitRangeL,fitRangeH);
   hMCPSignal->Fit("fMCPSignal"," q","",fitRangeL,fitRangeH);
   hMCPSignal->Fit("fMCPSignal","m q","",fitRangeL,fitRangeH);
   hMCPSignal->Fit("fMCPSignal","m q","",fitRangeL,fitRangeH);
   hMCPSignal->Fit("fMCPSignal","m q","",fitRangeL,fitRangeH);
   hMCPSignal->Fit("fMCPSignal","m ","",fitRangeL,fitRangeH);

   TLegend* leg2 = new TLegend(0.54,0.76,0.90,0.88,NULL,"brNDC");
   leg2->SetBorderSize(0);
   leg2->SetTextSize(0.04);
   leg2->SetTextFont(42);
   leg2->SetFillStyle(0);
   leg2->AddEntry(hMCPSignal,"MC Prompt D^{0}","pl");
   leg2->AddEntry(fMCPSignal,"Fit","l");
   leg2->Draw("same");

   cSideband->cd(3);
   hMCNPSignal->Fit("fMCNPSignal","LL q","",fitRangeL,fitRangeH);
   hMCNPSignal->Fit("fMCNPSignal","LL q","",fitRangeL,fitRangeH);
   hMCNPSignal->Fit("fMCNPSignal"," q","",fitRangeL,fitRangeH);
   hMCNPSignal->Fit("fMCNPSignal"," q","",fitRangeL,fitRangeH);
   hMCNPSignal->Fit("fMCNPSignal","LL q","",fitRangeL,fitRangeH);
   hMCNPSignal->Fit("fMCNPSignal","LL q","",fitRangeL,fitRangeH);
   hMCNPSignal->Fit("fMCNPSignal"," q","",fitRangeL,fitRangeH);
   hMCNPSignal->Fit("fMCNPSignal"," q","",fitRangeL,fitRangeH);
   hMCNPSignal->Fit("fMCNPSignal","m q","",fitRangeL,fitRangeH);
   hMCNPSignal->Fit("fMCNPSignal","m q","",fitRangeL,fitRangeH);
   hMCNPSignal->Fit("fMCNPSignal","m q","",fitRangeL,fitRangeH);
   hMCNPSignal->Fit("fMCNPSignal","m ","",fitRangeL,fitRangeH);
   
   TLegend* leg3 = new TLegend(0.54,0.76,0.90,0.88,NULL,"brNDC");
   leg3->SetBorderSize(0);
   leg3->SetTextSize(0.04);
   leg3->SetTextFont(42);
   leg3->SetFillStyle(0);
   leg3->AddEntry(hMCNPSignal,"MC Non-prompt D^{0}","pl");
   leg3->AddEntry(fMCNPSignal,"Fit","l");
   leg3->Draw("same");
   
   
   string sSideband = Form("(%e)*(exp((%e)*x+(%e))+(%e)*exp((%e)*x+(%e))+(%e)*exp((%e)*x+(%e)))",fSideband->GetParameter(0),fSideband->GetParameter(1),fSideband->GetParameter(2),fSideband->GetParameter(3),fSideband->GetParameter(4),fSideband->GetParameter(5),fSideband->GetParameter(6),fSideband->GetParameter(7),fSideband->GetParameter(8));
   string sMCPSignal = Form("(%e)*(exp((%e)*x+(%e))+(%e)*exp((%e)*x+(%e))+(%e)*exp((%e)*x+(%e)))",fMCPSignal->GetParameter(0),fMCPSignal->GetParameter(1),fMCPSignal->GetParameter(2),fMCPSignal->GetParameter(3),fMCPSignal->GetParameter(4),fMCPSignal->GetParameter(5),fMCPSignal->GetParameter(6),fMCPSignal->GetParameter(7),fMCPSignal->GetParameter(8));
   string sMCNPSignal = Form("(%e)*(exp((%e)*x+(%e))+(%e)*exp((%e)*x+(%e))+(%e)*exp((%e)*x+(%e)))",fMCNPSignal->GetParameter(0),fMCNPSignal->GetParameter(1),fMCNPSignal->GetParameter(2),fMCNPSignal->GetParameter(3),fMCNPSignal->GetParameter(4),fMCNPSignal->GetParameter(5),fMCNPSignal->GetParameter(6),fMCNPSignal->GetParameter(7),fMCNPSignal->GetParameter(8));
   
   
   string function;
   function="0*("+sSideband+")+[1]*([2]*"+sMCPSignal+"+(1-[2])*("+sMCNPSignal+"))";
   string functionNP;
   functionNP="0*("+sSideband+")+[1]*(0*"+sMCPSignal+"+(1-[2])*("+sMCNPSignal+"))";
   
    
   TCanvas* cFit = new TCanvas("cFit","",600,600);
   TF1* f = new TF1("f",function.c_str());
   f->SetParameters(1,0.1,0.9,0,0.1);
   f->SetParLimits(0,0,1000);
   f->SetParLimits(2,-1,2);

   f->SetLineColor(2);
   f->SetFillColor(2);
   f->SetFillStyle(3001);
   f->Draw("same");   

   hData->SetAxisRange(fitRangeL,fitRangeH,"X");
   hData->Fit("f","LL q");
   hData->Fit("f","LL q");
   hData->Fit("f","LL q");
   hData->Fit("f","LL q");
   hData->Fit("f","m");
   
   TF1* fNP = new TF1("fNP",functionNP.c_str());
   fNP->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2));
   fNP->SetRange(fitRangeL,fitRangeH*2);
   fNP->SetLineColor(4);
   fNP->SetFillStyle(3001);
   fNP->SetFillColor(4);
   fNP->Draw("same");  

   hData->SetXTitle("Flight Distance Significance");
   hData->SetYTitle("Event Fraction");
   hData->GetXaxis()->CenterTitle();
   hData->GetYaxis()->CenterTitle();
   hData->GetXaxis()->SetTitleOffset(1.3);
   hData->GetYaxis()->SetTitleOffset(1.8);
   hData->GetXaxis()->SetLabelOffset(0.007);
   hData->GetYaxis()->SetLabelOffset(0.007);
   hData->GetXaxis()->SetTitleSize(0.045);
   hData->GetYaxis()->SetTitleSize(0.045);
   hData->GetXaxis()->SetTitleFont(42);
   hData->GetYaxis()->SetTitleFont(42);
   hData->GetXaxis()->SetLabelFont(42);
   hData->GetYaxis()->SetLabelFont(42);
   hData->GetXaxis()->SetLabelSize(0.04);
   hData->GetYaxis()->SetLabelSize(0.04);
   hData->SetMarkerSize(0.8);
   hData->SetMarkerStyle(20);
   hData->SetStats(0);

   cout <<fNP->Integral(3.5,60)/f->Integral(3.5,60)<<endl;

   texCms->Draw();
   texCol->Draw();

   texY = new TLatex(0.47,0.84,"|y| < 1.0");
   texY->SetNDC();
   texY->SetTextFont(42);
   texY->SetTextSize(0.04);
   texY->SetLineWidth(2);
   texY->Draw();

   texPt = new TLatex(0.47,0.79,Form("%.1f < p_{T} < %.1f GeV/c",ptMin,ptMax));
   texPt->SetNDC();
   texPt->SetTextFont(42);
   texPt->SetTextSize(0.04);
   texPt->SetLineWidth(2);
   texPt->Draw();

   TLatex* texRatio = new TLatex(0.47,0.73,Form("Prompt frac. = %.1f #pm %.1f %%",100*f->GetParameter(2),100*f->GetParError(2)));
   texRatio->SetNDC();
   texRatio->SetTextFont(42);
   texRatio->SetTextSize(0.04);
   texRatio->SetLineWidth(2);
   texRatio->Draw();

   TLegend* leg = new TLegend(0.46,0.55,0.80,0.71);
   leg->SetBorderSize(0);
   leg->SetFillStyle(0);
   leg->AddEntry(hData,"Data","pl");
   leg->AddEntry(f,"Prompt D^{0}","f");
   leg->AddEntry(fNP,"Non-Prompt D^{0}","f");
   leg->Draw("same");

   cFit->SaveAs(Form("plots/PbPbMB_%.0f_%.0f_cFit.pdf",ptMin,ptMax));

   cSideband->cd(4);
   hMCPSignal->Draw("hist");
   hSideband->Draw("hist same");
   hMCNPSignal->Draw("hist same");
   hData->Draw("same e");

   cSideband->SaveAs(Form("plots/PbPbMB_%.0f_%.0f_cSideband.pdf",ptMin,ptMax));
   nt->Fill(ptMin,ptMax,f->GetParameter(2),f->GetParError(2));
   nt->Write();
   outf->Write();
   outf->Close();
   return f;
}

void normalize(TH1D* h,int color)
{
  h->Sumw2();
  for (int i=1;i<=h->GetNbinsX();i++)
    {
      Float_t val=h->GetBinContent(i);
      Float_t valErr=h->GetBinError(i);
      if (val==0) valErr=1;
      h->SetBinContent(i,val/h->GetBinWidth(i));
      h->SetBinError(i,valErr/h->GetBinWidth(i));
    }
  h->Scale(1./h->Integral(0,100));
  h->SetLineColor(color);
  h->SetMarkerColor(color);
  h->GetXaxis()->CenterTitle();
  h->GetYaxis()->CenterTitle();
  h->GetXaxis()->SetTitleOffset(1.3);
  h->GetYaxis()->SetTitleOffset(1.8);
  h->GetXaxis()->SetLabelOffset(0.007);
  h->GetYaxis()->SetLabelOffset(0.007);
  h->GetXaxis()->SetTitleSize(0.045);
  h->GetYaxis()->SetTitleSize(0.045);
  h->GetXaxis()->SetTitleFont(42);
  h->GetYaxis()->SetTitleFont(42);
  h->GetXaxis()->SetLabelFont(42);
  h->GetYaxis()->SetLabelFont(42);
  h->GetXaxis()->SetLabelSize(0.04);
  h->GetYaxis()->SetLabelSize(0.04);
  h->SetMarkerSize(0.8);
  h->SetMarkerStyle(20);
  h->SetStats(0);
}

int main(int argc, char* argv[])
{
  if(argc==1)
    {
      bFeedDownFractionPbPbMB();
      return 1;
    }
  else if(argc==3)
    {
      bFeedDownFractionPbPbMB(atof(argv[1]),atof(argv[2]));
      return 1;
    }
  else
    {
      std::cout<<"Invalid parameter number"<<std::endl;
      return 0;
    }
}

void scan()
{
  TFile* outf = new TFile("result.root","recreate");
  
  TH1D* h = new TH1D("h","",6,20,50);
  int bin=1;
  for (int i=20;i<50;i+=5)
    {
      TF1* f = bFeedDownFractionPbPbMB(i,i+5);
      h->SetBinContent(bin,f->GetParameter(2));
      h->SetBinError(bin,f->GetParError(2));
      bin++;
    }
  
  TCanvas* cResult = new TCanvas("cResult","",600,600);
  h->SetXTitle("D^{0} p_{T} (GeV/c)");
  h->SetYTitle("Prompt Fraction");
  h->Draw("e");
}


