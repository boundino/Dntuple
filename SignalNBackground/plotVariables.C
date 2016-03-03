#include <plotVariables.h>

enum real{pp_Dzero,pp_Dstar3p,pp_Dstar5p,PbPb_Dzero,PbPb_Dstar3p,PbPb_Dstar5p} isChannel=pp_Dzero;
void plotVariables()
{
  gStyle->SetPadTopMargin(0.08);
  gStyle->SetPadBottomMargin(0.12);

  void plot(TString var, TString varlatex, TString varname, Int_t nbins, Double_t vmin, Double_t vmax);

  plot("Dalpha","D* #alpha","alpha", 50, 0., 3.2);
  plot("Dchi2cl","D* vertex prob","vtxprob", 50, 0., 1.);
  plot("DsvpvDistance/DsvpvDisErr","D* 3D decay length sig","ffls3d", 50, 0., 20.);

  /*
  plot("Ddtheta","D* #theta","theta", 50, 0., 3.2);
  plot("DlxyBS/DlxyBSErr","D* lxyBS sig","lxyBSsig", 50, 0., 50);
  plot("DtktkRes_chi2cl","D^{0} vertex prob","resvtxprob", 50, 0., 1.);
  plot("DtktkRes_alpha","D^{0} #alpha","resalpha", 50, 0., 3.2);
  plot("DtktkRes_svpvDistance/DtktkRes_svpvDisErr","D^{0} decay length sig","resffls3d", 50, 0, 20.);
  */
}

void plot(TString var, TString varlatex, TString varname, Int_t nbins, Double_t vmin, Double_t vmax)
{
  cout<<"---- Processing - "<<var<<endl;
  cout<<"  -- Fill histograms"<<endl;
  TFile* ifBkg = new TFile(infnameBkg[isChannel]);
  TTree* ntBkg = (TTree*)ifBkg->Get(texNtuple[isChannel]);
  ntBkg->AddFriend("ntHlt");
  TFile* ifSgl = new TFile(infnameSgl[isChannel]);
  TTree* ntSgl = (TTree*)ifSgl->Get(texNtuple[isChannel]);
  ntSgl->AddFriend("ntHlt");
  ntSgl->AddFriend("ntHi");

  TH1D* hBkg = new TH1D(Form("hBkg_%s",varname.Data()),"",nbins,vmin,vmax);
  TH1D* hSgl = new TH1D(Form("hSgl_%s",varname.Data()),"",nbins,vmin,vmax);

  ntBkg->Project(Form("hBkg_%s",varname.Data()),var,Form("%s&&%s",selTriggerBkg[isChannel].Data(),selBkg[isChannel].Data()));
  ntSgl->Project(Form("hSgl_%s",varname.Data()),var,TCut(weight[isChannel])*Form("%s&&%s",selTriggerSgl[isChannel].Data(),selSgl[isChannel].Data()));

  cout<<"  -- Calculate normalization"<<endl;
  Double_t normBkg=0,normSgl=0;
  //normBkg = hBkg->GetEntries();
  //normSgl = hSgl->GetEntries();
  normBkg = hBkg->Integral(vmin,vmax);
  normSgl = hSgl->Integral(vmin,vmax);
  cout<<"     normBkg: "<<normBkg<<" ;   normSgl: "<<normSgl<<endl;

  cout<<"  -- Normalize histograms"<<endl;
  hBkg->Scale(1./normBkg);
  hSgl->Scale(1./normSgl); 

  cout<<"  -- Plot"<<endl;
  hBkg->SetXTitle(varlatex);
  hBkg->SetYTitle("#Probability");
  hBkg->SetTitleOffset(1.5,"Y");
  Double_t hisMax = (hBkg->GetMaximum()>hSgl->GetMaximum())?hBkg->GetMaximum():hSgl->GetMaximum();
  hBkg->SetMaximum(hisMax*1.2);

  hBkg->SetLineColor(kBlue+1);
  hBkg->SetFillStyle(1001);
  hBkg->SetFillColor(kBlue-9);
  hBkg->SetLineWidth(3);
  hBkg->SetStats(0);

  TH1D* hSglplot = new TH1D(Form("hSglplot_%s",varname.Data()),"",nbins,vmin,vmax);
  for(int ib=0;ib<nbins;ib++) hSglplot->SetBinContent(ib+1,hSgl->GetBinContent(ib+1));
  hSglplot->SetLineColor(kRed);
  hSglplot->SetFillStyle(3004);
  hSglplot->SetFillColor(kRed);
  hSglplot->SetLineWidth(3);
  hSglplot->SetStats(0);

  TCanvas* c = new TCanvas(Form("c_%s",varname.Data()),"",600,600);
  hBkg->Draw();
  hSglplot->Draw("same");

  cout<<"  -- Plot legends"<<endl;
  TLatex* tex = new TLatex(0.18,0.935,Form("5.02TeV %s",texPP[isChannel].Data()));
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.055);
  tex->Draw();
  TLatex* texp;
  texp = new TLatex(0.68,0.935,texDecay[isChannel]);
  texp->SetNDC();
  texp->SetTextFont(42);
  texp->SetTextSize(0.055);
  texp->Draw();
  TLegend* leg = new TLegend(0.56,0.70,0.86,0.86);
  leg->AddEntry(hBkg,"Background","f");
  leg->AddEntry(hSglplot,"Signal","f");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->Draw("same");

  cout<<"  -- Save plots"<<endl;
  c->SaveAs(Form("plots/%s_%s/c_%s.pdf",texPP[isChannel].Data(),texNtuple[isChannel].Data(),varname.Data()));
  cout<<endl;
}

