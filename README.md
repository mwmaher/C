#Metallurgy File Converter - C
	This document is to accompany CONVERT1.c

	CONVERT1.c was written by Michael W. Maher

	What does CONVERT1.c do?

	  1) Converts all occurances of LINE FEED and CARRIAGE RETURN
	     to a SPACE. 

	  2) Converts all of the ten character alloy labels in the file
	     to spaces.

	  3) A new-line character is used as a delimiter between records.

	  4) If the conversion is incomplete due to a file creation or
	     opening error the program will give an error message.

	  5) If the conversion is successful a message will be displayed.


	How do you use it?

	  1) You can use the default file names and convert
	     INCVRT.DAT to OUTCVRT.DAT by typing:

	     A> CONVERT1


	  2) You may convert your own files by employing the command-line
	     parameters.

	     Parameters: file name of file to be converted
			 file name of file to be created from converted data

	     EXAMPLE:  A> CONVERT1 infile.dat outfile.dat

	     The previous call will convert a file named infile.dat to
	     a file named outfile.dat.

