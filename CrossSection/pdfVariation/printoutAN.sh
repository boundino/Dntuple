#!/bin/bash

sed '1iconst int nbins=8;' printoutAN.C > printoutAN_PPMB.C
g++ printoutAN_PPMB.C $(root-config --cflags --libs) -g -o printoutAN_PPMB.exe 
./printoutAN_PPMB.exe "PPMB"
rm printoutAN_PPMB.exe
rm printoutAN_PPMB.C

sed '1iconst int nbins=7;' printoutAN.C > printoutAN_PP.C
g++ printoutAN_PP.C $(root-config --cflags --libs) -g -o printoutAN_PP.exe 
./printoutAN_PP.exe "PP"
rm printoutAN_PP.exe
rm printoutAN_PP.C

sed '1iconst int nbins=8;' printoutAN.C > printoutAN_PbPbMB.C
g++ printoutAN_PbPbMB.C $(root-config --cflags --libs) -g -o printoutAN_PbPbMB.exe 
./printoutAN_PbPbMB.exe "PbPbMB"
rm printoutAN_PbPbMB.exe
rm printoutAN_PbPbMB.C

sed '1iconst int nbins=7;' printoutAN.C > printoutAN_PbPb.C
g++ printoutAN_PbPb.C $(root-config --cflags --libs) -g -o printoutAN_PbPb.exe 
./printoutAN_PbPb.exe "PbPb"
rm printoutAN_PbPb.exe
rm printoutAN_PbPb.C