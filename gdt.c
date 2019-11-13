#include <stddef.h>
#include <stdint.h>
#include "gdt.h"

struct sector_t sectors[GDT_SIZE];
struct gdt_element_t GDT[GDT_SIZE];

void create_GDT(void){
	//SEGMENT ZEROWY, PUSTY
	sectors[0].limit=0;
	sectors[0].base=0;
	sectors[0].access=0;
	sectors[0].flag=FLAG_32BIT_MODE;
	
	//SEGMENT  KODU
	sectors[1].base=0x00000000;
	sectors[1].limit=0xFFFFFFFF;
	sectors[1].access=ACCESS_PRESENT|ACCESS_RING_0|ACCESS_CODE|ACCESS_CD_DESC|ACCESS_READ_WRITE|ACCESS_DIRECTION_UP;
	sectors[1].flag =FLAG_4KB_GRAIN|FLAG_32BIT_MODE;
	
	//SEGMENT DANYCH
	sectors[2].base=0x00000000;
	sectors[2].limit=0xFFFFFFFF;
	sectors[2].acess=ACCESS_PRESENT|ACCESS_RING_0|ACCESS_DATA|ACCESS_CD_DESC|ACCESS_READ_WRITE|ACCESS_DIRECTION_UP;
	sectors[2].flag=FLAG_4KB_GRAIN|FLAG_32BIT_MODE;
	
	// na wszelki
	sectors[3].base=0;
	sectors[3].limit=0;
	sectors[3].access=0;
	sectors[3].flag=FLAG_32BIT_MODE;


	for(int i=0;i<GDT_SIZE;i++){
		code_GDT_entry(GDT+i,sectors+i);
	
	reload_segments();
	GDT_init((uint32_t)GDT, sizeof(GDT));

}

void code_GDT_entry(struct gdt_element_t *element, struct sector_t *source){
	element->access=source->access;
	element->flag=source->flag;
	element->limit_16=source->limit & 0x0000FFFF;
	element->limit_20=(source->limit & 0x000F0000)>>16;
	element->base_16=source->base & 0x0000FFFF;
	element->base_24=(source->base & 0x00FF0000)>>16;
	element->base_32=(source->base & 0xFF000000)>>24;
}

