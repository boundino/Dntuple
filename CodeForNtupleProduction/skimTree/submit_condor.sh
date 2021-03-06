CONFIGFILE="skimTree.C"
TRANSFERFILE="skimTree.C,skimTree.h,uti.h"
DATASET=/mnt/hadoop/cms/store/user/jwang/DntupleRun2/pp_MinimumBias_Run2015E_PromptReco_v1_AOD/ntD_EvtBase_20160219_Dfinder_20160219_pp_MinimumBias_Run2015E_PromptReco_v1_AOD_MinimumBias2_dPt2tkPt0p5_Dstar3p5p/*
DESTINATION=/mnt/hadoop/cms/store/user/jwang/DntupleRun2/pp_MinimumBias_Run2015E_PromptReco_v1_AOD/ntD_EvtBase_20160219_Dfinder_20160219_pp_MinimumBias_Run2015E_PromptReco_v1_AOD_MinimumBias2_dPt2tkPt0p5_Dstar3p5p_skim_20160220
OUTFILE="ntD_EvtBase_MinimumBias2_dPt2tkPt0p5_Dstar3p5p_skim_20160220"
MAXFILES=1000
LOGDIR=/export/d00/scratch/jwang/hadooplogs/log_ntD_EvtBase_20160219_Dfinder_20160219_pp_MinimumBias_Run2015E_PromptReco_v1_AOD_MinimumBias2_dPt2tkPt0p5_Dstar3p5p_skim_20160220
LOGNAME=log_ntD_EvtBase_MinimumBias2_dPt2tkPt0p5_Dstar3p5p_skim_20160220

########################## Create subfile ###############################
dateTime=$(date +%Y%m%d%H%M)
fileCounter=0
INFILE=""
mkdir -p $DESTINATION
mkdir -p $LOGDIR

for file in $DATASET
do
    if [ $fileCounter -ge $MAXFILES ]
    then
	break
    fi

    INFILE="$file"
    fileCounter=$((fileCounter+1))

# make the condor file
cat > subfile <<EOF

Universe = vanilla
Initialdir = .
Executable = exec_condor.sh
+AccountingGroup = "group_cmshi.$(whoami)"
Arguments =  $CONFIGFILE $DESTINATION ${OUTFILE}_${fileCounter}.root $INFILE
GetEnv       = True
Input = /dev/null
# log files
Output       = $LOGDIR/$LOGNAME-$dateTime-${fileCounter}.out
Error        = $LOGDIR/$LOGNAME-$dateTime-${fileCounter}.err
Log          = $LOGDIR/$LOGNAME-$dateTime-${fileCounter}.log
should_transfer_files = YES
when_to_transfer_output = ON_EXIT
transfer_input_files = $TRANSFERFILE
Queue
EOF

############################ Submit ###############################

#cat subfile
condor_submit subfile
mv subfile $LOGDIR/$LOGNAME-$dateTime-$fileCounter.subfile
done
echo "Submitted $fileCounter jobs to Condor."