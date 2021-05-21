#ifndef WLAN_H
#define WLAN_H

#include <stdio.h>
#include <stdlib.h>

#define CMD "netsh wlan show networks mode=bssid > wlan.txt"
typedef enum LINE_TYPE {UNKNOWN = -1, SSID, NET, AUTH, ENCRYP, BSSID, SIG=10, RADIO, CH} LINE_TYPE;

typedef struct {
    char apmac[20];
    char signalStrength[3];
    char channel[5];
}ap;

typedef struct {
    char ssid[30];
    int numAp;
    ap aplist[20];
}ssid;

int wlanCount(FILE*);
void wlanAnalyse(FILE* fp);
int wlanNumber(char*);
char* readValue(char*);
int whatLine(char*);
void showWlan(ssid*, int);
void takeAwayNewLine (char*);

#endif 