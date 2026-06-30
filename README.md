# mimiclime

mimiclime is a top-down exploration game for the Game Boy Advance,\
where you play as a slime who becomes a monster it devours.


## Setup

### Setting up build environment

1. Setup dependencies for Butano with [devkitARM](https://gvaliente.github.io/butano/getting_started.html) or [Wonderful Toolchain](https://gvaliente.github.io/butano/getting_started_wt.html).
   * Butano itself is included as a submodule, so you don't need to manually download it.
1. **Recursively** clone this repo.
1. `pip install -r libs/butano-ldtk/requirements.txt`
1. That's it, you can now run `make -j$(nproc)` to build the project.

### Finding include paths with VSCode C/C++ extension

[See this gist.](https://gist.github.com/copyrat90/eee49d92846ca3585a69d5bea001710d)

* Change the `"cppStandard"` to `"c++26"`.
* Add `"BN_DMG_AUDIO_SYNC"` to `"commonDefines"`.

### Setting up debugger

[See this guide.](https://felixjones.co.uk/mgba_gdb/vscode.html)

### Using stats viewer

Open [`libs/iso-butano/tools/ibn_stats.lua`](libs/iso-butano/tools/ibn_stats.lua) with `Debug > Script Window` in [MesenCE](https://github.com/nesdev-org/MesenCE).


## Edit

### Editing levels

To edit the levels, open [`levels/mimiclime.ldtk`](levels/mimiclime.ldtk) with [LDtk](https://ldtk.io/) v1.5.3

Just saving the LDtk project is enough, the build process automatically takes care of the importing.

### Editing characters

To edit the characters, open [`characters/mimiclime/`](characters/mimiclime/) directory with [GBAForge](https://github.com/DarkKodKod/GBAForge).

Release Version 1.0.0 is rather old, so you need to build GBAForge yourself.\
**Comment out** [this line](https://github.com/DarkKodKod/GBAForge/blob/133e502e141390326b3609ac6d3f806be809de04/GBATool/Utils/Utils.cs#L306) before building,
so that the generated source doesn't have a timestamp.

After editing a character, you need to re-generate the source.\
Pressing **F5** or `Project > Build Project...` will do the trick.
