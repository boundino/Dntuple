####REMEMBER TO MOVE TO PP OR PbPb MODE
DIRECTORYOUTPUT="/afs/cern.ch/work/w/wangj/public/RunII/Dmeson/ntD_EvtBase_20151231_HeavyFlavor_DfinderData_pp_20151214_dPt0tkPt1_D0DsDstar3p5p"
NAME="loop.C"

rm mylistfinal.txt
rm run_*.sh
rm -rf LSFJOB_*

g++ $NAME $(root-config --cflags --libs) -Wall -O2 -o "${NAME/%.C/}.exe"

eos ls /store/user/twang/DfinderRun2/HeavyFlavor/DfinderData_pp_20151214_dPt0tkPt1_D0DsDstar3p5p/  | awk '{print "root://eoscms//eos/cms/store/user/twang/DfinderRun2/HeavyFlavor/DfinderData_pp_20151214_dPt0tkPt1_D0DsDstar3p5p/" $0}' >> mylistfinal.txt

count=0 ; for i in `cat mylistfinal.txt` ; do echo cd $PWD/ > run_$count.sh ; echo 'export X509_USER_PROXY=~/x509_user_proxy'>> run_$count.sh ; 
echo eval \`scram runtime -sh\` >> run_$count.sh ; echo cd - >> run_$count.sh ; echo $PWD/loop.exe $i $DIRECTORYOUTPUT/ntuple_$count.root  >> run_$count.sh ; chmod +x run_$count.sh; count=$((count+1)) ; done
#for i in `ls run_*` ; do bsub -q cmscaf1nd $i ; done
for i in `ls run_*` ; do bsub -q 1nh $i ; done

#cmscaf1nd