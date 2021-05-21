#ifndef WLAN_H
#define WLAN_H

#include <stdio.h>
#include <stdlib.h>

#define CMD "netsh wlan show networks mode=bssid > wlan.txt"
// enum LINE_TYPE {UNKNOWN = -1, SSID, NET, AUTH, ENCRYP, BSSID, SIG=10, RADIO, CH};

struct ap {
    char apmac[20];
    int signalStrength;
    int channel;
};
struct ssid{
    char ssid[30];
    int numAp;
    struct ap aplist[20];
};

int wlan_count(FILE*);
void wlan_analyse(FILE* fp);
int wlan_number(char*);
char* read_value(char*);
int what_line(char*);
void show_wlan(struct ssid*, int);
void takeAwayNewLine (char*);

#endif 