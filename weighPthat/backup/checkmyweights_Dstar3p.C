#include "uti.h"

void checkmyweights_Dstar3p()
{
  TString inputmc5="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_Dstarpt5p0_Pthat5_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root";
  TString inputmc10="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_Dstarpt10p0_Pthat10_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root";
  TString inputmc15="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_Dstarpt15p0_Pthat15_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root";
  TString inputmc30="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_Dstarpt30p0_Pthat30_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root";
  TString inputmc50="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_Dstarpt50p0_Pthat50_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root";
  TString inputmcTOT="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_noweight.root";
    
  TFile* infMC5 = new TFile(inputmc5.Data());
  TTree* nthi5 = (TTree*)infMC5->Get("ntHi");
  TFile* infMC10 = new TFile(inputmc10.Data());
  TTree* nthi10 = (TTree*)infMC10->Get("ntHi");
  TFile* infMC15 = new TFile(inputmc15.Data());
  TTree* nthi15 = (TTree*)infMC15->Get("ntHi");
  TFile* infMC30 = new TFile(inputmc30.Data());
  TTree* nthi30 = (TTree*)infMC30->Get("ntHi");
  TFile* infMC50 = new TFile(inputmc50.Data());
  TTree* nthi50 = (TTree*)infMC50->Get("ntHi");
  TFile* infMCTOT = new TFile(inputmcTOT.Data());
  TTree* nthiTOT = (TTree*)infMCTOT->Get("ntHi");

  Float_t events5 = nthi5->GetEntries();
  Float_t events10 = nthi10->GetEntries();
  Float_t events15 = nthi15->GetEntries();
  Float_t events30 = nthi30->GetEntries();
  Float_t events50 = nthi50->GetEntries();
  
  cout<<"event5  = "<<events5<<endl;
  cout<<"event10 = "<<events10<<endl;
  cout<<"event15 = "<<events15<<endl;
  cout<<"event30 = "<<events30<<endl;
  cout<<"event50 = "<<events50<<endl;
  
  TH1D *MCPthat5 = new TH1D("MCPthat5",";pthat;Events",50,0,100);
  TH1D *MCPthat10 = new TH1D("MCPthat10",";pthat;Events",50,0,100);
  TH1D *MCPthat15 = new TH1D("MCPthat15",";pthat;Events",50,0,100);
  TH1D *MCPthat30 = new TH1D("MCPthat30",";pthat;Events",50,0,100);
  TH1D *MCPthat50 = new TH1D("MCPthat50",";pthat;Events",50,0,100);
  TH1D *MCPthatTot = new TH1D("MCPthatTot",";pthat;Events",50,0,100);
  TH1D *MCPthatTotOriginal = new TH1D("MCPthatTotOriginal",";pthat;Events",100,0,100);

  TString weight5 = Form("9.117e+07/%.0f",events5);
  TString weight10 = Form("6.562e+06/%.0f",events10);
  TString weight15 = Form("1.247e+06/%.0f",events15);
  TString weight30 = Form("6.277e+04/%.0f",events30);
  TString weight50 = Form("6.646e+03/%.0f",events50);

  nthi5->Project("MCPthat5","pthat",TCut(weight5));
  nthi10->Project("MCPthat10","pthat",TCut(weight10));
  nthi15->Project("MCPthat15","pthat",TCut(weight15));
  nthi30->Project("MCPthat30","pthat",TCut(weight30));
  nthi50->Project("MCPthat50","pthat",TCut(weight50));
  nthiTOT->Project("MCPthatTotOriginal","pthat","1");
  
  MCPthatTot->Add(MCPthat5);
  MCPthatTot->Add(MCPthat10);
  MCPthatTot->Add(MCPthat15);
  MCPthatTot->Add(MCPthat30);
  MCPthatTot->Add(MCPthat50);
  MCPthatTot->Draw();
  
  TCanvas* canvas=new TCanvas("canvas","canvas",1000,1000);
  canvas->Divide(3,3);
  canvas->SetLogy();
  canvas->cd(1);
  MCPthat5->Draw();
  canvas->cd(2);
  MCPthat10->Draw();
  canvas->cd(3);
  MCPthat15->Draw();
  canvas->cd(4);
  MCPthat30->Draw();
  canvas->cd(5);
  MCPthat50->Draw();
  canvas->cd(6);
  MCPthatTotOriginal->Draw("p");
  canvas->cd(7);
  MCPthatTot->Draw("p");
  
  TCanvas* canvasall=new TCanvas("canvasall","canvasall",1000,1000);
  canvasall->SetLogy();
  //MCPthat5->SetMaximum(1e12);
  //MCPthat5->SetMinimum(1e-3);
  MCPthat5->SetMarkerColor(2);
  MCPthat5->Draw();
  MCPthat10->SetMarkerColor(4);
  MCPthat10->Draw("same");
  MCPthat15->SetMarkerColor(5);
  MCPthat15->Draw("same");      
  MCPthat30->SetMarkerColor(6);
  MCPthat30->Draw("same");
  MCPthat50->SetMarkerColor(7);
  MCPthat50->Draw("same");

}
