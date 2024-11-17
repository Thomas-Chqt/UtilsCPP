UtilsCPP
========

**UtilsCPP** is the cornerstone of my personal C++ projects. It is a library that includes common data structures and utilities essential for building my applications.  
The aim is to create an equivalent to the Standard Template Library (STL). While a significant portion of the standard library is not yet implemented, I continuously add features as needed.

#### Why not use the STL?

**UtilsCPP** is a personal learning project. I believe the best way to truly understand a concept is to implement it yourself.  
Additionally, to fully grasp the utility of something (e.g., smart pointers), it's important to first try doing things without it. By encountering challenges firsthand, you discover why such tools are necessary.  
This is why I’m building this library alongside all my projects, adding classes and functions as needed.

Features
--------

#### Smart Pointers

- `SharedPtr`: A shared pointer, similar to `std::shared_ptr`, providing reference-counted ownership of an object.
- `UniquePtr`: A unique pointer, similar to `std::unique_ptr`, ensuring exclusive ownership of an object.

#### Data Structures

- `Array`: A dynamically resizable array, allowing efficient memory management and element access.
- `Set`: A collection of unique elements, maintained in order using a binary search tree.
- `Dictionary`: A key-value pair data structure with unique keys, using `Set` internally for efficient storage.
- `String`: A wrapper around the `Array` class for handling null-terminated character strings.

#### Functor

- `Func`: A container for various callable types (lambdas, function pointers, and member function pointers).

#### Errors

- `Error`: The base class for all exceptions thrown by the library.
- `RuntimeError`: A subclass of `Error` that accepts a descriptive string as an argument in its constructor.

#### Typedefs and Macros

- `uint{8,16,32,64}`: Typedefs for unsigned 8, 16, 32, and 64-bit integers.
- `DEPRECATED`: Marks a symbol as deprecated.
- `UNREACHABLE`: Marks a section of code that should never be executed.

Build
-----

CMake is used as the build system. The recommended way to use the library is to clone the repository inside your project and use `add_subdirectory`.

Alternatively, the library can be built separately using CMake.

```sh
mkdir build
cmake -S . -B build
cmake --build build
```

| CMake Options         | Default Value | Description                |
|-----------------------|---------------|----------------------------|
| `BUILD_SHARED_LIBS`   |      OFF      | Build as shared library    |
| `UTILSCPP_BUILD_TESTS`|      OFF      | Build the test executable  |
| `UTILSCPP_INSTALL`    |      ON       | Enable the install command |

Learning
--------

During the development of this utility library, I deepened my understanding of key C++ concepts, particularly around data structures and memory management.  
Implementing my own vector class, `Array`, helped me understand how `std::vector` works, including the purpose of functions like `reserve` for optimizing memory usage.  
Working with shared pointers further improved my grasp of efficient memory management. Additionally, developing template classes enhanced my ability to write flexible, type-agnostic code.  
This project also improved my testing skills, as I used Google Test to create comprehensive unit tests, ensuring the reliability of each component.

Future Plans
------------

As I continue to work on new projects, **UtilsCPP** will grow and adapt to meet evolving requirements. Future development will focus on both expanding the library’s feature set and optimizing existing components:

- **Additional Containers**: Implementing more data structures, such as linked lists, queues, and stacks, to provide a wider range of options for efficient data handling and further broaden the utility of the library.
- **Enhancing Current Containers**: Improving the performance and robustness of existing containers. For example, the current `Set` class relies on a basic binary search tree that isn’t self-balancing. Future optimizations will focus on implementing self-balancing trees or other efficient data structures to ensure optimal performance, especially for large datasets.