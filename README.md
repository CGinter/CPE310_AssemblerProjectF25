# CPE310 Assembler Project Fall 2025
Red Team (Caden Ginter, Rachel Ogbonna, Victoria Marston, Chase Sprigle)'s submission for the CPE310 assembler project in Fall 2025 at WVU

This project implements a basic MIPS assembler supporting a subset of the MIPS instruction set.

## Welcome to the MIPS Translatron 3000

The MIPS Translatron 3000 is back, and it now supports most of the MIPS instruction set! The program is now more maintainable, more flexible, and more adaptable. A quick tour of the code:

### include.h

include.h contains all of the includes for the program. Every file includes it, which prevents a mess of includes in our source files.

### main.c

main.c runs the user interface and runs the appropriate parsers to handle user input and output. The primary logic for its interface is stored in util.c's `get_next_input` function, which runs a finite state machine to emulate Old Jim's original user interface. Extending this interface is a simple as adding and implementing a new state (the interactive debugger uses this flexibility).

### util.*

util.c (& util.h) contain multiple utilities used across the program. Most important of these is the `get_next_input` function, which hides the complexity of traversing the finite state machine (FSM) and returns both the next line of user input and the terminating state of the FSM.

### consts.*

consts.c (& consts.h) contain the constant values used globally by the program. This includes the central table that maps all instructions to their format. This is the sole source of truth for information about instructions, which ensures self-consistency between our assembler and disassembler.

### parser.*

parser.c (& parser.h) contain the logic that interprets lines of assembly language. It generates the internal instruction format that the other commands use to create machine code.

### gen\_assm.*

gen\_assm.c (& gen\_assm.h) contain the function that builds assembly from the internal instruction format. This is used to disassemble machine code.

### assm\_to\_mach.* & mach\_to\_assm.*

These files contain the logic that uses the table to convert between our internal instruction format and machine code format. They are used by other parts of the program to support all types of conversion.

## Compile

### POSIX-style system (Linux/MacOS)

 - Run `./compile`
 - The executable is `./bin/interpreter`

### Windows system

 - Run `.\compile.ps1` in a Powershell terminal (standard CMD not supported)
 - The executable is `.\bin\interpreter.exe`

## Running and Usage

In each command replace `{executable}` with your actual executable path (likely `.\bin\interpreter.exe` or `./bin/interpreter`).

### Legacy Interactive Mode

Run the executable with no arguments, `{executable}`, to access the traditional legacy interactive mode. This works identically to Old Jim's version, except that the main menu now has a new option. Selecting option `(4) Corrupted Code Inspector` opens the debugger that can be used to analyze a corrupted machine instruction. Simply enter a machine code instruction in binary (without spaces) and see all possible bit flips for inspection.

### Assemble a File

You can assemble a full assembly file by using auto mode with the `-a` flag. You can do so like: `{executable} -a {path-to-assembly}`. An example that is included in our repository: `{executable} -a ./tests/test1.asm` (Windows users should flip forward slashes to back slashes), which will output the compiled machine code for the assembly in that file to standard output.

### Disassemble a File

You can also disassemble a full machine code file, where the machine code is written out directly as ASCII 0s and 1s on newlines. You can view `./tests/test1.bin` for an example. Disassembly is similar to regular assembling, `{executable} -a -r {path-to-machine}`. An example you can run in our repository is `{executable} -a -r ./tests/test1.bin`, which will output the assembly for the machine code in `./tests/test1.bin`.

### Advanced Usage

On a POSIX-compliant system (Windows mileage may vary), the program supports some advanced usage. If you fail to specify a filename with the `-a` flag, the program will read directly from standard input. This still bypasses the user interface, and reads input like it is a file. This allows some very interesting shenanigans (again, Windows mileage may vary, screenshot in `shenanigans.png`). The following command effectively does nothing: `./bin/interpreter -a ./tests/test1.asm | ./bin/interpreter -a -r`. It assembles the instructions in `test1.asm` then it passes the machine code it made to itself again. The second copy of the program disassembles that code and prints the original assembly, effectively undoing its own work. In principle this could be used to directly output compiled programs to a command that programs a physical chip with the code or a simulator to test the code.
