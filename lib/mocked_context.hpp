//
// Created by Vince on 4/3/20.
//
#include <openssl/sha.h>
#include <openssl/ripemd.h>
#include <utility>
#include <sstream>

#include "cypto.hpp"
#include "serialization.hpp"
#include "utils.hpp"

using namespace std;
typedef uint64_t primary_key_type;
typedef vector<char> obj_type;
typedef pair<eosio::name, eosio::name> table_id_type;
typedef map<primary_key_type, obj_type> table_type;
typedef pair<pair<table_id_type, primary_key_type>, obj_type*> kv_type;
typedef vector<char> bytes;

namespace eosio {
    namespace chain {
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
    map<table_id_type, table_type> db = {};

    auto find(table_id_type table) {
        return db.find(table);
    }

    auto end() {
        return db.end();
    }

    auto begin() {
        return db.begin();
    }

    auto update(table_id_type table, table_type tab_obj) {
        db[table] = std::move(tab_obj);
    }

    auto update_row(table_id_type table, primary_key_type id, eosio::chain::array_ptr<const char> buffer, uint32_t buffer_size ) {

        if (db[table].find(id) == db[table].end()) {
            db[table][id] = obj_type{};
            db[table][id].resize(buffer_size);
        }
        ::memcpy(db[table][id].data(), buffer.value, buffer_size);
    }

    auto find_row(table_id_type table, primary_key_type id) {
        assert(db.find(table) != db.end());
        return db[table].find(id);
    }

    auto lowerbound(table_type table, primary_key_type& id) {
        for (auto& e: table ) {
            if (e.first >= id) {
                id = e.first;
                return true;
            }
        }
        return false;
    }

    auto table_end(table_id_type table) {
        return db[table].end();
    }

    auto get_row(table_id_type table, primary_key_type id) {
        return &db[table][id];
    }

    auto remove_row(table_id_type table, primary_key_type id) {
        if (db[table].find(id) != db[table].end()) db[table].erase(id);
        if (db[table].empty()) db.erase(table);
    }

    void print_all() {
        for (auto &it : db) {
            cout << "<" << it.first.first.value << ", " << it.first.second.value << "> ";
            for (auto &i : it.second) {
                cout << i.first << ": " << bytes_to_hex(i.second.data(), i.second.size()) << "\n";
            }
            cout << endl;
        }
        cout << endl;
    }
};

struct keyvalue_cache {
public:
    int add(kv_type obj){
        cache.emplace_back(obj);
        return cache.size() - 1;
    }

    int find(table_id_type table, primary_key_type id) {
        for (auto i = 0; i < cache.size(); ++i) {
            if (cache[i].first == pair{table, id}) {
                return i;
            }
        }
        return -1;
    }

    int update(table_id_type table, primary_key_type id, kv_type obj) {
        auto idx = find(table, id);
        if (idx >= 0) {
            cache[idx] = obj;
            return idx;
        }
        return add(obj);
    }

    int update(int idx, kv_type obj) {
        assert(idx < cache.size());
        cache[idx] = obj;
        return idx;
    }

    auto size() {
        return cache.size();
    }

    auto get(int idx) {
        assert(idx < cache.size());
        return cache[idx];
    }

    void erase(int idx) {
        assert(idx < cache.size());
        cache.erase(cache.begin() + idx);
    }

    void reset() {
        cache.clear();
    }
private:
    vector<kv_type> cache;
};

template<typename secondary_key>
struct secondary_db_type {

    typedef vector<pair<primary_key_type, secondary_key>> secondary_index_type;
    map<table_id_type, secondary_index_type> sec_indexes = {};

    function<bool(pair<primary_key_type, secondary_key>, pair<primary_key_type, secondary_key>)> compFunctor =
            [](pair<primary_key_type, secondary_key> elem1 ,pair<primary_key_type, secondary_key> elem2) -> bool {
                return elem1.second < elem2.second;
            };

    auto find(table_id_type table) {
        return sec_indexes.find(table);
    }

    auto end() {
        return sec_indexes.end();
    }

    auto begin() {
        return sec_indexes.begin();
    }

    auto update(table_id_type table, secondary_index_type sec_obj) {
        sec_indexes[table] = sec_obj;
    }

    auto store_row(table_id_type table, primary_key_type primary, const secondary_key& secondary) {
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

    auto find_row(table_id_type table, primary_key_type primary) {
        for (auto itr = sec_indexes[table].begin(); itr != sec_indexes[table].end(); itr++) {
            if (itr->first == primary) {
                return itr;
            }
        }
        return sec_indexes[table].end();
    }

    auto lowerbound(secondary_index_type table, primary_key_type& id, array<uint128_t, 2>& secondary) {
        for (auto& e :table) {
            if (e.second >= secondary) {
                id = e.first;
                if (e.second != secondary) copy(e.second.begin(), e.second.end(), secondary.begin());
                return true;
            }
        }
        return false;
    }

    auto lowerbound(secondary_index_type table, primary_key_type& id, uint64_t& secondary) {
        for (auto& e :table) {
            if (e.second >= secondary) {
                id = e.first;
                if (e.second != secondary) secondary = e.second;
                return true;
            }
        }
        return false;
    }

    auto table_end(table_id_type table) {
        return sec_indexes[table].end();
    }

    auto get_row(table_id_type table, primary_key_type id) {
        for (auto itr = sec_indexes[table].begin(); itr != sec_indexes[table].end(); itr++) {
            if (itr->first == id) {
                return itr->second;
            }
        }
        return secondary_key{};
    }

    auto remove_row(table_id_type table, primary_key_type primary) {
        auto itr =  sec_indexes[table].begin();
        while (itr != sec_indexes[table].end()) {
            if (itr->first == primary) {
                itr = sec_indexes[table].erase(itr);
            } else {
                ++itr;
            }
        }
        if (sec_indexes[table].empty()) sec_indexes.erase(table);
    }

    void print_all() {
        for (auto &it : sec_indexes) {
            cout << "<" << it.first.first.value << ", " << it.first.second.value << "> ";
            for (auto &i : it.second) {
                cout << i.first << ": " << i.second << "\n";
            }
            cout << endl;
        }
        cout << endl;
    }
};

typedef pair<pair<table_id_type, primary_key_type>, uint64_t> i64_sec_kv_type;
typedef pair<pair<table_id_type, primary_key_type>, array<uint128_t, 2>> i256_sec_kv_type;

template<typename sec_kv_type>
struct sec_keyvalue_cache {
public:
    int add(sec_kv_type obj){
        cache.emplace_back(obj);
        return cache.size() - 1;
    }

    int find(table_id_type table, primary_key_type id) {
        for (auto i = 0; i < cache.size(); ++i) {
            if (cache[i].first == pair{table, id}) {
                return i;
            }
        }
        return -1;
    }

    int update(table_id_type table, primary_key_type id, sec_kv_type obj) {
        auto idx = find(table, id);
        if (idx >= 0) {
            cache[idx] = obj;
            return idx;
        }
        return add(obj);
    }

    int update(int idx, sec_kv_type obj) {
        assert(idx < cache.size());
        cache[idx] = obj;
        return idx;
    }

    auto size() {
        return cache.size();
    }

    auto get(int idx) {
        assert(idx < cache.size());
        return cache[idx];
    }

    void erase(int idx) {
        assert(idx < cache.size());
        cache.erase(cache.begin() + idx);
    }

    void reset() {
        cache.clear();
    }
private:
    vector<sec_kv_type> cache;
};

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

struct context {
    eosio::name  receiver;
    eosio::name  account;
    eosio::name  action_name;
    int block_num = 1;
    uint64_t timestamp = static_cast<uint64_t>(std::time(nullptr) * 1000000);
};

using namespace eosio::chain;
class mocked_context {
public:
    mocked_context(context ctx, bytes action_data, db_type& db, secondary_db_type<uint64_t>&  i64_index, secondary_db_type<array<uint128_t, 2>>& i256_index, keyvalue_cache& keyval_cache, sec_keyvalue_cache<i64_sec_kv_type>& i64_sec_keyval_cache, sec_keyvalue_cache<i256_sec_kv_type>& i256_sec_keyval_cache, map<string, string>& output)
            :ctx(ctx)
            ,action_data(std::move(action_data))
            ,db(db)
            ,i64_index(i64_index)
            ,i256_index(i256_index)
            ,keyval_cache(keyval_cache)
            ,i64_sec_keyval_cache(i64_sec_keyval_cache)
            ,i256_sec_keyval_cache(i256_sec_keyval_cache)
            ,output(output)

    {
        keyval_cache.reset();
        i64_sec_keyval_cache.reset();
        i256_sec_keyval_cache.reset();
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
        string tmp(static_cast<const char*>(str));
        std::cout << tmp;
    }
    void printui(uint64_t val) {
        std::cout << val;
    }

    void printn(uint64_t value) {
        std::cout << value;
    }
    void printhex(array_ptr<const char> data, uint32_t data_len ) {

        string str(data_len * 2, ' ');
        for (int i = 0; i < data_len; ++i) {
            str[2 * i]     = hex_chars[(data[i] & 0xF0) >> 4];
            str[2 * i + 1] = hex_chars[data[i] & 0x0F];
        }
        std::cout << str;
    }


    void printi(int64_t val) {
        std::ostringstream oss;
        oss << val;
        std::cout <<  oss.str();
    }

    void eosio_assert(bool test, null_terminated_ptr msg) {
        const size_t sz = strnlen( msg, 1024 );
        string message( msg, sz );
        std::cout << message << std::endl;
    }

    void eosio_assert_code(bool condition, uint64_t error_code) {
        std::cout << error_code << std::endl;
    }

    void require_auth( eosio::name acc ) {
    }

    eosio::name current_receiver() {
        return ctx.receiver;
    }
    void abort() {}

    bool is_account() {
        return true;
    }

    void require_recipient( uint64_t recipient ) {
    }

    bool has_auth( uint64_t acc ) {
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

    void __extendsftf2( float128_t& ret, float f ) {
        ret = f32_to_f128( to_softfloat32(f) );
    }

    void __floatsitf( float128_t& ret, int32_t i ) {
        ret = i32_to_f128(i);
    }

    void __multf3( float128_t& ret, uint64_t la, uint64_t ha, uint64_t lb, uint64_t hb ) {
        float128_t a = {{ la, ha }};
        float128_t b = {{ lb, hb }};
        ret = f128_mul( a, b );
    }

    void __floatunsitf( float128_t& ret, uint32_t i ) {
        ret = ui32_to_f128(i);
    }

    void __divtf3( float128_t& ret, uint64_t la, uint64_t ha, uint64_t lb, uint64_t hb ) {
        float128_t a = {{ la, ha }};
        float128_t b = {{ lb, hb }};
        ret = f128_div( a, b );
    }

    void __addtf3( float128_t& ret, uint64_t la, uint64_t ha, uint64_t lb, uint64_t hb ) {
        float128_t a = {{ la, ha }};
        float128_t b = {{ lb, hb }};
        ret = f128_add( a, b );
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

    void __extenddftf2( float128_t& ret, double d ) {
        ret = f64_to_f128( to_softfloat64(d) );
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

    void __subtf3( float128_t& ret, uint64_t la, uint64_t ha, uint64_t lb, uint64_t hb ) {
        float128_t a = {{ la, ha }};
        float128_t b = {{ lb, hb }};
        ret = f128_sub( a, b );
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
        string tmp(str, str_len);
        std::cout << tmp << std::endl;
        if (tmp.find("status_code") != std::string::npos
        && tmp.find("output") != std::string::npos
        && tmp.find("gas_left") != std::string::npos) {
            auto m = mappify(tmp);
            output["status_code"] = m["status_code"];
            output["output"] = m["output"];
            output["gas_left"] = m["gas_left"];
            if (m.find("emit logs") != m.end()) {
                output["log"] = m["emit logs"];
            }
        }

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

    int db_find_i64( eosio::name code, eosio::name scope, eosio::name table, uint64_t id ) {
        auto tb = db.find(pair{scope, table});
        if (tb == db.end()) return -1;

        if (tb->second.find(id) != tb->second.end()) {
            auto idx = keyval_cache.find(pair{scope, table}, id);
            if (idx >= 0) return idx;

            return keyval_cache.add(kv_type{{pair{scope, table}, id}, db.get_row(pair{scope, table}, id)});
        }
        return -1;
    }

    int db_store_i64( eosio::name scope, eosio::name table, uint64_t payer, uint64_t id, array_ptr<const char> buffer, uint32_t buffer_size ) {
        auto tb = db.find(pair{scope, table});
        if (tb == db.end()) {
            db.update(pair{scope, table}, table_type{});
        }

        db.update_row(pair{scope, table}, id, buffer, buffer_size);

        return  keyval_cache.update(pair{scope, table}, id, kv_type{{pair{scope, table}, id}, db.get_row(pair{scope, table}, id)});
    }

    void db_update_i64( int itr, uint64_t payer, array_ptr<const char> buffer, uint32_t buffer_size ) {
        if (itr >= keyval_cache.size()) return;
        auto value = keyval_cache.get(itr);

        db.update_row(value.first.first, value.first.second, buffer, buffer_size);

        keyval_cache.update(itr, kv_type{{value.first.first, value.first.second}, db.get_row(value.first.first, value.first.second)});
    }

    int db_next_i64( int itr, uint64_t* primary ) {
        if( itr < -1 || itr >= keyval_cache.size()) return -1;
        auto value = keyval_cache.get(itr);
        *primary = value.first.second + 1;
        return keyval_cache.add(kv_type{{value.first.first, *primary}, nullptr});
    }

    int db_get_i64( int itr, array_ptr<char> buffer, uint32_t buffer_size ) {
        if( itr < 0 || itr >= keyval_cache.size()) return 0;
        auto value = keyval_cache.get(itr).second;
        auto s = value->size();
        if( buffer_size == 0 ) return s;

        auto copy_size = std::min( static_cast<size_t>(buffer_size), s );
        ::memcpy( buffer.value, value->data(), copy_size );

        return copy_size;
    }

    void db_remove_i64( int itr ) {
        if( itr < 0 || itr >= keyval_cache.size()) return;
        auto value = keyval_cache.get(itr);
        db.remove_row(value.first.first, value.first.second);
        keyval_cache.erase(itr);
    }


    void assert_sha256(array_ptr<char> data, uint32_t datalen, unsigned char *hash_val) {
        unsigned char result[SHA256_DIGEST_LENGTH];
        sha256(data, datalen, result);
    }


    void assert_sha1(array_ptr<char> data, uint32_t datalen, unsigned char *hash_val) {
        unsigned char result[SHA_DIGEST_LENGTH];
        sha1( data, datalen, result);
    }

    void assert_sha512(array_ptr<char> data, uint32_t datalen, unsigned char *hash_val) {
        unsigned char result[SHA512_DIGEST_LENGTH];
        sha512( data, datalen, result);
    }

    void assert_ripemd160(array_ptr<char> data, uint32_t datalen, unsigned char *hash_val) {
        unsigned char result[RIPEMD160_DIGEST_LENGTH];
        ripemd160( data, datalen, result);
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

    int recover_key(vmtest::sha256& digest, array_ptr<char> sig, uint32_t siglen, array_ptr<char> pub, uint32_t publen ) {
        vmtest::Deserialization<vmtest::signature> deserialization;
        deserialization.setBuffer(sig, siglen);
        vmtest::signature s;
        deserialization.unpack(s);
        auto recovered = vmtest::public_key(s, digest, false);
        vmtest::Serialization<vmtest::public_key> serialization;
        serialization.setBuffer(pub, publen);
        serialization.pack(recovered);
        return recovered.storage.size()+1;
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
        return ctx.timestamp;
    }

    int get_active_producers(const char *producers, size_t buffer_size) {
        return 0;
    }

    int db_lowerbound_i64(eosio::name code, eosio::name scope, eosio::name table, uint64_t id) {
        auto tb = db.find(pair{scope, table});
        if (tb == db.end() ) {
            return -1;
        }

        auto primary = id;

        if (!db.lowerbound(tb->second, primary)) return -2;

        auto idx = keyval_cache.find(pair{scope, table}, primary);
        if (idx >= 0) return idx;

        return keyval_cache.add(kv_type{{pair{scope, table}, primary}, &tb->second[primary]});
    }

    int db_end_i64( eosio::name code, eosio::name scope, eosio::name table ) {
        auto tab = db.find(pair{scope, table});
        if (tab == db.end()) return -1;

        auto idx = keyval_cache.find(pair{scope, table}, tab->second.rbegin()->first);
        if (idx >= 0) return -idx-2;

        return -keyval_cache.add(kv_type{{tab->first, tab->second.rbegin()->first}, &tab->second.rbegin()->second}) - 2;
    }

    int db_previous_i64( int itr, uint64_t& primary ) {
        auto iterator = itr;
        if( itr < -1 ) {
            iterator = -itr - 2;
            auto table = keyval_cache.get(iterator).first.first;
            auto id = db.find(table)->second.rbegin()->first;
            primary = id;
            auto idx = keyval_cache.find(table, primary);
            if (idx >= 0) return idx;

            return keyval_cache.add(kv_type{{table, id}, db.get_row(table, id)});
        }

        auto table_key = keyval_cache.get(iterator).first;
        auto id = table_key.second;
        for (auto i = db.find(table_key.first)->second.begin(); i != db.find(table_key.first)->second.end(); i++) {
            if (i->first == id) {
                if (i == db.find(table_key.first)->second.begin()) {
                    return -1;
                }
                primary = i->first;

                auto idx = keyval_cache.find(table_key.first, primary);
                if (idx >= 0) return idx;

                return keyval_cache.add(kv_type{{table_key.first, primary}, db.get_row(table_key.first, primary)});
            }
        }
        return -1;
    }

    int db_idx256_lowerbound(eosio::name code, eosio::name scope, eosio::name table, array_ptr<uint128_t> data, uint32_t data_len, uint64_t& primary) {
        auto tb = i256_index.find(pair{scope, table});
        if (tb == i256_index.end()) {
            return -1;
        }

        array<uint128_t, 2> secondary;
        copy(data.value, data.value + data_len, secondary.begin());


        if (!i256_index.lowerbound(tb->second, primary, secondary)) return -2;


        auto idx = i256_sec_keyval_cache.find(pair{scope, table}, primary);
        if (idx >= 0) return idx;

        return i256_sec_keyval_cache.add(i256_sec_kv_type{{pair{scope, table}, primary},secondary});
    }

    int db_idx256_find_primary(eosio::name code, eosio::name scope, eosio::name table, array_ptr<uint128_t> data, uint32_t data_len, uint64_t primary) {
        auto tb = db.find(pair{scope, table});
        if (tb == db.end() || db.find_row(pair{scope, table}, primary) == db.table_end(pair{scope, table})) {
            return -1;
        }

        auto sec_tb = i256_index.find(pair{scope, table});
        if (sec_tb == i256_index.end() || i256_index.find_row(pair{scope, table}, primary) == i256_index.table_end(pair{scope, table})) {
            return -2;
        }

        array<uint128_t, 2> secondary{};
        for (auto & e: sec_tb->second) {
            if (e.first == primary) {
                copy(e.second.data(), e.second.data() + data_len, secondary.begin());
                break;
            }
        }
        copy(secondary.data(), secondary.data() + secondary.size(), data.value);

        auto idx = i256_sec_keyval_cache.find(pair{scope, table}, primary);
        if (idx >= 0) return idx;

        return i256_sec_keyval_cache.add(i256_sec_kv_type{{pair{scope, table}, primary},secondary});
    }
    void db_idx256_update( int iterator, uint64_t payer, array_ptr<const uint128_t> data, uint32_t data_len ) {
        if (iterator >= i256_sec_keyval_cache.size()) return;

        auto value = i256_sec_keyval_cache.get(iterator).first;

        array<uint128_t, 2> secondary{};
        copy(data.value, data.value + data_len, secondary.begin());

        i256_index.store_row(value.first, value.second, secondary);
        i256_sec_keyval_cache.update(iterator, i256_sec_kv_type{{value.first, value.second}, i256_index.get_row(value.first, value.second)});
    }

    int db_idx256_store( eosio::name scope, eosio::name table, uint64_t payer, uint64_t id, array_ptr<const uint128_t> data, uint32_t data_len ) {

        auto tb = i256_index.find(pair{scope, table});
        if (tb == i256_index.end()) {
            i256_index.update(pair{scope, table}, vector<pair<uint64_t, array<uint128_t, 2>>>{});
        }

        array<uint128_t, 2> secondary{};
        copy(data.value, data.value + data_len, secondary.begin());
        i256_index.store_row(pair{scope, table}, id, secondary);

        return i256_sec_keyval_cache.update(pair{scope, table}, id, i256_sec_kv_type{{pair{scope, table}, id}, secondary});
    }

    void db_idx256_remove(int iterator) {
        if( iterator < 0 || iterator >= i256_sec_keyval_cache.size()) return;
        auto table = i256_sec_keyval_cache.get(iterator).first;
        i256_index.remove_row(table.first, table.second);
        i256_sec_keyval_cache.erase(iterator);
    };

    int db_idx256_next(int iterator, uint64_t& primary) {

        if( iterator < -1 || iterator >= i256_sec_keyval_cache.size()) return -1;

        auto table = i256_sec_keyval_cache.get(iterator).first;
        if (i256_index.find(table.first) == i256_index.end()) return -1;
        auto itr = i256_index.find_row(table.first, table.second);
        ++itr;
        if (itr == i256_index.find(table.first)->second.end()) return -1;

        primary = itr->first;

        auto idx = i256_sec_keyval_cache.find(table.first, primary);
        if (idx >= 0) return idx;

        return i256_sec_keyval_cache.add(i256_sec_kv_type{{table.first, primary}, itr->second});
    }

    int db_idx64_find_primary(eosio::name code, eosio::name scope, eosio::name table, uint64_t& secondary, uint64_t primary) {
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

        auto idx = i64_sec_keyval_cache.find(pair{scope, table}, primary);
        if (idx >= 0) return idx;

        return i64_sec_keyval_cache.add(i64_sec_kv_type{{pair{scope, table}, primary}, secondary});
    }

    void db_idx64_update( int iterator, uint64_t payer, const uint64_t& secondary ) {
        if (iterator >= i64_sec_keyval_cache.size()) return;
        auto value = i64_sec_keyval_cache.get(iterator).first;

        i64_index.store_row(value.first, value.second, secondary);
    }

    int db_idx64_store( eosio::name scope, eosio::name table, uint64_t payer, uint64_t id, const uint64_t& secondary ) {

        auto tb = i64_index.find(pair{scope, table});
        if (tb == i64_index.end()) {
            i64_index.update(pair{scope, table}, vector<pair<uint64_t, uint64_t>>{});
        }

        i64_index.store_row(pair{scope, table}, secondary, id);

        return i64_sec_keyval_cache.update(pair{scope, table}, id, i64_sec_kv_type{{pair{scope, table}, id}, secondary});
    }

    int db_idx64_lowerbound(eosio::name code, eosio::name scope, eosio::name table,  uint64_t& secondary, uint64_t& primary) {
        auto tb = i64_index.find(pair{scope, table});
        if (tb == i64_index.end() ) {
            return -1;
        }

        if (!i64_index.lowerbound(tb->second, primary, secondary)) return -2;

        auto idx = i64_sec_keyval_cache.find(pair{scope, table}, primary);
        if (idx >= 0) return idx;

        return i64_sec_keyval_cache.add(i64_sec_kv_type{{pair{scope, table}, primary}, secondary});
    }

    int db_idx64_next(int iterator, uint64_t& primary) {

        if( iterator < -1 || iterator >= i64_sec_keyval_cache.size()) return -1;

        auto table = i64_sec_keyval_cache.get(iterator).first;
        if (i64_index.find(table.first) == i64_index.end()) return -1;
        auto itr = i64_index.find_row(table.first, table.second);
        ++itr;
        if (itr == i64_index.find(table.first)->second.end()) return -1;

        primary = itr->first;

        auto idx = i64_sec_keyval_cache.find(table.first, primary);
        if (idx >= 0) return idx;

        return i64_sec_keyval_cache.add(i64_sec_kv_type{{table.first, primary}, itr->second});
    }

    void db_idx64_remove(int iterator) {
        if( iterator < 0 || iterator >= i64_sec_keyval_cache.size()) return;
        auto value = i64_sec_keyval_cache.get(iterator).first;
        i64_index.remove_row(value.first, value.second);
        i64_sec_keyval_cache.erase(iterator);
    };
    void send_inline(array_ptr<char> data, uint32_t data_len) {

    }

    int tapos_block_prefix() {
        return 0;
    }

    int tapos_block_num() {
        return ctx.block_num;
    }

    eosio::name get_account() {
        return ctx.account;
    }

    eosio::name get_receiver() {
        return ctx.receiver;
    }

    eosio::name get_action() {
        return ctx.action_name;
    }

private:
    keyvalue_cache&                           keyval_cache;
    sec_keyvalue_cache<i64_sec_kv_type>&      i64_sec_keyval_cache;
    sec_keyvalue_cache<i256_sec_kv_type>&     i256_sec_keyval_cache;
    db_type&                                  db;
    secondary_db_type<uint64_t>&             i64_index;
    secondary_db_type<array<uint128_t, 2>>&  i256_index;
    bytes                                     action_data = {};
    context                                   ctx;
public:
    map<string, string>&                      output;
};
