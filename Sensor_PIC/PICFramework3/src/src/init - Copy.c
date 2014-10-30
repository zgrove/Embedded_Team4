#include "init.h";

// Initializes A/D bits
void init_ad() {
    
    // Set A/D Port Config Bits
    // AN0 - AN12 are now analog
    ADCON1bits.PCFG = 0x0;

    // Set voltage reference config bits
    // V_SS = 0  V_REF- = 1
    ADCON1bits.VCFG1 = 0;
    // V_SS = 1  V_REF+ = 1
    ADCON1bits.VCFG0 = 0;

    // Select A/D input channel
    // Set A/D Calibration bit
    ADCON0bits.ADCAL = 0;

    // Set Analog Channel bits
    // AN0
    ADCON0bits.CHS = 0x0;

    // Select A/D Aquisition Time &
    // Conversion clock settings
    // Set data to right-justified
    ADCON2bits.ADFM = 1;
    // A/D Aquisition Time
    ADCON2bits.ACQT = 0x01; //001
    // A/D Conversion Clock
    ADCON2bits.ADCS = 0x06; //110

    // Turn on A/D
    ADCON0bits.ADON = 1;

    // Clear A/D Flag
    PIR1bits.ADIF = 0;
    // Set A/D Converter Interrupt Enable
    PIE1bits.ADIE = 1;
    // Set Global Interrupt Enable
    INTCONbits.GIE = 1;
}

// Initializes Debug bits
void init_debug() {
     LATBbits.LATB0 = 0;
     LATBbits.LATB1 = 0;
     LATBbits.LATB2 = 0;
     LATBbits.LATB3 = 0;
     LATBbits.LATB4 = 0;
     LATBbits.LATB5 = 0;
}

// Sets debug bits depending on where its called
void set_debug(unsigned char op) {
    switch (op) {
        case 'a':
        {
            LATBbits.LATB0 = 1;
            init_debug();
            break;
        };
        case 'b':
        {
            LATBbits.LATB1 = 1;
            init_debug();
        };
        case 'c':
        {
            LATBbits.LATB0 = 1;
            LATBbits.LATB1 = 1;
            init_debug();
            break;
        };
        default:
        {
            LATBbits.LATB4 = 1;
            init_debug();
            break;
        };
    };

}
