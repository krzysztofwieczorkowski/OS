#ifndef _GDT_H
#define _GDT_H

#include <stdint.h>
#include <stddef.h>
#define FLAG_4KB_GRAIN 0x8
#define FLAG_32BIT_MODE 0x4
#define ACCESS_PRESENT 0x80
#define ACCESS_RING_0 0x00
#define ACCESS_RING_1 0x20
#define ACCESS_RING_2 0x40
#define ACCESS_RING_3 0x60
#define ACCESS_CD_DESC 0x10
#define ACCESS_CODE 0x08
#define ACCESS_DATA 0x00
#define ACCESS_DIRECTION_DOWN 0x04
#define ACCESS_DIRECTION_UP 0x00
#define ACCESS_READ_WRITE 0x02
#define GDT_SIZE 4

extern void GDT_init(uint32_t adr, uint16_t size);
extern void reloadSegments(void);
void code_GDT_entry(struct gdt_element_t *element, struct sector_t *source);
void create_GDT(void);


struct sector_t{
	uint32_t limit;
	uint32_t base;
	uint8_t access;
	uint8_t flag;
};
struct gdt_element_t{
	uint16_t limit_16;
	uint16_t base_16;
	uint8_t base_24;
	uint8_t access;
	uint8_t limit_20:4;
	uint8_t flag:4;
	uint8_t base_32;
};

#endif
