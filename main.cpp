#include "String.hpp"
#include "Vector.hpp"
#include <cassert>
#include <iostream>

void test_string_class() {
    std::cout << "\n=== String Class Test ===\n";
    int test_counter = 0;

    // ======================================================
    // 1. Constructors and Basic Operations
    // ======================================================
    {
        String s1;
        assert(s1.is_empty() && s1.capacity() == 1); // Test 1
        ++test_counter;

        String s2("Hello");
        assert(s2.size() == 5 && s2[4] == 'o'); // Test 2
        ++test_counter;
    }

    // ======================================================
    // 2. erase() Method Edge Cases
    // ======================================================
    {

        String s1("ABCDEF");
        s1.erase(0, 2); 
        assert(s1 == "DEF" && s1.size() == 3); // Test 3
        ++test_counter;

        s1.erase(1, 2); 
        assert(s1 == "D" && s1.size() == 1); // Test 4
        ++test_counter;

        s1.erase(0, 0); 
        assert(s1 == "" && s1.is_empty()); // Test 5
        ++test_counter;;

        bool exception = false;
        try { s1.erase(0, 0); }
        catch (...) { exception = true; }
        assert(exception); // Test 6
        ++test_counter;
    }

    // ======================================================
    // 3. replace() Method Edge Cases
    // ======================================================
    {
        String s("ABCDEF");


        s.replace(0, 2, "XY");
        assert(s == "XYDEF" && s.size() == 5); // Test 7
        ++test_counter;

        s.replace(4, 4, "Z");
        assert(s == "XYDEZ" && s.size() == 5); // Test 8
        ++test_counter;

        s.replace(0, 4, "Hello");
        assert(s == "Hello" && s.size() == 5); // Test 9
        ++test_counter;
    }

    // ======================================================
    // 4. Combined Operations Test
    // ======================================================
    {
        String s("Start");

        s.erase(0, 1); 
        assert(s == "art" && s.size() == 3); // Test 10
        ++test_counter;

        s.replace(1, 1, "eplace"); 
        assert(s == "aeplacet" && s.size() == 8); // Test 11
        ++test_counter;

        s.erase(3, 7); 
        assert(s == "aep" && s.size() == 3); // Test 12
        ++test_counter;
    }

    // ======================================================
    // 5. Move Constructor Test
    // ======================================================
    {
        String source("MoveMe");
        String dest(std::move(source));

        assert(dest == "MoveMe");                     // Test 13
        assert(source.is_empty());                    // Test 14
        assert(dest.capacity() == 7);                 // Test 15
        test_counter += 3;
    }

    // ======================================================
     // 6. Move Assignment Operator
     // ======================================================
    {
        String source("Hello");
        String dest;
        dest = std::move(source);

        assert(dest == "Hello");                      // Test 16
        assert(source.is_empty());                    // Test 17
        test_counter += 2;
    }

    // ======================================================
    // 7. += Operator Tests
    // ======================================================
    {
        String s1("Hello");
        String s2("World");

        s1 += " ";
        assert(s1 == "Hello ");                       // Test 18

        s1 += s2;
        assert(s1 == "Hello World");                  // Test 19

        String empty;
        s1 += empty;
        assert(s1 == "Hello World");                  // Test 20
        test_counter += 3;
    }

    // ======================================================
    // 8. + Operator Tests
    // ======================================================
    {
        String s1("Hello");
        String s2("World");
        String s3 = s1 + " " + s2;

        assert(s3 == "Hello World");                  // Test 21
        assert(s1 == "Hello");                        // Test 22
        assert(s2 == "World");                        // Test 23

        String s4 = String() + "Test";
        assert(s4 == "Test");                         // Test 24
        test_counter += 4;
    }

    // ======================================================
    // 9. Comparison Operators
    // ======================================================
    {
        String s1("Apple");
        String s2("Apple");
        String s3("apple");
        String s4("App");

        assert(s1 == s2);                             // Test 25
        assert(s1 != s3);                             // Test 26
        assert(s1 != s4);                             // Test 27
        assert(s4 != "Apple");                        // Test 28
        test_counter += 4;
    }

    // ======================================================
    // 10. C-string Constructor Edge Cases
    // ======================================================
    {
        String s("");
        assert(s.is_empty());                         // Test 29

        String s2("X");
        assert(s2.size() == 1);                       // Test 30

        bool exception = false;
        try { String s3(nullptr); }
        catch (...) { exception = true; }
        assert(exception);                            // Test 31
        test_counter += 3;
    }

    // ======================================================
    // 11. Copy Constructor Test
    // ======================================================
    {
        String original("Original");
        String copy(original);

        assert(copy == original);                     // Test 32
        assert(copy.capacity() == original.capacity());// Test 33

        original[0] = 'X';
        assert(copy != original);                     // Test 34
        test_counter += 3;
    }

    // ======================================================
    // 12. Self-Assignment Test
    // ======================================================
    {
        String s("SelfAssign");
        s = s;
        assert(s == "SelfAssign");                    // Test 35
        ++test_counter;
    }


    std::cout << "=== All " << test_counter << " string tests passed! ===\n";
}


void test_vector_class() {
    std::cout << "\n=== Vector Class Test ===\n";
    int test_counter = 0;

    // ======================================================
    // 1. Constructors and Basic Operations
    // ======================================================
    {
        Vector<int> v1;
        assert(v1.empty() && v1.capacity() == 10 && v1.size() == 0); // Test 1
        test_counter++;

        Vector<String> v2;
        assert(v2.empty() && v2.capacity() == 10); // Test 2
        test_counter++;
    }

    // ======================================================
    // 2. Push/Pop Operations
    // ======================================================
    {
        Vector<int> v;
        v.push_back(10);
        assert(v.size() == 1 && v[0] == 10); // Test 3
        test_counter++;

        v.pop_back();
        assert(v.empty()); // Test 4
        test_counter++;

        Vector<String> vs;
        vs.emplace_back("Test");
        assert(vs.back() == "Test"); // Test 5
        test_counter++;
    }

    // ======================================================
    // 3. Iterator Functionality
    // ======================================================
    {
        Vector<int> v{ 1, 2, 3 };
        auto it = v.begin();
        assert(*it == 1); // Test 6
        test_counter++;

        ++it;
        assert(*it == 2); // Test 7
        test_counter++;

        auto end = v.end();
        assert(it != end); // Test 8
        test_counter++;

        bool caught = false;
        try { v.end()++; }
        catch (...) { caught = true; }
        assert(caught); // Test 9
        test_counter++;
    }

    // ======================================================
    // 4. Element Access and Modifiers
    // ======================================================
    {
        Vector<String> v{ "A", "B", "C" };
        assert(v.front() == "A" && v.back() == "C"); // Test 10
        test_counter++;

        v[1] = "X";
        assert(v[1] == "X"); // Test 11
        test_counter++;

        bool caught = false;
        try { v.at(5); }
        catch (...) { caught = true; }
        assert(caught); // Test 12
        test_counter++;
    }

    // ======================================================
    // 5. Memory Management
    // ======================================================
    {
        Vector<int> v;
        v.reserve(100);
        assert(v.capacity() == 100 && v.empty()); // Test 13
        test_counter++;

        v.resize(5, 10);
        assert(v.size() == 5 && v[4] == 10); // Test 14
        test_counter++;

        v.shrink_to_fit();
        assert(v.capacity() == 5); // Test 15
        test_counter++;
    }

    // ======================================================
    // 6. Copy/Move Semantics
    // ======================================================
    {
        Vector<int> v1{ 1,2,3 };
        Vector<int> v2 = v1;
        assert(v2.size() == 3 && v2[2] == 3); // Test 16
        test_counter++;

        Vector<int> v3 = std::move(v1);
        assert(v3.size() == 3 && v1.empty()); // Test 17
        test_counter++;
    }

    // ======================================================
    // 7. Complex Operations
    // ======================================================
    {
        Vector<int> v{ 1,2,3,4,5 };

        // Erase elements
        auto first = v.begin() + 1;
        auto last = v.begin() + 3;
        v.erase(first, last);
        assert(v.size() == 3 && v[1] == 4); // Test 18
        test_counter++;

        // Insert element
        v.insert(10, v.begin() + 1);
        assert(v.size() == 4 && v[1] == 10); // Test 19
        test_counter++;

        // Clear vector
        v.clear();
        assert(v.empty()); // Test 20
        test_counter++;
    }

    std::cout << "=== All " << test_counter << " vector tests passed! ===\n";
}

void start_all_tests() {
    test_string_class();
    test_vector_class();
}


int main() {
    start_all_tests();
    return 0;
}
