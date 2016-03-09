#!/bin/bash
LABEL_DEFAULT=default
LABEL_TKETA1=tketa1
LABEL_PVZ15=pvz15
#

DOFIT3PMC_DEFAULT=0
DOFIT3PData_DEFAULT=0
DOFIT5PMC_DEFAULT=0
DOFIT5PData_DEFAULT=0

DOFIT3PMC_TKETA1=0
DOFIT3PData_TKETA1=0
DOFIT5PMC_TKETA1=0
DOFIT5PData_TKETA1=0

DOFIT3PMC_PVZ15=1
DOFIT3PData_PVZ15=1
DOFIT5PMC_PVZ15=1
DOFIT5PData_PVZ15=1

#default
cp saveHistSinglept/cfpars/doubleratioParameter_default.h doubleratioParameter.h
#
if [ $DOFIT3PMC_DEFAULT -eq 1 ]; then
sed '1ienum real{MC_MB,Data_MB,MC,Data} isData=MC;' fitDstar3pMinpt.C > fitDstar3pMinpt_tmp.C
g++ fitDstar3pMinpt_tmp.C $(root-config --cflags --libs) -g -o fitDstar3pMinpt_tmp.exe 
./fitDstar3pMinpt_tmp.exe "$LABEL_DEFAULT"
rm fitDstar3pMinpt_tmp.exe
rm fitDstar3pMinpt_tmp.C
fi
if [ $DOFIT3PData_DEFAULT -eq 1 ]; then
sed '1ienum real{MC_MB,Data_MB,MC,Data} isData=Data;' fitDstar3pMinpt.C > fitDstar3pMinpt_tmp.C
g++ fitDstar3pMinpt_tmp.C $(root-config --cflags --libs) -g -o fitDstar3pMinpt_tmp.exe 
./fitDstar3pMinpt_tmp.exe "$LABEL_DEFAULT"
rm fitDstar3pMinpt_tmp.exe
rm fitDstar3pMinpt_tmp.C
fi
if [ $DOFIT5PMC_DEFAULT -eq 1 ]; then
sed '1ienum real{MC_MB,Data_MB,MC,Data} isData=MC;' fitDstar5pMinpt.C > fitDstar5pMinpt_tmp.C
g++ fitDstar5pMinpt_tmp.C $(root-config --cflags --libs) -g -o fitDstar5pMinpt_tmp.exe 
./fitDstar5pMinpt_tmp.exe "$LABEL_DEFAULT"
rm fitDstar5pMinpt_tmp.exe
rm fitDstar5pMinpt_tmp.C
fi
if [ $DOFIT5PData_DEFAULT -eq 1 ]; then
sed '1ienum real{MC_MB,Data_MB,MC,Data} isData=Data;' fitDstar5pMinpt.C > fitDstar5pMinpt_tmp.C
g++ fitDstar5pMinpt_tmp.C $(root-config --cflags --libs) -g -o fitDstar5pMinpt_tmp.exe 
./fitDstar5pMinpt_tmp.exe "$LABEL_DEFAULT"
rm fitDstar5pMinpt_tmp.exe
rm fitDstar5pMinpt_tmp.C
fi
#
rm doubleratioParameter.h
#default end


#tketa1
cp saveHistSinglept/cfpars/doubleratioParameter_tketa1.h doubleratioParameter.h
#
if [ $DOFIT3PMC_TKETA1 -eq 1 ]; then
sed '1ienum real{MC_MB,Data_MB,MC,Data} isData=MC;' fitDstar3pMinpt.C > fitDstar3pMinpt_tmp.C
g++ fitDstar3pMinpt_tmp.C $(root-config --cflags --libs) -g -o fitDstar3pMinpt_tmp.exe 
./fitDstar3pMinpt_tmp.exe "$LABEL_TKETA1"
rm fitDstar3pMinpt_tmp.exe
rm fitDstar3pMinpt_tmp.C
fi
if [ $DOFIT3PData_TKETA1 -eq 1 ]; then
sed '1ienum real{MC_MB,Data_MB,MC,Data} isData=Data;' fitDstar3pMinpt.C > fitDstar3pMinpt_tmp.C
g++ fitDstar3pMinpt_tmp.C $(root-config --cflags --libs) -g -o fitDstar3pMinpt_tmp.exe 
./fitDstar3pMinpt_tmp.exe "$LABEL_TKETA1"
rm fitDstar3pMinpt_tmp.exe
rm fitDstar3pMinpt_tmp.C
fi
if [ $DOFIT5PMC_TKETA1 -eq 1 ]; then
sed '1ienum real{MC_MB,Data_MB,MC,Data} isData=MC;' fitDstar5pMinpt.C > fitDstar5pMinpt_tmp.C
g++ fitDstar5pMinpt_tmp.C $(root-config --cflags --libs) -g -o fitDstar5pMinpt_tmp.exe 
./fitDstar5pMinpt_tmp.exe "$LABEL_TKETA1"
rm fitDstar5pMinpt_tmp.exe
rm fitDstar5pMinpt_tmp.C
fi
if [ $DOFIT5PData_TKETA1 -eq 1 ]; then
sed '1ienum real{MC_MB,Data_MB,MC,Data} isData=Data;' fitDstar5pMinpt.C > fitDstar5pMinpt_tmp.C
g++ fitDstar5pMinpt_tmp.C $(root-config --cflags --libs) -g -o fitDstar5pMinpt_tmp.exe 
./fitDstar5pMinpt_tmp.exe "$LABEL_TKETA1"
rm fitDstar5pMinpt_tmp.exe
rm fitDstar5pMinpt_tmp.C
fi
#
rm doubleratioParameter.h
#tketa1 end


#pvz15
cp saveHistSinglept/cfpars/doubleratioParameter_pvz15.h doubleratioParameter.h
#
if [ $DOFIT3PMC_PVZ15 -eq 1 ]; then
sed '1ienum real{MC_MB,Data_MB,MC,Data} isData=MC;' fitDstar3pMinpt.C > fitDstar3pMinpt_tmp.C
g++ fitDstar3pMinpt_tmp.C $(root-config --cflags --libs) -g -o fitDstar3pMinpt_tmp.exe 
./fitDstar3pMinpt_tmp.exe "$LABEL_PVZ15"
rm fitDstar3pMinpt_tmp.exe
rm fitDstar3pMinpt_tmp.C
fi
if [ $DOFIT3PData_PVZ15 -eq 1 ]; then
sed '1ienum real{MC_MB,Data_MB,MC,Data} isData=Data;' fitDstar3pMinpt.C > fitDstar3pMinpt_tmp.C
g++ fitDstar3pMinpt_tmp.C $(root-config --cflags --libs) -g -o fitDstar3pMinpt_tmp.exe 
./fitDstar3pMinpt_tmp.exe "$LABEL_PVZ15"
rm fitDstar3pMinpt_tmp.exe
rm fitDstar3pMinpt_tmp.C
fi
if [ $DOFIT5PMC_PVZ15 -eq 1 ]; then
sed '1ienum real{MC_MB,Data_MB,MC,Data} isData=MC;' fitDstar5pMinpt.C > fitDstar5pMinpt_tmp.C
g++ fitDstar5pMinpt_tmp.C $(root-config --cflags --libs) -g -o fitDstar5pMinpt_tmp.exe 
./fitDstar5pMinpt_tmp.exe "$LABEL_PVZ15"
rm fitDstar5pMinpt_tmp.exe
rm fitDstar5pMinpt_tmp.C
fi
if [ $DOFIT5PData_PVZ15 -eq 1 ]; then
sed '1ienum real{MC_MB,Data_MB,MC,Data} isData=Data;' fitDstar5pMinpt.C > fitDstar5pMinpt_tmp.C
g++ fitDstar5pMinpt_tmp.C $(root-config --cflags --libs) -g -o fitDstar5pMinpt_tmp.exe 
./fitDstar5pMinpt_tmp.exe "$LABEL_PVZ15"
rm fitDstar5pMinpt_tmp.exe
rm fitDstar5pMinpt_tmp.C
fi
#
rm doubleratioParameter.h
#pvz15 end
