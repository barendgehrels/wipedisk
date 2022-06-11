# wipedisk

Wipes a disk by writing a BIG file and erasing it again.

There are several sources doing the same thing, but I wanted something simple,
useful, readable, controllable and working, so I wrote another version.

## Compiling

Compiling is trivial, it is one file and does not depend on anything else.

## Running

You can run it by specifying a filename, a size (in KiloBytes), and optionally 
a flag `--keep`. If you specify that, the BIG file is not erased (you can do
it yourself), such that you can inspect what is done, what is written, and how
much space is left.