#ifndef BITBUFFER
#define BITBUFFER

typedef
struct BitBuffer{
	char buffer;
	char numBits;
};

// want a popBit operation

void initBitBuffer(BitBuffer * );
void writeBit(BitBuffer *, char);
char isFull(BitBuffer *);
char showBuffer(BitBuffer *);

#endif 