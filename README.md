# Jackpot
## Introduction
This is a slot machine game implementation in the terminal, written in C language using POSIX threads.

The multi-threaded architecture is as follows:
- One thread to control the game
- One thread to manage the display
- One thread per wheel to make it spin

## How to play
The game is played using POSIX signals on UNIX architectures. You use a `SIGSTP (CTRL+Z)` to insert a coin, a `SIGINT (CTRL+C)` to stop a wheel, and a `SIGQUIT (CTRL+\)` to quit the game cleanly.
