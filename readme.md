# pybeep

This extension requires Python 3 (will not build via pip with Python 2).


## Install

- `python3 -m pip install --user ~/git/pybeep` or replace ~/git/pybeep with a zip or URL to a zip.

- The user running `python3` must have write access to `/dev/tty0` such as via:
```
sudo usermod -a -G dialout $USER
sudo usermod -a -G tty $USER
```

Otherwise, the following error is expected:
```
open: No such file or directory
beep
```


## Use
```Python
import pybeep
pybeep.beep(220, 500)
# ^ frequency (Hz), duration (ms)
```

If the tty is not available or not writeable, the console will say "beep" and Python will attempt to write `\a`, but will do nothing if tty0 is not writeable.


## Known issues

In Debian 10 the "beep at..." message displays after re-login, but Python does not generate a beep and still says:
```
ioctl: Operation not permitted
ioctl: Operation not permitted
```

unless the program runs as root.

This is not specific to this program. The issue also occurs with the "beep" command (which works only as root even after adding to dialout and tty and rebooting) after installing the "beep" package.

See also:
- <https://github.com/NixOS/nixpkgs/issues/31112>
- <https://lists.opensuse.org/opensuse-de/2002-03/msg00054.html>
- <https://lists.debian.org/debian-user-de/2001/04/msg00703.html>
- <https://bugs.gentoo.org/168201> (fixed in Gentoo, apparently)


## Authors
- [jas14](https://github.com/jas14)
- [Poikilos](https://github.com/poikilos)
