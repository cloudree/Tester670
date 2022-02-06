/**
 * This is a tester for the 74x670 chip. 
 * 
 * The ’HC670 and CD74HCT670 are 16-bit register files
 * organized as 4 words x 4 bits each. Read and write address
 * and enable inputs allow simultaneous writing into one location
 * while reading another. Four data inputs are provided to store
 * the 4-bit word. The write address inputs (WA0 and WA1)
 * determine the location of the stored word in the register.
 * When write enable (WE) is low the word is entered into the
 * address location and it remains transparent to the data.
 * 
 * Changes:
 * 2022-02 - Use the onboard LED to show SUCCESS / FAILURE status
 *           This allows you to use the tester in the field without a serial terminal.
 *           Use white electrical tape to defuse the LED if they are too bright 
 *           for example on the Arduino NANO.
 */

#include <Arduino.h>
#include "Common.h"
#include "Debug.h"

/** 
 *  Writes a value pinCount bits long to the pins specified in the 3rd argument.
 */
void Write( byte value, int pinCount, int *pins )
{
#ifdef DEBUG_DETAIL  
    char buf[255];
    sprintf( buf, "W V[]=%x : ", value );
    DBG( buf );
#endif
    
    byte mask = 0x1;
    for( int i=0; i<pinCount; i++ )
    {
        int v = (value & mask) > 0 ? HIGH : LOW;
        mask <<= 1;

        digitalWrite( pins[i], v);
#ifdef DEBUG_DETAIL  
        DBG( v );
        DBG( "," );
#endif
    }
#ifdef DEBUG_DETAIL  
    DBGLN("");
#endif
}

/**
 * Reads value pinCount long from the pins specified in the 2nd argument.
 */
byte Read( int pinCount, int *pins )
{
#ifdef DEBUG_DETAIL  
    DBG( "R V[]=" );
#endif
    byte mask = 0x1, ret = 0;
    for( int i=0; i<pinCount; i++ )
    {
        int v = (digitalRead( pins[i] ) == LOW) ? 0 : 1;
        ret += (v * mask);
        mask <<= 1;
#ifdef DEBUG_DETAIL  
        DBG( v );
        DBG( "," );
#endif
    }
#ifdef DEBUG_DETAIL  
    DBG( ":" );
    DBGLN( ret );
#endif
    return ret;
}

/**
 * Write an data to a given address
 */
void Write670( byte addr, byte data )
{
    Write( addr, 2, pin_WAddr );
    Write( data, 4, pin_WData );

    // cycle the pin to initiate the write
    digitalWrite( pin_WE, LOW );
    delay(1);
    digitalWrite( pin_WE, HIGH );
}

/**
 * Read data from a given address
 */
byte Read670( byte addr )
{
    Write( addr, 2, pin_RAddr );
    
    
    // cycle the pin to initiate the read
    digitalWrite( pin_RE, LOW );
    byte ret = Read( 4, pin_RData );
    digitalWrite( pin_RE, HIGH );
    
    return ret;
}

void setup() 
{
    DebugInit();
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW

    pinMode( pin_WE, OUTPUT );
    pinMode( pin_WAddr[0], OUTPUT );
    pinMode( pin_WAddr[1], OUTPUT );

    pinMode( pin_RE, OUTPUT );
    pinMode( pin_RAddr[0], OUTPUT );
    pinMode( pin_RAddr[1], OUTPUT );
    
    for( int i=0; i<4; i++ )
    {
        pinMode( pin_WData[i], OUTPUT );
        pinMode( pin_RData[i], INPUT_PULLUP );
    }

    digitalWrite( pin_WE, HIGH );
    digitalWrite( pin_RE, HIGH );
}

void loop() 
{
    DBGLN("PHASE 1");
    // Store and check 2 different values in 4 addresses one address at a time. Total 8 checks for phase 1
    byte v[2] = { 0x5, 0xa };
    for( int i=0; i<2; i++ )
    {
        for( int a=0; a<4; a++ )
        {
            Write670( a, v[i] );
            if( Read670(a) != v[i] )
            {
                DBG( "Error at ");
                DBGHEXLN( a );
                DBGPAUSE();
            }
            else 
            {
                DBG(".");
            }
        }
    }

    DBGLN("\nPHASE 2");
    // Store and check 16 different values in 4 addresses one address at a time. Total 64 checks for phase 2
    for( int a=0; a<4; a++ )
    {
        for( int d=0; d<16; d++ )
        {
            Write670( a, d );
            if( Read670(a) != d )
            {
                DBG( "Error at ");
                DBGHEX( a );
                DBG( ", Value = ");
                DBGHEXLN( d );
                DBGPAUSE();
            }
            else 
            {
                DBG(".");
            }
        }
    }

    DBGLN("\nCompleted");
    digitalWrite(LED_BUILTIN, HIGH);   // on completion of the test turn the LED on.
    DBGPAUSE();
}
