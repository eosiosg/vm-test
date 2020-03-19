//
// Created by Vince on 4/3/20.
//
#include <openssl/sha.h>
#include <openssl/ripemd.h>
#include <utility>

#include "other_fc.hpp"
#include "serialization.hpp"

using uint128_t           = unsigned __int128;

using namespace std;
typedef vector<char> obj_type;
typedef map<uint64_t, obj_type> table_type;
typedef pair<pair<pair<uint64_t, uint64_t>, uint64_t>, obj_type*> kv_type;
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
    map<pair<uint64_t, uint64_t>, table_type> db = {};

    auto find(pair<uint64_t, uint64_t> table) {
        return db.find(table);
    }

    auto end() {
        return db.end();
    }

    auto begin() {
        return db.begin();
    }

    auto update(pair<uint64_t, uint64_t> table, table_type tab_obj) {
        db[table] = std::move(tab_obj);
    }

    auto update_row(pair<uint64_t, uint64_t> table, uint64_t id, eosio::chain::array_ptr<const char> buffer, uint32_t buffer_size ) {

        if (db[table].find(id) == db[table].end()) {
            db[table][id] = obj_type{};
            db[table][id].resize(buffer_size);
        }
        ::memcpy(db[table][id].data(), buffer.value, buffer_size);

    }

    auto find_row(pair<uint64_t, uint64_t> table, uint64_t id) {
        return db[table].find(id);
    }

    auto table_end(pair<uint64_t, uint64_t> table) {
        return db[table].end();
    }

    auto get_row(pair<uint64_t, uint64_t> table, uint64_t id) {
        return &db[table][id];
    }

    auto remove_row (pair<uint64_t, uint64_t> table, uint64_t id) {
        if (db[table].find(id) != db[table].end()) db[table].erase(id);
        if (db[table].empty()) db.erase(table);
    }

    void print_all() {
        for (auto &it : db) {
            cout << it.first.first << " " << it.first.second << " ";
            for (auto &i : it.second) {
                cout << i.first << " " << i.second.size() << "\n";
            }
        }
    }
};

template<typename secondary_key>
struct secondary_key_type {

    typedef vector<pair<uint64_t, secondary_key>> secondary_index_type;
    map<pair<uint64_t, uint64_t>, secondary_index_type> sec_indexes = {};

    function<bool(pair<uint64_t, secondary_key>, pair<uint64_t, secondary_key>)> compFunctor =
            [](pair<uint64_t, secondary_key> elem1 ,pair<uint64_t, secondary_key> elem2) -> bool {
                return elem1.second < elem2.second;
            };

    auto find(pair<uint64_t, uint64_t> table) {
        return sec_indexes.find(table);
    }

    auto end() {
        return sec_indexes.end();
    }

    auto begin() {
        return sec_indexes.begin();
    }

    auto update(pair<uint64_t, uint64_t> table, secondary_index_type sec_obj) {
        sec_indexes[table] = sec_obj;
    }

    void update_row(pair<uint64_t, uint64_t> table, uint64_t primary, const secondary_key& new_secondary) {
        for (auto itr = sec_indexes[table].begin(); itr != sec_indexes[table].end(); itr++) {
            if (itr->first == primary) {
                itr->second = new_secondary;
                sort(sec_indexes[table].begin(), sec_indexes[table].end(), compFunctor);
                break;
            }
        }
    }

    auto store_row(pair<uint64_t, uint64_t> table, const secondary_key& secondary, uint64_t primary) {
        for (auto itr = sec_indexes[table].begin(); itr != sec_indexes[table].end(); itr++) {
            if (itr->first == primary) {
                itr->second = secondary;
                sort(sec_indexes[table].begin(), sec_indexes[table].end(), compFunctor);
                return;
            }
        }
        sec_indexes[table].emplace_back(pair{primary, secondary});
        sort(sec_indexes[table].begin(), sec_indexes[table].end(), compFunctor);
    }

    auto find_row(pair<uint64_t, uint64_t> table, uint64_t primary) {
        for (auto itr = sec_indexes[table].begin(); itr != sec_indexes[table].end(); itr++) {
            if (itr->first == primary) {
                return itr;
            }
        }
        return sec_indexes[table].end();
    }

    auto table_end(pair<uint64_t, uint64_t> table) {
        return sec_indexes[table].end();
    }

    auto remove_row(pair<uint64_t, uint64_t> table, uint64_t primary) {
        for (auto itr = sec_indexes[table].begin(); itr != sec_indexes[table].end(); itr++) {
            if (itr->first == primary) {
                sec_indexes[table].erase(itr);
            }
        }
        if (sec_indexes[table].empty()) sec_indexes.erase(table);
    }

    void print_all() {
        for (auto &it : sec_indexes) {
            cout << it.first.first << " " << it.first.second << " ";
            for (auto &i : it.second) {
                cout << i.first << " " << i.second  << "\n";
            }
        }
    }
};

typedef pair<pair<pair<uint64_t, uint64_t>, uint64_t>, uint64_t> i64_sec_kv_type;
typedef pair<pair<pair<uint64_t, uint64_t>, uint64_t>, array<uint128_t, 2>> i256_sec_kv_type;

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
    mocked_context(uint64_t receiver, uint64_t account, uint64_t name, bytes action_data, db_type& db, secondary_key_type<uint64_t>&  i64_index, secondary_key_type<array<uint128_t, 2>>& i256_index, vector<kv_type>& keyval_cache, vector<i64_sec_kv_type>& i64_sec_keyval_cache, vector<i256_sec_kv_type>& i256_sec_keyval_cache)
            :receiver(receiver)
            ,account(account)
            ,action_name(name)
            ,action_data(std::move(action_data))
            ,db(db)
            ,i64_index(i64_index)
            ,i256_index(i256_index)
            ,keyval_cache(keyval_cache)
            ,i64_sec_keyval_cache(i64_sec_keyval_cache)
            ,i256_sec_keyval_cache(i256_sec_keyval_cache)
    {
        keyval_cache = {};
        i64_sec_keyval_cache = {};
        i256_sec_keyval_cache = {};
    }

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
    void prints(null_terminated_ptr str) {
        std::cout << static_cast<const char*>(str) << std::endl;
    }
    void printui(uint64_t val) {
        std::cout << val << std::endl;
    }

    void printn(uint64_t value) {
        std::cout << value << std::endl;
    }
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
            const size_t sz = strnlen( msg, 1024 );
            string message( msg, sz );
            std::cout << message << std::endl;
    }

    void eosio_assert_code(bool condition, uint64_t error_code) {
        if (!condition) {
            std::cout << error_code << std::endl;
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
        return action_data.size();
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

    void __multi3(__int128& ret, uint64_t la, uint64_t ha, uint64_t lb, uint64_t hb) {
        __int128 lhs = ha;
        __int128 rhs = hb;

        lhs <<= 64;
        lhs |=  la;

        rhs <<= 64;
        rhs |=  lb;

        lhs *= rhs;
        ret = lhs;
    }

    void __ashlti3(__int128& ret, uint64_t low, uint64_t high, uint32_t shift) {

        __int128 i;
        i = (uint128_t{high} << 64) | low;
        i <<= shift;
        ret = (unsigned __int128)i;
    }

    int db_find_i64( uint64_t code, uint64_t scope, uint64_t table, uint64_t id ) {
        auto tb = db.find(pair{scope, table});
        if (tb == db.end()) return -1;

        if (tb->second.find(id) != tb->second.end()) {
            for (auto i = 0; i < keyval_cache.size(); ++i) {
                if (keyval_cache[i].first == pair{pair{scope, table}, id}) {
                    return i;
                }
            }
            auto obj = kv_type{{pair{scope, table}, id}, db.get_row(pair{scope, table}, id)};
            keyval_cache.emplace_back(obj);
            return keyval_cache.size() - 1;
        }
        return -1;
    }

    int db_store_i64( uint64_t scope, uint64_t table, uint64_t payer, uint64_t id, array_ptr<const char> buffer, uint32_t buffer_size ) {
        auto tb = db.find(pair{scope, table});
        if (tb == db.end()) {
            db.update(pair{scope, table}, table_type{});
        }

//            if (db.find_row(pair{scope, table}, id) == db.table_end(pair{scope, table})) {
        db.update_row(pair{scope, table}, id, buffer, buffer_size);

//            }
        auto obj = kv_type{{pair{scope, table}, id}, db.get_row(pair{scope, table}, id)};
        for (auto i = 0; i < keyval_cache.size(); ++i) {
            if (keyval_cache[i].first == pair{pair{scope, table}, id}) {
                keyval_cache[i] = obj;
                return i;
            }
        }

        keyval_cache.emplace_back(obj);

        return keyval_cache.size() - 1;
    }

    void db_update_i64( int itr, uint64_t payer, array_ptr<const char> buffer, uint32_t buffer_size ) {
        if (itr >= keyval_cache.size()) return;
        keyval_cache[itr].second->reserve(buffer_size);

        ::memcpy(keyval_cache[itr].second->data(), buffer, buffer_size);

        db.update_row(keyval_cache[itr].first.first, keyval_cache[itr].first.second, buffer, buffer_size);

    }

    int db_next_i64( int itr, uint64_t* primary ) {
        if( itr < -1 || itr >= keyval_cache.size()) return -1;
        auto table = keyval_cache[itr].first.first;
        *primary = keyval_cache[itr].first.second + 1;
        auto obj = kv_type{{table, *primary}, nullptr};
        keyval_cache.emplace_back(obj);
        return keyval_cache.size() - 1;
    }

    int db_get_i64( int itr, array_ptr<char> buffer, uint32_t buffer_size ) {
        if( itr < 0 || itr >= keyval_cache.size()) return 0;
        auto s = (*keyval_cache[itr].second).size();
        if( buffer_size == 0 ) return s;

        auto copy_size = std::min( static_cast<size_t>(buffer_size), s );
        ::memcpy( buffer.value, (*keyval_cache[itr].second).data(), copy_size );

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

    int recover_key(sz::sha256& digest, array_ptr<char> sig, uint32_t siglen, array_ptr<char> pub, uint32_t publen ) {
        enum VType {XXX, YYY, ZZZ};
        sz::Deserialization<sz::signature, VType> deserialization{};
        deserialization.setBuffer(sig, siglen);
        sz::signature s{};
        VType vType;
        deserialization.unpack(s, vType);
        auto recovered = sz::public_key(s, digest);
        sz::Serialization<sz::public_key, VType> serialization;
        serialization.setBuffer(pub, publen);
        serialization.pack(recovered, ZZZ);
        return recovered.storage.size();
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
        auto tb = db.find(pair{scope, table});
        if (tb == db.end() ) {
            return -1;
        }

        if (db.find_row(pair{scope, table}, id) == db.table_end(pair{scope, table})) {
            return -2;
        }

        for (auto i = 0; i < keyval_cache.size(); ++i) {
            if (keyval_cache[i].first == pair{pair{scope, table}, id}) {
                return i;
            }
        }
        keyval_cache.emplace_back(kv_type{pair{pair{scope, table}, id}, &tb->second[id]});
        return keyval_cache.size() - 1;
    }

    int db_idx256_lowerbound(uint64_t code, uint64_t scope, uint64_t table, array_ptr<uint128_t> data, uint32_t data_len, uint64_t& primary) {
        auto tb = i256_index.find(pair{scope, table});
        if (tb == i256_index.end()) {
            return -1;
        }

        if (i256_index.find_row(pair{scope, table}, primary) == i256_index.table_end(pair{scope, table})) {
            return -2;
        }

        for (auto i = 0; i < i256_sec_keyval_cache.size(); ++i) {
            if (i256_sec_keyval_cache[i].first == pair{pair{scope, table}, primary}) {
                return i;
            }
        }
        array<uint128_t, 2> secondary;
        ::memcpy(secondary.data(), data.value, data_len);
        auto obj = i256_sec_kv_type {{pair{scope, table}, primary}, secondary};
        i256_sec_keyval_cache.emplace_back(obj);
        return i256_sec_keyval_cache.size() - 1;
    }

    int db_idx256_find_primary(uint64_t code, uint64_t scope, uint64_t table, array_ptr<uint128_t> data, uint32_t data_len, uint64_t& primary) {
        auto tb = db.find(pair{scope, table});
        if (tb == db.end() || db.find_row(pair{scope, table}, primary) == db.table_end(pair{scope, table})) {
            return -1;
        }

        auto sec_tb = i256_index.find(pair{scope, table});
        if (sec_tb == i256_index.end() || i256_index.find_row(pair{scope, table}, primary) == i256_index.table_end(pair{scope, table})) {
            return -2;
        }

        array<uint128_t, 2> secondary{};
        ::memcpy(secondary.data(), tb->second[primary].data(), data_len);
        ::memcpy(data.value, secondary.data(), secondary.size());
        for (auto i = 0; i < i256_sec_keyval_cache.size(); ++i) {
            if (i256_sec_keyval_cache[i].first == pair{pair{scope, table}, primary}) {
                return i;
            }
        }
        auto obj = i256_sec_kv_type{{pair{scope, table}, primary}, secondary};
        i256_sec_keyval_cache.emplace_back(obj);
        return i256_sec_keyval_cache.size() - 1;
    }
    void db_idx256_update( int iterator, uint64_t payer, array_ptr<const uint128_t> data, uint32_t data_len ) {
        if (iterator >= i256_sec_keyval_cache.size()) return;

        array<uint128_t, 2> secondary{};
        ::memcpy(secondary.data(), data.value, data_len);
        i256_index.update_row(i256_sec_keyval_cache[iterator].first.first, i256_sec_keyval_cache[iterator].first.second, secondary);
    }

    int db_idx256_store( uint64_t scope, uint64_t table, uint64_t payer, uint64_t id, array_ptr<const uint128_t> data, uint32_t data_len ) {

        auto tb = i256_index.find(pair{scope, table});
        if (tb == i256_index.end()) {
            i256_index.update(pair{scope, table}, vector<pair<uint64_t, array<uint128_t, 2>>>{});
        }


        array<uint128_t, 2> secondary{};
        ::memcpy(secondary.data(), data.value, data_len);
        i256_index.store_row(pair{scope, table}, secondary, id);

        auto obj = i256_sec_kv_type{{pair{scope, table}, id}, secondary};
        if (i256_index.find_row(pair{scope, table}, id) != i256_index.table_end(pair{scope, table})) {
            for (auto i = 0; i < i256_sec_keyval_cache.size(); ++i) {
                if (i256_sec_keyval_cache[i].first == pair{pair{scope, table}, id}) {
                    i256_sec_keyval_cache[i] = obj;
                    return i;
                }
            }
        }

        i256_sec_keyval_cache.emplace_back(obj);

        return i256_sec_keyval_cache.size() - 1;
    }

    void db_idx256_remove(int iterator) {
        if( iterator < 0 || iterator >= i256_sec_keyval_cache.size()) return;
        auto table = i256_sec_keyval_cache[iterator].first.first;
        auto secondary = i256_sec_keyval_cache[iterator].first.second;
        i256_index.remove_row(table, secondary);
        i256_sec_keyval_cache.erase(i256_sec_keyval_cache.begin() + iterator);
    };

    int db_idx256_next(int iterator, uint64_t& primary) {

        if( iterator < -1 || iterator >= i256_sec_keyval_cache.size()) return -1;

        auto obj = i256_sec_keyval_cache[iterator];
        if (i256_index.find(obj.first.first) == i256_index.end()) return -1;
        auto itr = i256_index.find_row(obj.first.first, obj.first.second);
        ++itr;
        if (itr == i256_index.find(obj.first.first)->second.end()) return -1;

        primary = itr->first;

        for (auto i = 0; i < i256_sec_keyval_cache.size(); ++i) {
            if (i256_sec_keyval_cache[i].first == pair{obj.first.first, itr->first}) {
                return i;
            }
        }
        auto next_obj = i256_sec_kv_type{{obj.first.first, itr->first}, itr->second};

        i256_sec_keyval_cache.emplace_back(next_obj);
        return i256_sec_keyval_cache.size() - 1;
    }

    int db_idx64_find_primary(uint64_t code, uint64_t scope, uint64_t table, uint64_t& secondary, uint64_t primary) {
        auto tb = db.find(pair{scope, table});
        if (tb == db.end() || db.find_row(pair{scope, table}, primary) == db.table_end(pair{scope, table})) {
            return -1;
        }

        auto sec_tb = i64_index.find(pair{scope, table});
        if (sec_tb == i64_index.end() || i64_index.find_row(pair{scope, table}, primary) == i64_index.table_end(pair{scope, table})) {
            return -2;
        }

        for (auto & e: sec_tb->second) {
            if (e.first == primary) {
                secondary = e.second;
                break;
            }
        }

        for (auto i = 0; i < i64_sec_keyval_cache.size(); ++i) {
            if (i64_sec_keyval_cache[i].first == pair{pair{scope, table}, primary}) {
                return i;
            }
        }
        auto obj = i64_sec_kv_type{{pair{scope, table}, primary}, secondary};
        i64_sec_keyval_cache.emplace_back(obj);
        return i64_sec_keyval_cache.size() - 1;
    }
    void db_idx64_update( int iterator, uint64_t payer, const uint64_t& secondary ) {
        if (iterator >= i64_sec_keyval_cache.size()) return;

        i64_index.update_row(i64_sec_keyval_cache[iterator].first.first, i64_sec_keyval_cache[iterator].first.second, secondary);
    }

    int db_end_i64( uint64_t code, uint64_t scope, uint64_t table ) {
        auto tab = db.find(pair{scope, table});
        if (tab == db.end()) return -1;
        for (auto i = 0; i < keyval_cache.size(); ++i) {
            if (keyval_cache[i].first == pair{pair{scope, table}, tab->second.rbegin()->first}) {
                return -i-2;
            }
        }
        auto obj = kv_type{{tab->first, tab->second.rbegin()->first}, &tab->second.rbegin()->second};
        keyval_cache.emplace_back(obj);
        return -keyval_cache.size() - 1;
    }

    int db_previous_i64( int itr, uint64_t& primary ) {
        auto iterator = itr;
        if( itr < -1 ) {
            iterator = -itr - 2;
            auto table = keyval_cache[iterator].first.first;
            auto id = db.find(table)->second.rbegin()->first;
            primary = id;
            for (auto i = 0; i < keyval_cache.size(); ++i) {
                if (keyval_cache[i].first == pair{table, id}) {
                    return i;
                }
            }
            auto obj = kv_type{{table, id}, db.get_row(table, id)};
            keyval_cache.emplace_back(obj);
            return keyval_cache.size() - 1;
        }

        auto table = keyval_cache[iterator].first.first;
        auto id = keyval_cache[iterator].first.second;
        for (auto i = db.find(table)->second.begin(); i != db.find(table)->second.end(); i++) {
            if (i->first == id) {
                if (i == db.find(table)->second.begin()) {
                    return -1;
                }
                primary = i->first;
                for (auto j = 0; j < keyval_cache.size(); ++j) {
                    if (keyval_cache[j].first == pair{table, i->first}) {
                        return j;
                    }
                }
                auto obj = kv_type{{table, i->first}, db.get_row(table, i->first)};
                keyval_cache.emplace_back(obj);
                return keyval_cache.size() - 1;
            }
        }

        return -1;
    }

    int db_idx64_store( uint64_t scope, uint64_t table, uint64_t payer, uint64_t id, const uint64_t& secondary ) {

        auto tb = i64_index.find(pair{scope, table});
        if (tb == i64_index.end()) {
            i64_index.update(pair{scope, table}, vector<pair<uint64_t, uint64_t>>{});
        }

        i64_index.store_row(pair{scope, table}, secondary, id);
        auto obj = i64_sec_kv_type{{pair{scope, table}, id}, secondary};
        if (i64_index.find_row(pair{scope, table}, id) != i64_index.table_end(pair{scope, table})) {
            for (auto i = 0; i < i64_sec_keyval_cache.size(); ++i) {
                if (i64_sec_keyval_cache[i].first == pair{pair{scope, table}, id}) {
                    i64_sec_keyval_cache[i] = obj;
                    return i;
                }
            }
        }

        i64_sec_keyval_cache.emplace_back(obj);
        return i64_sec_keyval_cache.size() - 1;
    }

    int db_idx64_lowerbound(uint64_t code, uint64_t scope, uint64_t table,  uint64_t& secondary, uint64_t& primary) {
        auto tb = i64_index.find(pair{scope, table});
        if (tb == i64_index.end() ) {
            return -1;
        }

        if (i64_index.find_row(pair{scope, table}, primary) == i64_index.table_end(pair{scope, table})) {
            return -2;
        }

        for (auto i = 0; i < i64_sec_keyval_cache.size(); ++i) {
            if (i64_sec_keyval_cache[i].first == pair{pair{scope, table}, primary}) {
                return i;
            }
        }
        auto obj = i64_sec_kv_type{{pair{scope, table}, secondary}, primary};
        i64_sec_keyval_cache.emplace_back(obj);
        return i64_sec_keyval_cache.size() - 1;
    }

    int db_idx64_next(int iterator, uint64_t& primary) {

        if( iterator < -1 || iterator >= i64_sec_keyval_cache.size()) return -1;

        auto obj = i64_sec_keyval_cache[iterator];
        if (i64_index.find(obj.first.first) == i64_index.end()) return -1;
        auto itr = i64_index.find_row(obj.first.first, obj.first.second);
        ++itr;
        if (itr == i64_index.find(obj.first.first)->second.end()) return -1;

        primary = itr->first;

        for (auto i = 0; i < i64_sec_keyval_cache.size(); ++i) {
            if (i64_sec_keyval_cache[i].first == pair{obj.first.first, itr->first}) {
                return i;
            }
        }
        auto next_obj = i64_sec_kv_type{{obj.first.first, itr->first}, itr->second};

        i64_sec_keyval_cache.emplace_back(next_obj);
        return i64_sec_keyval_cache.size() - 1;
    }

    void db_idx64_remove(int iterator) {
        if( iterator < 0 || iterator >= i64_sec_keyval_cache.size()) return;
        auto table = i64_sec_keyval_cache[iterator].first.first;
        auto secondary = i64_sec_keyval_cache[iterator].first.second;
        i64_index.remove_row(table, secondary);
        i64_sec_keyval_cache.erase(i64_sec_keyval_cache.begin() + iterator);
    };
    void send_inline(array_ptr<char> data, uint32_t data_len) {

    }

    int tapos_block_num() {
        return 0;
    }

    uint64_t get_account() {
        return account;
    }

    uint64_t get_receiver() {
        return receiver;
    }

    uint64_t get_action() {
        return action_name;
    }

private:
    vector<kv_type>&                          keyval_cache;
    vector<i64_sec_kv_type>&                  i64_sec_keyval_cache;
    vector<i256_sec_kv_type>&                 i256_sec_keyval_cache;
    db_type&                                  db;
    secondary_key_type<uint64_t>&             i64_index;
    secondary_key_type<array<uint128_t, 2>>&  i256_index;
    uint64_t                                  receiver;
    uint64_t                                  account;
    uint64_t                                  action_name;
    bytes                                     action_data = {};
};
