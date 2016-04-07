using namespace std;
#include "uti.h"

void printoutAN(TString collsyst="PP")
{
  Float_t ptmin[nbins],ptmax[nbins];
  Float_t tmp;

  ifstream fin_default(Form("outYield/default_%s.dat",collsyst.Data()));  Float_t yield_default[nbins];
  for(int i=0;i<nbins;i++)
    {
      fin_default>>ptmin[i];
      fin_default>>ptmax[i];
      fin_default>>yield_default[i];
    }

  ifstream fin_expo2(Form("outYield/expo2_%s.dat",collsyst.Data()));  Float_t yield_expo2[nbins];
  for(int i=0;i<nbins;i++)
    {
      fin_expo2>>tmp;
      fin_expo2>>tmp;
      fin_expo2>>yield_expo2[i];
    }

  ifstream fin_poly2(Form("outYield/poly2_%s.dat",collsyst.Data()));  Float_t yield_poly2[nbins];
  for(int i=0;i<nbins;i++)
    {
      fin_poly2>>tmp;
      fin_poly2>>tmp;
      fin_poly2>>yield_poly2[i];
    }

  ifstream fin_floatwid(Form("outYield/floatwid_%s.dat",collsyst.Data()));  Float_t yield_floatwid[nbins];
  for(int i=0;i<nbins;i++)
    {
      fin_floatwid>>tmp;
      fin_floatwid>>tmp;
      fin_floatwid>>yield_floatwid[i];
    }

  cout<<endl;
  cout<<"Background pdf variation - "<<collsyst<<endl;
  for(int i=0;i<nbins;i++)
    {
      cout<<"\\hline"<<endl;
      cout<<setiosflags(ios::fixed)<<setprecision(0)<<ptmin[i]<<"$-$"<<ptmax[i]<<" & "<<yield_default[i]<<" & "<<yield_poly2[i]<<" & "<<yield_expo2[i]<<" & ";
      Float_t diffmax = (fabs(yield_poly2[i]-yield_default[i])>fabs(yield_expo2[i]-yield_default[i]))?fabs(yield_poly2[i]-yield_default[i]):fabs(yield_expo2[i]-yield_default[i]);
      cout<<setiosflags(ios::fixed)<<setprecision(1)<<(diffmax*100./yield_default[i])<<" \\\\"<<endl;
    }
  cout<<"\\hline"<<endl;

  cout<<endl;
  cout<<"Signal pdf variation - "<<collsyst<<endl;
  for(int i=0;i<nbins;i++)
    {
      cout<<"\\hline"<<endl;
      cout<<setiosflags(ios::fixed)<<setprecision(0)<<ptmin[i]<<"$-$"<<ptmax[i]<<" & "<<yield_default[i]<<" & "<<yield_floatwid[i]<<" & ";
      Float_t diffmax = fabs(yield_floatwid[i]-yield_default[i]);
      cout<<setiosflags(ios::fixed)<<setprecision(1)<<(diffmax*100./yield_default[i])<<" \\\\"<<endl;
    }
  cout<<"\\hline"<<endl;

}

int main(int argc, char *argv[])
{
  if(argc!=2)
    {
      std::cout << "Wrong number of inputs" << std::endl;
      return 1;
    }
  else 
    {
      printoutAN(argv[1]);
      return 0;
    }
}
