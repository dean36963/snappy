# Snappy
A simple program to import, organise and browse photos.

## Requirements
Binaries are provided for Windows/Mac/Linux, which should work out the box.
If you want to build yourself from source, you'll need ``Qt``(5) and ``libexif``.
Qt Creator will be able to build from that, but if you want to build in the command line, you'll need to run the following code.

```bash
qmake
make
./snappy
```
Also, if you are running on a Mac, you may need to add an include library path to the project file. I found that I had to copy the libexif library to a separate path, and then add that path to the ``INCLUDEPATH`` variable, as other libraries conflicted with what Qt Creator was using.

