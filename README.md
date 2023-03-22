This is a program used only for didactic purposes in which computational efficiency was not thought of.
This program is capable of printing the bits of an input file into an output file, as well as generating a binary from a sequence of characters "0" and "1".

To compile, just do `gcc main.c -o binary_name`.

To execute, there are two possible parameters:\

`./binary -b input_file output_file`

The `-b` parameter is for printing the bits as text in the output file.

\

`./binary -f input_file output_file`

If the input file has only "0" and "1" characters, each character is converted to a bit, so that a sequence of eight characters forms a one-byte binary sequence that is written to the output file.
