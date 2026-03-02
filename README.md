# CPP Module 07 (42 School)

## 📋 Description
This module introduces **Templates** in C++. It covers the creation of function templates and class templates, allowing for generic programming where the same logic can be applied to different data types without code duplication.

## 🧠 Implementation Logic (Score: 100/100)
The exercises focus on syntax and the power of generic blueprints:

- **Ex00: Start with a few functions**: 
  - Implementation of `swap`, `min`, and `max` as function templates.
  - Understanding that templates allow these functions to work with any type that supports comparison operators (`<`, `>`).
- **Ex01: Iter**: 
  - Development of a template function `iter` that takes an array address, its length, and a function pointer to apply that function to every element of the array.
  - This demonstrates how templates can interact with function pointers and different array types (int, string, etc.).
- **Ex02: Array**: 
  - Implementation of a class template `Array` that mimics a dynamic array.
  - **Memory Management**: Allocation of memory for type `T` using `new[]`, and proper cleanup in the destructor.
  - **Subscript Operator**: Overloading the `[]` operator to allow element access with bounds checking (throwing an `std::out_of_range` exception if the index is invalid).
  - Proper handling of the Orthodox Canonical Form within a template class.

## 📂 Project Structure
- `ex00/`: Basic templates (`swap`, `min`, `max`).
- `ex01/`: Iter (Generic array iteration).
- `ex02/`: Array (Class template for dynamic arrays).

## 🛠️ Usage & Compilation
All exercises are compiled with the `-std=c++98` flag.
```bash
make
```
