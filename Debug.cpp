/*
 *  Debug.cpp in Twelve
 *  by cloudree@naver.com
 *  
 */

#include <Arduino.h>
#include <String.h>

#include "Common.h"
#include "Debug.h"

#ifdef _DEBUG

static bool inited = false;

void DebugInit()
{
    Serial.begin( SERIAL_SPEED);

    // wait until teminal action
    //while ( !Serial.available() )
    //    continue;
    
    Serial.println( String(PRODUCT) + String(" ") + String(VERSION) );
    
    inited = true;
}

void DBG(String msg)          { if(inited) Serial.print(msg); }
void DBGHEX(long int data)    { if(inited) Serial.print( String(data, HEX) + " "); }
void DBG(int num)             { if(inited) Serial.print( String(num) + " "); }
void DBGLN(String msg)        { if(inited) Serial.println(msg); }
void DBGHEXLN(long int data)  { if(inited) Serial.println( String(data, HEX) + " "); }
void DBGLN(int num)           { if(inited) Serial.println( String(num) + " "); }

void Dump(uint8_t len, uint8_t *buf)
{
    if(!inited) return;
  	for (int i = 0; i<len; i++) {
    		Serial.print(buf[i], HEX);
        if( i % 32 == 31 )
            Serial.println("");
        else
    		    Serial.print(",");
  	}
  	Serial.println("");
}

void DBGPAUSE()
{
    while( Serial.available() == 0 );
    Serial.read();
}

#endif  // _DEBUG
