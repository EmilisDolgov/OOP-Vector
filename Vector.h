#ifndef VECTOR_H
#define VECTOR_H

#include <iterator>

template <typename T>
class Vector 
{
public:
	typedef T                                     value_type;
	typedef ptrdiff_t                             difference_type;
	typedef T &                                   reference;
	typedef const T &                             const_reference;
	typedef T *                                   pointer;
	typedef const T *                             const_pointer;
	typedef T *                                   iterator;
	typedef const T *                             const_iterator;
	typedef std::reverse_iterator<iterator>       reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	typedef unsigned int                          size_type;

	Vector() noexcept;
	explicit Vector(size_type n);
	Vector(size_type n, const T &val);
	Vector(typename Vector<T>::iterator first, typename Vector<T>::iterator last);
	Vector(std::initializer_list<T>);
	Vector(const Vector<T> &);
	Vector(Vector<T> &&) noexcept;
	~Vector();
	Vector<T> & operator = (const Vector<T> &);
	Vector<T> & operator = (Vector<T> &&);
	Vector<T> & operator = (std::initializer_list<T>);
	void assign(size_type, const T &value);
	void assign(typename Vector<T>::iterator, typename Vector<T>::iterator);
	void assign(std::initializer_list<T>);

	iterator begin() noexcept;
	const_iterator cbegin() const noexcept;
	iterator end() noexcept;
	const_iterator cend() const noexcept;
	reverse_iterator rbegin() noexcept;
	const_reverse_iterator crbegin() const noexcept;
	reverse_iterator rend() noexcept;
	const_reverse_iterator crend() const noexcept;

	bool empty() const noexcept;
	size_type Size() const noexcept;
	size_type Capacity() const noexcept;
	void resize(size_type);
	void resize(size_type, const T &);
	void reserve(size_type);

	reference operator [](size_type);
	const_reference operator [](size_type) const;
	reference at(size_type);
	const_reference at(size_type) const;
	reference front();
	const_reference front() const;
	reference back();
	const_reference back() const;

	T * data() noexcept;
	const T * data() const noexcept;

	template <class ... Args> void emplace_back(Args && ... args);
	void push_back(const T &);
	void push_back(T &&);
	void pop_back();

	template <class ... Args> iterator emplace(const_iterator, Args && ...);
	iterator insert(const_iterator, const T &);
	iterator insert(const_iterator, T &&);
	iterator insert(const_iterator, size_type, const T&);
	template <class InputIt> iterator insert(const_iterator, InputIt, InputIt);
	iterator insert(const_iterator, std::initializer_list<T>);
	iterator erase(const_iterator);
	iterator erase(const_iterator, const_iterator);
	void swap(Vector<T> &);
	void clear() noexcept;

	bool operator == (const Vector<T> &) const;
	bool operator != (const Vector<T> &) const;
	bool operator < (const Vector<T> &) const;
	bool operator <= (const Vector<T> &) const;
	bool operator > (const Vector<T> &) const;
	bool operator >= (const Vector<T> &) const;
private:
	size_type capacity = 4;
	size_type size = 0;
	T *elem;
	inline void reallocate();

};
//defaultinis konstruktorius
template <typename T>
Vector<T>::Vector() noexcept {
	elem = new T[capacity];
}
//konstruktorius su paduotu dydžiu
template <typename T>
Vector<T>::Vector(typename Vector<T>::size_type n) {
	size_type i;
	capacity = n << 2; //pašiftina bitus 2 kartus
	elem = new T[capacity];
	for (i = 0; i < n; ++i)
		elem[i] = T();
	size = n;
}
//konstruktorius su paduotu dydžiu ir reikšme, kuria užpildo visą vektorių
template <typename T>
Vector<T>::Vector(typename Vector<T>::size_type n, const T &value) {
	size_type i;
	capacity = n << 2; //pašiftina bitus 2 kartus
	elem = new T[capacity];
	for (i = 0; i < n; ++i)
		elem[i] = value;
	size = n;
}
//konstruktorius su pradžios ir pabaigos iteratoriais
template <typename T>
Vector<T>::Vector(typename Vector<T>::iterator begin, typename Vector<T>::iterator end) {
	size_type i, count = end - begin;
	capacity = count << 2; //pašiftina bitus 2 kartus
	elem = new T[capacity];
	for (i = 0; i < count; ++i, ++first)
		elem[i] = *first;
	size = count;
}
//konstruktorius su listu
template <typename T>
Vector<T>::Vector(std::initializer_list<T> lst) {
	capacity = lst.size() << 2; //pašiftina bitus 2 kartus
	elem = new T[capacity];
	for (auto &i : lst)
		elem[size++] = i;
}
//copy konstruktorius
template <typename T>
Vector<T>::Vector(const Vector<T> &other) {
	size_type i;
	capacity = other.capacity;
	elem = new T[capacity];
	for (i = 0; i < other.size; ++i)
		elem[i] = other.elem[i];
	size = other.size;
}
//move konstruktorius
template <typename T>
Vector<T>::Vector(Vector<T> &&other) noexcept {
	size_type i;
	capacity = other.capacity;
	elem = new T[capacity];
	for (i = 0; i < other.vec_sz; ++i)
		elem[i] = std::move(other.elem[i]);
	size = other.size;
}
//destruktorius
template <typename T>
Vector<T>::~Vector() {
	delete[] elem;
}
//copy priskyrimo operatorius
template <typename T>
Vector<T> & Vector<T>::operator=(const Vector<T> &other) {
	size_type i;
	if (capacity < other.size) {
		size = other.size << 2;//pašiftina bitus 2 kartus
		reallocate();
	}
	for (i = 0; i < other.size; ++i)
		elem[i] = other.elem[i];
	size = other.size;
}
//move priskyrimo operatorius
template <typename T>
Vector<T> & Vector<T>::operator = (Vector<T> &&other) {
	size_type i;
	if (size < other.size) {
		size = other.size << 2;
		reallocate();
	}
	for (i = 0; i < other.size; ++i)
		elem[i] = std::move(other.elem[i]);
	size = other.size;
}
//operatorius listui priskirt
template <typename T>
Vector<T> & Vector<T>::operator = (std::initializer_list<T> lst) {
	if (capacity < lst.size()) {
		capacity = lst.size() << 2;
		reallocate();
	}
	size = 0;
	for (auto &i : lst)
		elem[size++] = i;
}
//assign funkcija su paduodamu nauju dydžiu ir reikšme
template <typename T>
void Vector<T>::assign(typename Vector<T>::size_type count, const T &value) {
	size_type i;
	if (count > capacity) {
		capacity = count << 2;
		reallocate();
	}
	for (i = 0; i < count; ++i)
		elem[i] = value;
	size = count;
}
//assign funkcija su paduodamais iteratoriais
template <typename T>
void Vector<T>::assign(typename Vector<T>::iterator begin, typename Vector<T>::iterator end) {
	size_type i, count = end-begin;
	if (count > capacity) {
		capacity = count << 2;
		reallocate();
	}
	for (i = 0; i < count; ++i, ++begin)
		elem[i] = *begin;
	size = count;
}
//assign funkcija su paduodamu listu
template <typename T>
void Vector<T>::assign(std::initializer_list<T> lst) {
	size_type i, count = lst.size();
	if (count > capacity) {
		capacity = count << 2;
		reallocate();
	}
	i = 0;
	for (auto &it : lst)
		elem[i++] = it;
}
//reallocate funkcija naudojama kitose funkcijose
template <typename T>
inline void Vector<T>::reallocate() {
	T *telem = new T[capacity];
	memcpy(telem, elem, size * sizeof(T));
	delete[] elem;
	elem = telem;
}
//begin iteratorius
template <typename T>
typename Vector<T>::iterator Vector<T>::begin() noexcept {
	return elem;
}
//const begin iteratorius
template <typename T>
typename Vector<T>::const_iterator Vector<T>::cbegin() const noexcept {
	return elem;
}
//end iteratorius
template <typename T>
typename Vector<T>::iterator Vector<T>::end() noexcept {
	return elem + size;
}
//const end iteratorius
template <typename T>
typename Vector<T>::const_iterator Vector<T>::cend() const noexcept {
	return elem + size;
}
//reverse begin iteratorius
template <typename T>
typename Vector<T>::reverse_iterator Vector<T>::rbegin() noexcept {
	return reverse_iterator(elem+size);
}
//const reverse begin iteratorius
template <typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::crbegin() const noexcept {
	return reverse_iterator(elem+size);
}
//reverse end iteratorius
template <typename T>
typename Vector<T>::reverse_iterator Vector<T>::rend() noexcept {
	return reverse_iterator(elem);
}
//reverse const end iteratorius
template <typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::crend() const noexcept {
	return reverse_iterator(elem);
}
//empty funkcija, patikrina ar vectorius tuščias
template <typename T>
bool Vector<T>::empty() const noexcept {
	return size == 0;
}
//size funkcija, grąžina vectoriaus dydį
template <typename T>
typename Vector<T>::size_type Vector<T>::Size() const noexcept {
	return size;
}
//capacity funkcija, grąžina vektoriaus capacity
template <typename T>
typename Vector<T>::size_type Vector<T>::Capacity() const noexcept {
	return capacity;
}
//resize funkcija, pakeičia vectoriaus dydį nauja pateikta
template <typename T>
void Vector<T>::resize(typename Vector<T>::size_type sz) {
	if (sz > size) {
		if (sz > capacity) {
			size= sz;
			reallocate();
		}
	}
	else {
		size_type i;
		for (i = size; i < sz; ++i)
			elem[i].~T();
	}
	size= sz;
}
//resize funkcija, pakeičia vectoriaus dydį nauju ir priskiria naują reikšmę
template <typename T>
void Vector<T>::resize(typename Vector<T>::size_type sz, const T &c) {
	if (sz > size) {
		if (sz > capacity) {
			capacity = sz;
			reallocate();
		}
		size_type i;
		for (i = size; i < sz; ++i)
			elem[i] = c;
	}
	else {
		size_type i;
		for (i = size; i < sz; ++i)
			elem[i].~T();
	}
	size = sz;
}
//reserve funkcija norint iš anksto priskirti dydį vectoriui
template <typename T>
void Vector<T>::reserve(typename Vector<T>::size_type _sz) {
	if (_sz > capacity) {
		capacity = _sz;
		reallocate();
	}
};
//operatorius[]
template <typename T>
typename Vector<T>::reference Vector<T>::operator [](typename Vector<T>::size_type idx) {
	return elem[idx];
}
//const operatorius[]
template <typename T>
typename Vector<T>::const_reference Vector<T>::operator [](typename Vector<T>::size_type idx) const {
	return elem[idx];
}
//funkcija at
template <typename T>
typename Vector<T>::reference Vector<T>::at(size_type pos) {
	if (pos < size)
		return elem[pos];
	else
		throw std::out_of_range("accessed position is out of range");
}
//const funkcija at
template <typename T>
typename Vector<T>::const_reference Vector<T>::at(size_type pos) const {
	if (pos < size)
		return elem[pos];
	else
		throw std::out_of_range("accessed position is out of range");
}
//funckija grąžinanti pirmą elementą vectoriaus
template <typename T>
typename Vector<T>::reference Vector<T>::front() {
	return elem[0];
}
//const funkcija grąžinanti pirmą elementa vectoriaus
template <typename T>
typename Vector<T>::const_reference Vector<T>::front() const {
	return elem[0];
}
//funkcija grąžinanti paskutinį vectoriaus elementą
template <typename T>
typename Vector<T>::reference Vector<T>::back() {
	return elem[size - 1];
}
//const funkcija grąžinanti paskutinį vectoriaus elementą
template <typename T>
typename Vector<T>::const_reference Vector<T>::back() const {
	return elem[size - 1];
}

//funkcija grąžina data
template <typename T>
T * Vector<T>::data() noexcept {
	return elem;
}
//const funkcija grąžina data
template <typename T>
const T * Vector<T>::data() const noexcept {
	return elem;
}
//funkcija prideda reikšmę į vectoriaus galą per konstruktorių
template <typename T>
template <class ... Args>
void Vector<T>::emplace_back(Args && ... args) {
	if (size == capacity) {
		capacity <<= 2;
		reallocate();
	}
	elem[size] = std::move(T(std::forward<Args>(args) ...));
	++size;
}
//funkcija kopijuoja reikšmę į vectoriaus galą 
template <typename T>
void Vector<T>::push_back(const T &val) {
	if (size == capacity) {
		capacity <<= 2;
		reallocate();
	}
	elem[size] = val;
	++size;
}
//funkcija perkelia reikšmę į vectoriaus galą
template <typename T>
void Vector<T>::push_back(T &&val) {
	if (size == capacity) {
		capacity <<= 2;
		reallocate();
	}
	elem[size] = std::move(val);
	++size;
}
//funkcija ištrina paskutinį elementą
template <typename T>
void Vector<T>::pop_back() {
	--size;
	elem[size].~T();
}
//prideda elementą į vietą prieš paduotą per konstruktorių
template <typename T>
template <class ... Args>
typename Vector<T>::iterator Vector<T>::emplace(typename Vector<T>::const_iterator it, Args && ... args) {
	iterator iit = &elem[it - elem];
	if (size == capacity) {
		capacity <<= 2;
		reallocate();
	}
	memmove(iit + 1, iit, (size - (it - elem)) * sizeof(T));
	(*iit) = std::move(T(std::forward<Args>(args) ...));
	++size;
	return iit;
}
//kopijuoja elementą į vietą prieš paduotą 
template <typename T>
typename Vector<T>::iterator Vector<T>::insert(typename Vector<T>::const_iterator it, const T &val) {
	iterator iit = &elem[it - elem];
	if (size == capacity) {
		capacity<<= 2;
		reallocate();
	}
	memmove(iit + 1, iit, (size - (it - elem)) * sizeof(T));
	(*iit) = val;
	++size;
	return iit;
}
//perkelia elementą į vietą prieš paduotą
template <typename T>
typename Vector<T>::iterator Vector<T>::insert(typename Vector<T>::const_iterator it, T &&val) {
	iterator iit = &elem[it - elem];
	if (size== capacity) {
		capacity <<= 2;
		reallocate();
	}
	memmove(iit + 1, iit, (size - (it - elem)) * sizeof(T));
	(*iit) = std::move(val);
	++size;
	return iit;
}
//įterpia cnt kiekį kopijų paduotų reikšmių prieš paduotą poziciją
template <typename T>
typename Vector<T>::iterator Vector<T>::insert(typename Vector<T>::const_iterator it, typename Vector<T>::size_type cnt, const T &val) {
	iterator f = &elem[it - elem];
	if (!cnt) return f;
	if (size + cnt > capacity) {
		capacity = (size + cnt) << 2;
		reallocate();
	}
	memmove(f + cnt, f, (size - (it - elem)) * sizeof(T));
	size += cnt;
	for (iterator it = f; cnt--; ++it)
		(*it) = val;
	return f;
}
//įterpia elementus iš range'o nuo begin iki end prieš paduotą poziciją
template <typename T>
template <class InputIt>
typename Vector<T>::iterator Vector<T>::insert(typename Vector<T>::const_iterator it, InputIt begin, InputIt end) {
	iterator f = &elem[it - elem];
	size_type cnt = end-begin;
	if (!cnt) return f;
	if (size + cnt > capacity) {
		capacity= (size + cnt) << 2;
		reallocate();
	}
	memmove(f + cnt, f, (size - (it - elem)) * sizeof(T));
	for (iterator it = f; begin != end; ++it, ++begin)
		(*it) = *begin;
	size += cnt;
	return f;
}
//įterpia reikšmes iš listo prieš paduotą poziciją
template <typename T>
typename Vector<T>::iterator Vector<T>::insert(typename Vector<T>::const_iterator it, std::initializer_list<T> lst) {
	size_type cnt = lst.size();
	iterator f = &elem[it - elem];
	if (!cnt) return f;
	if (size+ cnt >capacity) {
		capacity = (size + cnt) << 2;
		reallocate();
	}
	memmove(f + cnt, f, (size - (it - elem)) * sizeof(T));
	iterator iit = f;
	for (auto &i : lst) {
		(*iit) = i;
		++iit;
	}
	size += cnt;
	return f;
}
//ištrina reikšmę paduotoje pozicijoje
template <typename T>
typename Vector<T>::iterator Vector<T>::erase(typename Vector<T>::const_iterator it) {
	iterator iit = &elem[it - elem];
	(*iit).~T();
	memmove(iit, iit + 1, (size - (it - elem) - 1) * sizeof(T));
	--size;
	return iit;
}
//ištrina reikšmes paduotame intervale
template <typename T>
typename Vector<T>::iterator Vector<T>::erase(typename Vector<T>::const_iterator begin, typename Vector<T>::const_iterator end) {
	iterator f = &elem[begin - elem];
	if (begin == end) return f;
	for (; begin != end; ++begin)
		(*begin).~T();
	memmove(f, end, (size - (end - elem)) * sizeof(T));
	size -= end -begin;
	return f;
}
//sukeičia vectorių reikšmes vietomis
template <typename T>
void Vector<T>::swap(Vector<T> &rhs) {
	size_t tsize = size,
		tcapacity = capacity;
	T *telem = elem;

	size = rhs.size;
	capacity= rhs.capacity;
	arr = rhs.arr;

	rhs.size= tsize;
	rhs.capacit = tcapacity;
	rhs.elem = telem;
}
//ištrina visas reikšmes iš vektoriaus
template <typename T>
void Vector<T>::clear() noexcept {
	size_type i;
	for (i = 0; i < size; ++i)
	    elem[i].~T();
	size = 0;
};
template <typename T>
bool Vector<T>::operator == (const Vector<T> &rhs) const {
	if (size != rhs.size) return false;
	size_type i;
	for (i = 0; i <size; ++i)
		if (elem[i] != rhs.elem[i])
			return false;
	return true;
}

template <typename T>
bool Vector<T>::operator != (const Vector<T> &rhs) const {
	if (size!= rhs.size) return true;
	size_type i;
	for (i = 0; i <size; ++i)
		if (elem[i] != rhs.elem[i])
			return true;
	return false;
}

template <typename T>
bool Vector<T>::operator < (const Vector<T> &rhs) const {
	size_type i, j, ub = size < rhs.size ? size : rhs.size;
	for (i = 0; i < ub; ++i)
		if (elem[i] != rhs.elem[i])
			return elem[i] < rhs.elem[i];
	return size < rhs.size;
}

template <typename T>
bool Vector<T>::operator <= (const Vector<T> &rhs) const {
	size_type i, j, ub = size < rhs.size ? size : rhs.size;
	for (i = 0; i < ub; ++i)
		if (elem[i] != rhs.elem[i])
			return elem[i] < elem.arr[i];
	return size <= rhs.size;
}

template <typename T>
bool Vector<T>::operator > (const Vector<T> &rhs) const {
	size_type i, j, ub = size < rhs.size ? size : rhs.size;
	for (i = 0; i < ub; ++i)
		if (elem[i] != rhs.elem[i])
			return elem[i] > rhs.elem[i];
	return size > rhs.size;
}

template <typename T>
bool Vector<T>::operator >= (const Vector<T> &rhs) const {
	size_type i, j, ub = size < rhs.size ? size : rhs.size;
	for (i = 0; i < ub; ++i)
		if (elem[i] != rhs.elem[i])
			return elem[i] > rhs.elem[i];
	return size >= rhs.size;
};

#endif //!VECTOR_H