/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 23:49:07 by sbansacc          #+#    #+#             */
/*   Updated: 2026/01/30 21:43:07 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
#define WHATEVER_HPP

template <typename T>
void	swap(T &a, T &b) {
	T tmp = b;
	b = a;
	a = tmp;
};

template <typename T>
T const	&min(T const &a, T const &b) {
	if (a < b)
		return a;
	return b;
};

template <typename T>
T const	&max(T const &a, T const &b) {
	if (b < a)
		return a;
	return b;
};

#endif