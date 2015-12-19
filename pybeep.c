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
    // open console
    int console_fd;

    if ((console_fd = open("/dev/tty0", O_WRONLY)) == -1) {
        console_fd = open("/dev/vc/0", O_WRONLY);
    }
    if (console_fd == -1) {
        perror("open");
        printf("hello\n");
        putchar('\a');
        Py_RETURN_NONE;
    }

    // determine console sound capabilities
    if (ioctl(console_fd, EVIOCGSND(0)) != -1) {
        console_type = BEEP_TYPE_EVDEV;
    } else {
        console_type = BEEP_TYPE_CONSOLE;
    }

    // start beep
    do_beep(console_fd, DEFAULT_FREQ);

    // stop beep
    usleep(1000*DEFAULT_LENGTH);
    do_beep(console_fd, 0);

    // close console
    close(console_fd);
    Py_RETURN_NONE;
}
