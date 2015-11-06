#include <TTree.h>
#define MAX_XB 16384
#define MAX_GEN 8192
Int_t DZERO_PDGID = 421;

Int_t      Dsize;
Int_t      hiBin;
Double_t   Dpt[MAX_XB];
Double_t   Dy[MAX_XB];
Double_t   Dchi2cl[MAX_XB];
Double_t   Dalpha[MAX_XB];
Double_t   DsvpvDistance[MAX_XB];
Double_t   DsvpvDisErr[MAX_XB];
Double_t   Dgen[MAX_XB];

void setrecoBranch(TTree* dnt)
{
  dnt->SetBranchAddress("Dsize",&Dsize);
  dnt->SetBranchAddress("hiBin",&hiBin);
  dnt->SetBranchAddress("Dpt",Dpt);
  dnt->SetBranchAddress("Dy",Dy);
  dnt->SetBranchAddress("Dchi2cl",Dchi2cl);
  dnt->SetBranchAddress("Dalpha",Dalpha);
  dnt->SetBranchAddress("DsvpvDistance",DsvpvDistance);
  dnt->SetBranchAddress("DsvpvDisErr",DsvpvDisErr);
  dnt->SetBranchAddress("Dgen",Dgen);
}

Int_t     Gsize;
Double_t  Gpt[MAX_GEN];
Double_t  GpdgId[MAX_GEN];
Int_t     GisSignal[MAX_GEN];

void setgenBranch(TTree* nt)
{
  nt->SetBranchAddress("Gsize",&Gsize);
  nt->SetBranchAddress("Gpt",Gpt);
  nt->SetBranchAddress("GpdgId",GpdgId);
  nt->SetBranchAddress("GisSignal",GisSignal);
}
