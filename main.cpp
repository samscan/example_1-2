
#include "mbed.h"
#include "arm_book_lib.h"

UnbufferedSerial uartUsb(USBTX, USBRX, 115200);

AnalogIn potentiometer(A0);

float potentiometerReading = 0.0;

void uartTask();
float potentiometerAngle(float potentiometerReading); 

int main()
{
    while (true) {
        uartTask();
    }
}

void uartTask()
{
    char receivedChar = '\0';
    char str[100];
    int stringLength;
    if( uartUsb.readable() ) {
        uartUsb.read( &receivedChar, 1 );
        switch (receivedChar) {
        case 'p':
        case 'P':
            potentiometerReading = potentiometer.read();
            sprintf ( str, "Pot reading: %.3f\r\n", potentiometerReading );
            stringLength = strlen(str);
            uartUsb.write( str, stringLength );
            break;

        case 'a':
        case 'A': 
            potentiometerReading = potentiometer.read();
            sprintf (str, "Steering angle: %3f\r\n", potentiometerAngle(potentiometerReading));
            stringLength = strlen(str);
            uartUsb.write(str, stringLength);
            break;
        }
    }
}

float potentiometerAngle(float potentiometerReading)
{
    return ( (potentiometerReading - 0.5) * 6 * 360);
}
