# Spelunker

Reclaim disk space from old Unity projects.

Spelunker scans a directory tree for Unity projects and lists each one's `Library` folder by size, along with how long ago the project was last touched. Pick the ones you don't need and it deletes them.

Unity regenerates `Library` the next time you open the project, so removing it costs nothing but a longer import. On a drive with a few dozen old projects this routinely frees tens of gigabytes.

## Example

```
$ spelunker D:\

[1]: size: 3.0 GiB | Last written: 187 days ago | Path: D:\Projects\SpaceShooter
[2]: size: 2.6 GiB | Last written: 92 days ago  | Path: D:\noirMetroidvania
[3]: size: 2.5 GiB | Last written: 113 days ago | Path: D:\Ball_Tilt
[4]: size: 2.2 GiB | Last written: 26 days ago  | Path: D:\3d-gamejam

enter the [number] for each library to be deleted
1 3
Are you sure you want to delete these? [y/N]
y
D:\Projects\SpaceShooter\Library was deleted
Deleted: 24193 files, freed 3.0 GiB
D:\Ball_Tilt\Library was deleted
Deleted: 19882 files, freed 2.5 GiB
Do you want to continue? [y/N]
```

## Usage

```
spelunker <path>
```

`<path>` is where the search starts. Projects are listed largest first — enter the numbers you want cleaned, separated by spaces, and confirm.

Only the `Library` folder is removed. Nothing else in the project is touched, and a project showing `0.0 B` has already been cleaned (or was never opened).

After each round the list is redrawn so you can keep going without rescanning.

**Close Unity first.** Files held open by the editor can't be deleted, and cloud-synced folders (OneDrive, Dropbox) may refuse for the same reason.

## How it works

A directory counts as a Unity project when it contains both `Assets` and `ProjectSettings/ProjectVersion.txt`. Spelunker stops descending once it finds one, so it never walks through `Assets`.

It also skips directories that never contain projects — `steamapps`, `node_modules`, `.git`, `Windows`, `Program Files` and similar — which is what makes scanning a whole drive practical. A 2 TB drive takes about 90 seconds.

## Install

Prebuilt binaries are under [Releases](../../releases). Statically linked, no dependencies.

**Windows** — download `spelunker-windows-x86_64.exe` and run it from PowerShell:

```
.\spelunker-windows-x86_64.exe D:\Projects
```

SmartScreen warns about unsigned executables: *More info* → *Run anyway*. Double-clicking won't work — it needs a path as an argument.

**Linux** — download `spelunker-linux-x86_64`:

```
chmod +x spelunker-linux-x86_64
./spelunker-linux-x86_64 ~/Unity
```

**Either** — to run it as just `spelunker` from anywhere, rename the binary and move it to a folder on your `PATH` (`~/.local/bin` on Linux).

## Build from source

Requires CMake 3.15+ and a C++20 compiler.

```
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

## License

MIT
