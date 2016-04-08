#include <TColor.h>
#include <TBox.h>
#include <TH1D.h>

void RAA_0_10()
{
//=========Macro generated from canvas: RAA/RAA
//=========  (Thu Apr  7 17:28:40 2016) by ROOT version6.02/10
/*
   TCanvas *RAA = new TCanvas("RAA", "RAA",1,1,800,676);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   RAA->Range(-0.6654505,-0.2175,2.738206,1.595);
   RAA->SetFillColor(0);
   RAA->SetBorderMode(0);
   RAA->SetBorderSize(2);
   RAA->SetLogx();
   RAA->SetLeftMargin(0.15);
   RAA->SetRightMargin(0.04);
   RAA->SetTopMargin(0.08);
   RAA->SetBottomMargin(0.12);
   RAA->SetFrameFillStyle(0);
   RAA->SetFrameBorderMode(0);
   RAA->SetFrameFillStyle(0);
   RAA->SetFrameBorderMode(0);
   double xAxis94[38] = {0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 3.2, 4, 4.8, 5.6, 6.4, 7.2, 9.6, 12, 14.4, 19.2, 24, 28.8, 35.2, 41.6, 48, 60.8, 73.6, 86.4, 103.6, 120.8, 140, 165, 250, 400}; 
   
   TH1D *RAA_0_1094 = new TH1D("RAA_0_1094","",37, xAxis94);
   RAA_0_1094->SetBinContent(1,0.3244271);
   RAA_0_1094->SetBinContent(2,0.3148055);
   RAA_0_1094->SetBinContent(3,0.3144976);
   RAA_0_1094->SetBinContent(4,0.3289466);
   RAA_0_1094->SetBinContent(5,0.3537006);
   RAA_0_1094->SetBinContent(6,0.3670599);
   RAA_0_1094->SetBinContent(7,0.3797748);
   RAA_0_1094->SetBinContent(8,0.4000161);
   RAA_0_1094->SetBinContent(9,0.4172594);
   RAA_0_1094->SetBinContent(10,0.4250056);
   RAA_0_1094->SetBinContent(11,0.4297472);
   RAA_0_1094->SetBinContent(12,0.4373217);
   RAA_0_1094->SetBinContent(13,0.4313888);
   RAA_0_1094->SetBinContent(14,0.3940092);
   RAA_0_1094->SetBinContent(15,0.2980582);
   RAA_0_1094->SetBinContent(16,0.2229788);
   RAA_0_1094->SetBinContent(17,0.1705043);
   RAA_0_1094->SetBinContent(18,0.1551819);
   RAA_0_1094->SetBinContent(19,0.1465649);
   RAA_0_1094->SetBinContent(20,0.1516244);
   RAA_0_1094->SetBinContent(21,0.1879752);
   RAA_0_1094->SetBinContent(22,0.2042679);
   RAA_0_1094->SetBinContent(23,0.2531147);
   RAA_0_1094->SetBinContent(24,0.3140448);
   RAA_0_1094->SetBinContent(25,0.3577063);
   RAA_0_1094->SetBinContent(26,0.3980585);
   RAA_0_1094->SetBinContent(27,0.4054254);
   RAA_0_1094->SetBinContent(28,0.4881175);
   RAA_0_1094->SetBinContent(29,0.5095169);
   RAA_0_1094->SetBinContent(30,0.5562411);
   RAA_0_1094->SetBinContent(31,0.6224983);
   RAA_0_1094->SetBinContent(32,0.6811626);
   RAA_0_1094->SetBinContent(33,0.7155866);
   RAA_0_1094->SetBinContent(34,0.6816249);
   RAA_0_1094->SetBinContent(35,0.8450076);
   RAA_0_1094->SetBinContent(36,0.7695107);
   RAA_0_1094->SetBinContent(37,0.7173151);
   RAA_0_1094->SetBinError(1,0.0001227495);
   RAA_0_1094->SetBinError(2,6.539672e-05);
   RAA_0_1094->SetBinError(3,5.449352e-05);
   RAA_0_1094->SetBinError(4,5.978007e-05);
   RAA_0_1094->SetBinError(5,6.703027e-05);
   RAA_0_1094->SetBinError(6,7.363119e-05);
   RAA_0_1094->SetBinError(7,8.422524e-05);
   RAA_0_1094->SetBinError(8,7.244376e-05);
   RAA_0_1094->SetBinError(9,9.232254e-05);
   RAA_0_1094->SetBinError(10,0.0001131607);
   RAA_0_1094->SetBinError(11,0.0001384033);
   RAA_0_1094->SetBinError(12,0.0001684061);
   RAA_0_1094->SetBinError(13,0.0001979983);
   RAA_0_1094->SetBinError(14,0.0001325519);
   RAA_0_1094->SetBinError(15,0.0001860168);
   RAA_0_1094->SetBinError(16,0.0002412968);
   RAA_0_1094->SetBinError(17,0.0002965542);
   RAA_0_1094->SetBinError(18,0.0004010293);
   RAA_0_1094->SetBinError(19,0.000526414);
   RAA_0_1094->SetBinError(20,0.0005078709);
   RAA_0_1094->SetBinError(21,0.001169279);
   RAA_0_1094->SetBinError(22,0.002035421);
   RAA_0_1094->SetBinError(23,0.003030837);
   RAA_0_1094->SetBinError(24,0.00678866);
   RAA_0_1094->SetBinError(25,0.01161578);
   RAA_0_1094->SetBinError(26,0.01570298);
   RAA_0_1094->SetBinError(27,0.0198609);
   RAA_0_1094->SetBinError(28,0.02603206);
   RAA_0_1094->SetBinError(29,0.01722378);
   RAA_0_1094->SetBinError(30,0.02144536);
   RAA_0_1094->SetBinError(31,0.01649351);
   RAA_0_1094->SetBinError(32,0.01967085);
   RAA_0_1094->SetBinError(33,0.03039177);
   RAA_0_1094->SetBinError(34,0.04337595);
   RAA_0_1094->SetBinError(35,0.06896032);
   RAA_0_1094->SetBinError(36,0.0793627);
   RAA_0_1094->SetBinError(37,0.2846007);
   RAA_0_1094->SetMinimum(0);
   RAA_0_1094->SetMaximum(1.45);
   RAA_0_1094->SetEntries(2159.215);
   RAA_0_1094->SetDirectory(0);
   RAA_0_1094->SetLineWidth(2);
   RAA_0_1094->SetMarkerStyle(20);
   RAA_0_1094->SetMarkerSize(0.8);
   RAA_0_1094->GetXaxis()->SetTitle("p_{T} (GeV)");
   RAA_0_1094->GetXaxis()->SetRange(3,37);
   RAA_0_1094->GetXaxis()->CenterTitle(true);
   RAA_0_1094->GetXaxis()->SetLabelFont(42);
   RAA_0_1094->GetXaxis()->SetLabelOffset(-0.005);
   RAA_0_1094->GetXaxis()->SetLabelSize(0.05);
   RAA_0_1094->GetXaxis()->SetTitleSize(0.05);
   RAA_0_1094->GetXaxis()->SetTitleFont(42);
   RAA_0_1094->GetYaxis()->SetTitle("R_{AA}");
   RAA_0_1094->GetYaxis()->CenterTitle(true);
   RAA_0_1094->GetYaxis()->SetLabelFont(42);
   RAA_0_1094->GetYaxis()->SetLabelSize(0.05);
   RAA_0_1094->GetYaxis()->SetTitleSize(0.05);
   RAA_0_1094->GetYaxis()->SetTitleOffset(1.4);
   RAA_0_1094->GetYaxis()->SetTitleFont(42);
   RAA_0_1094->GetZaxis()->SetLabelFont(42);
   RAA_0_1094->GetZaxis()->SetLabelSize(0.05);
   RAA_0_1094->GetZaxis()->SetTitleSize(0.05);
   RAA_0_1094->GetZaxis()->SetTitleFont(42);
   RAA_0_1094->Draw("");
*/

   TBox *box = new TBox(0.9,0.9468587,1.5,1.053141);
   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   /*
   ci = TColor::GetColor("#cccccc");
   box->SetFillColor(ci);
   box->SetLineWidth(0);
   box->Draw();
   TLine *line = new TLine(0.7,1,400,1);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();

   TLatex*   tex = new TLatex(0.9,0.1,"0-10%");
   tex->SetLineWidth(2);
   tex->Draw();
   tex = new TLatex(1.8,1.03,"T_{AA} and lumi. uncertainty");
   tex->SetTextFont(42);
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();
   tex = new TLatex(1.8,0.93,"|#eta|<1");
   tex->SetTextFont(42);
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();
   */
   /*
   box = new TBox(0.7,0.2840527,0.8,0.3449424);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(0.8,0.2963213,0.9,0.3615719);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();
   */
   box = new TBox(0.9,0.3186202,1,0.3887811);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(1,0.3306545,1.1,0.4034653);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(1.1,0.3421083,1.2,0.4174413);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(1.2,0.3562451,1.4,0.4437872);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(1.4,0.3716015,1.6,0.4629173);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(1.6,0.3719727,1.8,0.4780385);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(1.8,0.3761227,2,0.4833717);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(2,0.3758849,2.2,0.4987585);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(2.2,0.3707855,2.4,0.4919921);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(2.4,0.3326337,3.2,0.4553847);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(3.2,0.2484958,4,0.3476207);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(4,0.1879222,4.8,0.2580353);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(4.8,0.1476529,5.6,0.1933556);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(5.6,0.136537,6.4,0.1738267);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(6.4,0.1311518,7.2,0.1619781);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(7.2,0.1369491,9.6,0.1662997);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(9.6,0.1697855,12,0.206165);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(12,0.1845033,14.4,0.2240326);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(14.4,0.2286417,19.2,0.2775877);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(19.2,0.2837113,24,0.3443784);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(24,0.3231786,28.8,0.3922339);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(28.8,0.3596479,35.2,0.4364691);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(35.2,0.366286,41.6,0.4445649);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(41.6,0.4409582,48,0.5352767);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(48,0.4602379,60.8,0.5587959);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(60.8,0.5024016,73.6,0.6100805);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(73.6,0.5622127,86.4,0.6827839);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(86.4,0.6151866,103.6,0.7471385);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();
   /*
   box = new TBox(103.6,0.6462731,120.8,0.7849001);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(120.8,0.6156005,140,0.7476492);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(140,0.7631575,165,0.9268578);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(165,0.6949735,250,0.844048);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(250,0.6478337,400,0.7867966);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   double xAxis95[38] = {0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 3.2, 4, 4.8, 5.6, 6.4, 7.2, 9.6, 12, 14.4, 19.2, 24, 28.8, 35.2, 41.6, 48, 60.8, 73.6, 86.4, 103.6, 120.8, 140, 165, 250, 400}; 
   
   TH1D *RAA_0_1095 = new TH1D("RAA_0_1095","",37, xAxis95);
   RAA_0_1095->SetBinContent(1,0.3244271);
   RAA_0_1095->SetBinContent(2,0.3148055);
   RAA_0_1095->SetBinContent(3,0.3144976);
   RAA_0_1095->SetBinContent(4,0.3289466);
   RAA_0_1095->SetBinContent(5,0.3537006);
   RAA_0_1095->SetBinContent(6,0.3670599);
   RAA_0_1095->SetBinContent(7,0.3797748);
   RAA_0_1095->SetBinContent(8,0.4000161);
   RAA_0_1095->SetBinContent(9,0.4172594);
   RAA_0_1095->SetBinContent(10,0.4250056);
   RAA_0_1095->SetBinContent(11,0.4297472);
   RAA_0_1095->SetBinContent(12,0.4373217);
   RAA_0_1095->SetBinContent(13,0.4313888);
   RAA_0_1095->SetBinContent(14,0.3940092);
   RAA_0_1095->SetBinContent(15,0.2980582);
   RAA_0_1095->SetBinContent(16,0.2229788);
   RAA_0_1095->SetBinContent(17,0.1705043);
   RAA_0_1095->SetBinContent(18,0.1551819);
   RAA_0_1095->SetBinContent(19,0.1465649);
   RAA_0_1095->SetBinContent(20,0.1516244);
   RAA_0_1095->SetBinContent(21,0.1879752);
   RAA_0_1095->SetBinContent(22,0.2042679);
   RAA_0_1095->SetBinContent(23,0.2531147);
   RAA_0_1095->SetBinContent(24,0.3140448);
   RAA_0_1095->SetBinContent(25,0.3577063);
   RAA_0_1095->SetBinContent(26,0.3980585);
   RAA_0_1095->SetBinContent(27,0.4054254);
   RAA_0_1095->SetBinContent(28,0.4881175);
   RAA_0_1095->SetBinContent(29,0.5095169);
   RAA_0_1095->SetBinContent(30,0.5562411);
   RAA_0_1095->SetBinContent(31,0.6224983);
   RAA_0_1095->SetBinContent(32,0.6811626);
   RAA_0_1095->SetBinContent(33,0.7155866);
   RAA_0_1095->SetBinContent(34,0.6816249);
   RAA_0_1095->SetBinContent(35,0.8450076);
   RAA_0_1095->SetBinContent(36,0.7695107);
   RAA_0_1095->SetBinContent(37,0.7173151);
   RAA_0_1095->SetBinError(1,0.0001227495);
   RAA_0_1095->SetBinError(2,6.539672e-05);
   RAA_0_1095->SetBinError(3,5.449352e-05);
   RAA_0_1095->SetBinError(4,5.978007e-05);
   RAA_0_1095->SetBinError(5,6.703027e-05);
   RAA_0_1095->SetBinError(6,7.363119e-05);
   RAA_0_1095->SetBinError(7,8.422524e-05);
   RAA_0_1095->SetBinError(8,7.244376e-05);
   RAA_0_1095->SetBinError(9,9.232254e-05);
   RAA_0_1095->SetBinError(10,0.0001131607);
   RAA_0_1095->SetBinError(11,0.0001384033);
   RAA_0_1095->SetBinError(12,0.0001684061);
   RAA_0_1095->SetBinError(13,0.0001979983);
   RAA_0_1095->SetBinError(14,0.0001325519);
   RAA_0_1095->SetBinError(15,0.0001860168);
   RAA_0_1095->SetBinError(16,0.0002412968);
   RAA_0_1095->SetBinError(17,0.0002965542);
   RAA_0_1095->SetBinError(18,0.0004010293);
   RAA_0_1095->SetBinError(19,0.000526414);
   RAA_0_1095->SetBinError(20,0.0005078709);
   RAA_0_1095->SetBinError(21,0.001169279);
   RAA_0_1095->SetBinError(22,0.002035421);
   RAA_0_1095->SetBinError(23,0.003030837);
   RAA_0_1095->SetBinError(24,0.00678866);
   RAA_0_1095->SetBinError(25,0.01161578);
   RAA_0_1095->SetBinError(26,0.01570298);
   RAA_0_1095->SetBinError(27,0.0198609);
   RAA_0_1095->SetBinError(28,0.02603206);
   RAA_0_1095->SetBinError(29,0.01722378);
   RAA_0_1095->SetBinError(30,0.02144536);
   RAA_0_1095->SetBinError(31,0.01649351);
   RAA_0_1095->SetBinError(32,0.01967085);
   RAA_0_1095->SetBinError(33,0.03039177);
   RAA_0_1095->SetBinError(34,0.04337595);
   RAA_0_1095->SetBinError(35,0.06896032);
   RAA_0_1095->SetBinError(36,0.0793627);
   RAA_0_1095->SetBinError(37,0.2846007);
   RAA_0_1095->SetMinimum(0);
   RAA_0_1095->SetMaximum(1.45);
   RAA_0_1095->SetEntries(2159.215);
   RAA_0_1095->SetDirectory(0);
   RAA_0_1095->SetLineWidth(2);
   RAA_0_1095->SetMarkerStyle(20);
   RAA_0_1095->SetMarkerSize(0.8);
   RAA_0_1095->GetXaxis()->SetTitle("p_{T} (GeV)");
   RAA_0_1095->GetXaxis()->SetRange(3,37);
   RAA_0_1095->GetXaxis()->CenterTitle(true);
   RAA_0_1095->GetXaxis()->SetLabelFont(42);
   RAA_0_1095->GetXaxis()->SetLabelOffset(-0.005);
   RAA_0_1095->GetXaxis()->SetLabelSize(0.05);
   RAA_0_1095->GetXaxis()->SetTitleSize(0.05);
   RAA_0_1095->GetXaxis()->SetTitleFont(42);
   RAA_0_1095->GetYaxis()->SetTitle("R_{AA}");
   RAA_0_1095->GetYaxis()->CenterTitle(true);
   RAA_0_1095->GetYaxis()->SetLabelFont(42);
   RAA_0_1095->GetYaxis()->SetLabelSize(0.05);
   RAA_0_1095->GetYaxis()->SetTitleSize(0.05);
   RAA_0_1095->GetYaxis()->SetTitleOffset(1.4);
   RAA_0_1095->GetYaxis()->SetTitleFont(42);
   RAA_0_1095->GetZaxis()->SetLabelFont(42);
   RAA_0_1095->GetZaxis()->SetLabelSize(0.05);
   RAA_0_1095->GetZaxis()->SetTitleSize(0.05);
   RAA_0_1095->GetZaxis()->SetTitleFont(42);
   RAA_0_1095->Draw("same");
   tex = new TLatex(0.96,0.936,"25.8 pb^{-1} (5.02 TeV pp) + 404 #mub^{-1} (5.02 TeV PbPb)");
   tex->SetNDC();
   tex->SetTextAlign(31);
   tex->SetTextFont(42);
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();
   tex = new TLatex(0.18645,0.892,"CMS");
   tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextFont(61);
   tex->SetTextSize(0.06);
   tex->SetLineWidth(2);
   tex->Draw();
   tex = new TLatex(0.18645,0.82,"Preliminary");
   tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextFont(52);
   tex->SetTextSize(0.0456);
   tex->SetLineWidth(2);
   tex->Draw();
   */

   double xAxis96[38] = {0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 3.2, 4, 4.8, 5.6, 6.4, 7.2, 9.6, 12, 14.4, 19.2, 24, 28.8, 35.2, 41.6, 48, 60.8, 73.6, 86.4, 103.6, 120.8, 140, 165, 250, 400}; 
   
   TH1D *RAA_0_10_copy96 = new TH1D("RAA_0_10_copy96","",37, xAxis96);
   RAA_0_10_copy96->SetBinContent(1,-1);
   RAA_0_10_copy96->SetBinContent(2,-1);
   RAA_0_10_copy96->SetBinContent(3,-1);
   RAA_0_10_copy96->SetBinContent(4,-1);
   /*
   RAA_0_10_copy96->SetBinContent(1,0.3244271);
   RAA_0_10_copy96->SetBinContent(2,0.3148055);
   RAA_0_10_copy96->SetBinContent(3,0.3144976);
   RAA_0_10_copy96->SetBinContent(4,0.3289466);
   */
   RAA_0_10_copy96->SetBinContent(5,0.3537006);
   RAA_0_10_copy96->SetBinContent(6,0.3670599);
   RAA_0_10_copy96->SetBinContent(7,0.3797748);
   RAA_0_10_copy96->SetBinContent(8,0.4000161);
   RAA_0_10_copy96->SetBinContent(9,0.4172594);
   RAA_0_10_copy96->SetBinContent(10,0.4250056);
   RAA_0_10_copy96->SetBinContent(11,0.4297472);
   RAA_0_10_copy96->SetBinContent(12,0.4373217);
   RAA_0_10_copy96->SetBinContent(13,0.4313888);
   RAA_0_10_copy96->SetBinContent(14,0.3940092);
   RAA_0_10_copy96->SetBinContent(15,0.2980582);
   RAA_0_10_copy96->SetBinContent(16,0.2229788);
   RAA_0_10_copy96->SetBinContent(17,0.1705043);
   RAA_0_10_copy96->SetBinContent(18,0.1551819);
   RAA_0_10_copy96->SetBinContent(19,0.1465649);
   RAA_0_10_copy96->SetBinContent(20,0.1516244);
   RAA_0_10_copy96->SetBinContent(21,0.1879752);
   RAA_0_10_copy96->SetBinContent(22,0.2042679);
   RAA_0_10_copy96->SetBinContent(23,0.2531147);
   RAA_0_10_copy96->SetBinContent(24,0.3140448);
   RAA_0_10_copy96->SetBinContent(25,0.3577063);
   RAA_0_10_copy96->SetBinContent(26,0.3980585);
   RAA_0_10_copy96->SetBinContent(27,0.4054254);
   RAA_0_10_copy96->SetBinContent(28,0.4881175);
   RAA_0_10_copy96->SetBinContent(29,0.5095169);
   RAA_0_10_copy96->SetBinContent(30,0.5562411);
   RAA_0_10_copy96->SetBinContent(31,0.6224983);
   RAA_0_10_copy96->SetBinContent(32,0.6811626);
   /*
   RAA_0_10_copy96->SetBinContent(33,0.7155866);
   RAA_0_10_copy96->SetBinContent(34,0.6816249);
   RAA_0_10_copy96->SetBinContent(35,0.8450076);
   RAA_0_10_copy96->SetBinContent(36,0.7695107);
   RAA_0_10_copy96->SetBinContent(37,0.7173151);
   */
   RAA_0_10_copy96->SetBinContent(33,-1);
   RAA_0_10_copy96->SetBinContent(34,-1);
   RAA_0_10_copy96->SetBinContent(35,-1);
   RAA_0_10_copy96->SetBinContent(36,-1);
   RAA_0_10_copy96->SetBinContent(37,-1);

   RAA_0_10_copy96->SetBinError(1,0.0001227495);
   RAA_0_10_copy96->SetBinError(2,6.539672e-05);
   RAA_0_10_copy96->SetBinError(3,5.449352e-05);
   RAA_0_10_copy96->SetBinError(4,5.978007e-05);
   RAA_0_10_copy96->SetBinError(5,6.703027e-05);
   RAA_0_10_copy96->SetBinError(6,7.363119e-05);
   RAA_0_10_copy96->SetBinError(7,8.422524e-05);
   RAA_0_10_copy96->SetBinError(8,7.244376e-05);
   RAA_0_10_copy96->SetBinError(9,9.232254e-05);
   RAA_0_10_copy96->SetBinError(10,0.0001131607);
   RAA_0_10_copy96->SetBinError(11,0.0001384033);
   RAA_0_10_copy96->SetBinError(12,0.0001684061);
   RAA_0_10_copy96->SetBinError(13,0.0001979983);
   RAA_0_10_copy96->SetBinError(14,0.0001325519);
   RAA_0_10_copy96->SetBinError(15,0.0001860168);
   RAA_0_10_copy96->SetBinError(16,0.0002412968);
   RAA_0_10_copy96->SetBinError(17,0.0002965542);
   RAA_0_10_copy96->SetBinError(18,0.0004010293);
   RAA_0_10_copy96->SetBinError(19,0.000526414);
   RAA_0_10_copy96->SetBinError(20,0.0005078709);
   RAA_0_10_copy96->SetBinError(21,0.001169279);
   RAA_0_10_copy96->SetBinError(22,0.002035421);
   RAA_0_10_copy96->SetBinError(23,0.003030837);
   RAA_0_10_copy96->SetBinError(24,0.00678866);
   RAA_0_10_copy96->SetBinError(25,0.01161578);
   RAA_0_10_copy96->SetBinError(26,0.01570298);
   RAA_0_10_copy96->SetBinError(27,0.0198609);
   RAA_0_10_copy96->SetBinError(28,0.02603206);
   RAA_0_10_copy96->SetBinError(29,0.01722378);
   RAA_0_10_copy96->SetBinError(30,0.02144536);
   RAA_0_10_copy96->SetBinError(31,0.01649351);
   RAA_0_10_copy96->SetBinError(32,0.01967085);
   RAA_0_10_copy96->SetBinError(33,0.03039177);
   RAA_0_10_copy96->SetBinError(34,0.04337595);
   RAA_0_10_copy96->SetBinError(35,0.06896032);
   RAA_0_10_copy96->SetBinError(36,0.0793627);
   RAA_0_10_copy96->SetBinError(37,0.2846007);
   /*
   RAA_0_10_copy96->SetMinimum(0);
   RAA_0_10_copy96->SetMaximum(1.45);
   RAA_0_10_copy96->SetEntries(2159.215);
   RAA_0_10_copy96->SetDirectory(0);
   RAA_0_10_copy96->SetLineWidth(2);
   RAA_0_10_copy96->SetMarkerStyle(20);
   RAA_0_10_copy96->SetMarkerSize(0.8);
   RAA_0_10_copy96->GetXaxis()->SetTitle("p_{T} (GeV)");
   RAA_0_10_copy96->GetXaxis()->SetRange(3,37);
   RAA_0_10_copy96->GetXaxis()->CenterTitle(true);
   RAA_0_10_copy96->GetXaxis()->SetLabelFont(42);
   RAA_0_10_copy96->GetXaxis()->SetLabelOffset(-0.005);
   RAA_0_10_copy96->GetXaxis()->SetLabelSize(0.05);
   RAA_0_10_copy96->GetXaxis()->SetTitleSize(0.05);
   RAA_0_10_copy96->GetXaxis()->SetTitleFont(42);
   RAA_0_10_copy96->GetYaxis()->SetTitle("R_{AA}");
   RAA_0_10_copy96->GetYaxis()->CenterTitle(true);
   RAA_0_10_copy96->GetYaxis()->SetLabelFont(42);
   RAA_0_10_copy96->GetYaxis()->SetLabelSize(0.05);
   RAA_0_10_copy96->GetYaxis()->SetTitleSize(0.05);
   RAA_0_10_copy96->GetYaxis()->SetTitleOffset(1.4);
   RAA_0_10_copy96->GetYaxis()->SetTitleFont(42);
   RAA_0_10_copy96->GetZaxis()->SetLabelFont(42);
   RAA_0_10_copy96->GetZaxis()->SetLabelSize(0.05);
   RAA_0_10_copy96->GetZaxis()->SetTitleSize(0.05);
   RAA_0_10_copy96->GetZaxis()->SetTitleFont(42);
   */
   RAA_0_10_copy96->SetLineWidth(2);
   RAA_0_10_copy96->SetLineColor(kRed);
   RAA_0_10_copy96->SetMarkerStyle(20);
   RAA_0_10_copy96->SetMarkerSize(0.8);
   RAA_0_10_copy96->SetMarkerColor(kRed);
   RAA_0_10_copy96->Draw("same");
   /*
   RAA->Modified();
   RAA->cd();
   RAA->SetSelected(RAA);
   */
}
