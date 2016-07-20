ISPbPb=1

INPUTDATAPbPbMBUNSKIMMED=(
    "/data/wangj/Data2015/Dntuple/PbPb/TrackerOnly/Dntuple_crab_PbPb_HIMinimumBias1_tkpt0p5eta1p5_Dy1p1_EvtPlaneCalibration_v2v3etagap_05142016new_TrackerOnly_JSON.root"
    "/data/wangj/Data2015/Dntuple/PbPb/TrackerOnly/Dntuple_crab_PbPb_HIMinimumBias2_tkpt0p5eta1p5_Dy1p1_EvtPlaneCalibration_v2v3etagap_05142016_TrackerOnly_JSON.root"
    "/data/wangj/Data2015/Dntuple/PbPb/TrackerOnly/Dntuple_crab_PbPb_HIMinimumBias3_tkpt0p5eta1p5_Dy1p1_EvtPlaneCalibration_v2v3etagap_05142016_TrackerOnly_JSON.root"
    "/data/wangj/Data2015/Dntuple/PbPb/TrackerOnly/Dntuple_crab_PbPb_HIMinimumBias4_tkpt0p5eta1p5_Dy1p1_EvtPlaneCalibration_v2v3etagap_05142016_TrackerOnly_JSON.root"
    "/data/wangj/Data2015/Dntuple/PbPb/TrackerOnly/Dntuple_crab_PbPb_HIMinimumBias5_tkpt0p5eta1p5_Dy1p1_EvtPlaneCalibration_v2v3etagap_05142016new_TrackerOnly_JSON.root"
    "/data/wangj/Data2015/Dntuple/PbPb/TrackerOnly/Dntuple_crab_PbPb_HIMinimumBias6_tkpt0p5eta1p5_Dy1p1_EvtPlaneCalibration_v2v3etagap_05142016new_TrackerOnly_JSON.root"
    "/data/wangj/Data2015/Dntuple/PbPb/TrackerOnly/Dntuple_crab_PbPb_HIMinimumBias7_tkpt0p5eta1p5_Dy1p1_EvtPlaneCalibration_v2v3etagap_05142016new_TrackerOnly_JSON.root"
    "/data/wangj/Data2015/Dntuple/PbPb/TrackerOnly/Dntuple_crab_PbPb_HIMinimumBias8_tkpt0p5eta1p5_Dy1p1_EvtPlaneCalibration_v2v3etagap_05142016new_TrackerOnly_JSON.root"
    "/data/wangj/Data2015/Dntuple/PbPb/TrackerOnly/Dntuple_crab_PbPb_HIMinimumBias9_tkpt0p5eta1p5_Dy1p1_EvtPlaneCalibration_v2v3etagap_05142016new_TrackerOnly_JSON.root"
    "/data/wangj/Data2015/Dntuple/PbPb/TrackerOnly/Dntuple_crab_PbPb_HIMinimumBias10_tkpt0p5eta1p5_Dy1p1_EvtPlaneCalibration_v2v3etagap_05142016new_TrackerOnly_JSON.root"
    "/data/wangj/Data2015/Dntuple/PbPb/TrackerOnly/Dntuple_crab_PbPb_HIMinimumBias11_tkpt0p5eta1p5_Dy1p1_EvtPlaneCalibration_v2v3etagap_05142016new_TrackerOnly_JSON.root"
)

SELTRIGGER=(
    "HLT_HIL1MinimumBiasHF2AND_part7_v1"
    "HLT_HIL1MinimumBiasHF2AND_part1_v1"
    "HLT_HIL1MinimumBiasHF2AND_part2_v1"
    "HLT_HIL1MinimumBiasHF2AND_part3_v1"
    "HLT_HIL1MinimumBiasHF2AND_part4_v1"
    "HLT_HIL1MinimumBiasHF2AND_part5_v1"
    "HLT_HIL1MinimumBiasHF2AND_part6_v1"
    "HLT_HIL1MinimumBiasHF2AND_part8_v1"
    "HLT_HIL1MinimumBiasHF2AND_part9_v1"
    "HLT_HIL1MinimumBiasHF2AND_part10_v1"
    "HLT_HIL1MinimumBiasHF2AND_part11_v1"
)

EVENTFILTERMB="pclusterCompatibilityFilter&&pprimaryVertexFilter&&phfCoincFilter3"

UNPRESCALE=403.517
UNPRESCALEMB=127.039

g++ prescaleBrilCalc.C $(root-config --cflags --libs) -g -o prescaleBrilCalc.exe
i=0
while((i<11))
do
    echo
    ./prescaleBrilCalc.exe "${INPUTDATAPbPbMBUNSKIMMED[i]}" "$UNPRESCALE" "$UNPRESCALEMB" "${EVENTFILTERMB}&&${SELTRIGGER[i]}" "$ISPbPb"
    i=$(($i+1))
done
rm prescaleBrilCalc.exe
