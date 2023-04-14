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
| <kbd>H</kbd> | Move Left |
| <kbd>J</kbd> | Move Down |
| <kbd>K</kbd> | Move Up |
| <kbd>L</kbd> | Move Right |

## TODO

- [x] Add score window;
- [ ] Code refactoring.
