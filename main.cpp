#include <iostream>

const unsigned char generatorPolynomial[] = {0x2f,0x15};

void displayCharAsBits(unsigned char c) {
	unsigned char mask = 0x80;
	for (unsigned int i = 0; i < 8; i++) {
		std::cout << ( (c & mask)>0 ? '1' : '0' );
		mask = mask >> 1;
	}
	return;
}

unsigned int numLeadingZeros(const unsigned char* bits, unsigned int numBytes) {
    unsigned int index = 0;
    unsigned int endValue = numBytes * 8;
    unsigned char mask = 0x00;
    for (;index < numBytes; index++) {
        mask = 0x80;
        for (int i = 0; i < 8; i++) {
            if((bits[index] & mask) > 1) {
                return (index * 8) + i;
            }
            mask = mask >> 1;
        }
    }
    return endValue;
}

unsigned char* crcRemainder(unsigned char* inputBits, unsigned int inputSize, unsigned char polynomialBits[], unsigned int polynomialSize, unsigned char initialFiller) {
	/*
		1.  Create a blank array of appropriate length (input + remainder)
		2.	Populate the first part of the blank array with the input bits
		3.	While there is a 1 in the padded input before the remainder,
			a)	Move to the index of the leading 1
			b)	Perform a bitwise XOR with the generator polynomial on the <inputSize> bits beginning at the index just moved to
			c)  Record the result of the XOR operation in the place of the <inputSize> bits just XORed
		4.  Extract the last <polynomialSize - 1> bits from the padded input
		5.  Return bits extracted in 4
	*/
	unsigned int paddedInputSize = inputSize + polynomialSize;
	unsigned char* paddedInput = new unsigned char [paddedInputSize];
	unsigned int bitOffset = numLeadingZeros(inputBits,inputSize) + numLeadingZeros(polynomialBits,polynomialSize);
	
	for (unsigned int i = 0; i < (inputSize * 8); i++) {
		paddedInput[i] = (inputBits[i] >> bitOffset);
	}
	return paddedInput;
}

int main()
{
    unsigned char message[] = {0x50,0x6f,0x6f,0x70};
    unsigned int messageLength = sizeof(message);
    for (unsigned int i = 0; i < messageLength; i++) {
        if (i > 0) {
            std::cout << ' ';
        }
        displayCharAsBits(message[i]);
    }
    std::cout << std::endl;
    std::cout << numLeadingZeros(message,messageLength);
    return 0;
}
