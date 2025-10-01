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

## Exercise 01 — (to be completed)

### Description
_(Reserved for the next exercise. Fill in after reading the subject.)_

### Requirements
- Language: C++98
- Container used: _(choose one not used before)_
- Compile flags: `-Wall -Wextra -Werror -std=c++98`

### Logic
_(To be defined)_

### Example
_(To be defined)_

---

## Exercise 02 — (to be completed)

### Description
_(Reserved for the third exercise. This one requires **two** different containers.)_

### Requirements
- Language: C++98
- Containers used: _(two containers not used before)_
- Compile flags: `-Wall -Wextra -Werror -std=c++98`

### Logic
_(To be defined)_

### Example
_(To be defined)_

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