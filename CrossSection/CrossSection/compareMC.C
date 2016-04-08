#include "uti.h"
#include "TLegendEntry.h"
#include "parameters.h"


void test(int effselector=0,TString pthat0="",TString pthat1="",TString pthat2="",TString pthatall=""){

  TString effhisto, titlename;
  if(effselector==0) {effhisto="hEffAcc"; titlename="Acceptance";}
  if(effselector==1) {effhisto="hEffReco"; titlename="Reco efficiency";}
  if(effselector==2) {effhisto="hEffSelection"; titlename="Selection efficiency";}
  if(effselector==3) {effhisto="hEff"; titlename="Total effiiciency";}

  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);
//pthat10pthat10ptreweighted.root
  
  int value1=10; int value2=30; int value3=50; 

  TFile *f1=new TFile(pthat0.Data());
  TFile *f2=new TFile(pthat1.Data());
  TFile *f3=new TFile(pthat2.Data());
  TFile *fallnoweight=new TFile(pthatall.Data());

  TH1D *h1=(TH1D*)f1->Get(effhisto.Data());
  TH1D *h2=(TH1D*)f2->Get(effhisto.Data());
  TH1D *h3=(TH1D*)f3->Get(effhisto.Data());
    
  for (int m=1;m<=nBinsReweight; m++){
  
  if (m>=11) {h1->SetBinContent(m,0); h1->SetBinError(m,0);  }
  if (m>=17) {h2->SetBinContent(m, 0); h2->SetBinError(m,0);  }
    
  }
  
  
  TH1D *hallnoweight=(TH1D*)fallnoweight->Get(effhisto.Data());
  TH2F* hemptyPthat=new TH2F("hemptyPthat","",50,0,100.,10,0.01,10.);  
  hemptyPthat->GetXaxis()->CenterTitle();
  hemptyPthat->GetYaxis()->CenterTitle();
  hemptyPthat->GetYaxis()->SetTitle("Efficiencies");
  hemptyPthat->GetXaxis()->SetTitle("p_{T}");
  hemptyPthat->GetXaxis()->SetTitleOffset(0.9);
  hemptyPthat->GetYaxis()->SetTitleOffset(1.0);
  hemptyPthat->GetXaxis()->SetTitleSize(0.05);
  hemptyPthat->GetYaxis()->SetTitleSize(0.05);
  hemptyPthat->GetXaxis()->SetTitleFont(42);
  hemptyPthat->GetYaxis()->SetTitleFont(42);
  hemptyPthat->GetXaxis()->SetLabelFont(42);
  hemptyPthat->GetYaxis()->SetLabelFont(42);
  hemptyPthat->GetXaxis()->SetLabelSize(0.035);
  hemptyPthat->GetYaxis()->SetLabelSize(0.035);  

  TH2F* hemptyPthatRatio=new TH2F("hemptyPthatRatio","",50,0,100.,10,0.0,2.);  
  hemptyPthatRatio->GetXaxis()->CenterTitle();
  hemptyPthatRatio->GetYaxis()->CenterTitle();
  hemptyPthatRatio->GetYaxis()->SetTitle("Efficiencies");
  hemptyPthatRatio->GetXaxis()->SetTitle("p_{T}");
  hemptyPthatRatio->GetXaxis()->SetTitleOffset(0.9);
  hemptyPthatRatio->GetYaxis()->SetTitleOffset(1.0);
  hemptyPthatRatio->GetXaxis()->SetTitleSize(0.05);
  hemptyPthatRatio->GetYaxis()->SetTitleSize(0.05);
  hemptyPthatRatio->GetXaxis()->SetTitleFont(42);
  hemptyPthatRatio->GetYaxis()->SetTitleFont(42);
  hemptyPthatRatio->GetXaxis()->SetLabelFont(42);
  hemptyPthatRatio->GetYaxis()->SetLabelFont(42);
  hemptyPthatRatio->GetXaxis()->SetLabelSize(0.035);
  hemptyPthatRatio->GetYaxis()->SetLabelSize(0.035);  


  TH1D *hRatio1=(TH1D*)h1->Clone("hRatio1");
  TH1D *hRatio2=(TH1D*)h2->Clone("hRatio2");
  TH1D *hRatio3=(TH1D*)h3->Clone("hRatio3"); 
  hRatio1->Divide(hallnoweight);
  hRatio2->Divide(hallnoweight);
  hRatio3->Divide(hallnoweight);
  


  TCanvas*c=new TCanvas("c","c",1000,500);
  c->Divide(2,1);
  c->cd(1);
  gPad->SetLogy();
  gPad->SetLogx();
  h1->SetLineColor(1);
  h2->SetLineColor(2);
  h3->SetLineColor(4);
  hallnoweight->SetLineColor(6);
  h1->SetMarkerColor(1);
  h2->SetMarkerColor(2);
  h3->SetMarkerColor(4);
  hallnoweight->SetMarkerColor(6);
  
  hemptyPthat->Draw();
  h1->Draw("same");
  h2->Draw("same");
  h3->Draw("same");
  hallnoweight->Draw("same");
  TLegend *legend=new TLegend(0.2100806,0.7068644,0.5084677,0.8605932,"");
  legend->SetBorderSize(0);
  legend->SetLineColor(0);
  legend->SetFillColor(0);
  legend->SetFillStyle(1001);
  legend->SetTextFont(42);
  legend->SetTextSize(0.045);
  TLegendEntry *ent_pthat1=legend->AddEntry(h1,Form("efficiency sample pthat=%d",value1),"pf");
  ent_pthat1->SetTextFont(42);
  ent_pthat1->SetLineColor(1);
  ent_pthat1->SetMarkerColor(1);
  TLegendEntry *ent_pthat2=legend->AddEntry(h2,Form("efficiency sample pthat=%d",value2),"pf");
  ent_pthat2->SetTextFont(42);
  ent_pthat2->SetLineColor(2);
  ent_pthat2->SetMarkerColor(2);
  TLegendEntry *ent_pthat3=legend->AddEntry(h3,Form("efficiency sample pthat=%d",value3),"pf");
  ent_pthat3->SetTextFont(42);
  ent_pthat3->SetLineColor(4);
  ent_pthat3->SetMarkerColor(4);
  
  TLegendEntry *ent_pthatallnoweigth=legend->AddEntry(hallnoweight,"efficiency sample pthat all","pf");
  ent_pthatallnoweigth->SetTextFont(42);
  ent_pthatallnoweigth->SetLineColor(6);
  ent_pthatallnoweigth->SetMarkerColor(6);
  legend->Draw("same");   
  c->cd(2);
  gPad->SetLogx();
  hRatio1->SetLineColor(1);
  hRatio2->SetLineColor(2);
  hRatio3->SetLineColor(4);
  hallnoweight->SetLineColor(6);
  hRatio1->SetMarkerColor(1);
  hRatio2->SetMarkerColor(2);
  hRatio3->SetMarkerColor(4);
  hallnoweight->SetMarkerColor(6);
  hemptyPthatRatio->Draw();
  hRatio1->Draw("same");
  hRatio2->Draw("same");
  hRatio3->Draw("same");
  
  if(effselector==0) c->SaveAs(Form("canvasAccEfficiency_phat%d_pthat%d_pthat%d.pdf",value1,value2,value3));
  if(effselector==1) c->SaveAs(Form("canvasRecoEfficiency_phat%d_pthat%d_pthat%d.pdf",value1,value2,value3));
  if(effselector==2) c->SaveAs(Form("canvasSelEfficiency_phat%d_pthat%d_pthat%d.pdf",value1,value2,value3));
  if(effselector==3) c->SaveAs(Form("canvasTotalEfficiency_phat%d_pthat%d_pthat%d.pdf",value1,value2,value3));

}


void compareMC(TString pthat0,TString pthat1,TString pthat2,TString pthatall){
  test(0,pthat0,pthat1,pthat2,pthatall);
  test(1,pthat0,pthat1,pthat2,pthatall);
  test(2,pthat0,pthat1,pthat2,pthatall);
  test(3,pthat0,pthat1,pthat2,pthatall);

}

int main(int argc, char *argv[])
{
  if((argc !=5))
  {
    std::cout << "Wrong number of inputs" << std::endl;
    return 1;
  }
  
  if(argc == 5)
    compareMC(argv[1],argv[2],argv[3],argv[4]);
  return 0;
}
