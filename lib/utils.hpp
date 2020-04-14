//
// Created by Vince on 11/4/20.
//

using uint128_t           = unsigned __int128;

std::ostream& operator<<( std::ostream& dest, uint128_t value )
{
    std::ostream::sentry s( dest );
    if ( s ) {
        uint128_t tmp = value;
        char buffer[ 128 ];
        char* d = std::end( buffer );
        do
        {
            -- d;
            *d = "0123456789"[ tmp % 10 ];
            tmp /= 10;
        } while ( tmp != 0 );

        int len = std::end( buffer ) - d;
        if ( dest.rdbuf()->sputn( d, len ) != len ) {
            dest.setstate( std::ios_base::badbit );
        }
    }
    return dest;
}

std::ostream& operator<<( std::ostream& dest, array<uint128_t, 2> value )
{
    for (auto& e: value) {
        dest << e << " ";
    }
    return dest;
}

char const hex_chars[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

string bytes_to_hex(char* data, size_t data_length) {
    string ret;
    for( auto i = 0; i < data_length; ++i )
    {
        const char ch = data[i];
        ret.append(&hex_chars[(ch  & 0xF0) >> 4], 1);
        ret.append(&hex_chars[ch & 0xF], 1);
    }
    return ret;
}

string unescape(const string& s)
{
    auto ret = s;
    ret.erase(remove(ret.begin(), ret.end(), '\n'), ret.end());
    ret.erase(remove(ret.begin(), ret.end(), '\t'), ret.end());
    ret.erase(remove(ret.begin(), ret.end(), '\r'), ret.end());
    return ret;
}

std::map<std::string, std::string> mappify(std::string const& s)
{
    std::map<std::string, std::string> ret;
    Json::Value root;
    JSONCPP_STRING err;
    Json::CharReaderBuilder builder;
    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    if (!reader->parse(s.c_str(), s.c_str() + s.size(), &root, &err)) {
        std::cout << "error" << std::endl;
        return ret;
    }

    Json::StreamWriterBuilder writer;

    for (auto const& key : root.getMemberNames()) {
        if (root[key].isArray()) ret[key] = unescape(Json::writeString(writer, root[key]));
        else ret[key] = unescape(root[key].asString());
    }
    return ret;
}

std::vector<unsigned char> hex_to_bytes(const std::string &str) {
    std::vector<unsigned char> bytes;

    for (unsigned int i = 0; i < str.length(); i += 2) {
        std::string byteString = str.substr(i, 2);

        auto bin = (uint8_t) strtol(byteString.c_str(), NULL, 16);
        bytes.push_back(bin);
    }

    return bytes;
}

uint128_t hex_to_u128(string str)
{
    uint128_t ret = 0;
    auto i = 0;
    while (i < str.size()) {
        // get current character then increment
        uint8_t byte = str[i];
        i++;
        // transform hex character to the 4bit equivalent number, using the ascii table indexes
        if (byte >= '0' && byte <= '9') byte = byte - '0';
        else if (byte >= 'a' && byte <='f') byte = byte - 'a' + 10;
        else if (byte >= 'A' && byte <='F') byte = byte - 'A' + 10;
        // shift 4 to make space for new digit, and add the 4 bits of the new digit
        ret = (ret << 4) | (byte & 0xF);
    }
    return ret;
}

template< typename T >
std::string int_to_hex( T i )
{
    std::stringstream stream;
    stream << "0x"
           << std::setfill ('0') << std::setw(sizeof(T)*2)
           << std::hex << i;
    return stream.str();
}

string u256_to_hex(const array<uint128_t, 2>& addr) {
    auto high = addr[0];
    auto low = addr[1];
    return int_to_hex(high) + int_to_hex(low).substr(2);
}

std::string bytes_to_hex_str(const uint8_t* val, size_t val_count)
{
    string ret(val_count * 2, ' ');
    for (size_t i = 0; i < val_count; i++)
    {
        ret[(i * 2) + 0] = hex_chars[((val[i] & 0xF0) >> 4)];
        ret[(i * 2) + 1] = hex_chars[((val[i] & 0x0F) >> 0)];
    }
    return "0x" + string(ret);
}

int64_t hex_to_i64(const string& str) {
    int64_t value;
    std::istringstream iss(str);
    iss >> value;
    return value;
}

uint64_t hex_to_ui64(const string& str) {
    uint64_t value;
    std::istringstream iss(str);
    iss >> value;
    return value;
}