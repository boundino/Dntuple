CONFIGFILE="loop.C"
TRANSFERFILE="loop.C,loop.h,Dntuple.h,format.h"
DATASET=/mnt/hadoop/cms/store/user/wangj/DfinderRun2/pp_MinimumBias_Run2015E_PromptReco_v1_AOD/MinimumBias6/DfinderData_pp_20160219_dPt2tkPt0p5_Dstar3p5p/160219_062512/0000
INFILECOUNTER=(1 209 111 114 264 265 266 267 27 285 304 318 319 32 320 326 332 351 125 37 386 388 389 39 390 13 423 442 444 445 469 473 48 52 574 60 600 601 604 606 65 168)
DESTINATION=/mnt/hadoop/cms/store/user/jwang/DntupleRun2/pp_MinimumBias_Run2015E_PromptReco_v1_AOD/ntD_EvtBase_20160219_Dfinder_20160219_pp_MinimumBias_Run2015E_PromptReco_v1_AOD_MinimumBias6_dPt2tkPt0p5_Dstar3p5p
OUTFILE="ntD_EvtBase_MinimumBias6_dPt2tkPt0p5_Dstar3p5p"
OUTFILECOUNTER=(1 123 15 18 184 185 186 187 190 207 229 244 245 246 247 253 260 281 30 301 319 321 322 323 324 35 361 382 384 385 411 416 423 468 528 557 558 559 562 564 580 77)
LOGDIR=/export/d00/scratch/jwang/hadooplogs/log_ntD_EvtBase_20160219_Dfinder_20160219_pp_MinimumBias_Run2015E_PromptReco_v1_AOD_MinimumBias6_dPt2tkPt0p5_Dstar3p5p
LOGNAME=log_ntD_EvtBase_MinimumBias6_dPt2tkPt0p5_Dstar3p5p

########################## Create subfile ###############################
mkdir -p $LOGDIR
dateTime=$(date +%Y%m%d%H%M)
fileCounter=0
INFILE=""
count=0
for ifile in ${INFILECOUNTER[@]}
do
    INFILE=${DATASET}/HiForestAOD_${ifile}.root
    fileCounter=${OUTFILECOUNTER[$count]}
    count=$((count+1))

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
echo "Submitted $count jobs to Condor."