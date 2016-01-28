#include "uti.h"

void checkmyweights()
{
  TString inputmc0="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0pt0p0_Pthat0_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20151212_dPt1tkPt1_D0Ds.root";
  TString inputmc5="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0pt5p0_Pthat5_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20151212_dPt1tkPt1_D0Ds.root";
  TString inputmc10="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0pt10p0_Pthat10_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20151212_dPt1tkPt1_D0Ds.root";
  TString inputmc15="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0pt15p0_Pthat15_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20151212_dPt1tkPt1_D0Ds.root";
  TString inputmc30="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0pt30p0_Pthat30_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20151212_dPt1tkPt1_D0Ds.root";
  TString inputmc50="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0pt50p0_Pthat50_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20151212_dPt1tkPt1_D0Ds.root";
  TString inputmcTOT="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0_noweight.root";
    
  TFile* infMC0 = new TFile(inputmc0.Data());
  TTree* nthi0 = (TTree*)infMC0->Get("ntHi");
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

  double events0=nthi0->GetEntries();
  double events5=nthi5->GetEntries();
  double events10=nthi10->GetEntries();
  double events15=nthi15->GetEntries();
  double events30=nthi30->GetEntries();
  double events50=nthi50->GetEntries();
  
  cout<<"event0="<<events0<<endl;
  cout<<"event5="<<events5<<endl;
  cout<<"event10="<<events10<<endl;
  cout<<"event15="<<events15<<endl;
  cout<<"event30="<<events30<<endl;
  cout<<"event50="<<events50<<endl;
  
  TH1D *MCPthat0 = new TH1D("MCPthat0",";pthat;Events",50,0,500);
  TH1D *MCPthat5 = new TH1D("MCPthat5",";pthat;Events",50,0,500);
  TH1D *MCPthat10 = new TH1D("MCPthat10",";pthat;Events",50,0,500);
  TH1D *MCPthat15 = new TH1D("MCPthat15",";pthat;Events",50,0,500);
  TH1D *MCPthat30 = new TH1D("MCPthat30",";pthat;Events",50,0,500);
  TH1D *MCPthat50 = new TH1D("MCPthat50",";pthat;Events",50,0,500);
  TH1D *MCPthatTot = new TH1D("MCPthatTot",";pthat;Events",50,0,500);
  TH1D *MCPthatTotOriginal = new TH1D("MCPthatTotOriginal",";pthat;Events",100,0,500);
  /*  
  TString weight0="6.924e+09/54587";
  TString weight5="1.713e+08/52335";
  TString weight10="1.073e+07/53125";
  TString weight15="2.305e+06/45728";
  TString weight30="9.654e+04/56560";
  TString weight50="8.639e+03/53978";
*/
  TString weight0="6.924e+09/54587";
  TString weight5="1.713e+08/52335";
  TString weight10="1.073e+07/53125";
  TString weight15="2.305e+06/45728";
  TString weight30="9.654e+04/56560";
  TString weight50="8.639e+03/53978";


  nthi0->Project("MCPthat0","pthat",TCut(weight0));
  nthi5->Project("MCPthat5","pthat",TCut(weight5));
  nthi10->Project("MCPthat10","pthat",TCut(weight10));
  nthi15->Project("MCPthat15","pthat",TCut(weight15));
  nthi30->Project("MCPthat30","pthat",TCut(weight30));
  nthi50->Project("MCPthat50","pthat",TCut(weight50));
  nthiTOT->Project("MCPthatTotOriginal","pthat","1");
  
  MCPthatTot->Add(MCPthat0);
  MCPthatTot->Add(MCPthat5);
  MCPthatTot->Add(MCPthat10);
  MCPthatTot->Add(MCPthat15);
  MCPthatTot->Add(MCPthat30);
  MCPthatTot->Add(MCPthat50);
  MCPthatTot->Draw();
  
  TCanvas*canvas=new TCanvas("canvas","canvas",1000,1000);
  canvas->Divide(3,3);
  canvas->cd(1);
  canvas->SetLogy();
  MCPthat0->Draw();
  canvas->cd(2);
  MCPthat5->Draw();
  canvas->cd(3);
  MCPthat10->Draw();
  canvas->cd(4);
  MCPthat15->Draw();
  canvas->cd(5);
  MCPthat30->Draw();
  canvas->cd(6);
  MCPthat50->Draw();
  canvas->cd(7);
  MCPthatTotOriginal->Draw("p");
  canvas->cd(8);
  MCPthatTot->Draw("p");
  
  TCanvas*canvasall=new TCanvas("canvasall","canvasall",1000,1000);
  canvasall->cd(1);
  canvasall->SetLogy();
  MCPthat0->SetMaximum(1e12);
  MCPthat0->SetMinimum(1e-3);
  MCPthat0->SetMarkerColor(1);
  MCPthat0->Draw("same");
  MCPthat5->SetMarkerColor(2);
  MCPthat5->Draw("same");
  MCPthat10->SetMarkerColor(4);
  MCPthat10->Draw("same");
  MCPthat15->SetMarkerColor(5);
  MCPthat15->Draw("same");      
  MCPthat30->SetMarkerColor(6);
  MCPthat30->Draw("same");
  MCPthat50->SetMarkerColor(7);
  MCPthat50->Draw("same");

}
