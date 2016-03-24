PTMIN=(15 20 25 35 50)
PTMAX=(20 25 35 50 100)
count=0

DOSAVEHIST=0
DOPLOTFIT=1

for ptmin in ${PTMIN[@]}
do
    echo "Processing ptbin: $ptmin - ${PTMAX[$count]} ..."
    if [ $DOSAVEHIST -eq 1 ]; then
    g++ bFeedDownFractionPP.C $(root-config --cflags --libs) -g -o bFeedDownFractionPP.exe 
    ./bFeedDownFractionPP.exe ${ptmin} ${PTMAX[$count]}
    rm bFeedDownFractionPP.exe
    fi
    COLL=PP
    if [ $DOPLOTFIT -eq 1 ]; then
        g++ plotFits.C $(root-config --cflags --libs) -g -o plotFits.exe
        ./plotFits.exe ${ptmin} ${PTMAX[$count]} ${COLL}
        rm plotFits.exe
    fi
    count=$((count+1))
done