## [**Original README here**](https://github.com/MusicPlayerDaemon/MPD)

A personal fork that fixes a few Windows-specific quirks:
- Compiles with FLAC support that's been missing from official binaries since 0.24.8 [#2536](https://github.com/MusicPlayerDaemon/MPD/issues/2536)
- ~Compiles with mpg123, so MP3 files' tags are parsed using libid3tag instead, avoiding an ancient ffmpeg bug where id3v2.4 multi-value tags are truncated (https://trac.ffmpeg.org/ticket/6949)~ merged upstream
- Bumps libid3tag from 0.15.1b to 0.16.4
- Gracefully handles process shutdown without losing state file.
- wasapi output fixes: [#1408](https://github.com/MusicPlayerDaemon/MPD/issues/1408) [#1880](https://github.com/MusicPlayerDaemon/MPD/issues/1880)
- Properly handles database updates between restarts, not forcing full rescan due to mtime mismatch.

## Building

Cross-compile from Linux using the same approach as upstream:
https://github.com/MusicPlayerDaemon/MPD/blob/master/doc/user.rst#compiling-for-windows

Jobs are capped at 4 to make building on WSL feasible without dedicating a lot of RAM to the VM.

```sh
pacman -S --needed mingw-w64-toolchain meson ninja cmake nasm pkg-config quilt gperf autoconf automake libtool
```

```sh
git clone --depth 1 https://github.com/0x0003/MPD
cd MPD && mkdir -p output/win64 && cd output/win64
../../win32/build.py --64 --buildtype=release -Dwrap_mode=forcefallback
strip mpd.exe
```

The resulting `mpd.exe` is at `output/win64/mpd.exe`.

