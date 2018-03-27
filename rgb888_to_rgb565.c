#include <stdio.h>
#include <stdint.h>

int main()
{
	FILE *fptrw, *fptr;
   	fptrw = fopen("lowercaseRGB565.c","w");
   	fptr = fopen("lowercaseRGB888.txt","r");

	fprintf(fptrw, "static const uint16_t pic_Energia_logo_100_132_bmp[] = {\n");

    int r, g, b;
    uint16_t red, green, blue, rgb;
    int count = 1;

    int totalc = 1;


    do 
    {        
        fscanf (fptr, "%d\t%d\t%d", &r, &g, &b);      

		red = (r << 8) & 0xf800;
		
		green = (g << 3) & 0x07e0;
		
		blue = (b >> 3);
		
		rgb = red | blue | green; 
		
		fprintf(fptrw, "0x%04x, ", rgb);

		totalc++;

      	if(++count > 12)
      	{
      		count = 1;
			fprintf(fptrw, "\n");      		
      	}      	

    } while (!feof (fptr));

    printf("%d", totalc);

    fprintf(fptrw, "};");

}