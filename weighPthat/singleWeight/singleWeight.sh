#!/bin/bash 

#INPUTFILE=(
#    "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0pt0p0_Pthat0_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20151212_dPt1tkPt1_D0Ds.root" 
#    "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0pt5p0_Pthat5_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20151212_dPt1tkPt1_D0Ds.root" 
#    "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0pt10p0_Pthat10_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20151212_dPt1tkPt1_D0Ds.root" 
#    "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0pt15p0_Pthat15_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20151212_dPt1tkPt1_D0Ds.root" 
#    "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0pt30p0_Pthat30_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20151212_dPt1tkPt1_D0Ds.root" 
#    "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0pt50p0_Pthat50_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20151212_dPt1tkPt1_D0Ds.root")
#OUTPUTDIRECTORY="/data/wangj/debug/weighPthat/weighDzero"
#OUTPUTFILE="ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0_weight.root"
#WEIGHT=(126843.39 3273.1442 201.97647 50.406753 1.7068600 0.16004668)

#INPUTFILE=(
#"/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_Dstarpt5p0_Pthat5_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root"
#"/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_Dstarpt10p0_Pthat10_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root"
#"/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_Dstarpt15p0_Pthat15_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root"
#"/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_Dstarpt30p0_Pthat30_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root"
#"/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_Dstarpt50p0_Pthat50_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root"
#)
#OUTPUTDIRECTORY="/data/wangj/debug/weighPthat/weighDstar3p"
#OUTPUTFILE="ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_weight.root"
#WEIGHT=(1557.5296 121.05670 21.982089 1.0752154 0.12885339)

#INPUTFILE=(
#"/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpipipi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpipipi_Dstarpt5p0_Pthat5_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root"
#"/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpipipi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpipipi_Dstarpt10p0_Pthat10_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root"
#"/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpipipi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpipipi_Dstarpt15p0_Pthat15_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root"
#"/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpipipi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpipipi_Dstarpt30p0_Pthat30_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root"
#"/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpipipi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpipipi_Dstarpt50p0_Pthat50_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root"
#)
#OUTPUTDIRECTORY="/data/wangj/debug/weighPthat/weighDstar5p"
#OUTPUTFILE="ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpipipi_weight.root"
#WEIGHT=(1734.4237 91.669337 28.187677 0.70483045 0.094527440)


##
g++ singleWeight.C $(root-config --cflags --libs) -g -o singleWeight.exe

if [ ! -d "$OUTPUTDIRECTORY" ]; then
    mkdir $OUTPUTDIRECTORY
else
    rm $OUTPUTDIRECTORY/*.root
fi

count=0
for ifile in ${INPUTFILE[@]}
do
    cp $ifile $OUTPUTDIRECTORY/ntD_toweigh_$count.root
    infname=$OUTPUTDIRECTORY/ntD_toweigh_$count.root
    ./singleWeight.exe "$infname" "${WEIGHT[$count]}"
    count=$((count+1))
done
rm singleWeight.exe
echo

echo " -- Merging weighed samples"
hadd $OUTPUTDIRECTORY/$OUTPUTFILE $OUTPUTDIRECTORY/ntD_toweigh_*.root
rm $OUTPUTDIRECTORY/ntD_toweigh_*.root
echo

echo " -- Merged output file"
echo "    $OUTPUTDIRECTORY/$OUTPUTFILE"
echo