#include <iostream>
#include "Array.hpp"
#include <string>
#include <sstream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include "Array.hpp"

// Couleurs pour l'output
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

int g_tests_passed = 0;
int g_tests_failed = 0;

void printTestHeader(const std::string& title) {
    std::cout << "\n" << CYAN << "╔═══════════════════════════════════════════════════╗" << RESET << std::endl;
    std::cout << CYAN << "║ " << title;
    for (size_t i = title.length(); i < 48; i++) std::cout << " ";
    std::cout << "║" << RESET << std::endl;
    std::cout << CYAN << "╚═══════════════════════════════════════════════════╝" << RESET << std::endl;
}

void assertTest(bool condition, const std::string& testName) {
    if (condition) {
        std::cout << GREEN << "✓ " << testName << RESET << std::endl;
        g_tests_passed++;
    } else {
        std::cout << RED << "✗ " << testName << RESET << std::endl;
        g_tests_failed++;
    }
}

template <typename T>
void printArray(const Array<T>& arr, const std::string& name) {
    std::cout << YELLOW << name << RESET << " [size=" << arr.size() << "]: ";
    for (unsigned int i = 0; i < arr.size() && i < 10; i++)
        std::cout << arr[i] << " ";
    if (arr.size() > 10)
        std::cout << "... (" << (arr.size() - 10) << " more)";
    std::cout << std::endl;
}

// Test 1: Constructeurs basiques
void test_constructors() {
    printTestHeader("TEST 1: CONSTRUCTEURS BASIQUES");
    
    // Constructeur vide
    Array<int> empty;
    assertTest(empty.size() == 0, "Constructeur vide: size = 0");
    
    // Constructeur avec 0
    Array<int> zero(0);
    assertTest(zero.size() == 0, "Constructeur Array(0): size = 0");
    
    // Constructeur avec 1
    Array<int> one(1);
    assertTest(one.size() == 1, "Constructeur Array(1): size = 1");
    
    // Constructeur avec taille normale
    Array<int> normal(42);
    assertTest(normal.size() == 42, "Constructeur Array(42): size = 42");
    
    // Constructeur avec grande taille
    Array<int> big(10000);
    assertTest(big.size() == 10000, "Constructeur Array(10000): size = 10000");
    
    std::cout << BLUE << "→ Les éléments sont initialisés par défaut (0 pour int)" << RESET << std::endl;
    Array<int> test(5);
    bool all_zero = true;
    for (unsigned int i = 0; i < test.size(); i++) {
        if (test[i] != 0) all_zero = false;
    }
    assertTest(all_zero, "Initialisation par défaut: tous les éléments = 0");
}

// Test 2: Copy constructor - Deep copy
void test_copy_constructor() {
    printTestHeader("TEST 2: COPY CONSTRUCTOR (DEEP COPY)");
    
    Array<int> original(5);
    for (unsigned int i = 0; i < original.size(); i++)
        original[i] = i * 10;
    
    Array<int> copy(original);
    
    assertTest(copy.size() == original.size(), "Taille copiée correctement");
    
    bool values_match = true;
    for (unsigned int i = 0; i < copy.size(); i++) {
        if (copy[i] != original[i]) values_match = false;
    }
    assertTest(values_match, "Valeurs copiées correctement");
    
    // Modification de l'original
    original[0] = 999;
    original[2] = 888;
    
    assertTest(copy[0] == 0 && copy[2] == 20, "Deep copy: modification de l'original n'affecte pas la copie");
    
    // Modification de la copie
    copy[1] = 777;
    assertTest(original[1] == 10, "Deep copy: modification de la copie n'affecte pas l'original");
    
    // Copy d'un tableau vide
    Array<int> empty;
    Array<int> empty_copy(empty);
    assertTest(empty_copy.size() == 0, "Copy constructor d'un tableau vide");
}

// Test 3: Operator= - Deep copy et auto-assignation
void test_assignment_operator() {
    printTestHeader("TEST 3: OPERATOR= (DEEP COPY & AUTO-ASSIGNATION)");
    
    Array<int> src(5);
    for (unsigned int i = 0; i < src.size(); i++)
        src[i] = i * 100;
    
    Array<int> dst(3);
    for (unsigned int i = 0; i < dst.size(); i++)
        dst[i] = 999;
    
    dst = src;
    
    assertTest(dst.size() == src.size(), "Taille copiée correctement");
    
    bool values_match = true;
    for (unsigned int i = 0; i < dst.size(); i++) {
        if (dst[i] != src[i]) values_match = false;
    }
    assertTest(values_match, "Valeurs copiées correctement");
    
    src[0] = 777;
    assertTest(dst[0] == 0, "Deep copy: modification de src n'affecte pas dst");
    
    // Auto-assignation
    Array<int> self(5);
    for (unsigned int i = 0; i < self.size(); i++)
        self[i] = i;
    
    Array<int>* ptr = &self;  // 👈 Ruse via pointeur
    self = *ptr;              // 👈 Le compilateur ne voit pas que c'est self = self
    
    bool self_intact = true;
    for (unsigned int i = 0; i < self.size(); i++) {
        if (self[i] != static_cast<int>(i)) self_intact = false;
    }
    assertTest(self_intact && self.size() == 5, "Auto-assignation: tableau intact");
    
    // Assignation avec différentes tailles
    Array<int> small(2);
    Array<int> large(100);
    small = large;
    assertTest(small.size() == 100, "Assignation: petite taille → grande taille");
    
    Array<int> large2(100);
    Array<int> small2(2);
    large2 = small2;
    assertTest(large2.size() == 2, "Assignation: grande taille → petite taille");
    
    // Assignation vide
    Array<int> empty;
    Array<int> full(10);
    full = empty;
    assertTest(full.size() == 0, "Assignation d'un tableau vide");
}

// Test 4: Operator[] - Accès et modification
void test_subscript_operator() {
    printTestHeader("TEST 4: OPERATOR[] (ACCÈS & MODIFICATION)");
    
    Array<int> arr(10);
    
    // Écriture
    for (unsigned int i = 0; i < arr.size(); i++)
        arr[i] = i * 2;
    
    // Lecture
    bool values_ok = true;
    for (unsigned int i = 0; i < arr.size(); i++) {
        if (arr[i] != static_cast<int>(i * 2)) values_ok = false;
    }
    assertTest(values_ok, "Écriture et lecture via operator[]");
    
    // Premier élément
    arr[0] = 42;
    assertTest(arr[0] == 42, "Accès au premier élément [0]");
    
    // Dernier élément
    arr[arr.size() - 1] = 99;
    assertTest(arr[arr.size() - 1] == 99, "Accès au dernier élément [size-1]");
    
    // Modification en chaîne
    arr[5] = arr[3] + arr[4];
    assertTest(arr[5] == (3*2 + 4*2), "Modification en chaîne");
}

// Test 5: Operator[] const
void test_const_subscript() {
    printTestHeader("TEST 5: OPERATOR[] CONST");
    
    Array<int> arr(5);
    for (unsigned int i = 0; i < arr.size(); i++)
        arr[i] = i * 10;
    
    const Array<int> const_arr(arr);
    
    bool values_ok = true;
    for (unsigned int i = 0; i < const_arr.size(); i++) {
        if (const_arr[i] != static_cast<int>(i * 10)) values_ok = false;
    }
    assertTest(values_ok, "Lecture via operator[] const");
    
    // Note: const_arr[0] = 42; ne devrait pas compiler
    std::cout << BLUE << "→ Impossible de modifier via const (vérifié à la compilation)" << RESET << std::endl;
}

// Test 6: Exceptions - Index hors limites
void test_exceptions() {
    printTestHeader("TEST 6: EXCEPTIONS (INDEX HORS LIMITES)");
    
    Array<int> arr(5);
    
    // Index = size
    bool caught = false;
    try {
        arr[5] = 42;
    } catch (const std::exception& e) {
        caught = true;
    }
    assertTest(caught, "Exception pour index = size");
    
    // Index > size
    caught = false;
    try {
        arr[100] = 42;
    } catch (const std::exception& e) {
        caught = true;
    }
    assertTest(caught, "Exception pour index > size");
    
    // Index très grand
    caught = false;
    try {
        arr[999999] = 42;
    } catch (const std::exception& e) {
        caught = true;
    }
    assertTest(caught, "Exception pour index très grand");
    
    // Index "négatif" (converti en unsigned énorme)
    caught = false;
    try {
        int neg = -1;
        arr[neg] = 42;
    } catch (const std::exception& e) {
        caught = true;
    }
    assertTest(caught, "Exception pour index négatif (-1)");
    
    caught = false;
    try {
        int neg = -42;
        arr[neg] = 42;
    } catch (const std::exception& e) {
        caught = true;
    }
    assertTest(caught, "Exception pour index négatif (-42)");
    
    // Lecture hors limites
    caught = false;
    try {
        int x = arr[10];
        (void)x;
    } catch (const std::exception& e) {
        caught = true;
    }
    assertTest(caught, "Exception pour lecture hors limites");
    
    // Tableau vide
    Array<int> empty;
    caught = false;
    try {
        empty[0] = 42;
    } catch (const std::exception& e) {
        caught = true;
    }
    assertTest(caught, "Exception pour accès à tableau vide[0]");
    
    // UINT_MAX
    caught = false;
    try {
        arr[std::numeric_limits<unsigned int>::max()] = 42;
    } catch (const std::exception& e) {
        caught = true;
    }
    assertTest(caught, "Exception pour index = UINT_MAX");
}

// Test 7: Différents types
void test_different_types() {
    printTestHeader("TEST 7: DIFFÉRENTS TYPES");
    
    // std::string
    Array<std::string> strings(3);
    strings[0] = "Hello";
    strings[1] = "World";
    strings[2] = "!";
    assertTest(strings[0] == "Hello" && strings[1] == "World", "Array<std::string>");
    
    // float
    Array<float> floats(3);
    floats[0] = 3.14f;
    floats[1] = 2.71f;
    floats[2] = 1.41f;
    assertTest(floats[0] > 3.13f && floats[0] < 3.15f, "Array<float>");
    
    // double
    Array<double> doubles(2);
    doubles[0] = 3.141592653589793;
    doubles[1] = 2.718281828459045;
    assertTest(doubles[0] > 3.14 && doubles[0] < 3.15, "Array<double>");
    
    // char
    Array<char> chars(5);
    chars[0] = 'H';
    chars[1] = 'e';
    chars[2] = 'l';
    chars[3] = 'l';
    chars[4] = 'o';
    assertTest(chars[0] == 'H' && chars[4] == 'o', "Array<char>");
    
    // bool
    Array<bool> bools(3);
    bools[0] = true;
    bools[1] = false;
    bools[2] = true;
    assertTest(bools[0] == true && bools[1] == false, "Array<bool>");
    
    // long
    Array<long> longs(2);
    longs[0] = 1234567890L;
    longs[1] = -9876543210L;
    assertTest(longs[0] == 1234567890L, "Array<long>");
}

// Test 8: Grandes tailles
void test_large_arrays() {
    printTestHeader("TEST 8: GRANDES TAILLES");
    
    // 10k éléments
    Array<int> medium(10000);
    assertTest(medium.size() == 10000, "Array de 10,000 éléments");
    medium[0] = 1;
    medium[9999] = 2;
    assertTest(medium[0] == 1 && medium[9999] == 2, "Accès premier/dernier sur 10k");
    
    // 100k éléments
    Array<int> large(100000);
    assertTest(large.size() == 100000, "Array de 100,000 éléments");
    
    // Test de remplissage
    for (unsigned int i = 0; i < 1000; i++)
        large[i] = i;
    bool fill_ok = true;
    for (unsigned int i = 0; i < 1000; i++) {
        if (large[i] != static_cast<int>(i)) fill_ok = false;
    }
    assertTest(fill_ok, "Remplissage et vérification sur 100k");
    
    std::cout << BLUE << "→ Attention: très grandes tailles peuvent échouer selon la RAM" << RESET << std::endl;
}

// Test 9: Copie en chaîne
void test_chain_copy() {
    printTestHeader("TEST 9: COPIE EN CHAÎNE");
    
    Array<int> a(5);
    for (unsigned int i = 0; i < a.size(); i++)
        a[i] = i;
    
    Array<int> b(a);
    Array<int> c(b);
    Array<int> d(c);
    
    a[0] = 999;
    b[1] = 888;
    c[2] = 777;
    
    assertTest(d[0] == 0 && d[1] == 1 && d[2] == 2, "Deep copy en chaîne: d intact");
    assertTest(c[0] == 0 && c[1] == 1, "Deep copy en chaîne: c partiellement intact");
    assertTest(b[0] == 0, "Deep copy en chaîne: b partiellement intact");
}

// Test 10: Assignation en chaîne
void test_chain_assignment() {
    printTestHeader("TEST 10: ASSIGNATION EN CHAÎNE");
    
    Array<int> a(3);
    Array<int> b(3);
    Array<int> c(3);
    
    for (unsigned int i = 0; i < a.size(); i++)
        a[i] = i * 10;
    
    c = b = a;
    
    assertTest(b.size() == 3 && c.size() == 3, "Assignation en chaîne: tailles OK");
    assertTest(b[0] == 0 && b[1] == 10 && c[0] == 0 && c[1] == 10, "Assignation en chaîne: valeurs OK");
    
    a[0] = 999;
    assertTest(b[0] == 0 && c[0] == 0, "Assignation en chaîne: copies indépendantes");
}

// Test 11: Scope et destruction
void test_scope_destruction() {
    printTestHeader("TEST 11: SCOPE & DESTRUCTION");
    
    std::cout << BLUE << "→ Création et destruction dans des scopes imbriqués" << RESET << std::endl;
    
    {
        Array<int> outer(100);
        outer[50] = 42;
        
        {
            Array<int> inner(50);
            inner[25] = 99;
            
            {
                Array<int> deep(10);
                deep[5] = 77;
                assertTest(deep[5] == 77, "Accès dans scope profond");
            }
            
            assertTest(inner[25] == 99, "Scope interne intact après destruction scope profond");
        }
        
        assertTest(outer[50] == 42, "Scope externe intact après destruction scope interne");
    }
    
    std::cout << GREEN << "✓ Aucun crash lors de la destruction (pas de double-free)" << RESET << std::endl;
    g_tests_passed++;
}

// Test 12: Edge cases vicieux
void test_evil_edge_cases() {
    printTestHeader("TEST 12: EDGE CASES VICIEUX 😈");
    
    // Copie puis modification immédiate
    Array<int> orig(5);
    orig[2] = 42;
    Array<int> copy = orig;
    copy[2] = 99;
    assertTest(orig[2] == 42, "Copie puis modification immédiate");
    
    // Assignation multiple
    Array<int> x(3), y(3), z(3);
    x[0] = 1; y[0] = 2; z[0] = 3;
    x = y = z;
    assertTest(x[0] == 3 && y[0] == 3, "Assignation multiple");
    
    // Copie d'un tableau qui sera détruit
    Array<int>* temp = new Array<int>(5);
    (*temp)[2] = 123;
    Array<int> survivor(*temp);
    delete temp;
    assertTest(survivor[2] == 123, "Copie survit à la destruction de l'original");
    
    // Tableau dans un tableau (via pointeur)
    Array<int*> arr_of_ptrs(3);
    int a = 1, b = 2, c = 3;
    arr_of_ptrs[0] = &a;
    arr_of_ptrs[1] = &b;
    arr_of_ptrs[2] = &c;
    assertTest(*arr_of_ptrs[0] == 1 && *arr_of_ptrs[2] == 3, "Array<int*>");
    
    // Size 1 - edge case classique
    Array<int> one(1);
    one[0] = 42;
    assertTest(one.size() == 1 && one[0] == 42, "Array de taille 1");
    
    bool caught = false;
    try {
        one[1] = 99;
    } catch (const std::exception& e) {
        caught = true;
    }
    assertTest(caught, "Array taille 1: exception pour [1]");
}

// Test 13: Stress test aléatoire
void test_random_stress() {
    printTestHeader("TEST 13: STRESS TEST ALÉATOIRE");
    
    srand(time(NULL));
    
    const unsigned int SIZE = 1000;
    Array<int> arr(SIZE);
    int* mirror = new int[SIZE];
    
    // Remplissage aléatoire
    for (unsigned int i = 0; i < SIZE; i++) {
        int val = rand();
        arr[i] = val;
        mirror[i] = val;
    }
    
    // Vérification
    bool match = true;
    for (unsigned int i = 0; i < SIZE; i++) {
        if (arr[i] != mirror[i]) match = false;
    }
    assertTest(match, "Stress test: 1000 valeurs aléatoires");
    
    // Copie et vérification
    Array<int> copy(arr);
    match = true;
    for (unsigned int i = 0; i < SIZE; i++) {
        if (copy[i] != mirror[i]) match = false;
    }
    assertTest(match, "Stress test: copie de 1000 valeurs");
    
    // Modification et vérification d'indépendance
    for (unsigned int i = 0; i < SIZE; i += 2) {
        arr[i] = rand();
    }
    
    match = true;
    for (unsigned int i = 1; i < SIZE; i += 2) {
        if (copy[i] != mirror[i]) match = false;
    }
    assertTest(match, "Stress test: copie indépendante après modifications");
    
    delete[] mirror;
}

// Test 14: Performance basique
void test_basic_performance() {
    printTestHeader("TEST 14: PERFORMANCE BASIQUE");
    
    std::cout << BLUE << "→ Test de performance (indicatif, pas de timing précis)" << RESET << std::endl;
    
    const unsigned int SIZE = 10000;
    
    // Construction
    Array<int> arr(SIZE);
    std::cout << GREEN << "✓ Construction de " << SIZE << " éléments" << RESET << std::endl;
    g_tests_passed++;
    
    // Écriture
    for (unsigned int i = 0; i < SIZE; i++)
        arr[i] = i;
    std::cout << GREEN << "✓ Écriture de " << SIZE << " éléments" << RESET << std::endl;
    g_tests_passed++;
    
    // Lecture
    long sum = 0;
    for (unsigned int i = 0; i < SIZE; i++)
        sum += arr[i];
    std::cout << GREEN << "✓ Lecture de " << SIZE << " éléments (sum=" << sum << ")" << RESET << std::endl;
    g_tests_passed++;
    
    // Copie
    Array<int> copy(arr);
    std::cout << GREEN << "✓ Copie de " << SIZE << " éléments" << RESET << std::endl;
    g_tests_passed++;
}

// Main de test
void runAllTests() {
    std::cout << MAGENTA << "\n";
    std::cout << "╔═════════════════════════════════════════════════════════╗\n";
    std::cout << "║                                                         ║\n";
    std::cout << "║         TESTEUR ULTRA-COMPLET Array<T>                  ║\n";
    std::cout << "║         Edge cases, pièges & stress tests               ║\n";
    std::cout << "║                                                         ║\n";
    std::cout << "╚═════════════════════════════════════════════════════════╝\n";
    std::cout << RESET << std::endl;
    
    test_constructors();
    test_copy_constructor();
    test_assignment_operator();
    test_subscript_operator();
    test_const_subscript();
    test_exceptions();
    test_different_types();
    test_large_arrays();
    test_chain_copy();
    test_chain_assignment();
    test_scope_destruction();
    test_evil_edge_cases();
    test_random_stress();
    test_basic_performance();
    
    // Résumé final
    std::cout << "\n" << MAGENTA << "╔═════════════════════════════════════════════════════════╗" << RESET << std::endl;
    std::cout << MAGENTA << "║                    RÉSUMÉ FINAL                         ║" << RESET << std::endl;
    std::cout << MAGENTA << "╚═════════════════════════════════════════════════════════╝" << RESET << std::endl;
    
    int total = g_tests_passed + g_tests_failed;
    std::cout << "\nTests réussis: " << GREEN << g_tests_passed << "/" << total << RESET << std::endl;
    
    if (g_tests_failed > 0) {
        std::cout << "Tests échoués: " << RED << g_tests_failed << "/" << total << RESET << std::endl;
    }
    
    double percentage = (total > 0) ? (100.0 * g_tests_passed / total) : 0;
    
    std::cout << "\nScore: ";
    if (percentage == 100.0) {
        std::cout << GREEN << percentage << "% 🎉 PARFAIT!" << RESET << std::endl;
    } else if (percentage >= 90.0) {
        std::cout << GREEN << percentage << "% 👍 Très bien!" << RESET << std::endl;
    } else if (percentage >= 75.0) {
        std::cout << YELLOW << percentage << "% ⚠️  Pas mal, mais à améliorer" << RESET << std::endl;
    } else {
        std::cout << RED << percentage << "% ❌ À revoir!" << RESET << std::endl;
    }
    
    std::cout << std::endl;
}

int main() {
    runAllTests();
    return 0;
}