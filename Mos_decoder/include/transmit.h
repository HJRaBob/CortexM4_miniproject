/*
 * transmit.h
 *
 *  Created on: 2017. 9. 6.
 *      Author: student
 */

#ifndef TRANSMIT_H_
#define TRANSMIT_H_

char MOS[30] = {' ','\0','e','t','i','a','n','m','s','u','r','w','d','k','g','o','h','v','f','\0','l','\0','p','j','b','x','c','y','z','q'};

int tim = 0;

int c_trans(char asc)
{
	switch(asc){
	case 'a' : tim = 2; return 0x10;
	case 'b' : tim = 4; return 0x0001;
	case 'c' : tim = 4; return 0x0101;
	case 'd' : tim = 3; return 0x001;
	case 'e' : tim = 1; return 0x0;
	case 'f' : tim = 4; return 0x0100;
	case 'g' : tim = 3; return 0x011;
	case 'h' : tim = 4; return 0x0000;
	case 'i' : tim = 2; return 0x00;
	case 'j' : tim = 4; return 0x1110;
	case 'k' : tim = 3; return 0x101;
	case 'l' : tim = 4; return 0x0010;
	case 'm' : tim = 2; return 0x11;
	case 'n' : tim = 2; return 0x01;
	case 'o' : tim = 3; return 0x111;
	case 'p' : tim = 4; return 0x0110;
	case 'q' : tim = 4; return 0x1011;
	case 'r' : tim = 3; return 0x010;
	case 's' : tim = 3; return 0x000;
	case 't' : tim = 1; return 0x1;
	case 'u' : tim = 3; return 0x100;
	case 'v' : tim = 4; return 0x1000;
	case 'w' : tim = 3; return 0x110;
	case 'x' : tim = 4; return 0x1001;
	case 'y' : tim = 4; return 0x1101;
	case 'z' : tim = 4; return 0x0011;
	default	 : tim = 0; return 0x0;
	}
}

#endif /* TRANSMIT_H_ */
