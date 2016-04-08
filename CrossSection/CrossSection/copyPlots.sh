MYPWD=${PWD}

rm -rf analysisNote
svn co -N svn+ssh://svn.cern.ch/reps/tdr2 analysisNote
cd analysisNote
svn update utils
svn update -N notes
svn update notes/AN-15-308
eval `./notes/tdr runtime -sh`
cd notes/AN-15-308/trunk

cp "$MYPWD"/Fits/DMass*.pdf Plots/Fits/.
cp "$MYPWD"/canvasEff_studyPP.pdf Plots/Efficiency/.
cp "$MYPWD"/canvasEff_studyNPPP.pdf Plots/Efficiency/.
cp "$MYPWD"/canvasEff_studyPPMB.pdf Plots/Efficiency/.
cp "$MYPWD"/canvasEff_studyPbPb.pdf Plots/Efficiency/.
cp "$MYPWD"/canvasEff_studyPbPbMB.pdf Plots/Efficiency/.

cp "$MYPWD"/canvas_pp_Btod0meson_5TeV_y1_PPMB.pdf Plots/FONLL/.
cp "$MYPWD"/canvas_pp_d0meson_5TeV_y1_PPMB.pdf Plots/FONLL/.
cp "$MYPWD"/canvas_pp_Btod0meson_5TeV_y1_PP.pdf Plots/FONLL/.
cp "$MYPWD"/canvas_pp_d0meson_5TeV_y1_PP.pdf Plots/FONLL/.
cp "$MYPWD"/canvasSigmaDzeroRatioPP.pdf Plots/Results/.
cp "$MYPWD"/canvasSigmaDzeroRatioPPMB.pdf Plots/Results/.
cp "$MYPWD"/CrossSectionComparison.pdf Plots/Results/.
cp "$MYPWD"/canvasRAAPbPbMB.pdf Plots/Results/.
cp "$MYPWD"/canvasRAAPbPb.pdf Plots/Results/.
cp "$MYPWD"/canvasRAAComparison.pdf Plots/Results/.

cp "$MYPWD"/canvasPtreweightedComparisonPP.pdf Plots/SystPtShape/.
cp "$MYPWD"/canvasPtreweightedComparisonPPMB.pdf Plots/SystPtShape/.
cp "$MYPWD"/canvasPtreweightedComparisonPbPb.pdf Plots/SystPtShape/.
cp "$MYPWD"/canvasPtreweightedComparisonPbPbMB.pdf Plots/SystPtShape/.
cp "$MYPWD"/canvasPtReweightPPptreweighted.pdf Plots/SystPtShape/.

cp "$MYPWD"/canvasTotAccEfficiencyPtHatWeight_isPbPb0.pdf Plots/Efficiency/.
cp "$MYPWD"/canvasTotAccEfficiencyPtHatWeight_isPbPb1.pdf Plots/Efficiency/.

cp "$MYPWD"/canvasClosurePP.pdf Plots/Efficiency/.
cp "$MYPWD"/canvasClosurePbPb.pdf Plots/Efficiency/.
cp "$MYPWD"/canvasClosurePPMB.pdf Plots/Efficiency/.
cp "$MYPWD"/canvasClosurePbPbMB.pdf Plots/Efficiency/.

canvasClosurePP.pdf

#tdr --style=an b AN-15-308 
svn add Plots/*/*
svn commit -m "update of plots" Plots
cd "$MYPWD"


