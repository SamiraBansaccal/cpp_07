/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 00:58:54 by sbansacc          #+#    #+#             */
/*   Updated: 2026/01/30 21:50:32 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <exception>
#include <cstdlib> // For srand() and rand()
#include <ctime>   // For time()

template <typename T>
class Array {
	public:
		Array();
		Array(unsigned int n);
		Array(Array const &copy);
		~Array();
		
		Array& operator=(Array const &assignment);
		T& operator[](unsigned int i);
		T const &operator[](unsigned int i) const;
		
		unsigned int size() const;
	private:
		T				*_elements;
		unsigned int	_size;
};

#include "Array.tpp"

#endif