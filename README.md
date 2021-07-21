# Narthex
PAX 2.0: Narthex (Greek: Νάρθηξ, νάρθηκας) is a modular & minimal password recovery suit for Unix and Unix-like operating system written in C. It contains autonomous programs for the creation of a personalised dictionaries that can be used for password recovery & offensive security assessment. The programs make use of Unix text streams for the collaboration with each other, according to the Unix philosophy. It is licensed under the GPL v3.0. Under development!

# The tools
+ Nenchanc  -  A capitalization tool that appends the results to the bottom of the dictionary (stdout).
+ Ninc      -  A incrementation tool that multiplies alphabetical lines and appends an n++ at the end of each line.
+ Ncom      -  A combination tool that creates different combinations between the existing lines of the dictionary.
+ Nrev      -  A reversing tool, that appends the reserved versions of the lines at the end of the dictionary.
+ Nleet     -  A leetifier. Replaces characters with Leet equivalents, such as @ instead of a, or 3 instead of e. Also appends
+ Nuniq     -  A uniq utility that uses minimal memory and works for unsorted files (as dictionaries are sorted by likelyhood, not alphabetically)
+ Nwiz      -  A wizard that asks for the infromation and combines the tools together to create a final dictionary.
+ N-Woran   -  A wordlist analyzer for leaks. It compares to known dictionaries, notes common words & character, char combinations & popularity.
