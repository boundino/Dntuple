#include <TFile.h>
#include <TEfficiency.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TLegend.h>
#include "uti.h"
#include <iostream>
//string triggerName = "HLT_DmesonPPTrackingGlobal_Dpt8_v1";//use 5
//string triggerName = "HLT_DmesonPPTrackingGlobal_Dpt15_v1";//use 5
//string triggerName = "HLT_DmesonPPTrackingGlobal_Dpt20_v1";//use 15
//string triggerName = "HLT_DmesonPPTrackingGlobal_Dpt30_v1";//ues 15
string triggerName = "HLT_DmesonPPTrackingGlobal_Dpt40_v1";//use 35
void compareTurnOn(){
//	TFile* sample1 = new TFile("triggerturnon_5.root");
//	TFile* sample2 = new TFile("triggerturnondata_5.root");
//	TFile* sample1 = new TFile("triggerturnon_15.root");
//	TFile* sample2 = new TFile("triggerturnondata_15.root");
	TFile* sample1 = new TFile("triggerturnon_35.root");
	TFile* sample2 = new TFile("triggerturnondata_35.root");
	TH1D* denominator1 = (TH1D*)sample1->Get(Form("hinclusive_%s_pt", triggerName.c_str()));
	TH1D* denominator2 = (TH1D*)sample2->Get(Form("h_Distrib_pt"));
	TH1D* numerator1 = (TH1D*)sample1->Get(Form("h%s_MBseed_pt", triggerName.c_str()));
	TH1D* numerator2 = (TH1D*)sample2->Get(Form("h_%s_Distrib_pt", triggerName.c_str()));
	for(int i = 0; i < 4; i++){
		if(numerator1->GetBinContent(i+1) > denominator1->GetBinContent(i+1)) {
			numerator1->SetBinContent(i+1, denominator1->GetBinContent(i+1));
			cout<<numerator1->GetBinContent(i+1)<<"/"<<denominator1->GetBinContent(i+1)<<endl;
			cout<<"WARNING!!!!!!!!!!, numerator1>denominator1 for bin "<<i+1<<" setting numerator1=denominator1"<<endl;
		}
		if(numerator2->GetBinContent(i+1) > denominator2->GetBinContent(i+1)) {
			numerator2->SetBinContent(i+1, denominator2->GetBinContent(i+1));
			cout<<numerator2->GetBinContent(i+1)<<"/"<<denominator2->GetBinContent(i+1)<<endl;
			cout<<"WARNING!!!!!!!!!!, numerator2>denominator2 for bin "<<i+1<<" setting numerator2=denominator2"<<endl;
		}
	}

	TEfficiency* eff1 = new TEfficiency(*numerator1, *denominator1);
	TEfficiency* eff2 = new TEfficiency(*numerator2, *denominator2);
    TCanvas* c = new TCanvas(Form("c"),"",500,500);
	
	eff2->SetMarkerColor('2');
	eff1->Draw();
	eff2->Draw("p same");
    TLegend* leg = myLegend(0.10,0.60,0.53,0.85);
    leg->SetFillColor(0);
    leg->SetBorderSize(0);
	leg->SetTextSize(0.03);
    leg->AddEntry((TObject*)0,"turn on comparison","p");
    leg->AddEntry((TObject*)0,Form("%s",triggerName.c_str()),"p");
	leg->AddEntry(eff1, "MC matched","p");
	leg->AddEntry(eff2, "Fitting","p");
	leg->Draw();
	c->SaveAs(Form("comparison/%s.pdf", triggerName.c_str()));
}
