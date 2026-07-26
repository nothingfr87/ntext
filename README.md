# NTEXT

NText is a simple, and lightweight text editor fully written in c

---

## Features

NText doesn't have a lot of features, just a simple and lightweight text editor like any editor, and it uses the same layout as nano!

NText is keyboard-focused, more keyboard keybinds will be added

    - Ctrl+S: Save
    - Ctrl+Q: Quit

---

## Installation

### Requirements

- GCC
- NCURSES
- pkg-config
- make

To install them:

```bash
sudo apt update
sudo apt install build-essentials pkg-config libncurses5-dev libncursesw5-dev
```

#### Fedora Distros

```bash
sudo dnf groupinstall "Development Tools"
sudo dnf install ncurses-devel pkgconf-pkg-config
```

#### Arch Distros

```bash
sudo pacman -S base-devel ncurses pkgconf
```

Now, clone the repository and build the project:

```bash
git clone https://github.com/nothingfr87/ntext.git
cd ntext

make build
```

The compiled binary will now be available in the project directory.

To install ntext system-wide:

```bash
sudo make all install
```

It'll be installed in `/usr/local/bin` by default, you can edit that in the [Makefile](Makefile)

---

## Issues:

If you encounter any bugs or unexpected behavior, please open an issue. Feedback and contributions are always appreciated.

---

## License

This project is licensed under the [GPLv3 License](LICENSE)
