#include "containers/String.hpp"
#include "containers/Vector.hpp"
#include "containers/Stack.hpp"
#include "containers/Queue.hpp"
#include "containers/List.hpp"
#include <cassert>
#include <iostream>
#include <string>


void test_vector_class() {
    std::cout << "\n=== Vector Class Test ===\n";
    int test_counter = 0;

    // ======================================================
    // 1. Constructors and Basic Operations
    // ======================================================
    {
        Vector<int> v1;
        assert(v1.empty() && v1.capacity() == 10 && v1.size() == 0); // Test 1
        ++test_counter;

        Vector<String> v2;
        assert(v2.empty() && v2.capacity() == 10); // Test 2
        ++test_counter;
    }

    // ======================================================
    // 2. Push/Pop Operations
    // ======================================================
    {
        Vector<int> v;
        v.push_back(10);
        assert(v.size() == 1 && v[0] == 10); // Test 3
        ++test_counter;

        v.pop_back();
        assert(v.empty()); // Test 4
        ++test_counter;

        Vector<String> vs;
        vs.emplace_back("Test");
        assert(vs.back() == "Test"); // Test 5
        ++test_counter;
    }

    // ======================================================
    // 3. Iterator Functionality
    // ======================================================
    {
        Vector<int> v{ 1, 2, 3 };
        auto it = v.begin();
        assert(*it == 1); // Test 6
        ++test_counter;

        ++it;
        assert(*it == 2); // Test 7
        ++test_counter;

        auto end = v.end();
        assert(it != end); // Test 8
        ++test_counter;

        bool caught = false;
        try { v.end()++; }
        catch (...) { caught = true; }
        assert(caught); // Test 9
        ++test_counter;
    }

    // ======================================================
    // 4. Element Access and Modifiers
    // ======================================================
    {
        Vector<String> v{ "A", "B", "C" };
        assert(v.front() == "A" && v.back() == "C"); // Test 10
        ++test_counter;

        v[1] = "X";
        assert(v[1] == "X"); // Test 11
        ++test_counter;

        bool caught = false;
        try { v.at(5); }
        catch (...) { caught = true; }
        assert(caught); // Test 12
        ++test_counter;
    }

    // ======================================================
    // 5. Memory Management
    // ======================================================
    {
        Vector<int> v;
        v.reserve(100);
        assert(v.capacity() == 100 && v.empty()); // Test 13
        ++test_counter;

        v.resize(5, 10);
        assert(v.size() == 5 && v[4] == 10); // Test 14
        ++test_counter;

        v.shrink_to_fit();
        assert(v.capacity() == 5); // Test 15
        ++test_counter;
    }

    // ======================================================
    // 6. Copy/Move Semantics
    // ======================================================
    {
        Vector<int> v1{ 1,2,3 };
        Vector<int> v2 = v1;
        assert(v2.size() == 3 && v2[2] == 3); // Test 16
        ++test_counter;

        Vector<int> v3 = std::move(v1);
        assert(v3.size() == 3 && v1.empty()); // Test 17
        ++test_counter;
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
        ++test_counter;

        // Insert element
        v.insert(10, v.begin() + 1);
        assert(v.size() == 4 && v[1] == 10); // Test 19
        ++test_counter;

        // Clear vector
        v.clear();
        assert(v.empty()); // Test 20
        ++test_counter;
    }

    std::cout << "=== All " << test_counter << " vector tests passed! ===\n";
}


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

        String s3("");
        assert(s3.is_empty() && s3.capacity() == 1); // Test 3
        ++test_counter;

        bool exception = false;
        try { String s4(nullptr); }
        catch (const std::invalid_argument&) { exception = true; }
        assert(exception); // Test 4
        ++test_counter;
    }

    // ======================================================
    // 2. Element Access (at, operator[])
    // ======================================================
    {
        String s("ABCD");
        assert(s.at(0) == 'A' && s[3] == 'D'); // Test 5
        ++test_counter;

        bool exception1 = false;
        try { s.at(5); }
        catch (const std::out_of_range&) { exception1 = true; }
        assert(exception1); // Test 6
        ++test_counter;

        s[1] = 'X';
        assert(s == "AXCD"); // Test 7
        ++test_counter;

        const String& cs = s;
        assert(cs[2] == 'C'); // Test 8
        ++test_counter;
    }

    // ======================================================
    // 3. Modifiers (push_back, pop_back, clear)
    // ======================================================
    {
        String s;
        s.push_back('A');
        assert(s == "A" && s.size() == 1); // Test 9
        ++test_counter;

        for (char c : {'B', 'C', 'D'}) s.push_back(c);
        assert(s == "ABCD"); // Test 10
        ++test_counter;

        s.pop_back();
        assert(s == "ABC"); // Test 11
        ++test_counter;

        s.clear();
        assert(s.is_empty()); // Test 12
        ++test_counter;

        bool exception = false;
        try { s.pop_back(); }
        catch (const std::out_of_range&) { exception = true; }
        assert(exception); // Test 13
        ++test_counter;
    }

    // ======================================================
    // 4. Insert Method
    // ======================================================
    {
        String s("Hello");
        s.insert(5, " World");
        assert(s == "Hello World"); // Test 14
        ++test_counter;

        s.insert(0, "Start: ");
        assert(s == "Start: Hello World"); // Test 15
        ++test_counter;

        s.insert(7, "Inserted ");
        assert(s == "Start: Inserted Hello World"); // Test 16
        ++test_counter;

        String empty;
        empty.insert(0, "Test");
        assert(empty == "Test"); // Test 17
        ++test_counter;

        bool exception = false;
        try { s.insert(100, "Fail"); }
        catch (const std::out_of_range&) { exception = true; }
        assert(exception); // Test 18
        ++test_counter;
    }

    // ======================================================
    // 5. Erase Method
    // ======================================================
    {
        String s1("ABCDEF");
        s1.erase(0, 2);
        assert(s1 == "DEF" && s1.size() == 3); // Test 19
        ++test_counter;

        s1.erase(1, 2);
        assert(s1 == "D" && s1.size() == 1); // Test 20
        ++test_counter;

        s1.erase(0, 0);
        assert(s1 == "" && s1.is_empty()); // Test 21
        ++test_counter;

        bool exception = false;
        try { s1.erase(0, 0); }
        catch (const std::out_of_range&) { exception = true; }
        assert(exception); // Test 22
        ++test_counter;

        String s2("Complete");
        s2.erase(2, 5);
        assert(s2 == "Cote"); // Test 23
        ++test_counter;
    }

    // ======================================================
    // 6. Replace Method
    // ======================================================
    {
        String s("ABCDEF");

        s.replace(0, 2, "XY");
        assert(s == "XYDEF" && s.size() == 5); // Test 24
        ++test_counter;

        s.replace(4, 4, "Z");
        assert(s == "XYDEZ" && s.size() == 5); // Test 25
        ++test_counter;

        s.replace(0, 4, "Hello");
        assert(s == "Hello" && s.size() == 5); // Test 26
        ++test_counter;

        s.replace(0, 3, "");
        assert(s == "o" && s.size() == 1); // Test 27
        ++test_counter;

        bool exception = false;
        try { s.replace(2, 1, "X"); }
        catch (const std::out_of_range&) { exception = true; }
        assert(exception); // Test 28
        ++test_counter;
    }

    // ======================================================
    // 7. Combined Operations
    // ======================================================
    {
        String s("Start");
        s.erase(0, 1);
        assert(s == "art" && s.size() == 3); // Test 29
        ++test_counter;

        s.replace(1, 1, "eplace");
        assert(s == "aeplacet" && s.size() == 8); // Test 30
        ++test_counter;

        s.erase(3, 7);
        assert(s == "aep" && s.size() == 3); // Test 31
        ++test_counter;

        s.insert(3, "END");
        assert(s == "aepEND"); // Test 32
        ++test_counter;
    }

    // ======================================================
    // 8. Capacity Management
    // ======================================================
    {
        String s;
        s.reserve(100);
        assert(s.capacity() >= 100 && s.is_empty()); // Test 33
        ++test_counter;

        s = "Hello";
        s.shrink_to_fit();
        assert(s.capacity() == 6 && s == "Hello"); // Test 34
        ++test_counter;

        s.resize(10, 'X');
        assert(s.size() == 10 && s[9] == 'X'); // Test 35
        ++test_counter;

        s.resize(3, 'Y');
        assert(s.size() == 3 && s == "Hel"); // Test 36
        ++test_counter;
    }

    // ======================================================
    // 9. Move Semantics
    // ======================================================
    {
        String source("MoveMe");
        String dest(std::move(source));
        assert(dest == "MoveMe" && dest.capacity() == 7); // Test 37
        assert(source.is_empty() && source.capacity() == 0); // Test 38
        test_counter += 2;

        String dest2;
        dest2 = std::move(dest);
        assert(dest2 == "MoveMe"); // Test 39
        assert(dest.is_empty()); // Test 40
        test_counter += 2;
    }

    // ======================================================
    // 10. Operators (+, +=, ==, !=)
    // ======================================================
    {
        String s1("Hello");
        s1 += " ";
        assert(s1 == "Hello "); // Test 41
        ++test_counter;

        String s2("World");
        s1 += s2;
        assert(s1 == "Hello World"); // Test 42
        ++test_counter;

        String s3 = s1 + "!";
        assert(s3 == "Hello World!"); // Test 43
        ++test_counter;

        assert(String("A") + "B" == "AB"); // Test 44
        ++test_counter;

        assert(s1 != s3 && String("A") != String("B")); // Test 45
        ++test_counter;

        s1 = "Test";
        s2 = "Test";
        assert(s1 == s2); // Test 46
        ++test_counter;
    }

    // ======================================================
    // 11. Copy Semantics
    // ======================================================
    {
        String orig("Original");
        String copy(orig);
        assert(copy == orig); // Test 47
        assert(copy.capacity() == orig.capacity()); // Test 48
        ++test_counter;

        copy[0] = 'X';
        assert(orig == "Original" && copy == "Xriginal"); // Test 49
        ++test_counter;

        String copy2;
        copy2 = orig;
        assert(copy2 == orig); // Test 50
        ++test_counter;
    }

    // ======================================================
    // 12. Edge Cases & Exceptions
    // ======================================================
    {
        String s;
        s.reserve(0); // Should be no-op
        assert(s.capacity() == 1); // Test 51
        ++test_counter;

        s = "A";
        s.shrink_to_fit();
        assert(s.capacity() == 2); // Test 52
        ++test_counter;

        String empty1, empty2;
        empty1 += empty2;
        assert(empty1.is_empty()); // Test 53
        ++test_counter;

        String s2("AB");
        s2.replace(0, 1, s2); // Self-replacement
        assert(s2 == "AB"); // Test 54
        ++test_counter;
    }

    // ======================================================
   // 13. Iterator Tests
   // ======================================================
    {
        // Basic iteration
        String s("Hello");
        size_t count = 0;
        for (String::Iterator it = s.begin(); it != s.end(); ++it) {
            ++count;
        }
        assert(count == s.size()); // Test 55
        ++test_counter;

        // Dereference and modification
        String::Iterator it = s.begin();
        *it = 'J';
        assert(s == "Jello"); // Test 56
        ++test_counter;

        // Value access
        it = s.begin() + 1;
        assert(*it == 'e'); // Test 57
        ++test_counter;

        // Increment/Decrement
        ++it;
        assert(*it == 'l'); // Test 58
        ++test_counter;
        it--;
        assert(*it == 'e'); // Test 59
        ++test_counter;

        // Arithmetic operations
        String::Iterator it2 = s.begin() + 3;
        assert(*(it2) == 'l'); // Test 60
        ++test_counter;
        assert(*(it2 + 1) == 'o'); // Test 61
        ++test_counter;

        // Comparison
        assert(it < it2); // Test 62
        ++test_counter;
        assert(!(it >= it2)); // Test 63
        ++test_counter;

        // Bounds checking
        bool exception = false;
        try {
            String::Iterator end_it = s.end();
            *end_it;
        }
        catch (const std::out_of_range&) {
            exception = true;
        }
        assert(exception); // Test 64
        ++test_counter;

        // Empty string iteration
        String empty;
        assert(empty.begin() == empty.end()); // Test 65
        ++test_counter;

        // Reverse iteration
        String rev;
        for (String::Iterator rit = s.end() - 1; rit >= s.begin(); --rit) {
            rev.push_back(*rit);
        }
        assert(rev == "olleJ"); // Test 66
        ++test_counter;

        // Partial range
        String part;
        for (String::Iterator pit = s.begin() + 1; pit < s.end() - 1; ++pit) {
            part.push_back(*pit);
        }
        assert(part == "ell"); // Test 67
        ++test_counter;

        // Iterator with replace/insert
        it = s.begin() + 4;
        s.replace(4, 4, "y!");
        it = s.end() - 1;
        assert(*it == '!'); // Test 68 (проверка валидности после изменения)
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


void test_queue_class() {
    std::cout << "\n=== Queue Class Test ===\n";
    int test_counter = 0;

    // ======================================================
    // 1. Basic Operations
    // ======================================================
    {
        Queue<String> q;
        assert(q.empty());                     // Test 1
        ++test_counter;

        q.push("A");
        assert(!q.empty());                    // Test 2
        assert(q.size() == 1);                 // Test 3
        assert(q.front() == "A");              // Test 4
        assert(q.back() == "A");               // Test 5
        test_counter += 4;

        q.push("B");
        assert(q.size() == 2);                 // Test 6
        assert(q.front() == "A");              // Test 7
        assert(q.back() == "B");               // Test 8
        test_counter += 3;

        q.pop();
        assert(q.size() == 1);                 // Test 9
        assert(q.front() == "B");              // Test 10
        assert(q.back() == "B");               // Test 11
        test_counter += 3;

        q.pop();
        assert(q.empty());                     // Test 12
        ++test_counter;
    }

    // ======================================================
    // 2. Initializer List
    // ======================================================
    {
        Queue<String> q = { "One", "Two", "Three" };
        assert(q.size() == 3);                 // Test 13
        assert(q.front() == "One");            // Test 14
        assert(q.back() == "Three");           // Test 15
        test_counter += 3;

        q.pop();
        assert(q.front() == "Two");            // Test 16
        ++test_counter;
    }

    // ======================================================
    // 3. Copy Semantics
    // ======================================================
    {
        Queue<String> q1;
        q1.push("X");
        q1.push("Y");

        // Copy constructor
        Queue<String> q2(q1);
        assert(q2.size() == 2);                // Test 17
        assert(q2.front() == "X");             // Test 18
        assert(q2.back() == "Y");              // Test 19
        test_counter += 3;

        // Modify original
        q1.pop();
        assert(q1.front() == "Y");             // Test 20
        assert(q2.front() == "X");             // Test 21
        test_counter += 2;

        // Copy assignment
        Queue<String> q3;
        q3 = q2;
        assert(q3.size() == 2);                // Test 22
        assert(q3.front() == "X");             // Test 23
        test_counter += 2;

        // Self-assignment
        q3 = q3;
        assert(q3.size() == 2);                // Test 24
        assert(q3.front() == "X");             // Test 25
        test_counter += 2;
    }

    // ======================================================
    // 4. Move Semantics
    // ======================================================
    {
        // Move constructor
        Queue<String> q1;
        q1.push("Move");

        Queue<String> q2(std::move(q1));
        assert(q2.size() == 1);                // Test 26
        assert(q2.front() == "Move");          // Test 27
        assert(q1.empty());                    // Test 28
        test_counter += 3;

        // Move assignment
        Queue<String> q3;
        q3 = std::move(q2);
        assert(q3.size() == 1);                // Test 29
        assert(q3.front() == "Move");          // Test 30
        assert(q2.empty());                    // Test 31
        test_counter += 3;

        // Move self-assignment
        q3 = std::move(q3);
        assert(q3.size() == 1);                // Test 32
        assert(q3.front() == "Move");          // Test 33
        test_counter += 2;
    }

    // ======================================================
    // 5. Capacity and Reservation
    // ======================================================
    {
        Queue<std::string> q;  
        assert(q.size() == 0);                 // Test 34
        ++test_counter;

        // Test initial capacity
        for (int i = 0; i < 10; ++i) {
            q.push(std::to_string(i));
        }
        assert(q.size() == 10);                // Test 35
        assert(q.front() == "0");              // Test 36
        test_counter += 2;

        // Trigger reallocation
        q.push("10");
        assert(q.size() == 11);                // Test 37
        assert(q.back() == "10");              // Test 38
        test_counter += 2;

        // Manual reservation
        Queue<std::string> q2;   
        q2.reserve(100);
        for (int i = 0; i < 100; ++i) {
            q2.push(std::to_string(i));
        }
        assert(q2.size() == 100);              // Test 39
        assert(q2.front() == "0");             // Test 40
        assert(q2.back() == "99");             // Test 41
        test_counter += 3;

        // Reserve smaller than current
        size_t prev_capacity = q2.size();
        q2.reserve(50);
        assert(q2.size() == 100);              // Test 42
        test_counter += 1;
    }

    // ======================================================
    // 6. Exception Handling
    // ======================================================
    {
        Queue<String> q;
        bool caught = false;

        // front() on empty
        try { q.front(); }
        catch (const std::out_of_range& e) {
            caught = true;
        }
        assert(caught);                        // Test 43
        ++test_counter;

        // back() on empty
        caught = false;
        try { q.back(); }
        catch (const std::out_of_range& e) {
            caught = true;
        }
        assert(caught);                        // Test 44
        ++test_counter;

        // pop() on empty
        caught = false;
        try { q.pop(); }
        catch (const std::out_of_range& e) {
            caught = true;
        }
        assert(caught);                        // Test 45
        ++test_counter;
    }

    // ======================================================
    // 7. Complex Operations and FIFO Property
    // ======================================================
    {
        Queue<std::string> q;
        const int N = 1000;

        // Fill the queue
        for (int i = 0; i < N; ++i) {
            q.push(std::to_string(i));
        }
        assert(q.size() == N);                 // Test 46
        ++test_counter;

        // Verify FIFO order
        for (int i = 0; i < N; ++i) {
            assert(q.front() == std::to_string(i));  // Test 47
            q.pop();
        }
        test_counter += 1;

        // Interleaved push/pop using only queues
        Queue<std::string> ref_queue;  // Reference queue for expected state
        int push_count = 0;

        for (int i = 0; i < 100; ++i) {
            if (i % 3 == 0 && !q.empty()) {
                // Remove from both queues
                q.pop();
                ref_queue.pop();
            }

            std::string val = "Val" + std::to_string(i);
            q.push(val);
            ref_queue.push(val);
            push_count++;

            // Verify sizes match
            assert(q.size() == ref_queue.size());  // Test 48

            // Verify front matches reference
            assert(q.front() == ref_queue.front());  // Test 49

            // Verify back matches reference
            assert(q.back() == ref_queue.back());    // Test 50
        }
        test_counter += 3;

        // Verify final state by comparing with reference queue
        assert(q.size() == push_count - (100 / 3));  // Test 51
        ++test_counter;

        // Verify full content
        while (!ref_queue.empty()) {
            assert(q.front() == ref_queue.front());  // Test 52
            q.pop();
            ref_queue.pop();
        }
        test_counter += 1;
    }
    // ======================================================
    // 8. Comparison Operators
    // ======================================================
    {
        Queue<String> q1 = { "A", "B", "C" };
        Queue<String> q2 = { "A", "B", "C" };
        Queue<String> q3 = { "X", "Y", "Z" };
        Queue<String> q4 = { "A", "B" };

        // Equality
        assert(q1 == q2);                      // Test 52
        ++test_counter;

        // Inequality
        assert(q1 != q3);                      // Test 53
        assert(q1 != q4);                      // Test 54
        test_counter += 2;

        // Empty queues
        Queue<String> q5;
        Queue<String> q6;
        assert(q5 == q6);                      // Test 55
        ++test_counter;

        // Modified copy
        q2.pop();
        assert(q1 != q2);                      // Test 56
        ++test_counter;
    }

    // ======================================================
    // 9. String Edge Cases
    // ======================================================
    {
        // Empty strings
        Queue<std::string> q1;   
        q1.push("");
        q1.push("");
        assert(q1.size() == 2);                // Test 57
        assert(q1.front() == "");              // Test 58
        assert(q1.back() == "");               // Test 59
        test_counter += 3;

        q1.pop();
        assert(q1.front() == "");              // Test 60
        ++test_counter;

        // Long strings
        std::string long_str(1000, 'X');
        Queue<std::string> q2;   
        q2.push(long_str);
        assert(q2.front() == long_str);        // Test 61
        ++test_counter;

        // Mixed content
        Queue<std::string> q3;   
        q3.push("123");
        q3.push("");
        q3.push(" ");
        q3.push("ABC");

        assert(q3.front() == "123");           // Test 62
        q3.pop();
        assert(q3.front() == "");              // Test 63
        q3.pop();
        assert(q3.front() == " ");             // Test 64
        q3.pop();
        assert(q3.front() == "ABC");           // Test 65
        test_counter += 4;
    }

    // ======================================================
    // 10. Stress Test
    // ======================================================
    {
        Queue<std::string> q;   
        const int N = 10000;

        for (int i = 0; i < N; ++i) {
            q.push(std::to_string(i));
        }
        assert(q.size() == N);                 // Test 66
        ++test_counter;

        for (int i = 0; i < N; ++i) {
            assert(q.front() == std::to_string(i));  // Test 67
            q.pop();
        }
        test_counter += 1;

        assert(q.empty());                     // Test 68
        ++test_counter;
    }

    std::cout << "=== All " << test_counter << " queue tests passed! ===\n";
}


void test_list_class() {
    std::cout << "\n=== List Class Test ===";
    int test_counter = 0;

    // ======================================================
    // 1. Constructors and basic operations (Tests 1-20)
    // ======================================================
    {
        // Tests for std::string
        List<String> str_list1;
        assert(str_list1.empty());                     // Test 1
        assert(str_list1.size() == 0);                // Test 2
        test_counter += 2;

        List<String> str_list2(5, "A");
        assert(str_list2.size() == 5);                // Test 3
        assert(str_list2[0] == "A");                  // Test 4
        assert(str_list2[4] == "A");                  // Test 5
        test_counter += 3;

        List<std::string> str_list3{ "A", "B", "C" };
        assert(str_list3.size() == 3);                // Test 6
        assert(str_list3[1] == "B");                  // Test 7
        test_counter += 2;

        // Tests for int
        List<int> int_list1;
        assert(int_list1.empty());                    // Test 8
        test_counter += 1;

        List<int> int_list2(10, 42);
        assert(int_list2.size() == 10);               // Test 9
        assert(int_list2[9] == 42);                  // Test 10
        test_counter += 2;

        List<int> int_list3{ 1, 2, 3, 4, 5 };
        assert(int_list3.size() == 5);                // Test 11
        assert(int_list3[0] == 1);                    // Test 12
        assert(int_list3[4] == 5);                    // Test 13
        test_counter += 3;

        // Copy verification
        List<std::string> str_list4 = str_list3;
        assert(str_list4.size() == 3);                // Test 14
        assert(str_list4[2] == "C");                  // Test 15
        test_counter += 2;

        List<int> int_list4 = int_list3;
        assert(int_list4.size() == 5);                // Test 16
        assert(int_list4[3] == 4);                    // Test 17
        test_counter += 2;

        // Move verification
        List<std::string> str_list5 = std::move(str_list4);
        assert(str_list5.size() == 3);                // Test 18
        assert(str_list4.empty());                    // Test 19
        test_counter += 2;

        List<int> int_list5 = std::move(int_list4);
        assert(int_list5.size() == 5);               // Test 20
        assert(int_list4.empty());                    // Test 21
        test_counter += 2;
    }

    // ======================================================
    // 2. Element addition operations (Tests 22-40)
    // ======================================================
    {
        // Tests for std::string
        List<String> str_list;
        str_list.push_back("A");
        assert(str_list.size() == 1);                 // Test 22
        assert(str_list[0] == "A");                   // Test 23
        test_counter += 2;

        str_list.push_front("B");
        assert(str_list.size() == 2);                 // Test 24
        assert(str_list[0] == "B");                   // Test 25
        test_counter += 2;

        str_list.push_back(std::move("C"));
        assert(str_list.size() == 3);                 // Test 26
        assert(str_list[2] == "C");                   // Test 27
        test_counter += 2;

        // Tests for int
        List<int> int_list;
        int_list.push_back(10);
        assert(int_list.size() == 1);                // Test 28
        assert(int_list[0] == 10);                   // Test 29
        test_counter += 2;

        int_list.push_front(20);
        assert(int_list.size() == 2);                 // Test 30
        assert(int_list[0] == 20);                    // Test 31
        test_counter += 2;

        int_list.push_back(30);
        assert(int_list.size() == 3);                 // Test 32
        assert(int_list[2] == 30);                    // Test 33
        test_counter += 2;

        // Middle insertion for std::string
        List<std::string> str_list2{ "A", "C" };
        auto it = str_list2.begin() + 1;
        str_list2.insert(it, "B");
        assert(str_list2.size() == 3);                // Test 34
        assert(str_list2[1] == "B");                  // Test 35
        test_counter += 2;

        // Middle insertion for int
        List<int> int_list2{ 1, 3 };
        auto it2 = int_list2.begin() + 1;
        int_list2.insert(it2, 2);
        assert(int_list2.size() == 3);                // Test 36
        assert(int_list2[1] == 2);                    // Test 37
        test_counter += 2;

        // Multiple element insertion
        List<int> int_list3{ 1, 5 };
        auto it3 = int_list3.begin() + 1;
        int_list3.insert(it3, 3, 3);
        assert(int_list3.size() == 5);                // Test 38
        assert(int_list3[2] == 3);                   // Test 39
        assert(int_list3[3] == 3);                   // Test 40
        test_counter += 3;
    }

    // ======================================================
    // 3. Element removal operations (Tests 41-60)
    // ======================================================
    {
        // Tests for std::string
        List<std::string> str_list{ "A", "B", "C" };
        str_list.pop_back();
        assert(str_list.size() == 2);                 // Test 41
        assert(str_list[1] == "B");                   // Test 42
        test_counter += 2;

        str_list.pop_front();
        assert(str_list.size() == 1);                 // Test 43
        assert(str_list[0] == "B");                   // Test 44
        test_counter += 2;

        // Tests for int
        List<int> int_list{ 1, 2, 3 };
        int_list.pop_back();
        assert(int_list.size() == 2);                 // Test 45
        assert(int_list[1] == 2);                     // Test 46
        test_counter += 2;

        int_list.pop_front();
        assert(int_list.size() == 1);                 // Test 47
        assert(int_list[0] == 2);                     // Test 48
        test_counter += 2;

        // Iterator-based removal for std::string
        List<std::string> str_list2{ "X", "Y", "Z" };
        auto it = str_list2.begin() + 1;
        it = str_list2.erase(it);
        assert(str_list2.size() == 2);                // Test 49
        assert(*it == "Z");                           // Test 50
        test_counter += 2;

        // Iterator-based removal for int
        List<int> int_list2{ 10, 20, 30 };
        auto it2 = int_list2.begin() + 1;
        it2 = int_list2.erase(it2);
        assert(int_list2.size() == 2);                // Test 51
        assert(*it2 == 30);                           // Test 52
        test_counter += 2;

        // List clearing
        List<int> int_list3{ 1, 2, 3 };
        int_list3.clear();
        assert(int_list3.empty());                    // Test 53
        test_counter += 1;

        // Exceptions on empty list
        List<std::string> empty_list;
        bool exception_thrown = false;
        try { empty_list.pop_back(); }
        catch (...) { exception_thrown = true; }
        assert(exception_thrown);                     // Test 54
        test_counter += 1;

        exception_thrown = false;
        try { empty_list.pop_front(); }
        catch (...) { exception_thrown = true; }
        assert(exception_thrown);                     // Test 55
        test_counter += 1;

        // Removing elements one by one
        List<int> int_list4{ 1, 2, 3 };
        int_list4.pop_back();
        int_list4.pop_back();
        int_list4.pop_back();
        assert(int_list4.empty());                    // Test 56
        test_counter += 1;

        // Removing non-existent iterator
        List<String> str_list3{ "A" };
        auto it3 = str_list3.end();
        exception_thrown = false;
        try { str_list3.erase(it3); }
        catch (...) { exception_thrown = true; }
        assert(exception_thrown);                    // Test 57
        test_counter += 1;

        // Removal followed by addition
        List<int> int_list5{ 1 };
        int_list5.pop_back();
        int_list5.push_back(2);
        assert(int_list5.size() == 1);               // Test 58
        assert(int_list5[0] == 2);                  // Test 59
        test_counter += 2;

        // Multiple removal/addition
        List<std::string> str_list4;
        for (int i = 0; i < 10; i++) {
            str_list4.push_back("X");
            str_list4.pop_back();
        }
        assert(str_list4.empty());                   // Test 60
        test_counter += 1;
    }

    // ======================================================
    // 4. Iterator operations (Tests 61-80)
    // ======================================================
    {
        // Basic iterator operations for std::string
        List<std::string> str_list{ "A", "B", "C" };
        auto it1 = str_list.begin();
        assert(*it1 == "A");                        // Test 61
        ++it1;
        assert(*it1 == "B");                         // Test 62
        test_counter += 2;

        // Basic iterator operations for int
        List<int> int_list{ 1, 2, 3 };
        auto it2 = int_list.begin();
        assert(*it2 == 1);                           // Test 63
        ++it2;
        assert(*it2 == 2);                           // Test 64
        test_counter += 2;

        // List traversal
        auto it3 = str_list.begin();
        it3 += 2;
        assert(*it3 == "C");                         // Test 65
        --it3;
        assert(*it3 == "B");                         // Test 66
        test_counter += 2;

        // Iterator comparison
        auto it4 = int_list.begin();
        auto it5 = int_list.begin();
        assert(it4 == it5);                          // Test 67
        ++it5;
        assert(it4 != it5);                          // Test 68
        test_counter += 2;

        // Constant iterators
        List<String> const_list{ "X", "Y", "Z" };
        auto cit = const_list.begin();
        assert(*cit == "X");                         // Test 69
        test_counter += 1;

        // end() iterator
        auto it6 = str_list.end();
        assert(!it6.is_valid());                     // Test 70
        test_counter += 1;

        // Iterator arithmetic
        List<int> long_list{ 0, 1, 2, 3, 4, 5 };
        auto it7 = long_list.begin() + 3;
        assert(*it7 == 3);                           // Test 71
        it7 = it7 - 2;
        assert(*it7 == 1);                           // Test 72
        test_counter += 2;

        // Iterator invalidation check
        List<std::string> str_list2{ "A", "B", "C" };
        auto it8 = str_list2.begin() + 1;
        str_list2.erase(str_list2.begin());
        assert(*it8 == "B");                         // Test 73
        str_list2.insert(str_list2.begin(), "X");
        assert(*it8 == "B");                         // Test 74
        test_counter += 2;

        // Iterators on empty list
        List<int> empty_list;
        assert(empty_list.begin() == empty_list.end()); // Test 75
        test_counter += 1;

        // Reverse traversal
        List<int> rev_list{ 1, 2, 3 };
        auto rit = rev_list.end() - 1;
        assert(*rit == 3);                           // Test 76
        --rit;
        assert(*rit == 2);                           // Test 77
        test_counter += 2;

        // += and -= operators check
        List<std::string> str_list3{ "A", "B", "C", "D" };
        auto it9 = str_list3.begin();
        it9 += 2;
        assert(*it9 == "C");                        // Test 78
        it9 -= 1;
        assert(*it9 == "B");                        // Test 79
        test_counter += 2;

        // Edge cases for iterators
        List<int> single_list{ 42 };
        auto it10 = single_list.begin();
        ++it10;
        assert(it10 == single_list.end());          // Test 80
        test_counter += 1;
    }

    // ======================================================
    // 5. Assignment operator tests (Tests 81-100)
    // ======================================================
    {
        // Copy assignment for int
        List<int> int_list1{ 1, 2, 3 };
        List<int> int_list2;
        int_list2 = int_list1;
        assert(int_list2.size() == 3);              // Test 81
        assert(int_list2[0] == 1);                 // Test 82
        test_counter += 2;

        // Copy assignment for std::string
        List<String> str_list1{ "A", "B", "C" };
        List<String> str_list2;
        str_list2 = str_list1;
        assert(str_list2.size() == 3);              // Test 83
        assert(str_list2[2] == "C");               // Test 84
        test_counter += 2;

        // Move assignment for int
        List<int> int_list3{ 4, 5, 6 };
        List<int> int_list4;
        int_list4 = std::move(int_list3);
        assert(int_list4.size() == 3);              // Test 85
        assert(int_list3.empty());                  // Test 86
        test_counter += 2;

        // Move assignment for std::string
        List<std::string> str_list3{ "X", "Y", "Z" };
        List<std::string> str_list4;
        str_list4 = std::move(str_list3);
        assert(str_list4.size() == 3);              // Test 87
        assert(str_list3.empty());                  // Test 88
        test_counter += 2;

        // Self-assignment (copy)
        List<int> int_list5{ 7, 8, 9 };
        int_list5 = int_list5;
        assert(int_list5.size() == 3);              // Test 89
        assert(int_list5[1] == 8);                  // Test 90
        test_counter += 2;

        // Self-assignment (move)
        List<std::string> str_list5{ "Self" };
        str_list5 = std::move(str_list5);
        assert(str_list5.size() == 1);              // Test 91
        assert(str_list5[0] == "Self");             // Test 92
        test_counter += 2;

        // Overlapping assignment
        List<int> int_list6{ 10, 20 };
        List<int> int_list7{ 30, 40 };
        int_list6 = int_list7;
        assert(int_list6.size() == 2);              // Test 93
        assert(int_list6[1] == 40);                 // Test 94
        test_counter += 2;

        // Assigning empty list
        List<std::string> empty_list1;
        List<std::string> empty_list2{ "A", "B" };
        empty_list2 = empty_list1;
        assert(empty_list2.empty());                // Test 95
        test_counter += 1;

        // Moving to non-empty list
        List<int> int_list8{ 1, 2 };
        List<int> int_list9{ 3, 4, 5 };
        int_list8 = std::move(int_list9);
        assert(int_list8.size() == 3);              // Test 96
        assert(int_list9.empty());                  // Test 97
        test_counter += 2;
    }

    // ======================================================
    // 6. Additional functionality tests (Tests 98-100)
    // ======================================================
    {
        // clear() method test
        List<int> clear_list{ 1, 2, 3 };
        clear_list.clear();
        assert(clear_list.empty());                 // Test 98
        assert(clear_list.size() == 0);             // Test 99
        test_counter += 2;

        // empty() method test
        List<std::string> empty_test;
        assert(empty_test.empty());                 // Test 100
        test_counter += 1;
    }

    // ======================================================
    // 7. Complex scenario tests (Tests 101-110)
    // ======================================================
    {
        // Combined test: all operations
        List<int> complex_list;
        assert(complex_list.empty());               // Test 101
        test_counter += 1;

        complex_list.push_back(1);
        complex_list.push_front(2);
        assert(complex_list.size() == 2);           // Test 102
        test_counter += 1;

        complex_list.insert(complex_list.begin() + 1, 3);
        assert(complex_list[1] == 3);               // Test 103
        test_counter += 1;

        complex_list.erase(complex_list.begin());
        assert(complex_list[0] == 3);               // Test 104
        test_counter += 1;

        complex_list.reverse();
        assert(complex_list[0] == 1);               // Test 105
        test_counter += 1;

        complex_list.push_back(1);
        complex_list.unique();
        assert(complex_list.size() == 2);           // Test 106
        test_counter += 1;

        List<int> complex_copy = complex_list;
        assert(complex_copy.size() == 2);           // Test 107
        test_counter += 1;

        List<int> complex_move = std::move(complex_copy);
        assert(complex_move.size() == 2);           // Test 108
        assert(complex_copy.empty());               // Test 109
        test_counter += 2;

        complex_move.clear();
        assert(complex_move.empty());               // Test 110
        test_counter += 1;
    }

    std::cout << "\n=== All " << test_counter << " list tests passed! ===\n";
}


void start_all_tests() {
    test_vector_class();
    test_string_class();
    test_stack_class();
    test_queue_class();
    test_list_class();
}

int main() {
    //TO DO MORE TEST FOR VECTOR, STACK, STRING
    start_all_tests();
    return 0;
}
