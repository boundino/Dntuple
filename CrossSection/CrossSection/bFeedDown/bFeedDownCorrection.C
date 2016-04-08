	#include <TF1.h>

// Yen-Jie: B feeddown fraction

float bFeedDownCorrection(double pt, bool isPbPb)
{
   double val=-1.0; // place holder
   double errval=-1.0;
   

   if (!isPbPb) { // pp
      if (pt>1&&pt<2) {
	 val = 0.868;
      } else if (pt>2&&pt<6) {
	 val = 0.868;
      } else if (pt>6&&pt<10) {
	 val = 0.979;
      }else if (pt>10&&pt<20) {
	 val = 0.955;
      } else if (pt>20&&pt<50) {
        val = 0.961;
      } else if (pt>50&&pt<100) { 
        val = 0.947;
      }
   } 
   else{
     // PbPb
     if (pt>1&&pt<2) {
       val = 1.000;
     } else if (pt>2&&pt<6) {
       val = 1.000;
     } else if (pt>6&&pt<10) {
       val = 0.946;
     }else if (pt>10&&pt<20) {
       val = 0.960;
     } else if (pt>20&&pt<50) {
       val = 1.000;
     } else if (pt>50&&pt<100) { 
       val = 0.976;
     }
   }
   return val;
}
