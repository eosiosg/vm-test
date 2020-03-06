//
// Created by Vince on 4/3/20.
//
#include <openssl/sha.h>
#include <openssl/ripemd.h>
#include <utility>

using uint128_t           = unsigned __int128;

using namespace std;
typedef vector<uint64_t> obj_type;
typedef map<uint64_t, obj_type> table_type;
typedef pair<pair<uint64_t, uint64_t>, obj_type*> kv_type;
typedef vector<char> bytes;

namespace eosio { namespace chain {
        template<typename T>
        struct array_ptr {
            explicit array_ptr(T *value) : value(value) {}

            typename std::add_lvalue_reference<T>::type operator*() const {
                return *value;
            }

            T *operator->() const noexcept {
                return value;
            }

            operator T *() const {
                return value;
            }

            T *value;
        };

/**
 * class to represent an in-wasm-memory char array that must be null terminated
 */
        struct null_terminated_ptr {
            explicit null_terminated_ptr(char *value) : value(value) {}

            typename std::add_lvalue_reference<char>::type operator*() const {
                return *value;
            }

            char *operator->() const noexcept {
                return value;
            }

            operator char *() const {
                return value;
            }

            char *value;
        };
    }
}
struct db_type {
    map<uint64_t, table_type> db = {};

    auto find(uint64_t table) {
        return db.find(table);
    }

    auto end() {
        return db.end();
    }

    auto begin() {
        return db.begin();
    }

    auto update(uint64_t table, table_type tab_obj) {
        db[table] = tab_obj;
    }

    auto update_row(uint64_t table, uint64_t id, eosio::chain::array_ptr<const char> buffer, uint32_t buffer_size ) {

        if (db[table].find(id) == db[table].end()) {
            db[table][id] = obj_type{};
            db[table][id].resize(sizeof(uint64_t) * buffer_size);
        }
        copy(buffer.value, buffer + sizeof(uint64_t) * buffer_size, back_inserter(db[table][id]));

    }

    auto find_row(uint64_t table, uint64_t id) {
        return db[table].find(id);
    }

    auto table_end(uint64_t table) {
        return db[table].end();
    }

    auto get_row(uint64_t table, uint64_t id) {
        return &db[table][id];
    }

    auto remove_row (uint64_t table, uint64_t id) {
        if (db[table].find(id) != db[table].end()) db[table].erase(id);
        if (db[table].empty()) db.erase(table);
    }

    void print_all() {
        for (auto &it : db) {
            cout << it.first << " ";
            for (auto &i : it.second) {
                cout << i.first << " " << i.second.size() << "\n";
            }
        }
    }
};

constexpr char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                           '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

namespace eosio {
    namespace vm {


        template <> struct wasm_type_converter<uint64_t *> : linear_memory_access {
            uint64_t *from_wasm(void *val) {
                return (uint64_t *)val;
            }

            const void *to_wasm(uint64_t *val) {
                return val;
            }
        };

        template <> struct wasm_type_converter<const uint64_t *> : linear_memory_access {
            const uint64_t *from_wasm(void *val) {
                return (uint64_t *)val;
            }

            const void *to_wasm(const uint64_t *val) {
                return val;
            }
        };

        template <> struct wasm_type_converter<float128_t *> : linear_memory_access {
            float128_t *from_wasm(void *val) {
                return (float128_t *)val;
            }

            const void *to_wasm(float128_t *val) {
                return val;
            }
        };

        template<>
        struct wasm_type_converter<name> {
            static auto from_wasm(uint64_t val) {
                return name{val};
            }
            static auto to_wasm(name val) {
                return val.value;
            }
        };

        template<typename T>
        struct wasm_type_converter<T*> : linear_memory_access {
            auto from_wasm(void* val) {
                validate_ptr<T>(val, 1);
                return eosio::vm::aligned_ptr_wrapper<T, alignof(T)>{val};
            }
        };

        template<>
        struct wasm_type_converter<char*> : linear_memory_access {
            void* to_wasm(char* val) {
                validate_ptr<char>(val, 1);
                return val;
            }
        };

        template <>
        struct wasm_type_converter<const char*> : linear_memory_access {
            const char* from_wasm(const void* val) {
                validate_c_str(val);
                return static_cast<const char*>(val);
            }
        };

        template<typename T>
        struct wasm_type_converter<T&> : linear_memory_access {
            auto from_wasm(uint32_t val) {
                EOS_VM_ASSERT( val != 0, wasm_memory_exception, "references cannot be created for null pointers" );
                void* ptr = get_ptr(val);
                validate_ptr<T>(ptr, 1);
                return eosio::vm::aligned_ref_wrapper<T, alignof(T)>{ptr};
            }
        };

        template<typename T>
        struct wasm_type_converter<eosio::chain::array_ptr<T>> : linear_memory_access {
            auto from_wasm(void* ptr, uint32_t size) {
                validate_ptr<T>(ptr, size);
                return aligned_array_wrapper<T, alignof(T)>(ptr, size);
            }
        };

        template<>
        struct wasm_type_converter<eosio::chain::array_ptr<char>> : linear_memory_access {
            auto from_wasm(void* ptr, uint32_t size) {
                validate_ptr<char>(ptr, size);
                return eosio::chain::array_ptr<char>((char*)ptr);
            }
            // memcpy/memmove
            auto from_wasm(void* ptr, eosio::chain::array_ptr<const char> /*src*/, uint32_t size) {
                validate_ptr<char>(ptr, size);
                return eosio::chain::array_ptr<char>((char*)ptr);
            }
            // memset
            auto from_wasm(void* ptr, int /*val*/, uint32_t size) {
                validate_ptr<char>(ptr, size);
                return eosio::chain::array_ptr<char>((char*)ptr);
            }
        };

        template<>
        struct wasm_type_converter<eosio::chain::array_ptr<const char>> : linear_memory_access {
            auto from_wasm(void* ptr, uint32_t size) {
                validate_ptr<char>(ptr, size);
                return eosio::chain:: array_ptr<const char>((char*)ptr);
            }
            // memcmp
            auto from_wasm(void* ptr, eosio::chain::array_ptr<const char> /*src*/, uint32_t size) {
                validate_ptr<char>(ptr, size);
                return eosio::chain::array_ptr<const char>((char*)ptr);
            }
            // memset
            auto from_wasm(void* ptr, int /*val*/, uint32_t size) {
                validate_ptr<char>(ptr, size);
                return eosio::chain::array_ptr<const char>((char*)ptr);
            }
        };

        template<>
        struct wasm_type_converter<eosio::chain::array_ptr<unsigned char>> : linear_memory_access {
            auto from_wasm(void* ptr, uint32_t size) {
                validate_ptr<unsigned char>(ptr, size);
                return eosio::chain::array_ptr<unsigned char>((unsigned char*)ptr);
            }
            // memcmp
            auto from_wasm(void* ptr, eosio::chain::array_ptr<unsigned char> /*src*/, uint32_t size) {
                validate_ptr<unsigned char>(ptr, size);
                return eosio::chain::array_ptr<unsigned char>((unsigned char*)ptr);
            }
            // memset
            auto from_wasm(void* ptr, int /*val*/, uint32_t size) {
                validate_ptr<unsigned char>(ptr, size);
                return eosio::chain::array_ptr<unsigned char>((unsigned char*)ptr);
            }
        };

        template<>
        struct wasm_type_converter<eosio::chain::null_terminated_ptr> : linear_memory_access {
            auto from_wasm(void* ptr) {
                validate_c_str(ptr);
                return eosio::chain::null_terminated_ptr{ static_cast<char*>(ptr) };
            }
        };
    } // namespace vm
} // namespace eosio

using namespace eosio::chain;
class mocked_context {
public:
    mocked_context(uint64_t receiver, uint64_t account, uint64_t name, bytes action_data, db_type& db)
    :receiver(receiver)
    ,account(account)
    ,action_name(name)
    ,action_data(std::move(action_data))
    ,db(db){}

    char* memcpy( array_ptr<char> dest, array_ptr<const char> src, uint32_t length) {
        return (char *)::memcpy(dest, src, length);
    }

    char* memmove( array_ptr<char> dest, array_ptr<const char> src, uint32_t length) {
        return (char *)::memmove(dest, src, length);
    }

    int memcmp( array_ptr<const char> dest, array_ptr<const char> src, uint32_t length) {
        int ret = ::memcmp(dest, src, length);
        if(ret < 0)
            return -1;
        if(ret > 0)
            return 1;
        return 0;
    }

    char* memset( array_ptr<char> dest, int value, uint32_t length ) {
        return (char *)::memset( dest, value, length );
    }
    void prints(null_terminated_ptr str) { std::cout << static_cast<const char*>(str) << std::endl; }
    void printui(uint64_t val) { std::cout << val << std::endl; }

    void printhex(array_ptr<const char> data, uint32_t data_len ) {

        string str(data_len * 2, ' ');
        for (int i = 0; i < data_len; ++i) {
            str[2 * i]     = hexmap[(data[i] & 0xF0) >> 4];
            str[2 * i + 1] = hexmap[data[i] & 0x0F];
        }
        std::cout << str << std::endl;
    }


    void printi(int64_t val) {
        std::ostringstream oss;
        oss << val;
        std::cout <<  oss.str() << std::endl;
    }

    void eosio_assert(bool test, null_terminated_ptr msg) {
        if (!test) {
            std::cout << static_cast<const char*>(msg) << std::endl;
            throw 0;
        }
    }

    void eosio_assert_code(bool condition, uint64_t error_code) {
        if (!condition) {
            std::cout << error_code << std::endl;
            throw 0;
        }
    }

    void require_auth( uint64_t account ) {
    }

    uint64_t current_receiver() {
        return receiver;
    }
    void abort() {}

    bool is_account() {
        return true;
    }

    void require_recipient( uint64_t recipient ) {
    }

    bool has_auth( uint64_t account ) {
        return true;
    }

    int action_data_size() {
        return action_data.size();;
    }

    int read_action_data(array_ptr<char> memory, uint32_t buffer_size) {

        auto s = action_data.size();
        if (buffer_size == 0) return s;
        auto copy_size = std::min(static_cast<size_t>(buffer_size), s);

        ::memcpy( (char*)memory.value,  action_data.data(), copy_size);

        return copy_size;
    }

    void __extendsftf2( float128_t* ret, float f ) {
        *ret = f32_to_f128( to_softfloat32(f) );
    }

    void __floatsitf( float128_t* ret, int32_t i ) {
        *ret = i32_to_f128(i);
    }

    void __multf3( float128_t* ret, uint64_t la, uint64_t ha, uint64_t lb, uint64_t hb ) {
        float128_t a = {{ la, ha }};
        float128_t b = {{ lb, hb }};
        *ret = f128_mul( a, b );
    }

    void __floatunsitf( float128_t* ret, uint32_t i ) {
        *ret = ui32_to_f128(i);
    }

    void __divtf3( float128_t* ret, uint64_t la, uint64_t ha, uint64_t lb, uint64_t hb ) {
        float128_t a = {{ la, ha }};
        float128_t b = {{ lb, hb }};
        *ret = f128_div( a, b );
    }

    void __addtf3( float128_t* ret, uint64_t la, uint64_t ha, uint64_t lb, uint64_t hb ) {
        float128_t a = {{ la, ha }};
        float128_t b = {{ lb, hb }};
        *ret = f128_add( a, b );
    }

    static bool is_nan( const float128_t f ) {
        return f128_is_nan( f );
    }

    int __unordtf2( uint64_t la, uint64_t ha, uint64_t lb, uint64_t hb ) {
        float128_t a = {{ la, ha }};
        float128_t b = {{ lb, hb }};
        if ( is_nan(a) || is_nan(b) )
            return 1;
        return 0;
    }

    int ___cmptf2( uint64_t la, uint64_t ha, uint64_t lb, uint64_t hb, int return_value_if_nan ) {
        float128_t a = {{ la, ha }};
        float128_t b = {{ lb, hb }};
        if ( __unordtf2(la, ha, lb, hb) )
            return return_value_if_nan;
        if ( f128_lt( a, b ) )
            return -1;
        if ( f128_eq( a, b ) )
            return 0;
        return 1;
    }

    void __extenddftf2( float128_t* ret, double d ) {
        *ret = f64_to_f128( to_softfloat64(d) );
    }

    int __eqtf2( uint64_t la, uint64_t ha, uint64_t lb, uint64_t hb ) {
        return ___cmptf2(la, ha, lb, hb, 1);
    }

    int __letf2( uint64_t la, uint64_t ha, uint64_t lb, uint64_t hb ) {
        return ___cmptf2(la, ha, lb, hb, 1);
    }

    int __netf2( uint64_t la, uint64_t ha, uint64_t lb, uint64_t hb ) {
        return ___cmptf2(la, ha, lb, hb, 1);
    }

    void __subtf3( float128_t* ret, uint64_t la, uint64_t ha, uint64_t lb, uint64_t hb ) {
        float128_t a = {{ la, ha }};
        float128_t b = {{ lb, hb }};
        *ret = f128_sub( a, b );
    }

    double __trunctfdf2( uint64_t l, uint64_t h ) {
        float128_t f = {{ l, h }};
        return from_softfloat64(f128_to_f64( f ));
    }

    int __getf2( uint64_t la, uint64_t ha, uint64_t lb, uint64_t hb ) {
        return ___cmptf2(la, ha, lb, hb, -1);
    }

    float __trunctfsf2( uint64_t l, uint64_t h ) {
        float128_t f = {{ l, h }};
        return from_softfloat32(f128_to_f32( f ));
    }

    void prints_l(const char *str, uint32_t str_len ) {
        std::cout << string(str, str_len);
    }

    uint32_t __fixunstfsi( uint64_t l, uint64_t h ) {
        float128_t f = {{ l, h }};
        return f128_to_ui32( f, 0, false );
    }

    int32_t __fixtfsi( uint64_t l, uint64_t h ) {
        float128_t f = {{ l, h }};
        return f128_to_i32( f, 0, false );
    }

    void __multi3(uint128_t* ret, uint64_t la, uint64_t ha, uint64_t lb, uint64_t hb) {
        uint128_t lhs = ha;
        uint128_t rhs = hb;

        lhs <<= 64;
        lhs |=  la;

        rhs <<= 64;
        rhs |=  lb;

        lhs *= rhs;
        *ret = lhs;
    }

    void __ashlti3(uint128_t* ret, uint64_t low, uint64_t high, uint32_t shift) {

        uint128_t i;
        i = (uint128_t{high} << 64) | low;
        i <<= shift;
        *ret = i;
    }

    int db_find_i64( uint64_t code, uint64_t scope, uint64_t table, uint64_t id ) {
        auto tb = db.find(table);
        if (tb == db.end()) return -1;
        auto i = 0;
        for (auto itr = tb->second.begin(); itr != tb->second.end(); i++) {
            if (itr->first == id) return i;
            ++i;
        }
        return -1;
    }

    int db_store_i64( uint64_t scope, uint64_t table, uint64_t payer, uint64_t id, array_ptr<const char> buffer, uint32_t buffer_size ) {
            auto tb = db.find(table);
            if (tb == db.end()) {
                db.update(table, table_type{});
            }

            if (db.find_row(table, id) == db.table_end(table)) {
                db.update_row(table, id, buffer, buffer_size);

                keyval_cache.emplace_back(kv_type{{table, id}, db.get_row(table, id)});

                return keyval_cache.size() - 1;
            }

            for (auto i = 0; i < keyval_cache.size(); ++i) {
                if (keyval_cache[i].first.first == table && keyval_cache[i].first.second == id) {
                    db.update_row(table, id, buffer, buffer_size);
                    return i;
                }
            }
            return -1;
    }

    void db_update_i64( int itr, uint64_t payer, array_ptr<const char> buffer, uint32_t buffer_size ) {
            if (itr >= keyval_cache.size()) return;
            auto data = *keyval_cache[itr].second;
            data.reserve(sizeof(uint64_t) * buffer_size);

            copy(buffer.value, buffer + sizeof(uint64_t) * buffer_size, back_inserter(data));

            db.update_row(keyval_cache[itr].first.first, keyval_cache[itr].first.second, buffer, buffer_size);

    }

    int db_next_i64( int itr, uint64_t* primary ) {
        if( itr < -1 || itr >= keyval_cache.size()) return -1;
        auto table = keyval_cache[itr].first.first;
        *primary = keyval_cache[itr].first.second + 1;
        keyval_cache.emplace_back(kv_type{{table, *primary}, nullptr});
        return static_cast<size_t>(keyval_cache.size()) - 1;
    }

    int db_get_i64( int itr, array_ptr<char> buffer, uint32_t buffer_size ) {
        if( itr < 0 || itr >= keyval_cache.size()) return 0;
        auto s = keyval_cache[itr].second->size();
        if( buffer_size == 0 ) return s;

        auto copy_size = std::min( static_cast<size_t>(buffer_size), s );
        ::memcpy( buffer.value, keyval_cache[itr].second->data(), copy_size );

        return copy_size;
    }

    void db_remove_i64( int itr ) {
        if( itr < 0 || itr >= keyval_cache.size()) return;
        auto table = keyval_cache[itr].first.first;
        auto id = keyval_cache[itr].first.second;
        db.remove_row(table, id);
        keyval_cache.erase(keyval_cache.begin() + itr);
    }


    void assert_sha256(array_ptr<char> data, uint32_t datalen, unsigned char *hash_val) {
        unsigned char result[SHA256_DIGEST_LENGTH];
        sha256(data, datalen, result);
//        result == hash_val;
    }


    void assert_sha1(array_ptr<char> data, uint32_t datalen, unsigned char *hash_val) {
        unsigned char result[SHA_DIGEST_LENGTH];
        sha1( data, datalen, result);
//        result == hash_val;
    }

    void assert_sha512(array_ptr<char> data, uint32_t datalen, unsigned char *hash_val) {
        unsigned char result[SHA512_DIGEST_LENGTH];
        sha512( data, datalen, result);
//        result == hash_val;
    }

    void assert_ripemd160(array_ptr<char> data, uint32_t datalen, unsigned char *hash_val) {
        unsigned char result[RIPEMD160_DIGEST_LENGTH];
        ripemd160( data, datalen, result);
//        result == hash_val;
    }

    void sha1(array_ptr<char> data, uint32_t datalen, unsigned char *hash_val) {
        SHA1(reinterpret_cast<const unsigned char *>(data.value), datalen, (unsigned char *) hash_val);
    }

    void sha256(array_ptr<char> data, uint32_t datalen, unsigned char *hash_val) {
        SHA256( reinterpret_cast<const unsigned char *>(data.value), datalen, (unsigned char *) hash_val);
    }

    void sha512(array_ptr<char> data, uint32_t datalen, unsigned char *hash_val) {
        SHA512( reinterpret_cast<const unsigned char *>(data.value), datalen, (unsigned char *) hash_val);
    }

    void ripemd160(array_ptr<char> data, uint32_t datalen, unsigned char *hash_val) {
        RIPEMD160( reinterpret_cast<const unsigned char *>(data.value), datalen, (unsigned char *) hash_val);
    }

    int recover_key(const char *digest, const char *sig, size_t siglen, const char *pub, size_t publen) {
        return 0;
    }

    void assert_recover_key(const char *digest, const char *sig, size_t siglen, const char *pub, size_t publen) {
    }

    void set_blockchain_parameters_packed(const char *packed_blockchain_parameters, size_t datalen) {
    }

    size_t get_blockchain_parameters_packed(const char *packed_blockchain_parameters, size_t buffer_size) {
        return 0;
    }

    void set_proposed_producers(const char *packed_producer_schedule, size_t datalen) {
    }

    uint64_t current_time() {
        return static_cast<uint64_t>(std::time(nullptr));
    }

    int get_active_producers(const char *producers, size_t buffer_size) {
        return 0;
    }

    int db_lowerbound_i64(uint64_t code, uint64_t scope, uint64_t table, uint64_t id) {
        auto tab = db.find(table);
        if (tab == db.end()) return -1;
        return 0;
    }

    int db_idx256_lowerbound(uint64_t code, uint64_t scope, uint64_t table, array_ptr<uint128_t> data, uint32_t data_len, uint64_t& primary) {
        return 0;
    }
    int db_idx256_find_primary(uint64_t code, uint64_t scope, uint64_t table, array_ptr<uint128_t> data, uint32_t data_len, uint64_t& primary) {
        return 0;
    }
    void db_idx256_update( int iterator, uint64_t payer, array_ptr<const uint128_t> data, uint32_t data_len ) {

    }
    int db_idx64_find_primary(uint64_t code, uint64_t scope, uint64_t table, uint64_t& secondary, uint64_t primary) {
        return 0;
    }
    void db_idx64_update( int iterator, uint64_t payer, const uint64_t& secondary ) {

    }
    int db_idx256_store( uint64_t scope, uint64_t table, uint64_t payer, uint64_t id, array_ptr<const uint128_t> data, uint32_t data_len ) {
        return 0;
    }

    int db_end_i64( uint64_t code, uint64_t scope, uint64_t table ) {
        auto tab = db.find(table);
        if (tab == db.end()) return -1;
        return 0;
    }

    int db_previous_i64( int itr, uint64_t& primary ) {
        if( itr < -1 || itr >= keyval_cache.size()) return -1;
        auto table = keyval_cache[itr].first.first;
        primary = keyval_cache[itr].first.second - 1;
        keyval_cache.emplace_back(kv_type{{table, primary}, nullptr});
        return keyval_cache.size() - 1;
    }

    int db_idx64_store( uint64_t scope, uint64_t table, uint64_t payer, uint64_t id, const uint64_t& secondary ) {
        return 0;
    }

    int db_idx64_lowerbound(uint64_t code, uint64_t scope, uint64_t table,  uint64_t& secondary, uint64_t& primary) {
        return 0;
    }

    void send_inline(array_ptr<char> data, uint32_t data_len) {

    }


private:
    vector<kv_type>                     keyval_cache;
    db_type&                            db;
    uint64_t                            receiver;
    uint64_t                            account;
    uint64_t                            action_name;
    bytes                               action_data = {};
};
