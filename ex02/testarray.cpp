/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testarray.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 04:11:07 by sbansacc          #+#    #+#             */
/*   Updated: 2026/01/22 04:18:21 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "Array.hpp"

template <typename T>
void printArray(const Array<T>& arr, const std::string& name) {
    std::cout << name << " [size=" << arr.size() << "]: ";
    for (unsigned int i = 0; i < arr.size(); i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}

void testArray() {
    std::cout << "\n========== TEST CONSTRUCTEURS ==========" << std::endl;
    
    // Test constructeur vide
    Array<int> empty;
    std::cout << "✓ Array vide créé, size = " << empty.size() << std::endl;
    
    // Test constructeur avec taille
    Array<int> arr(5);
    std::cout << "✓ Array de 5 int créé, size = " << arr.size() << std::endl;
    
    // Initialisation
    for (unsigned int i = 0; i < arr.size(); i++)
        arr[i] = i * 10;
    printArray(arr, "arr");
    
    std::cout << "\n========== TEST COPY CONSTRUCTOR ==========" << std::endl;
    
    Array<int> copy(arr);
    printArray(copy, "copy");
    
    // Modification de l'original
    arr[0] = 999;
    std::cout << "Après arr[0] = 999:" << std::endl;
    printArray(arr, "arr");
    printArray(copy, "copy (doit rester inchangé)");
    
    std::cout << "\n========== TEST OPERATOR= ==========" << std::endl;
    
    Array<int> assigned;
    assigned = arr;
    printArray(assigned, "assigned");
    
    // Modification de l'original
    arr[1] = 888;
    std::cout << "Après arr[1] = 888:" << std::endl;
    printArray(arr, "arr");
    printArray(assigned, "assigned (doit rester inchangé)");
    
    std::cout << "\n========== TEST EXCEPTIONS ==========" << std::endl;
    
    Array<int> test(3);
    for (unsigned int i = 0; i < test.size(); i++)
        test[i] = i + 1;
    printArray(test, "test");
    
    // Test index négatif (converti en grand unsigned)
    try {
        std::cout << "Tentative d'accès à index -1..." << std::endl;
        test[-1] = 42;
        std::cout << "✗ ERREUR: exception non lancée!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "✓ Exception attrapée: " << e.what() << std::endl;
    }
    
    // Test index = size
    try {
        std::cout << "Tentative d'accès à index " << test.size() << "..." << std::endl;
        test[test.size()] = 42;
        std::cout << "✗ ERREUR: exception non lancée!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "✓ Exception attrapée: " << e.what() << std::endl;
    }
    
    // Test index très grand
    try {
        std::cout << "Tentative d'accès à index 999..." << std::endl;
        test[999] = 42;
        std::cout << "✗ ERREUR: exception non lancée!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "✓ Exception attrapée: " << e.what() << std::endl;
    }
    
    std::cout << "\n========== TEST AVEC D'AUTRES TYPES ==========" << std::endl;
    
    // Test avec std::string
    Array<std::string> strings(3);
    strings[0] = "Hello";
    strings[1] = "World";
    strings[2] = "!";
    printArray(strings, "strings");
    
    // Test avec float
    Array<float> floats(4);
    for (unsigned int i = 0; i < floats.size(); i++)
        floats[i] = i * 1.5f;
    printArray(floats, "floats");
    
    std::cout << "\n========== TEST CONST ==========" << std::endl;
    
    const Array<int> constArr(arr);
    std::cout << "Array const, premier élément: " << constArr[0] << std::endl;
    std::cout << "✓ operator[] const fonctionne" << std::endl;
    
    std::cout << "\n========== TOUS LES TESTS PASSÉS ==========" << std::endl;
}