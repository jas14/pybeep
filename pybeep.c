#include <Python.h>
#include <fcntl.h>
#include <linux/kd.h>
#include <linux/input.h>
#include "pybeep.h"

void do_beep(int console_fd, float freq)
{
    if (console_type == BEEP_TYPE_EVDEV) {
        struct input_event e;
        e.type = EV_SND;
        e.code = SND_TONE;
        e.value = freq;

        if (write(console_fd, &e, sizeof(e)) < 0) {
            perror("write");
            putchar('\a');
        }
    } else {
        int period = (freq == 0 ? 0 : (int)(SPKR_CYCLES/freq));
        if (ioctl(console_fd, KIOCSOUND, period) < 0) {
            perror("ioctl");
            putchar('\a');
        }
    }
}

PyObject *
pybeep_beep(PyObject *self, PyObject *args)
{
    // PyObject *frequency = NULL; // Py_None
    // PyObject *duration = NULL; // Py_None
    // ^ causes a Segmentation fault at Py_INCREF, PyFloat_Check, or
    //   PyFloat_AsDouble! Only use PyObject for "O" format in
    //   PyArg_ParseTuple
    //   (See <https://dfm.io/posts/python-c-extensions/>).

    // See <https://docs.python.org/3/extending/extending.html>:
    float frequency = DEFAULT_FREQ;
    float duration = DEFAULT_LENGTH;
     if (!PyArg_ParseTuple(args, "|ff", &frequency, &duration)) {
          return NULL;
    }

    // open console
    int console_fd;

    if ((console_fd = open("/dev/tty0", O_WRONLY)) == -1) {
        console_fd = open("/dev/vc/0", O_WRONLY);
    }
    if (console_fd == -1) {
        perror("open");
        // printf("beep\n");
        putchar('\a');
        Py_RETURN_NONE;
    }

    // determine console sound capabilities
    if (ioctl(console_fd, EVIOCGSND(0)) != -1) {
        console_type = BEEP_TYPE_EVDEV;
    } else {
        console_type = BEEP_TYPE_CONSOLE;
    }

    // printf("beep at %fHz for %fms\n", frequency, duration);
    // start beep
    do_beep(console_fd, frequency);

    // stop beep
    usleep(1000*duration);
    do_beep(console_fd, 0);

    // close console
    close(console_fd);
    Py_RETURN_NONE;
}
