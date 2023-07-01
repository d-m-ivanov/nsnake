# Nsnake

__Nsnake__ is an implementation of well known __Snake__ game with ncurses library.

## Build

__Dependencies__:
- GNU make;
- [Ncurses](https://invisible-island.net/ncurses/) library.

### Arch Linux

```bash
$ sudo pacman -S ncurses
$ make
```

### Debian

```bash
$ sudo apt-get install libncurses5-dev libncursesw5-dev
$ make
```

## Controls

| Key | Description |
| --- | --- |
| <kbd>Q</kbd> | Quit |
| <kbd>A</kbd> | Move Left |
| <kbd>S</kbd> | Move Down |
| <kbd>W</kbd> | Move Up |
| <kbd>D</kbd> | Move Right |
