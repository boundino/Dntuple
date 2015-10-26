#include <TTree.h>

Int_t           RecoRunNo;
Int_t           RecoLumiNo;
Int_t           RecoEvtNo;
void setEvtDBranch(TTree *root)
{
  //EvtInfo
  root->SetBranchAddress("EvtInfo.RunNo",&RecoRunNo);
  root->SetBranchAddress("EvtInfo.EvtNo",&RecoEvtNo);
  root->SetBranchAddress("EvtInfo.LumiNo",&RecoLumiNo);
}
Int_t           HltRun;
ULong64_t       HltEvent;
Int_t           HltLumiBlock;
void setEvtHLTBranch(TTree* hltroot)
{
  hltroot->SetBranchAddress("Run",&HltRun);
  hltroot->SetBranchAddress("Event",&HltEvent);
  hltroot->SetBranchAddress("LumiBlock",&HltLumiBlock);
}
Int_t           HiRun;
Int_t           HiEvt;
Int_t           HiLumi;
void setEvtHIBranch(TTree* hiroot)
{
  hiroot->SetBranchAddress("run",&HiRun);
  hiroot->SetBranchAddress("evt",&HiEvt);
  hiroot->SetBranchAddress("lumi",&HiLumi);
}
