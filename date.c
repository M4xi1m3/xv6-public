// Print the current date

#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  struct date rtcdate;
  if (date(&rtcdate) < 0) {
    printf(1, "date: error\n");
  }

  printf(1, "%d-%d-%d %d:%d:%d\n", rtcdate.year, rtcdate.month, rtcdate.day, rtcdate.hour, rtcdate.minute, rtcdate.second);
  exit();
}
