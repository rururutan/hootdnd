
# hoot DnD tool

`hootdnd` is a tool that supports playing chiptune music files on [hoot](http://dmpsoft.s17.xrea.com/hoot/)

## Usage

> hootdnd filename

## Support format

* MDX (X68000 MXDRV)
* MND (X68000 MNDRV)
* MGS (MSX MGSDRV)
* BGM (MSX KINRO5)
* MPK (MSX MPK)
* PT3 (Vortex Tracker)
* SPC (SNES Sound Format)
* NSF/NEZ (NES Sound Format)
* KSS (Konami Sound System)
* AY  (AY)
* GBS/GBR (GameBoy DMG Sound Format)
* HES (PC-Engine Hudson Entertainment System)

Supports files defined with the bind tag in hoot.xml.

## Build

> cmake -S . -B build
> cmake --build build --config Release

## License

MIT

