#!/bin/bash
LABEL_DEFAULT=default
LABEL_TKETA1=tketa1
LABEL_PVZ15=pvz15
#

DORATIO_DEFAULT=1
DORATIO_TKETA1=1
DORATIO_PVZ15=1

if [ $DORATIO_DEFAULT -eq 1 ]; then
g++ plotdoubleratioMinpt.C $(root-config --cflags --libs) -g -o plotdoubleratioMinpt.exe 
./plotdoubleratioMinpt.exe "$LABEL_DEFAULT"
rm plotdoubleratioMinpt.exe
fi
if [ $DORATIO_TKETA1 -eq 1 ]; then
g++ plotdoubleratioMinpt.C $(root-config --cflags --libs) -g -o plotdoubleratioMinpt.exe 
./plotdoubleratioMinpt.exe "$LABEL_TKETA1"
rm plotdoubleratioMinpt.exe
fi
if [ $DORATIO_PVZ15 -eq 1 ]; then
g++ plotdoubleratioMinpt.C $(root-config --cflags --libs) -g -o plotdoubleratioMinpt.exe 
./plotdoubleratioMinpt.exe "$LABEL_PVZ15"
rm plotdoubleratioMinpt.exe
fi
