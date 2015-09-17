###Condor submitting template for plain root jobs. Run on all the files separately in a given folder, the DATASET folder below
###TA-WEI WANG, 02/20/2014 created
###Your plain root file needs to be modified , see example loop.C
###Please compile the .C before submission to make sure your code is working.
###Checking condor jobs status: condor_q <username> 

###Plain root .C to be run
CONFIGFILE="loop.C"

###All the header/related files needed
TRANSFERFILE="loop.C,loop.h"

###Folder location within which files are to be run
DATASET=/mnt/hadoop/cms/store/user/twang/HI_DfinderNtuple/DinderMC_Pyquen_D0tokaonpion_D0pt1p0_Pthat0_TuneZ2_Unquenched_2760GeV_20150912/*
#DATASET=/mnt/hadoop/cms/store/user/twang/HI_DfinderNtuple/DinderMC_Pyquen_D0tokaonpion_D0pt1p0_Pthat15_TuneZ2_Unquenched_2760GeV_20150912/*
#DATASET=/mnt/hadoop/cms/store/user/twang/HI_DfinderNtuple/DinderMC_Pyquen_D0tokaonpion_D0pt1p0_Pthat30_TuneZ2_Unquenched_2760GeV_20150912/*
#DATASET=/mnt/hadoop/cms/store/user/twang/HI_DfinderNtuple/DinderMC_Pyquen_D0tokaonpion_D0pt1p0_Pthat50_TuneZ2_Unquenched_2760GeV_20150912/*

###Output file location
DESTINATION=/mnt/hadoop/cms/store/user/jwang/Dmeson/ntD_20150916_DinderMC_Pyquen_D0tokaonpion_D0pt1p0_Pthat0_TuneZ2_Unquenched_2760GeV_20150912_EvtBase
#DESTINATION=/mnt/hadoop/cms/store/user/jwang/Dmeson/ntD_20150916_DinderMC_Pyquen_D0tokaonpion_D0pt1p0_Pthat15_TuneZ2_Unquenched_2760GeV_20150912_EvtBase
#DESTINATION=/mnt/hadoop/cms/store/user/jwang/Dmeson/ntD_20150916_DinderMC_Pyquen_D0tokaonpion_D0pt1p0_Pthat30_TuneZ2_Unquenched_2760GeV_20150912_EvtBase
#DESTINATION=/mnt/hadoop/cms/store/user/jwang/Dmeson/ntD_20150916_DinderMC_Pyquen_D0tokaonpion_D0pt1p0_Pthat50_TuneZ2_Unquenched_2760GeV_20150912_EvtBase

###Output file name
OUTFILE="ntD_20150916_mc_pthat0_20150912_evtbase"
#OUTFILE="ntD_20150916_mc_pthat15_20150912_evtbase"
#OUTFILE="ntD_20150916_mc_pthat30_20150912_evtbase"
#OUTFILE="ntD_20150916_mc_pthat50_20150912_evtbase"

###Maximum number of files to be run
MAXFILES=1000

###Log file location and it's name
LOGDIR=/export/d00/scratch/jwang/hadooplogs/ntD_20150916_mc_pthat0_20150912_EvtBase
#LOGDIR=/export/d00/scratch/jwang/hadooplogs/ntD_20150916_mc_pthat15_20150912_EvtBase
#LOGDIR=/export/d00/scratch/jwang/hadooplogs/ntD_20150916_mc_pthat30_20150912_EvtBase
#LOGDIR=/export/d00/scratch/jwang/hadooplogs/ntD_20150916_mc_pthat50_20150912_EvtBase

LOGNAME=log_ntD_20150916_mc_pthat0_20150912_EvtBase
#LOGNAME=log_ntD_20150916_mc_pthat15_20150912_EvtBase
#LOGNAME=log_ntD_20150916_mc_pthat30_20150912_EvtBase
#LOGNAME=log_ntD_20150916_mc_pthat50_20150912_EvtBase

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