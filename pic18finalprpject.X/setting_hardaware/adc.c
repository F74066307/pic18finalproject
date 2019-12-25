#include <xc.h>
#include <pic18f4520.h>
#include <stdlib.h>
#include <math.h>
#include "adc.h"

//
double LPGCurve[3]  =  {2.3,0.21,-0.47}; 
double COCurve[3]  =  {2.3,0.72,-0.34};   
double SmokeCurve[3] = {2.3,0.53,-0.44};                                                       
double Ro = 10.0;  
int RL_VALUE = 1; 
 
int GAS_LPG = 0;
int GAS_CO = 1;
int GAS_SMOKE = 2;

double lpg = 0;
double co = 0;
double smoke = 0;



int MQGetPercentage(double rs_ro_ratio, double *pcurve) {
  return (pow(10,(((log(rs_ro_ratio)-pcurve[1])/pcurve[2]) + pcurve[0])));
}

double MQGetGasPercentage(double rs_ro_ratio, int gas_id) {
  if ( gas_id == GAS_LPG ) {
     return MQGetPercentage(rs_ro_ratio,LPGCurve);
  } else if ( gas_id == GAS_CO ) {
     return MQGetPercentage(rs_ro_ratio,COCurve);
  } else if ( gas_id == GAS_SMOKE ) {
     return MQGetPercentage(rs_ro_ratio,SmokeCurve);
  }    
  return 0;
}

void ADC_Initialize(void) {
    
    ADCON1 = 0x0D; //AN0,AN1->analog,other->digital	
    ADCON2=0x94;//right,ACQT=4TAD,ADCS=FOSC/4
    ADRES=0;
    
}

void MQ_Read(double* values){
    int digital;
    
    
    ADCON0bits.CHS = 1 ; // Select Channel
    ADCON0bits.ADON = 1;
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO_nDONE==1);
    digital = ADRES;
    double res=5.00*(1023-digital)/(double)digital;
    lpg = MQGetGasPercentage(res/Ro,GAS_LPG);
    if(lpg>=10000){
        lpg=10000;
    }
    co = MQGetGasPercentage(res/Ro,GAS_CO);
    if(co>=10000){
        co=10000;
    }
    smoke = MQGetGasPercentage(res/Ro,GAS_SMOKE);
    if(smoke>=10000){
        smoke=10000;
    }
    //ADCON0bits.ADON = 0;
    
    values[0]=lpg;
    values[1]=co;
    values[2]=smoke;
}
