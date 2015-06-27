# libqexec - Lib Quick Exec for Java
A faster Runtime.exec for Java

### How does it work?
Native libraries of course. It simply calls `popen()` for you in a C library.

### How to use it.
Simple. Download or compile the library under the `native/`. Then integrate the Java source with yours. On your java app startup, add the flag `-Djava.library.path="/path/to/library` so the program can find the native library.

Static methods in `QExec`:

`public static String exec(String cmd, int bufSize)`
Executes the command as specified:
- `String cmd`. This is a string containing the command you would like to execute
- `int bufSize`. This is the buffer size for when building the output string in the C lib. Just use `QExec.DEFAULT_BUFFER_SIZE`.
- Returns the String containing the output of the command.

`public static void execToConsole(String cmd)`
Executes the command and outputs the output of the command to the `System.out`
- `String cmd`. A string containing the command you would like to execute

`public static void execToNull(String cmd)`
Does the same as `execToConsole` except it appends `> /dev/null`/`> NUL`, therefore not outputting to the console. Don't use this if the command contains `|` or `>`.
