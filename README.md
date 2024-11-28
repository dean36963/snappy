# Snappy
A simple program to import, organise and browse photos.

![Screen of snapshot showing the event view page](res/eventview.png?raw=true)

## Status
Just written as a side project for fun. Currently just runs on Linux but should also work on Mac if the right libraries are installed. Windows is currently untested.

## Requirements
If you want to build yourself from source, you'll need ``Qt5`` and ``eviv2``.
Linker options may need to be changed for different operating systems, uncomment the appropriate sections in the snappy.pro file.
Qt Creator will be able to build from this project easily enough but if you want to build in the command line, you'll need to run the following code.

```bash
qmake
make
./snappy
```
Also, if you are running on a Mac, you may need to add an include library path to the project file. I found that I had to copy the library to a separate path, and then add that path to the ``INCLUDEPATH`` variable, as other libraries conflicted with what Qt Creator was using.

