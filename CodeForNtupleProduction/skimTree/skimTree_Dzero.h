#include "uti.h"

void SelectRecoBranches(TTree* nt)
{
  nt->SetBranchStatus("DtktkRes*",0);
  nt->SetBranchStatus("Dtrk3*",0);
  nt->SetBranchStatus("Dtrk4*",0);
  nt->SetBranchStatus("DRestrk*",0);
}

void SelectHltBranches(TTree* nthlt)
{
  nthlt->SetBranchStatus("*",0);
  nthlt->SetBranchStatus("HLT_HIL1MinimumBiasHF*",1);
  nthlt->SetBranchStatus("HLT_HIDmeson*",1);
}
