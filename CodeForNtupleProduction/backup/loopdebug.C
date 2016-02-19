using namespace std;

#include "loop.h"
#include "format_float.h"
#include "Dntupledebug.h"

Bool_t istest = true;
int loopdebug(TString infile="root://eoscms//eos/cms//store/user/twang/DfinderRun2/Pythia8D0kpi_Dstarpt10p0_Pthat10_TuneCUETP8M1_5020GeV_GEN_SIM_20151212/DfinderMC_PbPb_20151229_dPt0tkPt2p5_D0Dstar3p5p/finder_PbPb_40_1_u3j.root",
             TString outfile="test.root", Bool_t REAL=false, Bool_t isPbPb=false, Int_t startEntries=0, Int_t endEntries=-1, Bool_t skim=false, Bool_t gskim=true, Bool_t checkMatching=true, Bool_t iseos=false)
{
  if(istest)
    {
      infile="/store/user/twang/DfinderRun2/pp_Pythia8_prompt_D0pt10p0_Pthat10_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20151212/DfinderMC_pp_20160209_dPt0tkPt0p5_D0Dstar/finder_pp_13_1_kpS.root";
      //infile="/afs/cern.ch/user/t/twang/public/ForJing/finder_pp.root";
      //infile="/store/user/twang/DfinderRun2/pp_Pythia8D0kpipipi_Dstarpt10p0_Pthat10_TuneCUETP8M1_5020GeV_GEN_SIM_20151212/DfinderMC_pp_20160201_dPt0tkPt0p5_D0Dstar/finder_pp_19_1_2DA.root";
      //infile="/store/user/twang/DfinderRun2/pp_Pythia8D0kpi_Dstarpt10p0_Pthat10_TuneCUETP8M1_5020GeV_GEN_SIM_20151212/DfinderMC_pp_20160201_dPt0tkPt0p5_D0Dstar/finder_pp_17_1_B6N.root";
      outfile="test.root";
      REAL=false;
      isPbPb=false;
      startEntries=0;
      endEntries=-1;
      checkMatching=true;
      iseos=true;
    }

  cout<<endl;
  if(REAL) cout<<"--- Processing - REAL DATA";
  else cout<<"--- Processing - MC";
  if(isPbPb) cout<<" - PbPb";
  else cout<<" - pp";
  cout<<endl;

  TString ifname;
  if(iseos) ifname = Form("root://eoscms.cern.ch//eos/cms%s",infile.Data());
  else ifname = infile;
  TFile* f = TFile::Open(ifname);
  TTree* root = (TTree*)f->Get("Dfinder/root");
  TTree* hltroot = (TTree*)f->Get("hltanalysis/HltTree");
  TTree* skimroot = (TTree*)f->Get("skimanalysis/HltTree");
  TTree* hiroot = (TTree*)f->Get("hiEvtAnalyzer/HiTree");

  EvtInfoBranches     *EvtInfo = new EvtInfoBranches;
  VtxInfoBranches     *VtxInfo = new VtxInfoBranches;
  TrackInfoBranches   *TrackInfo = new TrackInfoBranches;
  DInfoBranches       *DInfo = new DInfoBranches;
  GenInfoBranches     *GenInfo = new GenInfoBranches;

  setHltTreeBranch(hltroot);
  setHiTreeBranch(hiroot);

  EvtInfo->setbranchadd(root);
  VtxInfo->setbranchadd(root);
  TrackInfo->setbranchadd(root);
  DInfo->setbranchadd(root);
  GenInfo->setbranchadd(root);

  Long64_t nentries = root->GetEntries();
  if(endEntries>nentries || endEntries == -1) endEntries = nentries;

  cout<<"--- Check the number of events for three trees"<<endl;
  cout<<root->GetEntries()<<" "<<hltroot->GetEntries()<<" "<<hiroot->GetEntries();
  cout<<" "<<skimroot->GetEntries()<<endl;
  cout<<endl;
  cout<<"--- Processing events"<<endl;

  TH1F* htkptdif = new TH1F("htkptdif",";trk pt rel diff before and after fit;",80,-10,10);

  for(int i=startEntries;i<endEntries;i++)
    {
      root->GetEntry(i);
      hltroot->GetEntry(i);
      skimroot->GetEntry(i);
      hiroot->GetEntry(i);
      if(checkMatching)
        {
          if(((int)Df_HLT_Event!=EvtInfo->EvtNo||(int)Df_HLT_Run!=EvtInfo->RunNo||(int)Df_HLT_LumiBlock!=EvtInfo->LumiNo) || 
             ((int)Df_HiTree_Evt!=EvtInfo->EvtNo||(int)Df_HiTree_Run!=EvtInfo->RunNo||(int)Df_HiTree_Lumi!=EvtInfo->LumiNo))
            {
              cout<<"Error: not matched "<<i<<" | (Hlt,Dfr,Hi) | ";
              cout<<"EvtNo("<<Df_HLT_Event<<","<<EvtInfo->EvtNo<<","<<Df_HiTree_Evt<<") ";
              cout<<"RunNo("<<Df_HLT_Run<<","<<EvtInfo->RunNo<<","<<Df_HiTree_Run<<") ";
              cout<<"LumiNo("<<Df_HLT_LumiBlock<<","<<EvtInfo->LumiNo<<","<<Df_HiTree_Lumi<<")"<<endl;
              continue;
            }
        }      

      //cout<<"--- Event "<<i<<endl;
      //debuggen(GenInfo);
      debugcomb(TrackInfo, DInfo, GenInfo);
      //debug(TrackInfo, DInfo, GenInfo);
      //beforeNafterFit(TrackInfo, DInfo, htkptdif);
    }
  //TCanvas* chtkptdif = new TCanvas("chtkptdif","",600,600);
  //htkptdif->Draw();
  return 1;
}
