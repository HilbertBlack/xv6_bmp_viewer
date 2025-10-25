#include "types.h"
#include "stat.h"
#include "user.h"

int main(int agrc, char ** argv) 
{

	int l1l = 0x000000F0, l1r = 0x00000042;
//	int full1 = (l1l<<8) | l1r;
	
//	int num = vgaprint(0,0,l1l,l1r);
	
//nt l2l = 0x000000A0, l2r = 0x00000043;
//nt full2 = (l2l<<8) | l2r;


	vgaprint(0,0,l1l,l1r);
	vgaprint(1,1,l1l,l1r);
	vgaprint(2,2,l1l,l1r);
	vgaprint(3,3,l1l,l1r);

//	printf(1, "num:%d |actualy:%d\nnum2:%d | actual:%d",num,full1,vgaprint(1,1,l2l,l2r),full2);
	exit();
} 
