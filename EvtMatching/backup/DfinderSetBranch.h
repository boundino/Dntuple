#include <TTree.h>

#define MAX_XB 16384
#define MAX_MUON 512
#define MAX_TRACK 4096
#define MAX_GEN 8192
#define MAX_BX 128
#define MAX_Vertices 4096
//#define N_TRIGGER_BOOKINGS 5842

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Build Branch //////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

//build
//EvtInfo
Int_t           bld_EvtInfo_RunNo;
Int_t           bld_EvtInfo_EvtNo;
Int_t           bld_EvtInfo_BxNo;
Int_t           bld_EvtInfo_LumiNo;
Int_t           bld_EvtInfo_Orbit;
Bool_t          bld_EvtInfo_McFlag;
Int_t           bld_EvtInfo_nBX;
Int_t           bld_EvtInfo_BXPU[MAX_BX];
Int_t           bld_EvtInfo_nPU[MAX_BX];
Float_t         bld_EvtInfo_trueIT[MAX_BX];
Double_t        bld_EvtInfo_PVx;
Double_t        bld_EvtInfo_PVy;
Double_t        bld_EvtInfo_PVz;
Double_t        bld_EvtInfo_PVxE;
Double_t        bld_EvtInfo_PVyE;
Double_t        bld_EvtInfo_PVzE;
Double_t        bld_EvtInfo_PVnchi2;
Double_t        bld_EvtInfo_PVchi2;
//VtxInfo
Int_t           bld_VtxInfo_Size;
Int_t           bld_VtxInfo_isValid[MAX_Vertices];
Bool_t          bld_VtxInfo_isFake[MAX_Vertices];
Float_t         bld_VtxInfo_Ndof[MAX_Vertices];
Float_t         bld_VtxInfo_NormalizedChi2[MAX_Vertices];
Float_t         bld_VtxInfo_Pt_Sum[MAX_Vertices];
Float_t         bld_VtxInfo_Pt_Sum2[MAX_Vertices];
Float_t         bld_VtxInfo_x[MAX_Vertices];
Float_t         bld_VtxInfo_y[MAX_Vertices];
Float_t         bld_VtxInfo_z[MAX_Vertices];
//TrackInfo
Int_t           bld_TrackInfo_size;
Int_t           bld_TrackInfo_index[MAX_TRACK];
Int_t           bld_TrackInfo_handle_index[MAX_TRACK];
Int_t           bld_TrackInfo_charge[MAX_TRACK];
Double_t        bld_TrackInfo_pt[MAX_TRACK];
Double_t        bld_TrackInfo_eta[MAX_TRACK];
Double_t        bld_TrackInfo_phi[MAX_TRACK];
Double_t        bld_TrackInfo_ptErr[MAX_TRACK];
Double_t        bld_TrackInfo_etaErr[MAX_TRACK];
Double_t        bld_TrackInfo_phiErr[MAX_TRACK];
Int_t           bld_TrackInfo_striphit[MAX_TRACK];
Int_t           bld_TrackInfo_pixelhit[MAX_TRACK];
Int_t           bld_TrackInfo_nStripLayer[MAX_TRACK];
Int_t           bld_TrackInfo_nPixelLayer[MAX_TRACK];
Int_t           bld_TrackInfo_fpbarrelhit[MAX_TRACK];
Int_t           bld_TrackInfo_fpendcaphit[MAX_TRACK];
Double_t        bld_TrackInfo_chi2[MAX_TRACK];
Double_t        bld_TrackInfo_ndf[MAX_TRACK];
Double_t        bld_TrackInfo_d0[MAX_TRACK];
Double_t        bld_TrackInfo_d0error[MAX_TRACK];
Double_t        bld_TrackInfo_dzPV[MAX_TRACK];
Double_t        bld_TrackInfo_dxyPV[MAX_TRACK];
Int_t           bld_TrackInfo_geninfo_index[MAX_TRACK];
Int_t           bld_TrackInfo_trackQuality[MAX_TRACK];
Bool_t          bld_TrackInfo_highPurity[MAX_TRACK];
//DInfo
Int_t           bld_DInfo_size;
Int_t           bld_DInfo_index[MAX_XB];
Int_t           bld_DInfo_type[MAX_XB];    

Double_t        bld_DInfo_b4fit_mass[MAX_XB];
Double_t        bld_DInfo_b4fit_pt[MAX_XB];
Double_t        bld_DInfo_b4fit_eta[MAX_XB];
Double_t        bld_DInfo_b4fit_phi[MAX_XB];

Double_t        bld_DInfo_tktkRes_mass[MAX_XB];
Double_t        bld_DInfo_tktkRes_pt[MAX_XB];
Double_t        bld_DInfo_tktkRes_eta[MAX_XB];
Double_t        bld_DInfo_tktkRes_phi[MAX_XB];
Double_t        bld_DInfo_tktkRes_px[MAX_XB];
Double_t        bld_DInfo_tktkRes_py[MAX_XB];
Double_t        bld_DInfo_tktkRes_pz[MAX_XB];
Double_t        bld_DInfo_tktkRes_vtxX[MAX_XB];
Double_t        bld_DInfo_tktkRes_vtxY[MAX_XB];
Double_t        bld_DInfo_tktkRes_vtxZ[MAX_XB];
Double_t        bld_DInfo_tktkRes_vtxXE[MAX_XB];
Double_t        bld_DInfo_tktkRes_vtxYE[MAX_XB];
Double_t        bld_DInfo_tktkRes_vtxZE[MAX_XB];
Double_t        bld_DInfo_tktkRes_vtxdof[MAX_XB];
Double_t        bld_DInfo_tktkRes_vtxchi2[MAX_XB];
Double_t        bld_DInfo_tktkRes_rftk1_pt[MAX_XB];
Double_t        bld_DInfo_tktkRes_rftk1_eta[MAX_XB];
Double_t        bld_DInfo_tktkRes_rftk1_phi[MAX_XB];
Double_t        bld_DInfo_tktkRes_rftk2_pt[MAX_XB];
Double_t        bld_DInfo_tktkRes_rftk2_eta[MAX_XB];
Double_t        bld_DInfo_tktkRes_rftk2_phi[MAX_XB];

Double_t        bld_DInfo_mass[MAX_XB];
Double_t        bld_DInfo_pt[MAX_XB];
Double_t        bld_DInfo_eta[MAX_XB];
Double_t        bld_DInfo_phi[MAX_XB];
Double_t        bld_DInfo_px[MAX_XB];
Double_t        bld_DInfo_py[MAX_XB];
Double_t        bld_DInfo_pz[MAX_XB];
Double_t        bld_DInfo_alpha[MAX_XB];
Double_t        bld_DInfo_svpvDistance[MAX_XB];
Double_t        bld_DInfo_svpvDisErr[MAX_XB];
Double_t        bld_DInfo_MaxDoca[MAX_XB];
Double_t        bld_DInfo_vtxX[MAX_XB];
Double_t        bld_DInfo_vtxY[MAX_XB];
Double_t        bld_DInfo_vtxZ[MAX_XB];
Double_t        bld_DInfo_vtxXE[MAX_XB];
Double_t        bld_DInfo_vtxYE[MAX_XB];
Double_t        bld_DInfo_vtxZE[MAX_XB];
Double_t        bld_DInfo_vtxdof[MAX_XB];
Double_t        bld_DInfo_vtxchi2[MAX_XB];

Double_t        bld_DInfo_rftk1_px[MAX_XB];
Double_t        bld_DInfo_rftk1_py[MAX_XB];
Double_t        bld_DInfo_rftk1_pz[MAX_XB];
Double_t        bld_DInfo_rftk2_px[MAX_XB];
Double_t        bld_DInfo_rftk2_py[MAX_XB];
Double_t        bld_DInfo_rftk2_pz[MAX_XB];
Double_t        bld_DInfo_rftk3_px[MAX_XB];
Double_t        bld_DInfo_rftk3_py[MAX_XB];
Double_t        bld_DInfo_rftk3_pz[MAX_XB];
Double_t        bld_DInfo_rftk4_px[MAX_XB];
Double_t        bld_DInfo_rftk4_py[MAX_XB];
Double_t        bld_DInfo_rftk4_pz[MAX_XB];
Double_t        bld_DInfo_rftk1_pt[MAX_XB];
Double_t        bld_DInfo_rftk1_eta[MAX_XB];
Double_t        bld_DInfo_rftk1_phi[MAX_XB];
Double_t        bld_DInfo_rftk2_pt[MAX_XB];
Double_t        bld_DInfo_rftk2_eta[MAX_XB];
Double_t        bld_DInfo_rftk2_phi[MAX_XB];
Double_t        bld_DInfo_rftk3_pt[MAX_XB];
Double_t        bld_DInfo_rftk3_eta[MAX_XB];
Double_t        bld_DInfo_rftk3_phi[MAX_XB];
Double_t        bld_DInfo_rftk4_pt[MAX_XB];
Double_t        bld_DInfo_rftk4_eta[MAX_XB];
Double_t        bld_DInfo_rftk4_phi[MAX_XB];
Int_t           bld_DInfo_rftk1_index[MAX_XB];
Int_t           bld_DInfo_rftk2_index[MAX_XB];
Int_t           bld_DInfo_rftk3_index[MAX_XB];
Int_t           bld_DInfo_rftk4_index[MAX_XB];
Int_t           bld_DInfo_rftk1_MassHypo[MAX_XB];
Int_t           bld_DInfo_rftk2_MassHypo[MAX_XB];
Int_t           bld_DInfo_rftk3_MassHypo[MAX_XB];
Int_t           bld_DInfo_rftk4_MassHypo[MAX_XB];

//GenInfo
Int_t           bld_GenInfo_size;
Int_t           bld_GenInfo_index[MAX_GEN];
Int_t           bld_GenInfo_handle_index[MAX_GEN];
Double_t        bld_GenInfo_pt[MAX_GEN];
Double_t        bld_GenInfo_eta[MAX_GEN];
Double_t        bld_GenInfo_phi[MAX_GEN];
Double_t        bld_GenInfo_mass[MAX_GEN];
Int_t           bld_GenInfo_pdgId[MAX_GEN];
Int_t           bld_GenInfo_status[MAX_GEN];
Int_t           bld_GenInfo_nMo[MAX_GEN];
Int_t           bld_GenInfo_nDa[MAX_GEN];
Int_t           bld_GenInfo_mo1[MAX_GEN];
Int_t           bld_GenInfo_mo2[MAX_GEN];
Int_t           bld_GenInfo_da1[MAX_GEN];
Int_t           bld_GenInfo_da2[MAX_GEN];
Int_t           bld_GenInfo_da3[MAX_GEN];
Int_t           bld_GenInfo_da4[MAX_GEN];


void buildDBranch(TTree* dnt)
{
  //EvtInfo

  //DInfo

  //DInfo.b4fitInfo

  //DInfo.trkInfo

  //DInfo.tktkResInfo

  //DInfo.genInfo

}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Set Branch //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Int_t           RecoRunNo;
Int_t           RecoLumiNo;
Int_t           RecoEvtNo;
void setEvtDBranch(TTree *root)
{
  //EvtInfo
  root->SetBranchAddress("EvtInfo.RunNo",&RecoRunNo);
  root->SetBranchAddress("EvtInfo.EvtNo",&RecoEvtNo);
  root->SetBranchAddress("EvtInfo.LumiNo",&RecoLumiNo);
}
Int_t           HltRun;
ULong64_t       HltEvent;
Int_t           HltLumiBlock;
void setEvtHLTBranch(TTree* hltroot)
{
  hltroot->SetBranchAddress("Run",&HltRun);
  hltroot->SetBranchAddress("Event",&HltEvent);
  hltroot->SetBranchAddress("LumiBlock",&HltLumiBlock);
}


//EvtInfo
Int_t           EvtInfo_RunNo;
Int_t           EvtInfo_EvtNo;
Int_t           EvtInfo_BxNo;
Int_t           EvtInfo_LumiNo;
Int_t           EvtInfo_Orbit;
Bool_t          EvtInfo_McFlag;
Int_t           EvtInfo_nBX;
Int_t           EvtInfo_BXPU[MAX_BX];
Int_t           EvtInfo_nPU[MAX_BX];
Float_t         EvtInfo_trueIT[MAX_BX];
Double_t        EvtInfo_PVx;
Double_t        EvtInfo_PVy;
Double_t        EvtInfo_PVz;
Double_t        EvtInfo_PVxE;
Double_t        EvtInfo_PVyE;
Double_t        EvtInfo_PVzE;
Double_t        EvtInfo_PVnchi2;
Double_t        EvtInfo_PVchi2;
//VtxInfo
Int_t           VtxInfo_Size;
Int_t           VtxInfo_isValid[MAX_Vertices];
Bool_t          VtxInfo_isFake[MAX_Vertices];
Float_t         VtxInfo_Ndof[MAX_Vertices];
Float_t         VtxInfo_NormalizedChi2[MAX_Vertices];
Float_t         VtxInfo_Pt_Sum[MAX_Vertices];
Float_t         VtxInfo_Pt_Sum2[MAX_Vertices];
Float_t         VtxInfo_x[MAX_Vertices];
Float_t         VtxInfo_y[MAX_Vertices];
Float_t         VtxInfo_z[MAX_Vertices];
//TrackInfo
Int_t           TrackInfo_size;
Int_t           TrackInfo_index[MAX_TRACK];
Int_t           TrackInfo_handle_index[MAX_TRACK];
Int_t           TrackInfo_charge[MAX_TRACK];
Double_t        TrackInfo_pt[MAX_TRACK];
Double_t        TrackInfo_eta[MAX_TRACK];
Double_t        TrackInfo_phi[MAX_TRACK];
Double_t        TrackInfo_ptErr[MAX_TRACK];
Double_t        TrackInfo_etaErr[MAX_TRACK];
Double_t        TrackInfo_phiErr[MAX_TRACK];
Int_t           TrackInfo_striphit[MAX_TRACK];
Int_t           TrackInfo_pixelhit[MAX_TRACK];
Int_t           TrackInfo_nStripLayer[MAX_TRACK];
Int_t           TrackInfo_nPixelLayer[MAX_TRACK];
Int_t           TrackInfo_fpbarrelhit[MAX_TRACK];
Int_t           TrackInfo_fpendcaphit[MAX_TRACK];
Double_t        TrackInfo_chi2[MAX_TRACK];
Double_t        TrackInfo_ndf[MAX_TRACK];
Double_t        TrackInfo_d0[MAX_TRACK];
Double_t        TrackInfo_d0error[MAX_TRACK];
Double_t        TrackInfo_dzPV[MAX_TRACK];
Double_t        TrackInfo_dxyPV[MAX_TRACK];
Int_t           TrackInfo_geninfo_index[MAX_TRACK];
Int_t           TrackInfo_trackQuality[MAX_TRACK];
Bool_t          TrackInfo_highPurity[MAX_TRACK];
//DInfo
Int_t           DInfo_size;
Int_t           DInfo_index[MAX_XB];
Int_t           DInfo_type[MAX_XB];    

Double_t        DInfo_b4fit_mass[MAX_XB];
Double_t        DInfo_b4fit_pt[MAX_XB];
Double_t        DInfo_b4fit_eta[MAX_XB];
Double_t        DInfo_b4fit_phi[MAX_XB];

Double_t        DInfo_tktkRes_mass[MAX_XB];
Double_t        DInfo_tktkRes_pt[MAX_XB];
Double_t        DInfo_tktkRes_eta[MAX_XB];
Double_t        DInfo_tktkRes_phi[MAX_XB];
Double_t        DInfo_tktkRes_px[MAX_XB];
Double_t        DInfo_tktkRes_py[MAX_XB];
Double_t        DInfo_tktkRes_pz[MAX_XB];
Double_t        DInfo_tktkRes_vtxX[MAX_XB];
Double_t        DInfo_tktkRes_vtxY[MAX_XB];
Double_t        DInfo_tktkRes_vtxZ[MAX_XB];
Double_t        DInfo_tktkRes_vtxXE[MAX_XB];
Double_t        DInfo_tktkRes_vtxYE[MAX_XB];
Double_t        DInfo_tktkRes_vtxZE[MAX_XB];
Double_t        DInfo_tktkRes_vtxdof[MAX_XB];
Double_t        DInfo_tktkRes_vtxchi2[MAX_XB];
Double_t        DInfo_tktkRes_rftk1_pt[MAX_XB];
Double_t        DInfo_tktkRes_rftk1_eta[MAX_XB];
Double_t        DInfo_tktkRes_rftk1_phi[MAX_XB];
Double_t        DInfo_tktkRes_rftk2_pt[MAX_XB];
Double_t        DInfo_tktkRes_rftk2_eta[MAX_XB];
Double_t        DInfo_tktkRes_rftk2_phi[MAX_XB];

Double_t        DInfo_mass[MAX_XB];
Double_t        DInfo_pt[MAX_XB];
Double_t        DInfo_eta[MAX_XB];
Double_t        DInfo_phi[MAX_XB];
Double_t        DInfo_px[MAX_XB];
Double_t        DInfo_py[MAX_XB];
Double_t        DInfo_pz[MAX_XB];
Double_t        DInfo_alpha[MAX_XB];
Double_t        DInfo_svpvDistance[MAX_XB];
Double_t        DInfo_svpvDisErr[MAX_XB];
Double_t        DInfo_MaxDoca[MAX_XB];
Double_t        DInfo_vtxX[MAX_XB];
Double_t        DInfo_vtxY[MAX_XB];
Double_t        DInfo_vtxZ[MAX_XB];
Double_t        DInfo_vtxXE[MAX_XB];
Double_t        DInfo_vtxYE[MAX_XB];
Double_t        DInfo_vtxZE[MAX_XB];
Double_t        DInfo_vtxdof[MAX_XB];
Double_t        DInfo_vtxchi2[MAX_XB];

Double_t        DInfo_rftk1_px[MAX_XB];
Double_t        DInfo_rftk1_py[MAX_XB];
Double_t        DInfo_rftk1_pz[MAX_XB];
Double_t        DInfo_rftk2_px[MAX_XB];
Double_t        DInfo_rftk2_py[MAX_XB];
Double_t        DInfo_rftk2_pz[MAX_XB];
Double_t        DInfo_rftk3_px[MAX_XB];
Double_t        DInfo_rftk3_py[MAX_XB];
Double_t        DInfo_rftk3_pz[MAX_XB];
Double_t        DInfo_rftk4_px[MAX_XB];
Double_t        DInfo_rftk4_py[MAX_XB];
Double_t        DInfo_rftk4_pz[MAX_XB];
Double_t        DInfo_rftk1_pt[MAX_XB];
Double_t        DInfo_rftk1_eta[MAX_XB];
Double_t        DInfo_rftk1_phi[MAX_XB];
Double_t        DInfo_rftk2_pt[MAX_XB];
Double_t        DInfo_rftk2_eta[MAX_XB];
Double_t        DInfo_rftk2_phi[MAX_XB];
Double_t        DInfo_rftk3_pt[MAX_XB];
Double_t        DInfo_rftk3_eta[MAX_XB];
Double_t        DInfo_rftk3_phi[MAX_XB];
Double_t        DInfo_rftk4_pt[MAX_XB];
Double_t        DInfo_rftk4_eta[MAX_XB];
Double_t        DInfo_rftk4_phi[MAX_XB];
Int_t           DInfo_rftk1_index[MAX_XB];
Int_t           DInfo_rftk2_index[MAX_XB];
Int_t           DInfo_rftk3_index[MAX_XB];
Int_t           DInfo_rftk4_index[MAX_XB];
Int_t           DInfo_rftk1_MassHypo[MAX_XB];
Int_t           DInfo_rftk2_MassHypo[MAX_XB];
Int_t           DInfo_rftk3_MassHypo[MAX_XB];
Int_t           DInfo_rftk4_MassHypo[MAX_XB];

//GenInfo
Int_t           GenInfo_size;
Int_t           GenInfo_index[MAX_GEN];
Int_t           GenInfo_handle_index[MAX_GEN];
Double_t        GenInfo_pt[MAX_GEN];
Double_t        GenInfo_eta[MAX_GEN];
Double_t        GenInfo_phi[MAX_GEN];
Double_t        GenInfo_mass[MAX_GEN];
Int_t           GenInfo_pdgId[MAX_GEN];
Int_t           GenInfo_status[MAX_GEN];
Int_t           GenInfo_nMo[MAX_GEN];
Int_t           GenInfo_nDa[MAX_GEN];
Int_t           GenInfo_mo1[MAX_GEN];
Int_t           GenInfo_mo2[MAX_GEN];
Int_t           GenInfo_da1[MAX_GEN];
Int_t           GenInfo_da2[MAX_GEN];
Int_t           GenInfo_da3[MAX_GEN];
Int_t           GenInfo_da4[MAX_GEN];

void setDBranch(TTree *root)
{
  //EvtInfo
  root->SetBranchAddress("EvtInfo.RunNo",&EvtInfo_RunNo);
  root->SetBranchAddress("EvtInfo.EvtNo",&EvtInfo_EvtNo);
  root->SetBranchAddress("EvtInfo.BxNo",&EvtInfo_BxNo);
  root->SetBranchAddress("EvtInfo.LumiNo",&EvtInfo_LumiNo);
  root->SetBranchAddress("EvtInfo.Orbit",&EvtInfo_Orbit);
  root->SetBranchAddress("EvtInfo.McFlag",&EvtInfo_McFlag);
  root->SetBranchAddress("EvtInfo.nBX",&EvtInfo_nBX);
  root->SetBranchAddress("EvtInfo.BXPU",EvtInfo_BXPU);
  root->SetBranchAddress("EvtInfo.nPU",EvtInfo_nPU);
  root->SetBranchAddress("EvtInfo.trueIT",EvtInfo_trueIT);
  root->SetBranchAddress("EvtInfo.PVx",&EvtInfo_PVx);
  root->SetBranchAddress("EvtInfo.PVy",&EvtInfo_PVy);
  root->SetBranchAddress("EvtInfo.PVz",&EvtInfo_PVz);
  root->SetBranchAddress("EvtInfo.PVxE",&EvtInfo_PVxE);
  root->SetBranchAddress("EvtInfo.PVyE",&EvtInfo_PVyE);
  root->SetBranchAddress("EvtInfo.PVzE",&EvtInfo_PVzE);
  root->SetBranchAddress("EvtInfo.PVnchi2",&EvtInfo_PVnchi2);
  root->SetBranchAddress("EvtInfo.PVchi2",&EvtInfo_PVchi2);
  //TrackInfo
  root->SetBranchAddress("TrackInfo.size",&TrackInfo_size);
  root->SetBranchAddress("TrackInfo.index",TrackInfo_index);
  root->SetBranchAddress("TrackInfo.handle_index",TrackInfo_handle_index);
  root->SetBranchAddress("TrackInfo.charge",TrackInfo_charge);
  root->SetBranchAddress("TrackInfo.pt",TrackInfo_pt);
  root->SetBranchAddress("TrackInfo.eta",TrackInfo_eta);
  root->SetBranchAddress("TrackInfo.phi",TrackInfo_phi);
  root->SetBranchAddress("TrackInfo.ptErr",TrackInfo_ptErr);
  root->SetBranchAddress("TrackInfo.etaErr",TrackInfo_etaErr);
  root->SetBranchAddress("TrackInfo.phiErr",TrackInfo_phiErr);
  root->SetBranchAddress("TrackInfo.striphit",TrackInfo_striphit);
  root->SetBranchAddress("TrackInfo.pixelhit",TrackInfo_pixelhit);
  root->SetBranchAddress("TrackInfo.nStripLayer",TrackInfo_nStripLayer);
  root->SetBranchAddress("TrackInfo.nPixelLayer",TrackInfo_nPixelLayer);
  root->SetBranchAddress("TrackInfo.fpbarrelhit",TrackInfo_fpbarrelhit);
  root->SetBranchAddress("TrackInfo.fpendcaphit",TrackInfo_fpendcaphit);
  root->SetBranchAddress("TrackInfo.chi2",TrackInfo_chi2);
  root->SetBranchAddress("TrackInfo.ndf",TrackInfo_ndf);
  root->SetBranchAddress("TrackInfo.d0",TrackInfo_d0);
  root->SetBranchAddress("TrackInfo.d0error",TrackInfo_d0error);
  root->SetBranchAddress("TrackInfo.dzPV",TrackInfo_dzPV);
  root->SetBranchAddress("TrackInfo.dxyPV",TrackInfo_dxyPV);
  root->SetBranchAddress("TrackInfo.geninfo_index",TrackInfo_geninfo_index);
  root->SetBranchAddress("TrackInfo.trackQuality",TrackInfo_trackQuality);
  root->SetBranchAddress("TrackInfo.highPurity",TrackInfo_highPurity);
  //DInfo
  root->SetBranchAddress("DInfo.size",&DInfo_size);
  root->SetBranchAddress("DInfo.index",DInfo_index);
  root->SetBranchAddress("DInfo.type",DInfo_type);
  root->SetBranchAddress("DInfo.b4fit_mass",DInfo_b4fit_mass);
  root->SetBranchAddress("DInfo.b4fit_pt",DInfo_b4fit_pt);
  root->SetBranchAddress("DInfo.b4fit_eta",DInfo_b4fit_eta);
  root->SetBranchAddress("DInfo.b4fit_phi",DInfo_b4fit_phi);
  root->SetBranchAddress("DInfo.tktkRes_mass",DInfo_tktkRes_mass);
  root->SetBranchAddress("DInfo.tktkRes_pt",DInfo_tktkRes_pt);
  root->SetBranchAddress("DInfo.tktkRes_eta",DInfo_tktkRes_eta);
  root->SetBranchAddress("DInfo.tktkRes_phi",DInfo_tktkRes_phi);
  root->SetBranchAddress("DInfo.tktkRes_px",DInfo_tktkRes_px);
  root->SetBranchAddress("DInfo.tktkRes_py",DInfo_tktkRes_py);
  root->SetBranchAddress("DInfo.tktkRes_pz",DInfo_tktkRes_pz);
  root->SetBranchAddress("DInfo.tktkRes_vtxX",DInfo_tktkRes_vtxX);
  root->SetBranchAddress("DInfo.tktkRes_vtxY",DInfo_tktkRes_vtxY);
  root->SetBranchAddress("DInfo.tktkRes_vtxZ",DInfo_tktkRes_vtxZ);
  root->SetBranchAddress("DInfo.tktkRes_vtxXE",DInfo_tktkRes_vtxXE);
  root->SetBranchAddress("DInfo.tktkRes_vtxYE",DInfo_tktkRes_vtxYE);
  root->SetBranchAddress("DInfo.tktkRes_vtxZE",DInfo_tktkRes_vtxZE);
  root->SetBranchAddress("DInfo.tktkRes_vtxdof",DInfo_tktkRes_vtxdof);
  root->SetBranchAddress("DInfo.tktkRes_vtxchi2",DInfo_tktkRes_vtxchi2);
  root->SetBranchAddress("DInfo.tktkRes_rftk1_pt",DInfo_tktkRes_rftk1_pt);
  root->SetBranchAddress("DInfo.tktkRes_rftk1_eta",DInfo_tktkRes_rftk1_eta);
  root->SetBranchAddress("DInfo.tktkRes_rftk1_phi",DInfo_tktkRes_rftk1_phi);
  root->SetBranchAddress("DInfo.tktkRes_rftk2_pt",DInfo_tktkRes_rftk2_pt);
  root->SetBranchAddress("DInfo.tktkRes_rftk2_eta",DInfo_tktkRes_rftk2_eta);
  root->SetBranchAddress("DInfo.tktkRes_rftk2_phi",DInfo_tktkRes_rftk2_phi);
  root->SetBranchAddress("DInfo.mass",DInfo_mass);
  root->SetBranchAddress("DInfo.pt",DInfo_pt);
  root->SetBranchAddress("DInfo.eta",DInfo_eta);
  root->SetBranchAddress("DInfo.phi",DInfo_phi);
  root->SetBranchAddress("DInfo.px",DInfo_px);
  root->SetBranchAddress("DInfo.py",DInfo_py);
  root->SetBranchAddress("DInfo.pz",DInfo_pz);
  root->SetBranchAddress("DInfo.alpha",DInfo_alpha);
  root->SetBranchAddress("DInfo.svpvDistance",DInfo_svpvDistance);
  root->SetBranchAddress("DInfo.svpvDisErr",DInfo_svpvDisErr);
  root->SetBranchAddress("DInfo.MaxDoca",DInfo_MaxDoca);
  root->SetBranchAddress("DInfo.vtxX",DInfo_vtxX);
  root->SetBranchAddress("DInfo.vtxY",DInfo_vtxY);
  root->SetBranchAddress("DInfo.vtxZ",DInfo_vtxZ);
  root->SetBranchAddress("DInfo.vtxXE",DInfo_vtxXE);
  root->SetBranchAddress("DInfo.vtxYE",DInfo_vtxYE);
  root->SetBranchAddress("DInfo.vtxZE",DInfo_vtxZE);
  root->SetBranchAddress("DInfo.vtxdof",DInfo_vtxdof);
  root->SetBranchAddress("DInfo.vtxchi2",DInfo_vtxchi2);
  root->SetBranchAddress("DInfo.rftk1_px",DInfo_rftk1_px);
  root->SetBranchAddress("DInfo.rftk1_py",DInfo_rftk1_py);
  root->SetBranchAddress("DInfo.rftk1_pz",DInfo_rftk1_pz);
  root->SetBranchAddress("DInfo.rftk2_px",DInfo_rftk2_px);
  root->SetBranchAddress("DInfo.rftk2_py",DInfo_rftk2_py);
  root->SetBranchAddress("DInfo.rftk2_pz",DInfo_rftk2_pz);
  root->SetBranchAddress("DInfo.rftk3_px",DInfo_rftk3_px);
  root->SetBranchAddress("DInfo.rftk3_py",DInfo_rftk3_py);
  root->SetBranchAddress("DInfo.rftk3_pz",DInfo_rftk3_pz);
  root->SetBranchAddress("DInfo.rftk4_px",DInfo_rftk4_px);
  root->SetBranchAddress("DInfo.rftk4_py",DInfo_rftk4_py);
  root->SetBranchAddress("DInfo.rftk4_pz",DInfo_rftk4_pz);
  root->SetBranchAddress("DInfo.rftk1_pt",DInfo_rftk1_pt);
  root->SetBranchAddress("DInfo.rftk1_eta",DInfo_rftk1_eta);
  root->SetBranchAddress("DInfo.rftk1_phi",DInfo_rftk1_phi);
  root->SetBranchAddress("DInfo.rftk2_pt",DInfo_rftk2_pt);
  root->SetBranchAddress("DInfo.rftk2_eta",DInfo_rftk2_eta);
  root->SetBranchAddress("DInfo.rftk2_phi",DInfo_rftk2_phi);
  root->SetBranchAddress("DInfo.rftk3_pt",DInfo_rftk3_pt);
  root->SetBranchAddress("DInfo.rftk3_eta",DInfo_rftk3_eta);
  root->SetBranchAddress("DInfo.rftk3_phi",DInfo_rftk3_phi);
  root->SetBranchAddress("DInfo.rftk4_pt",DInfo_rftk4_pt);
  root->SetBranchAddress("DInfo.rftk4_eta",DInfo_rftk4_eta);
  root->SetBranchAddress("DInfo.rftk4_phi",DInfo_rftk4_phi);
  root->SetBranchAddress("DInfo.rftk1_index",DInfo_rftk1_index);
  root->SetBranchAddress("DInfo.rftk2_index",DInfo_rftk2_index);
  root->SetBranchAddress("DInfo.rftk3_index",DInfo_rftk3_index);
  root->SetBranchAddress("DInfo.rftk4_index",DInfo_rftk4_index);
  root->SetBranchAddress("DInfo.rftk1_MassHypo",DInfo_rftk1_MassHypo);
  root->SetBranchAddress("DInfo.rftk2_MassHypo",DInfo_rftk2_MassHypo);
  root->SetBranchAddress("DInfo.rftk3_MassHypo",DInfo_rftk3_MassHypo);
  root->SetBranchAddress("DInfo.rftk4_MassHypo",DInfo_rftk4_MassHypo);
  //GenInfo
  root->SetBranchAddress("GenInfo.size",&GenInfo_size);
  root->SetBranchAddress("GenInfo.index",GenInfo_index);
  root->SetBranchAddress("GenInfo.handle_index",GenInfo_handle_index);
  root->SetBranchAddress("GenInfo.pt",GenInfo_pt);
  root->SetBranchAddress("GenInfo.eta",GenInfo_eta);
  root->SetBranchAddress("GenInfo.phi",GenInfo_phi);
  root->SetBranchAddress("GenInfo.mass",GenInfo_mass);
  root->SetBranchAddress("GenInfo.pdgId",GenInfo_pdgId);
  root->SetBranchAddress("GenInfo.status",GenInfo_status);
  root->SetBranchAddress("GenInfo.nMo",GenInfo_nMo);
  root->SetBranchAddress("GenInfo.nDa",GenInfo_nDa);
  root->SetBranchAddress("GenInfo.mo1",GenInfo_mo1);
  root->SetBranchAddress("GenInfo.mo2",GenInfo_mo2);
  root->SetBranchAddress("GenInfo.da1",GenInfo_da1);
  root->SetBranchAddress("GenInfo.da2",GenInfo_da2);
  root->SetBranchAddress("GenInfo.da3",GenInfo_da3);
  root->SetBranchAddress("GenInfo.da4",GenInfo_da4);
}

//HltInfo

Int_t           Df_HLT_Run;
ULong64_t       Df_HLT_Event;
Int_t           Df_HLT_HIMinBiasHfOrBSC_v1;
Int_t           Df_HLT_HIMinBiasHfOrBSC_v1_Prescl;
Int_t           Df_HLT_HIMinBiasHfOrBSC_v4;
Int_t           Df_HLT_HIMinBiasHfOrBSC_v4_Prescl;
Int_t           Df_HLT_DmesonTrackingGlobalPt8_Dpt20_v1;
Int_t           Df_HLT_DmesonTrackingGlobalPt8_Dpt20_v1_Prescl;
Int_t           Df_HLT_DmesonTrackingGlobalPt8_Dpt60_v1;
Int_t           Df_HLT_DmesonTrackingGlobalPt8_Dpt60_v1_Prescl;
Int_t           Df_HLT_DmesonTrackingGlobalPt8_Dpt40_v1;
Int_t           Df_HLT_DmesonTrackingGlobalPt8_Dpt40_v1_Prescl;
Int_t           Df_HLT_PuAK4CaloJet80Eta2p3_ForDmesons_v1;
Int_t           Df_HLT_PuAK4CaloJet80Eta2p3_ForDmesons_v1_Prescl;
Int_t           Df_HLT_PuAK4CaloJet60Eta2p3_ForDmesons_v1;
Int_t           Df_HLT_PuAK4CaloJet60Eta2p3_ForDmesons_v1_Prescl;

void setDataHLTBranch(TTree* hltroot)
{
  hltroot->SetBranchAddress("Run",&Df_HLT_Run);
  hltroot->SetBranchAddress("Event",&Df_HLT_Event);
  hltroot->SetBranchAddress("HLT_HIMinBiasHfOrBSC_v1",&Df_HLT_HIMinBiasHfOrBSC_v1);
  hltroot->SetBranchAddress("HLT_HIMinBiasHfOrBSC_v1_Prescl",&Df_HLT_HIMinBiasHfOrBSC_v1_Prescl);
  hltroot->SetBranchAddress("HLT_DmesonTrackingGlobalPt8_Dpt20_v1",&Df_HLT_DmesonTrackingGlobalPt8_Dpt20_v1);
  hltroot->SetBranchAddress("HLT_DmesonTrackingGlobalPt8_Dpt20_v1_Prescl",&Df_HLT_DmesonTrackingGlobalPt8_Dpt20_v1_Prescl);
  hltroot->SetBranchAddress("HLT_DmesonTrackingGlobalPt8_Dpt60_v1",&Df_HLT_DmesonTrackingGlobalPt8_Dpt60_v1);
  hltroot->SetBranchAddress("HLT_DmesonTrackingGlobalPt8_Dpt60_v1_Prescl",&Df_HLT_DmesonTrackingGlobalPt8_Dpt60_v1_Prescl);
  hltroot->SetBranchAddress("HLT_DmesonTrackingGlobalPt8_Dpt40_v1",&Df_HLT_DmesonTrackingGlobalPt8_Dpt40_v1);
  hltroot->SetBranchAddress("HLT_DmesonTrackingGlobalPt8_Dpt40_v1_Prescl",&Df_HLT_DmesonTrackingGlobalPt8_Dpt40_v1_Prescl);
  hltroot->SetBranchAddress("HLT_PuAK4CaloJet80Eta2p3_ForDmesons_v1",&Df_HLT_PuAK4CaloJet80Eta2p3_ForDmesons_v1);
  hltroot->SetBranchAddress("HLT_PuAK4CaloJet80Eta2p3_ForDmesons_v1_Prescl",&Df_HLT_PuAK4CaloJet80Eta2p3_ForDmesons_v1_Prescl);
  hltroot->SetBranchAddress("HLT_PuAK4CaloJet60Eta2p3_ForDmesons_v1",&Df_HLT_PuAK4CaloJet60Eta2p3_ForDmesons_v1);
  hltroot->SetBranchAddress("HLT_PuAK4CaloJet60Eta2p3_ForDmesons_v1_Prescl",&Df_HLT_PuAK4CaloJet60Eta2p3_ForDmesons_v1_Prescl);
}
void setMCHLTBranch(TTree* hltroot)
{
  hltroot->SetBranchAddress("Run",&Df_HLT_Run);
  hltroot->SetBranchAddress("Event",&Df_HLT_Event);
  //hltroot->SetBranchAddress("HLT_HIMinBiasHfOrBSC_v4",&Df_HLT_HIMinBiasHfOrBSC_v4);
  //hltroot->SetBranchAddress("HLT_HIMinBiasHfOrBSC_v4_Prescl",&Df_HLT_HIMinBiasHfOrBSC_v4_Prescl);
  hltroot->SetBranchAddress("HLT_DmesonTrackingGlobalPt8_Dpt20_v1",&Df_HLT_DmesonTrackingGlobalPt8_Dpt20_v1);
  hltroot->SetBranchAddress("HLT_DmesonTrackingGlobalPt8_Dpt20_v1_Prescl",&Df_HLT_DmesonTrackingGlobalPt8_Dpt20_v1_Prescl);
  hltroot->SetBranchAddress("HLT_DmesonTrackingGlobalPt8_Dpt60_v1",&Df_HLT_DmesonTrackingGlobalPt8_Dpt60_v1);
  hltroot->SetBranchAddress("HLT_DmesonTrackingGlobalPt8_Dpt60_v1_Prescl",&Df_HLT_DmesonTrackingGlobalPt8_Dpt60_v1_Prescl);
  hltroot->SetBranchAddress("HLT_DmesonTrackingGlobalPt8_Dpt40_v1",&Df_HLT_DmesonTrackingGlobalPt8_Dpt40_v1);
  hltroot->SetBranchAddress("HLT_DmesonTrackingGlobalPt8_Dpt40_v1_Prescl",&Df_HLT_DmesonTrackingGlobalPt8_Dpt40_v1_Prescl);
  hltroot->SetBranchAddress("HLT_PuAK4CaloJet80Eta2p3_ForDmesons_v1",&Df_HLT_PuAK4CaloJet80Eta2p3_ForDmesons_v1);
  hltroot->SetBranchAddress("HLT_PuAK4CaloJet80Eta2p3_ForDmesons_v1_Prescl",&Df_HLT_PuAK4CaloJet80Eta2p3_ForDmesons_v1_Prescl);
  hltroot->SetBranchAddress("HLT_PuAK4CaloJet60Eta2p3_ForDmesons_v1",&Df_HLT_PuAK4CaloJet60Eta2p3_ForDmesons_v1);
  hltroot->SetBranchAddress("HLT_PuAK4CaloJet60Eta2p3_ForDmesons_v1_Prescl",&Df_HLT_PuAK4CaloJet60Eta2p3_ForDmesons_v1_Prescl);
}

//hiEvtInfo
Float_t         Df_HiTree_Npart;
Float_t         Df_HiTree_Ncoll;
Float_t         Df_HiTree_Nhard;
Int_t           Df_HiTree_hiBin;

void setHiTreeBranch(TTree* hitreeroot)
{
  hitreeroot->SetBranchAddress("Npart",&Df_HiTree_Npart);
  hitreeroot->SetBranchAddress("Ncoll",&Df_HiTree_Ncoll);
  hitreeroot->SetBranchAddress("Nhard",&Df_HiTree_Nhard);
  hitreeroot->SetBranchAddress("hiBin",&Df_HiTree_hiBin);
}

/*
Int_t      HLT_HIMinBiasBSC_v1;
Int_t      HLT_HIMinBiasBSC_v1_Prescl;
Int_t      HLT_HIMinBiasBSC_OR_v1;
Int_t      HLT_HIMinBiasBSC_OR_v1_Prescl;
Int_t      HLT_HIMinBiasHF_v1;
Int_t      HLT_HIMinBiasHF_v1_Prescl;
Int_t      HLT_HIMinBiasHf_OR_v1;
Int_t      HLT_HIMinBiasHf_OR_v1_Prescl;
Int_t      HLT_HIMinBiasBSC_v4;
Int_t      HLT_HIMinBiasBSC_v4_Prescl;
Int_t      HLT_HIMinBiasBSC_OR_v4;
Int_t      HLT_HIMinBiasBSC_OR_v4_Prescl;
Int_t      HLT_HIMinBiasHF_v4;
Int_t      HLT_HIMinBiasHF_v4_Prescl;
Int_t      HLT_HIMinBiasHf_OR_v4;
Int_t      HLT_HIMinBiasHf_OR_v4_Prescl;
  dnt->Branch("HLT_HIMinBiasBSC_v1",&HLT_HIMinBiasBSC_v1);
  dnt->Branch("HLT_HIMinBiasBSC_v1_Prescl",&HLT_HIMinBiasBSC_v1_Prescl);
  dnt->Branch("HLT_HIMinBiasBSC_OR_v1",&HLT_HIMinBiasBSC_OR_v1);
  dnt->Branch("HLT_HIMinBiasBSC_OR_v1_Prescl",&HLT_HIMinBiasBSC_OR_v1_Prescl);
  dnt->Branch("HLT_HIMinBiasHF_v1",&HLT_HIMinBiasHF_v1);
  dnt->Branch("HLT_HIMinBiasHF_v1_Prescl",&HLT_HIMinBiasHF_v1_Prescl);
  dnt->Branch("HLT_HIMinBiasHf_OR_v1",&HLT_HIMinBiasHf_OR_v1);
  dnt->Branch("HLT_HIMinBiasHf_OR_v1_Prescl",&HLT_HIMinBiasHf_OR_v1_Prescl);
  dnt->Branch("HLT_HIMinBiasBSC_v4",&HLT_HIMinBiasBSC_v4);
  dnt->Branch("HLT_HIMinBiasBSC_v4_Prescl",&HLT_HIMinBiasBSC_v4_Prescl);
  dnt->Branch("HLT_HIMinBiasBSC_OR_v4",&HLT_HIMinBiasBSC_OR_v4);
  dnt->Branch("HLT_HIMinBiasBSC_OR_v4_Prescl",&HLT_HIMinBiasBSC_OR_v4_Prescl);
  dnt->Branch("HLT_HIMinBiasHF_v4",&HLT_HIMinBiasHF_v4);
  dnt->Branch("HLT_HIMinBiasHF_v4_Prescl",&HLT_HIMinBiasHF_v4_Prescl);
  dnt->Branch("HLT_HIMinBiasHf_OR_v4",&HLT_HIMinBiasHf_OR_v4);
  dnt->Branch("HLT_HIMinBiasHf_OR_v4_Prescl",&HLT_HIMinBiasHf_OR_v4_Prescl);
Int_t           Df_HLT_HIMinBiasBSC_v1;
Int_t           Df_HLT_HIMinBiasBSC_v1_Prescl;
Int_t           Df_HLT_HIMinBiasBSC_OR_v1;
Int_t           Df_HLT_HIMinBiasBSC_OR_v1_Prescl;
Int_t           Df_HLT_HIMinBiasHF_v1;
Int_t           Df_HLT_HIMinBiasHF_v1_Prescl;
Int_t           Df_HLT_HIMinBiasHf_OR_v1;
Int_t           Df_HLT_HIMinBiasHf_OR_v1_Prescl;
Int_t           Df_HLT_HIMinBiasBSC_v4;
Int_t           Df_HLT_HIMinBiasBSC_v4_Prescl;
Int_t           Df_HLT_HIMinBiasBSC_OR_v4;
Int_t           Df_HLT_HIMinBiasBSC_OR_v4_Prescl;
Int_t           Df_HLT_HIMinBiasHF_v4;
Int_t           Df_HLT_HIMinBiasHF_v4_Prescl;
Int_t           Df_HLT_HIMinBiasHf_OR_v4;
Int_t           Df_HLT_HIMinBiasHf_OR_v4_Prescl;
  hltroot->SetBranchAddress("HLT_HIMinBiasBSC_v1_Prescl",&Df_HLT_HIMinBiasBSC_v1_Prescl);
  hltroot->SetBranchAddress("HLT_HIMinBiasBSC_OR_v1",&Df_HLT_HIMinBiasBSC_OR_v1);
  hltroot->SetBranchAddress("HLT_HIMinBiasBSC_OR_v1_Prescl",&Df_HLT_HIMinBiasBSC_OR_v1_Prescl);
  hltroot->SetBranchAddress("HLT_HIMinBiasHF_v1",&Df_HLT_HIMinBiasHF_v1);
  hltroot->SetBranchAddress("HLT_HIMinBiasHF_v1_Prescl",&Df_HLT_HIMinBiasHF_v1_Prescl);
  hltroot->SetBranchAddress("HLT_HIMinBiasHf_OR_v1",&Df_HLT_HIMinBiasHf_OR_v1);
  hltroot->SetBranchAddress("HLT_HIMinBiasHf_OR_v1_Prescl",&Df_HLT_HIMinBiasHf_OR_v1_Prescl);
  hltroot->SetBranchAddress("HLT_HIMinBiasBSC_v4_Prescl",&Df_HLT_HIMinBiasBSC_v4_Prescl);
  hltroot->SetBranchAddress("HLT_HIMinBiasBSC_OR_v4",&Df_HLT_HIMinBiasBSC_OR_v4);
  hltroot->SetBranchAddress("HLT_HIMinBiasBSC_OR_v4_Prescl",&Df_HLT_HIMinBiasBSC_OR_v4_Prescl);
  hltroot->SetBranchAddress("HLT_HIMinBiasHF_v4",&Df_HLT_HIMinBiasHF_v4);
  hltroot->SetBranchAddress("HLT_HIMinBiasHF_v4_Prescl",&Df_HLT_HIMinBiasHF_v4_Prescl);
  hltroot->SetBranchAddress("HLT_HIMinBiasHf_OR_v4",&Df_HLT_HIMinBiasHf_OR_v4);
  hltroot->SetBranchAddress("HLT_HIMinBiasHf_OR_v4_Prescl",&Df_HLT_HIMinBiasHf_OR_v4_Prescl);
*/

/*
//BInfo
Int_t      Bindex[MAX_XB];
Double_t   Bmass[MAX_XB];
Double_t   Bpt[MAX_XB];
Double_t   Beta[MAX_XB];
Double_t   Bphi[MAX_XB];
Double_t   By[MAX_XB];
Double_t   BvtxX[MAX_XB];
Double_t   BvtxY[MAX_XB];
Double_t   Bd0[MAX_XB];
Double_t   Bd0Err[MAX_XB];
Double_t   Bchi2ndf[MAX_XB];
Double_t   Bchi2cl[MAX_XB];
Double_t   Bdtheta[MAX_XB];
Double_t   Blxy[MAX_XB];
Bool_t     Bisbestchi2[MAX_XB];
//BInfo.MuInfo
Bool_t     Bmu1TrackerMuArbitrated[MAX_XB];
Bool_t     Bmu2TrackerMuArbitrated[MAX_XB];
Bool_t     Bmu1isTrackerMuon[MAX_XB];
Bool_t     Bmu2isTrackerMuon[MAX_XB];
Bool_t     Bmu1isGlobalMuon[MAX_XB];
Bool_t     Bmu2isGlobalMuon[MAX_XB];
Bool_t     Bmu1TMOneStationTight[MAX_XB];
Bool_t     Bmu2TMOneStationTight[MAX_XB];
Int_t      Bmu1InPixelLayer[MAX_XB];
Int_t      Bmu2InPixelLayer[MAX_XB];
Int_t      Bmu1InStripLayer[MAX_XB];
Int_t      Bmu2InStripLayer[MAX_XB];
Int_t      Bmu1InTrackerLayer[MAX_XB];
Int_t      Bmu2InTrackerLayer[MAX_XB];
Double_t   Bmu1eta[MAX_XB];
Double_t   Bmu2eta[MAX_XB];
Double_t   Bmu1phi[MAX_XB];
Double_t   Bmu2phi[MAX_XB];
Double_t   Bmu1y[MAX_XB];
Double_t   Bmu2y[MAX_XB];
Double_t   Bmu1pt[MAX_XB];
Double_t   Bmu2pt[MAX_XB];
Double_t   Bmu1p[MAX_XB];
Double_t   Bmu2p[MAX_XB];
Double_t   Bmu1E[MAX_XB];
Double_t   Bmu2E[MAX_XB];
Double_t   Bmu1dzPV[MAX_XB];
Double_t   Bmu2dzPV[MAX_XB];
Double_t   Bmu1dxyPV[MAX_XB];
Double_t   Bmu2dxyPV[MAX_XB];
Double_t   Bmu1normchi2[MAX_XB];
Double_t   Bmu2normchi2[MAX_XB];
Double_t   Bmu1Chi2ndf[MAX_XB];
Double_t   Bmu2Chi2ndf[MAX_XB];
//BInfo.ujInfo
Double_t   Bmumumass[MAX_XB];
Double_t   Bmumueta[MAX_XB];
Double_t   Bmumuphi[MAX_XB];
Double_t   Bmumuy[MAX_XB];
Double_t   Bmumupt[MAX_XB];
Double_t   Bujmass[MAX_XB];
Double_t   BujvProb[MAX_XB];
Double_t   Bujpt[MAX_XB];
Double_t   Bujeta[MAX_XB];
Double_t   Bujphi[MAX_XB];
Double_t   Bujy[MAX_XB];
Double_t   Bujlxy[MAX_XB];
//BInfo.trkInfo
Double_t   Btrk1Pt[MAX_XB];
Double_t   Btrk2Pt[MAX_XB];
Double_t   Btrk1Eta[MAX_XB];
Double_t   Btrk2Eta[MAX_XB];
Double_t   Btrk1Phi[MAX_XB];
Double_t   Btrk2Phi[MAX_XB];
Double_t   Btrk1Y[MAX_XB];
Double_t   Btrk2Y[MAX_XB];
Double_t   Btrk1Dxy[MAX_XB];
Double_t   Btrk2Dxy[MAX_XB];
Double_t   Btrk1D0Err[MAX_XB];
Double_t   Btrk2D0Err[MAX_XB];
Double_t   Btrk1PixelHit[MAX_XB];
Double_t   Btrk2PixelHit[MAX_XB];
Double_t   Btrk1StripHit[MAX_XB];
Double_t   Btrk2StripHit[MAX_XB];
Double_t   Btrk1Chi2ndf[MAX_XB];
Double_t   Btrk2Chi2ndf[MAX_XB];
//BInfo.tktkInfo
Double_t   Btktkmass[MAX_XB];
Double_t   BtktkmassKK[MAX_XB];
Double_t   BtktkvProb[MAX_XB];
Double_t   Btktkpt[MAX_XB];
Double_t   Btktketa[MAX_XB];
Double_t   Btktkphi[MAX_XB];
Double_t   Btktky[MAX_XB];
Double_t   Bdoubletmass[MAX_XB];
Double_t   Bdoubletpt[MAX_XB];
Double_t   Bdoubleteta[MAX_XB];
Double_t   Bdoubletphi[MAX_XB];
Double_t   Bdoublety[MAX_XB];
//BInfo.genInfo
Double_t   Bgen[MAX_XB];
Int_t      BgenIndex[MAX_XB];
Double_t   Bgenpt[MAX_XB];
Double_t   Bgeneta[MAX_XB];
Double_t   Bgenphi[MAX_XB];
Double_t   Bgeny[MAX_XB];
Int_t      BgenpdgId[MAX_XB];

void buildBBranch(TTree* bnt)
{
  //EvtInfo
  bnt->Branch("RunNo",&RunNo);
  bnt->Branch("EvtNo",&EvtNo);
  bnt->Branch("Bsize",&Bsize);
  bnt->Branch("PVx",&PVx);
  bnt->Branch("PVy",&PVy);
  bnt->Branch("PVz",&PVz);
  bnt->Branch("PVxE",&PVxE);
  bnt->Branch("PVyE",&PVyE);
  bnt->Branch("PVzE",&PVzE);
  bnt->Branch("PVnchi2",&PVnchi2);
  bnt->Branch("PVchi2",&PVchi2);
  //BInfo
  bnt->Branch("Bindex",Bindex,"Bindex[size]/I");
  bnt->Branch("Bmass",Bmass,"Bmass[size]/D");
  bnt->Branch("Bpt",Bpt,"Bpt[size]/D");
  bnt->Branch("Beta",Beta,"Beta[size]/D");
  bnt->Branch("Bphi",Bphi,"Bphi[size]/D");
  bnt->Branch("By",By,"By[size]/D");
  bnt->Branch("BvtxX",BvtxX,"BvtxX[size]/D");
  bnt->Branch("BvtxY",BvtxY,"BvtxY[size]/D");
  bnt->Branch("Bd0",Bd0,"Bd0[size]/D");
  bnt->Branch("Bd0Err",Bd0Err,"Bd0Err[size]/D");
  bnt->Branch("Bchi2ndf",Bchi2ndf,"Bchi2ndf[size]/D");
  bnt->Branch("Bchi2cl",Bchi2cl,"Bchi2cl[size]/D");
  bnt->Branch("Bdtheta",Bdtheta,"Bdtheta[size]/D");
  bnt->Branch("Blxy",Blxy,"Blxy[size]/D");
  bnt->Branch("Bisbestchi2",Bisbestchi2,"Bisbestchi2[size]/O");
  //BInfo.muInfo
  bnt->Branch("Bmu1TrackerMuArbitrated",Bmu1TrackerMuArbitrated,"Bmu1TrackerMuArbitrated[size]/O");
  bnt->Branch("Bmu2TrackerMuArbitrated",Bmu2TrackerMuArbitrated,"Bmu2TrackerMuArbitrated[size]/O");
  bnt->Branch("Bmu1isTrackerMuon",Bmu1isTrackerMuon,"Bmu1isTrackerMuon[size]/O");
  bnt->Branch("Bmu2isTrackerMuon",Bmu2isTrackerMuon,"Bmu2isTrackerMuon[size]/O");
  bnt->Branch("Bmu1isGlobalMuon",Bmu1isGlobalMuon,"Bmu1isGlobalMuon[size]/O");
  bnt->Branch("Bmu2isGlobalMuon",Bmu2isGlobalMuon,"Bmu2isGlobalMuon[size]/O");
  bnt->Branch("Bmu1TMOneStationTight",Bmu1TMOneStationTight,"Bmu1TMOneStationTight[size]/O");
  bnt->Branch("Bmu2TMOneStationTight",Bmu2TMOneStationTight,"Bmu2TMOneStationTight[size]/O");
  bnt->Branch("Bmu1InPixelLayer",Bmu1InPixelLayer,"Bmu1InPixelLayer[size]/I");
  bnt->Branch("Bmu2InPixelLayer",Bmu2InPixelLayer,"Bmu2InPixelLayer[size]/I");
  bnt->Branch("Bmu1InStripLayer",Bmu1InStripLayer,"Bmu1InStripLayer[size]/I");
  bnt->Branch("Bmu2InStripLayer",Bmu2InStripLayer,"Bmu2InStripLayer[size]/I");
  bnt->Branch("Bmu1InTrackerLayer",Bmu1InTrackerLayer,"Bmu1InTrackerLayer[size]/I");
  bnt->Branch("Bmu2InTrackerLayer",Bmu2InTrackerLayer,"Bmu2InTrackerLayer[size]/I");
  bnt->Branch("Bmu1eta",Bmu1eta,"Bmu1eta[size]/D");
  bnt->Branch("Bmu2eta",Bmu2eta,"Bmu2eta[size]/D");
  bnt->Branch("Bmu1phi",Bmu1phi,"Bmu1phi[size]/D");
  bnt->Branch("Bmu2phi",Bmu2phi,"Bmu2phi[size]/D");
  bnt->Branch("Bmu1y",Bmu1y,"Bmu1y[size]/D");
  bnt->Branch("Bmu2y",Bmu2y,"Bmu2y[size]/D");
  bnt->Branch("Bmu1pt",Bmu1pt,"Bmu1pt[size]/D");
  bnt->Branch("Bmu2pt",Bmu2pt,"Bmu2pt[size]/D");
  bnt->Branch("Bmu1p",Bmu1p,"Bmu1p[size]/D");
  bnt->Branch("Bmu2p",Bmu2p,"Bmu2p[size]/D");
  bnt->Branch("Bmu1E",Bmu1E,"Bmu1E[size]/D");
  bnt->Branch("Bmu2E",Bmu2E,"Bmu2E[size]/D");
  bnt->Branch("Bmu1dzPV",Bmu1dzPV,"Bmu1dzPV[size]/D");
  bnt->Branch("Bmu2dzPV",Bmu2dzPV,"Bmu2dzPV[size]/D");
  bnt->Branch("Bmu1dxyPV",Bmu1dxyPV,"Bmu1dxyPV[size]/D");
  bnt->Branch("Bmu2dxyPV",Bmu2dxyPV,"Bmu2dxyPV[size]/D");
  bnt->Branch("Bmu1normchi2",Bmu1normchi2,"Bmu1normchi2[size]/D");
  bnt->Branch("Bmu2normchi2",Bmu2normchi2,"Bmu2normchi2[size]/D");
  bnt->Branch("Bmu1Chi2ndf",Bmu1Chi2ndf,"Bmu1Chi2ndf[size]/D");
  bnt->Branch("Bmu2Chi2ndf",Bmu2Chi2ndf,"Bmu2Chi2ndf[size]/D");
  //BInfo.ujInfo
  bnt->Branch("Bmumumass",Bmumumass,"Bmumumass[size]/D");
  bnt->Branch("Bmumueta",Bmumueta,"Bmumueta[size]/D");
  bnt->Branch("Bmumuphi",Bmumuphi,"Bmumuphi[size]/D");
  bnt->Branch("Bmumuy",Bmumuy,"Bmumuy[size]/D");
  bnt->Branch("Bmumupt",Bmumupt,"Bmumupt[size]/D");  
  bnt->Branch("Bujmass",Bujmass,"Bujmass[size]/D");
  bnt->Branch("BujvProb",BujvProb,"BujvProb[size]/D");
  bnt->Branch("Bujpt",Bujpt,"Bujpt[size]/D");
  bnt->Branch("Bujeta",Bujeta,"Bujeta[size]/D");
  bnt->Branch("Bujphi",Bujphi,"Bujphi[size]/D");
  bnt->Branch("Bujy",Bujy,"Bujy[size]/D");
  bnt->Branch("Bujlxy",Bujlxy,"Bujlxy[size]/D");
  //BInfo.trkInfo
  bnt->Branch("Btrk1Pt",Btrk1Pt,"Btrk1Pt[size]/D");
  bnt->Branch("Btrk2Pt",Btrk2Pt,"Btrk2Pt[size]/D");
  bnt->Branch("Btrk1Eta",Btrk1Eta,"Btrk1Eta[size]/D");  
  bnt->Branch("Btrk2Eta",Btrk2Eta,"Btrk2Eta[size]/D");  
  bnt->Branch("Btrk1Phi",Btrk1Phi,"Btrk1Phi[size]/D");  
  bnt->Branch("Btrk2Phi",Btrk2Phi,"Btrk2Phi[size]/D");  
  bnt->Branch("Btrk1Y",Btrk1Y,"Btrk1Y[size]/D");  
  bnt->Branch("Btrk2Y",Btrk2Y,"Btrk2Y[size]/D");  
  bnt->Branch("Btrk1Dxy",Btrk1Dxy,"Btrk1Dxy[size]/D");
  bnt->Branch("Btrk2Dxy",Btrk2Dxy,"Btrk2Dxy[size]/D");
  bnt->Branch("Btrk1D0Err",Btrk1D0Err,"Btrk1D0Err[size]/D");
  bnt->Branch("Btrk2D0Err",Btrk2D0Err,"Btrk2D0Err[size]/D");
  bnt->Branch("Btrk1PixelHit",Btrk1PixelHit,"Btrk1PixelHit[size]/D");
  bnt->Branch("Btrk2PixelHit",Btrk2PixelHit,"Btrk2PixelHit[size]/D");
  bnt->Branch("Btrk1StripHit",Btrk1StripHit,"Btrk1StripHit[size]/D");
  bnt->Branch("Btrk2StripHit",Btrk2StripHit,"Btrk2StripHit[size]/D");
  bnt->Branch("Btrk1Chi2ndf",Btrk1Chi2ndf,"Btrk1Chi2ndf[size]/D");
  bnt->Branch("Btrk2Chi2ndf",Btrk2Chi2ndf,"Btrk2Chi2ndf[size]/D");
  //BInfo.tktkInfo
  bnt->Branch("Btktkmass",Btktkmass,"Btktkmass[size]/D");
  bnt->Branch("BtktkmassKK",BtktkmassKK,"BtktkmassKK[size]/D");
  bnt->Branch("BtktkvProb",BtktkvProb,"BtktkvProb[size]/D");
  bnt->Branch("Btktkpt",Btktkpt,"Btktkpt[size]/D");
  bnt->Branch("Btktketa",Btktketa,"Btktketa[size]/D");
  bnt->Branch("Btktkphi",Btktkphi,"Btktkphi[size]/D");
  bnt->Branch("Btktky",Btktky,"Btktky[size]/D");
  bnt->Branch("Bdoubletmass",Bdoubletmass,"Bdoubletmass[size]/D");
  bnt->Branch("Bdoubletpt",Bdoubletpt,"Bdoubletpt[size]/D");
  bnt->Branch("Bdoubleteta",Bdoubleteta,"Bdoubleteta[size]/D");  
  bnt->Branch("Bdoubletphi",Bdoubletphi,"Bdoubletphi[size]/D");  
  bnt->Branch("Bdoublety",Bdoublety,"Bdoublety[size]/D");
  //BInfo.genInfo
  bnt->Branch("Bgen",Bgen,"Bgen[size]/D");
  bnt->Branch("BgenIndex",BgenIndex,"BgenIndex[size]/I");
  bnt->Branch("Bgenpt",Bgenpt,"Bgenpt[size]/D");
  bnt->Branch("Bgeneta",Bgeneta,"Bgeneta[size]/D");
  bnt->Branch("Bgenphi",Bgenphi,"Bgenphi[size]/D");
  bnt->Branch("Bgeny",Bgeny,"Bgeny[size]/D");
  bnt->Branch("BgenpdgId",BgenpdgId,"BgenpdgId[size]/I");
}

//MuonInfo
Int_t           MuonInfo_size;
Int_t           MuonInfo_index[MAX_MUON];
Int_t           MuonInfo_handle_index[MAX_MUON];
Int_t           MuonInfo_charge[MAX_MUON];
Double_t        MuonInfo_pt[MAX_MUON];
Double_t        MuonInfo_eta[MAX_MUON];
Double_t        MuonInfo_phi[MAX_MUON];
Bool_t          MuonInfo_isTrackerMuon[MAX_MUON];
Bool_t          MuonInfo_isGlobalMuon[MAX_MUON];
Int_t           MuonInfo_muqual[MAX_MUON];
Double_t        MuonInfo_iso_trk[MAX_MUON];
Double_t        MuonInfo_iso_ecal[MAX_MUON];
Double_t        MuonInfo_iso_hcal[MAX_MUON];
Int_t           MuonInfo_type[MAX_MUON];
Double_t        MuonInfo_n_matches[MAX_MUON];
Bool_t          MuonInfo_TMOneStationTight[MAX_MUON];
Bool_t          MuonInfo_TrackerMuonArbitrated[MAX_MUON];
Int_t           MuonInfo_isGoodCand[MAX_MUON];
Int_t           MuonInfo_geninfo_index[MAX_MUON];
Bool_t          MuonInfo_BfinderMuID[MAX_MUON];
Bool_t          MuonInfo_SoftMuID[MAX_MUON];
Bool_t          MuonInfo_isStandAloneMuon[MAX_MUON];
Int_t           MuonInfo_StandAloneMuon_charge[MAX_MUON];
Double_t        MuonInfo_StandAloneMuon_pt[MAX_MUON];
Double_t        MuonInfo_StandAloneMuon_eta[MAX_MUON];
Double_t        MuonInfo_StandAloneMuon_phi[MAX_MUON];
Double_t        MuonInfo_StandAloneMuon_d0[MAX_MUON];
Double_t        MuonInfo_StandAloneMuon_dz[MAX_MUON];
Double_t        MuonInfo_StandAloneMuon_dzPV[MAX_MUON];
Double_t        MuonInfo_StandAloneMuon_dxyPV[MAX_MUON];
Bool_t          MuonInfo_outerTrackisNonnull[MAX_MUON];
Bool_t          MuonInfo_innerTrackisNonnull[MAX_MUON];
Bool_t          MuonInfo_globalTrackisNonnull[MAX_MUON];
Int_t           MuonInfo_innerTrackQuality[MAX_MUON];
Double_t        MuonInfo_normchi2[MAX_MUON];
Int_t           MuonInfo_i_striphit[MAX_MUON];
Int_t           MuonInfo_i_pixelhit[MAX_MUON];
Int_t           MuonInfo_i_nStripLayer[MAX_MUON];
Int_t           MuonInfo_i_nPixelLayer[MAX_MUON];
Double_t        MuonInfo_i_chi2[MAX_MUON];
Double_t        MuonInfo_i_ndf[MAX_MUON];
Int_t           MuonInfo_fpbarrelhit[MAX_MUON];
Int_t           MuonInfo_fpendcaphit[MAX_MUON];
Double_t        MuonInfo_d0[MAX_MUON];
Double_t        MuonInfo_dz[MAX_MUON];
Double_t        MuonInfo_dzPV[MAX_MUON];
Double_t        MuonInfo_dxyPV[MAX_MUON];
Double_t        MuonInfo_g_chi2[MAX_MUON];
Double_t        MuonInfo_g_ndf[MAX_MUON];
Int_t           MuonInfo_g_striphit[MAX_MUON];
Int_t           MuonInfo_g_pixelhit[MAX_MUON];
Int_t           MuonInfo_nmuhit[MAX_MUON];
Bool_t          MuonInfo_isTriggered[MAX_MUON];
//BInfo
Int_t           BInfo_uj_size;
Int_t           BInfo_uj_index[MAX_XB];
Double_t        BInfo_uj_mass[MAX_XB];
Double_t        BInfo_uj_eta[MAX_XB];
Double_t        BInfo_uj_phi[MAX_XB];
Double_t        BInfo_uj_px[MAX_XB];
Double_t        BInfo_uj_py[MAX_XB];
Double_t        BInfo_uj_pz[MAX_XB];
Double_t        BInfo_uj_vtxX[MAX_XB];
Double_t        BInfo_uj_vtxY[MAX_XB];
Double_t        BInfo_uj_vtxZ[MAX_XB];
Double_t        BInfo_uj_vtxXE[MAX_XB];
Double_t        BInfo_uj_vtxYE[MAX_XB];
Double_t        BInfo_uj_vtxZE[MAX_XB];
Double_t        BInfo_uj_vtxdof[MAX_XB];
Double_t        BInfo_uj_vtxchi2[MAX_XB];
Int_t           BInfo_uj_rfmu1_index[MAX_XB];
Int_t           BInfo_uj_rfmu2_index[MAX_XB];
Int_t           BInfo_uj_isGoodCand[MAX_XB];
Double_t        BInfo_uj_rfmu1_px[MAX_XB];
Double_t        BInfo_uj_rfmu1_py[MAX_XB];
Double_t        BInfo_uj_rfmu1_pz[MAX_XB];
Double_t        BInfo_uj_rfmu2_px[MAX_XB];
Double_t        BInfo_uj_rfmu2_py[MAX_XB];
Double_t        BInfo_uj_rfmu2_pz[MAX_XB];
Int_t           BInfo_size;
Int_t           BInfo_index[MAX_XB];
Double_t        BInfo_mass[MAX_XB];
Double_t        BInfo_eta[MAX_XB];
Double_t        BInfo_phi[MAX_XB];
Double_t        BInfo_px[MAX_XB];
Double_t        BInfo_py[MAX_XB];
Double_t        BInfo_pz[MAX_XB];
Double_t        BInfo_pt[MAX_XB];
Double_t        BInfo_pxE[MAX_XB];
Double_t        BInfo_pyE[MAX_XB];
Double_t        BInfo_pzE[MAX_XB];
Double_t        BInfo_vtxX[MAX_XB];
Double_t        BInfo_vtxY[MAX_XB];
Double_t        BInfo_vtxZ[MAX_XB];
Double_t        BInfo_vtxXE[MAX_XB];
Double_t        BInfo_vtxYE[MAX_XB];
Double_t        BInfo_vtxZE[MAX_XB];
Double_t        BInfo_vtxdof[MAX_XB];
Double_t        BInfo_vtxchi2[MAX_XB];
Int_t           BInfo_rfuj_index[MAX_XB];
Int_t           BInfo_rftk1_index[MAX_XB];
Int_t           BInfo_rftk2_index[MAX_XB];
Int_t           BInfo_isGoodCand[MAX_XB];
Int_t           BInfo_type[MAX_XB];
Double_t        BInfo_rfmu1_px[MAX_XB];
Double_t        BInfo_rfmu1_py[MAX_XB];
Double_t        BInfo_rfmu1_pz[MAX_XB];
Double_t        BInfo_rfmu2_px[MAX_XB];
Double_t        BInfo_rfmu2_py[MAX_XB];
Double_t        BInfo_rfmu2_pz[MAX_XB];
Double_t        BInfo_rftk1_px[MAX_XB];
Double_t        BInfo_rftk1_py[MAX_XB];
Double_t        BInfo_rftk1_pz[MAX_XB];
Double_t        BInfo_rftk2_px[MAX_XB];
Double_t        BInfo_rftk2_py[MAX_XB];
Double_t        BInfo_rftk2_pz[MAX_XB];
Double_t        BInfo_tktk_mass[MAX_XB];
Double_t        BInfo_tktk_pt[MAX_XB];
Double_t        BInfo_tktk_eta[MAX_XB];
Double_t        BInfo_tktk_phi[MAX_XB];
Double_t        BInfo_tktk_px[MAX_XB];
Double_t        BInfo_tktk_py[MAX_XB];
Double_t        BInfo_tktk_pz[MAX_XB];
Double_t        BInfo_tktk_vtxX[MAX_XB];
Double_t        BInfo_tktk_vtxY[MAX_XB];
Double_t        BInfo_tktk_vtxZ[MAX_XB];
Double_t        BInfo_tktk_vtxXE[MAX_XB];
Double_t        BInfo_tktk_vtxYE[MAX_XB];
Double_t        BInfo_tktk_vtxZE[MAX_XB];
Double_t        BInfo_tktk_vtxdof[MAX_XB];
Double_t        BInfo_tktk_vtxchi2[MAX_XB];
Double_t        BInfo_tktk_rftk1_px[MAX_XB];
Double_t        BInfo_tktk_rftk1_py[MAX_XB];
Double_t        BInfo_tktk_rftk1_pz[MAX_XB];
Double_t        BInfo_tktk_rftk2_px[MAX_XB];
Double_t        BInfo_tktk_rftk2_py[MAX_XB];
Double_t        BInfo_tktk_rftk2_pz[MAX_XB];

void SetBBranch(TTree* root)
{
  //MuonINfo 
  root->SetBranchAddress("MuonInfo.size",&MuonInfo_size);
  root->SetBranchAddress("MuonInfo.index",MuonInfo_index);
  root->SetBranchAddress("MuonInfo.handle_index",MuonInfo_handle_index);
  root->SetBranchAddress("MuonInfo.charge",MuonInfo_charge);
  root->SetBranchAddress("MuonInfo.pt",MuonInfo_pt);
  root->SetBranchAddress("MuonInfo.eta",MuonInfo_eta);
  root->SetBranchAddress("MuonInfo.phi",MuonInfo_phi);
  root->SetBranchAddress("MuonInfo.isTrackerMuon",MuonInfo_isTrackerMuon);
  root->SetBranchAddress("MuonInfo.isGlobalMuon",MuonInfo_isGlobalMuon);
  root->SetBranchAddress("MuonInfo.muqual",MuonInfo_muqual);
  root->SetBranchAddress("MuonInfo.iso_trk",MuonInfo_iso_trk);
  root->SetBranchAddress("MuonInfo.iso_ecal",MuonInfo_iso_ecal);
  root->SetBranchAddress("MuonInfo.iso_hcal",MuonInfo_iso_hcal);
  root->SetBranchAddress("MuonInfo.type",MuonInfo_type);
  root->SetBranchAddress("MuonInfo.n_matches",MuonInfo_n_matches);
  root->SetBranchAddress("MuonInfo.TMOneStationTight",MuonInfo_TMOneStationTight);
  root->SetBranchAddress("MuonInfo.TrackerMuonArbitrated",MuonInfo_TrackerMuonArbitrated);
  root->SetBranchAddress("MuonInfo.isGoodCand",MuonInfo_isGoodCand);
  root->SetBranchAddress("MuonInfo.geninfo_index",MuonInfo_geninfo_index);
  root->SetBranchAddress("MuonInfo.BfinderMuID",MuonInfo_BfinderMuID);
  root->SetBranchAddress("MuonInfo.SoftMuID",MuonInfo_SoftMuID);
  root->SetBranchAddress("MuonInfo.isStandAloneMuon",MuonInfo_isStandAloneMuon);
  root->SetBranchAddress("MuonInfo.StandAloneMuon_charge",MuonInfo_StandAloneMuon_charge);
  root->SetBranchAddress("MuonInfo.StandAloneMuon_pt",MuonInfo_StandAloneMuon_pt);
  root->SetBranchAddress("MuonInfo.StandAloneMuon_eta",MuonInfo_StandAloneMuon_eta);
  root->SetBranchAddress("MuonInfo.StandAloneMuon_phi",MuonInfo_StandAloneMuon_phi);
  root->SetBranchAddress("MuonInfo.StandAloneMuon_d0",MuonInfo_StandAloneMuon_d0);
  root->SetBranchAddress("MuonInfo.StandAloneMuon_dz",MuonInfo_StandAloneMuon_dz);
  root->SetBranchAddress("MuonInfo.StandAloneMuon_dz",MuonInfo_StandAloneMuon_dz);
  root->SetBranchAddress("MuonInfo.StandAloneMuon_dzPV",MuonInfo_StandAloneMuon_dzPV);
  root->SetBranchAddress("MuonInfo.StandAloneMuon_dxyPV",MuonInfo_StandAloneMuon_dxyPV);
  root->SetBranchAddress("MuonInfo.outerTrackisNonnull",MuonInfo_outerTrackisNonnull);
  root->SetBranchAddress("MuonInfo.innerTrackisNonnull",MuonInfo_innerTrackisNonnull);
  root->SetBranchAddress("MuonInfo.globalTrackisNonnull",MuonInfo_globalTrackisNonnull);
  root->SetBranchAddress("MuonInfo.innerTrackQuality",MuonInfo_innerTrackQuality);
  root->SetBranchAddress("MuonInfo.normchi2",MuonInfo_normchi2);
  root->SetBranchAddress("MuonInfo.i_striphit",MuonInfo_i_striphit);
  root->SetBranchAddress("MuonInfo.i_pixelhit",MuonInfo_i_pixelhit);
  root->SetBranchAddress("MuonInfo.i_nStripLayer",MuonInfo_i_nStripLayer);
  root->SetBranchAddress("MuonInfo.i_nPixelLayer",MuonInfo_i_nPixelLayer);
  root->SetBranchAddress("MuonInfo.i_chi2",MuonInfo_i_chi2);
  root->SetBranchAddress("MuonInfo.i_ndf",MuonInfo_i_ndf);
  root->SetBranchAddress("MuonInfo.fpbarrelhit",MuonInfo_fpbarrelhit);
  root->SetBranchAddress("MuonInfo.fpendcaphit",MuonInfo_fpendcaphit);
  root->SetBranchAddress("MuonInfo.d0",MuonInfo_d0);
  root->SetBranchAddress("MuonInfo.dz",MuonInfo_dz);
  root->SetBranchAddress("MuonInfo.dzPV",MuonInfo_dzPV);
  root->SetBranchAddress("MuonInfo.dxyPV",MuonInfo_dxyPV);
  root->SetBranchAddress("MuonInfo.g_striphit",MuonInfo_g_striphit);
  root->SetBranchAddress("MuonInfo.g_pixelhit",MuonInfo_g_pixelhit);  
  root->SetBranchAddress("MuonInfo.g_chi2",MuonInfo_g_chi2);
  root->SetBranchAddress("MuonInfo.g_ndf",MuonInfo_g_ndf);
  root->SetBranchAddress("MuonInfo.nmuhit",MuonInfo_nmuhit);
  root->SetBranchAddress("MuonInfo.isTriggered",MuonInfo_isTriggered);
  //BInfo
  root->SetBranchAddress("BInfo.uj_size",&BInfo_uj_size);
  root->SetBranchAddress("BInfo.uj_index",BInfo_uj_index);
  root->SetBranchAddress("BInfo.uj_mass",BInfo_uj_mass);
  root->SetBranchAddress("BInfo.uj_eta",BInfo_uj_eta);
  root->SetBranchAddress("BInfo.uj_phi",BInfo_uj_phi);
  root->SetBranchAddress("BInfo.uj_px",BInfo_uj_px);
  root->SetBranchAddress("BInfo.uj_py",BInfo_uj_py);
  root->SetBranchAddress("BInfo.uj_pz",BInfo_uj_pz);
  root->SetBranchAddress("BInfo.uj_vtxX",BInfo_uj_vtxX);
  root->SetBranchAddress("BInfo.uj_vtxY",BInfo_uj_vtxY);
  root->SetBranchAddress("BInfo.uj_vtxZ",BInfo_uj_vtxZ);
  root->SetBranchAddress("BInfo.uj_vtxXE",BInfo_uj_vtxXE);
  root->SetBranchAddress("BInfo.uj_vtxYE",BInfo_uj_vtxYE);
  root->SetBranchAddress("BInfo.uj_vtxZE",BInfo_uj_vtxZE);
  root->SetBranchAddress("BInfo.uj_vtxdof",BInfo_uj_vtxdof);
  root->SetBranchAddress("BInfo.uj_vtxchi2",BInfo_uj_vtxchi2);
  root->SetBranchAddress("BInfo.uj_rfmu1_index",BInfo_uj_rfmu1_index);
  root->SetBranchAddress("BInfo.uj_rfmu2_index",BInfo_uj_rfmu2_index);
  root->SetBranchAddress("BInfo.uj_isGoodCand",BInfo_uj_isGoodCand);
  root->SetBranchAddress("BInfo.uj_rfmu1_px",BInfo_uj_rfmu1_px);
  root->SetBranchAddress("BInfo.uj_rfmu1_py",BInfo_uj_rfmu1_py);
  root->SetBranchAddress("BInfo.uj_rfmu1_pz",BInfo_uj_rfmu1_pz);
  root->SetBranchAddress("BInfo.uj_rfmu2_px",BInfo_uj_rfmu2_px);
  root->SetBranchAddress("BInfo.uj_rfmu2_py",BInfo_uj_rfmu2_py);
  root->SetBranchAddress("BInfo.uj_rfmu2_pz",BInfo_uj_rfmu2_pz);
  root->SetBranchAddress("BInfo.size",&BInfo_size);
  root->SetBranchAddress("BInfo.index",BInfo_index);
  root->SetBranchAddress("BInfo.mass",BInfo_mass);
  root->SetBranchAddress("BInfo.eta",BInfo_eta);
  root->SetBranchAddress("BInfo.phi",BInfo_phi);  
  root->SetBranchAddress("BInfo.px",BInfo_px);
  root->SetBranchAddress("BInfo.py",BInfo_py);
  root->SetBranchAddress("BInfo.pt",BInfo_pt);
  root->SetBranchAddress("BInfo.pz",BInfo_pz);
  root->SetBranchAddress("BInfo.pxE",BInfo_pxE);
  root->SetBranchAddress("BInfo.pyE",BInfo_pyE);
  root->SetBranchAddress("BInfo.pzE",BInfo_pzE);
  root->SetBranchAddress("BInfo.vtxX",BInfo_vtxX);
  root->SetBranchAddress("BInfo.vtxY",BInfo_vtxY);
  root->SetBranchAddress("BInfo.vtxZ",BInfo_vtxZ);
  root->SetBranchAddress("BInfo.vtxXE",BInfo_vtxXE);
  root->SetBranchAddress("BInfo.vtxYE",BInfo_vtxYE);
  root->SetBranchAddress("BInfo.vtxZE",BInfo_vtxZE);
  root->SetBranchAddress("BInfo.vtxdof",BInfo_vtxdof);
  root->SetBranchAddress("BInfo.vtxchi2",BInfo_vtxchi2);
  root->SetBranchAddress("BInfo.rfuj_index",BInfo_rfuj_index);
  root->SetBranchAddress("BInfo.rftk1_index",BInfo_rftk1_index);
  root->SetBranchAddress("BInfo.rftk2_index",BInfo_rftk2_index);
  root->SetBranchAddress("BInfo.isGoodCand",BInfo_isGoodCand);
  root->SetBranchAddress("BInfo.type",BInfo_type);
  root->SetBranchAddress("BInfo.rfmu1_px",BInfo_rfmu1_px);
  root->SetBranchAddress("BInfo.rfmu1_py",BInfo_rfmu1_py);
  root->SetBranchAddress("BInfo.rfmu1_pz",BInfo_rfmu1_pz);
  root->SetBranchAddress("BInfo.rfmu2_px",BInfo_rfmu2_px);
  root->SetBranchAddress("BInfo.rfmu2_py",BInfo_rfmu2_py);
  root->SetBranchAddress("BInfo.rfmu2_pz",BInfo_rfmu2_pz);
  root->SetBranchAddress("BInfo.rftk1_px",BInfo_rftk1_px);
  root->SetBranchAddress("BInfo.rftk1_py",BInfo_rftk1_py);
  root->SetBranchAddress("BInfo.rftk1_pz",BInfo_rftk1_pz);
  root->SetBranchAddress("BInfo.rftk2_px",BInfo_rftk2_px);
  root->SetBranchAddress("BInfo.rftk2_py",BInfo_rftk2_py);
  root->SetBranchAddress("BInfo.rftk2_pz",BInfo_rftk2_pz);
  root->SetBranchAddress("BInfo.tktk_mass",BInfo_tktk_mass);
  root->SetBranchAddress("BInfo.tktk_pt",BInfo_tktk_pt);
  root->SetBranchAddress("BInfo.tktk_eta",BInfo_tktk_eta);
  root->SetBranchAddress("BInfo.tktk_phi",BInfo_tktk_phi);
  root->SetBranchAddress("BInfo.tktk_px",BInfo_tktk_px);
  root->SetBranchAddress("BInfo.tktk_py",BInfo_tktk_py);
  root->SetBranchAddress("BInfo.tktk_pz",BInfo_tktk_pz);
  root->SetBranchAddress("BInfo.tktk_vtxX",BInfo_tktk_vtxX);
  root->SetBranchAddress("BInfo.tktk_vtxY",BInfo_tktk_vtxY);
  root->SetBranchAddress("BInfo.tktk_vtxZ",BInfo_tktk_vtxZ);
  root->SetBranchAddress("BInfo.tktk_vtxXE",BInfo_tktk_vtxXE);
  root->SetBranchAddress("BInfo.tktk_vtxYE",BInfo_tktk_vtxYE);
  root->SetBranchAddress("BInfo.tktk_vtxZE",BInfo_tktk_vtxZE);
  root->SetBranchAddress("BInfo.tktk_vtxdof",BInfo_tktk_vtxdof);
  root->SetBranchAddress("BInfo.tktk_vtxchi2",BInfo_tktk_vtxchi2);
  root->SetBranchAddress("BInfo.tktk_rftk1_px",BInfo_tktk_rftk1_px);
  root->SetBranchAddress("BInfo.tktk_rftk1_py",BInfo_tktk_rftk1_py);
  root->SetBranchAddress("BInfo.tktk_rftk1_pz",BInfo_tktk_rftk1_pz);
  root->SetBranchAddress("BInfo.tktk_rftk2_px",BInfo_tktk_rftk2_px);
  root->SetBranchAddress("BInfo.tktk_rftk2_py",BInfo_tktk_rftk2_py);
  root->SetBranchAddress("BInfo.tktk_rftk2_pz",BInfo_tktk_rftk2_pz);
}
*/
