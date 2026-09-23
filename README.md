# SPELUNKER

## What is it?

Spelunker is a tool used to find Unity Library folders, making it easier to find unused projects wasting space.

## Example

$ spelunker D:\Projects

Path: "D:\Projects\OldPrototype" size: 4.2 GiB last written: 312 days ago
Path: "D:\Projects\TowerDefense" size: 8.7 GiB last written: 2 days ago


## Download

Prebuilt binaries are available under [Releases](../../releases).

On Linux, make the file executable after downloading:

chmod +x spelunker


On Windows, SmartScreen may warn about an unsigned executable. Click "More info" and then "Run anyway".

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