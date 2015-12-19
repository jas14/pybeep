#include <Python.h>

#define DEFAULT_LENGTH  100     /* milliseconds */
#define DEFAULT_FREQ    440.0   /* Middle A */
#define SPKR_CYCLES     1193180 /* ~~ magic ~~ */

typedef enum { BEEP_TYPE_CONSOLE, BEEP_TYPE_EVDEV } beep_type_t;

PyObject *pybeep_beep(PyObject *self, PyObject *args);

beep_type_t console_type;
