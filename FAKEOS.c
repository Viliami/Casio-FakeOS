/*****************************************************************/
/*                                                               */
/*   CASIO fx-9860G SDK Library                                  */
/*                                                               */
/*   File name : FAKEOS.c                                 */
/*                                                               */
/*   Copyright (c) 2016 CASIO COMPUTER CO., LTD.                 */
/*                                                               */
/*****************************************************************/

/*****************************************************************

AUTHOR: VILIAMI

******************************************************************/

#include "fxlib.h"
#include "timer.h"
#include <stdio.h>
#include <string.h>

//****************************************************************************
//  AddIn_main (Sample program main function)
//
//  param   :   isAppli   : 1 = This application is launched by MAIN MENU.
//                        : 0 = This application is launched by a strip in eACT application.
//
//              OptionNum : Strip number (0~3)
//                         (This parameter is only used when isAppli parameter is 0.)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************

#define __KEYBIOS_H__
#define KEY_CHAR_0 71
#define KEY_CHAR_1 72
#define KEY_CHAR_2 62
#define KEY_CHAR_3 52
#define KEY_CHAR_4 73
#define KEY_CHAR_5 63
#define KEY_CHAR_6 53
#define KEY_CHAR_7 74
#define KEY_CHAR_8 64
#define KEY_CHAR_9 54
#define KEY_CHAR_DP 61
#define KEY_CHAR_EXP 51
#define KEY_CHAR_PMINUS 41
#define KEY_CHAR_PLUS 42
#define KEY_CHAR_MINUS 32
#define KEY_CHAR_MULT 43
#define KEY_CHAR_DIV 33
#define KEY_CHAR_FRAC 75
#define KEY_CHAR_LPAR 55
#define KEY_CHAR_RPAR 45
#define KEY_CHAR_COMMA 35
#define KEY_CHAR_STORE 25
#define KEY_CHAR_LOG 66
#define KEY_CHAR_LN 56
#define KEY_CHAR_SIN 46
#define KEY_CHAR_COS 36
#define KEY_CHAR_TAN 26
#define KEY_CHAR_SQUARE 67
#define KEY_CHAR_POW 57
#define KEY_CTRL_EXE 31
#define KEY_CTRL_DEL 44
#define KEY_CTRL_AC 32
#define KEY_CTRL_FD 65
#define KEY_CTRL_EXIT 47
#define KEY_CTRL_SHIFT 78
#define KEY_CTRL_ALPHA 77
#define KEY_CTRL_OPTN 68
#define KEY_CTRL_VARS 58
#define KEY_CTRL_UP 28
#define KEY_CTRL_DOWN 37
#define KEY_CTRL_LEFT 38
#define KEY_CTRL_RIGHT 27
#define KEY_CTRL_F1 79
#define KEY_CTRL_F2 69
#define KEY_CTRL_F3 59
#define KEY_CTRL_F4 49
#define KEY_CTRL_F5 39
#define KEY_CTRL_F6 29
#define KEY_CTRL_MENU 48
#ifndef OS2Change
#define OS2Change
#ifndef OS2Change_GetOS2
#define OS2Change_GetOS2
typedef int(*sc_i2cp2sip)(char*, char*, short int*, short int*);
const unsigned int sc0015[] = { 0xD201D002, 0x422B0009, 0x80010070, 0x0015 };
#define GlibGetOSVersionInfo (*(sc_i2cp2sip)sc0015)
int OSVersionAsInt(void)
{
unsigned char mainversion;
unsigned char minorversion;
unsigned short release;
unsigned short build;
GlibGetOSVersionInfo( &mainversion, &minorversion, &release, &build );
return ( ( mainversion << 24 ) & 0xFF000000 ) | ( ( minorversion << 16 ) & 0x00FF0000 ) | ( release & 0x0000FFFF );
}
#define isOS2 (OSVersionAsInt() >= 0x02020000)
#define OS2(x,y) ((OSVersionAsInt() >= 0x02020000)?y:x)
#endif
#ifndef OS2Change_Keyboard
#define OS2Change_Keyboard
void delay(void)
{
char i;
for (i=0; i<5; i++){};
}
unsigned char CheckKeyRow(unsigned char code)
{
unsigned char result=0;
short*PORTB_CTRL=(void*)0xA4000102;
short*PORTM_CTRL=(void*)0xA4000118;
char*PORTB=(void*)0xA4000122;
char*PORTM=(void*)0xA4000138;
char*PORTA=(void*)0xA4000120;
short smask;
char cmask;
unsigned char column, row;
column = code>>4;
row = code &0x0F;
smask = 0x0003 << (( row %8)*2);
cmask = ~( 1 << ( row %8) );
if(row <8)
{
  *PORTB_CTRL = 0xAAAA ^ smask;
  *PORTM_CTRL = (*PORTM_CTRL & 0xFF00 ) | 0x00AA;
  delay();
  *PORTB = cmask;
  *PORTM = (*PORTM & 0xF0 ) | 0x0F;
}
else
{
  *PORTB_CTRL = 0xAAAA;
  *PORTM_CTRL = ((*PORTM_CTRL & 0xFF00 ) | 0x00AA)  ^ smask;
  delay();
  *PORTB = 0xFF;
  *PORTM = (*PORTM & 0xF0 ) | cmask;
}

delay();
result = (~(*PORTA))>>column & 1;
delay();
*PORTB_CTRL = 0xAAAA;
*PORTM_CTRL = (*PORTM_CTRL & 0xFF00 ) | 0x00AA;
delay();
*PORTB_CTRL = 0x5555;
*PORTM_CTRL = (*PORTM_CTRL & 0xFF00 ) | 0x0055;
delay();

return result;
}

unsigned char KeyDown(unsigned char keycode)
{
unsigned short key[8];
const unsigned short* keyboardregister = (unsigned short*)0xA44B0000;
if(isOS2)
{
  unsigned char row = keycode%10;
  memcpy(key, keyboardregister, sizeof(unsigned short) << 3);
 
  return (0 != (key[row >> 1] & 1 << keycode / 10 - 1 + ((row & 1) << 3)));
}
else
{
  return CheckKeyRow((keycode % 10) + ((keycode / 10 - 1) << 4));
}
}
unsigned char GetKeyMod(unsigned int *key)
{
unsigned char x, ret;

ret = GetKey(key);

for(x = 0; x < 80; x++)
{
  if(KeyDown(x))
  {
   *key = x;
   break;
  }
}
return ret;
}
#define IsKeyDown(x) KeyDown(x)
#define IsKeyUp(x) !KeyDown(x)
#define GetKey(x) GetKeyMod(x)
#endif
#endif

#define TRUE 1
#define FALSE 0
#define TILE_WIDTH 30
#define TILE_HEIGHT 19
#define SMALL_TILE_WIDTH 19
#define SMALL_TILE_HEIGHT 8

unsigned int key, alt_key = 0;
int selected_x = 0, selected_y = 0, scroll_y = 0, keycode = 0, keycode2 = 0,cursor = TRUE;
short unused = 0, loading_bar_x = 19;
int selected_tile[4][4] = {
{1,0,0,0},
{0,0,0,0},
{0,0,0,0},
{0,0,0,9}
};
DISPBOX popup;
typedef enum {MENU ,RUNMAT, STAT, EACT, GRAPH, SSHT, DYNA, TABLE, RECUR, CONICS, EQUA, PRGM, TVM, LINK, MEMORY, SYSTEM,SYSTEM_CONTRAST,SYSTEM_PP,SYSTEM_LANG, SYSTEM_VER,SYSTEM_RSET,
SYSTEM_RSET_STUP,SYSTEM_RSET_MAIN,SYSTEM_RSET_ADD,SYSTEM_RSET_SMEM, SYSTEM_RSET_AS, SYSTEM_RSET_2, SYSTEM_RSET2_MS, SYSTEM_RSET2_ALL, SYSTEM_RSET2_MS_YES, SYSTEM_RSET2_ALL_YES , OFF_LOGO, OFF, ONETHREEAC_RESET} State;
typedef enum{false, true} bool;
bool block_input = false;
State state = MENU;
State prevState = MENU;
int cas_title[7][128] = {
{1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,1,0,0,0,1,0,0,1,1,1,0,0,0,1,1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,0,1,1,1,1,1,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1},
{0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,1,0,1,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,1,0,1,1,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0},
{0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,1,1,0,0,1,0,1,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0},
{1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,1,0,1,0,1,0,1,1,1,1,1,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,0,0,0,1,0,1,0,1,0,1,1,1,1,0,0,1,0,1,0,1,0,1,0,0,0,1,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1},
{0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,0,1,1,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0},
{0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0},
{1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,1,1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,0,1,1,1,1,1,0,1,0,0,0,1,0,0,1,1,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1}
};

int run_mat[19] = {
0,
424813135,
358233765,
425110245,
357704357,
345121445,
1,
286365837,
167847141,
75310229,
167844581,
286326789,
67174527,
67181687,
528293991,
67182711,
67214455,
119,
536870911
};

int stat[19] = {
0,
251240193,
270681089,
203670529,
35800065,
472007681,
1,
135397373,
134554769,
139011217,
135397373,
153166977,
139011199,
142737219,
153166973,
167772259,
268435295,
65,
536870911
};

int e_act[19] = {
0,
202960385,
304415745,
515703809,
270861313,
237298689,
1,
267379457,
135275905,
198683393,
134231553,
198650881,
135288959,
197570627,
135323773,
135274595,
267378813,
67,
536870911
};

int s_sht[19] = {
0,
236805121,
270616577,
211404801,
33900545,
473516033,
1,
268435425,
149876449,
149876449,
149876449,
252776705,
252776831,
150994779,
252776795,
252776769,
167772027,
123,
536870911
};

int graph[19] = {
0,
249772321,
278177057,
384285153,
312779041,
244621601,
1,
7358721,
8933889,
8937985,
17056769,
17089537,
268435327,
33704001,
33966175,
67719235,
68214909,
67,
536870911
};

int dyna[19] = {
0,
478825473,
307450369,
304274945,
304239105,
472011265,
1,
71582721,
71582721,
71582721,
71582721,
35948545,
35948671,
18157667,
9773151,
7258179,
268435037,
99,
536870911
};

int table[19] = {
0,
523473377,
71979265,
75207137,
71979265,
72064481,
1,
356582417,
306250769,
356582417,
272696337,
536870657,
272696447,
356582465,
306250877,
306250875,
272696439,
119,
536870911
};

int recur[19] = {
0,
485729729,
310650145,
485762497,
344204609,
317954337,
1,
257,
513,
1047553,
3757057,
13181953,
17388671,
34208867,
34145373,
100270691,
84148829,
84410723,
536870911
};

int conics[19] = {
0,
241477433,
278308929,
278243377,
278177801,
241477489,
1,
262145,
4161537,
12869633,
17043457,
33818625,
268435071,
33818723,
17043549,
12869729,
4161661,
262243,
536870911
};

int equa[19] = {
0,
509908993,
278176769,
513063937,
279225345,
508765185,
1,
105201665,
19506177,
118566401,
153617409,
121896961,
49279,
3743843,
176234589,
3743809,
49245,
93,
536870911
};

int prgm[19] = {
0,
484680193,
311703041,
484813313,
279224833,
278110721,
1,
33550337,
33556481,
50326529,
44756481,
50327041,
44822143,
50327107,
33558109,
78290499,
156580957,
313161795,
536870911
};

int tvm[19] = {
0,
524619777,
71675905,
71651329,
69799937,
68227073,
1,
60929,
34817,
143191553,
85886977,
36210689,
261881983,
34209889,
263979103,
34078815,
95,
97,
536870911
};

int link[19] = {
0,
283723777,
273502209,
273375233,
273240065,
518604801,
1,
266403329,
136348161,
195082753,
195607041,
137724417,
179677823,
136479299,
178301533,
136348253,
266403421,
67,
536870911
};

int memory[19] = {
0,
292833685,
457626965,
360011157,
289690953,
292833609,
1,
1022977,
6267393,
7873281,
7348993,
527965953,
285462143,
293716033,
293847135,
532627523,
264110175,
65,
536870911
};

int system[19] = {
0,
219379525,
279192685,
138553173,
71377989,
407250757,
1,
29360129,
83885569,
106955009,
134217217,
62914561,
130175,
126812737,
75103839,
126812739,
130143,
95,
536870911
};

int mat[8] = {
524287,
524287,
384433,
313691,
283931,
318810,
384344,
524280
};

int contrast[8] = {
524287,
507967,
492511,
459759,
492511,
507966,
524284,
524280
};

int apo[8] = {
524287,
491535,
495631,
473327,
495631,
491534,
524284,
524280
};

int lang[8] = {
524287,
383847,
371551,
371039,
363095,
371542,
306020,
524280
};

int ver[8] = {
524287,
381071,
382903,
381367,
382863,
440246,
487604,
524280
};

int rset[8] = {
524287,
320583,
351727,
355439,
325103,
357870,
347244,
524280
};

int stup[8] = {
524287,
411047,
388523,
454059,
486823,
486830,
323180,
524280
};

int main[8] = {
524287,
383835,
300379,
349515,
381267,
382298,
382296,
524280
};

int add[8] = {
524287,
418591,
372079,
372079,
273775,
372078,
369436,
524280
};

int smem[8] = {
524287,
309853,
234185,
371285,
436949,
441052,
113244,
524280
};

int a_s[8] = {
521215,
421319,
371647,
374735,
273143,
372214,
373388,
524280
};

int r_arrow[8] = {
524287,
262144,
262912,
262784,
262720,
262784,
262912,
262144
};

/*int l_arrow[8] = {
524287,
262144,
268288,
272384,
280576,
272384,
268288,
262144
};*/

int m_s [8] = {
522751,
382691,
300511,
351207,
349563,
382714,
383300,
524280
};

int all[8] = {
524287,
421631,
372479,
372479,
274175,
372478,
369212,
524280
};

int casio_logo_1[13] = {
1073219520,
2147223488,
4294840288,
4028501728,
3759021808,
3758103664,
3758111864,
3758110776,
3759046652,
4028530684,
4294901758,
2147278862,
1073274894
};

int casio_logo_2[13] = {
2147017215,
4294763519,
4294764543,
3759990656,
3758155520,
4294502144,
4294764288,
2147280640,
1894144,
3759990656,
4294764543,
4294763519,
2147017215
};

int casio_logo_3[13] = {
3072,
3584,
3840,
3840,
1792,
1820,
1826,
1881,
1877,
3929,
3925,
3618,
3100
};

void draw_header(){
	int x,y;
	for(y = 0; y < 7; y++){
		for(x = 0; x < 128; x++){
			if(cas_title[y][x] == 1)
				Bdisp_SetPoint_VRAM(x,y,1);
		}
	}
}

void draw_array(int pixel_array[19][30], int startX, int startY){
	int x,y;
	for(y = startY; y < TILE_HEIGHT+startY; y++){
		for(x= startX; x <  TILE_WIDTH+startX; x++){
			if(pixel_array[y-startY][x-startX] == 1){
				Bdisp_SetPoint_VRAM(x,y,1);
			}
		}
	}
}

void draw_int_array(int pixel_array[SMALL_TILE_WIDTH],int startX,int startY,int selected){
	int x,y,number;
	if(startY < 7 || startY >= 63 ){
		return;
	}
	for(y = 0; y < TILE_HEIGHT; y++){
		number = pixel_array[y];
		for(x = 0;  x < TILE_WIDTH; x++){
			int bit = number & 1;
			if(bit != selected){
				Bdisp_SetPoint_VRAM(-x+(TILE_WIDTH-1)+startX,y+startY,1);
		    	}
			number = number >> 1;
		}
	}
}

void draw_pixel_array(int pixel_array[13], int startX, int startY){
	int x,y,number;
	for(y = 0; y < 13; y++){
		number = pixel_array[y];
		for(x = 0;  x < 32; x++){
			int bit = number & 1;
			if(bit == 1)
				Bdisp_SetPoint_VRAM(-x+(32-1)+startX,y+startY,1);
		    	number = number >> 1;
		}
	}
}

void draw_int_array_small(int pixel_array[SMALL_TILE_HEIGHT], int startX, int startY){
	int x,y,number;
	for(y = 0; y < SMALL_TILE_HEIGHT; y++){
		number = pixel_array[y];
		for(x = 0; x < SMALL_TILE_WIDTH; x++){
			int bit = number & 1;
			if(bit == 1)
				Bdisp_SetPoint_VRAM(-x+(SMALL_TILE_WIDTH-1)+startX, y+startY,1);
			number = number >> 1;
		}
	}
}

void draw_down_arrow(){
	Bdisp_DrawLineVRAM(123,56,123,62);
	Bdisp_SetPoint_VRAM(122,61,1);
	Bdisp_SetPoint_VRAM(121,60,1);
	Bdisp_SetPoint_VRAM(124,61,1);
	Bdisp_SetPoint_VRAM(125,60,1);
}

void draw_up_arrow(){
	Bdisp_DrawLineVRAM(123,8,123,14);
	Bdisp_SetPoint_VRAM(122,9,1);
	Bdisp_SetPoint_VRAM(121,10,1);
	Bdisp_SetPoint_VRAM(124,9,1);
	Bdisp_SetPoint_VRAM(125,10,1);
}

void draw_arrows(){
	if(scroll_y == 0){
		draw_down_arrow();
	}else if(scroll_y == TILE_HEIGHT){
		draw_up_arrow();
	}
}

void draw_menu(){
	draw_header();
	draw_int_array(run_mat,0,7-scroll_y,selected_tile[0][0]);
	draw_int_array(stat,TILE_WIDTH,7-scroll_y,selected_tile[0][1]);
	draw_int_array(e_act,2*TILE_WIDTH,7-scroll_y,selected_tile[0][2]);
	draw_int_array(s_sht,3*TILE_WIDTH,7-scroll_y,selected_tile[0][3]);
	
	draw_int_array(graph,0,7+TILE_HEIGHT-scroll_y,selected_tile[1][0]);
	draw_int_array(dyna,TILE_WIDTH,7+TILE_HEIGHT-scroll_y,selected_tile[1][1]);
	draw_int_array(table,TILE_WIDTH*2,7+TILE_HEIGHT-scroll_y,selected_tile[1][2]);
	draw_int_array(recur,TILE_WIDTH*3,7+TILE_HEIGHT-scroll_y,selected_tile[1][3]);

	draw_int_array(conics,0,7+TILE_HEIGHT*2-scroll_y,selected_tile[2][0]);
	draw_int_array(equa,TILE_WIDTH,7+TILE_HEIGHT*2-scroll_y,selected_tile[2][1]);
	draw_int_array(prgm,TILE_WIDTH*2,7+TILE_HEIGHT*2-scroll_y,selected_tile[2][2]);
	draw_int_array(tvm,TILE_WIDTH*3,7+TILE_HEIGHT*2-scroll_y,selected_tile[2][3]);

	draw_int_array(link,0,7+TILE_HEIGHT*3-scroll_y,selected_tile[3][0]);
	draw_int_array(memory,TILE_WIDTH,7+TILE_HEIGHT*3-scroll_y,selected_tile[3][1]);
	draw_int_array(system,TILE_WIDTH*2,7+TILE_HEIGHT*3-scroll_y,selected_tile[3][2]);

	draw_arrows();
}

void power_off(){
	state = OFF;
	Bdisp_AllClr_DDVRAM();
	KillTimer(ID_USER_TIMER1);
}

void power_on(){
	state = prevState;
	block_input = false;
	KillTimer(ID_USER_TIMER1);
	KillTimer(ID_USER_TIMER2);
	Bdisp_AllClr_DDVRAM();
	if(state == MENU){
		draw_menu();
		Bdisp_PutDisp_DD();
	}
}

void draw_loading_square(){
	Bdisp_SetPoint_VRAM(124,0,1);
	Bdisp_SetPoint_VRAM(125,0,1);
	Bdisp_SetPoint_VRAM(126,0,1);
	Bdisp_SetPoint_VRAM(127,0,1);
	Bdisp_SetPoint_VRAM(124,1,1);
	Bdisp_SetPoint_VRAM(125,1,1);
	Bdisp_SetPoint_VRAM(126,1,1);
	Bdisp_SetPoint_VRAM(127,1,1);
	Bdisp_SetPoint_VRAM(124,2,1);
	Bdisp_SetPoint_VRAM(125,2,1);
	Bdisp_SetPoint_VRAM(126,2,1);
	Bdisp_SetPoint_VRAM(127,2,1);
	Bdisp_SetPoint_VRAM(124,3,1);
	Bdisp_SetPoint_VRAM(125,3,1);
	Bdisp_SetPoint_VRAM(126,3,1);
	Bdisp_SetPoint_VRAM(127,3,1);
	Bdisp_PutDisp_DD();
}

void handleKeys(){
	key = 9999;
	
	if(state == OFF){
		if(IsKeyDown(KEY_CHAR_1) && IsKeyDown(KEY_CHAR_3)){
			draw_menu();
			Bdisp_PutDisp_DD();
		}
	}

	Bkey_GetKeyWait(&keycode, &keycode2, KEYWAIT_HALTON_TIMEROFF, 0,1,&unused) ;
	
	if(state == OFF){
		if(keycode == 1 && keycode2 == 1){
			block_input = false;
		}
	}

	if(block_input)
		return;

	if(keycode == 1 && keycode2 == 1){
		key = KEY_CTRL_AC;
	}else if(keycode ==3 && keycode2 == 8 ){
		key = KEY_CTRL_DOWN;
		alt_key = 0;
	}else if(keycode == 2 && keycode2 == 8){
		key = KEY_CTRL_RIGHT;
		alt_key = 0;
	}else if(keycode == 2 && keycode2 == 9){
		key = KEY_CTRL_UP;
		alt_key = 0;
	}else if(keycode == 3 && keycode2 == 9){
		key = KEY_CTRL_LEFT;
		alt_key = 0;
	}else if(keycode == 4 && keycode2 == 9){
		key = KEY_CTRL_MENU;
		alt_key = 0;
	}else if(keycode == 3 && keycode2 == 2){
		key = KEY_CTRL_EXE;
		alt_key = 0;
	}else if(keycode == 4 && keycode2 == 8){
		key = KEY_CTRL_EXIT;
		alt_key = 0;
	}else if(keycode == 7 && keycode2 == 9){
		alt_key = KEY_CTRL_SHIFT;
	}else if(keycode == 7 && keycode2 == 8){
		alt_key = KEY_CTRL_ALPHA;
	}else if(keycode2 == 10){
		if(keycode == 7){
			key = KEY_CTRL_F1;
			alt_key = 0;
		}else if(keycode == 6){
			key = KEY_CTRL_F2;
			alt_key = 0;
		}else if(keycode == 5){
			key = KEY_CTRL_F3;
			alt_key = 0;
		}else if(keycode == 4){
			key = KEY_CTRL_F4;
			alt_key = 0;
		}else if(keycode == 3){
			key = KEY_CTRL_F5;
			alt_key = 0;
		}else if(keycode == 2){
			key = KEY_CTRL_F6;
			alt_key = 0;
		}
	}

	switch(key){
		case KEY_CTRL_UP:
			if(state == MENU){
				selected_tile[selected_y][selected_x] = 0;
				if(selected_y > 0){
					selected_y--;
					if(selected_y == 0 && scroll_y == TILE_HEIGHT){
						scroll_y = 0;
					}
				}
			}
			break;
		case KEY_CTRL_DOWN:
			if(state == MENU){
				selected_tile[selected_y][selected_x] = 0;
				if(selected_y < 3 && !(selected_x == 3 && selected_y == 2)){
					selected_y++;
					if(selected_y == 3 && scroll_y == 0){
						scroll_y = TILE_HEIGHT;
					}
				}else if(selected_y == 2 && selected_x == 3){
					selected_y++;
					selected_x = 2;
					scroll_y = TILE_HEIGHT;
				}
			}
			break;
		case KEY_CTRL_LEFT:
			if(state == MENU){
				selected_tile[selected_y][selected_x] = 0;
				if(selected_x > 0){
					selected_x--;
				}else if(selected_y > 0){
					selected_x = 3;
					selected_y--;
					if(selected_y == 0 && scroll_y == TILE_HEIGHT)
						scroll_y = 0;
				}
			}
			break;
		case KEY_CTRL_RIGHT:
			if(state == MENU){
				selected_tile[selected_y][selected_x] = 0;
				if(selected_x < 3 && !(selected_x == 2 && selected_y == 3)){
					selected_x++;
				}else if(selected_y < 3){
					selected_x = 0;
					selected_y++;
					if(selected_y == 3 && scroll_y == 0){
						scroll_y = TILE_HEIGHT;
					}
				}
			}
			break;
		case KEY_CTRL_EXE:
			if(state == MENU){
				if(selected_y == 0 && selected_x == 0){ //run.mat selected
					Bdisp_AllClr_DDVRAM();
					state = RUNMAT;
				}else if(selected_y == 3 && selected_x == 2){
					Bdisp_AllClr_DDVRAM();
					state = SYSTEM;
				}
			}
			break;
		case KEY_CTRL_MENU:
			if(state != MENU && state != SYSTEM_RSET2_ALL_YES){
				prevState = state;
				state = MENU;
				KillTimer(ID_USER_TIMER1);
			}else if(state == MENU){
				Bdisp_AllClr_DDVRAM();
				state = prevState;
			}
			break;
		case KEY_CTRL_F1:
			if(state == SYSTEM_RSET){
				state = SYSTEM_RSET_STUP;
			}else if(state == SYSTEM_RSET_2){
				state = SYSTEM_RSET2_MS;
			}else if(state == SYSTEM_RSET2_ALL){
				state =SYSTEM_RSET2_ALL_YES;
				loading_bar_x = 19;
			}else if(state == SYSTEM){
				Bdisp_AllClr_DDVRAM();
				state = SYSTEM_CONTRAST;
			}
			break;
		case KEY_CTRL_F2:
			if(state == SYSTEM_RSET){
				state = SYSTEM_RSET_MAIN;
			}else if(state == SYSTEM_RSET_2){
				state = SYSTEM_RSET2_ALL;
			}else if(state == SYSTEM){
				Bdisp_AllClr_DDVRAM();
				state = SYSTEM_PP;
			}
			break;
		case KEY_CTRL_F3:
			if(state == SYSTEM_RSET){
				state = SYSTEM_RSET_ADD;
			}else if(state == SYSTEM){
				Bdisp_AllClr_DDVRAM();
				state = SYSTEM_LANG;
			}
			break;
		case KEY_CTRL_F4:
			if(state == SYSTEM_RSET){
				state = SYSTEM_RSET_SMEM;
			}else if(state == SYSTEM){
				Bdisp_AllClr_DDVRAM();
				state = SYSTEM_VER;
			}
			break;
		case KEY_CTRL_F5:
			if(state == SYSTEM){
				Bdisp_AllClr_DDVRAM();
				state = SYSTEM_RSET;
			}else if(state == SYSTEM_RSET){
				state = SYSTEM_RSET_AS;
			}
			break;
		case KEY_CTRL_F6:
			if(state == SYSTEM_RSET || state == SYSTEM_RSET_2){
				Bdisp_AllClr_DDVRAM();
				if(state == SYSTEM_RSET_2){
					state = SYSTEM_RSET;
				}else if(state == SYSTEM_RSET){
					state = SYSTEM_RSET_2;
				}
			}
			if(state == SYSTEM_RSET_STUP || state == SYSTEM_RSET_MAIN || state == SYSTEM_RSET_ADD || state == SYSTEM_RSET_SMEM || state == SYSTEM_RSET_AS)
				state = SYSTEM_RSET;
			if(state == SYSTEM_RSET2_MS || state == SYSTEM_RSET2_ALL)
				state = SYSTEM_RSET_2;
			break;
		case KEY_CTRL_EXIT:
			if(state == SYSTEM_RSET_STUP || state == SYSTEM_RSET_MAIN || state == SYSTEM_RSET_ADD || state == SYSTEM_RSET_SMEM || state == SYSTEM_RSET_AS){
				state = SYSTEM_RSET;
			}else if(state == SYSTEM_RSET2_MS || state == SYSTEM_RSET2_ALL){
				state = SYSTEM_RSET_2;
			}else if(state == SYSTEM_RSET2_ALL_YES){
				prevState = MENU;
				power_off();
				SetTimer(ID_USER_TIMER1, 1500, draw_loading_square);
				SetTimer(ID_USER_TIMER2, 4000, power_on);
			}else if(state == SYSTEM_RSET || state == SYSTEM_RSET_2 || state == SYSTEM_CONTRAST || state == SYSTEM_PP || state == SYSTEM_LANG || state == SYSTEM_VER){
				state = SYSTEM;
			}
			break;
		case KEY_CTRL_AC:
			if(alt_key == KEY_CTRL_SHIFT){
				prevState = state;
				state = OFF_LOGO;
				alt_key = 0;
				block_input = true;
				KillTimer(ID_USER_TIMER1);
				SetTimer(ID_USER_TIMER1,1500,power_off);
			}else if(state == OFF){
				power_on();
			}
			break;
	}
	selected_tile[selected_y][selected_x] = 1; //update selected_tile array
}



void draw_bottom_button(int pixel_array[8], int f_number){
	int startX = 2+(20*(f_number-1));
	draw_int_array_small(pixel_array,startX,56);
}

void draw_cursor(){
	Bdisp_AllClr_DDVRAM();
	draw_bottom_button(mat,1);
	if(cursor){
		Bdisp_DrawLineVRAM(0,0,0,7);
		Bdisp_DrawLineVRAM(1,0,1,7);
		cursor = FALSE;
	}else{
		cursor = TRUE;
	}
	Bdisp_PutDisp_DD();
}

void draw_runmat(){
	draw_bottom_button(mat,1);
	SetTimer(ID_USER_TIMER1,500,draw_cursor);
}

void draw_system(){
	locate(1,1);
	Print("System Manager");
	locate(1,3);
	Print("F1:Contrast");
	locate(1,4);
	Print("F2:Power Properties");
	locate(1,5);
	Print("F3:Language");
	locate(1,6);
	Print("F4:Version");
	locate(1,7);
	Print("F5:Reset");
	draw_bottom_button(contrast,1);
	draw_bottom_button(apo,2);
	draw_bottom_button(lang,3);
	draw_bottom_button(ver,4);
	draw_bottom_button(rset,5);
}

void draw_contrast(){

}

void draw_apo(){

}

void draw_lang(){

}

void draw_ver(){

}

void draw_rset(){
	locate(1,1);
	Print("*****   RESET   *****");
	locate(1,2);
	Print("F1:Setup Data");
	locate(1,3);
	Print("F2:Main Memories");
	locate(1,4);
	Print("F3:Add-In");
	locate(1,5);
	Print("F4:Storage Memories");
	locate(1,6);
	Print("F5:Add-In&Storage");
	locate(1,7);
	Print("F6:Next Page");
	draw_bottom_button(stup,1);
	draw_bottom_button(main,2);
	draw_bottom_button(add,3);
	draw_bottom_button(smem,4);
	draw_bottom_button(a_s,5);
	draw_bottom_button(r_arrow,6);
}

void draw_rset_2(){
	locate(1,1);
	Print("*****   RESET   *****");
	locate(1,2);
	Print("F1:Main&Storage");
	locate(1,3);
	Print("F2:Initialize All");
	draw_bottom_button(m_s,1);
	draw_bottom_button(all,2);
	draw_bottom_button(r_arrow,6);
}

void clear_box(int x, int y, int x2, int y2){
	int i = 0, j = 0;
	for(j = y; j < y2; j ++){
		for(i = x; i < x2; i++){
			Bdisp_SetPoint_VRAM(i,j,0); //clear point
		}
	}
}

void draw_box_border(){ //draws border for popup box
	Bdisp_DrawLineVRAM(popup.left, popup.top, popup.right, popup.top); //horizontal line on top
	Bdisp_DrawLineVRAM(popup.left, popup.top, popup.left, popup.bottom); //vertical line on left side
	//vertical lines on right side
	Bdisp_DrawLineVRAM(popup.right, popup.top, popup.right, popup.bottom);
	Bdisp_DrawLineVRAM(popup.right-1, popup.top+1, popup.right-1, popup.bottom-1);
	//horizontal lines on bottom
	Bdisp_DrawLineVRAM(popup.left, popup.bottom, popup.right, popup.bottom);
	Bdisp_DrawLineVRAM(popup.left+1, popup.bottom-1, popup.right-1, popup.bottom-1);
}

void draw_popup_box(char* title){ //draws popup box
	clear_box(popup.left ,popup.top, popup.right, popup.bottom);
	draw_box_border();
	locate(7,2);
	Print("Reset OK?");
	locate(4,3);
	Print(title);
	locate(6,5);
	Print("Yes:[F1]");
	locate(6,6);
	Print("No :[F6]");
}

void draw_memory(){
	
}

void draw_loading_bar(){
	int i = 0;
	if(state == SYSTEM_RSET2_ALL_YES){
		draw_rset_2();
	}
	clear_box(popup.left ,popup.top, popup.right, popup.bottom);
	draw_box_border();
	locate(3,3);
	Print("One Moment Please");
	Bdisp_DrawLineVRAM(18,31,107,31); //top horizontal line
	Bdisp_DrawLineVRAM(18,41,107,41); //bottom horizontal line
	Bdisp_DrawLineVRAM(18,31,18,41); //left vertical line
	Bdisp_DrawLineVRAM(107,31,107,41); //right vertical line
	for(i = 17; i <= loading_bar_x; i++){
		Bdisp_DrawLineVRAM(i, 31, i, 41);
	}
	if(loading_bar_x <= 106){
		block_input = true;
		draw_loading_square();
		loading_bar_x++;
	}else{
		KillTimer(ID_USER_TIMER1);
		block_input = false;
		if(state == SYSTEM_RSET2_ALL_YES){
			draw_rset_2();
		}
		clear_box(popup.left ,popup.top, popup.right, popup.bottom);
		draw_box_border();
		clear_box(popup.left ,popup.top, popup.right, popup.bottom);
		draw_box_border();
		locate(8,2);
		Print("Reset!");
		locate(4,3);
		if(state == SYSTEM_RSET2_ALL_YES){
			Print("Initialize All");
		}
		locate(6,6);
		Print("Press:[EXIT]");
	}
	Bdisp_PutDisp_DD();
}

void draw_sys_contrast(){
	unsigned char triangle_arrow[5] = {'[',0xE6,0x9A,']',0};
	Bdisp_DrawLineVRAM(2, 56, 2, 63);
	Bdisp_DrawLineVRAM(2, 56, 21, 56); //actual border is Bdisp_DrawLineVRAM(2, 56, 21, 56)
	PrintMini(4,58,"INIT",MINI_OVER);
	locate(1,1);
	Print("Contrast");
	locate(2,3);
	Print(triangle_arrow);
	locate(5,3);
	Print("Key");
	locate(15,3);
	Print("[ ]Key");\
}

void draw_sys_pp(){

}

void draw_sys_lang(){

}

void draw_sys_ver(){

}

void draw_loading_box(){
	if(state == SYSTEM_RSET2_ALL_YES){
		draw_rset_2();
	}
	clear_box(popup.left ,popup.top, popup.right, popup.bottom);
	draw_box_border();
	locate(3,3);
	Print("One Moment Please");
	SetTimer(ID_USER_TIMER1,100,draw_loading_bar);
}

int AddIn_main(int isAppli, unsigned short OptionNum){

	popup.top = 3; popup.left = 9; popup.right = 118; popup.bottom = 52;
    	Bdisp_AllClr_DDVRAM();
	draw_menu();
	Bdisp_PutDisp_DD();

    	while(1){

		handleKeys();
		if(state != RUNMAT)
			Bdisp_AllClr_DDVRAM(); //clear screen

		switch(state){
			case MENU:
				draw_menu();
				break;
			case RUNMAT:
				draw_runmat();
				break;
			case STAT:
				break;
			case EACT:
				break;
			case SSHT:
				break;
			case GRAPH:
				break;
			case DYNA:
				break;
			case TABLE:
				break;
			case RECUR:
				break;
			case CONICS:
				break;
			case EQUA:
				break;
			case PRGM:
				break;
			case TVM:
				break;
			case LINK:
				break;
			case MEMORY:
				draw_memory();
				break;
			case SYSTEM:
				draw_system();
				break;
			case SYSTEM_CONTRAST:
				draw_sys_contrast();
				break;
			case SYSTEM_PP:
				draw_sys_pp();
				break;
			case SYSTEM_LANG:
				draw_sys_lang();
				break;
			case SYSTEM_VER:
				draw_sys_ver();
				break;
			case SYSTEM_RSET:
				draw_rset();
				break;
			case SYSTEM_RSET_2:
				draw_rset_2();
				break;
			case SYSTEM_RSET_STUP:
				draw_rset();
				draw_popup_box("Setup Data");
				break;
			case SYSTEM_RSET_MAIN:
				draw_rset();
				draw_popup_box("Main Memories");
				break;
			case SYSTEM_RSET_ADD:
				draw_rset();
				draw_popup_box("Add-in");
				break;
			case SYSTEM_RSET_SMEM:
				draw_rset();
				draw_popup_box("Storage Memories");
				break;
			case SYSTEM_RSET_AS:
				draw_rset();
				draw_popup_box("Add-in");
				break;
			case SYSTEM_RSET2_MS:
				draw_rset_2();
				draw_popup_box("Main Memories");
				break;
			case SYSTEM_RSET2_ALL:
				draw_rset_2();
				draw_popup_box("Initialize All");
				break;
			case SYSTEM_RSET2_MS_YES:
				
				break;
			case SYSTEM_RSET2_ALL_YES:
				if(loading_bar_x == 19){
					draw_loading_box();
				}else if(loading_bar_x == 107){
					if(state == SYSTEM_RSET2_ALL_YES){
						draw_rset_2();
					}
					clear_box(popup.left ,popup.top, popup.right, popup.bottom);
					draw_box_border();
					clear_box(popup.left ,popup.top, popup.right, popup.bottom);
					draw_box_border();
					locate(8,2);
					Print("Reset!");
					locate(4,3);
					if(state == SYSTEM_RSET2_ALL_YES){
						Print("Initialize All");
					}
					locate(6,6);
					Print("Press:[EXIT]");
				}
				break;
			case OFF_LOGO:
				draw_pixel_array(casio_logo_1, 29,26);
				draw_pixel_array(casio_logo_2, 61,26);
				draw_pixel_array(casio_logo_3, 73,26);
				break;
			case OFF:
				break;
			case ONETHREEAC_RESET:
				break;
		}

		Bdisp_PutDisp_DD(); //update screen
    	}

    	return 1;
}




//****************************************************************************
//**************                                              ****************
//**************                 Notice!                      ****************
//**************                                              ****************
//**************  Please do not change the following source.  ****************
//**************                                              ****************
//****************************************************************************


#pragma section _BR_Size
unsigned long BR_Size;
#pragma section


#pragma section _TOP

//****************************************************************************
//  InitializeSystem
//
//  param   :   isAppli   : 1 = Application / 0 = eActivity
//              OptionNum : Option Number (only eActivity)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
int InitializeSystem(int isAppli, unsigned short OptionNum)
{
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}

#pragma section

