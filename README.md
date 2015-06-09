# Snappy
A simple program to import, organise and browse photos.

## Requirements
Binaries are provided for Windows/Mac/Linux, which should work out the box.
If you want to build yourself from source, you'll need ``Qt5`` and ``eviv2``.
Qt Creator will be able to build from that, but if you want to build in the command line, you'll need to run the following code.

```bash
qmake
make
./snappy
```
Also, if you are running on a Mac, you may need to add an include library path to the project file. I found that I had to copy the library to a separate path, and then add that path to the ``INCLUDEPATH`` variable, as other libraries conflicted with what Qt Creator was using.

## Outstanding development tasks

- [x] Make event folder listen for library changed events. I.e. so when the importer has completed, the event tree should update accordingly.
- [x] Make importer slightly more robust
- [x] Photo area should show one picture per event under whatever folder is selected.
- [x] Add right click menu for photo area
- [x] Zoom functionality in large photo mode.
- [ ] Fullscreen functionality in large photo mode.
- [ ] Make action to move photos to another event

## Nice to have things

- [ ] Download your google photos?
- [ ] Private mode?
