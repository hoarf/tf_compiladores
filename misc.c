#include <stdio.h>


//src: http://www.c4learn.com/c-program-to-compare-two-textdata-files-in-c-programming.html
int misc_compareFiles(char * fname1, char * fname2)
{
	FILE *fp1, *fp2;
	int ch1, ch2;

	fp1 = fopen( fname1,  "r" );
	fp2 = fopen( fname2,  "r" );

	if ( fp1 == NULL )
	{
		printf("Cannot open %s for reading ", fname1 );
		return -1;
	}
	else if (fp2 == NULL)
	{
		printf("Cannot open %s for reading ", fname2 );
		return -1;
	}
	else
	{
		ch1  =  getc( fp1 ) ;
		ch2  =  getc( fp2 ) ;

		while( (ch1!=EOF) && (ch2!=EOF) && (ch1 == ch2))
		{
			ch1 = getc(fp1);
			ch2 = getc(fp2) ;
		}
		fclose ( fp1 );
		fclose ( fp2 );
		if (ch1 == ch2)
			return 1;
		else if (ch1 !=  ch2)
			return 0;
	}
}
