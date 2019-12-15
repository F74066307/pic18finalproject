#include <xc.h>
#include <pic18f4520.h>
#include <stdlib.h>
#include <math.h>

//https://qiita.com/erukiti/items/1d9658f7c363e79d051b
#define MQ135_DEFAULTPPM 399 //default ppm of CO2 for calibration
#define MQ135_DEFAULTRO 68550 //default Ro for MQ135_DEFAULTPPM ppm of CO2
#define MQ135_SCALINGFACTOR 116.6020682 //CO2 gas value
#define MQ135_EXPONENT -2.769034857 //CO2 gas value
#define MQ135_MAXRSRO 2.428 //for CO2
#define MQ135_MINRSRO 0.358 //for CO2

#define RO 2000.0

double mq135_ro = RO;

void ADC_Initialize(void) {
    TRISA = 0x03;//RA0,RA1 input
    //ADCON=0x01;//CH=0,go_done=0,on=1
    ADCON1 = 0x0D; //AN0,AN1->analog,other->digital	
    ADCON2=0x94;//right,ACQT=4TAD,ADCS=FOSC/4
    ADRES=0;
}

double mq135_getppm(long resvalue, long ro) {
  double ret = 0;
  double validinterval = resvalue / (double)ro;
  if (validinterval < MQ135_MAXRSRO && validinterval > MQ135_MINRSRO) {
    ret = (double)MQ135_SCALINGFACTOR * pow(((double)resvalue / ro), MQ135_EXPONENT);
  }
  return ret;
}

double ADC_Read(int channel)
{
    //0 for LM35DZ,1 for MQ-135
    int digital;
    double result=0;
    
    ADCON0bits.CHS = channel ; // Select Channel0
    ADCON0bits.ADON = 1;
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO_nDONE==1);

    digital = ADRES;
    if(channel==1){
        //MQ-135 CO2
        int val = (RO * (1023 - digital) / digital);
        result=mq135_getppm(val, MQ135_DEFAULTRO);
    }
    else{
        //LM35DZ
        result=digital*4.88/10;
    }
    ADCON0bits.ADON = 0;
    return result;
}