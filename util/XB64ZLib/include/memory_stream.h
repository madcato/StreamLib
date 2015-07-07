
#ifndef __MEMORY_STREAM__H__
#define __MEMORY_STREAM__H__

/// namespace stream
namespace stream
{

/// namespace exceptions
namespace exceptions
{
	/**
		Array bound exception
	*/
	class ArrayBoundsException : public exceptions::StreamException
	{
	public:
		ArrayBoundsException():exceptions::StreamException(-1,"Array bounds exception"){}
	};

} // namespace exceptions

/// namespace util
namespace util
{

/**
	Automatic pointer to array with bound check 
*/
template<class _Ty>
	class auto_array_ptr {
public:
	typedef _Ty element_type;
	auto_array_ptr() _THROW0()
		: _Owns(false), _Ptr(0),_size(0) {}
	explicit auto_array_ptr(size_t size_array,_Ty *_P) _THROW0()
		: _Owns(_P != 0), _Ptr(_P),_size(size_array) {}
	explicit auto_array_ptr(size_t size_array) _THROW0()
		: _Owns(true){_Ptr = new _Ty[size_array];_size = size_array; memset(_Ptr,0,_size);}
	auto_array_ptr(const auto_array_ptr<_Ty>& _Y) _THROW0()
		: _Owns(_Y._Owns), _size(_Y._size), _Ptr(_Y.release()) {}
	auto_array_ptr<_Ty>& operator=(const auto_array_ptr<_Ty>& _Y) _THROW0()
		{if (this != &_Y)
			{if (_Ptr != _Y.get())
				{if (_Owns)
					delete[] _Ptr;
				_Owns = _Y._Owns; }
			else if (_Y._Owns)
				_Owns = true;
			_Ptr = _Y.release(); 
			_size = _Y._size; }
		return (*this); }
	~auto_array_ptr()
		{if (_Owns)
			delete[] _Ptr; }
	/**
		Cast operator for char arrays.
		@return A new BLOB obejct
	*/
	operator auto_array_ptr<char>()
	{
		auto_array_ptr<char> array(this->capacity(),(char*)this->release());

		return array;
	}

	
	_Ty *operator->() const _THROW0()
		{return (get()); }
	_Ty *get() const _THROW0()
		{return (_Ptr); }
	_Ty *release() const _THROW0()
		{((auto_array_ptr<_Ty> *)this)->_Owns = false;
		return (_Ptr); }
	_Ty& operator[](int i) throw(exceptions::ArrayBoundsException*)
		{if((i < 0)||(i >= _size)) throw new exceptions::ArrayBoundsException(); return _Ptr[i];};
	_Ty operator[](int i)const throw(exceptions::ArrayBoundsException*)
		{if((i < 0)||(i >= _size)) throw new exceptions::ArrayBoundsException(); return _Ptr[i];};
	size_t capacity() const _THROW0(){return _size;}
private:
	bool _Owns;
	_Ty *_Ptr;
	size_t _size;
	};



/**
	Reference counted pointer.
*/
template<class _Ty>
class ref_count_ptr
{
public:
	typedef _Ty element_type;
	explicit ref_count_ptr() _THROW0()
		: _Ptr(new _Ty),_ref_count(new _internal_ref_count()) {}
	explicit ref_count_ptr(_Ty *_P) _THROW0()
		: _Ptr(_P),_ref_count(new _internal_ref_count()) {}	
	ref_count_ptr(const ref_count_ptr<_Ty>& _Y) _THROW0()
		: _ref_count(_Y._ref_count), _Ptr(_Y.get()) {_ref_count->_ref_count++;}
	ref_count_ptr<_Ty>& operator=(const ref_count_ptr<_Ty>& _Y) _THROW0()
		{ _Y._ref_count->_ref_count++; _ref_count = _Y._ref_count; _Ptr = _Y.get();
		return (*this); }
	ref_count_ptr(const std::auto_ptr<_Ty>& _Y) _THROW0()
		: _ref_count(new _internal_ref_count()), _Ptr(_Y.release()){}
	~ref_count_ptr()
		{ if (_ref_count->_ref_count == 1)
			{
				delete _Ptr;
				delete _ref_count;
			}
			else
			{
				_ref_count->_ref_count--;
			}
		}	
	_Ty *operator->() const _THROW0()
		{return (get()); }
	_Ty *get() const _THROW0()
		{return (_Ptr); }	
private:
	
	class _internal_ref_count
	{
	public:
		_internal_ref_count():_ref_count(1){}		
		int _ref_count;
	};

	_Ty *_Ptr;
	_internal_ref_count* _ref_count;

	
};

} // namespace util

} // End namespace stream

#endif __MEMORY_STREAM__H__