# Line Editor Documentation

This is a terminal-based line editor written in C.

## Available Commands

| Command | Usage | Description | Example |
| :--- | :--- | :--- | :--- |
| **P** | `P` | Displays all lines in the document with numbers | `P` |
| **I** | `I <line> <text>` | Inserts text at specified line number | `I 1 Hello World` |
| **D** | `D <line>` | Deletes the line at specified line number | `D 1` |
| **S** | `S <filename>` | Saves in-memory document to a text file | `S output.txt` |
| **L** | `L <filename>` | Loads document from a text file | `L output.txt` |
| **Q** | `Q` | Quits the program | `Q` |
