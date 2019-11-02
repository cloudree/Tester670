//
// Tester 670
//

#include <Arduino.h>
#include "Common.h"
#include "Debug.h"

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

void Write670( byte addr, byte data )
{
    Write( addr, 2, pin_WAddr );
    Write( data, 4, pin_WData );

    digitalWrite( pin_WE, LOW );
    delay(1);
    digitalWrite( pin_WE, HIGH );
}

byte Read670( byte addr )
{
    Write( addr, 2, pin_RAddr );
    
    digitalWrite( pin_RE, LOW );
    byte ret = Read( 4, pin_RData );
    digitalWrite( pin_RE, HIGH );
    
    return ret;
}

void setup() 
{
    DebugInit();

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
    DBGPAUSE();
}
