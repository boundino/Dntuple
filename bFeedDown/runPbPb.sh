PTMIN=(20 40 50)
PTMAX=(40 50 100)
count=0

DOSAVEHIST=0
DOPLOTFIT=1

for ptmin in ${PTMIN[@]}
do
    echo "Processing ptbin: $ptmin - ${PTMAX[$count]} ..."
    if [ $DOSAVEHIST -eq 1 ]; then
        g++ bFeedDownFractionPbPb.C $(root-config --cflags --libs) -g -o bFeedDownFractionPbPb.exe 
        ./bFeedDownFractionPbPb.exe ${ptmin} ${PTMAX[$count]}
        rm bFeedDownFractionPbPb.exe
    fi
    COLL=PbPb
    if [ $DOPLOTFIT -eq 1 ]; then
        g++ plotFits.C $(root-config --cflags --libs) -g -o plotFits.exe 
        ./plotFits.exe ${ptmin} ${PTMAX[$count]} ${COLL}
        rm plotFits.exe
    fi
    count=$((count+1))
done