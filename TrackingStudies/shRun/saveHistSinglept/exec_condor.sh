CONFIGFILE=$1
PTTHRESHOLD=$2
OUTFILE=$3
DESTINATION=$4

source /osg/app/cmssoft/cms/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc491
cd /cvmfs/cms.cern.ch/slc6_amd64_gcc491/cms/cmssw/CMSSW_7_5_8/src
eval `scramv1 runtime -sh` 
cd -

root -l -b -q  $CONFIGFILE\(\"${PTTHRESHOLD}\",\"${OUTFILE}\"\)
mv ${OUTFILE} ${DESTINATION}/${OUTFILE}
##
