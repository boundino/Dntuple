#include "loop.h"
using namespace std;

Bool_t iseos = false;
int loop(TString infile="/data/twang/DfinderRun2/Pythia8_5020GeV_DstarD0kpipipi_755patch3_GEN_SIM_PU_20151120/crab_DfinderMC_Dstar5p_tkPt2_20151126/151127_005816/0000/finder_PbPb.root",
         TString outfile="/data/wangj/Data2015/Dntuple/example/test.root", Bool_t REAL=false, Bool_t isPbPb=false, Int_t startEntries=0, Int_t endEntries=-1, Bool_t skim=false, Bool_t gskim=true, Bool_t checkMatching=true)
{
  double findMass(Int_t particlePdgId);
  int findPdgid(Double_t tkmass);
  void fillTreeEvt();
  void fillDTree(TVector3* bP, TVector3* bVtx, TLorentzVector* b4P, Int_t j, Int_t typesize, Bool_t REAL);
  bool isDsignalGen(Int_t Dtype, Int_t j);

  cout<<endl;
  if(REAL) cout<<"--- Processing - REAL DATA";
  else cout<<"--- Processing - MC";
  if(isPbPb) cout<<" - PbPb";
  else cout<<" - pp";
  cout<<endl;

  TString ifname;
  if(iseos) ifname = Form("root://eoscms.cern.ch//eos/cms%s",infile.Data());
  else ifname = infile;
  TFile* f = TFile::Open(ifname);
  TTree* root = (TTree*)f->Get("Dfinder/root");
  TTree* hltroot = (TTree*)f->Get("hltanalysis/HltTree");
  //TTree* skimroot = (TTree*)f->Get("skimanalysis/HltTree");
  //TTree* hiroot = (TTree*)f->Get("hiEvtAnalyzer/HiTree");
  setDBranch(root);
  setHltTreeBranch(hltroot);
  //if(isPbPb) setHiTreeBranch(hiroot);

  Long64_t nentries = root->GetEntries();
  if(endEntries>nentries || endEntries==-1) endEntries = nentries;
  TFile *outf = new TFile(Form("%s", outfile.Data()),"recreate");

  int isDchannel[12];
  isDchannel[0] = 1; //k+pi-
  isDchannel[1] = 1; //k-pi+
  isDchannel[2] = 1; //k-pi+pi+
  isDchannel[3] = 1; //k+pi-pi-
  isDchannel[4] = 1; //k-pi-pi+pi+
  isDchannel[5] = 1; //k+pi+pi-pi-
  isDchannel[6] = 1; 
  isDchannel[7] = 1; 
  isDchannel[8] = 1; 
  isDchannel[9] = 1; 
  isDchannel[10] = 1; 
  isDchannel[11] = 1; 

  cout<<"--- Building trees"<<endl;
  TTree* ntD1 = new TTree("ntDkpi","");           buildDBranch(ntD1);
  TTree* ntD2 = new TTree("ntDkpipi","");         buildDBranch(ntD2);
  TTree* ntD3 = new TTree("ntDkpipipi","");       buildDBranch(ntD3);
  TTree* ntD4 = new TTree("ntDPhikkpi","");       buildDBranch(ntD4);
  TTree* ntD5 = new TTree("ntDD0kpipi","");       buildDBranch(ntD5);
  TTree* ntD6 = new TTree("ntDD0kpipipipi","");   buildDBranch(ntD6);
  TTree* ntGen = new TTree("ntGen","");           buildGenBranch(ntGen);
  TTree* ntHlt = hltroot->CloneTree(0);
  ntHlt->SetName("ntHlt");
  //TTree* ntSkim = skimroot->CloneTree(0);
  //ntSkim->SetName("ntSkim");
  //TTree* ntHi = hiroot->CloneTree(0);
  //ntHi->SetName("ntHi");
  cout<<"--- Building trees finished"<<endl;

  Int_t offsetHltTree=0;
  TVector3* bP = new TVector3;
  TVector3* bVtx = new TVector3;
  TLorentzVector* b4P = new TLorentzVector;
  TLorentzVector* bGen = new TLorentzVector;
  cout<<"--- Check the number of events for three trees"<<endl;
  cout<<root->GetEntries()<<" "<<hltroot->GetEntries();
  //if(isPbPb) cout<<" "<<hiroot->GetEntries();
  cout<<endl;
  cout<<"--- Processing events"<<endl;
  for(Int_t i=startEntries;i<endEntries;i++)
    {
      root->GetEntry(i);
      hltroot->GetEntry(i);
      //skimroot->GetEntry(i);
      //if(isPbPb) hiroot->GetEntry(i);
      if(i%100000==0) cout<<setw(7)<<i<<" / "<<(endEntries-startEntries)<<endl;
      if(checkMatching)
        {
          if((Int_t)Df_HLT_Event!=EvtInfo_EvtNo||(Int_t)Df_HLT_Run!=EvtInfo_RunNo||(Int_t)Df_HLT_LumiBlock!=EvtInfo_LumiNo || (isPbPb&&((Int_t)Df_HiTree_Evt!=EvtInfo_EvtNo||(Int_t)Df_HiTree_Run!=EvtInfo_RunNo||(Int_t)Df_HiTree_Lumi!=EvtInfo_LumiNo)))
            {
              cout<<"Error: not matched "<<i<<" | ";
              cout<<"EvtNo("<<Df_HLT_Event<<","<<EvtInfo_EvtNo<<") RunNo("<<Df_HLT_Run<<","<<EvtInfo_RunNo<<") LumiNo("<<Df_HLT_LumiBlock<<","<<EvtInfo_LumiNo<<") | EvtNo("<<Df_HiTree_Evt<<","<<EvtInfo_EvtNo<<") RunNo("<<Df_HiTree_Run<<","<<EvtInfo_RunNo<<") LumiNo("<<Df_HiTree_Lumi<<","<<EvtInfo_LumiNo<<")"<<endl;
              continue;
            }
        }
      fillTreeEvt();
      Int_t Dtypesize[6]={0,0,0,0,0,0};
      Int_t ptflag=-1,ptMatchedflag=-1,probflag=-1,probMatchedflag=-1;
      Double_t pttem=0,ptMatchedtem=0,probtem=0,probMatchedtem=0;
      for(Int_t t=0;t<12;t++)
	{
	  if(t%2==0)
	    {
	      Dsize = 0;
	      ptflag = -1;
	      pttem = 0;
	      ptMatchedflag = -1;
	      ptMatchedtem = 0;
	      probflag = -1;
	      probtem = 0;
	      probMatchedflag = -1;
	      probMatchedtem = 0;
	    }
	  if(isDchannel[t]==1)
	    {
	      for(int j=0;j<DInfo_size;j++)
		{
		  if(skim)
		    {
		      if(DInfo_alpha[j]>0.13) continue;
		      if((DInfo_pt[j]>=13.&&(DInfo_svpvDistance[j]/DInfo_svpvDisErr[j])<2.5)||
			 (DInfo_pt[j]>=5.5&&DInfo_pt[j]<13.&&(DInfo_svpvDistance[j]/DInfo_svpvDisErr[j])<4.)||
			 (DInfo_pt[j]<5.5&&(DInfo_svpvDistance[j]/DInfo_svpvDisErr[j])<5.)) continue;
		    }
		  if(DInfo_type[j]==(t+1))
		    {
		      fillDTree(bP,bVtx,b4P,j,Dtypesize[t/2],REAL);
		      if(DInfo_pt[j]>pttem)
			{
			  ptflag = Dtypesize[t/2];
			  pttem = DInfo_pt[j];
			}
		      if(TMath::Prob(DInfo_vtxchi2[j],DInfo_vtxdof[j])>probtem)
			{
			  probflag = Dtypesize[t/2];
			  probtem = TMath::Prob(DInfo_vtxchi2[j],DInfo_vtxdof[j]);
			}
		      if(((!REAL&&(Dgen[Dtypesize[t/2]]==23333||Dgen[Dtypesize[t/2]]==23344))||REAL)&&Dtrk1Pt[Dtypesize[t/2]]>8.&&Dtrk2Pt[Dtypesize[t/2]]>8.&&Dchi2cl[Dtypesize[t/2]]>0.05&&(DsvpvDistance[Dtypesize[t/2]]/DsvpvDisErr[Dtypesize[t/2]])>2.5&&TMath::Cos(Dalpha[Dtypesize[t/2]])>0.95&&(Dtrk1highPurity[Dtypesize[t/2]]&&Dtrk2highPurity[Dtypesize[t/2]]))
			{
			  if(DInfo_pt[j]>ptMatchedtem)
			    {
			      ptMatchedflag = Dtypesize[t/2];
			      ptMatchedtem = DInfo_pt[j];
			    }
			  if(TMath::Prob(DInfo_vtxchi2[j],DInfo_vtxdof[j])>probMatchedtem)
			    {
			      probMatchedflag = Dtypesize[t/2];
			      probMatchedtem = TMath::Prob(DInfo_vtxchi2[j],DInfo_vtxdof[j]);
			    }
			}
		      Dtypesize[t/2]++;
		    }
		}
	      if(t%2==1)
		{
		  if(ptflag>=0) Dmaxpt[ptflag] = true;
		  if(probflag>=0) Dmaxprob[probflag] = true;
		  if(ptMatchedflag>=0) DmaxptMatched[ptMatchedflag] = true;
		  if(probMatchedflag>=0) DmaxprobMatched[probMatchedflag] = true;
		}	      
	      if(t==1)      ntD1->Fill();
	      else if(t==3) ntD2->Fill();
	      else if(t==5) ntD3->Fill();
	      else if(t==7) ntD4->Fill();
	      else if(t==9) ntD5->Fill();
	      else if(t==11) ntD6->Fill();
	    }
	}

      ntHlt->Fill();
      //ntSkim->Fill();
      //if(isPbPb) ntHi->Fill();

      if(!REAL)
	{
	  Int_t gt=0,sigtype=0;
	  Int_t gsize=0;
	  Gsize = 0;
	  for(int j=0;j<GenInfo_size;j++)
	    {
	      if(TMath::Abs(GenInfo_pdgId[j])!=DZERO_PDGID&&gskim) continue;
	      Gsize = gsize+1;
	      Gpt[gsize] = GenInfo_pt[j];
	      Geta[gsize] = GenInfo_eta[j];
	      Gphi[gsize] = GenInfo_phi[j];
	      GpdgId[gsize] = GenInfo_pdgId[j];
	      bGen->SetPtEtaPhiM(GenInfo_pt[j],GenInfo_eta[j],GenInfo_phi[j],GenInfo_mass[j]);
	      Gy[gsize] = bGen->Rapidity();
	      sigtype=0;
	      for(gt=1;gt<13;gt++)
		{
		  if(isDsignalGen(gt,j))
		    {
		      sigtype=gt;
		      break;
		    }
		}
	      GisSignal[gsize] = sigtype;
	      gsize++;
	    }
	  ntGen->Fill();
	}
    }
  outf->Write();
  cout<<"--- Writing finished"<<endl;
  outf->Close();

  cout<<"--- In/Output files"<<endl;
  cout<<infile<<endl;
  cout<<outfile<<endl;
  cout<<endl;

  return 1;
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


void fillTreeEvt()
{
  //Event Info
  RunNo = EvtInfo_RunNo;
  EvtNo = EvtInfo_EvtNo;
  LumiNo = EvtInfo_LumiNo;
  PVx = EvtInfo_PVx;
  PVy = EvtInfo_PVy;
  PVz = EvtInfo_PVz;
  PVxE = EvtInfo_PVxE;
  PVyE = EvtInfo_PVyE;
  PVzE = EvtInfo_PVzE;
  PVnchi2 = EvtInfo_PVnchi2;
  PVchi2 = EvtInfo_PVchi2;
  BSx = EvtInfo_BSx;
  BSy = EvtInfo_BSy;
  BSz = EvtInfo_BSz;
  BSxErr = EvtInfo_BSxErr;
  BSyErr = EvtInfo_BSyErr;
  BSzErr = EvtInfo_BSzErr;
  BSdxdz = EvtInfo_BSdxdz;
  BSdydz = EvtInfo_BSdydz;
  BSdxdzErr = EvtInfo_BSdxdzErr;
  BSdydzErr = EvtInfo_BSdydzErr;
  BSWidthX = EvtInfo_BSWidthX;
  BSWidthXErr = EvtInfo_BSWidthXErr;
  BSWidthY = EvtInfo_BSWidthY;
  BSWidthYErr = EvtInfo_BSWidthYErr;
}

void fillDTree(TVector3* bP, TVector3* bVtx, TLorentzVector* b4P, Int_t j, Int_t typesize, Bool_t REAL)
{
  //EvtInfo
  Dsize = typesize+1;

  //DInfo
  bP->SetPtEtaPhi(DInfo_pt[j],DInfo_eta[j]*0,DInfo_phi[j]);
  bVtx->SetXYZ(DInfo_vtxX[j]-EvtInfo_PVx,
	       DInfo_vtxY[j]-EvtInfo_PVy,
	       DInfo_vtxZ[j]*0-EvtInfo_PVz*0);
  b4P->SetPtEtaPhiM(DInfo_pt[j],DInfo_eta[j],DInfo_phi[j],DInfo_mass[j]);
  Dindex[typesize] = typesize;
  Dtype[typesize] = DInfo_type[j];
  Dmass[typesize] = DInfo_mass[j];
  Dpt[typesize] = DInfo_pt[j];
  Deta[typesize] = DInfo_eta[j];
  Dphi[typesize] = DInfo_phi[j];
  Dy[typesize] = b4P->Rapidity();
  DvtxX[typesize] = DInfo_vtxX[j] - EvtInfo_PVx;
  DvtxY[typesize] = DInfo_vtxY[j] - EvtInfo_PVy;
  Dd0[typesize] = TMath::Sqrt((DInfo_vtxX[j]-EvtInfo_PVx)*(DInfo_vtxX[j]-EvtInfo_PVx)+(DInfo_vtxY[j]-EvtInfo_PVy)*(DInfo_vtxY[j]-EvtInfo_PVy));
  Dd0Err[typesize] = TMath::Sqrt(DInfo_vtxXErr[j]*DInfo_vtxXErr[j]+DInfo_vtxYErr[j]*DInfo_vtxYErr[j]);
  Ddxyz[typesize] = TMath::Sqrt((DInfo_vtxX[j]-EvtInfo_PVx)*(DInfo_vtxX[j]-EvtInfo_PVx)+(DInfo_vtxY[j]-EvtInfo_PVy)*(DInfo_vtxY[j]-EvtInfo_PVy)+(DInfo_vtxZ[j]-EvtInfo_PVz)*(DInfo_vtxZ[j]-EvtInfo_PVz));
  DdxyzErr[typesize] = TMath::Sqrt(DInfo_vtxXErr[j]*DInfo_vtxXErr[j]+DInfo_vtxYErr[j]*DInfo_vtxYErr[j]+DInfo_vtxZErr[j]*DInfo_vtxZErr[j]);
  Dchi2ndf[typesize] = DInfo_vtxchi2[j]/DInfo_vtxdof[j];
  Dchi2cl[typesize] = TMath::Prob(DInfo_vtxchi2[j],DInfo_vtxdof[j]);
  Ddtheta[typesize] = bP->Angle(*bVtx);
  Dlxy[typesize] = ((DInfo_vtxX[j]-EvtInfo_PVx)*b4P->Px() + (DInfo_vtxY[j]-EvtInfo_PVy)*b4P->Py())/DInfo_pt[j];
  Dalpha[typesize] = DInfo_alpha[j];
  DsvpvDistance[typesize] = DInfo_svpvDistance[j];
  DsvpvDisErr[typesize] = DInfo_svpvDisErr[j];
  DsvpvDistance_2D[typesize] = DInfo_svpvDistance_2D[j];
  DsvpvDisErr_2D[typesize] = DInfo_svpvDisErr_2D[j];
  Double_t r2lxyBS = (DInfo_vtxX[j]-EvtInfo_BSx+(DInfo_vtxZ[j]-EvtInfo_BSz)*EvtInfo_BSdxdz) * (DInfo_vtxX[j]-EvtInfo_BSx+(DInfo_vtxZ[j]-EvtInfo_BSz)*EvtInfo_BSdxdz)
    + (DInfo_vtxY[j]-EvtInfo_BSy+(DInfo_vtxZ[j]-EvtInfo_BSz)*EvtInfo_BSdydz) * (DInfo_vtxY[j]-EvtInfo_BSy+(DInfo_vtxZ[j]-EvtInfo_BSz)*EvtInfo_BSdydz);
  Double_t xlxyBS = DInfo_vtxX[j]-EvtInfo_BSx + (DInfo_vtxZ[j]-EvtInfo_BSz)*EvtInfo_BSdxdz;
  Double_t ylxyBS = DInfo_vtxY[j]-EvtInfo_BSy + (DInfo_vtxZ[j]-EvtInfo_BSz)*EvtInfo_BSdydz;
  DlxyBS[typesize] = TMath::Sqrt(r2lxyBS);
  DlxyBSErr[typesize] = (1./r2lxyBS) * ((xlxyBS*xlxyBS)*DInfo_vtxXErr[j] + (2*xlxyBS*ylxyBS)*DInfo_vtxYXErr[j] + (ylxyBS*ylxyBS)*DInfo_vtxYErr[j]);
  DMaxDoca[typesize] = DInfo_MaxDoca[j];
  Dmaxpt[typesize] = false;
  Dmaxprob[typesize] = false;
  DmaxptMatched[typesize] = false;
  DmaxprobMatched[typesize] = false;

  //DInfo.trkInfo
  Double_t trk1mass,trk2mass,trk3mass,trk4mass;
  if(DInfo_type[j]==1||DInfo_type[j]==2||DInfo_type[j]==3||DInfo_type[j]==4||DInfo_type[j]==5||DInfo_type[j]==6)
    {
      Dtrk1Idx[typesize] = DInfo_rftk1_index[j];
      Dtrk1Pt[typesize] = TrackInfo_pt[DInfo_rftk1_index[j]];
      Dtrk1Eta[typesize] = TrackInfo_eta[DInfo_rftk1_index[j]];
      Dtrk1Phi[typesize] = TrackInfo_phi[DInfo_rftk1_index[j]];
      Dtrk1PtErr[typesize] = TrackInfo_ptErr[DInfo_rftk1_index[j]];
      Dtrk1EtaErr[typesize] = TrackInfo_etaErr[DInfo_rftk1_index[j]];
      Dtrk1PhiErr[typesize] = TrackInfo_phiErr[DInfo_rftk1_index[j]];
      trk1mass = findMass(DInfo_rftk1_MassHypo[j]);
      b4P->SetPtEtaPhiM(TrackInfo_pt[DInfo_rftk1_index[j]],TrackInfo_eta[DInfo_rftk1_index[j]],TrackInfo_phi[DInfo_rftk1_index[j]],trk1mass);
      Dtrk1Y[typesize] = b4P->Rapidity();
      Dtrk1Dxy[typesize] = TrackInfo_dxyPV[DInfo_rftk1_index[j]];
      Dtrk1D0Err[typesize] = TrackInfo_d0error[DInfo_rftk1_index[j]];
      Dtrk1PixelHit[typesize] = TrackInfo_pixelhit[DInfo_rftk1_index[j]];
      Dtrk1StripHit[typesize] = TrackInfo_striphit[DInfo_rftk1_index[j]];
      Dtrk1nPixelLayer[typesize] = TrackInfo_nPixelLayer[DInfo_rftk1_index[j]];
      Dtrk1nStripLayer[typesize] = TrackInfo_nStripLayer[DInfo_rftk1_index[j]];
      Dtrk1MassHypo[typesize] = DInfo_rftk1_MassHypo[j]*TrackInfo_charge[DInfo_rftk1_index[j]];
      Dtrk1Chi2ndf[typesize] = TrackInfo_chi2[DInfo_rftk1_index[j]]/TrackInfo_ndf[DInfo_rftk1_index[j]];
      Dtrk1MVAVal[typesize] = TrackInfo_trkMVAVal[DInfo_rftk1_index[j]];
      Dtrk1Algo[typesize] = TrackInfo_trkAlgo[DInfo_rftk1_index[j]];
      Dtrk1highPurity[typesize] = TrackInfo_highPurity[DInfo_rftk1_index[j]];
      Dtrk1Quality[typesize] = TrackInfo_trackQuality[DInfo_rftk1_index[j]];

      Dtrk2Idx[typesize] = DInfo_rftk2_index[j];
      Dtrk2Pt[typesize] = TrackInfo_pt[DInfo_rftk2_index[j]];
      Dtrk2Eta[typesize] = TrackInfo_eta[DInfo_rftk2_index[j]];
      Dtrk2Phi[typesize] = TrackInfo_phi[DInfo_rftk2_index[j]];
      Dtrk2PtErr[typesize] = TrackInfo_ptErr[DInfo_rftk2_index[j]];
      Dtrk2EtaErr[typesize] = TrackInfo_etaErr[DInfo_rftk2_index[j]];
      Dtrk2PhiErr[typesize] = TrackInfo_phiErr[DInfo_rftk2_index[j]];
      trk2mass = findMass(DInfo_rftk2_MassHypo[j]);
      b4P->SetPtEtaPhiM(TrackInfo_pt[DInfo_rftk2_index[j]],TrackInfo_eta[DInfo_rftk2_index[j]],TrackInfo_phi[DInfo_rftk2_index[j]],trk2mass);
      Dtrk2Y[typesize] = b4P->Rapidity();
      Dtrk2Dxy[typesize] = TrackInfo_dxyPV[DInfo_rftk2_index[j]];
      Dtrk2D0Err[typesize] = TrackInfo_d0error[DInfo_rftk2_index[j]];
      Dtrk2PixelHit[typesize] = TrackInfo_pixelhit[DInfo_rftk2_index[j]];
      Dtrk2StripHit[typesize] = TrackInfo_striphit[DInfo_rftk2_index[j]];
      Dtrk2nPixelLayer[typesize] = TrackInfo_nPixelLayer[DInfo_rftk2_index[j]];
      Dtrk2nStripLayer[typesize] = TrackInfo_nStripLayer[DInfo_rftk2_index[j]];
      Dtrk2Chi2ndf[typesize] = TrackInfo_chi2[DInfo_rftk2_index[j]]/TrackInfo_ndf[DInfo_rftk2_index[j]];
      Dtrk2MassHypo[typesize] = DInfo_rftk2_MassHypo[j]*TrackInfo_charge[DInfo_rftk2_index[j]];
      Dtrk2MVAVal[typesize] = TrackInfo_trkMVAVal[DInfo_rftk2_index[j]];
      Dtrk2Algo[typesize] = TrackInfo_trkAlgo[DInfo_rftk2_index[j]];
      Dtrk2highPurity[typesize] = TrackInfo_highPurity[DInfo_rftk2_index[j]];
      Dtrk2Quality[typesize] = TrackInfo_trackQuality[DInfo_rftk2_index[j]];

      if(DInfo_type[j]==1||DInfo_type[j]==2)
        {
          Dtrk3Idx[typesize] = -1;
          Dtrk3Pt[typesize] = -1;
          Dtrk3Eta[typesize] = -20;
          Dtrk3Phi[typesize] = -20;
          Dtrk3PtErr[typesize] = 0;
          Dtrk3EtaErr[typesize] = 0;
          Dtrk3PhiErr[typesize] = 0;
          Dtrk3Y[typesize] = -1;
          Dtrk3Dxy[typesize] = -1;
          Dtrk3D0Err[typesize] = -1;
          Dtrk3PixelHit[typesize] = -1;
          Dtrk3StripHit[typesize] = -1;
          Dtrk3nPixelLayer[typesize] = -1;
          Dtrk3nStripLayer[typesize] = -1;
          Dtrk3Chi2ndf[typesize] = -1;
          Dtrk3MassHypo[typesize] = 0;
          Dtrk3MVAVal[typesize] = -100;
          Dtrk3Algo[typesize] = 0;
          Dtrk3Quality[typesize] = 0;
          Dtrk3highPurity[typesize] = false;
          Dtrk4Idx[typesize] = -1;
          Dtrk4Pt[typesize] = -1;
          Dtrk4Eta[typesize] = -20;
          Dtrk4Phi[typesize] = -20;
          Dtrk4PtErr[typesize] = 0;
          Dtrk4EtaErr[typesize] = 0;
          Dtrk4PhiErr[typesize] = 0;
          Dtrk4Y[typesize] = -1;
          Dtrk4Dxy[typesize] = -1;
          Dtrk4D0Err[typesize] = -1;
          Dtrk4PixelHit[typesize] = -1;
          Dtrk4StripHit[typesize] = -1;
          Dtrk4nPixelLayer[typesize] = -1;
          Dtrk4nStripLayer[typesize] = -1;
          Dtrk4Chi2ndf[typesize] = -1;
          Dtrk4MassHypo[typesize] = 0;
          Dtrk4MVAVal[typesize] = -100;
          Dtrk4Algo[typesize] = 0;
          Dtrk4Quality[typesize] = 0;
          Dtrk4highPurity[typesize] = false;
          
          DtktkResmass[typesize] = -1;
          DtktkRespt[typesize] = -1;
          DtktkReseta[typesize] = -20;
          DtktkResphi[typesize] = -20;
        }
      else if(DInfo_type[j]==3||DInfo_type[j]==4)
        {
          Dtrk3Idx[typesize] = DInfo_rftk3_index[j];
          Dtrk3Pt[typesize] = TrackInfo_pt[DInfo_rftk3_index[j]];
          Dtrk3Eta[typesize] = TrackInfo_eta[DInfo_rftk3_index[j]];
          Dtrk3Phi[typesize] = TrackInfo_phi[DInfo_rftk3_index[j]];
          Dtrk3PtErr[typesize] = TrackInfo_ptErr[DInfo_rftk3_index[j]];
          Dtrk3EtaErr[typesize] = TrackInfo_etaErr[DInfo_rftk3_index[j]];
          Dtrk3PhiErr[typesize] = TrackInfo_phiErr[DInfo_rftk3_index[j]];
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
          Dtrk3MassHypo[typesize] = DInfo_rftk3_MassHypo[j]*TrackInfo_charge[DInfo_rftk3_index[j]];
          Dtrk3MVAVal[typesize] = TrackInfo_trkMVAVal[DInfo_rftk3_index[j]];
          Dtrk3Algo[typesize] = TrackInfo_trkAlgo[DInfo_rftk3_index[j]];
          Dtrk3highPurity[typesize] = TrackInfo_highPurity[DInfo_rftk3_index[j]];
          Dtrk3Quality[typesize] = TrackInfo_trackQuality[DInfo_rftk3_index[j]];
          Dtrk4Idx[typesize] = -1;
          Dtrk4Pt[typesize] = -1;
          Dtrk4Eta[typesize] = -20;
          Dtrk4Phi[typesize] = -20;
          Dtrk4PtErr[typesize] = 0;
          Dtrk4EtaErr[typesize] = 0;
          Dtrk4PhiErr[typesize] = 0;
          Dtrk4Y[typesize] = -1;
          Dtrk4Dxy[typesize] = -1;
          Dtrk4D0Err[typesize] = -1;
          Dtrk4PixelHit[typesize] = -1;
          Dtrk4StripHit[typesize] = -1;
          Dtrk4nPixelLayer[typesize] = -1;
          Dtrk4nStripLayer[typesize] = -1;
          Dtrk4Chi2ndf[typesize] = -1;
          Dtrk4MassHypo[typesize] = 0;
          Dtrk4MVAVal[typesize] = -100;
          Dtrk4Algo[typesize] = 0;
          Dtrk4Quality[typesize] = 0;
          Dtrk4highPurity[typesize] = false;

          DtktkResmass[typesize] = -1;
          DtktkRespt[typesize] = -1;
          DtktkReseta[typesize] = -20;
          DtktkResphi[typesize] = -20;
        }
      else if(DInfo_type[j]==5||DInfo_type[j]==6)
        {
          Dtrk3Idx[typesize] = DInfo_rftk3_index[j];
          Dtrk4Idx[typesize] = DInfo_rftk4_index[j];
          Dtrk3Pt[typesize] = TrackInfo_pt[DInfo_rftk3_index[j]];
          Dtrk4Pt[typesize] = TrackInfo_pt[DInfo_rftk4_index[j]];
          Dtrk3Eta[typesize] = TrackInfo_eta[DInfo_rftk3_index[j]];
          Dtrk4Eta[typesize] = TrackInfo_eta[DInfo_rftk4_index[j]];
          Dtrk3Phi[typesize] = TrackInfo_phi[DInfo_rftk3_index[j]];
          Dtrk4Phi[typesize] = TrackInfo_phi[DInfo_rftk4_index[j]];
          Dtrk3PtErr[typesize] = TrackInfo_ptErr[DInfo_rftk3_index[j]];
          Dtrk4PtErr[typesize] = TrackInfo_ptErr[DInfo_rftk4_index[j]];
          Dtrk3EtaErr[typesize] = TrackInfo_etaErr[DInfo_rftk3_index[j]];
          Dtrk4EtaErr[typesize] = TrackInfo_etaErr[DInfo_rftk4_index[j]];
          Dtrk3PhiErr[typesize] = TrackInfo_phiErr[DInfo_rftk3_index[j]];
          Dtrk4PhiErr[typesize] = TrackInfo_phiErr[DInfo_rftk4_index[j]];
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
          Dtrk3MassHypo[typesize] = DInfo_rftk3_MassHypo[j]*TrackInfo_charge[DInfo_rftk3_index[j]];
          Dtrk4MassHypo[typesize] = DInfo_rftk4_MassHypo[j]*TrackInfo_charge[DInfo_rftk4_index[j]];
          Dtrk3MVAVal[typesize] = TrackInfo_trkMVAVal[DInfo_rftk3_index[j]];
          Dtrk4MVAVal[typesize] = TrackInfo_trkMVAVal[DInfo_rftk4_index[j]];
          Dtrk3Algo[typesize] = TrackInfo_trkAlgo[DInfo_rftk3_index[j]];
          Dtrk4Algo[typesize] = TrackInfo_trkAlgo[DInfo_rftk4_index[j]];
          Dtrk3highPurity[typesize] = TrackInfo_highPurity[DInfo_rftk3_index[j]];
          Dtrk4highPurity[typesize] = TrackInfo_highPurity[DInfo_rftk4_index[j]];
          Dtrk3Quality[typesize] = TrackInfo_trackQuality[DInfo_rftk3_index[j]];
          Dtrk4Quality[typesize] = TrackInfo_trackQuality[DInfo_rftk4_index[j]];

          DtktkResmass[typesize] = -1;
          DtktkRespt[typesize] = -1;
          DtktkReseta[typesize] = -20;
          DtktkResphi[typesize] = -20;
        }
    }
  else if(DInfo_type[j]==7||DInfo_type[j]==8||DInfo_type[j]==9||DInfo_type[j]==10||DInfo_type[j]==11||DInfo_type[j]==12)
    {
      Dtrk1Idx[typesize] = DInfo_rftk2_index[j];
      Dtrk1Pt[typesize] = TrackInfo_pt[DInfo_rftk2_index[j]];
      Dtrk1Eta[typesize] = TrackInfo_eta[DInfo_rftk2_index[j]];
      Dtrk1Phi[typesize] = TrackInfo_phi[DInfo_rftk2_index[j]];
      Dtrk1PtErr[typesize] = TrackInfo_ptErr[DInfo_rftk2_index[j]];
      Dtrk1EtaErr[typesize] = TrackInfo_etaErr[DInfo_rftk2_index[j]];
      Dtrk1PhiErr[typesize] = TrackInfo_phiErr[DInfo_rftk2_index[j]];
      b4P->SetPtEtaPhiM(TrackInfo_pt[DInfo_rftk2_index[j]],TrackInfo_eta[DInfo_rftk2_index[j]],TrackInfo_phi[DInfo_rftk2_index[j]],PION_MASS);
      Dtrk1Y[typesize] = b4P->Rapidity();
      Dtrk1Dxy[typesize] = TrackInfo_dxyPV[DInfo_rftk2_index[j]];
      Dtrk1D0Err[typesize] = TrackInfo_d0error[DInfo_rftk2_index[j]];
      Dtrk1PixelHit[typesize] = TrackInfo_pixelhit[DInfo_rftk2_index[j]];
      Dtrk1StripHit[typesize] = TrackInfo_striphit[DInfo_rftk2_index[j]];
      Dtrk1nPixelLayer[typesize] = TrackInfo_nPixelLayer[DInfo_rftk2_index[j]];
      Dtrk1nStripLayer[typesize] = TrackInfo_nStripLayer[DInfo_rftk2_index[j]];
      Dtrk1Chi2ndf[typesize] = TrackInfo_chi2[DInfo_rftk2_index[j]]/TrackInfo_ndf[DInfo_rftk2_index[j]];
      Dtrk1MassHypo[typesize] = DInfo_rftk2_MassHypo[j]*TrackInfo_charge[DInfo_rftk2_index[j]];
      Dtrk1MVAVal[typesize] = TrackInfo_trkMVAVal[DInfo_rftk2_index[j]];
      Dtrk1Algo[typesize] = TrackInfo_trkAlgo[DInfo_rftk2_index[j]];
      Dtrk1highPurity[typesize] = TrackInfo_highPurity[DInfo_rftk2_index[j]];
      Dtrk1Quality[typesize] = TrackInfo_trackQuality[DInfo_rftk2_index[j]];

      Dtrk2Idx[typesize] = -1;
      Dtrk2Pt[typesize] = -1;
      Dtrk2Eta[typesize] = -20;
      Dtrk2Phi[typesize] = -20;
      Dtrk2PtErr[typesize] = 0;
      Dtrk2EtaErr[typesize] = 0;
      Dtrk2PhiErr[typesize] = 0;
      Dtrk2Y[typesize] = -1;
      Dtrk2Dxy[typesize] = -1;
      Dtrk2D0Err[typesize] = -1;
      Dtrk2PixelHit[typesize] = -1;
      Dtrk2StripHit[typesize] = -1;
      Dtrk2nPixelLayer[typesize] = -1;
      Dtrk2nStripLayer[typesize] = -1;
      Dtrk2Chi2ndf[typesize] = -1;
      Dtrk2MassHypo[typesize] = 0;
      Dtrk2MVAVal[typesize] = -100;
      Dtrk2Algo[typesize] = 0;
      Dtrk2Quality[typesize] = 0;
      Dtrk2highPurity[typesize] = false;
      Dtrk3Idx[typesize] = -1;
      Dtrk3Pt[typesize] = -1;
      Dtrk3Eta[typesize] = -20;
      Dtrk3Phi[typesize] = -20;
      Dtrk3PtErr[typesize] = 0;
      Dtrk3EtaErr[typesize] = 0;
      Dtrk3PhiErr[typesize] = 0;
      Dtrk3Y[typesize] = -1;
      Dtrk3Dxy[typesize] = -1;
      Dtrk3D0Err[typesize] = -1;
      Dtrk3PixelHit[typesize] = -1;
      Dtrk3StripHit[typesize] = -1;
      Dtrk3nPixelLayer[typesize] = -1;
      Dtrk3nStripLayer[typesize] = -1;
      Dtrk3Chi2ndf[typesize] = -1;
      Dtrk3MassHypo[typesize] = 0;
      Dtrk3MVAVal[typesize] = -100;
      Dtrk3Algo[typesize] = 0;
      Dtrk3Quality[typesize] = 0;
      Dtrk3highPurity[typesize] = false;
      Dtrk4Idx[typesize] = -1;
      Dtrk4Pt[typesize] = -1;
      Dtrk4Eta[typesize] = -20;
      Dtrk4Phi[typesize] = -20;
      Dtrk4PtErr[typesize] = 0;
      Dtrk4EtaErr[typesize] = 0;
      Dtrk4PhiErr[typesize] = 0;
      Dtrk4Y[typesize] = -1;
      Dtrk4Dxy[typesize] = -1;
      Dtrk4D0Err[typesize] = -1;
      Dtrk4PixelHit[typesize] = -1;
      Dtrk4StripHit[typesize] = -1;
      Dtrk4nPixelLayer[typesize] = -1;
      Dtrk4nStripLayer[typesize] = -1;
      Dtrk4Chi2ndf[typesize] = -1;
      Dtrk4MassHypo[typesize] = 0;
      Dtrk4MVAVal[typesize] = -100;
      Dtrk4Algo[typesize] = 0;
      Dtrk4Quality[typesize] = 0;
      Dtrk4highPurity[typesize] = false;

      DtktkResmass[typesize] = DInfo_tktkRes_mass[j];
      DtktkRespt[typesize] = DInfo_tktkRes_pt[j];
      DtktkReseta[typesize] = DInfo_tktkRes_eta[j];
      DtktkResphi[typesize] = DInfo_tktkRes_phi[j];
    }

  Int_t DpdgId=0,RpdgId=0;
  if(DInfo_type[j]==1||DInfo_type[j]==2||DInfo_type[j]==5||DInfo_type[j]==6) DpdgId=DZERO_PDGID;
  else if(DInfo_type[j]==3||DInfo_type[j]==4) DpdgId=DPLUS_PDGID;
  else if(DInfo_type[j]==7||DInfo_type[j]==8) DpdgId=DSUBS_PDGID;
  else if(DInfo_type[j]==9||DInfo_type[j]==10||DInfo_type[j]==11||DInfo_type[j]==12) DpdgId=DSTAR_PDGID;
  if(DInfo_type[j]==7||DInfo_type[j]==8) RpdgId=PHI_PDGID;
  else if(DInfo_type[j]==9||DInfo_type[j]==10||DInfo_type[j]==11||DInfo_type[j]==12) RpdgId=DZERO_PDGID;
  Dgen[typesize] = 0;//gen init
  DgenIndex[typesize] = -1;
  DgennDa[typesize] = -1;
  Dgenpt[typesize] = -1;
  Dgeneta[typesize] = -20;
  Dgenphi[typesize] = -20;
  Dgeny[typesize] = -1;
  if(!REAL)
    {
      if(DInfo_type[j]==1||DInfo_type[j]==2)
        {
          if(DInfo_rftk1_index[j]>-1 && DInfo_rftk2_index[j]>-1)
            {
              if(TrackInfo_geninfo_index[DInfo_rftk1_index[j]]>-1 && 
                 TrackInfo_geninfo_index[DInfo_rftk2_index[j]]>-1)
                {
                  if(GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk1_index[j]]]>-1 && 
                     GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]]>-1)
                    {
                      if(TMath::Abs(GenInfo_pdgId[GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk1_index[j]]]])==DpdgId && 
                         GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk1_index[j]]]==GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]])
                        {
                          if(TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk1_index[j]]])==DInfo_rftk1_MassHypo[j] && 
                             TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]])==DInfo_rftk2_MassHypo[j])
                            {
                              Dgen[typesize] = 23333;
                            }
                          else if(TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]])==DInfo_rftk1_MassHypo[j] && 
                                  TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk1_index[j]]])==DInfo_rftk2_MassHypo[j])
                            {
                              Dgen[typesize] = 23344;
                            }
                        }
                    }
                }
            }
        }
      else if(DInfo_type[j]==3||DInfo_type[j]==4)
        {
          if(DInfo_rftk1_index[j]>-1 && DInfo_rftk2_index[j]>-1 && DInfo_rftk3_index[j]>-1)
            {
              if(TrackInfo_geninfo_index[DInfo_rftk1_index[j]]>-1 && 
                 TrackInfo_geninfo_index[DInfo_rftk2_index[j]]>-1 && 
                 TrackInfo_geninfo_index[DInfo_rftk3_index[j]]>-1)
                {
                  if(GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk1_index[j]]]>-1 && 
                     GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]]>-1 && 
                     GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk3_index[j]]]>-1)
                    {
                      if(TMath::Abs(GenInfo_pdgId[GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk1_index[j]]]])==DpdgId && 
                         GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk1_index[j]]]==GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]] &&
                         GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk1_index[j]]]==GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk3_index[j]]])
                        {
                          if(TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk1_index[j]]])==DInfo_rftk1_MassHypo[j] && 
                             TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]])==DInfo_rftk2_MassHypo[j] &&
                             TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk3_index[j]]])==DInfo_rftk3_MassHypo[j])
                            {
                              Dgen[typesize] = 23333;
                            }
                          else if((TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk1_index[j]]])==DInfo_rftk2_MassHypo[j]&&
                                   TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]])==DInfo_rftk1_MassHypo[j]&&
                                   TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk3_index[j]]])==PION_PDGID) ||
                                  (TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk1_index[j]]])==DInfo_rftk3_MassHypo[j]&&
                                   TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk3_index[j]]])==DInfo_rftk1_MassHypo[j]&&
                                   TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]])==PION_PDGID) ||
                                  (TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]])==DInfo_rftk3_MassHypo[j]&&
                                   TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk3_index[j]]])==DInfo_rftk2_MassHypo[j]&&
                                   TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk1_index[j]]])==PION_PDGID))
                            {
                              Dgen[typesize] = 23344;
                            }
                        }
                    }
                }
            }
        }
      else if(DInfo_type[j]==5||DInfo_type[j]==6)
        {
          if(DInfo_rftk1_index[j]>-1 && DInfo_rftk2_index[j]>-1 && DInfo_rftk3_index[j]>-1 && DInfo_rftk4_index[j]>-1)
            {
              if(TrackInfo_geninfo_index[DInfo_rftk1_index[j]]>-1 && 
                 TrackInfo_geninfo_index[DInfo_rftk2_index[j]]>-1 && 
                 TrackInfo_geninfo_index[DInfo_rftk3_index[j]]>-1 && 
                 TrackInfo_geninfo_index[DInfo_rftk4_index[j]]>-1)
                {
                  if(GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk1_index[j]]]>-1 && 
                     GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]]>-1 && 
                     GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk3_index[j]]]>-1 && 
                     GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk4_index[j]]]>-1)
                    {
                      if(TMath::Abs(GenInfo_pdgId[GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk1_index[j]]]])==DpdgId && 
                         GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk1_index[j]]]==GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]] &&
                         GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk1_index[j]]]==GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk3_index[j]]] &&
                         GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk1_index[j]]]==GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk4_index[j]]])
                        {
                          if(TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk1_index[j]]])==DInfo_rftk1_MassHypo[j] && 
                             TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]])==DInfo_rftk2_MassHypo[j] &&
                             TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk3_index[j]]])==DInfo_rftk3_MassHypo[j] &&
                             TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk4_index[j]]])==DInfo_rftk4_MassHypo[j])
                            {
                              Dgen[typesize] = 23333;
                            }
                          else if((TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk1_index[j]]])==DInfo_rftk2_MassHypo[j] &&
                                   TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]])==DInfo_rftk1_MassHypo[j] &&
                                   TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk3_index[j]]])==PION_PDGID &&
                                   TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk4_index[j]]])==PION_PDGID) ||
                                  (TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk1_index[j]]])==DInfo_rftk3_MassHypo[j] &&
                                   TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk3_index[j]]])==DInfo_rftk1_MassHypo[j] &&
                                   TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]])==PION_PDGID &&
                                   TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk4_index[j]]])==PION_PDGID) ||
                                  (TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk1_index[j]]])==DInfo_rftk4_MassHypo[j] &&
                                   TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk4_index[j]]])==DInfo_rftk1_MassHypo[j] &&
                                   TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]])==PION_PDGID &&
                                   TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk3_index[j]]])==PION_PDGID) ||
                                  (TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]])==DInfo_rftk3_MassHypo[j] &&
                                   TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk3_index[j]]])==DInfo_rftk2_MassHypo[j] &&
                                   TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk1_index[j]]])==PION_PDGID &&
                                   TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk4_index[j]]])==PION_PDGID) ||
                                  (TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]])==DInfo_rftk4_MassHypo[j] &&
                                   TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk4_index[j]]])==DInfo_rftk2_MassHypo[j] &&
                                   TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk1_index[j]]])==PION_PDGID &&
                                   TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk3_index[j]]])==PION_PDGID) ||
                                  (TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk3_index[j]]])==DInfo_rftk4_MassHypo[j] &&
                                   TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk4_index[j]]])==DInfo_rftk3_MassHypo[j] &&
                                   TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk1_index[j]]])==PION_PDGID &&
                                   TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]])==PION_PDGID))
                            {
                              Dgen[typesize] = 23344;
                            }
                        }
                    }
                }
            }
        }
      Int_t dGenIdxRes = -1;
      if(DInfo_type[j]==7||DInfo_type[j]==8||DInfo_type[j]==9||DInfo_type[j]==10)
        {
          if(DInfo_tktkRes_rftk1_index[j]>-1 && DInfo_tktkRes_rftk2_index[j]>-1)
            {
              if(TrackInfo_geninfo_index[DInfo_tktkRes_rftk1_index[j]]>-1 && 
                 TrackInfo_geninfo_index[DInfo_tktkRes_rftk2_index[j]]>-1)
                {
                  if(GenInfo_mo1[TrackInfo_geninfo_index[DInfo_tktkRes_rftk1_index[j]]]>-1 && 
                     GenInfo_mo1[TrackInfo_geninfo_index[DInfo_tktkRes_rftk2_index[j]]]>-1)
                    {
                      if(TMath::Abs(GenInfo_pdgId[GenInfo_mo1[TrackInfo_geninfo_index[DInfo_tktkRes_rftk1_index[j]]]])==RpdgId && 
                         GenInfo_mo1[TrackInfo_geninfo_index[DInfo_tktkRes_rftk1_index[j]]]==GenInfo_mo1[TrackInfo_geninfo_index[DInfo_tktkRes_rftk2_index[j]]])
                        {
                          if(GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[DInfo_tktkRes_rftk1_index[j]]]]>-1 &&
                             GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[DInfo_tktkRes_rftk2_index[j]]]]>-1)
                            {
                              if(TMath::Abs(GenInfo_pdgId[GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[DInfo_tktkRes_rftk1_index[j]]]]])==DpdgId)
                                {
                                  if(TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_tktkRes_rftk1_index[j]]])==findPdgid(DInfo_tktkRes_rftk1_mass[j]) && 
                                     TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_tktkRes_rftk2_index[j]]])==findPdgid(DInfo_tktkRes_rftk2_mass[j]))
                                    {
                                      Dgen[typesize] = 3333;
                                      dGenIdxRes = GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[DInfo_tktkRes_rftk1_index[j]]]];
                                    }
                                  if((DInfo_type[j]==9||DInfo_type[j]==10) &&
                                     TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_tktkRes_rftk2_index[j]]])==findPdgid(DInfo_tktkRes_rftk1_mass[j]) && 
                                     TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_tktkRes_rftk1_index[j]]])==findPdgid(DInfo_tktkRes_rftk2_mass[j]))
                                    {
                                      Dgen[typesize] = 3344;
                                      dGenIdxRes = GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[DInfo_tktkRes_rftk1_index[j]]]];
                                    }
                                }
                            }
                        }
                    }
                }
            }
          if(DInfo_rftk2_index[j]>-1)
            {
              if(TrackInfo_geninfo_index[DInfo_rftk2_index[j]]>-1)
                {
                  if(GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]]>-1)
                    {
                      if(TMath::Abs(GenInfo_pdgId[GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]]])==DpdgId &&
                         GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]]==dGenIdxRes)
                        {
                          if(TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]])==PION_PDGID)
                            {
                              Dgen[typesize]+=20000;
                            }
                        }
                    }
                }
            }
        }
      dGenIdxRes = -1;
      if(DInfo_type[j]==11||DInfo_type[j]==12)
        {
          if(DInfo_tktkRes_rftk1_index[j]>-1 && DInfo_tktkRes_rftk2_index[j]>-1 && DInfo_tktkRes_rftk3_index[j]>-1 && DInfo_tktkRes_rftk4_index[j]>-1)
            {
              if(TrackInfo_geninfo_index[DInfo_tktkRes_rftk1_index[j]]>-1 && 
                 TrackInfo_geninfo_index[DInfo_tktkRes_rftk2_index[j]]>-1 && 
                 TrackInfo_geninfo_index[DInfo_tktkRes_rftk3_index[j]]>-1 && 
                 TrackInfo_geninfo_index[DInfo_tktkRes_rftk4_index[j]]>-1)
                {
                  if(GenInfo_mo1[TrackInfo_geninfo_index[DInfo_tktkRes_rftk1_index[j]]]>-1 && 
                     GenInfo_mo1[TrackInfo_geninfo_index[DInfo_tktkRes_rftk2_index[j]]]>-1 &&
                     GenInfo_mo1[TrackInfo_geninfo_index[DInfo_tktkRes_rftk3_index[j]]]>-1 &&
                     GenInfo_mo1[TrackInfo_geninfo_index[DInfo_tktkRes_rftk4_index[j]]]>-1)
                    {
                      if(TMath::Abs(GenInfo_pdgId[GenInfo_mo1[TrackInfo_geninfo_index[DInfo_tktkRes_rftk1_index[j]]]])==RpdgId && 
                         GenInfo_mo1[TrackInfo_geninfo_index[DInfo_tktkRes_rftk1_index[j]]]==GenInfo_mo1[TrackInfo_geninfo_index[DInfo_tktkRes_rftk2_index[j]]] &&
                         GenInfo_mo1[TrackInfo_geninfo_index[DInfo_tktkRes_rftk1_index[j]]]==GenInfo_mo1[TrackInfo_geninfo_index[DInfo_tktkRes_rftk3_index[j]]] &&
                         GenInfo_mo1[TrackInfo_geninfo_index[DInfo_tktkRes_rftk1_index[j]]]==GenInfo_mo1[TrackInfo_geninfo_index[DInfo_tktkRes_rftk4_index[j]]])
                        {
                          if(GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[DInfo_tktkRes_rftk1_index[j]]]]>-1)
                            {
                              if(TMath::Abs(GenInfo_pdgId[GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[DInfo_tktkRes_rftk1_index[j]]]]])==DpdgId)
                                {
                                  if(TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_tktkRes_rftk1_index[j]]])==findPdgid(DInfo_tktkRes_rftk1_mass[j]) && 
                                     TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_tktkRes_rftk2_index[j]]])==findPdgid(DInfo_tktkRes_rftk2_mass[j]) &&
                                     TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_tktkRes_rftk3_index[j]]])==findPdgid(DInfo_tktkRes_rftk3_mass[j]) &&
                                     TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_tktkRes_rftk4_index[j]]])==findPdgid(DInfo_tktkRes_rftk4_mass[j]))
                                    {
                                      Dgen[typesize] = 3333;
                                      dGenIdxRes = GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[DInfo_tktkRes_rftk1_index[j]]]];
                                    }
                                  else if((TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_tktkRes_rftk1_index[j]]])==findPdgid(DInfo_tktkRes_rftk2_mass[j]) && 
                                           TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_tktkRes_rftk2_index[j]]])==findPdgid(DInfo_tktkRes_rftk1_mass[j]) &&
                                           TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_tktkRes_rftk3_index[j]]])==PION_PDGID &&
                                           TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_tktkRes_rftk4_index[j]]])==PION_PDGID) ||
                                          (TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_tktkRes_rftk1_index[j]]])==findPdgid(DInfo_tktkRes_rftk3_mass[j]) && 
                                           TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_tktkRes_rftk3_index[j]]])==findPdgid(DInfo_tktkRes_rftk1_mass[j]) &&
                                           TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_tktkRes_rftk2_index[j]]])==PION_PDGID &&
                                           TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_tktkRes_rftk4_index[j]]])==PION_PDGID) ||
                                          (TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_tktkRes_rftk1_index[j]]])==findPdgid(DInfo_tktkRes_rftk4_mass[j]) && 
                                           TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_tktkRes_rftk4_index[j]]])==findPdgid(DInfo_tktkRes_rftk1_mass[j]) &&
                                           TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_tktkRes_rftk2_index[j]]])==PION_PDGID &&
                                           TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_tktkRes_rftk3_index[j]]])==PION_PDGID) ||
                                          (TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_tktkRes_rftk2_index[j]]])==findPdgid(DInfo_tktkRes_rftk3_mass[j]) && 
                                           TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_tktkRes_rftk3_index[j]]])==findPdgid(DInfo_tktkRes_rftk2_mass[j]) &&
                                           TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_tktkRes_rftk1_index[j]]])==PION_PDGID &&
                                           TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_tktkRes_rftk4_index[j]]])==PION_PDGID) ||
                                          (TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_tktkRes_rftk2_index[j]]])==findPdgid(DInfo_tktkRes_rftk4_mass[j]) && 
                                           TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_tktkRes_rftk4_index[j]]])==findPdgid(DInfo_tktkRes_rftk2_mass[j]) &&
                                           TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_tktkRes_rftk1_index[j]]])==PION_PDGID &&
                                           TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_tktkRes_rftk3_index[j]]])==PION_PDGID) ||
                                          (TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_tktkRes_rftk3_index[j]]])==findPdgid(DInfo_tktkRes_rftk4_mass[j]) && 
                                           TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_tktkRes_rftk4_index[j]]])==findPdgid(DInfo_tktkRes_rftk3_mass[j]) &&
                                           TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_tktkRes_rftk1_index[j]]])==PION_PDGID &&
                                           TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_tktkRes_rftk2_index[j]]])==PION_PDGID))
                                    {
                                      Dgen[typesize] = 3344;
                                      dGenIdxRes = GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[DInfo_tktkRes_rftk1_index[j]]]];
                                    }
                                }
                            }
                        }
                    }
                }
            }
          if(DInfo_rftk2_index[j]>-1)
            {
              if(TrackInfo_geninfo_index[DInfo_rftk2_index[j]]>-1)
                {
                  if(GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]]>-1)
                    {
                      if(TMath::Abs(GenInfo_pdgId[GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]]])==DpdgId &&
                         GenInfo_mo1[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]]==dGenIdxRes)
                        {
                          if(TMath::Abs(GenInfo_pdgId[TrackInfo_geninfo_index[DInfo_rftk2_index[j]]])==PION_PDGID)
                            {
                              Dgen[typesize]+=20000;
                            }
                        }
                    }
                }
            }
        }
      
      if(Dgen[typesize]==23333||Dgen[typesize]==23344)
	{
	  DgenIndex[typesize] = dGenIdxRes;
	  if((DInfo_type[j]==1||DInfo_type[j]==2)&&GenInfo_nDa[DgenIndex[typesize]]>2) Dgen[typesize]=41000;
	  DgennDa[typesize] = GenInfo_nDa[DgenIndex[typesize]];
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

bool isDsignalGen(Int_t dmesontype, Int_t j)
{
  bool flag=false;
  if(dmesontype==1||dmesontype==2)
    {
      if(TMath::Abs(GenInfo_pdgId[j])==DZERO_PDGID&&GenInfo_nDa[j]==2&&GenInfo_da1[j]!=-1&&GenInfo_da2[j]!=-1)
	{
	  if((TMath::Abs(GenInfo_pdgId[GenInfo_da1[j]])==KAON_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da2[j]])==PION_PDGID) || 
	     (TMath::Abs(GenInfo_pdgId[GenInfo_da1[j]])==PION_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da2[j]])==KAON_PDGID))
	    {
	      flag=true;
	    }
	}
    }
  if(dmesontype==3||dmesontype==4)
    {
      if(TMath::Abs(GenInfo_pdgId[j])==DPLUS_PDGID&&GenInfo_nDa[j]==3&&GenInfo_da1[j]!=-1&&GenInfo_da2[j]!=-1&&GenInfo_da3[j]!=-1)
        {
          if((TMath::Abs(GenInfo_pdgId[GenInfo_da1[j]])==KAON_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da2[j]])==PION_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da3[j]])==PION_PDGID) ||
             (TMath::Abs(GenInfo_pdgId[GenInfo_da2[j]])==KAON_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da1[j]])==PION_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da3[j]])==PION_PDGID) ||
             (TMath::Abs(GenInfo_pdgId[GenInfo_da3[j]])==KAON_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da1[j]])==PION_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da2[j]])==PION_PDGID))
            {
              flag=true;
            }
        }
    }
  if(dmesontype==5||dmesontype==6)
    {
      if(TMath::Abs(GenInfo_pdgId[j])==DZERO_PDGID&&GenInfo_nDa[j]==4&&GenInfo_da1[j]!=-1&&GenInfo_da2[j]!=-1&&GenInfo_da3[j]!=-1&&GenInfo_da4[j]!=-1)
        {
          if((TMath::Abs(GenInfo_pdgId[GenInfo_da1[j]])==KAON_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da2[j]])==PION_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da3[j]])==PION_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da4[j]])==PION_PDGID) ||
             (TMath::Abs(GenInfo_pdgId[GenInfo_da2[j]])==KAON_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da1[j]])==PION_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da3[j]])==PION_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da4[j]])==PION_PDGID) ||
             (TMath::Abs(GenInfo_pdgId[GenInfo_da3[j]])==KAON_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da1[j]])==PION_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da2[j]])==PION_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da4[j]])==PION_PDGID) ||
             (TMath::Abs(GenInfo_pdgId[GenInfo_da4[j]])==KAON_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da1[j]])==PION_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da2[j]])==PION_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da3[j]])==PION_PDGID))
            {
              flag=true;
            }
        }
    }
  if(dmesontype==7||dmesontype==8)
    {
      if(TMath::Abs(GenInfo_pdgId[j])==DSUBS_PDGID&&GenInfo_nDa[j]==2&&GenInfo_da1[j]!=-1&&GenInfo_da2[j]!=-1)
	{
	  if(TMath::Abs(GenInfo_pdgId[GenInfo_da1[j]])==PHI_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da2[j]])==PION_PDGID)
	    {
              if(GenInfo_nDa[GenInfo_da1[j]]==2&&GenInfo_da1[GenInfo_da1[j]]!=-1&&GenInfo_da2[GenInfo_da1[j]]!=-1)
                {
                  if(TMath::Abs(GenInfo_pdgId[GenInfo_da1[GenInfo_da1[j]]])==KAON_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da2[GenInfo_da1[j]]])==KAON_PDGID)
                    {
                      flag=true;                      
                    }
                }
	    }
	}
    }
  if(dmesontype==9||dmesontype==10)
    {
      if(TMath::Abs(GenInfo_pdgId[j])==DSTAR_PDGID&&GenInfo_nDa[j]==2&&GenInfo_da1[j]!=-1&&GenInfo_da2[j]!=-1)
	{
	  if(TMath::Abs(GenInfo_pdgId[GenInfo_da1[j]])==DZERO_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da2[j]])==PION_PDGID)
	    {
              if(GenInfo_nDa[GenInfo_da1[j]]==2&&GenInfo_da1[GenInfo_da1[j]]!=-1&&GenInfo_da2[GenInfo_da1[j]]!=-1)
                {
                  if((TMath::Abs(GenInfo_pdgId[GenInfo_da1[GenInfo_da1[j]]])==PION_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da2[GenInfo_da1[j]]])==KAON_PDGID)||
                     (TMath::Abs(GenInfo_pdgId[GenInfo_da1[GenInfo_da1[j]]])==KAON_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da2[GenInfo_da1[j]]])==PION_PDGID))
                    {
                      flag=true;                      
                    }
                }
	    }
	}
    }
  if(dmesontype==11||dmesontype==12)
    {
      if(TMath::Abs(GenInfo_pdgId[j])==DSTAR_PDGID&&GenInfo_nDa[j]==2&&GenInfo_da1[j]!=-1&&GenInfo_da2[j]!=-1)
	{
	  if(TMath::Abs(GenInfo_pdgId[GenInfo_da1[j]])==DZERO_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da2[j]])==PION_PDGID)
	    {
              if(GenInfo_nDa[GenInfo_da1[j]]==4&&GenInfo_da1[GenInfo_da1[j]]!=-1&&GenInfo_da2[GenInfo_da1[j]]!=-1)
                {
                  if((TMath::Abs(GenInfo_pdgId[GenInfo_da1[GenInfo_da1[j]]])==KAON_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da2[GenInfo_da1[j]]])==PION_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da3[GenInfo_da1[j]]])==PION_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da4[GenInfo_da1[j]]])==PION_PDGID) ||
                     (TMath::Abs(GenInfo_pdgId[GenInfo_da2[GenInfo_da1[j]]])==KAON_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da1[GenInfo_da1[j]]])==PION_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da3[GenInfo_da1[j]]])==PION_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da4[GenInfo_da1[j]]])==PION_PDGID) ||
                     (TMath::Abs(GenInfo_pdgId[GenInfo_da3[GenInfo_da1[j]]])==KAON_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da1[GenInfo_da1[j]]])==PION_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da2[GenInfo_da1[j]]])==PION_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da4[GenInfo_da1[j]]])==PION_PDGID) ||
                     (TMath::Abs(GenInfo_pdgId[GenInfo_da4[GenInfo_da1[j]]])==KAON_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da1[GenInfo_da1[j]]])==PION_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da2[GenInfo_da1[j]]])==PION_PDGID&&TMath::Abs(GenInfo_pdgId[GenInfo_da3[GenInfo_da1[j]]])==PION_PDGID))
                    {
                      flag=true;                      
                    }
                }
	    }
	}
    }
  return flag;
}


int main(int argc, char *argv[])
{
  if((argc != 3) && (argc != 4))
  {
    std::cout << "Usage: mergeForest <input_collection> <output_file>" << std::endl;
    return 1;
  }
  
  if(argc == 3)
    loop(argv[1], argv[2]);
  //else if (argc == 4)
  //  loop(argv[1], argv[2], argv[3]);
  return 0;
}
