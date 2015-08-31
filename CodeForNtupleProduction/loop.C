#include <TTree.h>
#include <TFile.h>
#include <TChain.h>
#include <TMath.h>
#include <TString.h>
#include <TNtuple.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <iostream>
#include <cmath>
#include "loop.h"

#define MUON_MASS   0.10565837
#define PION_MASS   0.13957018
#define KAON_MASS   0.493677
#define KSHORT_MASS 0.497614
#define KSTAR_MASS  0.89594
#define PHI_MASS    1.019455
#define JPSI_MASS   3.096916

Int_t PION_PDGID = 211;
Int_t KAON_PDGID = 321;
Int_t DZERO_PDGID = 421;
Int_t DPLUS_PDGID = 411;
Int_t DSUBS_PDGID = 431;


int loop(TString infile="/mnt/hadoop/cms/store/user/tawei/Dfinder/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/Pyquen_D0tokaonpion_Pt0_D0pt1p0_TuneZ2_Unquenched_2760GeV_step3_20150612_250kevt_20150824_kpi/RECO_150_1_vhm.root", TString outfile="comp.root", bool REAL=false, int startEntries=0)
{
  double findMass(Int_t particlePdgId);
  void fillDTree(TVector3* bP, TVector3* bVtx, TLorentzVector* b4P, Int_t j, Int_t typesize, Bool_t REAL);
  bool isDsignalGen(Int_t Dtype, Int_t j);

  if(REAL) cout<<"--- REAL DATA ---"<<endl;
  else cout<<"--- MC ---"<<endl;
  
  //File type
  TFile *f = new TFile(infile);
  TTree *root = (TTree*)f->Get("demo/root");
  TFile *outf = new TFile(outfile,"recreate");
  setBranch(root);

  int isDchannel[5];
  isDchannel[0] = 1; //
  isDchannel[1] = 0; //
  isDchannel[2] = 0; //
  isDchannel[3] = 0; //
  isDchannel[4] = 0; //

  cout<<"--- Building trees ---"<<endl;
  TTree* ntD1 = new TTree("ntDkPpiM","");       buildDBranch(ntD1);
  TTree* ntD2 = new TTree("ntDkMpiP","");       buildDBranch(ntD2);
  TTree* ntD3 = new TTree("ntDkMpiPpiP","");    buildDBranch(ntD3);
  TTree* ntD4 = new TTree("ntDkPpiMpiM","");    buildDBranch(ntD4);
  TTree* ntD5 = new TTree("ntkMpiPpiPpiM","");  buildDBranch(ntD5);
  TTree* ntGen = new TTree("ntGen","");         buildGenBranch(ntGen);
  cout<<"--- Building trees finished ---"<<endl;

  Long64_t nentries = root->GetEntries();
  //nentries = 10000;
  Long64_t nbytes = 0;
  TVector3* bP = new TVector3;
  TVector3* bVtx = new TVector3;
  TLorentzVector* b4P = new TLorentzVector;
  TLorentzVector* bGen = new TLorentzVector;

  Int_t itest=0;
  for (int i=startEntries;i<nentries;i++)
    {
      nbytes += root->GetEntry(i);
      if (i%10000==0) cout <<i<<" / "<<nentries<<endl;
      Int_t Dtypesize[5]={0,0,0,0,0};
      Double_t Dbest=0;
      Int_t Dbestindex=0;
      for(int t=0;t<5;t++)
	{
	  Dsize=0;
	  if(isDchannel[t]==1)
	    {
	      Dbest=-1;
	      Dbestindex=-1;
	      for(int j=0;j<DInfo_size;j++)
		{
		  if(DInfo_type[j]==(t+1))
		    {
		      fillDTree(bP,bVtx,b4P,j,Dtypesize[t],REAL);
		      if(Dchi2cl[Dtypesize[t]]>Dbest)
		      	{
		      	  Dbest = Dchi2cl[Dtypesize[t]];
		      	  Dbestindex = Dtypesize[t];
		      	}
		      Dtypesize[t]++;
		    }
		}
	      if(Dbestindex>-1)
	      	{
	      	  Disbestchi2[Dbestindex] = true;
	      	}
	      if(t==0) ntD1->Fill();
	      else if(t==1) ntD2->Fill();
	      else if(t==2) ntD3->Fill();
	      else if(t==3) ntD4->Fill();
	      else if(t==4) ntD5->Fill();
	    }
	}

      if(!REAL)
	{
	  Int_t gt=0,sigtype=0;
	  Gsize = GenInfo_size;
	  for(int j=0;j<GenInfo_size;j++)
	    {
	      Gpt[j] = GenInfo_pt[j];
	      Geta[j] = GenInfo_eta[j];
	      Gphi[j] = GenInfo_phi[j];
	      GpdgId[j] = GenInfo_pdgId[j];
	      bGen->SetPtEtaPhiM(GenInfo_pt[j],GenInfo_eta[j],GenInfo_phi[j],GenInfo_mass[j]);
	      sigtype=0;
	      for(gt=0;gt<5;gt++)
		{
		  if(isDsignalGen(gt,j))
		    {
		      sigtype=gt;
		      break;
		    }
		}
	      GisSignal[j] = sigtype;
	    }
	  ntGen->Fill();
	}
    }

  cout<<itest<<endl;
  outf->Write();
  outf->Close();
}


double findMass(Int_t particlePdgId)
{
  if(TMath::Abs(particlePdgId)==211) return PION_MASS;
  if(TMath::Abs(particlePdgId)==321) return KAON_MASS;
  else
    {
      cout<<"ERROR: find particle mass falied >> Particle pdgId: "<<particlePdgId<<endl;
      return 0;
    }
}

void fillDTree(TVector3* bP, TVector3* bVtx, TLorentzVector* b4P, Int_t j, Int_t typesize, Bool_t REAL)
{
  //EvtInfo
  RunNo = EvtInfo_RunNo;
  EvtNo = EvtInfo_EvtNo;
  Dsize = typesize+1;
  PVx = EvtInfo_PVx;
  PVy = EvtInfo_PVy;
  PVz = EvtInfo_PVz;
  PVxE = EvtInfo_PVxE;
  PVyE = EvtInfo_PVyE;
  PVzE = EvtInfo_PVzE;
  PVnchi2 = EvtInfo_PVnchi2;
  PVchi2 = EvtInfo_PVchi2;
  //DInfo
  bP->SetXYZ(DInfo_px[j],DInfo_py[j],DInfo_pz[j]*0);
  bVtx->SetXYZ(DInfo_vtxX[j]-EvtInfo_PVx,
	       DInfo_vtxY[j]-EvtInfo_PVy,
	       DInfo_vtxZ[j]*0-EvtInfo_PVz*0);
  b4P->SetXYZM(DInfo_px[j],DInfo_py[j],DInfo_pz[j],DInfo_mass[j]);
  Dindex[typesize] = typesize;
  DisGoodCand[typesize] = DInfo_isGoodCand[j];
  Dmass[typesize] = DInfo_mass[j];
  Dpt[typesize] = DInfo_pt[j];
  Deta[typesize] = DInfo_eta[j];
  Dphi[typesize] = DInfo_phi[j];
  Dy[typesize] = b4P->Rapidity();
  DvtxX[typesize] = DInfo_vtxX[j] - EvtInfo_PVx;
  DvtxY[typesize] = DInfo_vtxY[j] - EvtInfo_PVy;
  Dd0[typesize] = TMath::Sqrt((DInfo_vtxX[j]-EvtInfo_PVx)*(DInfo_vtxX[j]-EvtInfo_PVx)+(DInfo_vtxY[j]-EvtInfo_PVy)*(DInfo_vtxY[j]-EvtInfo_PVy));
  Dd0Err[typesize] = TMath::Sqrt(DInfo_vtxXE[j]*DInfo_vtxXE[j]+DInfo_vtxYE[j]*DInfo_vtxYE[j]);
  Dchi2ndf[typesize] = DInfo_vtxchi2[j]/DInfo_vtxdof[j];
  Dchi2cl[typesize] = TMath::Prob(DInfo_vtxchi2[j],DInfo_vtxdof[j]);
  Ddtheta[typesize] = bP->Angle(*bVtx);
  Dlxy[typesize] = ((DInfo_vtxX[j]-EvtInfo_PVx)*DInfo_px[j] + (DInfo_vtxY[j]-EvtInfo_PVy)*DInfo_py[j])/DInfo_pt[j];
  Disbestchi2[typesize] = false;
  //DInfo.b4fitInfo
  Db4fit_mass[typesize] = DInfo_b4fit_mass[j];
  Db4fit_pt[typesize] = DInfo_b4fit_pt[j];
  Db4fit_eta[typesize] = DInfo_b4fit_eta[j];
  Db4fit_phi[typesize] = DInfo_b4fit_phi[j];
  //DInfo.trkInfo
  Double_t trk1mass,trk2mass,trk3mass,trk4mass;
  Dtrk1Pt[typesize] = TrackInfo_pt[DInfo_rftk1_index[j]];
  Dtrk2Pt[typesize] = TrackInfo_pt[DInfo_rftk2_index[j]];
  Dtrk1Eta[typesize] = TrackInfo_eta[DInfo_rftk1_index[j]];
  Dtrk2Eta[typesize] = TrackInfo_eta[DInfo_rftk2_index[j]];
  Dtrk1Phi[typesize] = TrackInfo_phi[DInfo_rftk1_index[j]];
  Dtrk2Phi[typesize] = TrackInfo_phi[DInfo_rftk2_index[j]];
  trk1mass = findMass(DInfo_rftk1_MassHypo[j]);
  trk2mass = findMass(DInfo_rftk2_MassHypo[j]);
  b4P->SetPtEtaPhiM(TrackInfo_pt[DInfo_rftk1_index[j]],TrackInfo_eta[DInfo_rftk1_index[j]],TrackInfo_phi[DInfo_rftk1_index[j]],trk1mass);
  Dtrk1Y[typesize] = b4P->Rapidity();
  b4P->SetPtEtaPhiM(TrackInfo_pt[DInfo_rftk2_index[j]],TrackInfo_eta[DInfo_rftk2_index[j]],TrackInfo_phi[DInfo_rftk2_index[j]],trk2mass);
  Dtrk2Y[typesize] = b4P->Rapidity();
  Dtrk1Dxy[typesize] = TrackInfo_dxyPV[DInfo_rftk1_index[j]];
  Dtrk2Dxy[typesize] = TrackInfo_dxyPV[DInfo_rftk2_index[j]];
  Dtrk1D0Err[typesize] = TrackInfo_d0error[DInfo_rftk1_index[j]];
  Dtrk2D0Err[typesize] = TrackInfo_d0error[DInfo_rftk2_index[j]];
  Dtrk1PixelHit[typesize] = TrackInfo_pixelhit[DInfo_rftk1_index[j]];
  Dtrk2PixelHit[typesize] = TrackInfo_pixelhit[DInfo_rftk2_index[j]];
  Dtrk1StripHit[typesize] = TrackInfo_striphit[DInfo_rftk1_index[j]];
  Dtrk2StripHit[typesize] = TrackInfo_striphit[DInfo_rftk2_index[j]];
  Dtrk1nPixelLayer[typesize] = TrackInfo_nPixelLayer[DInfo_rftk1_index[j]];
  Dtrk2nPixelLayer[typesize] = TrackInfo_nPixelLayer[DInfo_rftk2_index[j]];
  Dtrk1nStripLayer[typesize] = TrackInfo_nStripLayer[DInfo_rftk1_index[j]];
  Dtrk2nStripLayer[typesize] = TrackInfo_nStripLayer[DInfo_rftk2_index[j]];
  Dtrk1Chi2ndf[typesize] = TrackInfo_chi2[DInfo_rftk1_index[j]]/TrackInfo_ndf[DInfo_rftk1_index[j]];
  Dtrk2Chi2ndf[typesize] = TrackInfo_chi2[DInfo_rftk2_index[j]]/TrackInfo_ndf[DInfo_rftk2_index[j]];
  Dtrk1MassHypo[typesize] = DInfo_rftk1_MassHypo[j];
  Dtrk2MassHypo[typesize] = DInfo_rftk2_MassHypo[j];
  if(DInfo_type[j]==1||DInfo_type[j]==2)
    {
      Dtrk3Pt[typesize] = -1;
      Dtrk4Pt[typesize] = -1;
      Dtrk3Eta[typesize] = -20;
      Dtrk4Eta[typesize] = -20;
      Dtrk3Phi[typesize] = -20;
      Dtrk4Phi[typesize] = -20;
      Dtrk3Y[typesize] = -1;
      Dtrk4Y[typesize] = -1;
      Dtrk3Dxy[typesize] = -1;
      Dtrk4Dxy[typesize] = -1;
      Dtrk3D0Err[typesize] = -1;
      Dtrk4D0Err[typesize] = -1;
      Dtrk3PixelHit[typesize] = -1;
      Dtrk4PixelHit[typesize] = -1;
      Dtrk3StripHit[typesize] = -1;
      Dtrk4StripHit[typesize] = -1;
      Dtrk1nPixelLayer[typesize] = -1;
      Dtrk2nPixelLayer[typesize] = -1;
      Dtrk1nStripLayer[typesize] = -1;
      Dtrk2nStripLayer[typesize] = -1;
      Dtrk3Chi2ndf[typesize] = -1;
      Dtrk4Chi2ndf[typesize] = -1;
      Dtrk3MassHypo[typesize] = 0;
      Dtrk4MassHypo[typesize] = 0;
      DtktkResmass[typesize] = -1;
      DtktkRespt[typesize] = -1;
      DtktkReseta[typesize] = -20;
      DtktkResphi[typesize] = -20;
    }
  else if(DInfo_type[j]==3||DInfo_type[j]==4)
    {
      Dtrk3Pt[typesize] = TrackInfo_pt[DInfo_rftk3_index[j]];
      Dtrk3Eta[typesize] = TrackInfo_eta[DInfo_rftk3_index[j]];
      Dtrk3Phi[typesize] = TrackInfo_phi[DInfo_rftk3_index[j]];
      trk3mass = findMass(DInfo_rftk3_MassHypo[j]);
      b4P->SetPtEtaPhiM(TrackInfo_pt[DInfo_rftk3_index[j]],TrackInfo_eta[DInfo_rftk3_index[j]],TrackInfo_phi[DInfo_rftk3_index[j]],trk3mass);
      Dtrk3Y[typesize] = b4P->Rapidity();
      Dtrk3Dxy[typesize] = TrackInfo_dxyPV[DInfo_rftk3_index[j]];
      Dtrk3D0Err[typesize] = TrackInfo_d0error[DInfo_rftk3_index[j]];
      Dtrk3PixelHit[typesize] = TrackInfo_pixelhit[DInfo_rftk3_index[j]];
      Dtrk3StripHit[typesize] = TrackInfo_striphit[DInfo_rftk3_index[j]];
      Dtrk3nPixelLayer[typesize] = TrackInfo_nPixelLayer[DInfo_rftk3_index[j]];
      Dtrk3nStripLayer[typesize] = TrackInfo_nStripLayer[DInfo_rftk3_index[j]];
      Dtrk3Chi2ndf[typesize] = TrackInfo_chi2[DInfo_rftk3_index[j]]/TrackInfo_ndf[DInfo_rftk3_index[j]];
      Dtrk3MassHypo[typesize] = DInfo_rftk3_MassHypo[j];
      Dtrk4Pt[typesize] = -1;
      Dtrk4Eta[typesize] = -20;
      Dtrk4Phi[typesize] = -20;
      Dtrk4Y[typesize] = -1;
      Dtrk4Dxy[typesize] = -1;
      Dtrk4D0Err[typesize] = -1;
      Dtrk4PixelHit[typesize] = -1;
      Dtrk4StripHit[typesize] = -1;
      Dtrk4nPixelLayer[typesize] = -1;
      Dtrk4nStripLayer[typesize] = -1;
      Dtrk4Chi2ndf[typesize] = -1;
      Dtrk4MassHypo[typesize] = 0;
      DtktkResmass[typesize] = -1;
      DtktkRespt[typesize] = -1;
      DtktkReseta[typesize] = -20;
      DtktkResphi[typesize] = -20;
    }
  else if(DInfo_type[j]==5)
    {
      Dtrk3Pt[typesize] = TrackInfo_pt[DInfo_rftk3_index[j]];
      Dtrk4Pt[typesize] = TrackInfo_pt[DInfo_rftk4_index[j]];
      Dtrk3Eta[typesize] = TrackInfo_eta[DInfo_rftk3_index[j]];
      Dtrk4Eta[typesize] = TrackInfo_eta[DInfo_rftk4_index[j]];
      Dtrk3Phi[typesize] = TrackInfo_phi[DInfo_rftk3_index[j]];
      Dtrk4Phi[typesize] = TrackInfo_phi[DInfo_rftk4_index[j]];
      trk3mass = findMass(DInfo_rftk3_MassHypo[j]);
      trk4mass = findMass(DInfo_rftk4_MassHypo[j]);
      b4P->SetPtEtaPhiM(TrackInfo_pt[DInfo_rftk3_index[j]],TrackInfo_eta[DInfo_rftk3_index[j]],TrackInfo_phi[DInfo_rftk3_index[j]],trk3mass);
      Dtrk3Y[typesize] = b4P->Rapidity();
      b4P->SetPtEtaPhiM(TrackInfo_pt[DInfo_rftk4_index[j]],TrackInfo_eta[DInfo_rftk4_index[j]],TrackInfo_phi[DInfo_rftk4_index[j]],trk4mass);
      Dtrk4Y[typesize] = b4P->Rapidity();
      Dtrk3Dxy[typesize] = TrackInfo_dxyPV[DInfo_rftk3_index[j]];
      Dtrk4Dxy[typesize] = TrackInfo_dxyPV[DInfo_rftk4_index[j]];
      Dtrk3D0Err[typesize] = TrackInfo_d0error[DInfo_rftk3_index[j]];
      Dtrk4D0Err[typesize] = TrackInfo_d0error[DInfo_rftk4_index[j]];
      Dtrk3PixelHit[typesize] = TrackInfo_pixelhit[DInfo_rftk3_index[j]];
      Dtrk4PixelHit[typesize] = TrackInfo_pixelhit[DInfo_rftk4_index[j]];
      Dtrk3StripHit[typesize] = TrackInfo_striphit[DInfo_rftk3_index[j]];
      Dtrk4StripHit[typesize] = TrackInfo_striphit[DInfo_rftk4_index[j]];
      Dtrk3nPixelLayer[typesize] = TrackInfo_nPixelLayer[DInfo_rftk3_index[j]];
      Dtrk4nPixelLayer[typesize] = TrackInfo_nPixelLayer[DInfo_rftk4_index[j]];
      Dtrk3nStripLayer[typesize] = TrackInfo_nStripLayer[DInfo_rftk3_index[j]];
      Dtrk4nStripLayer[typesize] = TrackInfo_nStripLayer[DInfo_rftk4_index[j]];
      Dtrk3Chi2ndf[typesize] = TrackInfo_chi2[DInfo_rftk3_index[j]]/TrackInfo_ndf[DInfo_rftk3_index[j]];
      Dtrk4Chi2ndf[typesize] = TrackInfo_chi2[DInfo_rftk4_index[j]]/TrackInfo_ndf[DInfo_rftk4_index[j]];
      Dtrk3MassHypo[typesize] = DInfo_rftk3_MassHypo[j];
      Dtrk4MassHypo[typesize] = DInfo_rftk4_MassHypo[j];
      DtktkResmass[typesize] = -1;
      DtktkRespt[typesize] = -1;
      DtktkReseta[typesize] = -20;
      DtktkResphi[typesize] = -20;
    }
  else if(DInfo_type[j]==6||DInfo_type[j]==7)
    {
      Dtrk3Pt[typesize] = TrackInfo_pt[DInfo_rftk3_index[j]];
      Dtrk4Pt[typesize] = TrackInfo_pt[DInfo_rftk4_index[j]];
      Dtrk3Eta[typesize] = TrackInfo_eta[DInfo_rftk3_index[j]];
      Dtrk4Eta[typesize] = TrackInfo_eta[DInfo_rftk4_index[j]];
      Dtrk3Phi[typesize] = TrackInfo_phi[DInfo_rftk3_index[j]];
      Dtrk4Phi[typesize] = TrackInfo_phi[DInfo_rftk4_index[j]];
      trk3mass = findMass(DInfo_rftk3_MassHypo[j]);
      trk4mass = findMass(DInfo_rftk4_MassHypo[j]);
      b4P->SetPtEtaPhiM(TrackInfo_pt[DInfo_rftk3_index[j]],TrackInfo_eta[DInfo_rftk3_index[j]],TrackInfo_phi[DInfo_rftk3_index[j]],trk3mass);
      Dtrk3Y[typesize] = b4P->Rapidity();
      b4P->SetPtEtaPhiM(TrackInfo_pt[DInfo_rftk4_index[j]],TrackInfo_eta[DInfo_rftk4_index[j]],TrackInfo_phi[DInfo_rftk4_index[j]],trk4mass);
      Dtrk4Y[typesize] = b4P->Rapidity();
      Dtrk3Dxy[typesize] = TrackInfo_dxyPV[DInfo_rftk3_index[j]];
      Dtrk4Dxy[typesize] = TrackInfo_dxyPV[DInfo_rftk4_index[j]];
      Dtrk3D0Err[typesize] = TrackInfo_d0error[DInfo_rftk3_index[j]];
      Dtrk4D0Err[typesize] = TrackInfo_d0error[DInfo_rftk4_index[j]];
      Dtrk3PixelHit[typesize] = TrackInfo_pixelhit[DInfo_rftk3_index[j]];
      Dtrk4PixelHit[typesize] = TrackInfo_pixelhit[DInfo_rftk4_index[j]];
      Dtrk3StripHit[typesize] = TrackInfo_striphit[DInfo_rftk3_index[j]];
      Dtrk4StripHit[typesize] = TrackInfo_striphit[DInfo_rftk4_index[j]];
      Dtrk3Chi2ndf[typesize] = TrackInfo_chi2[DInfo_rftk3_index[j]]/TrackInfo_ndf[DInfo_rftk3_index[j]];
      Dtrk4Chi2ndf[typesize] = TrackInfo_chi2[DInfo_rftk4_index[j]]/TrackInfo_ndf[DInfo_rftk4_index[j]];
      Dtrk3MassHypo[typesize] = DInfo_rftk3_MassHypo[j];
      Dtrk4MassHypo[typesize] = DInfo_rftk4_MassHypo[j];
      DtktkResmass[typesize] = DInfo_tktkRes_mass[j];
      DtktkRespt[typesize] = DInfo_tktkRes_pt[j];
      DtktkReseta[typesize] = DInfo_tktkRes_eta[j];
      DtktkResphi[typesize] = DInfo_tktkRes_phi[j];
    }

  Int_t hypo=-1,DpdgId=0,level=0;
  if(DInfo_type[j]==1||DInfo_type[j]==2||DInfo_type[j]==5) DpdgId=DZERO_PDGID;
  else if(DInfo_type[j]==3||DInfo_type[j]==4) DpdgId=DPLUS_PDGID;
  else if(DInfo_type[j]==6||DInfo_type[j]==7) DpdgId=DSUBS_PDGID;
  Dgen[typesize] = 0;//gen init
  DgenIndex[typesize] = -1;//gen init
  Dgenpt[typesize] = -1;
  Dgeneta[typesize] = -20;
  Dgenphi[typesize] = -20;
  Dgeny[typesize] = -1;
  Int_t rGenIdxTk1 = -1;
  Int_t rGenIdxTk2 = -1;
  Int_t dGenIdxTk1 = -1;
  Int_t dGenIdxTk2 = -1;
  Int_t dGenIdxTk3 = -1;
  Int_t dGenIdxTk4 = -1;
  Int_t dGenIdxRes = -1;
  if(!REAL)
    {
      if(DInfo_type[j]==1||DInfo_type[j]==2||DInfo_type[j]==3||DInfo_type[j]==4||DInfo_type[j]==5)
	{
	  if(TrackInfo_geninfo_index[DInfo_rftk1_index[j]]>-1)
	    {
	      level=0;
	      if(TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk1_index[j]]])==DInfo_rftk1_MassHypo[j])
		{
		  hypo=-1;
		  if(TMath::Abs(DInfo_rftk1_MassHypo[j])==KAON_PDGID) hypo=0;
		  else if(TMath::Abs(DInfo_rftk1_MassHypo[j])==PION_PDGID) hypo=1;
		  if(hypo==0||hypo==1)
		    {
		      level=1;		      
		      if(GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk1_index[j]]]>-1)
			{
			  if(TMath::Abs(GenInfo_pdgId[GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk1_index[j]]]])==DpdgId)
			    {
			      level=3;
			      dGenIdxTk1=GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk1_index[j]]];
			    }
			}
		    }
		}
	      Dgen[typesize]=level;
	    }
	  if(TrackInfo_geninfo_index[DInfo_rftk2_index[j]]>-1)
	    {
	      level=0;
	      if(TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]])==DInfo_rftk2_MassHypo[j])
		{
		  if((hypo==0&&TMath::Abs(DInfo_rftk2_MassHypo[j])==PION_PDGID)||(hypo==1&&TMath::Abs(DInfo_rftk2_MassHypo[j])==KAON_PDGID))
		    {
		      if(hypo==1&&TMath::Abs(DInfo_rftk2_MassHypo[j])==KAON_PDGID) hypo=2;
		      level=1;
		      if(GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]]>-1)
                        {
                          if(TMath::Abs(GenInfo_pdgId[GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]]])==DpdgId)
                            {
                              level=3;
                              dGenIdxTk2=GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]];
                            }
                        }
		    }
		  else if(hypo==1&&TMath::Abs(DInfo_rftk2_MassHypo[j])==PION_PDGID&&(DInfo_type[j]==3||DInfo_type[j]==4||DInfo_type[j]==5))
		    {
		      hypo=3;
		      level=1;
		      if(GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]]>-1)
			{
			  if(TMath::Abs(GenInfo_pdgId[GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]]])==DpdgId)
                            {
			      level=3;
                              dGenIdxTk2=GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]];
			    }
			}
		    }
		}
	      Dgen[typesize]+=(level*10);
	    }
	  if(DInfo_type[j]==1||DInfo_type[j]==2)
	    {
	      Dgen[typesize]+=3300;
	    }
	  else
	    {
	      if(TrackInfo_geninfo_index[DInfo_rftk3_index[j]]>-1)
		{
		  level=0;
		  if(TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk3_index[j]]])==DInfo_rftk3_MassHypo[j])
		    {
		      if(((hypo==0||hypo==2)&&TMath::Abs(DInfo_rftk3_MassHypo[j])==PION_PDGID)||(hypo==3&&TMath::Abs(DInfo_rftk3_MassHypo[j])==KAON_PDGID))
			{
			  if(hypo==3&&TMath::Abs(DInfo_rftk3_MassHypo[j])==KAON_PDGID) hypo=4;
			  level=1;
			  if(GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk3_index[j]]]>-1)
			    {
			      if(TMath::Abs(GenInfo_pdgId[GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk3_index[j]]]])==DpdgId)
				{
				  level=3;
				  dGenIdxTk3=GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk3_index[j]]];
				}
			    }
			  else if(hypo==3&&TMath::Abs(DInfo_rftk3_MassHypo[j])==PION_PDGID&&DInfo_type[j]==5)
			    {
			      hypo=5;
			      level=1;
			      if(GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk3_index[j]]]>-1)
				{
				  if(TMath::Abs(GenInfo_pdgId[GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk3_index[j]]]])==DpdgId)
				    {
				      level=3;
				      dGenIdxTk3=GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk3_index[j]]];
				    }
				}
			    }
			}
		    }
		  Dgen[typesize]+=(level*100);
		}
	      if(DInfo_type[j]==3||DInfo_type[j]==4)
		{
		  Dgen[typesize]+=3000;
		}
	      else
		{
		  if(TrackInfo_geninfo_index[DInfo_rftk4_index[j]]>-1)
		    {
		      level=0;
		      if(TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk4_index[j]]])==DInfo_rftk4_MassHypo[j])
			{
			  if(((hypo==0||hypo==2||hypo==4)&&TMath::Abs(DInfo_rftk4_MassHypo[j])==PION_PDGID)||(hypo==5&&TMath::Abs(DInfo_rftk4_MassHypo[j])==KAON_PDGID))
			    {
			      level=1;
			      if(GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk4_index[j]]]>-1)
				{
				  if(TMath::Abs(GenInfo_pdgId[GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk4_index[j]]]])==DpdgId)
				    {
				      level=3;
				      dGenIdxTk4=GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk4_index[j]]];
				    }
				}
			    }
			}
		      Dgen[typesize]+=(level*1000);
		    }
		}
	    }
	  if(Dgen[typesize]==3333&&dGenIdxTk1==dGenIdxTk2)
	    {
	      if(DInfo_type[j]==1||DInfo_type[j]==2)
		{
		  Dgen[typesize]+=20000;
		}
	      else if(dGenIdxTk1==dGenIdxTk3)
		{
		  if(DInfo_type[j]==3||DInfo_type[j]==4)
		    {
		      Dgen[typesize]+=20000;
		    }
		  else if(dGenIdxTk1==dGenIdxTk4)
		    {
		      Dgen[typesize]+=20000;
		    }
		}	    
	    }
	}//if(DInfo_type[j]==1||DInfo_type[j]==2||DInfo_type[j]==3||DInfo_type[j]==4||DInfo_type[j]==5)
      if(Dgen[typesize]==23333)
	{
	  DgenIndex[typesize] = dGenIdxTk1;
	  Dgenpt[typesize] = GenInfo_pt[DgenIndex[typesize]];
	  Dgeneta[typesize] = GenInfo_eta[DgenIndex[typesize]];
	  Dgenphi[typesize] = GenInfo_phi[DgenIndex[typesize]];
	  b4P->SetXYZM(GenInfo_pt[DgenIndex[typesize]]*cos(GenInfo_phi[DgenIndex[typesize]]),
		       GenInfo_pt[DgenIndex[typesize]]*sin(GenInfo_phi[DgenIndex[typesize]]),
		       GenInfo_pt[DgenIndex[typesize]]*sinh(GenInfo_eta[DgenIndex[typesize]]),
		       GenInfo_mass[DgenIndex[typesize]]);
	  Dgeny[typesize] = b4P->Rapidity();
	}
    }//if(!real)
}//fillDtree

//
bool isDsignalGen(Int_t Dtype, Int_t j)
{
  bool flag=false;
  if(Dtype==1||Dtype==2)
    {
      if(abs(GenInfo_pdgId[j])==DZERO_PDGID&&GenInfo_nDa[j]==2&&GenInfo_da1[j]!=-1&&GenInfo_da2[j]!=-1)
	{
	  if((TMath::Abs(GenInfo_pdgId[GenInfo_da1[j]])==KAON_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da2[j]])==PION_PDGID) || 
	     (TMath::Abs(GenInfo_pdgId[GenInfo_da1[j]])==PION_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da2[j]])==KAON_PDGID))
	    {
	      flag=true;
	    }
	}
    }
  return flag;
}

