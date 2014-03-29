# Print Linux laptop battery status

## Usage

`battery [-s]`

### Option

-s: Print in compact mode, can be used with *tmux*, *zsh*, etc.

## Setup

Please attach the battery to your laptop before compiling `battery`.

Download the source code and chdir to the directory. Type `make` to compile
the program into a file `battery`.

## Why don't use a script-based solution?

I use this program to display battery status in tmux statusbar. The status
refreshes very often, so I hope it can be cheaper to get the battery state.  To
see the difference, type the folloing command in `bash` to measure how long it
takes to run `battery` 1000 times:

```bash
time for i in `seq 1 1000`; do ./battery > /dev/null; done
```

Search for other script-based solutions online (battery.py, battery.sh, ...)
and do the same thing to them. Compare the result and you will see the savings.
