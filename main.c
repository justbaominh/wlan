#include "wlan.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int bufferLength = 255;

int main() {
    system(CMD);
    FILE* fp = fopen("wlan.txt", "r");
    // if (fp != NULL) {
    //     wlan_analyse(fp);
    //     fclose(fp);
    // }
        // printf("Error: wlan.txt file doesn't exist!\n");
    int a = wlan_count(fp);
    printf("Found %d WLANs\n", a);
    wlan_analyse(fp);
/* Get the line number of text file*/

    fclose(fp);
    return 0;
}

int wlan_count(FILE* fp) {
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

int what_line(char* buffer) {
        if (strstr(buffer, "SSID") != NULL) {
            return 1;
        }
        if (strstr(buffer, "BSSID") != NULL) {
            return 2;
        }

        if (strstr(buffer, "Signal") != NULL) {
            return 3;
        }

        if (strstr(buffer, "Channel") != NULL) {
            return 4;
        }
}

void wlan_analyse(FILE *fp) {
    int linesCount = 1;
    char c;
    while((c=fgetc(fp))!=EOF) {
        if(c=='\n')
        linesCount++;
    }
    printf("Numbers of lines in text file: %d\n", linesCount);
    struct ssid *ssidList = (struct ssid *)malloc(sizeof(struct ssid) * wlan_count(fp));
    char buffer[bufferLength];
    for (int i=3; i < linesCount; i++) {
        fgets(buffer, bufferLength, fp);
        if (what_line(buffer) == 1) {
            printf("%s\n",read_value(buffer));
        }
        
    }
}
char* read_value(char* buffer) {
    char *arg = strchr(buffer, ':');
    if (arg != NULL)
        arg++;
    return arg;
}