using namespace std;
#include "skimTree.h"

int skimTree(TString ifname="oldtree.root",
	     TString ofname="newtree.root",
	     Bool_t skimbranch=true)
{
  cout<<endl;
  cout<<" -- Checking if input and output files are same"<<endl;
  if(ifname==ofname)
    {
      cout<<"    Error: Input file will be overwritten."<<endl;
      return 0;
    }
  TFile* inf = TFile::Open(ifname);
  TTree* ntDD0kpipi = (TTree*)inf->Get("ntDD0kpipi");
  TTree* ntDD0kpipipipi = (TTree*)inf->Get("ntDD0kpipipipi");
  TTree* ntHlt = (TTree*)inf->Get("ntHlt");

  Int_t Dsize_ntDD0kpipi;      ntDD0kpipi->SetBranchAddress("Dsize",&Dsize_ntDD0kpipi);
  Int_t Dsize_ntDD0kpipipipi;  ntDD0kpipipipi->SetBranchAddress("Dsize",&Dsize_ntDD0kpipipipi);

  if(skimbranch)
    {
      SelectRecoBranches(ntDD0kpipi);
      SelectRecoBranches(ntDD0kpipipipi);
      SelectHltBranches(ntHlt);
    }
  TFile* outf = new TFile(ofname,"recreate");
  TTree* ntDD0kpipi_new = ntDD0kpipi->CloneTree(0);
  TTree* ntDD0kpipipipi_new = ntDD0kpipipipi->CloneTree(0);
  TTree* ntHlt_new = ntHlt->CloneTree(0);

  cout<<" -- Check evt no. for three trees"<<endl;
  cout<<"    "<<ntDD0kpipi->GetEntries()<<", "<<ntDD0kpipipipi->GetEntries()<<", "<<ntHlt->GetEntries()<<endl;
  if(ntDD0kpipi->GetEntries()!=ntDD0kpipipipi->GetEntries()||ntDD0kpipipipi->GetEntries()!=ntHlt->GetEntries())
    {
      cout<<"    Error: Event numbers are different in three trees."<<endl;
      return 0;
    }
  Long64_t nentries = ntDD0kpipi->GetEntries();

  cout<<" -- Event reading"<<endl;
  for(Long64_t i=0;i<nentries;i++)
    {
      if(i%100000==0) cout<<setiosflags(ios::left)<<"    "<<setw(8)<<i<<" / "<<nentries<<endl;
      ntDD0kpipi->GetEntry(i);
      ntDD0kpipipipi->GetEntry(i);
      ntHlt->GetEntry(i);
      if(Dsize_ntDD0kpipi>0||Dsize_ntDD0kpipipipi>0)
	{
	  ntDD0kpipi_new->Fill();
	  ntDD0kpipipipi_new->Fill();
	  ntHlt_new->Fill(); 
	} 
    }
  outf->Write();
  cout<<" -- Writing new trees done"<<endl;
  outf->Close();

  return 1;  
}

int main(int argc, char *argv[])
{
  if(argc==3)
    {
      skimTree(argv[1], argv[2]);
      return 1;
    }
  else
    {
      std::cout<<"Error: invalid parameter number."<<std::endl;
      return 0;
    }
}
