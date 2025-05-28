#include "String.hpp"
#include "Vector.hpp"
#include "Stack.hpp"
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


void test_stack_class() {
    std::cout << "\n=== Stack Class Test ===\n";
    int test_counter = 0;

    // ======================================================
    // 1. Stack<int>: Basic Operations
    // ======================================================
    {
        Stack<int> s;
        assert(s.empty());                     // Test 1
        ++test_counter;

        s.push(10);
        assert(!s.empty() && s.top() == 10);   // Test 2
        ++test_counter;

        s.push(20);
        assert(s.top() == 20);                    // Test 3
        ++test_counter;

        s.pop();
        assert(s.top() == 10);                    // Test 4
        ++test_counter;
    }

    // ======================================================
    // 2. Stack<int>: Initializer List, Copy & Move
    // ======================================================
    {
        Stack<int> s1 = { 1, 2, 3 };
        assert(s1.top() == 3);                    // Test 5
        ++test_counter;

        Stack<int> s2(s1); // Copy
        assert(s2.top() == 3);                    // Test 6
        s1.pop();
        assert(s1.top() != s2.top());             // Test 7
        ++test_counter += 2;

        Stack<int> s3(std::move(s2)); // Move
        assert(s3.top() == 3);                    // Test 8
        assert(s2.empty());                    // Test 9
        ++test_counter += 2;
    }

    // ======================================================
    // 3. Stack<int>: Assignment
    // ======================================================
    {
        Stack<int> s1 = { 100, 200 };
        Stack<int> s2;
        s2 = s1;

        assert(s2.top() == 200);                  // Test 10
        s1.pop();
        assert(s1.top() != s2.top());             // Test 11
        ++test_counter += 2;

        Stack<int> s3;
        s3 = std::move(s2);
        assert(s3.top() == 200);                  // Test 12
        assert(s2.empty());                    // Test 13
        ++test_counter += 2;
    }

    // ======================================================
    // 4. Stack<int>: Exceptions
    // ======================================================
    {
        Stack<int> s;
        bool caught = false;
        try { s.top(); }
        catch (...) { caught = true; }
        assert(caught);                           // Test 14

        caught = false;
        try { s.pop(); }
        catch (...) { caught = true; }
        assert(caught);                           // Test 15
        ++test_counter += 2;
    }

    // ======================================================
    // 5. Stack<std::string>: Basic & Edge Cases
    // ======================================================
    {
        Stack<String> s;
        s.push("Hello");
        s.push("World");
        assert(s.top() == "World");               // Test 16
        ++test_counter;

        s.pop();
        assert(s.top() == "Hello");               // Test 17
        ++test_counter;

        Stack<String> s2 = { "A", "B", "C" };
        assert(s2.top() == "C");                  // Test 18
        ++test_counter;

        Stack<String> s3(s2); // Copy
        s2.pop();
        assert(s3.top() == "C");                  // Test 19
        ++test_counter;

        Stack<String> s4;
        s4 = std::move(s3);
        assert(s4.top() == "C");                  // Test 20
        assert(s3.empty());                    // Test 21
        ++test_counter += 2;

        s4.clear();
        assert(s4.empty());                    // Test 22
        ++test_counter;

        bool caught = false;
        try { s4.top(); }
        catch (...) { caught = true; }
        assert(caught);                           // Test 23
        ++test_counter;
    }

    std::cout << "=== All " << test_counter << " stack tests passed! ===\n";
}

void start_all_tests() {
    test_string_class();
    test_stack_class();
}

int main() {
    start_all_tests();
    return 0;
}
