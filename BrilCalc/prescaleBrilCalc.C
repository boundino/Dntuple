using namespace std;
#include "uti.h"

void prescaleBrilCalc(TString inputMB, Float_t unprescale, Float_t unprescaleMB, TString eventfilter, Int_t isPbPb)
{
  TString tPbPb = (isPbPb>0)?"PbPb":"pp";
  cout<<"  -- Calculating lumi of "<<tPbPb<<endl;

  Double_t prescaleMB = unprescaleMB/unprescale;
  
  TFile* f = new TFile(inputMB);
  TTree* ntDkpi = (TTree*)f->Get("ntDkpi");
  ntDkpi->AddFriend("ntSkim");
  ntDkpi->AddFriend("ntHlt");
  ntDkpi->AddFriend("ntHi");
 
  TH1F* hcountsMB0100 = new TH1F("hcountsMB0100","",100,-2,2);
  TH1F* hcountsMB010 = new TH1F("hcountsMB010","",100,-2,2);
  
  //0-100%
  cout<<"  -- Processing 0-100%"<<endl;
  ntDkpi->Draw("1>>hcountsMB0100",Form("%s&&hiBin<180",eventfilter.Data()));
  Double_t ncountsMB0100 = hcountsMB0100->GetEntries()*10/9;
  cout<<"   - Number of MB events (0-90%): "<<ncountsMB0100<<endl;

  Double_t TAA0100 = 392.4/(70.*1e9);
  Double_t lumiMB0100 = TAA0100*ncountsMB0100;
  Double_t lumiHighpt0100 = lumiMB0100/prescaleMB;
  
  cout<<"   - Luminosity brilcalc low pt: "<<lumiMB0100<<endl;
  cout<<"   - Luminosity brilcalc high pt: "<<lumiHighpt0100<<endl;
  
  //0-10%
  cout<<"  -- Processing 0-10%"<<endl;  
  ntDkpi->Draw("1>>hcountsMB010",Form("%s&&hiBin<20",eventfilter.Data()));
  Double_t ncountsMB010 = hcountsMB010->GetEntries();
  cout<<"   - Number of MB events (0-10%): "<<ncountsMB010<<endl;
  
  Double_t TAA010 = (23.2/1e9);
  Double_t lumiMB010 = TAA010*ncountsMB010;
  Double_t lumiHighpt010 = lumiMB010/prescaleMB;      

  cout<<"   - Luminosity brilcalc low pt: "<<lumiMB010<<endl;
  cout<<"   - Luminosity brilcalc high pt: "<<lumiHighpt010<<endl;
}

int main(int argc, char* argv[])
{
  if(argc==6)
    {
      prescaleBrilCalc(argv[1],atof(argv[2]),atof(argv[3]),argv[4],atoi(argv[5]));
      return 0;
    }
  else
    {
      cout<<"  Error: Invalid parameters number"<<endl;
    }
}

