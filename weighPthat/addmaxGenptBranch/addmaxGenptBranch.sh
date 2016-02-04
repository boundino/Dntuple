#!/bin/bash 

###
INPUTFILE=(
    "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0pt0p0_Pthat0_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20151212_dPt1tkPt1_D0Ds.root" 
    "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0pt5p0_Pthat5_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20151212_dPt1tkPt1_D0Ds.root" 
    "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0pt10p0_Pthat10_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20151212_dPt1tkPt1_D0Ds.root" 
    "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0pt15p0_Pthat15_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20151212_dPt1tkPt1_D0Ds.root" 
    "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0pt30p0_Pthat30_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20151212_dPt1tkPt1_D0Ds.root" 
    "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0pt50p0_Pthat50_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20151212_dPt1tkPt1_D0Ds.root")
OUTPUTDIRECTORY="/data/wangj/debug/weighPthat/addmaxGenptBranch/Dzero"
OUTPUTFILE="ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0_addmaxgenpt"
sed '1iint genSignal[2]={1,2};' addmaxGenptBranch.C > addmaxGenptBranch_tmp.C

#INPUTFILE=(
#"/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_Dstarpt5p0_Pthat5_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root"
#"/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_Dstarpt10p0_Pthat10_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root"
#"/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_Dstarpt15p0_Pthat15_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root"
#"/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_Dstarpt30p0_Pthat30_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root"
#"/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_Dstarpt50p0_Pthat50_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root"
#)
#OUTPUTDIRECTORY="/data/wangj/debug/weighPthat/addmaxGenptBranch/Dstar3p"
#OUTPUTFILE="ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_addmaxgenpt"
#sed '1iint genSignal[2]={9,10};' addmaxGenptBranch.C > addmaxGenptBranch_tmp.C

#INPUTFILE=(
#"/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpipipi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpipipi_Dstarpt5p0_Pthat5_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root"
#"/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpipipi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpipipi_Dstarpt10p0_Pthat10_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root"
#"/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpipipi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpipipi_Dstarpt15p0_Pthat15_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root"
#"/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpipipi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpipipi_Dstarpt30p0_Pthat30_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root"
#"/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpipipi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpipipi_Dstarpt50p0_Pthat50_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root"
#)
#OUTPUTDIRECTORY="/data/wangj/debug/weighPthat/addmaxGenptBranch/Dstar5p"
#OUTPUTFILE="ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpipipi_addmaxgenpt"
#sed '1iint genSignal[2]={11,12};' addmaxGenptBranch.C > addmaxGenptBranch_tmp.C


###
g++ addmaxGenptBranch_tmp.C $(root-config --cflags --libs) -g -o addmaxGenptBranch_tmp.exe

if [ ! -d "$OUTPUTDIRECTORY" ]; then
    mkdir $OUTPUTDIRECTORY
else
    rm $OUTPUTDIRECTORY/*.root
fi

count=0
for ifile in ${INPUTFILE[@]}
do
    cp $ifile $OUTPUTDIRECTORY/${OUTPUTFILE}_$count.root
    infname=$OUTPUTDIRECTORY/${OUTPUTFILE}_$count.root
    ./addmaxGenptBranch_tmp.exe "$ifile" "$infname"
    count=$((count+1))
done
rm addmaxGenptBranch_tmp.exe
rm addmaxGenptBranch_tmp.C
echo