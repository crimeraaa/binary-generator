# Overview

This is a simple command-line program that just generates multiple text files.

Each of these text file list out the full ranges of their respective integer type and bit size.

Do note that there are separate files for unsigned and signed.

> Why no 32-bit and 64-bit numbers?

My default text viewer is Notepad, so I can't even begin to write files that represent the full range of those!

Notepad only reads up to the 65 536th line. 32-bit integers generally represent a range of 4.2 billion numbers, so yeah...

# Usage

No command-line arguments needed!

```powershell
.\binary
```

# Compiling

Download `binary.c` and open your terminal, then make sure the working directory is where this file is located.

Then use your preferred C compiler and your system's executable extension. 

I'm on Windows 10 using `gcc` and executables have the `.exe` extension, so I run the following:

```powershell
gcc .\binary.c -o .\binary.exe
```

`clang` should have a similar command:

```powershell
clang .\binary.c -o .\binary.exe
```
