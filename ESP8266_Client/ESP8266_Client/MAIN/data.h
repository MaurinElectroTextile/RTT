#ifndef __DATA_H__
#define __DATA_H__

typedef struct {
  struct {
    double fossil_ratio;
    double nuclear_ratio;
    double renewable_ratio;
  } energy;
  struct {
    double temp;
    double temp_min;
    double temp_max;
    int cond_id;
  } weather;
} data_t;

enum {
  DATA_TODAY,
  DATA_TOMORROW,
  DATA_YESTERDAY,
  DATA_COUNT
};

extern data_t data[];

extern bool fetchData(int when);

#endif /*__DATA_H__*/
