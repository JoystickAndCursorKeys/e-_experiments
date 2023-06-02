unsigned char buffer[256];
signed char primes[] = {  2, 3, 5, 7, 11, 13, 17, 19, 23, 29,  31, 37, 41, 43, 47, 53, 59, 61, 67, 71,  73, 79, 83, 89, 97 };
unsigned char cntu[20], cntd[20];
unsigned char step = 1, step2 = 0, step2b = 0, step3 = 0, flip = 1;


void seedRnd( unsigned int seed ) {

    for( unsigned byte i=0; i<20; i=i+1 ) {
        unsigned char v;
        
        v = (unsigned char) primes[i];
        v = v ^ BYTE0( seed );
        v = v ^ BYTE1( seed );
        cntu[i] = v;

        v = (unsigned char) primes[i];
        v = v ^ BYTE1( seed );
        v = v ^ BYTE0( seed );
        cntd[i] = v;
    }

} 

void initRnd() {
    for( int i=0; i<=256; i++ ) {
        buffer[i] = (unsigned byte) i;
    }

    for( int i=0; i<=256; i++ ) {
        unsigned byte i1 = getSimpleRnd();
        unsigned byte i2 = i;

        if( i1 != i2 ) {
            unsigned byte tmp;
            tmp = buffer[ i1 ];
            buffer[ i1 ] = buffer[ i2 ];
            buffer[ i2 ] = tmp;
        }
    }  

    seedRnd( 1+4+16+64+256+1024+4096+16384 );
}


inline unsigned byte getRandom() {

    step2++;
    if( step2 > 253 ) {
        step2b++;
        step2 = 0;
        if( step2b > 5) {
            initRnd();
            step2b= 0 ;
        }
        
    }

    unsigned byte i = getSimpleRnd();

    return buffer[ i ];
}


inline unsigned byte getSimpleRnd() {

    step++;
    if( step > 20-2 ) { step =1 ; }

    for( unsigned byte i=0; i<20; i=i+step ) {
        unsigned char v;
        signed char delta;
        v = cntu[i];
        delta = primes[i];
        v+=delta;
        cntu[i] = v;

        v = cntd[i];
        delta = primes[20-i]-1;
        v-=delta;
        cntd[i] = v;
    }

    unsigned byte result = 1+4+16+64;
    for( unsigned byte i=0; i<20; i+=step) {
        unsigned char v;
        v = cntu[i];        
        result = result ^ v;

        v = cntd[i];        
        result = result ^ v;        
    }

    step3++;
    if( step3 > 100) {
        flip = 1 - flip;
        step3 = 0;
    }
    if( flip ) {
        result = result ^ ( 2 + 8 + 32 + 128 ); 
    }
    return result;

}

/* testing out the random routing, using some screen functions that are not included in this file */

void main() {

    print_cls();
    initRnd();
    seedRnd(27181);

    for( int i=0; i<12500; i++ ) {
        unsigned byte x,y;

        x = (unsigned byte)  getRandom();
        x = buffer[ x ];
        x = ubslow_modulus(x, 40); 

        y = (unsigned byte) getRandom();
        y = buffer[ y ];
        y = ubslow_modulus(y, 25); 

        ezt_putchar( x, y, (unsigned char) i, 1 );
        
    }
}
