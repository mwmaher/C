/* remhplb.c

   By Michael W. Maher
   Ver 1.0: 12/17/92

   DESCRIPTION:

   SYNOPSIS:

   NOTES:
*/

#include<memory.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/**************************** type definitions *****************************/

/******************************* constants *********************************/
#define OUT_REC_SIZE 1
#define FALSE 0
#define TRUE 1

/****************************** global data ********************************/


void main(int argc, char **argv);
void convert_empl(char *infilename, char *outfilename);

void main(int argc, char **argv)
  {
  fprintf(stdout, "\n"
		  "RemHPLB.C By Michael W. Maher\n"
		  "Ver 1.0: 12/17/92\n"
		  "This program will remove all strings of the form"
		  "(LB?;) from a file.\n");
  if(argc == 3)
    convert_empl(argv[1], argv[2]);
  else
    fprintf(stdout, "\nParameters: infile outfile\n");
  return;
  }


void convert_empl(char *infilename, char *outfilename)
  {
  int  state = 0;
  char inbuf[OUT_REC_SIZE+1],
       outbuf[OUT_REC_SIZE+1];
  FILE *infile,
       *outfile;

  memset(inbuf, '\0', OUT_REC_SIZE+1);
  fprintf(stdout, "\nConverting file...\n\n");
  if ((infile = fopen(infilename, "rt")) == NULL)
    fprintf(stderr, "ERROR: can not open source file.\n");
  else
    {
    if ((outfile = fopen(outfilename, "wt")) == NULL)
      fprintf(stderr, "ERROR: can not open destination file.\n");
    else
      {
      fprintf(stdout, "Writing to the destination file...\n");
      inbuf[1] = '\0';
      while (fread(inbuf, sizeof(char), OUT_REC_SIZE, infile) == OUT_REC_SIZE)
	{
	if (inbuf[0] == 'L')
	  {
	  state = 1;
	  inbuf[0] = '\0';             /* eat 'L' character */
	  }
	else if ((inbuf[0] == 'B') && (state == 1))
	  {
	  state = 2;
	  inbuf[0] = '\0';             /* eat 'B' character if follow 'L' */
	  }
	else if (state == 2)
	  {
	  state = 3;
	  inbuf[0] = '\0';             /* eat char following "LB" */
	  }
	else if (state == 3)
	  {
	  state = 0;
	  inbuf[0] = '\0';             /* eat char following "LB?" */
	  }
	if (inbuf[0] == 'D')
	  {
	  state = 1;
	  inbuf[0] = '\0';             /* eat 'D' character */
	  }
	else if ((inbuf[0] == 'I') && (state == 1))
	  {
	  state = 2;
	  inbuf[0] = '\0';             /* eat 'I' character if follow 'D' */
	  }
	else if (state >= 2)
	  {
	  state += 3;
	  inbuf[0] = '\0';             /* eat char following "DI" */
	  }
	else if (state == 3)
	  {
	  if (inbuf[0] = ';')
	    state = 0;
	  inbuf[0] = '\0';
	  }
	/* write out the data record */
	fwrite(inbuf, sizeof(char), strlen(inbuf), outfile);
	}
      }
    }
  fclose(infile);
  fclose(outfile);
  fprintf(stdout, "Conversion completed.\n\n");
  return;
  }


