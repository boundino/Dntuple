// vim:set ts=4 sw=4 fdm=marker et:
using namespace std;
#include "format_float.h"

void beforeNafterFit(TrackInfoBranches *TrackInfo, DInfoBranches *DInfo, TH1F* htkptdif)
{
  for(int j=0;j<DInfo->size;j++)
    {
      if(DInfo->type[j]==11||DInfo->type[j]==12)
        {
          htkptdif->Fill((TrackInfo->pt[DInfo->tktkRes_rftk1_index[j]]-DInfo->tktkRes_rftk1_pt[j])/DInfo->tktkRes_rftk1_pt[j]);
          htkptdif->Fill((TrackInfo->pt[DInfo->tktkRes_rftk2_index[j]]-DInfo->tktkRes_rftk2_pt[j])/DInfo->tktkRes_rftk2_pt[j]);
          htkptdif->Fill((TrackInfo->pt[DInfo->tktkRes_rftk3_index[j]]-DInfo->tktkRes_rftk3_pt[j])/DInfo->tktkRes_rftk1_pt[j]);
          htkptdif->Fill((TrackInfo->pt[DInfo->tktkRes_rftk4_index[j]]-DInfo->tktkRes_rftk4_pt[j])/DInfo->tktkRes_rftk1_pt[j]);
        }
    }
}

void debugcomb(TrackInfoBranches *TrackInfo, DInfoBranches *DInfo, GenInfoBranches *GenInfo)
{
  //
  for(int k=0;k<GenInfo->size;k++)
    {
      if(abs(GenInfo->pdgId[k])==421 && GenInfo->nDa[k]>=4 && GenInfo->mo1[k]>-1)
        {
          if(abs(GenInfo->pdgId[GenInfo->mo1[k]])==413 && GenInfo->da1[k]>-1 && GenInfo->da2[k]>-1 && GenInfo->da3[k]>-1 && GenInfo->da4[k]>-1)
            {
              if(GenInfo->nDa[k]==4&&abs(GenInfo->pdgId[GenInfo->da1[k]])==321&&abs(GenInfo->pdgId[GenInfo->da2[k]])==211&&abs(GenInfo->pdgId[GenInfo->da3[k]])==211&&abs(GenInfo->pdgId[GenInfo->da4[k]])==211) continue;
              cout<<setiosflags(ios::left)<<" -- GEN D0's nDa "<<setw(4)<<GenInfo->nDa[k]<<": ";
              cout<<setiosflags(ios::left)<<setw(6)<<GenInfo->pdgId[GenInfo->da1[k]];
              cout<<setiosflags(ios::left)<<setw(6)<<GenInfo->pdgId[GenInfo->da2[k]];
              cout<<setiosflags(ios::left)<<setw(6)<<GenInfo->pdgId[GenInfo->da3[k]];
              cout<<setiosflags(ios::left)<<setw(6)<<GenInfo->pdgId[GenInfo->da4[k]];
              cout<<endl;
            }
        }
    }
}

void debug(TrackInfoBranches *TrackInfo, DInfoBranches *DInfo, GenInfoBranches *GenInfo, Bool_t skimclosest=true)
{
  //
  Float_t genpt=0;
  for(int k=0;k<GenInfo->size;k++)
    {
      if(abs(GenInfo->pdgId[k])==421 && GenInfo->nDa[k]==4 && GenInfo->mo1[k]>-1)
        {
          if(abs(GenInfo->pdgId[GenInfo->mo1[k]])==413 && GenInfo->da1[k]>-1 && GenInfo->da2[k]>-1 && GenInfo->da3[k]>-1 && GenInfo->da4[k]>-1)
            {
              if(abs(GenInfo->pdgId[GenInfo->da1[k]])==321 && abs(GenInfo->pdgId[GenInfo->da2[k]])==211 && abs(GenInfo->pdgId[GenInfo->da3[k]])==211 && abs(GenInfo->pdgId[GenInfo->da4[k]])==211)
                {
                  genpt = GenInfo->pt[k];
                  cout<<setiosflags(ios::left)<<" -- GEN D0 "<<setw(4)<<k<<": ";
                  cout<<setiosflags(ios::left)<<setiosflags(ios::fixed)<<setprecision(4)<<setw(8)<<GenInfo->pt[k];
                  cout<<setiosflags(ios::left)<<setiosflags(ios::fixed)<<setprecision(4)<<setw(8)<<GenInfo->eta[k];
                  cout<<setiosflags(ios::left)<<setiosflags(ios::fixed)<<setprecision(4)<<setw(8)<<GenInfo->phi[k];
                  cout<<setiosflags(ios::left)<<"| ";
                  cout<<setiosflags(ios::left)<<setw(3)<<GenInfo->da1[k]<<setiosflags(ios::fixed)<<setprecision(4)<<"("<<setw(8)<<GenInfo->pt[GenInfo->da1[k]]<<setw(8)<<GenInfo->eta[GenInfo->da1[k]]<<setw(8)<<GenInfo->phi[GenInfo->da1[k]]<<") ";
                  cout<<setiosflags(ios::left)<<setw(3)<<GenInfo->da2[k]<<setiosflags(ios::fixed)<<setprecision(4)<<"("<<setw(8)<<GenInfo->pt[GenInfo->da2[k]]<<setw(8)<<GenInfo->eta[GenInfo->da2[k]]<<setw(8)<<GenInfo->phi[GenInfo->da2[k]]<<") ";
                  cout<<setiosflags(ios::left)<<setw(3)<<GenInfo->da3[k]<<setiosflags(ios::fixed)<<setprecision(4)<<"("<<setw(8)<<GenInfo->pt[GenInfo->da3[k]]<<setw(8)<<GenInfo->eta[GenInfo->da3[k]]<<setw(8)<<GenInfo->phi[GenInfo->da3[k]]<<") ";
                  cout<<setiosflags(ios::left)<<setw(3)<<GenInfo->da4[k]<<setiosflags(ios::fixed)<<setprecision(4)<<"("<<setw(8)<<GenInfo->pt[GenInfo->da4[k]]<<setw(8)<<GenInfo->eta[GenInfo->da4[k]]<<setw(8)<<GenInfo->phi[GenInfo->da4[k]]<<")";
                  cout<<endl;
                }
            }
        }
    }
  if(genpt==0)
    {
      cout<<"    No GEN D0 from 5prong D*"<<endl;
    }
  else
    {
      Int_t countDstar=0,countDstarclosest=0;
      for(int j=0;j<DInfo->size;j++)
        {
          if(DInfo->type[j]==11||DInfo->type[j]==12)
            {
              countDstar++;
              //if(skimclosest && abs(DInfo->tktkRes_pt[j]-genpt)>1.) continue;
              //countDstarclosest++;
              if(TrackInfo->geninfo_index[DInfo->tktkRes_rftk1_index[j]]==0) cout<<TrackInfo->size<<endl;
              cout<<setiosflags(ios::left)<<"    RECOD0 "<<setw(4)<<j<<": ";
              cout<<setiosflags(ios::left)<<setiosflags(ios::fixed)<<setprecision(4)<<setw(8)<<DInfo->tktkRes_pt[j];
              cout<<setiosflags(ios::left)<<setiosflags(ios::fixed)<<setprecision(4)<<setw(8)<<DInfo->tktkRes_eta[j];
              cout<<setiosflags(ios::left)<<setiosflags(ios::fixed)<<setprecision(4)<<setw(8)<<DInfo->tktkRes_phi[j];
              cout<<setiosflags(ios::left)<<"| ";
              cout<<setiosflags(ios::left)<<setw(3)<<TrackInfo->geninfo_index[DInfo->tktkRes_rftk1_index[j]]<<setiosflags(ios::fixed)<<setprecision(4)<<"("<<setw(8)<<TrackInfo->pt[DInfo->tktkRes_rftk1_index[j]]<<setw(8)<<TrackInfo->eta[DInfo->tktkRes_rftk1_index[j]]<<setw(8)<<TrackInfo->phi[DInfo->tktkRes_rftk1_index[j]]<<") ";
              cout<<setiosflags(ios::left)<<setw(3)<<TrackInfo->geninfo_index[DInfo->tktkRes_rftk2_index[j]]<<setiosflags(ios::fixed)<<setprecision(4)<<"("<<setw(8)<<TrackInfo->pt[DInfo->tktkRes_rftk2_index[j]]<<setw(8)<<TrackInfo->eta[DInfo->tktkRes_rftk2_index[j]]<<setw(8)<<TrackInfo->phi[DInfo->tktkRes_rftk2_index[j]]<<") ";
              cout<<setiosflags(ios::left)<<setw(3)<<TrackInfo->geninfo_index[DInfo->tktkRes_rftk3_index[j]]<<setiosflags(ios::fixed)<<setprecision(4)<<"("<<setw(8)<<TrackInfo->pt[DInfo->tktkRes_rftk3_index[j]]<<setw(8)<<TrackInfo->eta[DInfo->tktkRes_rftk3_index[j]]<<setw(8)<<TrackInfo->phi[DInfo->tktkRes_rftk3_index[j]]<<") ";
              cout<<setiosflags(ios::left)<<setw(3)<<TrackInfo->geninfo_index[DInfo->tktkRes_rftk4_index[j]]<<setiosflags(ios::fixed)<<setprecision(4)<<"("<<setw(8)<<TrackInfo->pt[DInfo->tktkRes_rftk4_index[j]]<<setw(8)<<TrackInfo->eta[DInfo->tktkRes_rftk4_index[j]]<<setw(8)<<TrackInfo->phi[DInfo->tktkRes_rftk4_index[j]]<<") ";
              cout<<setiosflags(ios::left)<<"| ";
              cout<<setiosflags(ios::left)<<setw(3)<<DInfo->tktkRes_rftk1_index[j];
              cout<<setiosflags(ios::left)<<setw(3)<<DInfo->tktkRes_rftk2_index[j];
              cout<<setiosflags(ios::left)<<setw(3)<<DInfo->tktkRes_rftk3_index[j];
              cout<<setiosflags(ios::left)<<setw(3)<<DInfo->tktkRes_rftk4_index[j];
              cout<<endl;
              cout<<setw(43)<<" ";
              cout<<setiosflags(ios::left)<<setw(3)<<TrackInfo->geninfo_index[DInfo->tktkRes_rftk1_index[j]]<<setiosflags(ios::fixed)<<setprecision(4)<<"("<<setw(8)<<DInfo->tktkRes_rftk1_pt[j]<<setw(8)<<DInfo->tktkRes_rftk1_eta[j]<<setw(8)<<DInfo->tktkRes_rftk1_phi[j]<<") ";
              cout<<setiosflags(ios::left)<<setw(3)<<TrackInfo->geninfo_index[DInfo->tktkRes_rftk2_index[j]]<<setiosflags(ios::fixed)<<setprecision(4)<<"("<<setw(8)<<DInfo->tktkRes_rftk2_pt[j]<<setw(8)<<DInfo->tktkRes_rftk2_eta[j]<<setw(8)<<DInfo->tktkRes_rftk2_phi[j]<<") ";
              cout<<setiosflags(ios::left)<<setw(3)<<TrackInfo->geninfo_index[DInfo->tktkRes_rftk3_index[j]]<<setiosflags(ios::fixed)<<setprecision(4)<<"("<<setw(8)<<DInfo->tktkRes_rftk3_pt[j]<<setw(8)<<DInfo->tktkRes_rftk3_eta[j]<<setw(8)<<DInfo->tktkRes_rftk3_phi[j]<<") ";
              cout<<setiosflags(ios::left)<<setw(3)<<TrackInfo->geninfo_index[DInfo->tktkRes_rftk4_index[j]]<<setiosflags(ios::fixed)<<setprecision(4)<<"("<<setw(8)<<DInfo->tktkRes_rftk4_pt[j]<<setw(8)<<DInfo->tktkRes_rftk4_eta[j]<<setw(8)<<DInfo->tktkRes_rftk4_phi[j]<<") ";
              cout<<endl;
            }
        }
      if(countDstar==0) cout<<"    No reco 5-prong D*"<<endl;
      //else if(countDstarclosest==0) cout<<"    No close reco D0"<<endl;
      //
    }
}

double findMass(int particlePdgId)
{
  if(TMath::Abs(particlePdgId)==211) return PION_MASS;
  if(TMath::Abs(particlePdgId)==321) return KAON_MASS;
  else
    {
      cout<<"ERROR: find particle mass falied >> Particle pdgId: "<<particlePdgId<<endl;
      return 0;
    }
}

int findPdgid(Double_t tkmass)
{
  if(TMath::Abs(tkmass-KAON_MASS)<0.1) return KAON_PDGID;
  else if(TMath::Abs(tkmass-PION_MASS)<0.1) return PION_PDGID;
  else
    {
      cout<<"ERROR: find particle pdgid falied >> Particle mass: "<<tkmass<<endl;
      return 0;
    }
}
