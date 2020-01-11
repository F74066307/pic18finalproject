#include "adc.h"

//translation gas coef array
double LPGCurve[3] = {2.3, 0.21, -0.47};
double COCurve[3] = {2.3, 0.72, -0.34};
double SmokeCurve[3] = {2.3, 0.53, -0.44};

//gas id
int GAS_LPG = 0;
int GAS_CO = 1;
int GAS_SMOKE = 2;

//air coef
double Ro;

/*
 *use predefined equation to calculate gas in ppm
 * 
 * param: double rs_ro_ratio - Rs/Ro
 * param: double *pcurve - translation gas coef array
 */
int MQGetPercentage(double rs_ro_ratio, double *pcurve) {
    return (pow(10, (((log10(rs_ro_ratio) - pcurve[1]) / pcurve[2]) + pcurve[0])));
}

/*
 *get target gas value in ppm with Rs/Ro value
 * 
 * param: double rs_ro_ratio - Rs/Ro
 * param: int gas_id - target gas id
 */
double MQGetGasPercentage(double rs_ro_ratio, int gas_id) {
    if (gas_id == GAS_LPG) {
        return MQGetPercentage(rs_ro_ratio, LPGCurve);
    } else if (gas_id == GAS_CO) {
        return MQGetPercentage(rs_ro_ratio, COCurve);
    } else if (gas_id == GAS_SMOKE) {
        return MQGetPercentage(rs_ro_ratio, SmokeCurve);
    }
    return 0;
}

/*
 *read and return a doble array with [lpg,co,smoke] in ppm value by adc
 * 
 * param: double* values - the array to place result
 */
void MQ_Read(double* values) {
    //raw adc value
    int digital;

    //lpg,co,smoke value
    double lpg;
    double co;
    double smoke;

    ADCON0bits.CHS = 0; // Select Channel
    ADCON0bits.ADON = 1; // enable adc
    ADCON0bits.GO = 1; // start conversion
    //wait for conversion finish
    while (ADCON0bits.GO_nDONE == 1);

    //read raw adc value
    digital = ADRES;

    //get lpg,co,smoke value with upper bound
    double res = 1.00 * (1023 - digital) / (double) digital;
    lpg = MQGetGasPercentage(res / Ro, GAS_LPG);
    if (lpg >= 9000) {
        lpg = 9000;
    }
    co = MQGetGasPercentage(res / Ro, GAS_CO);
    if (co >= 9000) {
        co = 9000;
    }
    smoke = MQGetGasPercentage(res / Ro, GAS_SMOKE);
    if (smoke >= 9000) {
        smoke = 9000;
    }

    //set results
    values[0] = lpg;
    values[1] = co;
    values[2] = smoke;

}

/*
 *init adc module and Calibrating the MQ2 sensor
 */
void ADC_Initialize(void) {

    ADCON1 = 0x0D; //AN0,AN1->analog,other->digital	
    ADCON2 = 0x94; //right,ACQT=4TAD,ADCS=FOSC/4
    ADRES = 0;

    //init mq2 sensor
    int i;
    double val = 0;
    for (i = 0; i < 10; i++) { //take multiple samples
        int digital;
        ADCON0bits.CHS = 0; // Select Channel
        ADCON0bits.ADON = 1;
        ADCON0bits.GO = 1;
        while (ADCON0bits.GO_nDONE == 1);
        digital = ADRES;
        double res = 1.00 * (1023 - digital) / (double) digital;
        val += res;
        __delay_us(50);
    }
    val = val / 10; //calculate the average value
    val = val / 10.0; //divided by RO_CLEAN_AIR_FACTOR yields the Ro  
    Ro = val; //Calibrating the sensor. Please make sure the sensor is in clean air 
}