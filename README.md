Baselibc
========
This is a very simple libc for embedded systems. Mainly geared for 32-bit microcontrollers in the 10-100kB memory range.
The library compiles to less than 5kB total on Cortex-M3, and much less if some functions aren't used.

The code is based on klibc and tinyprintf modules. License is therefore currently GPL.

However, tinyprintf author has agreed to relicense under BSD, and I think I have removed all the GPL parts from klibc.
Therefore it should be possible to relicense to BSD by just double-checking all the source files used.
