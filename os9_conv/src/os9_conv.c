/*
 * os9_conv.c
 *
 * Apple ][ "The Mill" OS9 DSK image to OS9 RBF format (and back) converter
 *
 *  Created on: 07 gen 2017
 *      Author: Luca Ridarelli
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRACKS 35                               /* There are 35 tracks in an Apple ][ standard floppy disk */
#define SECTORS 16                              /* 16 sectors per track */
#define BYTES_SECTOR 256                        /* 256 bytes per sector */
#define TOTAL_BYTES TRACKS*SECTORS*BYTES_SECTOR /* counting a total of 14560 bytes */


/* Functions  prototypes */

void convert_to_OS9( char source[TRACKS][SECTORS][BYTES_SECTOR],char dest[TRACKS][SECTORS][BYTES_SECTOR], int interleave[SECTORS]);

void convert_to_apple( char source[TRACKS][SECTORS][BYTES_SECTOR],char dest[TRACKS][SECTORS][BYTES_SECTOR], int interleave[SECTORS]);

void show_help();

/* Main entry point */

int main(int argc, char *argv[])
{
  /* Buffers to hold the source and destination dsk images */
  char source_buffer[TRACKS][SECTORS][BYTES_SECTOR];
  char destination_buffer[TRACKS][SECTORS][BYTES_SECTOR];

  /* The Apple ][ "The Mill" disk sector interleave translation table*/

  int apple_interleave[SECTORS] = {0x00,0x0C,0x02,0x07,0x04,0x09,0x0E,0x0B,
                              0x01,0x06,0x03,0x08,0x0D,0x0A,0x05,0x0F} ;

  /* Variables to hold the user provided arguments */
  char* source_file_name;
  char* destination_file_name;
  char* option ;

  /* The actions to perform */
  enum action {toNone, toMILL, toOS9};
  enum action convert = toNone;

  /* Input and output standard file structures */
  FILE *source_file;
  FILE *destination_file;


  /* Check the number of arguments and grab them */
  if (argc==4)
    {
      source_file_name=argv[1];
      destination_file_name=argv[2];
      option=argv[3];
    }
  else
    { if (argc==1)
      {
	printf("\nApple ][ \"The Mill\" <-> OS9 RBF DSK converter V 1.0 - 2017 Luca Ridarelli\n\n"
	         "DSK disk images must origin from Apple ][ \"The Mill\" OS9\n\n");
      }
      show_help();
      return(EXIT_FAILURE);
    }

  /* check the <option> argument and choose an action */
  if (strcmp(option,"-a")==0)
    {
      convert=toMILL;
    }
  else
    if (strcmp(option,"-o")==0)
      {
	convert=toOS9;
      }
    else
      {
	printf("\nERROR! Wrong Option. \n\n");
	show_help();
	return(EXIT_FAILURE);
      }


  /* Try to open the source file */
 if ((source_file=fopen(source_file_name,"rb"))==NULL)
   {
     printf("\nERROR! Unable to Open Source File.\n");
     exit(EXIT_FAILURE);
   }

  /* Try to read the whole file in memory */
 if (fread(source_buffer,TOTAL_BYTES,1,source_file) != 1)
   {
     printf("\nERROR! Unable to read Source File.\n");
     exit(EXIT_FAILURE);

   }

  /* execute the requested action */
 switch(convert)
  {
   case toOS9:   convert_to_OS9(source_buffer,destination_buffer,apple_interleave);
                 break;

   case toMILL: convert_to_apple(source_buffer,destination_buffer,apple_interleave);
                 break;

   default :     printf("\nERROR! Wrong Option.\n\n");
	         show_help();
	         return(EXIT_FAILURE);

  }

 /* Try to open the destination file */
  if ((destination_file=fopen(destination_file_name,"wb"))==NULL)
    {
      printf("\nERROR! Unable to Open Destination File.\n");
      exit(EXIT_FAILURE);
    }

  /* Try to write the whole buffer to the destination file */
  if (fwrite(destination_buffer,TOTAL_BYTES,1,destination_file) != 1)
    {
      printf("\nERROR! Unable to Write Destination File Write.\n");
      exit(EXIT_FAILURE);
    }

  /* Success! Close all files and exit */
  fclose(source_file);
  fclose(destination_file);
  return(EXIT_SUCCESS);
}


/*
 * Convert_to_OS9
 *
 * Creates a copy, in OS9 RBF format, of the Apple ][ The mill DSK image suppressing the sector interleave and
 * exchanges track 0 sectors 0 and 0x0f since , in the Apple Os9 "The Mill" disk, sector 0
 * holds 6502 boot code and sector 0x0f the OS9 "identification sector" that , instead , should
 * be located at OS9 LSN0 (track 0 sector 0 in our case).
 */

void convert_to_OS9( char source[TRACKS][SECTORS][BYTES_SECTOR],char dest[TRACKS][SECTORS][BYTES_SECTOR], int interleave[SECTORS])
{
  for(int track=0;track<TRACKS;track++)
    {
      for(int sector=0;sector<SECTORS;sector++)
       {
         for(int byte=0;byte<BYTES_SECTOR;byte++)
     	  {
     	    dest[track][sector][byte]=source[track][interleave[sector]][byte];
	  }
        }
    }
  for(int byte=0;byte<BYTES_SECTOR;byte++)
    {
      dest[0][0][byte]=source[0][SECTORS-1][byte];
      dest[0][SECTORS-1][byte]=source[0][0][byte];
    }
 return;
}

/*
 * Convert_to_apple
 *
 * Creates the Apple ][ The mill DSK image resuming the sector interleave and
 * exchanging track 0 sectors 0 and 0x0f  (see Convert_to_OS9).
 * Note that onvert_to_apple assumes that the source file is in OS9 format BUT always
 * originated from an Apple ][ OS9 "The Mill" image. In other words, to obtain a regular
 * Apple ][ OS9 "The Mill" image, track 0 sector 0xF should always contain the 6502 boot code.
 *
*/

void convert_to_apple( char source[TRACKS][SECTORS][BYTES_SECTOR],char dest[TRACKS][SECTORS][BYTES_SECTOR], int interleave[SECTORS])
{
  for(int track=0;track<TRACKS;track++)
    {
      for(int sector=0;sector<SECTORS;sector++)
       {
         for(int byte=0;byte<BYTES_SECTOR;byte++)
     	  {
     	    dest[track][interleave[sector]][byte]=source[track][sector][byte];
	  }
        }
    }
  for(int byte=0;byte<BYTES_SECTOR;byte++)
    {
      dest[0][0][byte]=source[0][SECTORS-1][byte];
      dest[0][SECTORS-1][byte]=source[0][0][byte];
    }
  return;
}

/*
 * show_help
 *
 * shows the help message
 */
void show_help()
{
  printf("Syntax : os9_conv <source file> <destination file> <option>\n\n"
         "Options: -a (convert OS9 dsk image to Apple ][ \"The Mill\" format)\n"
         "         -o (convert Apple ][ \"The Mill\" OS9 DSK image to OS9 format)\n");
    return;
}

