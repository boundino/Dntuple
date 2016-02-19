#include "format_float.h"

void test()
{
  TVector3* v3tk1 = new TVector3;
  v3tk1->SetPtEtaPhi(1.76005,-0.172386,1.79737);
  TVector3* v3tk2 = new TVector3;
  v3tk2->SetPtEtaPhi(2.93291,-0.268635,2.08529);
  TVector3* v3tk3 = new TVector3;
  v3tk3->SetPtEtaPhi(3.64433,-0.214499,2.10423);
  TVector3* v3tk4 = new TVector3;
  v3tk4->SetPtEtaPhi(1.22771,-0.242259,1.78876);
  TVector3* v3D0 = new TVector3;
  v3D0->SetXYZ(v3tk1->X()+v3tk2->X()+v3tk3->X()+v3tk4->X(),v3tk1->Y()+v3tk2->Y()+v3tk3->Y()+v3tk4->Y(),v3tk1->Z()+v3tk2->Z()+v3tk3->Z()+v3tk4->Z());
  cout<<v3D0->Pt()<<" "<<v3D0->PseudoRapidity()<<" "<<v3D0->Phi()<<endl;
  /*
  TVector3* v3tk1 = new TVector3;
  v3tk1->SetPtEtaPhi(1.75597,-0.171777,1.79272);
  TVector3* v3tk2 = new TVector3;
  v3tk2->SetPtEtaPhi(0.664763,-0.0134482,-1.15398);
  TVector3* v3tk3 = new TVector3;
  v3tk3->SetPtEtaPhi(3.4221,0.377819,-1.06399);
  TVector3* v3tk4 = new TVector3;
  v3tk4->SetPtEtaPhi(2.87494,-0.269269,2.08845);
  TVector3* v3D0 = new TVector3;
  v3D0->SetXYZ(v3tk1->X()+v3tk2->X()+v3tk3->X()+v3tk4->X(),v3tk1->Y()+v3tk2->Y()+v3tk3->Y()+v3tk4->Y(),v3tk1->Z()+v3tk2->Z()+v3tk3->Z()+v3tk4->Z());
  cout<<v3D0->Pt()<<" "<<v3D0->PseudoRapidity()<<" "<<v3D0->Phi()<<endl;
  */
}
