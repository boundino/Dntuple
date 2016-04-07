using namespace std;
#include "uti.h"

void printoutAN(TString collsyst="PP")
{
  Float_t ptmin[nbins],ptmax[nbins];
  Float_t tmp;

  ifstream fin_defaultnew(Form("outYield/defaultnew_%s.dat",collsyst.Data()));  Float_t yield_defaultnew[nbins];
  for(int i=0;i<nbins;i++)
    {
      fin_defaultnew>>ptmin[i];
      fin_defaultnew>>ptmax[i];
      fin_defaultnew>>yield_defaultnew[i];
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

  ifstream fin_increasewid(Form("outYield/increasewid_%s.dat",collsyst.Data()));  Float_t yield_increasewid[nbins];
  for(int i=0;i<nbins;i++)
    {
      fin_increasewid>>tmp;
      fin_increasewid>>tmp;
      fin_increasewid>>yield_increasewid[i];
    }

  ifstream fin_decreasewid(Form("outYield/decreasewid_%s.dat",collsyst.Data()));  Float_t yield_decreasewid[nbins];
  for(int i=0;i<nbins;i++)
    {
      fin_decreasewid>>tmp;
      fin_decreasewid>>tmp;
      fin_decreasewid>>yield_decreasewid[i];
    }

  cout<<endl;
  cout<<"Background pdf variation - "<<collsyst<<endl;
  for(int i=0;i<nbins;i++)
    {
      cout<<"\\hline"<<endl;
      cout<<setiosflags(ios::fixed)<<setprecision(0)<<ptmin[i]<<"$-$"<<ptmax[i]<<" & "<<yield_defaultnew[i]<<" & "<<yield_poly2[i]<<" & "<<yield_expo2[i]<<" & ";
      Float_t diffmax = (fabs(yield_poly2[i]-yield_defaultnew[i])>fabs(yield_expo2[i]-yield_defaultnew[i]))?fabs(yield_poly2[i]-yield_defaultnew[i]):fabs(yield_expo2[i]-yield_defaultnew[i]);
      cout<<setiosflags(ios::fixed)<<setprecision(1)<<(diffmax*100./yield_defaultnew[i])<<" \\\\"<<endl;
    }
  cout<<"\\hline"<<endl;

  cout<<endl;
  cout<<"Signal pdf variation - "<<collsyst<<endl;
  for(int i=0;i<nbins;i++)
    {
      cout<<"\\hline"<<endl;
      cout<<setiosflags(ios::fixed)<<setprecision(0)<<ptmin[i]<<"$-$"<<ptmax[i]<<" & "<<yield_defaultnew[i]<<" & "<<yield_increasewid[i]<<" & "<<yield_decreasewid[i]<<" & ";
      Float_t diffmax = (fabs(yield_increasewid[i]-yield_defaultnew[i])>fabs(yield_decreasewid[i]-yield_defaultnew[i]))?fabs(yield_increasewid[i]-yield_defaultnew[i]):fabs(yield_decreasewid[i]-yield_defaultnew[i]);
      cout<<setiosflags(ios::fixed)<<setprecision(1)<<(diffmax*100./yield_defaultnew[i])<<" \\\\"<<endl;
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
