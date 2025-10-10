# 42 C++ Module 09

This module contains **three exercises** focusing on STL containers, algorithmic complexity, and data manipulation using C++98.

Each exercise must use **different STL containers** according to the subject's rules:
- You must use at least one container per exercise (except ex02, which requires two).
- Once a container is used in one exercise, it **cannot** be reused in the others.

---

## Exercise 00 — Bitcoin Exchange

### Description
Create a program that, given a historical database of Bitcoin prices, computes the value of a given amount of Bitcoin on a specific date.

### Requirements
- Language: C++98
- Container used: `std::map`
- Compile flags: `-Wall -Wextra -Werror -std=c++98`
- Handle all possible errors gracefully.

### Logic
1. Load the CSV database into a `std::map<std::string, double>`.
2. Read the input file line by line.
3. Validate dates and values.
4. For each line, find the correct exchange rate:
   - If the date exists → use it.
   - If not → use the closest **previous** date.
5. Print `date => value = value * rate`.
6. Handle invalid input with descriptive errors.

### Example
```
$ ./btc input.txt
2011-01-03 => 3 = 0.9
2011-01-09 => 1 = 0.32
Error: not a positive number.
Error: bad input => 2001-42-42
Error: too large a number.
```

---

## Exercise 01 — RPN (Reverse Polish Notation)

### Description
Create a program that evaluates a mathematical expression written in **Reverse Polish Notation (RPN)**.  
The program receives the expression as a **single command-line argument**, processes it using a stack, and prints the result.

### Requirements
- Language: **C++98**
- **Container used:** `std::stack<long long>` (adaptor; uses `std::deque` by default)
- Compile flags: `-Wall -Wextra -Werror -std=c++98`
- Input constraints:
  - Tokens are separated by spaces.
  - Operands are **single-digit integers** (`0..9`). *(Only the inputs are constrained; intermediate and final results are not.)*
  - Supported operators: `+`, `-`, `*`, `/`
  - No parentheses and no decimal numbers.
- Output:
  - On success: print the numeric result to **stdout**.
  - On error (invalid token, not enough operands, division by zero, malformed expression, wrong number of args): print **`Error`** to **stderr** and exit with non-zero status.

### Logic
1. Parse the input string from left to right, splitting by whitespace.
2. For each token:
   - If it’s a digit `0..9`, push its value onto the stack.
   - If it’s an operator, pop two operands (`b` then `a`), compute `a op b`, and push the result.
   - Otherwise, throw an error.
3. At the end, the stack must contain **exactly one** value → that’s the result; otherwise, **error**.
4. Division is **integer division**; division by zero triggers an **error**.

### Example
```
$> ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
42
$> ./RPN "7 7 * 7 -"
42
$> ./RPN "1 2 * 2 / 2 * 2 4 - +"
0
$> ./RPN "(1 + 1)"
Error
```

---

## Exercise 02 — PmergeMe (Merge-Insertion Sort)

### Description
Create a program named **`PmergeMe`** that sorts a sequence of **positive integers** passed as command-line arguments using the **Ford–Johnson merge-insertion sort** algorithm (also known as *merge-insert sort*).  
The program must implement the algorithm **separately** for **two different STL containers** and compare their execution times.

### Requirements
- Language: **C++98**
- Executable name: `PmergeMe`
- Files to turn in: `Makefile`, `main.cpp`, `PmergeMe.{hpp,cpp}`
- **Containers used:** `std::vector` and `std::list` *(do not reuse containers already used in previous exercises)*
- Compile flags: `-Wall -Wextra -Werror -std=c++98`
- Input:
  - Program takes a sequence of **positive integers** as command-line arguments.
  - Any non-numeric, negative, or out-of-range value must print **`Error`** to `stderr`.
  - **Duplicates:** at your discretion (allowed or rejected). If rejected, print **`Error`**.
- Output:
  - Line 1: `Before:` followed by the unsorted sequence.
  - Line 2: `After:` followed by the sorted sequence.
  - Line 3: execution time for the first container (vector).
  - Line 4: execution time for the second container (list).
- Performance:
  - Must handle at least **3000 integers**.
- Errors:
  - On any invalid input or runtime error, print **`Error`** to `stderr` and exit with a non-zero status.

### Logic
1. **Parse & validate input** — store the original sequence.
2. **Print “Before”** — show the unsorted sequence.
3. **Vector path**
   1. Copy the data into a `std::vector`.
   2. Form adjacent **pairs**; for each pair place the smaller in `smalls` and the larger in `bigs`.  
      - If the input size is odd, the last element goes to `bigs`.
   3. Sort `bigs` with `std::sort()`.
   4. Insert each element from `smalls` into `bigs` using **binary search** (`std::lower_bound`) + `insert()`.
   5. Save the merged result as the vector output; **print “After”**.
4. **List path**
   1. Copy the data into a `std::list`.
   2. Repeat the same steps adapted to list iterators:
      - Pair & split into `smalls` and `bigs`.
      - Sort `bigs` with `list::sort()`.
      - Insert `smalls` into `bigs` using `std::lower_bound` (valid on bidirectional iterators) or a linear scan.
   3. Save the merged result as the list output.
5. **Timing**
   - Measure the execution time of each path (include all operations: pairing, sorting, inserting).
   - Tip (C++98): use `gettimeofday()` and display **microseconds**.

> *Note:* The original Ford–Johnson algorithm defines an optimal insertion order using the **Jacobsthal sequence**. Implementing this optimisation is **optional** here; a straightforward approach (*pair → sort bigs → binary-insert smalls*) fully satisfies the subject.

### Example
```
$> ./PmergeMe 3 5 9 7 4
Before: 3 5 9 7 4
After: 3 4 5 7 9
Time to process a range of 5 elements with std::vector : 0.31 us
Time to process a range of 5 elements with std::list : 0.58 us

$> ./PmergeMe shuf -i 1-100000 -n 3000 | tr "\n" " "
Before: 141 79 526 321 [...]
After: 79 141 321 526 [...]
Time to process a range of 3000 elements with std::vector : 62.14 us
Time to process a range of 3000 elements with std::list : 69.27 us

$> ./PmergeMe "-1" "2"
Error
```

---

## Compilation
```
make
```

## Execution
```
./<program_name> <input_file>
```

## Cleaning
```
make clean    # remove object files
make fclean   # remove executable
make re       # rebuild everything
```

---

## References
- [C++ Reference – std::map](https://cplusplus.com/reference/map/map/)
- [STL Containers Overview](https://cplusplus.com/reference/stl/)
- [42 School C++ Modules](https://github.com/42School)