#include "uti.h"

void SelectRecoBranches(TTree* nt)
{
  nt->SetBranchStatus("*",0);
  nt->SetBranchStatus("Dsize",1);
  nt->SetBranchStatus("Dmass",1);
  nt->SetBranchStatus("Dpt",1);
  nt->SetBranchStatus("Deta",1);
  nt->SetBranchStatus("Dphi",1);
  nt->SetBranchStatus("Dy",1);
  nt->SetBranchStatus("DtktkRes*",1);
  nt->SetBranchStatus("Dtrk1*",1);
  nt->SetBranchStatus("DRestrk*",1);
}

void SelectHltBranches(TTree* nthlt)
{
  nthlt->SetBranchStatus("*",0);
  nthlt->SetBranchStatus("HLT_L1MinimumBiasHF1OR_part*",1);
}
