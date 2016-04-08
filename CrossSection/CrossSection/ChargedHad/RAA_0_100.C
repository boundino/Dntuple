#include <TColor.h>
#include <TBox.h>
#include <TH1D.h>

void RAA_0_100()
{
//=========Macro generated from canvas: RAA/RAA
//=========  (Thu Apr  7 17:28:39 2016) by ROOT version6.02/10
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

   double xAxis61[38] = {0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 3.2, 4, 4.8, 5.6, 6.4, 7.2, 9.6, 12, 14.4, 19.2, 24, 28.8, 35.2, 41.6, 48, 60.8, 73.6, 86.4, 103.6, 120.8, 140, 165, 250, 400}; 
   
   TH1D *RAA_0_10061 = new TH1D("RAA_0_10061","",37, xAxis61);
   RAA_0_10061->SetBinContent(1,0.3357305);
   RAA_0_10061->SetBinContent(2,0.3457896);
   RAA_0_10061->SetBinContent(3,0.3604347);
   RAA_0_10061->SetBinContent(4,0.3761913);
   RAA_0_10061->SetBinContent(5,0.40539);
   RAA_0_10061->SetBinContent(6,0.4246648);
   RAA_0_10061->SetBinContent(7,0.4402166);
   RAA_0_10061->SetBinContent(8,0.4605355);
   RAA_0_10061->SetBinContent(9,0.4794503);
   RAA_0_10061->SetBinContent(10,0.492377);
   RAA_0_10061->SetBinContent(11,0.4986405);
   RAA_0_10061->SetBinContent(12,0.5007929);
   RAA_0_10061->SetBinContent(13,0.4938326);
   RAA_0_10061->SetBinContent(14,0.4598961);
   RAA_0_10061->SetBinContent(15,0.3719685);
   RAA_0_10061->SetBinContent(16,0.2969196);
   RAA_0_10061->SetBinContent(17,0.250061);
   RAA_0_10061->SetBinContent(18,0.2279972);
   RAA_0_10061->SetBinContent(19,0.2226817);
   RAA_0_10061->SetBinContent(20,0.2313449);
   RAA_0_10061->SetBinContent(21,0.2699394);
   RAA_0_10061->SetBinContent(22,0.2902458);
   RAA_0_10061->SetBinContent(23,0.3431948);
   RAA_0_10061->SetBinContent(24,0.4182);
   RAA_0_10061->SetBinContent(25,0.4503293);
   RAA_0_10061->SetBinContent(26,0.4944811);
   RAA_0_10061->SetBinContent(27,0.5185174);
   RAA_0_10061->SetBinContent(28,0.5633206);
   RAA_0_10061->SetBinContent(29,0.6211606);
   RAA_0_10061->SetBinContent(30,0.6571701);
   RAA_0_10061->SetBinContent(31,0.7123546);
   RAA_0_10061->SetBinContent(32,0.7498177);
   RAA_0_10061->SetBinContent(33,0.7696006);
   RAA_0_10061->SetBinContent(34,0.7838902);
   RAA_0_10061->SetBinContent(35,0.8553915);
   RAA_0_10061->SetBinContent(36,0.8737696);
   RAA_0_10061->SetBinContent(37,0.8442617);
   RAA_0_10061->SetBinError(1,6.270133e-05);
   RAA_0_10061->SetBinError(2,4.624946e-05);
   RAA_0_10061->SetBinError(3,5.123776e-05);
   RAA_0_10061->SetBinError(4,5.719036e-05);
   RAA_0_10061->SetBinError(5,6.709163e-05);
   RAA_0_10061->SetBinError(6,7.628768e-05);
   RAA_0_10061->SetBinError(7,8.771548e-05);
   RAA_0_10061->SetBinError(8,7.52401e-05);
   RAA_0_10061->SetBinError(9,9.607725e-05);
   RAA_0_10061->SetBinError(10,0.0001190045);
   RAA_0_10061->SetBinError(11,0.000145899);
   RAA_0_10061->SetBinError(12,0.0001748692);
   RAA_0_10061->SetBinError(13,0.0002051064);
   RAA_0_10061->SetBinError(14,0.000138721);
   RAA_0_10061->SetBinError(15,0.0002018347);
   RAA_0_10061->SetBinError(16,0.0002677426);
   RAA_0_10061->SetBinError(17,0.0003484304);
   RAA_0_10061->SetBinError(18,0.0004617924);
   RAA_0_10061->SetBinError(19,0.0006219679);
   RAA_0_10061->SetBinError(20,0.000608264);
   RAA_0_10061->SetBinError(21,0.001344485);
   RAA_0_10061->SetBinError(22,0.002368688);
   RAA_0_10061->SetBinError(23,0.0034273);
   RAA_0_10061->SetBinError(24,0.007668626);
   RAA_0_10061->SetBinError(25,0.01237787);
   RAA_0_10061->SetBinError(26,0.01627645);
   RAA_0_10061->SetBinError(27,0.02049748);
   RAA_0_10061->SetBinError(28,0.02258258);
   RAA_0_10061->SetBinError(29,0.01193305);
   RAA_0_10061->SetBinError(30,0.01156148);
   RAA_0_10061->SetBinError(31,0.0116744);
   RAA_0_10061->SetBinError(32,0.01356314);
   RAA_0_10061->SetBinError(33,0.02142726);
   RAA_0_10061->SetBinError(34,0.03181756);
   RAA_0_10061->SetBinError(35,0.04775425);
   RAA_0_10061->SetBinError(36,0.05873332);
   RAA_0_10061->SetBinError(37,0.2061978);
   RAA_0_10061->SetMinimum(0);
   RAA_0_10061->SetMaximum(1.45);
   RAA_0_10061->SetEntries(5723.499);
   RAA_0_10061->SetDirectory(0);
   RAA_0_10061->SetLineWidth(2);
   RAA_0_10061->SetMarkerStyle(20);
   RAA_0_10061->SetMarkerSize(0.8);
   RAA_0_10061->GetXaxis()->SetTitle("p_{T} (GeV)");
   RAA_0_10061->GetXaxis()->CenterTitle(true);
   RAA_0_10061->GetXaxis()->SetLabelFont(42);
   RAA_0_10061->GetXaxis()->SetLabelOffset(-0.005);
   RAA_0_10061->GetXaxis()->SetLabelSize(0.05);
   RAA_0_10061->GetXaxis()->SetTitleSize(0.05);
   RAA_0_10061->GetXaxis()->SetTitleFont(42);
   RAA_0_10061->GetYaxis()->SetTitle("R_{AA}");
   RAA_0_10061->GetYaxis()->CenterTitle(true);
   RAA_0_10061->GetYaxis()->SetLabelFont(42);
   RAA_0_10061->GetYaxis()->SetLabelSize(0.05);
   RAA_0_10061->GetYaxis()->SetTitleSize(0.05);
   RAA_0_10061->GetYaxis()->SetTitleOffset(1.4);
   RAA_0_10061->GetYaxis()->SetTitleFont(42);
   RAA_0_10061->GetZaxis()->SetLabelFont(42);
   RAA_0_10061->GetZaxis()->SetLabelSize(0.05);
   RAA_0_10061->GetZaxis()->SetTitleSize(0.05);
   RAA_0_10061->GetZaxis()->SetTitleFont(42);
   RAA_0_10061->GetXaxis()->SetRange(6.,33);
   RAA_0_10061->Draw("");
   */
   TBox *box = new TBox(0.9,0.9440983,1.5,1.055902);

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
   TLatex*   tex = new TLatex(0.9,0.1,"0-100%");
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
   box = new TBox(0.7,0.3255431,0.8,0.3953264);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(0.8,0.3388803,0.9,0.4135023);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();
   */
   box = new TBox(0.9,0.3651831,1,0.445597);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(1,0.3825461,1.1,0.4667834);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(1.1,0.3965556,1.2,0.4838777);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(1.2,0.4101423,1.4,0.5109286);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(1.4,0.4269874,1.6,0.5319132);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(1.6,0.4309375,1.8,0.5538164);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(1.8,0.4364195,2,0.5608616);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(2,0.4304395,2.2,0.5711463);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(2.2,0.424457,2.4,0.5632081);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(2.4,0.3882574,3.2,0.5315348);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(3.2,0.310116,4,0.433821);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(4,0.2502382,4.8,0.3436009);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(4.8,0.2165473,5.6,0.2835746);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(5.6,0.2006038,6.4,0.2553906);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(6.4,0.199264,7.2,0.2460994);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(7.2,0.2089539,9.6,0.2537359);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(9.6,0.2438186,12,0.2960602);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(12,0.2621625,14.4,0.3183291);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(14.4,0.3100127,19.2,0.3763768);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(19.2,0.3778059,24,0.4585941);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(24,0.4068577,28.8,0.4938008);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(28.8,0.4467566,35.2,0.5422056);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(35.2,0.4684437,41.6,0.568591);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(41.6,0.5088605,48,0.6177807);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(48,0.561051,60.8,0.6812702);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(60.8,0.5935109,73.6,0.7208293);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(73.6,0.6433226,86.4,0.7813866);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(86.4,0.6771475,103.6,0.8224879);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   /*
   box = new TBox(103.6,0.6950113,120.8,0.8441899);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(120.8,0.7079108,140,0.8598695);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(140,0.7724787,165,0.9383044);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(165,0.7890943,250,0.958445);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();

   box = new TBox(250,0.762439,400,0.9260844);
   ci = TColor::GetColor("#ffaaaa");
   box->SetFillColor(ci);
   box->Draw();
   */
   /*
   double xAxis62[38] = {0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 3.2, 4, 4.8, 5.6, 6.4, 7.2, 9.6, 12, 14.4, 19.2, 24, 28.8, 35.2, 41.6, 48, 60.8, 73.6, 86.4, 103.6, 120.8, 140, 165, 250, 400}; 
   
   TH1D *RAA_0_10062 = new TH1D("RAA_0_10062","",37, xAxis62);
   RAA_0_10062->SetBinContent(1,0.3357305);
   RAA_0_10062->SetBinContent(2,0.3457896);
   RAA_0_10062->SetBinContent(3,0.3604347);
   RAA_0_10062->SetBinContent(4,0.3761913);
   RAA_0_10062->SetBinContent(5,0.40539);
   RAA_0_10062->SetBinContent(6,0.4246648);
   RAA_0_10062->SetBinContent(7,0.4402166);
   RAA_0_10062->SetBinContent(8,0.4605355);
   RAA_0_10062->SetBinContent(9,0.4794503);
   RAA_0_10062->SetBinContent(10,0.492377);
   RAA_0_10062->SetBinContent(11,0.4986405);
   RAA_0_10062->SetBinContent(12,0.5007929);
   RAA_0_10062->SetBinContent(13,0.4938326);
   RAA_0_10062->SetBinContent(14,0.4598961);
   RAA_0_10062->SetBinContent(15,0.3719685);
   RAA_0_10062->SetBinContent(16,0.2969196);
   RAA_0_10062->SetBinContent(17,0.250061);
   RAA_0_10062->SetBinContent(18,0.2279972);
   RAA_0_10062->SetBinContent(19,0.2226817);
   RAA_0_10062->SetBinContent(20,0.2313449);
   RAA_0_10062->SetBinContent(21,0.2699394);
   RAA_0_10062->SetBinContent(22,0.2902458);
   RAA_0_10062->SetBinContent(23,0.3431948);
   RAA_0_10062->SetBinContent(24,0.4182);
   RAA_0_10062->SetBinContent(25,0.4503293);
   RAA_0_10062->SetBinContent(26,0.4944811);
   RAA_0_10062->SetBinContent(27,0.5185174);
   RAA_0_10062->SetBinContent(28,0.5633206);
   RAA_0_10062->SetBinContent(29,0.6211606);
   RAA_0_10062->SetBinContent(30,0.6571701);
   RAA_0_10062->SetBinContent(31,0.7123546);
   RAA_0_10062->SetBinContent(32,0.7498177);
   RAA_0_10062->SetBinContent(33,0.7696006);
   RAA_0_10062->SetBinContent(34,0.7838902);
   RAA_0_10062->SetBinContent(35,0.8553915);
   RAA_0_10062->SetBinContent(36,0.8737696);
   RAA_0_10062->SetBinContent(37,0.8442617);
   RAA_0_10062->SetBinError(1,6.270133e-05);
   RAA_0_10062->SetBinError(2,4.624946e-05);
   RAA_0_10062->SetBinError(3,5.123776e-05);
   RAA_0_10062->SetBinError(4,5.719036e-05);
   RAA_0_10062->SetBinError(5,6.709163e-05);
   RAA_0_10062->SetBinError(6,7.628768e-05);
   RAA_0_10062->SetBinError(7,8.771548e-05);
   RAA_0_10062->SetBinError(8,7.52401e-05);
   RAA_0_10062->SetBinError(9,9.607725e-05);
   RAA_0_10062->SetBinError(10,0.0001190045);
   RAA_0_10062->SetBinError(11,0.000145899);
   RAA_0_10062->SetBinError(12,0.0001748692);
   RAA_0_10062->SetBinError(13,0.0002051064);
   RAA_0_10062->SetBinError(14,0.000138721);
   RAA_0_10062->SetBinError(15,0.0002018347);
   RAA_0_10062->SetBinError(16,0.0002677426);
   RAA_0_10062->SetBinError(17,0.0003484304);
   RAA_0_10062->SetBinError(18,0.0004617924);
   RAA_0_10062->SetBinError(19,0.0006219679);
   RAA_0_10062->SetBinError(20,0.000608264);
   RAA_0_10062->SetBinError(21,0.001344485);
   RAA_0_10062->SetBinError(22,0.002368688);
   RAA_0_10062->SetBinError(23,0.0034273);
   RAA_0_10062->SetBinError(24,0.007668626);
   RAA_0_10062->SetBinError(25,0.01237787);
   RAA_0_10062->SetBinError(26,0.01627645);
   RAA_0_10062->SetBinError(27,0.02049748);
   RAA_0_10062->SetBinError(28,0.02258258);
   RAA_0_10062->SetBinError(29,0.01193305);
   RAA_0_10062->SetBinError(30,0.01156148);
   RAA_0_10062->SetBinError(31,0.0116744);
   RAA_0_10062->SetBinError(32,0.01356314);
   RAA_0_10062->SetBinError(33,0.02142726);
   RAA_0_10062->SetBinError(34,0.03181756);
   RAA_0_10062->SetBinError(35,0.04775425);
   RAA_0_10062->SetBinError(36,0.05873332);
   RAA_0_10062->SetBinError(37,0.2061978);

   RAA_0_10062->SetMinimum(0);
   RAA_0_10062->SetMaximum(1.45);
   RAA_0_10062->SetEntries(5723.499);
   RAA_0_10062->SetDirectory(0);
   RAA_0_10062->SetLineWidth(2);
   RAA_0_10062->SetMarkerStyle(20);
   RAA_0_10062->SetMarkerSize(0.8);
   RAA_0_10062->GetXaxis()->SetTitle("p_{T} (GeV)");
   RAA_0_10062->GetXaxis()->CenterTitle(true);
   RAA_0_10062->GetXaxis()->SetLabelFont(42);
   RAA_0_10062->GetXaxis()->SetLabelOffset(-0.005);
   RAA_0_10062->GetXaxis()->SetLabelSize(0.05);
   RAA_0_10062->GetXaxis()->SetTitleSize(0.05);
   RAA_0_10062->GetXaxis()->SetTitleFont(42);
   RAA_0_10062->GetYaxis()->SetTitle("R_{AA}");
   RAA_0_10062->GetYaxis()->CenterTitle(true);
   RAA_0_10062->GetYaxis()->SetLabelFont(42);
   RAA_0_10062->GetYaxis()->SetLabelSize(0.05);
   RAA_0_10062->GetYaxis()->SetTitleSize(0.05);
   RAA_0_10062->GetYaxis()->SetTitleOffset(1.4);
   RAA_0_10062->GetYaxis()->SetTitleFont(42);
   RAA_0_10062->GetZaxis()->SetLabelFont(42);
   RAA_0_10062->GetZaxis()->SetLabelSize(0.05);
   RAA_0_10062->GetZaxis()->SetTitleSize(0.05);
   RAA_0_10062->GetZaxis()->SetTitleFont(42);
   RAA_0_10062->GetXaxis()->SetRange(6,33);
   RAA_0_10062->Draw("same");
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

   double xAxis63[38] = {0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 3.2, 4, 4.8, 5.6, 6.4, 7.2, 9.6, 12, 14.4, 19.2, 24, 28.8, 35.2, 41.6, 48, 60.8, 73.6, 86.4, 103.6, 120.8, 140, 165, 250, 400}; 

   TH1D *RAA_0_100_copy63 = new TH1D("RAA_0_100_copy63","",37, xAxis63);
   RAA_0_100_copy63->SetBinContent(1,-1);
   RAA_0_100_copy63->SetBinContent(2,-1);
   RAA_0_100_copy63->SetBinContent(3,-1);
   RAA_0_100_copy63->SetBinContent(4,-1);
   /*
   RAA_0_100_copy63->SetBinContent(1,0.3357305);
   RAA_0_100_copy63->SetBinContent(2,0.3457896);
   RAA_0_100_copy63->SetBinContent(3,0.3604347);
   RAA_0_100_copy63->SetBinContent(4,0.3761913);
   */
   RAA_0_100_copy63->SetBinContent(5,0.40539);
   RAA_0_100_copy63->SetBinContent(6,0.4246648);
   RAA_0_100_copy63->SetBinContent(7,0.4402166);
   RAA_0_100_copy63->SetBinContent(8,0.4605355);
   RAA_0_100_copy63->SetBinContent(9,0.4794503);
   RAA_0_100_copy63->SetBinContent(10,0.492377);
   RAA_0_100_copy63->SetBinContent(11,0.4986405);
   RAA_0_100_copy63->SetBinContent(12,0.5007929);
   RAA_0_100_copy63->SetBinContent(13,0.4938326);
   RAA_0_100_copy63->SetBinContent(14,0.4598961);
   RAA_0_100_copy63->SetBinContent(15,0.3719685);
   RAA_0_100_copy63->SetBinContent(16,0.2969196);
   RAA_0_100_copy63->SetBinContent(17,0.250061);
   RAA_0_100_copy63->SetBinContent(18,0.2279972);
   RAA_0_100_copy63->SetBinContent(19,0.2226817);
   RAA_0_100_copy63->SetBinContent(20,0.2313449);
   RAA_0_100_copy63->SetBinContent(21,0.2699394);
   RAA_0_100_copy63->SetBinContent(22,0.2902458);
   RAA_0_100_copy63->SetBinContent(23,0.3431948);
   RAA_0_100_copy63->SetBinContent(24,0.4182);
   RAA_0_100_copy63->SetBinContent(25,0.4503293);
   RAA_0_100_copy63->SetBinContent(26,0.4944811);
   RAA_0_100_copy63->SetBinContent(27,0.5185174);
   RAA_0_100_copy63->SetBinContent(28,0.5633206);
   RAA_0_100_copy63->SetBinContent(29,0.6211606);
   RAA_0_100_copy63->SetBinContent(30,0.6571701);
   RAA_0_100_copy63->SetBinContent(31,0.7123546);
   RAA_0_100_copy63->SetBinContent(32,0.7498177);
   /*
   RAA_0_100_copy63->SetBinContent(33,0.7696006);
   RAA_0_100_copy63->SetBinContent(34,0.7838902);
   RAA_0_100_copy63->SetBinContent(35,0.8553915);
   RAA_0_100_copy63->SetBinContent(36,0.8737696);
   RAA_0_100_copy63->SetBinContent(37,0.8442617);
   */
   RAA_0_100_copy63->SetBinContent(33,-1);
   RAA_0_100_copy63->SetBinContent(34,-1);
   RAA_0_100_copy63->SetBinContent(35,-1);
   RAA_0_100_copy63->SetBinContent(36,-1);
   RAA_0_100_copy63->SetBinContent(37,-1);

   RAA_0_100_copy63->SetBinError(1,6.270133e-05);
   RAA_0_100_copy63->SetBinError(2,4.624946e-05);
   RAA_0_100_copy63->SetBinError(3,5.123776e-05);
   RAA_0_100_copy63->SetBinError(4,5.719036e-05);
   RAA_0_100_copy63->SetBinError(5,6.709163e-05);
   RAA_0_100_copy63->SetBinError(6,7.628768e-05);
   RAA_0_100_copy63->SetBinError(7,8.771548e-05);
   RAA_0_100_copy63->SetBinError(8,7.52401e-05);
   RAA_0_100_copy63->SetBinError(9,9.607725e-05);
   RAA_0_100_copy63->SetBinError(10,0.0001190045);
   RAA_0_100_copy63->SetBinError(11,0.000145899);
   RAA_0_100_copy63->SetBinError(12,0.0001748692);
   RAA_0_100_copy63->SetBinError(13,0.0002051064);
   RAA_0_100_copy63->SetBinError(14,0.000138721);
   RAA_0_100_copy63->SetBinError(15,0.0002018347);
   RAA_0_100_copy63->SetBinError(16,0.0002677426);
   RAA_0_100_copy63->SetBinError(17,0.0003484304);
   RAA_0_100_copy63->SetBinError(18,0.0004617924);
   RAA_0_100_copy63->SetBinError(19,0.0006219679);
   RAA_0_100_copy63->SetBinError(20,0.000608264);
   RAA_0_100_copy63->SetBinError(21,0.001344485);
   RAA_0_100_copy63->SetBinError(22,0.002368688);
   RAA_0_100_copy63->SetBinError(23,0.0034273);
   RAA_0_100_copy63->SetBinError(24,0.007668626);
   RAA_0_100_copy63->SetBinError(25,0.01237787);
   RAA_0_100_copy63->SetBinError(26,0.01627645);
   RAA_0_100_copy63->SetBinError(27,0.02049748);
   RAA_0_100_copy63->SetBinError(28,0.02258258);
   RAA_0_100_copy63->SetBinError(29,0.01193305);
   RAA_0_100_copy63->SetBinError(30,0.01156148);
   RAA_0_100_copy63->SetBinError(31,0.0116744);
   RAA_0_100_copy63->SetBinError(32,0.01356314);
   RAA_0_100_copy63->SetBinError(33,0.02142726);
   RAA_0_100_copy63->SetBinError(34,0.03181756);
   RAA_0_100_copy63->SetBinError(35,0.04775425);
   RAA_0_100_copy63->SetBinError(36,0.05873332);
   RAA_0_100_copy63->SetBinError(37,0.2061978);

   /*
   RAA_0_100_copy63->SetMinimum(0);
   RAA_0_100_copy63->SetMaximum(1.45);
   RAA_0_100_copy63->SetEntries(5723.499);
   RAA_0_100_copy63->SetDirectory(0);
   RAA_0_10_copy96->SetLineWidth(2);
   RAA_0_10_copy96->SetMarkerStyle(20);
   RAA_0_10_copy96->SetMarkerSize(0.8);
   RAA_0_100_copy63->GetXaxis()->SetTitle("p_{T} (GeV)");
   RAA_0_100_copy63->GetXaxis()->SetRange(6,33);
   RAA_0_100_copy63->GetXaxis()->CenterTitle(true);
   RAA_0_100_copy63->GetXaxis()->SetLabelFont(42);
   RAA_0_100_copy63->GetXaxis()->SetLabelOffset(-0.005);
   RAA_0_100_copy63->GetXaxis()->SetLabelSize(0.05);
   RAA_0_100_copy63->GetXaxis()->SetTitleSize(0.05);
   RAA_0_100_copy63->GetXaxis()->SetTitleFont(42);
   RAA_0_100_copy63->GetYaxis()->SetTitle("R_{AA}");
   RAA_0_100_copy63->GetYaxis()->CenterTitle(true);
   RAA_0_100_copy63->GetYaxis()->SetLabelFont(42);
   RAA_0_100_copy63->GetYaxis()->SetLabelSize(0.05);
   RAA_0_100_copy63->GetYaxis()->SetTitleSize(0.05);
   RAA_0_100_copy63->GetYaxis()->SetTitleOffset(1.4);
   RAA_0_100_copy63->GetYaxis()->SetTitleFont(42);
   RAA_0_100_copy63->GetZaxis()->SetLabelFont(42);
   RAA_0_100_copy63->GetZaxis()->SetLabelSize(0.05);
   RAA_0_100_copy63->GetZaxis()->SetTitleSize(0.05);
   RAA_0_100_copy63->GetZaxis()->SetTitleFont(42);
   */
   RAA_0_100_copy63->SetLineWidth(2);
   RAA_0_100_copy63->SetLineColor(kRed);
   RAA_0_100_copy63->SetMarkerStyle(20);
   RAA_0_100_copy63->SetMarkerSize(0.8);
   RAA_0_100_copy63->SetMarkerColor(kRed);
   RAA_0_100_copy63->Draw("same");
   /*
   RAA->Modified();
   RAA->cd();
   RAA->SetSelected(RAA);
   */
}
