#include "PtBins.h"

Float_t ptmin = 20.;
Float_t ptmax = 25.;

void readxmlPP()
{
  void calRatio(Float_t* results);

  //read weight file
  const char* filename = Form("weights/%s/TMVAClassification_CutsSA.weights.xml",channel.Data());
  void *doc = TMVA::gTools().xmlengine().ParseFile(filename,TMVA::gTools().xmlenginebuffersize());
  void* rootnode = TMVA::gTools().xmlengine().DocGetRootElement(doc);//node "MethodSetup"
  TString fullMethodName("");  
  TMVA::gTools().ReadAttr(rootnode, "Method", fullMethodName);
  cout<<endl;
  cout<<" ╒══════════════════════════════════════════════════╕"<<endl;
  cout<<" |               Cut Opt Configuration              |"<<endl;
  cout<<" ├────────────┬────────────────────────────┬────────┤"<<endl;
  cout<<" │ "<<setiosflags(ios::left)<<setw(10)<<"Method"<<" | "<<setiosflags(ios::left)<<setw(26)<<fullMethodName<<" | "<<setiosflags(ios::left)<<setw(6)<<" "<<" |"<<endl;

  void *opts = TMVA::gTools().GetChild(rootnode,"Options");
  void* opt = TMVA::gTools().GetChild(opts,"Option");

  TString varProp("");
  while(opt)
    {
      TString optname("");
      TMVA::gTools().ReadAttr(opt, "name", optname);
      if(optname=="VarProp") varProp = TMVA::gTools().GetContent(opt);
      opt = TMVA::gTools().GetNextChild(opt);
    }

  TObjArray *marginclass = varProp.Tokenize(" ");
  std::vector<TString> margins;//avoid objarrays...
  int i=0;
  for (i=0;i<marginclass->GetEntries();i++)
    {
      margins.push_back(((TObjString *)(marginclass->At(i)))->String());
    }
  void* variables = TMVA::gTools().GetChild(rootnode,"Variables");
  UInt_t nVar;
  std::vector<TString> varnames;
  TMVA::gTools().ReadAttr(variables, "NVar", nVar);

  void* var = TMVA::gTools().GetChild(variables,"Variable");
  TString varval[3];
  for (unsigned int k=0;k<nVar;k++)
    {
      TString varname("");
      TMVA::gTools().ReadAttr(var, "Expression", varname);
      TString tem = Form("Variable%i",k);
      varval[k] = varname;
      cout<<" ├────────────┼────────────────────────────┼────────┤"<<endl;
      cout<<" │ "<<setiosflags(ios::left)<<setw(10)<<tem<<" | "<<setiosflags(ios::left)<<setw(26)<<varname<<" | "<<setiosflags(ios::left)<<setw(6)<<margins[k]<<" |"<<endl;
      var = TMVA::gTools().GetNextChild(var);
      varnames.push_back(varname);
    }
  cout<<" ╞════════════╪════════════════════════════╪════════╡"<<endl;

  void* weight = TMVA::gTools().GetChild(rootnode,"Weights");
  void* eff = TMVA::gTools().GetChild(weight,"Bin");
  Int_t n = 0;
  while(eff)
    {
      TMVA::gTools().ReadAttr(eff, "effS", effS[n]);
      TMVA::gTools().ReadAttr(eff, "effB", effB[n]);
      void* cutsnode = TMVA::gTools().GetChild(eff,"Cuts");

      TString cut;
      for (ULong_t l=0;l<varnames.size();l++)
	{
	  Double_t min,max;
	  TMVA::gTools().ReadAttr(cutsnode, TString("cutMin_")+l, min);
	  TMVA::gTools().ReadAttr(cutsnode, TString("cutMax_")+l, max);
	  TString lessmax = "<"; lessmax+=max;
	  TString moremin = ">"; moremin+=min;
	  if(margins[l]=="FMin")
	    {
	      cut+=" && "+varnames[l]+lessmax;
	      cutval[l].push_back(max);
	    }
	  if(margins[l]=="FMax")
	    {
	      cut+=" && "+varnames[l]+moremin;
	      cutval[l].push_back(min);
	    }
	}
      cuts.push_back(cut);
      eff = TMVA::gTools().GetNextChild(eff);
      n++;
    }
  TMVA::gTools().xmlengine().FreeDoc(doc);

  Float_t wS = 0;
  Float_t wB = 0;
  Float_t* weights = new float[2];
  //
  calRatio(weights);
  //
  cout<<endl;
  wS = weights[1];
  wB = weights[0];

  cout<<"Looking for max significance ..."<<endl;

  Double_t max = 0;
  Int_t maxindex = 0;
  effS[0]=0;
  for(i=1;i<100;i++)
    {
      effSig[i] = wS*effS[i]/sqrt(wS*effS[i]+wB*effB[i]);
      if(i==1)
	{
	  max=effSig[1];
	  maxindex=1;
	}
      else if(effSig[i]>max)
	{
	  max=effSig[i];
	  maxindex=i;
	}
    }
  cout<<endl;
  cout<<" ╒══════════════════════════════════════════════════╕"<<endl;
  cout<<" |                     Opt Result                   |"<<endl;
  cout<<" ├────────────┬────────────┬────────────┬───────────┤"<<endl;
  cout<<" │ "<<setiosflags(ios::left)<<setw(10)<<"Sig eff"<<" | "<<setiosflags(ios::left)<<setw(10)<<effS[maxindex]<<" | "<<setiosflags(ios::left)<<setw(10)<<"Signi"<<" | "<<setiosflags(ios::left)<<setw(9)<<max<<" |"<<endl;
  cout<<" ├────────────┴────────────┴───┬────────┴───────────┤"<<endl;

  Int_t m;
  for(m=0;m<3;m++)
    {
      if(m) cout<<" ├─────────────────────────────┼────────────────────┤"<<endl;
      cout<<" │ "<<setiosflags(ios::left)<<setw(27)<<varval[m]<<" | "<<setiosflags(ios::left)<<setw(18)<<cutval[m].at(maxindex)<<" |"<<endl;
    }
  cout<<" ╘═════════════════════════════╧════════════════════╛"<<endl;
  cout<<endl;

  TGraph* gsig = new TGraph(100,effS,effSig);
  gsig->SetTitle("");
  TCanvas* csig = new TCanvas("c1","",200,100,600,600);
  csig->SetGrid();
  gsig->Draw("A*");
  TLegend* leg = new TLegend(0.08,0.91,0.15,0.98);
  leg->AddEntry("null", "D*","");
  leg->SetFillColor(kWhite);
  leg->Draw();
  csig->SaveAs(Form("plots/plot_%s/sig/%s/sig-eff_%.1f_%.1f.pdf",channel.Data(),func.Data(),ptmin,ptmax));
}

void calRatio(Float_t* results)
{
  TFile* inputS = new TFile("/afs/cern.ch/work/j/jisun/public/Dmesonana/Dmesonana_hiforest_D0filtered_2760GeV_D0pt3_pthat015305080120_1220_1222_all_v1.root");
  TFile* inputB = new TFile("/afs/cern.ch/work/j/jisun/public/Dmesonana/Dmesonana_PPJet_Jettrig_obj_pt0p5_d0dstar_alpha1p0_highpurity_1209_all_v1.root");
  TTree* ntS = (TTree*)inputS->Get("ntDD0kpipi");
  TTree* ntB = (TTree*)inputB->Get("ntDD0kpipi");
  TTree* ntG = (TTree*)inputS->Get("ntGen");

  Int_t i;
  TString cutS = Form("%s&&Dpt>%f&&Dpt<%f&&Dgen==23333",cut.Data(),ptmin,ptmax);
  TString cutB = Form("%s&&Dpt>%f&&Dpt<%f&&TMath::Abs(Dmass-2.01)>0.1&&TMath::Abs(Dmass-2.01)<0.15",cut.Data(),ptmin,ptmax);
  //TString cutB = Form("%s&&Dpt>%f&&Dpt<%f&&TMath::Abs(DtktkResmass-1.864)>0.1&&TMath::Abs(DtktkResmass-1.864)<0.15",cut.Data(),ptmin,ptmax);
  TString cutG = Form("%s&&Gpt>%f&&Gpt<%f",cut_gen.Data(),ptmin,ptmax);
  if(verbose)
    {
      cout<<"  -- Cut applied"
      cout<<"cutS: "<<cutS<<endl;
      cout<<"cutB: "<<cutB<<endl;
      cout<<"cutG: "<<cutG<<endl;
    }

  TString ptstring = Form("(%.1f,%.1f)",ptmin,ptmax);
  cout<<" │ "<<setiosflags(ios::left)<<setw(10)<<"Pt"<<" │ "<<setiosflags(ios::left)<<setw(26)<<ptstring<<" | "<<setiosflags(ios::left)<<setw(6)<<" "<<" |"<<endl;
  cout<<" ╘════════════╧════════════════════════════╧════════╛"<<endl;
  cout<<endl;

  //Fill histogram
  TH1D* hmassS = new TH1D("hmassS","",50,1.7,2.3);
  TH1D* hmassB = new TH1D("hmassB","",50,0.,10.);
  ntS->Project("hmassS","Dmass",cutS);
  ntB->Project("hmassB","Dmass",cutB);

  //Get sigma
  hmassS->GetXaxis()->SetTitle("Gen-matched D mass (GeV/c^{2})");
  hmassS->GetYaxis()->SetTitle("Entries");
  TCanvas* cmassS = new TCanvas("cmassS","",200,10,600,600);
  hmassS->Draw();
  TF1* fmass = new TF1("fmass","[0]*([3]*Gaus(x,[1],[2])+(1-[3])*Gaus(x,[1],[4]))");
  fmass->SetParLimits(2,0.005,0.05);
  fmass->SetParLimits(3,0,1);
  Double_t setparam1 = 2.01;
  Double_t setparam2 = 0.01;
  Double_t setparam4 = 0.08;
  fmass->SetParameter(1,setparam1);
  fmass->SetParameter(2,setparam2);
  fmass->SetParameter(4,setparam4);
  fmass->FixParameter(3,1);
  hmassS->Fit("fmass","","",1.7,2.3);
  cmassS->SaveAs(Form("plots/plot_%s/Signal.pdf",channel.Data()));
  Float_t sigma = fmass->GetParameter(2);

  //Background
  hmassB->GetXaxis()->SetTitle("Sideband D mass (GeV/c^{2})");
  hmassB->GetYaxis()->SetTitle("Entries");
  Int_t nentriesB = hmassB->GetEntries();
  TCanvas* cmassB = new TCanvas("cmassB","",200,10,600,600);
  hmassB->Draw();
  cmassB->SaveAs(Form("plots/plot_%s/Background.pdf",channel.Data()));

  //Calculate theory prediction
  ifstream getdata("fonlls/fo_Dzero_pp_2.76_eta2.dat");
  if(!getdata.is_open()) cout<<"Opening the file fails"<<endl;
  Float_t tem;
  Int_t nbin = 0;

  while(!getdata.eof())
    {
      getdata>>pt[nbin]>>central[nbin]>>tem>>tem>>tem>>tem>>tem>>tem>>tem>>tem;
      if(pt[nbin]>=ptmin && pt[nbin]<=ptmax) nbin++;
    }
  TH1D* hfonll = new TH1D("hfonll","",nbin-1,pt);
  for (i=0;i<nbin;i++)
    {
      hfonll->SetBinContent(i,central[i]);
    }
  hfonll->Draw();

  //Efficiency correction
  TH1D* hgen = new TH1D("hgen","",nbin-1,pt);
  TH1D* hrec = new TH1D("hrec","",nbin-1,pt);
  TH1D* heff = new TH1D("heff","",nbin-1,pt);
  ntG->Project("hgen","Gpt",cutG);
  ntS->Project("hrec","Dpt",cutS);
  heff->Divide(hrec,hgen,1.,1.,"B");
  TH1D* htheoryreco = new TH1D("htheoryreco","",nbin-1,pt);
  htheoryreco->Multiply(heff,hfonll,1,1,"B");

  //Scale signal and background
  Double_t lumi = 13.9;//
  Double_t prodfrac = 0.1;//
  Double_t decaybrac = 0.677*0.0388;//D*(D0pi) * D0(kpi)
  Double_t deltapt = 0.25;
  Double_t yieldDstar = htheoryreco->Integral();
  yieldDstar*=(1.e-9)*lumi*prodfrac*decaybrac*deltapt;

  results[0] = nentriesB*Nsigma*sigma/0.05;
  results[1] = yieldDstar;
  cout<<endl;
  cout<<" ╒══════════════════════════════════════════════════╕"<<endl;
  cout<<" |                   Weight Result                  |"<<endl;
  cout<<" ├────────────┬────────────┬────────────┬───────────┤"<<endl;
  cout<<" │ "<<setiosflags(ios::left)<<setw(10)<<"Bkg #"<<" | "<<setiosflags(ios::left)<<setw(10)<<nentriesB<<" | "<<setiosflags(ios::left)<<setw(10)<<"Sig reg"<<" | "<<setiosflags(ios::left)<<setw(9)<<setprecision(3)<<sigma*Nsigma*2<<" |"<<endl;
  cout<<" ├────────────┼────────────┼────────────┼───────────┤"<<endl;
  cout<<" │ "<<setiosflags(ios::left)<<setw(10)<<"SigWeight"<<" | "<<setiosflags(ios::left)<<setw(10)<<yieldDstar<<" | "<<setiosflags(ios::left)<<setw(10)<<"BkgWeight"<<" | "<<setiosflags(ios::left)<<setw(9)<<nentriesB*Nsigma*sigma/0.05<<" |"<<endl;
  cout<<" ╘════════════╧════════════╧════════════╧═══════════╛"<<endl;
}


/*
void GetCut(double eff)
{
  //find closest eff
  int ind = 0; float deff=fabs(effS[0]-eff);
  for (unsigned int i=0;i<cuts.size();i++)
    {
      if (fabs(effS[i]-eff)<deff)
	{
	  ind = i;
	  deff = fabs(effS[i]-eff);
	}
    }
  cout<<"Cut for signal eff. "<<effS[ind]<<" and bkg. rej. "<<effB[ind]<<":"<<endl;
  cout<<cuts[ind]<<endl;
}
*/
