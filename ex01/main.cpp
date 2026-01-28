/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 00:10:42 by sbansacc          #+#    #+#             */
/*   Updated: 2026/01/22 00:46:23 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "iter.hpp"

/* ===== Fonctions de test ===== */

void print_int(int &x)
{
	std::cout << x << " ";
}

void print_const_int(int const &x)
{
	std::cout << x << " ";
}

void increment(int &x)
{
	x++;
}

template <typename T>
void print_template(T const &x)
{
	std::cout << x << " ";
}

/* ===== Main ===== */

int main(void)
{
	std::cout << "==== int array (modifiable) ====" << std::endl;
	int a[] = {1, 2, 3, 4, 5};

	iter(a, 5, print_int);
	std::cout << std::endl;

	iter(a, 5, increment);
	iter(a, 5, print_int);
	std::cout << std::endl << std::endl;

	std::cout << "==== int array (const) ====" << std::endl;
	int const b[] = {10, 20, 30, 40};

	iter(b, 4, print_const_int);
	std::cout << std::endl;

	iter(b, 4, print_template<int>);
	std::cout << std::endl << std::endl;

	std::cout << "==== string array ====" << std::endl;
	std::string s[] = {"hello", "cpp", "templates"};

	iter(s, 3, print_template<std::string>);
	std::cout << std::endl;

	std::cout << "==== string array (const) ====" << std::endl;
	std::string const cs[] = {"42", "school"};

	iter(cs, 2, print_template<std::string>);
	std::cout << std::endl;

	return 0;
}