CONDITION="pvz15"
ISDATA="Data"
cp cfpars/doubleratioParameter_$CONDITION.h doubleratioParameter.h

PTBINS=(5 6 7 8 9 10 11 12 13 14)
CONFIGFILE="saveHist5pSinglept.C"
TRANSFERFILE="saveHist5pSinglept.C,doubleratioParameter.h,uti.h"

DESTINATION=/export/d00/scratch/jwang/fmass
OUTFILE="fmass_pp"

LOGDIR=/export/d00/scratch/jwang/logs/saveHist_pp_saveHist5pSinglept_${ISDATA}_${CONDITION}
mkdir -p $LOGDIR
LOGNAME=log
dateTime=$(date +%Y%m%d%H%M)

########################## Create subfile ###############################

for minpt in ${PTBINS[@]}
do

# make the condor file
cat > subfile <<EOF

Universe = vanilla
Initialdir = .
Executable = exec_condor.sh
+AccountingGroup = "group_cmshi.$(whoami)"
Arguments =  $CONFIGFILE $minpt ${OUTFILE}_${CONDITION}_5p_${ISDATA}_${minpt}.root $DESTINATION
GetEnv       = True
Input = /dev/null
# log files
Output       = $LOGDIR/$LOGNAME-$dateTime-${minpt}.out
Error        = $LOGDIR/$LOGNAME-$dateTime-${minpt}.err
Log          = $LOGDIR/$LOGNAME-$dateTime-${minpt}.log
should_transfer_files = YES
when_to_transfer_output = ON_EXIT
transfer_input_files = $TRANSFERFILE
Queue
EOF

############################ Submit ###############################

#cat subfile
condor_submit subfile
mv subfile $LOGDIR/$LOGNAME-$dateTime-${minpt}.subfile
done
echo "Jobs submitted to Condor."