#include "wlan.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int bufferLength = 255;

int main() {
    system(CMD);
    FILE* fp = fopen("wlan.txt", "r");
    if (fp != NULL) {
        wlanAnalyse(fp);
        fclose(fp);
    }
    else
        printf("Error: wlan.txt file doesn't exist!\n");
    fclose(fp);
    return 0;
}

int wlanCount(FILE* fp) {
    char *token;
    char buffer[bufferLength];
    int countValue;
    for (int i = 0; i < 3; i++) {
        fgets(buffer, bufferLength, fp);
    } 
    token = strtok(buffer," ");

    for (int j = 0; j < 2; j++) {
        token = strtok(NULL, " ");
    }
    countValue = atoi(token);
    return countValue;
}

LINE_TYPE whatLine(char* buffer) {
    if (strstr(buffer, "BSSID") != NULL) {
        return BSSID;
    }
    if (strstr(buffer, "SSID") != NULL) {
        return SSID;
    }
    if (strstr(buffer, "Signal") != NULL) {
        return SIG;
    }
    if (strstr(buffer, "Channel") != NULL) {
        return CH;
    }
    return UNKNOWN;
}

void wlanAnalyse(FILE *fp) {
    int a = wlanCount(fp);
    printf("Found %d WLANs\n", a);
    int linesCount = 1;
    char c;
    while((c=fgetc(fp))!=EOF) {
        if(c=='\n')
        linesCount++;
    }
    rewind(fp);

    ssid *ssidList = (ssid *)malloc(sizeof(ssid) * a);
    
    char buffer[bufferLength];
    int ssidCounter=0;
    int bssidCounter=0;
    for (int i=0; i < linesCount; i++) {
        fgets(buffer, bufferLength, fp);
        switch (whatLine(buffer))
        {
        case SSID:
            bssidCounter = 0;
            strcpy(ssidList[ssidCounter].ssid, readValue(buffer));
            printf("ESSID: %s\n", ssidList[ssidCounter].ssid);
            ssidCounter++;
            break;
        case BSSID: 
            strcpy(ssidList[ssidCounter].aplist[bssidCounter].apmac, readValue(buffer));
            strtok(ssidList[ssidCounter].aplist[bssidCounter].apmac, "\n");
            printf("\tAP %d MAC: %s  ", bssidCounter+1,ssidList[ssidCounter].aplist[bssidCounter].apmac);
            bssidCounter++;
            break;
        case SIG:
            strcpy(ssidList[ssidCounter].aplist[bssidCounter].signalStrength, readValue(buffer));
            strtok(ssidList[ssidCounter].aplist[bssidCounter].signalStrength, "\n");
            printf("Signal: %s  ",ssidList[ssidCounter].aplist[bssidCounter].signalStrength);
            break;
        case CH:
            strcpy(ssidList[ssidCounter].aplist[bssidCounter].channel, readValue(buffer));
            printf("Channel: %s\n",ssidList[ssidCounter].aplist[bssidCounter].channel, readValue(buffer));
            break;
        default:
            break;
        }
    }
    free(ssidList);
}

char* readValue(char* buffer) {
    char *arg = strchr(buffer, ':');
    if (arg != NULL)
        arg++;
    return arg;
}

