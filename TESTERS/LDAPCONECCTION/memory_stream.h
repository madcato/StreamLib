
namespace Stream
{

namespace Exceptions
{
	/**
		Array bound exception
	*/
	class ArrayBoundsException : public Exceptions::StreamException
	{
	public:
		ArrayBoundsException():Exceptions::StreamException(-14001,"Array bounds exception"){}
	};

} // namespace Exceptions
/**
	automatic pointer to array with bound check 
*/
template<class _Ty>
	class auto_array_ptr {
public:
	typedef _Ty element_type;
	explicit auto_array_ptr(_Ty *_P = 0,size_t size_array = 0) _THROW0()
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
	_Ty *operator->() const _THROW0()
		{return (get()); }
	_Ty *get() const _THROW0()
		{return (_Ptr); }
	_Ty *release() const _THROW0()
		{((auto_array_ptr<_Ty> *)this)->_Owns = false;
		return (_Ptr); }
	_Ty& operator[](int i)const throw(Exceptions::ArrayBoundsException*)
		{if((i < 0)||(i >= _size)) throw Exceptions::ArrayBoundsException(); return _Ptr[i];};
	size_t capacity() const _THROW0(){return _size;}
private:
	bool _Owns;
	_Ty *_Ptr;
	size_t _size;
	};


} // End namespace Stream