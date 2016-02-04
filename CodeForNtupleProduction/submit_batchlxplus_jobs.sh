DIRECTORYOUTPUT="/afs/cern.ch/work/w/wangj/public/RunII/Dmeson/ntD_EvtBase_20160203_Dfinder_20160201_pp_Pythia8_prompt_D0pt50p0_Pthat50_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20151212_dPt0tkPt0p5_D0Dstar"
NAME="loop.C"

rm mylistfinal.txt
rm run_*.sh
rm -rf LSFJOB_*

g++ $NAME $(root-config --cflags --libs) -Wall -O2 -o "${NAME/%.C/}.exe"

eos ls /store/user/twang/DfinderRun2/pp_Pythia8_prompt_D0pt50p0_Pthat50_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20151212/DfinderMC_pp_20160201_dPt1tkPt0p5_D0Dstar/  | awk '{print "root://eoscms//eos/cms//store/user/twang/DfinderRun2/pp_Pythia8_prompt_D0pt50p0_Pthat50_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20151212/DfinderMC_pp_20160201_dPt1tkPt0p5_D0Dstar/" $0}' >> mylistfinal.txt

count=0 ; for i in `cat mylistfinal.txt` ; do echo cd $PWD/ > run_$count.sh ; echo 'export X509_USER_PROXY=~/x509_user_proxy'>> run_$count.sh ; 
echo eval \`scram runtime -sh\` >> run_$count.sh ; echo cd - >> run_$count.sh ; echo $PWD/loop.exe $i $DIRECTORYOUTPUT/ntuple_$count.root  >> run_$count.sh ; chmod +x run_$count.sh; count=$((count+1)) ; done
#for i in `ls run_*` ; do bsub -q cmscaf1nd $i ; done
for i in `ls run_*` ; do bsub -q 1nh $i ; done
