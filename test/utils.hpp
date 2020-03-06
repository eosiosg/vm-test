//
// Created by Vince on 4/3/20.
//

uint8_t from_hex( char c ) {
    if( c >= '0' && c <= '9' )
        return c - '0';
    if( c >= 'a' && c <= 'f' )
        return c - 'a' + 10;
    if( c >= 'A' && c <= 'F' )
        return c - 'A' + 10;
    return 0;
}

std::string to_hex( const char* d, uint32_t s )
{
    std::string r;
    const char* to_hex="0123456789abcdef";
    uint8_t* c = (uint8_t*)d;
    for( uint32_t i = 0; i < s; ++i )
        (r += to_hex[(c[i]>>4)]) += to_hex[(c[i] &0x0f)];
    return r;
}