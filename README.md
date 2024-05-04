# pipex
7th project of 42 school

file1 cmd1 cmd2 file 2
the output of the cm1 is passed as input for the cmd 2
file 2 store the answer


I have to create a pipe like in this command:
< infile ls -l | wc -l > outfile
./pipex infile "ls -l" "wc -l" outfile

- < infile = an existing file and his value is redirect to the standard input (fd 0)
- ls -l | = a command to display a list of elements in the current dir
but the list is not display because the pipe store the output in fd (1),
the standard output
- wc -l = a command to count the number of line and display that, 
but it's not display because it's the store in outfile
- > outfile = an existing or non existing file or to store the output
the number of line of the output of ls -l command.
