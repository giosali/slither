# Building

## Fedora

On Fedora, the following must be run to get started:

```sh
sudo dnf install gcc-c++ libinput-devel libudev-devel libevdev-devel
```

Your package manager might install `libevdev-devel` in `/usr/include/libevdev-1.0/libevdev`. If that's the case, create a symlink to that directory to avoid build errors:

```sh
sudo ln -s /usr/include/libevdev-1.0/libevdev /usr/include/libevdev
```

# Coding Style

[Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
