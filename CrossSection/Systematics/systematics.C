#include <TF1.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TLegend.h>

// Yen-Jie: systematics table for D meson
// Unit: In percentage

// =============================================================================================================
const int nPtBins = 15;
double PtBins[nPtBins+1] = { 2, 3, 4, 5, 6, 8, 10, 15, 20, 25, 30, 40, 50, 60, 80, 100};

// =============================================================================================================
// D meson decay
// =============================================================================================================
double DKpiBRUncertainty	= 1.29;			// from PDG

// =============================================================================================================
// pp uncertainty
// =============================================================================================================

// Normalization uncertainty
double ppLumiUncertainty 	= 5;			// 5% for the moment, to be updated (4/7/2016)

// Point-to-point
double ppTrackingEfficiency 	= 4;   			// single track systematics from D* studies
TH1D*  ppSignalExtraction;				// (4/7/2016)
TH1D*  ppMesonSelection;				// (4/7/2016)
TH1D*  ppBFeedDownCorrection; 				// (4/7/2016)

TF1 *fPPPtShape = new TF1("fPPPtShapeSig","[0]+[1]/(x)+[2]/x/x+[3]*x");


// =============================================================================================================
// PbPb uncertainty
// =============================================================================================================

// Normalization uncertainty
double PbPbNMBUncertainty	= 2;			// uncertainty associated with minbias events,
							// used in RAA for pT < 20 GeV (4/7/2016)
double TAAUncertainty0to100	= 2.5;			// Updated number (4/7/2016)
double TAAUncertainty0to10	= 1.8;			// Updated number (4/7/2016)
double PbPbTrigger		= 0.6;			// Statistical uncertainty of the eff plateau (92.8+-0.6%)
double PbPbLumiUncertainty	= 10;			// 10% for the moment, to be updated (from Daniel), NOT used

// Point-to-point

TH1D*  PbPbSignalExtraction;				// (4/7/2016)
TH1D*  PbPbMesonSelection;				// (4/7/2016)
TH1D*  PbPbBFeedDownCorrection;				// (4/7/2016)

TF1 *fPbPbPtShape= new TF1("fPbPbPtShapeSig","[0]+[1]/(x)+[2]/x/x+[3]*x");


bool initialized = 0;

void initializationPP()
{
   ppBFeedDownCorrection = new TH1D("ppBFeedDownCorrection","",nPtBins,PtBins);
   ppBFeedDownCorrection->SetBinContent(1,	1.2);
   ppBFeedDownCorrection->SetBinContent(2,	1.2);
   ppBFeedDownCorrection->SetBinContent(3,	1.2);
   ppBFeedDownCorrection->SetBinContent(4,	1.2);
   ppBFeedDownCorrection->SetBinContent(5,	1.4);
   ppBFeedDownCorrection->SetBinContent(6,	1.4);
   ppBFeedDownCorrection->SetBinContent(7,	2.0);
   ppBFeedDownCorrection->SetBinContent(8,	2.0);
   ppBFeedDownCorrection->SetBinContent(9,	0.6);
   ppBFeedDownCorrection->SetBinContent(10,	0.6);
   ppBFeedDownCorrection->SetBinContent(11,	0.6);
   ppBFeedDownCorrection->SetBinContent(12,	0.6);
   ppBFeedDownCorrection->SetBinContent(13,	2.7);
   ppBFeedDownCorrection->SetBinContent(14,	2.7);
   ppBFeedDownCorrection->SetBinContent(15,	2.7);

   ppMesonSelection = new TH1D("ppMesonSelection","",nPtBins,PtBins);
   ppMesonSelection->SetBinContent(1,		3.6);
   ppMesonSelection->SetBinContent(2,		3.6);
   ppMesonSelection->SetBinContent(3,		3.6);
   ppMesonSelection->SetBinContent(4,		3.6);
   ppMesonSelection->SetBinContent(5,		3.6);
   ppMesonSelection->SetBinContent(6,		3.6);
   ppMesonSelection->SetBinContent(7,		3.6);
   ppMesonSelection->SetBinContent(8,		3.6);
   ppMesonSelection->SetBinContent(9,		0.5);
   ppMesonSelection->SetBinContent(10,		0.5);
   ppMesonSelection->SetBinContent(11,		0.5);
   ppMesonSelection->SetBinContent(12,		0.5);
   ppMesonSelection->SetBinContent(13,		0.5);
   ppMesonSelection->SetBinContent(14,		0.5);
   ppMesonSelection->SetBinContent(15,		0.5);

   ppSignalExtraction = new TH1D("ppSignalExtraction","",nPtBins,PtBins);
   ppSignalExtraction->SetBinContent(1,		8.2);
   ppSignalExtraction->SetBinContent(2,		7.6);
   ppSignalExtraction->SetBinContent(3,		3.5);
   ppSignalExtraction->SetBinContent(4,		3.0);
   ppSignalExtraction->SetBinContent(5,		3.0);
   ppSignalExtraction->SetBinContent(6,		1.7);
   ppSignalExtraction->SetBinContent(7,		2.1);
   ppSignalExtraction->SetBinContent(8,		4.0);
   ppSignalExtraction->SetBinContent(9,		2.0);
   ppSignalExtraction->SetBinContent(10,	1.6);
   ppSignalExtraction->SetBinContent(11,	2.3);
   ppSignalExtraction->SetBinContent(12,	2.8);
   ppSignalExtraction->SetBinContent(13,	5.2);
   ppSignalExtraction->SetBinContent(14,	2.4);
   ppSignalExtraction->SetBinContent(15,	7.6);
    
   fPPPtShape->SetParameters(0.999265,-0.0458006,-0.181359,0);
   }

void initializationPbPbCent0100()
{
   PbPbBFeedDownCorrection = new TH1D("PbPbBFeedDownCorrection","",nPtBins,PtBins);
   PbPbBFeedDownCorrection->SetBinContent(1,	0.6);
   PbPbBFeedDownCorrection->SetBinContent(2,	0.6);
   PbPbBFeedDownCorrection->SetBinContent(3,	0.6);
   PbPbBFeedDownCorrection->SetBinContent(4,	0.6);
   PbPbBFeedDownCorrection->SetBinContent(5,	2.0);
   PbPbBFeedDownCorrection->SetBinContent(6,	2.0);
   PbPbBFeedDownCorrection->SetBinContent(7,	1.7);
   PbPbBFeedDownCorrection->SetBinContent(8,	1.7);
   PbPbBFeedDownCorrection->SetBinContent(9,	1.6);
   PbPbBFeedDownCorrection->SetBinContent(10,	1.6);
   PbPbBFeedDownCorrection->SetBinContent(11,	1.6);
   PbPbBFeedDownCorrection->SetBinContent(12,	1.6);
   PbPbBFeedDownCorrection->SetBinContent(13,	3.6);
   PbPbBFeedDownCorrection->SetBinContent(14,	3.6);
   PbPbBFeedDownCorrection->SetBinContent(15,	3.6);

   PbPbMesonSelection = new TH1D("PbPbMesonSelection","",nPtBins,PtBins);
   PbPbMesonSelection->SetBinContent(1,		3.5);
   PbPbMesonSelection->SetBinContent(2,		3.5);
   PbPbMesonSelection->SetBinContent(3,		3.5);
   PbPbMesonSelection->SetBinContent(4,		3.5);
   PbPbMesonSelection->SetBinContent(5,		3.5);
   PbPbMesonSelection->SetBinContent(6,		3.5);
   PbPbMesonSelection->SetBinContent(7,		3.5);
   PbPbMesonSelection->SetBinContent(8,		3.5);
   PbPbMesonSelection->SetBinContent(9,		2.7);
   PbPbMesonSelection->SetBinContent(10,		2.7);
   PbPbMesonSelection->SetBinContent(11,		2.7);
   PbPbMesonSelection->SetBinContent(12,		2.7);
   PbPbMesonSelection->SetBinContent(13,		2.7);
   PbPbMesonSelection->SetBinContent(14,		2.7);
   PbPbMesonSelection->SetBinContent(15,		2.7);


   PbPbSignalExtraction = new TH1D("PbPbSignalExtraction","",nPtBins,PtBins);
   PbPbSignalExtraction->SetBinContent(1,	4.8);
   PbPbSignalExtraction->SetBinContent(2,	2.0);
   PbPbSignalExtraction->SetBinContent(3,	3.0);
   PbPbSignalExtraction->SetBinContent(4,	2.3);
   PbPbSignalExtraction->SetBinContent(5,	1.7);
   PbPbSignalExtraction->SetBinContent(6,	1.7);
   PbPbSignalExtraction->SetBinContent(7,	1.3);
   PbPbSignalExtraction->SetBinContent(8,	6.5);
   PbPbSignalExtraction->SetBinContent(9,	7.1);
   PbPbSignalExtraction->SetBinContent(10,	9.4);
   PbPbSignalExtraction->SetBinContent(11,	7.5);
   PbPbSignalExtraction->SetBinContent(12,	3.3);
   PbPbSignalExtraction->SetBinContent(13,	4.9);
   PbPbSignalExtraction->SetBinContent(14,	5.5);
   PbPbSignalExtraction->SetBinContent(15,	10.5);
    
   fPbPbPtShape->SetParameters(0.984161,0.0593406,-0.3992,0.000271564);
   }

void initializationPbPbCent010()
{
   PbPbBFeedDownCorrection = new TH1D("PbPbBFeedDownCorrection","",nPtBins,PtBins);
   PbPbBFeedDownCorrection->SetBinContent(1,	0.6);
   PbPbBFeedDownCorrection->SetBinContent(2,	0.6);
   PbPbBFeedDownCorrection->SetBinContent(3,	0.6);
   PbPbBFeedDownCorrection->SetBinContent(4,	0.6);
   PbPbBFeedDownCorrection->SetBinContent(5,	2.0);
   PbPbBFeedDownCorrection->SetBinContent(6,	2.0);
   PbPbBFeedDownCorrection->SetBinContent(7,	1.7);
   PbPbBFeedDownCorrection->SetBinContent(8,	1.7);
   PbPbBFeedDownCorrection->SetBinContent(9,	1.6);
   PbPbBFeedDownCorrection->SetBinContent(10,	1.6);
   PbPbBFeedDownCorrection->SetBinContent(11,	1.6);
   PbPbBFeedDownCorrection->SetBinContent(12,	1.6);
   PbPbBFeedDownCorrection->SetBinContent(13,	3.6);
   PbPbBFeedDownCorrection->SetBinContent(14,	3.6);
   PbPbBFeedDownCorrection->SetBinContent(15,	0);

   PbPbMesonSelection = new TH1D("PbPbMesonSelection","",nPtBins,PtBins);
   PbPbMesonSelection->SetBinContent(1,		8.1);
   PbPbMesonSelection->SetBinContent(2,		8.1);
   PbPbMesonSelection->SetBinContent(3,		8.1);
   PbPbMesonSelection->SetBinContent(4,		8.1);
   PbPbMesonSelection->SetBinContent(5,		8.1);
   PbPbMesonSelection->SetBinContent(6,		8.1);
   PbPbMesonSelection->SetBinContent(7,		8.1);
   PbPbMesonSelection->SetBinContent(8,		8.1);
   PbPbMesonSelection->SetBinContent(9,		1.7);
   PbPbMesonSelection->SetBinContent(10,		1.7);
   PbPbMesonSelection->SetBinContent(11,		1.7);
   PbPbMesonSelection->SetBinContent(12,		1.7);
   PbPbMesonSelection->SetBinContent(13,		1.7);
   PbPbMesonSelection->SetBinContent(14,		1.7);
   PbPbMesonSelection->SetBinContent(15,		0);


   PbPbSignalExtraction = new TH1D("PbPbSignalExtraction","",nPtBins,PtBins);
   PbPbSignalExtraction->SetBinContent(1,	12.8);
   PbPbSignalExtraction->SetBinContent(2,	4.3);
   PbPbSignalExtraction->SetBinContent(3,	5.8);
   PbPbSignalExtraction->SetBinContent(4,	5.4);
   PbPbSignalExtraction->SetBinContent(5,	3.7);
   PbPbSignalExtraction->SetBinContent(6,	3,7);
   PbPbSignalExtraction->SetBinContent(7,	3.4);
   PbPbSignalExtraction->SetBinContent(8,	12.0); // TO BE FIXED, TEMPORARY SET TO THE RESULT IN THE BIN 9
   PbPbSignalExtraction->SetBinContent(9,	12.0);
   PbPbSignalExtraction->SetBinContent(10,	8.6);
   PbPbSignalExtraction->SetBinContent(11,	12.7);
   PbPbSignalExtraction->SetBinContent(12,	6.5);
   PbPbSignalExtraction->SetBinContent(13,	10.1);
   PbPbSignalExtraction->SetBinContent(14,	17.5);
   PbPbSignalExtraction->SetBinContent(15,	0);
    
   fPbPbPtShape->SetParameters(1.00862,-0.277991,0.325087,0.);
}

void initialization(double centL=0,double centH=100){

initializationPP();
if (centL==0&&centH==100) initializationPbPbCent0100();
if (centL==0&&centH==10) initializationPbPbCent010();
initialized=1;

}

// =============================================================================================================
// RAA systematics
// =============================================================================================================
float normalizationUncertaintyForRAA(double centL=0,double centH=100)
{
   double sys = 0;
   sys+=ppLumiUncertainty*ppLumiUncertainty;
   sys+=PbPbNMBUncertainty*PbPbNMBUncertainty;
   if (centL==0&&centH==10) {
      // 0-10%
      sys+=TAAUncertainty0to10*TAAUncertainty0to10;
   } else {
      // 0-100%
      sys+=TAAUncertainty0to100*TAAUncertainty0to100;
   }
   return sqrt(sys);
}

float systematicsForRAA(double pt,double centL=0,double centH=100, double HLT=0, int stage=0)
{
   if (!initialized && centL==0&&centH==100) initialization(centL,centH);
   if (!initialized && centL==0&&centH==10) initialization(centL,centH);

   double sys=0;

   if (pt<2) return 0;
  
   if (stage==1) return sqrt(sys);
   
   sys+= PbPbSignalExtraction->GetBinContent(PbPbSignalExtraction->FindBin(pt))*
         PbPbSignalExtraction->GetBinContent(PbPbSignalExtraction->FindBin(pt));
   sys+= ppSignalExtraction->GetBinContent(ppSignalExtraction->FindBin(pt))*
         ppSignalExtraction->GetBinContent(ppSignalExtraction->FindBin(pt));


   if (stage==2) return sqrt(sys);

   sys+= ppMesonSelection->GetBinContent(ppMesonSelection->FindBin(pt))*
         ppMesonSelection->GetBinContent(ppMesonSelection->FindBin(pt));

   sys+= ppBFeedDownCorrection->GetBinContent(ppBFeedDownCorrection->FindBin(pt))*
         ppBFeedDownCorrection->GetBinContent(ppBFeedDownCorrection->FindBin(pt));
   
   sys+=fPPPtShape->Eval(pt)*fPPPtShape->Eval(pt);


   sys+= PbPbMesonSelection->GetBinContent(PbPbMesonSelection->FindBin(pt))*
         PbPbMesonSelection->GetBinContent(PbPbMesonSelection->FindBin(pt));

   sys+= PbPbBFeedDownCorrection->GetBinContent(PbPbBFeedDownCorrection->FindBin(pt))*
         PbPbBFeedDownCorrection->GetBinContent(PbPbBFeedDownCorrection->FindBin(pt));
	 
   sys+=fPbPbPtShape->Eval(pt)*fPbPbPtShape->Eval(pt);
  
   return sqrt(sys);

}

// =============================================================================================================
// RCP systematics
// =============================================================================================================
float normalizationUncertaintyForRCP(double centL=0,double centH=100)
{
   return 0;
}

float systematicsForRCP(double pt, double HLT=0,double centL=0,double centH=100)
{
   if (!initialized && centL==0&&centH==100) initializationPbPbCent0100();
   if (!initialized && centL==0&&centH==10) initializationPbPbCent010();
   return 0.2;

}


// =============================================================================================================
// cross-section systematics for pp
// =============================================================================================================
float normalizationUncertaintyForPP()
{
   return sqrt((DKpiBRUncertainty*DKpiBRUncertainty)+(ppLumiUncertainty*ppLumiUncertainty));
}

float systematicsPP(double pt, double HLT=0)
{
   if (!initialized) initialization();
   double sys=0;
   sys+=(ppTrackingEfficiency*2)*(ppTrackingEfficiency*2);
   sys+=ppLumiUncertainty*ppLumiUncertainty;
   sys+= ppMesonSelection->GetBinContent(ppMesonSelection->FindBin(pt))* 
         ppMesonSelection->GetBinContent(ppMesonSelection->FindBin(pt));

   sys+= ppBFeedDownCorrection->GetBinContent(ppBFeedDownCorrection->FindBin(pt))* 
         ppBFeedDownCorrection->GetBinContent(ppBFeedDownCorrection->FindBin(pt));
   sys+=fPPPtShape->Eval(pt)*fPPPtShape->Eval(pt);
   sys+= ppSignalExtraction->GetBinContent(ppSignalExtraction->FindBin(pt))* 
         ppSignalExtraction->GetBinContent(ppSignalExtraction->FindBin(pt));
   
   return sqrt(sys);
}

// =============================================================================================================
// cross-section systematics for PbPb
// =============================================================================================================
float normalizationUncertaintyForPbPb(double centL=0,double centH=100)
{
   double sys = ((DKpiBRUncertainty*DKpiBRUncertainty)+(PbPbNMBUncertainty*PbPbNMBUncertainty));
   if (centL==0&&centH==10) {
      // 0-10%
      sys+=TAAUncertainty0to10*TAAUncertainty0to10;
   } else {
      // 0-100%
      sys+=TAAUncertainty0to100*TAAUncertainty0to100;
   }   
   return sqrt(sys);
}


float systematicsPbPb(double pt, double centL=0,double centH=100, double HLT=0)
{
   if (!initialized && centL==0&&centH==100) initializationPbPbCent0100();
   if (!initialized && centL==0&&centH==10) initializationPbPbCent010();
   
   double sys=0;
   
   // pp tracking eff uncertainty used for the moment
   sys+=(ppTrackingEfficiency*2)*(ppTrackingEfficiency*2);
   if (pt<20) sys+=PbPbNMBUncertainty*PbPbNMBUncertainty;
   	else  sys+=PbPbLumiUncertainty*PbPbLumiUncertainty;
   
   sys+=TAAUncertainty0to100*TAAUncertainty0to100;
   sys+= PbPbMesonSelection->GetBinContent(PbPbMesonSelection->FindBin(pt))* 
         PbPbMesonSelection->GetBinContent(PbPbMesonSelection->FindBin(pt));

   sys+= PbPbBFeedDownCorrection->GetBinContent(PbPbBFeedDownCorrection->FindBin(pt))* 
         PbPbBFeedDownCorrection->GetBinContent(PbPbBFeedDownCorrection->FindBin(pt));
   sys+=fPbPbPtShape->Eval(pt)*fPbPbPtShape->Eval(pt);
   sys+= PbPbSignalExtraction->GetBinContent(PbPbSignalExtraction->FindBin(pt))* 
         PbPbSignalExtraction->GetBinContent(PbPbSignalExtraction->FindBin(pt));
    
   return sqrt(sys);

}


// =============================================================================================================
// Drawer
// =============================================================================================================
void drawSys(double x1,double y1, double x2,double y2, int color = 1)
{
   TLine *l1 = new TLine(x1,y1/100.,x2,y2/100.);
   TLine *l2 = new TLine(x1,-y1/100.,x2,-y2/100.);
   l1->SetLineWidth(2);
   l2->SetLineWidth(2);
   l1->SetLineColor(color);
   l2->SetLineColor(color);
   l1->Draw();
   l2->Draw();
 
}

// =============================================================================================================
// Plot systematics for RAA
// =============================================================================================================
void plotSystematicsRAA(double centL=0,double centH=100)
{
   TH1D *htmp = new TH1D("htmp","",10000,1,101);
   htmp->SetAxisRange(-0.5,0.5,"Y");
   htmp->SetXTitle("D meson p_{T} (GeV/c)");
   htmp->SetYTitle("Systematical Uncertainty");
   TCanvas *c = new TCanvas("c","",600,600);
   c->SetLogx();
   htmp->Draw();

   drawSys(1,0, 1,normalizationUncertaintyForRAA(centL,centH),2);
   drawSys(1,normalizationUncertaintyForRAA(centL,centH), 1.5,normalizationUncertaintyForRAA(centL,centH),2);
   drawSys(1.5,0, 1.5,normalizationUncertaintyForRAA(centL,centH),2);


   drawSys(2,0, 2,systematicsForRAA(2,centL,centH,0,0),1);


   for (double i=2;i<100;i+=0.1)
   {      
      drawSys(i,systematicsForRAA(i,centL,centH,0,0), i+0.1,systematicsForRAA(i+0.1,centL,centH,0,0),1);
//      drawSys(i,systematicsForRAA(i,0,1), i+0.1,systematicsForRAA(i+0.1,0,1),2);
      drawSys(i,sqrt((systematicsForRAA(i,centL,centH,0,2)*systematicsForRAA(i,centL,centH,0,2))-(systematicsForRAA(i,centL,centH,0,1)*systematicsForRAA(i,centL,centH,0,1))),
              i+0.1,sqrt((systematicsForRAA(i+0.1,centL,centH,0,2)*systematicsForRAA(i+0.1,centL,centH,0,2))-(systematicsForRAA(i+0.1,centL,centH,0,1)*systematicsForRAA(i+0.1,centL,centH,0,1))),4);
      drawSys(i,sqrt((systematicsForRAA(i,centL,centH,0,0)*systematicsForRAA(i,centL,centH,0,0))-(systematicsForRAA(i,centL,centH,0,2)*systematicsForRAA(i,centL,centH,0,2))),
              i+0.1,sqrt((systematicsForRAA(i+0.1,centL,centH,0,0)*systematicsForRAA(i+0.1,centL,centH,0,0))-(systematicsForRAA(i+0.1,centL,centH,0,2)*systematicsForRAA(i+0.1,centL,centH,0,2))),kGreen+2);
   }

   TH1D *h1 = new TH1D("h1","",100,0,1);
   h1->SetLineWidth(2); h1->SetLineColor(1);
   TH1D *h2 = new TH1D("h2","",100,0,1);
   h2->SetLineWidth(2); h2->SetLineColor(2);
   TH1D *h4 = new TH1D("h4","",100,0,1);
   h4->SetLineWidth(2); h4->SetLineColor(4);
   TH1D *h5 = new TH1D("h5","",100,0,1);
   h5->SetLineWidth(2); h5->SetLineColor(kGreen+2);
 
   TLegend *leg = new TLegend(0.2,0.7,0.9,0.9);
   leg->SetBorderSize(0);
   leg->SetFillStyle(0);
   leg->AddEntry(h2,"Overall Normalization (N_{MB}, Lumi)","l");
   leg->AddEntry(h1,"Total Systematics","l");
   leg->AddEntry(h4,"Signal Extraction","l");
   leg->AddEntry(h5,"D Meson Selection and Correction","l");
   leg->Draw();

}
