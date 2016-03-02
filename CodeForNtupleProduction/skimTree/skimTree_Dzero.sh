INPUTFILE="/data/wangj/MC2015/Dntuple/PbPb/ntD_PbPb_Dzero_kpi_prompt/ntD_EvtBase_20160229_Dfinder_20160215_PbPb_Pythia8_prompt_D0pt50p0_Pthat50_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_PU_20151212_dPt1tkPt1_D0Ds.root"
OUTPUTFILE="/data/wangj/MC2015/Dntuple/PbPb/ntD_PbPb_Dzero_kpi_prompt/ntD_EvtBase_20160229_Dfinder_20160215_PbPb_Pythia8_prompt_D0pt50p0_Pthat50_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_PU_20151212_dPt1tkPt1_D0Ds_skimbranches.root"

g++ skimTree_Dzero.C $(root-config --cflags --libs) -g -o skimTree_Dzero.exe 
./skimTree_Dzero.exe "$INPUTFILE" "$OUTPUTFILE"
rm skimTree_Dzero.exe
