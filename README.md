# Spelunker

Find and clean up Unity `Library` folders. Spelunker scans a directory tree for Unity projects, shows how much space each one's `Library` folder takes and when the project was last worked on, and lets you delete the ones you don't need.

`Library` is regenerated automatically by Unity the next time you open the project, so deleting it is safe — it only costs you a longer import on the next open. On a drive with a few dozen old projects this usually frees tens of gigabytes.

## Example

```
$ spelunker D:\

[1]: size: 3.0 GiB | Last written: 187 days ago | Path: D:\Projects\SpaceShooter
[2]: size: 2.6 GiB | Last written: 92 days ago | Path: D:\noirMetroidvania
[3]: size: 2.5 GiB | Last written: 113 days ago | Path: D:\Ball_Tilt
[4]: size: 2.2 GiB | Last written: 26 days ago | Path: D:\3d-gamejam

enter the [number] for each library to be deleted
1 3
Are you sure you want to delete these? [y/N]
y
D:\Projects\SpaceShooter\Library was deleted
D:\Ball_Tilt\Library was deleted
```

## Usage

```
spelunker <path>
```

The path is where the search starts. Spelunker descends recursively and stops as soon as it finds a Unity project, so pointing it at a whole drive works — it just takes longer.

Projects are listed largest first. Enter the numbers of the ones you want cleaned, separated by spaces, then confirm. Only the `Library` folder is removed; nothing else in the project is touched.

## Download

Prebuilt binaries are available under [Releases](../../releases). No dependencies — download and run.

### Windows

Download `spelunker-windows-x86_64.exe`, open PowerShell where it is saved, and run:

```
.\spelunker-windows-x86_64.exe D:\Projects
```

SmartScreen may warn about an unsigned executable. Click "More info", then "Run anyway".

Double-clicking does nothing useful — Spelunker is a command line tool and needs a path as an argument.

### Linux

```
chmod +x spelunker-linux-x86_64
./spelunker-linux-x86_64 ~/Unity
```

### Running it from anywhere

Move the binary into a folder on your `PATH` — `~/.local/bin` on Linux, or any folder you've added on Windows — and rename it to `spelunker`. Then you can just run `spelunker <path>` from anywhere.

## Building from source

Requires CMake 3.15+ and a C++20 compiler.

```
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

The binary ends up in `build/`.
