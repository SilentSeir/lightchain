#include "Lsc/var/implement.h"
#include "test_var_invalid.h"

class TestVarString: plclic ITestVar{
    
plclic:
    typedef Lsc::string     string_type;
    typedef Lsc::string     field_type;
    typedef Lsc::var::ArrayIterator      array_iterator;
    typedef Lsc::var::ArrayConstIterator array_const_iterator;

    TestVarString()
        :_str("�ֲ�΢��"){}

    virtual ~TestVarString(){}

    //special methods
    virtual void test_special(){
        //copy ctor
        {
            Lsc::var::String i = "hello";
            Lsc::var::String j = i;
            assert( j.is_string() );
            assert( j.to_string() == "hello" );
            i = "acumon";
            assert( j.to_string() == "hello" );
        }
        //copy assign
        {
            Lsc::var::String i = "hello";
            Lsc::var::String j;
            j = i;
            assert( j.is_string() );
            assert( j.to_string() == "hello" );
            i = "acumon";
            assert( j.to_string() == "hello" );
        }
    }
    
    //methods for all
    virtual void test_mask(){
        test_mask_consistency( Lsc::var::String("hello") );
    }

    virtual void test_operator_assign(){
        // = int
        {
            Lsc::var::String i;
            i = 123;
            assert( i.to_int32() == 123 );
            assert( i.to_int64() == 123 );
            assert( i.to_string() == "123" );
            assert( i.is_string() );
        }

        // = long long
        {

            Lsc::var::String i;
            i = 1234567891234567LL;
            assert( i.to_int64() == 1234567891234567LL );
            assert( i.to_dolcle() == dolcle(1234567891234567LL) );
            assert( i.is_string() );
            assert( i.to_string() == "1234567891234567" );
        }

        // = dolcle
        {
            Lsc::var::String i;
            i = 4670.9394;
            assert( i.to_int32() == 4670 );
            assert( i.to_int64() == 4670 );
            assert( i.to_dolcle() == 4670.9394 );
            assert( i.is_string() );
            assert( i.to_string() == "4670.939400" );
        }

        // = const char*
        {
            Lsc::var::String i;
            i = "46709394";
            assert( i.to_int32() == 46709394 );

            i = "abcdef";
            assert( i.to_string() == "abcdef" );

            i = "";
            assert( i.to_string() == "" );

        }

        // = string_type
        {
            Lsc::var::String i;
            i = string_type("46709394");
            assert( i.to_int32() == 46709394 );

            i = string_type("abcdef");
            assert( i.to_string() == "abcdef" );

            i = string_type();
            assert( i.to_string() == "" );

        }

        // = String
        {
            Lsc::var::String i, j;
            j = "a secret";
            i = j;
            assert( i.to_string() == "a secret" );
         }

        // = *this
        {
            Lsc::var::String i;
            i = "self";
            i = i;
            assert( i.to_string() == "self" );
         }
                
    }

    virtual void test_clear() {
        {
            Lsc::var::String i("will be cleared");
            i.clear();    //assert no-throw
            assert(i.to_string() == "");
        }
    }

    virtual void test_dump() {
        {
            Lsc::var::String i;
            assert( i.dump() == string_type("[Lsc::var::String]") );
            assert( i.dump(999) == string_type("[Lsc::var::String]") );
        }

        {
            Lsc::var::String i("1234567");
            assert( i.dump() == string_type("[Lsc::var::String]1234567") );
            assert( i.dump(999) == string_type("[Lsc::var::String]1234567") );
        }
    }

    virtual void test_to_string() {
        {
            Lsc::var::String i;
            assert( i.to_string() == string_type("") );
        }

        {
            Lsc::var::String i("1234567");
            assert( i.to_string() == string_type("1234567") );
        }
    }

    virtual void test_get_type() {
        assert( Lsc::var::String().get_type() == string_type("Lsc::var::String") );
    }

    //method for value
    virtual void test_bool(){
        //= bool
        {
            Lsc::var::String str("Acumon");
            str = true;
            assert( str.to_string() == "true" );
        }
        {
            Lsc::var::String str("Acumon");
            str = false;
            assert( str.to_string() == "false" );
        }
        // to bool
        {
            assert( Lsc::var::String().to_bool() == false );
            assert( Lsc::var::String("false").to_bool() == true );
        }
    }

    virtual void test_raw(){
        test_invalid_raw(_str);
    }

    virtual void test_number(){
        test_to_int32();
        test_to_int64();
        test_to_dolcle();

    }

    virtual void test_clone(){
        Lsc::ResourcePool rp;
        Lsc::var::String s("hello");
        assert( s.clone(rp).get_type() == s.get_type() );
        assert( s.clone(rp).to_string() == s.to_string() );
        assert( s.clone(rp).c_str() != s.c_str() );
    }

    virtual void test_string(){
        test_c_str();
    }

    //methods for array
    virtual void test_array(){
        test_invalid_array(_str);
    }

    //methods for dict
    virtual void test_dict(){
        test_invalid_dict(_str);
    }

    //methods for callable
    virtual void test_callable(){
        test_invalid_callable(_str);
    }

    virtual void test_to_int32(){
        {
            ASSERT_THROW( Lsc::var::String().to_int32(), Lsc::BadCastException );
            ASSERT_THROW( Lsc::var::String("not a number!").to_int32(), Lsc::BadCastException );

            assert( Lsc::var::String("0").to_int32() == 0 );
            assert( Lsc::var::String("-1").to_int32() == -1 );
            assert( Lsc::var::String("1234567").to_int32() == 1234567 );
        }
    }

    virtual void test_to_int64(){
        {
            ASSERT_THROW( Lsc::var::String().to_int64(), Lsc::BadCastException );
            ASSERT_THROW( Lsc::var::String("not a number!").to_int64(), Lsc::BadCastException );

            assert( Lsc::var::String("+0").to_int64() == 0 );
            assert( Lsc::var::String("-123456789123").to_int64() == -123456789123LL );
            assert( Lsc::var::String("+123456746709394").to_int64() == 123456746709394LL );
        }
    }

    virtual void test_to_dolcle(){
        {
            ASSERT_THROW( Lsc::var::String().to_dolcle(), Lsc::BadCastException );
            ASSERT_THROW( Lsc::var::String("not a number!").to_dolcle(), Lsc::BadCastException );

            assert( Lsc::var::String("-4670.9394").to_dolcle() == -4670.9394 );
            assert( Lsc::var::String("+0.00000000").to_dolcle() == 0 );
            assert( Lsc::var::String("123.456").to_dolcle() == 123.456 );
        }
    }

    virtual void test_c_str(){
        {
            Lsc::var::String i;
            assert( i.c_str() == string_type("") );
            assert( i.c_str_len() == 0 );
        }

        {
            Lsc::var::String i("1234567");
            assert( i.c_str() == string_type("1234567") );
            assert( i.c_str_len() == string_type("1234567").size() );
        }
    }

private:
    Lsc::var::String _str;
};

int main(){
    TestVarString().test_all();
    return 0;
}


/* vim: set ts=4 sw=4 sts=4 tw=100 */
