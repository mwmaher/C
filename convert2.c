/* convert2.c

   By Michael W. Maher

   Ver 1.0 10/1/90
   Ver 1.1  6/4/91

   The following program converts a file and writes it to a new file.

   usage: CONVERT2 [infilespec]

   The conversion process:
      1) All ASCII_RETURN char and ASCII_LINE_FEED char are converted
	 to a SPACE.
      2) all of the first 10 characters of the alloy label are converted
	 to spaces.
      3) a new line character is used as a delimiter between records.

   Version 1.1 now supports wildcard characters.
*/

/* include files */
#include<conio.h>
#include<dos.h>
#include<graph.h>
#include<process.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* constants */
#define ASCII_TAB 9
#define ASCII_LINE_FEED 10
#define ASCII_FORM_FEED 12
#define ASCII_RETURN 13

#define BLOCK1_SIZE 83
#define TYPE_SIZE 17

/* globals */
FILE *infileptr;
FILE *outfileptr;

/* function prototypes */
void main(int argc, char **argv);
void process_block1(char *block1);
void process_type(char *type);
void convert_file(FILE *infileptr, FILE *outfileptr);


void main(int argc, char **argv)
  {
  struct find_t fileinfo_in,
		fileinfo_out;
  unsigned      in_find_flag = 1,
		out_find_flag = 1;
  char          drive[_MAX_DRIVE],
		dir[_MAX_DIR],
		ext[_MAX_EXT],
		fname[_MAX_FNAME],
		ftemp[_MAX_FNAME],
		outfilename[_MAX_DRIVE + _MAX_DIR + _MAX_FNAME + _MAX_EXT];

  if ((argc != 2) || (strcmp(argv[1], "?") == 0))
    {
    printf("\nConvert2 By Michael W. Maher  Ver 1.1  6/4/91\n"
	   "\nUsage: CONVERT2 infilespec");
    return;
    }
  in_find_flag = _dos_findfirst(argv[1], _A_NORMAL, &fileinfo_in);
  _splitpath(fileinfo_in.name, drive, dir, fname, ext);
  _splitpath(argv[1], drive, dir, ftemp, ext);
  _makepath(outfilename, drive, dir, fname, "TXT");
  out_find_flag = _dos_findfirst(outfilename, _A_NORMAL, &fileinfo_out);
  if (in_find_flag != 0)
    printf("\nNo matching files found.\n");
  while (in_find_flag == 0)
    {
    printf("\nSearching...");
    infileptr  = fopen(fileinfo_in.name, "rt");
    if (out_find_flag != 0)
      outfileptr = fopen(outfilename, "wt");
    else
      {
      printf("\n\aERROR: %s already exists!  (no conversion)", outfilename);
      outfileptr == NULL;
      }  /* end else */
    if ((infileptr != NULL) && (outfileptr != NULL))
      {
      printf("Converting...");
      convert_file(infileptr, outfileptr);
      fclose(infileptr);
      fclose(outfileptr);
      printf("\n[%s] -> [%s]", fileinfo_in.name, outfilename);
      }  /* end if */
    in_find_flag = _dos_findnext(&fileinfo_in);
    _splitpath(fileinfo_in.name, drive, dir, fname, ext);
    _splitpath(argv[1], drive, dir, ftemp, ext);
    _makepath(outfilename, drive, dir, fname, "TXT");
    out_find_flag = _dos_findfirst(outfilename, _A_NORMAL, &fileinfo_out);
    }  /* end while */
  printf("\nAll done.");
  return;
  }  /* end main */


void convert_file(FILE *infileptr, FILE *outfileptr)

  {
  char block1[BLOCK1_SIZE+1],
       numb_type_str[3],
       type[TYPE_SIZE+1];
  int  numb_type, j;

  while (fread((void *) block1,
	 sizeof(char),
	 BLOCK1_SIZE,
	 infileptr) == BLOCK1_SIZE)
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
      }  /* end for */
    fwrite("\n", sizeof(char), 1, outfileptr);
    }  /* end while */
  return;
  }


void process_block1(char *block1)
  {
  int i;

  for (i = 0; i < BLOCK1_SIZE; i++)
    {
    if ((block1[i] == ASCII_RETURN) || (block1[i] == ASCII_LINE_FEED))
      block1[i] = ' ';
    }  /* end for */
  return;
  }  /* end function */


void process_type(char *type)
  {
  /* replace the first 10 characters with spaces (remove alloy code) */
  int i;

  for (i = 0; i < 10; i++)
    {
    type[i] = ' ';
    }  /* end for */
  for (i = 0; i < TYPE_SIZE; i++)
    {
    if ((type[i] == ASCII_RETURN) || (type[i] == ASCII_LINE_FEED))
      type[i] = ' ';
    }  /* end for */
  return;
  }  /* end function */


