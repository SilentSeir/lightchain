#ifndef  __BSL_VAR_MAGIC_ARRAY_H__
#define  __BSL_VAR_MAGIC_ARRAY_H__

#include <deque>
#include "Lsc/pool/Lsc_pool.h"
#include "Lsc/var/IVar.h"
#include "Lsc/var/MagicRef.h"
#include "Lsc/var/Null.h"
#include "Lsc/var/utils.h"

namespace Lsc{
namespace var{
    //typedefs
    template<typename allocator_t>
        class MagicBasicArray;

    typedef MagicBasicArray<Lsc::pool_allocator<void> > MagicArray;

    template<typename allocator_t>
        class MagicBasicArray: plclic IVar{
        plclic:
            typedef IVar::string_type   string_type;
            typedef IVar::field_type    field_type;
            typedef allocator_t         allocator_type;
            typedef ArrayIterator       array_iterator;
            typedef ArrayConstIterator  array_const_iterator;
            typedef MagicRef            reference_type;

        plclic:
            MagicBasicArray(Lsc::ResourcePool& rp)
                :_array(), _rp(rp) {}

            MagicBasicArray( const MagicBasicArray& other )
                :IVar(other), _array(other._array), _rp(other._rp){}

            MagicBasicArray& operator = ( const MagicBasicArray& other ){
                try{
                    _array = other._array;
                }catch(Lsc::Exception& e){
                    e<<"{"<<__PRETTY_FUNCTION__<<"("<<other.dump(0)<<")}";
                    throw;
                }catch(std::exception& e){
                    throw StdException(e)<<BSL_EARG<<"{"<<__PRETTY_FUNCTION__<<"("<<other.dump(0)<<")}";

                }catch(...){
                    throw UnknownException()<<BSL_EARG<<"{"<<__PRETTY_FUNCTION__<<"("<<other.dump(0)<<")}";
                }
                return *this;
            }
                
            virtual ~MagicBasicArray() {}

            /**
             *
            **/
            virtual size_t size() const {
                return _array.size();
            }

            /**
             *
             **/
            virtual void clear(){
                return _array.clear();
            }
            
            /**
             *
             * �ú���ֻ��¡������㣬����¡�ӽ�㣬���������ͣ���¡ָ��Ľ��
             *
            **/
            virtual MagicBasicArray& clone( Lsc::ResourcePool& rp ) const {
                return rp.clone(*this);
            }

            /**
             * 
             * ��is_deep_copy���������Ƿ����
             * ��Ϊfalse, ֻ��¡������㣬����¡�ӽ��
             * ��Ϊtrue, ��¡������㣬���ҵݹ��¡�ӽ��
             * ���������ͣ���¡ָ��Ľ��
             * 
            **/
            virtual MagicBasicArray& clone( Lsc::ResourcePool& rp, bool is_deep_copy ) const {
                MagicBasicArray& res = rp.clone(*this);
                if(is_deep_copy){
                    size_t n = _array.size();
                    for(size_t i = 0; i < n; ++i){
                        res.set(i, _array[i].clone(rp, is_deep_copy));
                    }
                }
                return res;
            }

            /**
             *
            **/
            virtual string_type dump(size_t verbose_level = 0) const {
                string_type res;
                if ( verbose_level == 0 ){
                    res.appendf("[Lsc::var::MagicBasicArray] this[%p] size[%zd]", this, _array.size() ); 
                }else{
                    dump_to_string(*this, res, verbose_level, "", 0 );
                }
                return res;
            }

            /**
             *
            **/
            virtual string_type to_string() const {
                return dump(0);
            }

            virtual MagicBasicArray& operator = ( IVar& var ) {
                if ( typeid(var) == typeid(*this) ){
                    return operator =(dynamic_cast<MagicBasicArray&>(var));
                }else if ( var.is_array() ){
                    size_t var_size = var.size();
                    try{
                        _array.resize( var_size, reference_type(_rp) );
                    }catch(Lsc::Exception& e){
                        throw;
                    }catch(std::exception& e){
                        throw StdException(e)<<BSL_EARG;
                    }catch(...){
                        throw UnknownException()<<BSL_EARG;
                    }
                    for( size_t i = 0; i < var_size; ++ i ){
                        _array[i] = var[int(i)];
                    }
                }else{
                    throw Lsc::InvalidOperationException()<<BSL_EARG<<"cast from "<<var.dump(0);
                }

                return *this;
                    
            }


            /**
             *
            **/
            virtual string_type get_type() const {
                return "Lsc::var::MagicBasicArray";
            }

            /**
             *
            **/
            virtual IVar::mask_type get_mask() const {
                return IVar::IS_ARRAY;
            }

            //testers
            virtual bool is_array() const {
                return true;
            }

            //converters
            using IVar::operator =;

            //methods for array
            virtual IVar& get( size_t idx ) {
                if ( idx >= _array.size() ){
                    return Lsc::var::Null::null;
                }
                return _array[idx];
            }

            virtual IVar& get( size_t idx, IVar& default_value ) {
                if ( idx >= _array.size() ){
                    return default_value;
                }
                return _array[idx];
            }

            virtual const IVar& get( size_t idx ) const {
                if ( idx >= _array.size() ){
                    return Lsc::var::Null::null;
                }
                return _array[idx];
            }

            virtual const IVar& get( size_t idx, const IVar& default_value ) const {
                if ( idx >= _array.size() ){
                    return default_value;
                }
                return _array[idx];
            }

            virtual void set( size_t idx, IVar& value ){
                if ( idx >= _array.size() ){
                    try{
                        _array.resize(idx + 1, reference_type(_rp) );
                    }catch(Lsc::Exception& e){
                        throw;
                    }catch(std::exception& e){
                        throw StdException(e)<<BSL_EARG;
                    }catch(...){
                        throw UnknownException()<<BSL_EARG;
                    }
                }
                _array[idx] = value;
            }

            virtual bool del( size_t idx ){
                if ( idx >= _array.size() || _array[idx].is_null() ){
                    return false;
                }else{
                    _array[idx] = Null::null;
                    return true;
                }
            }

            virtual array_const_iterator array_begin() const {
                return array_const_iterator( _s_create_const_iterator( &_array, 0 ), _s_clone_const_iterator, _s_destroy_const_iterator );
            }

            virtual array_iterator array_begin() {
                return array_iterator( _s_create_iterator( &_array, 0 ), _s_clone_iterator, _s_destroy_iterator );
            }

            virtual array_const_iterator array_end() const {
                return array_const_iterator( _s_create_const_iterator( &_array, _array.size() ), _s_clone_const_iterator, _s_destroy_const_iterator );
            }

            virtual array_iterator array_end() {
                return array_iterator( _s_create_iterator( &_array, _array.size() ), _s_clone_iterator, _s_destroy_iterator );
            }

            virtual const IVar& operator []( int idx ) const {
                return this->get( idx >= 0 ? size_t(idx) : size_t(_array.size() + idx) );
            }

            virtual IVar& operator []( int idx ){
                if ( idx >= int(_array.size()) ){
                    try{
                        _array.resize( idx + 1, reference_type(_rp) );
                    }catch(Lsc::Exception& e){
                        throw;
                    }catch(std::exception& e){
                        throw StdException(e)<<BSL_EARG;
                    }catch(...){
                        throw UnknownException()<<BSL_EARG;
                    }
                }                
                return  this->get( idx >= 0 ? size_t(idx) : size_t(_array.size() + idx) );
            }

            //methods for dict
#if __GNUC__ > 2
            using IVar::operator [];
            using IVar::get;
            using IVar::set;
            using IVar::del;
#else
            //avoid using bug of g++ 2.96
            virtual IVar& get( const field_type& name ) {
                throw Lsc::InvalidOperationException()<<BSL_EARG<<"type["<<typeid(*this).name()<<"] this["<<dump(0)<<"] name["<<name<<"]";
            }

            virtual IVar& get( const field_type& name, IVar& default_value ) {
                throw Lsc::InvalidOperationException()<<BSL_EARG<<"type["<<typeid(*this).name()<<"] this["<<dump(0)<<"] name["<<name<<"] default["<<default_value.dump(0)<<"]";
            }

            virtual const IVar& get( const field_type& name ) const {
                throw Lsc::InvalidOperationException()<<BSL_EARG<<"type["<<typeid(*this).name()<<"] this["<<dump(0)<<"] name["<<name<<"]";
            }

            virtual const IVar& get( const field_type& name, const IVar& default_value ) const {
                throw Lsc::InvalidOperationException()<<BSL_EARG<<"type["<<typeid(*this).name()<<"] this["<<dump(0)<<"] name["<<name<<"] default["<<default_value.dump(0)<<"]";
            }

            virtual void set( const field_type& name, IVar& value_ ){
                throw Lsc::InvalidOperationException()<<BSL_EARG<<"type["<<typeid(*this).name()<<"] this["<<dump(0)<<"] name["<<name<<"] value["<<value_.dump(0)<<"]";
            }

            virtual bool del( const field_type& name ) {
                throw Lsc::InvalidOperationException()<<BSL_EARG<<"type["<<typeid(*this).name()<<"] this["<<dump(0)<<"] name["<<name<<"]";
            }

            virtual const IVar& operator []( const field_type& name ) const {
                throw Lsc::InvalidOperationException()<<BSL_EARG<<"type["<<typeid(*this).name()<<"] this["<<dump(0)<<"] name["<<name<<"]";
            }

            virtual IVar& operator []( const field_type& name ){
                throw Lsc::InvalidOperationException()<<BSL_EARG<<"type["<<typeid(*this).name()<<"] this["<<dump(0)<<"] name["<<name<<"]";
            }

#endif

        private:
            typedef std::deque<reference_type> array_type;
            class ArrayIteratorImpl;
            class ArrayConstIteratorImpl;

            class ArrayIteratorImpl: plclic IArrayIteratorImpl{
                friend class ArrayConstIteratorImpl;
            plclic:

                ArrayIteratorImpl( array_type* p_array, size_t offset )
                    :_p_array(p_array), _offset(offset){}

                virtual ~ArrayIteratorImpl() {
                    //pass
                }

                virtual size_t  key() const {
                    return _offset;
                }

                virtual IVar& value() const {
                    return (*_p_array)[_offset];
                }

                virtual void iterate(){
                    ++ _offset;
                }

                virtual void    assign( const IArrayIteratorImpl& other ) {
                    const ArrayIteratorImpl *p = dynamic_cast<const ArrayIteratorImpl *>(&other);
                    if ( !p ){
                        throw Lsc::BadCastException()<<BSL_EARG<<"from:"<<typeid(other).name()<<" to:ArrayIteratorImpl";
                    }
                    _p_array = p->_p_array;
                    _offset  = p->_offset;
                }

                virtual bool    equal_to( const IArrayIteratorImpl& other ) const;

                virtual bool    equal_to( const IArrayConstIteratorImpl& other ) const;

            private:
                array_type *_p_array;
                size_t      _offset;
            };


            class ArrayConstIteratorImpl: plclic IArrayConstIteratorImpl{
                friend class ArrayIteratorImpl;
            plclic:

                ArrayConstIteratorImpl( const array_type* p_array, size_t offset )
                    :_p_array(p_array), _offset(offset){}

                virtual ~ArrayConstIteratorImpl() {
                    //pass
                }

                virtual size_t  key() const {
                    return _offset;
                }

                virtual const IVar& value() const {
                    return (*_p_array)[_offset];
                }

                virtual void iterate(){
                    ++ _offset;
                }

                virtual void    assign( const IArrayIteratorImpl& other ) {
                    const ArrayIteratorImpl *p = dynamic_cast<const ArrayIteratorImpl *>(&other);
                    if ( !p ){
                        throw Lsc::BadCastException()<<BSL_EARG<<"from:"<<typeid(other).name()<<" to:ArrayIteratorImpl";
                    }
                    _p_array = p->_p_array;
                    _offset  = p->_offset;
                }

                virtual void    assign( const IArrayConstIteratorImpl& other ) {
                    const ArrayConstIteratorImpl *p = dynamic_cast<const ArrayConstIteratorImpl *>(&other);
                    if ( !p ){
                        throw Lsc::BadCastException()<<BSL_EARG<<"from:"<<typeid(other).name()<<" to:ArrayIteratorImpl";
                    }
                    _p_array = p->_p_array;
                    _offset  = p->_offset;
                }

                virtual bool    equal_to( const IArrayConstIteratorImpl& other ) const;

                virtual bool    equal_to( const IArrayIteratorImpl& other ) const;

            private:
                const array_type *  _p_array;
                size_t              _offset;
            };

            static IArrayIteratorImpl * _s_create_iterator( array_type* p_array, size_t offset){
                typedef typename allocator_t::template rebind<ArrayIteratorImpl>::other impl_alloc_t;
                IArrayIteratorImpl *p = impl_alloc_t().allocate(1);   //throw
                new(p) ArrayIteratorImpl(p_array, offset );  //nothrow
                return p;
            }

            static IArrayConstIteratorImpl * _s_create_const_iterator( const array_type* p_array, size_t offset){
                typedef typename allocator_t::template rebind<ArrayConstIteratorImpl>::other impl_alloc_t;
                IArrayConstIteratorImpl *p = impl_alloc_t().allocate(1);   //throw
                new(p) ArrayConstIteratorImpl(p_array, offset );  //nothrow
                return p;
            }

            static IArrayIteratorImpl * _s_clone_iterator( const IArrayIteratorImpl *p_other ){
                typedef typename allocator_t::template rebind<ArrayIteratorImpl>::other impl_alloc_t;
                const ArrayIteratorImpl *psrc = dynamic_cast<const ArrayIteratorImpl*>(p_other);
                if ( !psrc ){
                    throw Lsc::BadCastException()<<BSL_EARG<<"from:"<<typeid(*p_other).name()<<" to:ArrayIteratorImpl";
                }
                IArrayIteratorImpl *p = impl_alloc_t().allocate(1);   //throw
                new(p) ArrayIteratorImpl(*psrc);  
                return p;
            }

            static IArrayConstIteratorImpl * _s_clone_const_iterator( const IArrayConstIteratorImpl *p_other ){
                typedef typename allocator_t::template rebind<ArrayConstIteratorImpl>::other impl_alloc_t;
                const ArrayConstIteratorImpl *psrc = dynamic_cast<const ArrayConstIteratorImpl*>(p_other);
                if ( !psrc ){
                    throw Lsc::BadCastException()<<BSL_EARG<<"from:"<<typeid(*p_other).name()<<" to:ArrayIteratorImpl";
                }
                IArrayConstIteratorImpl *p = impl_alloc_t().allocate(1);   //throw
                new(p) ArrayConstIteratorImpl(*psrc);  
                return p;
            }

            static void _s_destroy_iterator( IArrayIteratorImpl * p){
                typedef typename allocator_t::template rebind<ArrayIteratorImpl>::other impl_alloc_t;
                ArrayIteratorImpl *_p = dynamic_cast<ArrayIteratorImpl *>(p); 
                if ( _p ){
                    _p->~ArrayIteratorImpl();
                    impl_alloc_t().deallocate( _p, 1 );
                }
            }

            static void _s_destroy_const_iterator( IArrayConstIteratorImpl * p){
                typedef typename allocator_t::template rebind<ArrayConstIteratorImpl>::other impl_alloc_t;
                ArrayConstIteratorImpl *_p = dynamic_cast<ArrayConstIteratorImpl *>(p); 
                if ( _p ){
                    _p->~ArrayConstIteratorImpl();
                    impl_alloc_t().deallocate( _p, 1 );
                }
            }

            array_type _array;
            Lsc::ResourcePool& _rp;
        };

    template<typename allocator_t>
        inline bool MagicBasicArray<allocator_t>::ArrayIteratorImpl::equal_to( const IArrayIteratorImpl& other ) const {
            const ArrayIteratorImpl *p = dynamic_cast<const ArrayIteratorImpl *>(&other);
            return p != NULL  && _p_array == p->_p_array && _offset == p->_offset;
        }

    template<typename allocator_t>
        inline bool MagicBasicArray<allocator_t>::ArrayIteratorImpl::equal_to( const IArrayConstIteratorImpl& other ) const {
            const ArrayConstIteratorImpl *p = dynamic_cast<const ArrayConstIteratorImpl *>(&other);
            return p != NULL  && _p_array == p->_p_array && _offset == p->_offset;
        }

    template<typename allocator_t>
        inline bool MagicBasicArray<allocator_t>::ArrayConstIteratorImpl::equal_to( const IArrayIteratorImpl& other ) const {
            const ArrayIteratorImpl *p = dynamic_cast<const ArrayIteratorImpl *>(&other);
            return p != NULL  && _p_array == p->_p_array && _offset == p->_offset;
        }

    template<typename allocator_t>
        inline bool MagicBasicArray<allocator_t>::ArrayConstIteratorImpl::equal_to( const IArrayConstIteratorImpl& other ) const {
            const ArrayConstIteratorImpl *p = dynamic_cast<const ArrayConstIteratorImpl *>(&other);
            return p != NULL  && _p_array == p->_p_array && _offset == p->_offset;
        }

}}   //namespace Lsc::var

#endif  //__BSL_VAR_MAGIC_ARRAY_H__

/* vim: set ts=4 sw=4 sts=4 tw=100 */