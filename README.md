# SPELUNKER

## What is it?

Spelunker is a tool used to find Unity Library folders, making it easier to find unused projects wasting space.

## Example

$ spelunker D:\Projects

Path: "D:\Projects\OldPrototype" size: 4.2 GiB last written: 312 days ago



## Download

Prebuilt binaries are available under [Releases](../../releases).

### Windows

Download `spelunker-windows-x86_64.exe`, open PowerShell in the folder where it is saved, and run:

.\spelunker-windows-x86_64.exe D:\Projects


Windows SmartScreen may warn about an unsigned executable. Click "More info", then "Run anyway".

Double-clicking the file will not work — Spelunker is a command line tool and needs a path as an argument.

### Linux

Download `spelunker-linux-x86_64`, make it executable, and run it:

chmod +x spelunker-linux-x86_64
./spelunker-linux-x86_64 ~/Unity


### Running it from anywhere

To use the command without typing the full path, move the binary into a folder that is on your `PATH` — for example `~/.local/bin` on Linux — and rename it to `spelunker`.

## Usage

spelunker <path>


The path is the directory where the search starts. Spelunker searches recursively and stops descending once it finds a Unity project.

Example:

spelunker D:\


## Building from source

Requires CMake and a C++20 compiler.

cmake -B build
cmake --build build


The binary ends up in `build/`.