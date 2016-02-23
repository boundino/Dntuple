using namespace std;
#include <fstream>
#include <iostream>
#define FLE_NUM 16

void resubmit_filename()
{
  int ofname[FLE_NUM];
  for(int i=0;i<FLE_NUM;i++) ofname[i]=0;
  int ifname[FLE_NUM];
  for(int i=0;i<FLE_NUM;i++) ifname[i]=0;

  ifstream flist("MBflist/MB19_v2.dat");
  if(!flist) cout<<"Error"<<endl;
  for(int i=0;i<FLE_NUM;i++)
    {
      flist>>ofname[i];
      flist>>ifname[i];
    }

  cout<<"input"<<endl;
  for(int i=0;i<FLE_NUM;i++) cout<<ifname[i]<<" ";
  cout<<endl;
  cout<<"output"<<endl;
  for(int i=0;i<FLE_NUM;i++) cout<<ofname[i]<<" ";
  cout<<endl;
  cout<<endl;
}
