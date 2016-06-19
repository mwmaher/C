/* convert1.c

   Started 10/1/90 By Michael W. Maher

   The following program converts a file of the form in_file_rec to
   to the form out_file_rec and writes it to a new file.

   command line parameters:  in file name of file to be converted,
			     out file name of file to be created.



   The conversion process:
      1) All ASCII_RETURN char and ASCII_LINE_FEED char are converted
	 to a SPACE.
      2) all of the first 10 characters of the alloy label are converted
	 to spaces.
      3) a new line character is used as a delimiter between records.
*/

#include<graph.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<conio.h>

#define ASCII_TAB 9
#define ASCII_LINE_FEED 10
#define ASCII_FORM_FEED 12
#define ASCII_RETURN 13

#define BLOCK1_SIZE 83
#define TYPE_SIZE 17

FILE *infileptr;
FILE *outfileptr;

char infilename[255], outfilename[255];

void main(int argc, char **argv);
void process_block1(char *block1);
void process_type(char *type);

void main(int argc, char **argv)
  {
  char block1[BLOCK1_SIZE+1];
  char numb_type_str[3];
  char type[TYPE_SIZE+1];
  int numb_type, j;

  if (argc > 2)
    {
    strcpy(infilename, argv[1]);
    strcpy(outfilename, argv[2]);
    }
  else
    {
    strcpy(infilename, "incvrt.dat");
    strcpy(outfilename, "outcvrt.dat");
    }
  infileptr  = fopen(infilename, "rt");
  outfileptr = fopen(outfilename, "wt");
  if ((infileptr != NULL) && (outfileptr != NULL))
    {
    while (fread((void *) block1, sizeof(char),
	   BLOCK1_SIZE, infileptr) == BLOCK1_SIZE)
      {
      process_block1(block1);
      fwrite(block1, sizeof(char), BLOCK1_SIZE, outfileptr);

      fread(numb_type_str, sizeof(char), 2, infileptr);
      fwrite(numb_type_str, sizeof(char), 2, outfileptr);
      numb_type = atoi(numb_type_str);

      fread(numb_type_str, sizeof(char), 1, infileptr);
      fwrite(" ", sizeof(char), 1, outfileptr);

      for (j = 1; j <= numb_type; j++)
	{
	fread(type, sizeof(char), TYPE_SIZE, infileptr);
	process_type(type);
	fwrite(type, sizeof(char), TYPE_SIZE, outfileptr);
	}
      fwrite("\n", sizeof(char), 1, outfileptr);
      }
    fclose(infileptr);
    fclose(outfileptr);
    printf("\n The conversion of [%s] to [%s] is complete",
	    infilename, outfilename);
    }
  else
    printf("\n ERROR: The conversion of [%s] is NOT complete", infilename);
  return;
  }


void process_block1(char *block1)
  {
  int i;

  for (i = 0; i < BLOCK1_SIZE; i++)
    {
    if ((block1[i] == ASCII_RETURN) || (block1[i] == ASCII_LINE_FEED))
      block1[i] = ' ';
    }
  return;
  }


void process_type(char *type)
  {
  /* replace the first 10 characters with spaces (remove alloy code) */
  int i;

  for (i = 0; i < 10; i++)
    {
    type[i] = ' ';
    }
  for (i = 0; i < TYPE_SIZE; i++)
    {
    if ((type[i] == ASCII_RETURN) || (type[i] == ASCII_LINE_FEED))
      type[i] = ' ';
    }
  return;
  }
