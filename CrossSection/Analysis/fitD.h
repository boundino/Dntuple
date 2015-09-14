TString cmcut = "(Dtrk1PixelHit+Dtrk1StripHit)>11&&(Dtrk2PixelHit+Dtrk2StripHit)>11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer))<0.25&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer))<0.25&&(Dtrk1PtErr/Dtrk1Pt)<0.075&&(Dtrk2PtErr/Dtrk2Pt)<0.075&&Dtrk1Eta<1.1&&Dtrk2Eta<1.1&&Dy>-1.&&Dy<1.&&(Ddxyz/DdxyzErr)>2.5";
TString ptcut0 = "Ddtheta<0.12&&(Dpt>2.5&&Dpt<40.&&(Ddxyz/DdxyzErr)>5.90&&Dchi2cl>0.248)";
TString cut0 = Form("%s&&%s",cmcut.Data(),ptcut0.Data());
TString ptcut1 = "Ddtheta<0.12&&((Dpt>2.5&&Dpt<3.5&&(Ddxyz/DdxyzErr)>5.90&&Dchi2cl>0.248) || (Dpt>3.5&&Dpt<4.5&&(Ddxyz/DdxyzErr)>5.81&&Dchi2cl>0.200) || (Dpt>4.5&&Dpt<5.5&&(Ddxyz/DdxyzErr)>5.10&&Dchi2cl>0.191) || (Dpt>5.5&&Dpt<7.0&&(Ddxyz/DdxyzErr)>4.62&&Dchi2cl>0.148) || (Dpt>7.0&&Dpt<9.0&&(Ddxyz/DdxyzErr)>4.46&&Dchi2cl>0.102) || (Dpt>9.0&&Dpt<11.&&(Ddxyz/DdxyzErr)>4.39&&Dchi2cl>0.080) || (Dpt>11.&&Dpt<13.&&(Ddxyz/DdxyzErr)>4.07&&Dchi2cl>0.073) || (Dpt>13.&&Dpt<16.&&(Ddxyz/DdxyzErr)>3.88&&Dchi2cl>0.060) || (Dpt>16.&&Dpt<20.&&(Ddxyz/DdxyzErr)>3.67&&Dchi2cl>0.055) || (Dpt>20.&&Dpt<28.&&(Ddxyz/DdxyzErr)>3.25&&Dchi2cl>0.054) || (Dpt>28.&&Dpt<40.&&(Ddxyz/DdxyzErr)>2.55&&Dchi2cl>0.043))";
TString cut1 = Form("%s&&%s",cmcut.Data(),ptcut1.Data());
TString cuts[2] = {cut0,cut1};

//TString cmcutpurdue = "dcanddau1pt>1.5&&dcanddau2pt>1.5&&dcanddau1eta<1.1&&dcanddau2eta<1.1&&dcandy>-1.&&dcandy<1.&&dcandffls3d>2.5";
TString cmcutpurdue = "dcanddau1pt>1.5&&dcanddau2pt>1.5&&dcanddau1eta<1.1&&dcanddau2eta<1.1&&dcandy>-1.&&dcandy<1.";
TString ptcutpurdue0 = "TMath::ACos(dcandcosalpha)<0.12&&(dcandpt>2.5&&dcandpt<40.&&dcandffls3d>5.90&&dcandfprob>0.248)";
TString cutpurdue0 = Form("%s&&%s",cmcutpurdue.Data(),ptcutpurdue0.Data());
TString ptcutpurdue1 = "TMath::ACos(dcandcosalpha)<0.12&&((dcandpt>2.5&&dcandpt<3.5&&dcandffls3d>5.90&&dcandfprob>0.248) || (dcandpt>3.5&&dcandpt<4.5&&dcandffls3d>5.81&&dcandfprob>0.200) || (dcandpt>4.5&&dcandpt<5.5&&dcandffls3d>5.10&&dcandfprob>0.191) || (dcandpt>5.5&&dcandpt<7.0&&dcandffls3d>4.62&&dcandfprob>0.148) || (dcandpt>7.0&&dcandpt<9.0&&dcandffls3d>4.46&&dcandfprob>0.102) || (dcandpt>9.0&&dcandpt<11.&&dcandffls3d>4.39&&dcandfprob>0.080) || (dcandpt>11.&&dcandpt<13.&&dcandffls3d>4.07&&dcandfprob>0.073) || (dcandpt>13.&&dcandpt<16.&&dcandffls3d>3.88&&dcandfprob>0.060) || (dcandpt>16.&&dcandpt<20.&&dcandffls3d>3.67&&dcandfprob>0.055) || (dcandpt>20.&&dcandpt<28.&&dcandffls3d>3.25&&dcandfprob>0.054) || (dcandpt>28.&&dcandpt<40.&&dcandffls3d>2.55&&dcandfprob>0.043))";
TString cutpurdue1 = Form("%s&&%s",cmcutpurdue.Data(),ptcutpurdue1.Data());
TString cutspurdue[2] = {cutpurdue0,cutpurdue1};





