#include "uti.h"
#include "parameters.h"
#include "TLegendEntry.h"
#include "TNtuple.h"
#include "TH1F.h"
#include "../TriggerStudies/triggerEfficiency.C"

using namespace std;


void triggercombination(TString ispp="PP",TString inputdata="/data/dmeson2015/DataDntuple/nt_20160112_DfinderData_pp_20160111_dPt0tkPt1_D0Dstar3p5p_DCSJSON_v2.root",TString inputdataMB="/data/jisun/ppMB2015fullstats/skim_ncand_D0Dntuple_crab_pp_ALLMinimumBias_AOD_D0_tkpt0p5_Ds_01212016.root", int threshold=0, TString output="outputtestpp.root"){

  TFile* inf = new TFile(inputdata.Data());
  TTree* nt = (TTree*) inf->Get("ntDkpi");
  TTree* HltTree= (TTree*) inf->Get("ntHlt");
  HltTree->AddFriend(nt);
  nt->AddFriend(HltTree);
  
  TFile* infMB = new TFile(inputdataMB.Data());
  TTree* ntMB = (TTree*) infMB->Get("ntDkpi");
  TTree* HltTreeMB= (TTree*) infMB->Get("ntHlt");
  HltTreeMB->AddFriend(ntMB);
  ntMB->AddFriend(HltTreeMB);
  
  TString cut=Form("Max$(Dpt)>%d",threshold);
  cout<<cut.Data()<<endl;

  TH1D* hPrescalesPtBins = new TH1D("hPrescalesPtBins","",nBins,ptBins);
  TH1D* hTriggerEfficiencyPtBins = new TH1D("hTriggerEfficiencyPtBins","",nBins,ptBins);
  
  TString triggerHLT[ntriggers];
   int triggerassignment[nBins];
  int triggerHLTthresholds[nBins];
  bool isPbPb;
  
  if(ispp=="PP"){
     for (int index=0; index<ntriggers;index++){
       triggerHLT[index]=triggerHLTPP[index];
       triggerHLTthresholds[index]=triggerHLTPPthresholds[index];
    }
     for (int index=0; index<nBins;index++) triggerassignment[index]=triggerassignmentPP[index];
     isPbPb=false;

  }
  if(ispp=="PbPb"){
     for (int index=0; index<ntriggers;index++){
       triggerHLT[index]=triggerHLTPbPb[index];
       triggerHLTthresholds[index]=triggerHLTPbPbthresholds[index];
    }
     for (int index=0; index<nBins;index++) triggerassignment[index]=triggerassignmentPbPb[index];
     isPbPb=true;

  }

  double ntriggerscounters[ntriggers];       
  double prescale[ntriggers];
  double errorprescale[ntriggers];
  double nflag[ntriggers];               
  double ncounters[ntriggers];
  double ncountersANDunprescaled[ntriggers];

  for (int index=0; index<ntriggers;index++){  
    ntriggerscounters[index]=0.;
    prescale[index]=0.;
    nflag[index]=0.;
    ncounters[index]=0.;
    ncountersANDunprescaled[index]=0.;
  }
  
  TH1D*hCountsPrescANDUnpresc[nBins];
  TH1D*hCountsUnpresc[nBins];
  
  for (int m=0;m<ntriggers;m++) {
  
    TString hnamePrescANDUnpresc=Form("hCountsPrescANDUnpresc_%d",m);
    TString hnameUnpresc=Form("hCountsUnpresc_%d",m);
    
    TString fillhistoPrescANDUnpresc=Form("%s>>%s",triggerHLT[m].Data(),hnamePrescANDUnpresc.Data());
    TString fillhistoUnpresc=Form("%s>>%s",triggerHLT[ntriggers-1].Data(),hnameUnpresc.Data());
    
    TString selPrescANDUnpresc=Form("%s&&%s&&%s",triggerHLT[m].Data(),triggerHLT[ntriggers-1].Data(),cut.Data());
    TString selUnpresc=Form("%s&&%s",triggerHLT[ntriggers-1].Data(),cut.Data());
    
    hCountsPrescANDUnpresc[m]=new TH1D(hnamePrescANDUnpresc.Data(),"histo",100,-0.5,2);
    hCountsUnpresc[m]=new TH1D(hnameUnpresc.Data(),"histo",100,-0.5,2);
    
    nt->Draw(fillhistoPrescANDUnpresc.Data(),selPrescANDUnpresc.Data());
    nt->Draw(fillhistoUnpresc.Data(),selUnpresc.Data());
    
    ncountersANDunprescaled[m]=hCountsPrescANDUnpresc[m]->GetEntries();
    ncounters[m]=hCountsUnpresc[m]->GetEntries();
    
  }
  
    for (int index=0; index<ntriggers;index++){
     prescale[index]=ncountersANDunprescaled[index]/ncounters[ntriggers-1];
     errorprescale[index]=1/ncounters[ntriggers-1]*TMath::Sqrt(ncountersANDunprescaled[index]*(1-(ncountersANDunprescaled[index]/ncounters[ntriggers-1])));
     cout<<"------index------"<<endl;
     cout<<"triggerHLT="<<triggerHLT[index]<<endl;
     cout<<"nuprescaled="<<ncounters[ntriggers-1]<<endl; 
     cout<<"ncountersANDunprescaled="<<ncountersANDunprescaled[index]<<endl; 
     cout<<"prescale="<<prescale[index]<<endl; 
     cout<<"error on prescale binomial="<<errorprescale[index]<<endl; 
     cout<<"relative error on prescale binomial="<<errorprescale[index]/prescale[index]<<endl; 
     
    }
    
    for (int index=0; index<nBins;index++){
     hPrescalesPtBins->SetBinContent(index+1,prescale[triggerassignment[index]]);
     hPrescalesPtBins->SetBinError(index+1,errorprescale[triggerassignment[index]]);
     double triggerefficiency=triggerEfficiency(hPrescalesPtBins->GetBinCenter(index+1),triggerHLTthresholds[triggerassignment[index]],isPbPb);
     std::cout<<"bin center="<<hPrescalesPtBins->GetBinCenter(index+1)<<", thresholds="<<triggerHLTthresholds[triggerassignment[index]]<<",isPbPb="<<isPbPb<<", efficiency="<<triggerefficiency<<std::endl;
     hTriggerEfficiencyPtBins->SetBinContent(index+1,triggerefficiency);
     
    }
    
    TH1D*htrg=new TH1D("htrg","htrg",2,-100,100);
    TH1D*hMB=new TH1D("hMB","hMB",2,-100,100);
    
    //TString mypath="(HLT_L1MinimumBiasHF1OR_part1_v1||HLT_L1MinimumBiasHF1OR_part2_v1||HLT_L1MinimumBiasHF1OR_part3_v1||HLT_L1MinimumBiasHF1OR_part4_v1||HLT_L1MinimumBiasHF1OR_part5_v1||HLT_L1MinimumBiasHF1OR_part6_v1||HLT_L1MinimumBiasHF1OR_part7_v1||HLT_L1MinimumBiasHF1OR_part8_v1||HLT_L1MinimumBiasHF1OR_part9_v1||HLT_L1MinimumBiasHF1OR_part10_v1||HLT_L1MinimumBiasHF1OR_part11_v1||HLT_L1MinimumBiasHF1OR_part12_v1||HLT_L1MinimumBiasHF1OR_part13_v1||HLT_L1MinimumBiasHF1OR_part14_v1||HLT_L1MinimumBiasHF1OR_part15_v1||HLT_L1MinimumBiasHF1OR_part16_v1||HLT_L1MinimumBiasHF1OR_part17_v1||HLT_L1MinimumBiasHF1OR_part18_v1||HLT_L1MinimumBiasHF1OR_part19_v1)";
    //HltTree->Draw("1>>htrg",Form("%s",triggerHLT[ntriggers-1].Data()));
    //HltTreeMB->Draw("1>>hMB",Form("%s&&%s",triggerHLT[ntriggers-1].Data(),mypath.Data()));
    HltTree->Draw("1>>htrg",triggerHLT[ntriggers-1].Data());
    HltTreeMB->Draw("1>>hMB",triggerHLT[ntriggers-1].Data());

    double ncountstrg=htrg->GetEntries();
    double ncountsMB=hMB->GetEntries();
    double ratio=ncountsMB/ncountstrg;
    double relerrortrg=TMath::Sqrt(ncountstrg)/ncountstrg;
    double relerrorMB=TMath::Sqrt(ncountsMB)/ncountsMB;
    double relratio=TMath::Sqrt(relerrortrg*relerrortrg+relerrorMB*relerrorMB);

    std::cout<<"ratio of unprescaled triggers in MB over triggered sample="<<ratio<<"with relative uncertainty="<<relratio<<std::endl; 

      
    hTriggerEfficiencyPtBins->Draw();
    TFile*foutput=new TFile(output.Data(),"recreate");
    foutput->cd();
    hPrescalesPtBins->Write();
    hTriggerEfficiencyPtBins->Write();
    
}


int main(int argc, char *argv[])
{
  if((argc != 6))
  {
    std::cout << "Wrong number of inputs" << std::endl;
    return 1;
  }

  if(argc == 6)
    triggercombination(argv[1],argv[2],argv[3],atoi(argv[4]),argv[5]);
  return 0;
}


