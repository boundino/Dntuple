INPUTFILE="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0_noweight.root";
OUTPUTFILE="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0_pthatweight.root";

cp "$INPUTFILE" "$OUTPUTFILE"
g++ weighPthat.C $(root-config --cflags --libs) -g -o weighPthat.exe 
./weighPthat.exe "$INPUTFILE" "$OUTPUTFILE"
rm weighPthat.exe