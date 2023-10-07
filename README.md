# Prizewheel
A program to randomly pick a winner from those in your squad which were close enough to be logged in ArcDPS.
## Installation
- Option 1. The easiest method is to copy the precompiled executable to someplace in your path.  This is what most people should do.
- Option 2. The harder method is to download the source and compile it with Visual Studio.  It has only been tested with Visual Studio 2022 on a Windows 11 machine.  It is a `CMake` project that uses `vcpkg` so theoretically, it should be easy for someone who knows what those are to build.  If not, stick with option 1.

## How to use it
All the examples here assume `prizewheel.exe` is in your path.  If it isn't, then you will need to specify the full path to the `prizewheel.exe` file when running it.
- Open a terminal.
- Locate the latest `.etcv` or `.zetcv` file that you want to pick the winner from.
- Run the following where <filename> is the name of the file located above.
  ```bash
  prizewheel <filename>
  ```
- Example - Assumes `prizewheel.exe` is in your path.
  ```bash
  C:\wvw_logs> prizewheel 20230925-235127.zevtc
  The lucky winner is [23] Deathwizh$ ./prizewheel.exe 20230925-235127.zevtc
  Attempting to decompress.
  28 Friendly Characters
  0 - Lakeshow Domination
  1 - Dan Gleasak
  2 - Dark Mode Firefly
  3 - Dragon Mchawkk
  4 - Reina Iceheart
  5 - Fin Ishinner
  6 - Nasta Yoda
  7 - Iced Coffee King
  8 - Sir Drogen
  9 - Romeriser
  10 - Penguin Protektor
  11 - Vigil Moon
  12 - T├¡assa Lyorn
  13 - Bad Name Machine
  14 - Bluegrasse
  15 - S├║nny Side Up
  16 - Unr├⌐k
  17 - Yochan├ín
  18 - Susanna Serqet
  19 - Graivant
  20 - Streey
  21 - Sic Dim Sum
  22 - Sno Bueno
  23 - Deathwizh
  24 - Arkonn
  25 - Rule Raucus
  26 - Agile The Cutpurse
  27 - Aryafire
  Spinning.....
  The lucky winner is [4] Reina Iceheart
  ```


## Notes
- There is no warranty, expressed or implied.  
- Use it at your own risk.  That said it should be safe.  It doesn't attempt to make any network connections and the only files it opens are those you tell it to.  The source is published for your review.  
- If you find any bugs, feel free to let me know and I'll see what I can do.
