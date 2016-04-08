using namespace std;
#include "uti.h"
#include "ChargedHad/RAA_0_10.C"
#include "ChargedHad/RAA_0_100.C"
#include "parameters.h"
#include "TLegendEntry.h"

void CombineRAA(TString fileMB="ROOTfiles/outputRAAMB.root", TString file="ROOTfiles/outputRAA.root", TString filecharged="/afs/cern.ch/work/g/ginnocen/public/Spectra_March17_evtselCorrData.root", Float_t centMin=0., Float_t centMax=100., Int_t isHadDupl=1, Int_t isMerged=1)
{
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);

  TFile* filePPMB = new TFile(fileMB.Data());  
  TGraphAsymmErrors* gNuclearModificationMB = (TGraphAsymmErrors*)filePPMB->Get("gNuclearModification");
  TH1D* hNuclearModificationMB = (TH1D*)filePPMB->Get("hNuclearModification");

  TFile* filePP = new TFile(file.Data());  
  TGraphAsymmErrors* gNuclearModification = (TGraphAsymmErrors*)filePP->Get("gNuclearModification");
  TH1D* hNuclearModification = (TH1D*)filePP->Get("hNuclearModification");
  
  TFile* fRAA=new TFile(filecharged.Data());
  TH1D* hTrackPt_trkCorr_PbPb_copy1 = new TH1D("hTrackPt_trkCorr_PbPb_copy1","",1,0,1);
  hTrackPt_trkCorr_PbPb_copy1->Sumw2();
  hTrackPt_trkCorr_PbPb_copy1->SetLineWidth(2);
  hTrackPt_trkCorr_PbPb_copy1->SetLineColor(kRed);
  hTrackPt_trkCorr_PbPb_copy1->SetMarkerStyle(20);
  hTrackPt_trkCorr_PbPb_copy1->SetMarkerSize(0.8);
  hTrackPt_trkCorr_PbPb_copy1->SetMarkerColor(kRed);
  //TH1D* hTrackPt_trkCorr_PbPb_copy1 = (TH1D*)fRAA->Get("hTrackPt_trkCorr_PbPb_copy1");
  //TH1D*hTrackPt_trkCorr_PbPb_copy1=(TH1D*)fRAA->Get("RAA_0_100");  

  TCanvas*canvasRAA=new TCanvas("canvasRAA","canvasRAA",600,600);//550,500
  canvasRAA->cd();
  canvasRAA->SetFillColor(0);
  canvasRAA->SetBorderMode(0);
  canvasRAA->SetBorderSize(2);
  canvasRAA->SetLeftMargin(0.185);//0.200
  canvasRAA->SetRightMargin(0.025);
  canvasRAA->SetTopMargin(0.080);
  canvasRAA->SetBottomMargin(0.150);
  canvasRAA->SetFrameBorderMode(0);
  canvasRAA->SetLogx();

  TH2F* hemptyEff;
  if(isHadDupl==1) hemptyEff=new TH2F("hemptyEff","",50,0.7,120.,10.,0,1.45); else hemptyEff=new TH2F("hemptyEff","",50,1.0,120.,10.,0,1.45);//50,-2,120.,10.,0,1.5
  hemptyEff->GetXaxis()->CenterTitle();
  hemptyEff->GetYaxis()->CenterTitle();
  hemptyEff->GetYaxis()->SetTitle("D^{0} R_{AA}");
  hemptyEff->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hemptyEff->GetXaxis()->SetTitleOffset(0.95);//0.9
  hemptyEff->GetYaxis()->SetTitleOffset(1.15);//1.
  hemptyEff->GetXaxis()->SetTitleSize(0.060);//0.045
  hemptyEff->GetYaxis()->SetTitleSize(0.060);//0.045
  hemptyEff->GetXaxis()->SetTitleFont(42);
  hemptyEff->GetYaxis()->SetTitleFont(42);
  hemptyEff->GetXaxis()->SetLabelFont(42);
  hemptyEff->GetYaxis()->SetLabelFont(42);
  hemptyEff->GetXaxis()->SetLabelSize(0.050);//0.035
  hemptyEff->GetYaxis()->SetLabelSize(0.050);//0.035  
  hemptyEff->GetXaxis()->SetLabelOffset(-0.01);
  hemptyEff->SetMaximum(2);
  hemptyEff->SetMinimum(0.);
  hemptyEff->Draw();

  TLine *line;
  if(isHadDupl==1) line = new TLine(0.7,1,120,1); else line = new TLine(1.0,1,120,1);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->Draw();

  if(isHadDupl==1)
    {
      if(centMin==0&&centMax==100) RAA_0_100();
      else if(centMin==0&&centMax==10) RAA_0_10();
      else
        {
          cout<<"ERROR: Invalid Centrality range"<<endl;
        }
    }
  gNuclearModification->SetFillColor(5);//1
  gNuclearModification->SetFillStyle(1001);//0 
  gNuclearModification->SetLineWidth(1);//3
  gNuclearModification->SetMarkerSize(1);
  gNuclearModification->SetMarkerStyle(21);
  if(isMerged==1)
    {
      gNuclearModification->SetLineColor(1);//kGreen+4
      gNuclearModification->SetMarkerColor(1);//kGreen+4
    }
  else
    {
      gNuclearModification->SetLineColor(kAzure+1);//4
      gNuclearModification->SetMarkerColor(kAzure+1);//4
    }
  gNuclearModification->Draw("5same");
  gNuclearModificationMB->SetFillColor(5);//1
  gNuclearModificationMB->SetFillStyle(1001);//0 
  gNuclearModificationMB->SetLineWidth(1);//3
  gNuclearModificationMB->SetMarkerSize(1);
  gNuclearModificationMB->SetMarkerStyle(21);
  if(isMerged==1)
    {
      gNuclearModificationMB->SetLineColor(1);//kGreen+4
      gNuclearModificationMB->SetMarkerColor(1);//kGreen+4
    }
  else
    {
      gNuclearModificationMB->SetLineColor(kTeal+4);//kGreen+4
      gNuclearModificationMB->SetMarkerColor(kTeal+4);//kGreen+4
    }
  gNuclearModificationMB->Draw("5same");
  
  hNuclearModification->SetLineWidth(3);
  hNuclearModification->SetMarkerSize(1);
  hNuclearModification->SetMarkerStyle(21);
  if(isMerged==1)
    {
      hNuclearModification->SetLineColor(1);//kGreen+4
      hNuclearModification->SetMarkerColor(1);//kGreen+4
    }
  else
    {
      hNuclearModification->SetLineColor(kAzure+1);//4
      hNuclearModification->SetMarkerColor(kAzure+1);//4
    }
  hNuclearModification->Draw("psame");//same
  hNuclearModificationMB->SetLineWidth(3);
  hNuclearModificationMB->SetMarkerSize(1);
  hNuclearModificationMB->SetMarkerStyle(21);
  if(isMerged==1)
    {
      hNuclearModificationMB->SetLineColor(1);//kGreen+4
      hNuclearModificationMB->SetMarkerColor(1);//kGreen+4
    }
  else
    {
      hNuclearModificationMB->SetLineColor(kTeal+4);//kGreen+4
      hNuclearModificationMB->SetMarkerColor(kTeal+4);//kGreen+4
    }
  hNuclearModificationMB->Draw("psame");//same

  /*  
  hTrackPt_trkCorr_PbPb_copy1->SetMarkerColor(2);
  hTrackPt_trkCorr_PbPb_copy1->SetLineColor(2);
  hTrackPt_trkCorr_PbPb_copy1->SetMarkerSize(1);
  hTrackPt_trkCorr_PbPb_copy1->SetMarkerStyle(20);  
  if(isHadDupl==1) hTrackPt_trkCorr_PbPb_copy1->Draw("same");
  hTrackPt_trkCorr_PbPb_copy1->SetLineWidth(3);
  */

  TLatex* texlumi = new TLatex(0.19,0.936,"25.8 pb^{-1} (5.02 TeV pp) + 404 #mub^{-1} (5.02 TeV PbPb)");
  texlumi->SetNDC();
  //texlumi->SetTextAlign(31);
  texlumi->SetTextFont(42);
  texlumi->SetTextSize(0.038);
  texlumi->SetLineWidth(2);
  texlumi->Draw();
  TLatex* texcms = new TLatex(0.22,0.90,"CMS");
  texcms->SetNDC();
  texcms->SetTextAlign(13);
  texcms->SetTextFont(62);//61
  texcms->SetTextSize(0.06);
  texcms->SetLineWidth(2);
  texcms->Draw();
  TLatex* texpre = new TLatex(0.22,0.84,"Preliminary");
  texpre->SetNDC();
  texpre->SetTextAlign(13);
  texpre->SetTextFont(52);
  texpre->SetTextSize(0.04);
  texpre->SetLineWidth(2);
  texpre->Draw();

  TString texper="%";
  //TLatex * tlatexeff2=new TLatex(0.65,0.20,Form("Centrality %.0f-%.0f%s",centMin,centMax,texper.Data()));//0.2612903,0.8425793
  TLatex * tlatexeff2=new TLatex(0.52,0.60,Form("Centrality %.0f-%.0f%s",centMin,centMax,texper.Data()));//0.2612903,0.8425793
  tlatexeff2->SetNDC();
  tlatexeff2->SetTextColor(1);
  tlatexeff2->SetTextFont(42);
  tlatexeff2->SetTextSize(0.043);
  tlatexeff2->SetLineWidth(2);
  tlatexeff2->Draw();

  TLegend *legendSigma=new TLegend(0.50,0.75,0.90,0.90,"");//0.5100806,0.6268644,0.8084677,0.7805932
  legendSigma->SetBorderSize(0);
  legendSigma->SetLineColor(0);
  legendSigma->SetFillColor(0);
  legendSigma->SetFillStyle(1001);
  legendSigma->SetTextFont(42);
  legendSigma->SetTextSize(0.045);//0.05

  if(isMerged==0)
    {
      TLegendEntry *ent_Dhighpt=legendSigma->AddEntry(gNuclearModification,"R_{AA} D triggers.","pf");
      ent_Dhighpt->SetTextFont(42);
      ent_Dhighpt->SetLineColor(1);
      ent_Dhighpt->SetMarkerColor(1);
      ent_Dhighpt->SetTextSize(0.045);
      
      TLegendEntry *ent_DMB=legendSigma->AddEntry(gNuclearModificationMB,"R_{AA} D MB.","pf");
      ent_DMB->SetTextFont(42);
      ent_DMB->SetLineColor(1);
      ent_DMB->SetMarkerColor(1);
      ent_DMB->SetTextSize(0.045);
      
      if(isHadDupl==1)
        {
          TLegendEntry *ent_Charged=legendSigma->AddEntry(hTrackPt_trkCorr_PbPb_copy1,"R_{AA} charged hadrons","pl");//pf
          ent_Charged->SetTextFont(42);
          ent_Charged->SetLineColor(1);
          ent_Charged->SetMarkerColor(1);
          ent_Charged->SetTextSize(0.045);//0.03
        }
    }
  else
    {
      TLegendEntry *ent_Dhighpt=legendSigma->AddEntry(gNuclearModification,"R_{AA} D^{0}","pf");
      ent_Dhighpt->SetTextFont(42);
      ent_Dhighpt->SetLineColor(4);
      ent_Dhighpt->SetMarkerColor(4);
      ent_Dhighpt->SetTextSize(0.043);
      
      if(isHadDupl==1)
        {
          TLegendEntry *ent_Charged=legendSigma->AddEntry(hTrackPt_trkCorr_PbPb_copy1,"R_{AA} charged hadrons","pl");//pf
          ent_Charged->SetTextFont(42);
          ent_Charged->SetLineColor(1);
          ent_Charged->SetMarkerColor(1);
          ent_Charged->SetTextSize(0.043);//0.03
        } 
    }
  if(isHadDupl==1||isMerged==0) legendSigma->Draw();
  canvasRAA->SaveAs(Form("plotRAA/canvasRAAComparison_%.0f_%.0f.pdf",centMin,centMax));
}

int main(int argc, char *argv[])
{
  if(argc==8)
    {
      CombineRAA(argv[1], argv[2], argv[3], atof(argv[4]), atof(argv[5]), atoi(argv[6]), atoi(argv[7]));
      return 0;
    }
  else if(argc==6)
    {
      CombineRAA(argv[1], argv[2], argv[3], atof(argv[4]), atof(argv[5]));
      return 0;
    }
  else
    {
      std::cout << "Wrong number of inputs" << std::endl;
      return 1;
    }
}



