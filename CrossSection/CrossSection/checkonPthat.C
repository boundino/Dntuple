void checkonPthat(int isPbPb=0){

  TFile*file;
  const int nbins=12;
  double boundaries[nbins+1]={0,5,10,15,20,30,40,50,60,70,80,90,100};
  
  if(isPbPb==0) file=new TFile("/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_prompt_D0_dPt0tkPt0p5_pthatweight.root");
  else file=new TFile("/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_PbPb_Pythia8_prompt_D0_dPt1tkPt1_pthatweight.root");
  TTree* nt = (TTree*) file->Get("ntDkpi");
  TTree* HltTree= (TTree*) file->Get("ntHlt");
  HltTree->AddFriend(nt);
  nt->AddFriend(HltTree);
  TTree* ntHi = (TTree*) file->Get("ntHi");
  nt->AddFriend(ntHi);

  TProfile*profileDsvpvDisErrPthat[nbins];
  
  for (int m=0;m<nbins;m++) {
    TString histoname=Form("profileDsvpvDisErrPthat%d",m);
    profileDsvpvDisErrPthat[m]=new TProfile(histoname.Data(),histoname.Data(),30,0,500,0,1000);  
    nt->Draw(Form("DsvpvDisErr:pthat>>%s",histoname.Data()),Form("Dpt>%f&&Dpt<%f&&Dgen==23333",boundaries[m],boundaries[m+1]));
  }  

  TH1F*histocoefficient=new TH1F("histocoefficient","histocoefficient",nbins,boundaries);
  TCanvas*canvas=new TCanvas("canvas","canvas",1000,1000);
  canvas->Divide(4,3);
  for (int m=0;m<nbins;m++) {
  canvas->cd(m+1);
  profileDsvpvDisErrPthat[m]->Draw();
  TF1*myfit=new TF1("myfit","pol1",0,500);
  profileDsvpvDisErrPthat[m]->Fit("myfit");
  double coeff=myfit->GetParameter(1);
  double coefferr=myfit->GetParError(1);
  
  histocoefficient->SetBinContent(m+1,coeff);
  histocoefficient->SetBinError(m+1,coefferr);
  }
 TCanvas*canvasCoeff=new TCanvas("canvasCoeff","canvasCoeff",500,500);
 canvasCoeff->cd(1);
  histocoefficient->Draw();
}

