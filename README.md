# FindIdenticalDirectoryEntries
This program search through a directory structure.
All duplicate files are written to a text file, as is their directory location.
Files are determined duplicate by content, size and name.
As the program launches, a user is asked to specify a diretory, if no directory or an invalid directory is entered,
the program will return an approriate error message and use the programs dicretory as default.

Currently I'm working on refactoring. 
I'm aiming to make the classes less coupled, and also do something about the giant struct construction in the header file.
I made this program in a week, 
at the time I was more concerned it making it work then actually future proofind and applying proper software engineering practices.
