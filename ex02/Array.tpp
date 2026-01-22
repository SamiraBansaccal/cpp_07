/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 02:01:55 by sbansacc          #+#    #+#             */
/*   Updated: 2026/01/22 04:34:36 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

template <typename T> Array<T>::Array(): _elements(0), _size(0) {}
template <typename T> Array<T>::Array(unsigned int n): _elements(new T[n]()), _size(n) {}

template <typename T> Array<T>::Array(Array const &copy): _elements(new T[copy._size]), _size(copy._size) {
	unsigned int i = 0;
	while (i < _size)
	{
		_elements[i] = copy._elements[i];
		i++;
	}
}

template <typename T> Array<T>::~Array() { delete [] _elements; }

template <typename T> Array<T>& Array<T>::operator=(Array const &assignment) {
	unsigned int i = 0;
	if (this != &assignment)
	{
		delete[] _elements;
		_size = assignment._size;
		_elements = new T[_size];
		while (i < _size)
		{
			_elements[i] = assignment._elements[i];
			i++;
		}
	}
	return *this;
}

template <typename T> T& Array<T>::operator[](unsigned int i) {
	if (i >= _size)
		throw std::out_of_range("index out of range");
	return _elements[i];
}

template <typename T> T const & Array<T>::operator[](unsigned int i) const {
	if (i >= _size)
		throw std::out_of_range("index out of range");
	return _elements[i];
}

template <typename T> unsigned int Array<T>::size() const { return _size; }
