PTMIN=(6 10 15)
PTMAX=(10 15 20)
count=0

DOSAVEHIST=0
DOPLOTFIT=1

for ptmin in ${PTMIN[@]}
do
    echo "Processing ptbin: $ptmin - ${PTMAX[$count]} ..."
    if [ $DOSAVEHIST -eq 1 ]; then
        g++ bFeedDownFractionPbPbMB.C $(root-config --cflags --libs) -g -o bFeedDownFractionPbPbMB.exe 
        ./bFeedDownFractionPbPbMB.exe ${ptmin} ${PTMAX[$count]}
        rm bFeedDownFractionPbPbMB.exe
    fi
    COLL=PbPbMB
    if [ $DOPLOTFIT -eq 1 ]; then
        g++ plotFits.C $(root-config --cflags --libs) -g -o plotFits.exe
        ./plotFits.exe ${ptmin} ${PTMAX[$count]} ${COLL}
        rm plotFits.exe
    fi
    count=$((count+1))
done
