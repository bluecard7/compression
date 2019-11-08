#include "bitbuf.h"

void initBitBuffer(BitBuffer * bb){
	bb->buffer = 0;
	bb->numBits = 0;
}

void writeBit(BitBuffer * bb, char bit){
	bb->buffer <<= 1;
	bb->buffer |= bit;
	++bb->numBits; 
}

char isFull(BitBuffer * bb){
	return bb->numBits == 8 ? 1: 0;
}

char showBuffer(BitBuffer * bb){
	return bb->buffer;
}
