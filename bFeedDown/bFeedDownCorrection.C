	#include <TF1.h>

// Yen-Jie: B feeddown fraction

float bFeedDownFraction(double pt, double HLT, bool isPbPb)
{
   double val=0.23; // place holder
   if (!isPbPb) { // pp
      if (pt>6&&pt<8) {
         // 81.5 +- 2.3
	 val = 1-0.815;
      } else if (pt>8&&pt<10) {
         // 69.2 +- 2.9
	 val = 1-0.692;
      }else if (pt>10&&pt<15) {
         // 71.8 +- 2.8
	 val = 1-0.718;
      } else if (pt>15&&pt<20) {
         //  73.0 +- 6.3
         val = 1-0.730;
      } else if (pt>20&&pt<30) { 
         // 77.0+- 1.7%
         val = 1-0.770;
      } else if (pt>30&&pt<40) {  
         // 75.3 +- 1.6%
	 val = 1-0.753;
      } else if (pt>40&&pt<50) {
         // 83.3% +- 3.5%
	 val = 1-0.833;
      } else if (pt>50) {
         // 82.4% +- 3.1%
	 val = 1-0.824;
      }
   } else {
     // PbPb
      val = 0.15; // place holder
   }
   return val;
}
