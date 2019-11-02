/*
 *  Debug.h in Twelve
 *  by cloudree@naver.com
 *  
 */

#ifdef _DEBUG

#define SERIAL_SPEED    57600
void DebugInit();

void DBG(String msg);
void DBGHEX(long int data);
void DBG(int num);
void DBGLN(String msg);
void DBGHEXLN(long int data);
void DBGLN(int num);
void Dump(uint8_t len, uint8_t *buf);
void DBGPAUSE();

#else  // _DEBUG

# define DebugInit()
# define DBG(a)
# define DBGHEX(a)
# define DBGHEXLN(a)
# define DBGLN(a)
# define Dump(a,b)
# define DBGPAUSE()

#endif  // _DEBUG
