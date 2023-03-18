#include <GL/gl.h>
#include <stdio.h>
//make#include <alloc.h>
#include <stdlib.h>
#include "Texture.h"


unsigned LoadTexture(char *FileName, int Mode)
{
	unsigned char *Data;
    unsigned char type[4];
    unsigned char info[7];
    int Bits;
    FILE *s;
	int Width,Height;
	unsigned TexId;
	int i,j;

    if (!(s = fopen (FileName, "r+bt"))) return false;
    fread (&type, sizeof (char), 3, s);
    fseek (s, 12, SEEK_SET);
    fread (&info, sizeof (char), 6, s);
    if (type[1] != 0 || (type[2] != 2 && type[2] != 3))	return false;
    
    Width = info[0] + info[1] * 256; 
    Height = info[2] + info[3] * 256;
    Bits =	info[4];
	
	glGenTextures(1, &TexId);
	glBindTexture (GL_TEXTURE_2D, TexId);
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Mode);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Mode);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	switch(info[4])	{

	    case 32:
			Data = (unsigned char*) malloc (Width*Height * 4); 
			fread (Data, sizeof (unsigned char), Width*Height * 4, s);
			for (j=0; j<Height; j++) {
				for (i=0; i<Width; i++) {
        			unsigned char t = Data[(i+j*Width)*4];
					Data[(i+j*Width)*4] = Data[(i+j*Width)*4+2];
					Data[(i+j*Width)*4+2] = t;
				}
			}
			glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data);
			break;

		case 24:
			Data = (unsigned char*) malloc (Width*Height * 3); 
			fread (Data, sizeof (unsigned char), Width*Height * 3, s);
			for (j=0; j<Height; j++) {
				for (i=0; i<Width; i++) {
					unsigned char t = Data[(i+j*Width)*3];
					Data[(i+j*Width)*3] = Data[(i+j*Width)*3+2];
					Data[(i+j*Width)*3+2] = t;
				}
			}
			glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, Data);
			break;
	}
	
	free(Data);
	return TexId;
}
