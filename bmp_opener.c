#include "types.h"
#include "user.h"
#include "stat.h"
#include "memlayout.h"

#define N  netc+=
#define N4 netc+= 4*

int X = 0;
unsigned short * vga_buf = (unsigned short *)P2V(0xB8000);
int FD = -1;


int printx(unsigned char byte)
{
	unsigned char nibble[2];
	 
	nibble[0] = (byte & 0xF0)>>4;
	nibble[1] = byte & 0x0F;

	for(int i=0;i<2;i++)
	{	switch (nibble[i])
		{
			case 0:printf(1,"0");break;
			case 1:printf(1,"1");break;
			case 2:printf(1,"2");break;
			case 3:printf(1,"3");break;
			case 4:printf(1,"4");break;
			case 5:printf(1,"5");break;
			case 6:printf(1,"6");break;
			case 7:printf(1,"7");break;
			case 8:printf(1,"8");break;
			case 9:printf(1,"9");break;
			case 10:printf(1,"A");break;
			case 11:printf(1,"B");break;
			case 12:printf(1,"C");break;
			case 13:printf(1,"D");break;
			case 14:printf(1,"E");break;
			case 15:printf(1,"F");break;
		}
	}
	return 0;
}

int print_pixel(int x, int y, unsigned char byte)
{
	unsigned char nibble[2];
	int space = 0x00000020;
	nibble[0] = byte & 0xF0;
	nibble[1] =(byte & 0x0F)<<4;

	for (int i=0;i<2;i++) 
	{
		if 		(nibble[i] == 0x10) nibble[i] = 0x40;
		else if (nibble[i] == 0x40) nibble[i] = 0x10;
		else if (nibble[i] == 0x90) nibble[i] = 0xC0;
		else if (nibble[i] == 0xC0) nibble[i] = 0x90;
		else if (nibble[i] == 0x60) nibble[i] = 0x30;
		else if (nibble[i] == 0x30) nibble[i] = 0x60;
		else if (nibble[i] == 0xB0) nibble[i] = 0xE0;
		else if (nibble[i] == 0xE0) nibble[i] = 0xB0;
		else if (nibble[i] == 0x70) nibble[i] = 0x80;
		else if (nibble[i] == 0x80) nibble[i] = 0x70;
		
	}
	vgaprint(x,y,nibble[0],space);vgaprint(x,y+1,nibble[0],space);
	vgaprint(x,y+2,nibble[1],space);vgaprint(x,y+2+1,nibble[1],space);

//	printf(1,"x:%d y:%d\n",x,y);




// //	int l1l = 0x000000F0, l1r = 0x00000042;
	// //int full1 = (l1l<<8) | l1r;
// 
// //	vgaprint(16+x,16+y,l1l,l1r);
// //	printx(1,"%d|",print_result);
// 
// //	int print_result = -1;
// 
// //	for(int i=0;i<2;i++)
	// int i=0;
	// {
		// vgaprint(x,y+0*2,	(int)(nibble[i]),space);//	printf(1,"%d|",print_result);
	// 
// //		vgaprint(x,y+1+0*2,(int)(nibble[i]),space);//	printf(1,"%d|",print_result);
	// }
	// i=1;
	// {
		// vgaprint(x,20+y+1*2,	(int)(nibble[i]),space);//	printf(1,"%d|",print_result);
	// 
// //		vgaprint(x,20+y+1+1*2,(int)(nibble[i]),space);//	printf(1,"%d|",print_result);
	// }
	
	return 0;
}

//opens the file in reading mode
int file_open(char * file_name)
{
	int fd = open(file_name,0);
	FD = fd;
	return fd;
}

int fread( void * buf_ptr, int item_size,int item_count,int fd)
{
	
	int read_count = read(fd, buf_ptr, item_size * item_count);

	return read_count;
}


int main(int argc, char ** argv)
{
        if (argc <= 1)
	{
        	printf(1,"Not enough arguments: bmp_opener <File name>\n");
		exit();
	}
//	printf(1,"Opening the file :%s\n",argv[1]);
        
	file_open(argv[1]);
//	printf(1,"fd :%d\n",FD);


	int line_count = 0;
	unsigned char c = '\0', BM[2], buf[16];
	unsigned int file_size = -1, dummy4, pixel_start_byte, DIB_size, image_width, image_height; 
	int count = 0;


    fread((void*)BM,1,2,FD);
//    printf(1,"\nFile format : %s\n",BM);

	fread((void *)&file_size,4,1,FD);
//	printf(1,"File size :%d\n",file_size);

	fread(&dummy4,	   4,1,FD); 
	fread(&pixel_start_byte,4,1,FD);
	fread(&DIB_size,	   4,1,FD);
	fread(&image_width,	   4,1,FD);
	fread(&image_height,	   4,1,FD);


//	printf(1,"start of the pixel: %d\n",pixel_start_byte);
//	printf(1,"DIB header size: %d\n",DIB_size);
//	printf(1,"image width:%d\n",image_width);
//	printf(1,"image height:%d\n",image_height);

	line_count = 0;
//	printf(1,"\n%d: ",line_count);
	

	close(FD);
	file_open(argv[1]);
	
	while(fread((void *)&c,1,1,FD) > 0)
	{
		buf[count] = c;
//		printx(c);
//		printf(1," ");
		
		count++;
	
		if (count == 16)
		{
//			printf(1,"\t");
			for(int i=0;i< 16;i++)
			{	
				if(buf[i] <= 31)
				{
//					printf(1,".");
					continue;
				}
//				printf(1,"%c",buf[i]);
			}

			count = 0;	
			line_count++;					
//			printf(1,"\n%d: ",line_count);
			

		}
	}
//	char tab = '\t';
	int padding = (16*3)-(count*3);
	for (int i=0;i< padding;i++) printf(1," ");
//	printf(1,"%c",tab);
	
	for (int i=0;i < count ;i++)
	{
		if (buf[i] <= 31)
		{
//			printf(1,".");
			continue;
		}
//		printf(1,"%c",buf[i]);
	}
	
//	printf(1,"\n");
	close(FD);

//printing the image in raster graphics
	file_open(argv[1]);

	int temp = 0;
	unsigned char dummy1 = 0;
	
	while(temp < pixel_start_byte)
	{
		fread(&dummy1,1,1,FD);
		temp++;
	}

//	printf(1,"Image:\n\n");

	int col_count = 0;
	int row_count = image_height-1;

	while (fread(&dummy1,1,1,FD) >0 )
	{		
//	printf(1,"<<<row(%d)|col_count++(%d)>>>\n",row_count ,col_count);
		if (col_count >= image_width)
		{	
			col_count = 0;
			row_count = row_count-1;
		}
		if (row_count < 0)
		{
			break;
		}
	//	printx(dummy1);
		print_pixel(row_count,col_count*2,dummy1);
		col_count = col_count + 2;
		
	}
	
	exit();

}
