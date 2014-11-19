
/*
	Arcade card and SGX library example.
	
*/


#include <huc.h>
#include <sgx.h>

#incbin(map,"pce_bat1.bin");
#incbin(tile,"pce_tile1.bin");
#incbin(pal,"pce_pal1.bin");


main()
{
	
	char i,j,k,l,m,n;
	
	
		
	disp_off();		/* <- I don't think this works.... */
	spr_set();
	spr_hide();
	load_default_font();
	set_screen_size(SCR_SIZE_32x32);
	disp_on();

	if(!sgx_detect())
	{  put_string("Halt: SGX not hardware found", 2, 13); for(;;){} }


	/* These NEED to be set, else you won't see the SGX 2nd layer BG or sprites. */
	vpc_win_size( VPC_WIN_A, 0x01ff);
	vpc_win_size( VPC_WIN_B, 0x01ff);
	vpc_win_reg( VPC_WIN_A, VDC_ON+VPC_NORM);
	vpc_win_reg( VPC_WIN_B, VDC_ON+VPC_NORM);
	vpc_win_reg( VPC_WIN_AB, VDC_ON+VPC_NORM);
	vpc_win_reg( VPC_WIN_NONE, VDC_ON+VPC_NORM);

	
	set_font_pal(4);
	set_font_color(14,0);
	load_default_font();
	put_string("SGX hardware found", 2, 3);
	
	sgx_set_screen_size(SCR_SIZE_32x32);
	sgx_load_vram(0x0000,map, 0x400);
	sgx_load_vram(0x1000,tile, 0x4000);
	load_palette(0, pal,16);
	
	sgx_spr_hide();
	sgx_spr_set(1);

	sgx_disp_on();
				
	put_string("Scrolling SGX layer ", 2, 6);
	for(;;)
	{
		for( j=0; j<0xff; j++)
		{
			vsync();
			sgx_scroll( j , j);
		}
	}		
	
	
}