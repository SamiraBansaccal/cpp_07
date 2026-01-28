/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 00:10:39 by sbansacc          #+#    #+#             */
/*   Updated: 2026/01/22 00:46:59 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

template <typename T, typename F>
void iter(T *array, size_t const len, F f) {
	size_t i = 0;
	while (i < len)
		f(array[i++]);
};

