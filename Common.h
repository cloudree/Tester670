/*
 * Common.h
 * by cloudree
 *
 */

#define PRODUCT       "=-=-=-= Tester_670 =-=-=-="
#define MAJOR_VERSION "0"
#define MINOR_VERSION "1"
#define VERSION       ("v" MAJOR_VERSION "." MINOR_VERSION)

#define _DEBUG
// 91% is safe : 120544
// 92% has error : 121192

// Global --------------
const int pin_WData[4] = { A1, A3, A2, A0 };
const int pin_RData[4] = { 6, 7, 8, 9 };

const int pin_WAddr[2] = { 2, 3 };
const int pin_RAddr[2] = { 10, 12 };

const int pin_WE = 4;
const int pin_RE = 5;
