///////////////////////////////////////////////////////////////////////
// Christopher Mitchell
// Linux Battery Level Checker
// May 13th, 2009
// http://www.cemetech.net
//
// This code isn't terribly groundbreaking, but please be respectful as
// far as reuse and modifications; credit me, or at least drop me an
// email to let me know you found my code helpful
///////////////////////////////////////////////////////////////////////

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define BATT_PATH "/sys/class/power_supply/BAT0/"
#define PATH_BATT_STATE BATT_PATH "status"
#define PATH_BATT_INFO BATT_PATH "info"
#define BATT_READ_BUFLEN 256

struct battstate {
  short unsigned int powerstate, time_hour, time_min;
  float chargelevel;
};

enum powerstates { // indicate charging or discharging
  POWER_CHARGING,
  POWER_CHARGED,
  POWER_DISCHARGING
};

int main(int argc, char *argv[]);
struct battstate *getBattState(void);

int main(int argc, char *argv[]) {
  struct battstate *thisstate;

  thisstate = getBattState();
  switch (thisstate->powerstate) {
  case POWER_CHARGING:
    printf("Battery is currently charging.\n");
    break;
  case POWER_CHARGED:
    printf("Battery is charged.\n");
    break;
  case POWER_DISCHARGING:
    printf("Battery is currently discharging.\n");
    break;
  default:
    printf("!!BUG!! Unrecognized power state returned.\n");
    exit(-1);
    break;
  }
  printf("Battery charge level is %f%%.\n", thisstate->chargelevel);
  if (thisstate->powerstate != POWER_CHARGED) {
    printf("Remainging %d:%d\n", thisstate->time_hour, thisstate->time_min);
  }
  return 0;
}

struct battstate *getBattState(void) {
  static struct battstate mybattstate;
  int battStateHandle;
  long int battRate_mA = 0;
  long int battMax_mAh = 0;
  long int battRemain_mAh = 0;
  char buffer[BATT_READ_BUFLEN];
  char tok_unit[8];
  int readoffset;
  short int readstate = 0, readlen = 0; // 0=reading,1=eol,2=eof

  if (-1 == (battStateHandle = open(PATH_BATT_INFO, O_RDONLY))) {
    perror("Could not open battery info for reading");
    exit(-1);
  }

  while (readstate < 2) {
    readoffset = 0;
    readstate = 0;
    while (!readstate) {
      if (0 > (readlen = read(battStateHandle, buffer + readoffset, 1))) {
        perror("Failed to read battery state");
        exit(-1);
      }
      if (!readlen) {
        readstate = 2;
        break;
      }
      if ('\n' == *(buffer + readoffset)) {
        readstate++;
        *(buffer + readoffset + 1) = '\0';
      }
      readoffset++;
    }
    if (readstate == 2)
      break;
    if (NULL != strstr(buffer, "last full capacity")) {
      if (0 >= sscanf(buffer + 25, "%ld %s", &battMax_mAh, tok_unit)) {
        perror("sscanf for battery capacity");
        exit(-1);
      }
      break;
    }
  }
  close(battStateHandle);

  if (-1 == (battStateHandle = open(PATH_BATT_STATE, O_RDONLY))) {
    perror("Could not open battery state for reading");
    exit(-1);
  }

  readstate = 0;
  while (readstate < 2) {
    readoffset = 0;
    readstate = 0;
    while (!readstate) {
      if (0 > (readlen = read(battStateHandle, buffer + readoffset, 1))) {
        perror("Failed to read battery state");
        exit(-1);
      }
      if (0 == readlen) {
        readstate = 2;
        break;
      }
      if ('\n' == *(buffer + readoffset)) {
        readstate++;
        *(buffer + readoffset + 1) = '\0';
      }
      readoffset++;
    }
    if (readstate == 2)
      break;
    if (NULL != strstr(buffer, "charging state")) {
      if (NULL != strstr(buffer, "discharging"))
        mybattstate.powerstate = POWER_DISCHARGING;
      else if (NULL != strstr(buffer, "charged"))
        mybattstate.powerstate = POWER_CHARGED;
      else
        mybattstate.powerstate = POWER_CHARGING;
    } else if (NULL != strstr(buffer, "present rate")) {
      if (0 >= sscanf(buffer + 25, "%ld %s", &battRate_mA, tok_unit)) {
        perror("sscanf for battery rate failed");
        exit(-1);
      }
    } else if (NULL != strstr(buffer, "remaining capacity")) {
      if (0 >= sscanf(buffer + 25, "%ld %s", &battRemain_mAh, tok_unit)) {
        perror("sscanf for battery capacity");
        exit(-1);
      }
    }
  }
  close(battStateHandle);

  // printf("%ld, %ld, %ld\n",battRemain_mAh,battMax_mAh,battRate_mA);
  mybattstate.chargelevel =
      100.00 * ((float)battRemain_mAh / (float)battMax_mAh);
  if (battRate_mA) {
    mybattstate.time_hour = floor(battRemain_mAh / battRate_mA);
    mybattstate.time_min =
        floor(60 * (((float)battRemain_mAh / (float)battRate_mA) -
                    mybattstate.time_hour));
  }
  return &mybattstate;
}
