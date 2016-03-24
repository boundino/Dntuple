PTMIN=(2 6 8 10)
PTMAX=(6 8 10 15)
count=0

DOSAVEHIST=0
DOPLOTFIT=1

for ptmin in ${PTMIN[@]}
do
    echo "Processing ptbin: $ptmin - ${PTMAX[$count]} ..."
    if [ $DOSAVEHIST -eq 1 ]; then
    g++ bFeedDownFractionPPMB.C $(root-config --cflags --libs) -g -o bFeedDownFractionPPMB.exe 
    ./bFeedDownFractionPPMB.exe  ${ptmin} ${PTMAX[$count]}
    rm bFeedDownFractionPPMB.exe
    fi
    COLL=PPMB
    if [ $DOPLOTFIT -eq 1 ]; then
        g++ plotFits.C $(root-config --cflags --libs) -g -o plotFits.exe
        ./plotFits.exe ${ptmin} ${PTMAX[$count]} ${COLL}
        rm plotFits.exe
    fi
    count=$((count+1))
done
