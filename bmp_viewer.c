#include<stdio.h>
#define N  netc+=
#define N4 netc+= 4*



int print_pixel(unsigned char byte)
{
//	printf("|%02X\n|",byte);
	unsigned char left_nibble = (byte & 0xF0) >> 4;
	unsigned char right_nibble = byte & 0x0F;

//	printf(":::|%02X|%02X|%02X|\n",byte,left_nibble,right_nibble);

	unsigned int nibble = left_nibble;
	int flag = 0;
HERE:
	switch (nibble)
	{
		case 0:
			printf("\033[40m  ");break;// 	black
		case 1:
			printf("\033[41m  ");break;//	red
		case 3:
			printf("\033[43m  ");break;//	brown
		case 2:
			printf("\033[42m  ");break;//	green
		case 4:
			printf("\033[44m  ");break;//	blue
		case 5:
			printf("\033[45m  ");break;//	magenta
		case 6:
            printf("\033[46m  ");break;//	cyan
        case 7:
            printf("\033[100m  ");break;//	light grey
        case 8:
            printf("\033[47m  ");break;// 	dark grey
        case 9:
            printf("\033[101m  ");break;//	light red
        case 10:
            printf("\033[102m  ");break;//	light green
		case 11:
			printf("\033[103m  ");break;//	yellow
		case 12:
            printf("\033[104m  ");break;//	light blue
        case 13:
            printf("\033[105m  ");break;//	light magenta
        case 14:
            printf("\033[106m  ");break;//	 light cyan
        case 15:
            printf("\033[107m  ");break;//	white
	}
if(flag == 0)
{
	flag = 1;
	nibble = right_nibble;
	goto HERE;
}
	
	printf("\033[0m");
	return 0;
}

int main(int argc, char ** argv)
{


	unsigned tff = 255;
	printf("the last value: %c",tff);
//	unsigned char a = 16;
//	printf("hexa of %c : %X\n",a,a);

	if (argc < 2)
	{
		printf("Please provide a file input\n");
		return 0;
	}

	
	printf("Opening the file:%s\n",argv[1]);

	FILE * fptr = fopen(argv[1],"r");

	int line_count = 1;
	unsigned char c = '\0';
	unsigned char buf[16]; 
	unsigned char limit32 = 31;
	int count = 0;
	int netc = 0;
	printf("\n%5i: ",line_count++);

	while(fscanf(fptr,"%c",&c) != -1)
	{
		buf[count] = c;
		printf("%02X ",c);
		
		count++;
	
		if (count == 16)
		{
			printf("\t");
			for(int i=0;i< 16;i++)
			{	
				if(buf[i] <= 31)
				{
					printf(".");
					continue;
				}
				printf("%c",buf[i]);
			}

			count = 0;
			printf("\n%5i: ",line_count);
			line_count++;

		}
	//	printf("%02X ",c);

	}
	char tab = '\t';
	int padding = (16*3)-(count*3);
	printf("%*c",padding,tab);
	
	for (int i=0;i < count ;i++)
	{
		if (buf[i] <= 31)
		{
			printf(".");
			continue;
		}
		printf("%c",buf[i]);
	}

	printf("\n");

	fclose(fptr);
	
	printf("\n=======DISCRIPTION OF THE %s========\n",argv[1]);

	unsigned char B, M ,f,s,t,fr;
	unsigned int size=0, DIB_size =0, image_height =0, image_width =0;
	unsigned char dummy1=0;
	unsigned short int dummy2=0;
	unsigned int dummy4=0;

	fptr = fopen(argv[1],"r");
	
	unsigned char * vptr = (void *)&size;
	unsigned int pixel_start_byte = 0;

	N fscanf (fptr,"%c%c",&B,&M); if (B == 'B' && M == 'M') printf("File format: BMP\n");
	N fscanf (fptr,"%c%c%c%c",&f,&s,&t,&fr);

	printf ("the size:%02X %02X %02X %02X\n",f,s,t,fr);

	//fscanf(fptr,"%c%c%c%c",(vptr+3),(vptr+2),(vptr+1),(vptr)); printf("The size of BMP file:%d\n",size);

				    printf("s:%X\n",size);
	size = size | fr;size <<= 8;printf("s:%X\n",size);
	size = size | t; size <<= 8;printf("s:%X\n",size);
	size = size | s; size <<= 8;printf("s:%X\n",size);
	size = size | f;	    printf("s:%X\n",size);
	

	printf("the size(d):%u\n",size);	

	fseek(fptr,-4,SEEK_CUR);
	fread(&dummy4,4,1,fptr); printf("< %08X >\n",dummy4);

	N4 fread(&dummy4,	   4,1,fptr); //printf("|%8X|",dummy1);
	N4 fread(&pixel_start_byte,4,1,fptr);
	N4 fread(&DIB_size,	   4,1,fptr);
	N4 fread(&image_width,	   4,1,fptr);
	N4 fread(&image_height,	   4,1,fptr);

	printf("start of the pixel x:%X  d:%u\n",pixel_start_byte,pixel_start_byte);
	printf("DIB header size: %u\n",DIB_size);
	printf("image width:%u\n",image_width);
	printf("image height:%u\n",image_height);

	//fptr = fptr + (pixel_start_byte - netc);	
	fseek(fptr,0,SEEK_END);
	

	int col_count = 0, row_count = 1, loop = 1;
	unsigned char * bptr = ((void *)&dummy4);

	int row_start = (image_width/2);

	while (1)
	{
		fseek(fptr,-1*row_start*row_count,SEEK_END);

		for (col_count=0;col_count< image_width; col_count+=2)
		{
			fread(&dummy1,1,1,fptr);
			print_pixel(dummy1);
		}
		printf("\n\r");
		row_count++;
		if(row_count > image_height)
		{
			break;
		}
	}
	
	printf("total bytes red : %i\n",netc);

	fclose(fptr);

	return 0;
}
