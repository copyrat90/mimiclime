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

### Setting up debugger

[See this guide.](https://felixjones.co.uk/mgba_gdb/vscode.html)

### Using stats viewer

Open [`libs/iso-butano/tools/ibn_stats.lua`](libs/iso-butano/tools/ibn_stats.lua) with `Debug > Script Window` in [MesenCE](https://github.com/nesdev-org/MesenCE).
