#include <TTree.h>

#define MAX_XB 16384
#define MAX_MUON 512
#define MAX_TRACK 4096
#define MAX_GEN 8192
#define MAX_BX 128
#define MAX_Vertices 4096
#define N_TRIGGER_BOOKINGS 5842

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
