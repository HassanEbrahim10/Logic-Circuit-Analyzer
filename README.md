# 🔷 Digital Logic Circuit Analyzer & Simplifier (C++)

## 📌 Project Overview

This project is a complete Digital Logic Circuit Analyzer implemented in C++.

It was developed for Discrete Mathematics / Digital Logic Design to:

- Analyze Boolean expressions
- Generate full truth tables
- Detect logical properties (Tautology / Contradiction / Satisfiable)
- Check equivalence between expressions
- Simplify Boolean expressions programmatically

The project combines theoretical Boolean algebra with practical algorithm implementation.

---

# 🎯 Project Objectives

Given a digital logic circuit:

1. Simplify the Boolean expression analytically.
2. Generate the truth table of the original expression.
3. Generate the truth table of the simplified expression.
4. Check if both expressions are equivalent.
5. Determine whether the circuit is:
   - Tautology
   - Contradiction
   - Satisfiable

---

# 🏗 System Features

## 1️⃣ Circuit Input

The system supports:

### 🔹 Equation Mode
User directly enters a Boolean expression.

Supported operators:
- `&` → AND
- `|` → OR
- `~` → NOT
- Parentheses `()`

Example:
↪ F = ~( ((A ∧ B) ∧ C) ∧ ((A ∧ B) ∧ ~C) )

---

## 2️⃣ Truth Table Generation

The program:

- Extracts all unique variables automatically
- Calculates number of rows: Rows = 2^n

  
Where `n` is number of inputs.

- Generates all binary combinations
- Evaluates the expression for each row
- Stores results in a 2D vector
- Prints formatted truth table

---

## 3️⃣ Logical Classification

After building the truth table, the system checks:

### ✔ Tautology
If all outputs = 1

### ❌ Contradiction
If all outputs = 0

### ⚖ Satisfiable
If at least one output = 1

---

## 4️⃣ Circuit Equivalence

To verify simplification:

- Generate truth table for original expression
- Generate truth table for simplified expression
- Compare final output columns
- If identical → Equivalent
- Otherwise → Not Equivalent

---

# 🔬 Boolean Simplification Method

The simplification module is inspired by the **Quine–McCluskey algorithm**.

### Steps Used:

1. Extract minterms (rows where output = 1)
2. Convert minterms to binary representation
3. Merge terms that differ in one bit
4. Replace differing bit with '-' (Don't Care)
5. Extract Prime Implicants
6. Construct minimized Boolean expression

This method is the algorithmic alternative to Karnaugh Maps and is suitable for programmatic implementation.

---

# 📌 Case Study: Given Circuit

## Original Expression

F = ~( ((A ∧ B) ∧ C) ∧ ((A ∧ B) ∧ ~C) )

---

# 🧠 Analytical Simplification

### Step 1: Expand

F = ~( ((A ∧ B) ∧ C) ∧ ((A ∧ B) ∧ ~C) )

---

### Step 2: Apply Associative Law

F = ~( (A ∧ B) ∧ C ∧ (A ∧ B) ∧ ~C )

---

### Step 3: Apply Idempotent Law

(A ∧ B) ∧ (A ∧ B) = (A ∧ B)

So:

F = ~( (A ∧ B) ∧ (C ∧ ~C) )

---

### Step 4: Apply Contradiction Law

C ∧ ~C = c "Contradiction"

Thus:

F = ~( (A ∧ B) ∧ c )


---

### Step 5: Apply Universal bound low  
(A ∧ B) ∧ c = c 


So:

F = ~c = t = t "Tautology"

---

# ✅ Final Simplified Expression

F = t

---

# 📊 Truth Table Verification

| A | B | C | F |
|---|---|---|---|
| 0 | 0 | 0 | 1 |
| 0 | 0 | 1 | 1 |
| 0 | 1 | 0 | 1 |
| 0 | 1 | 1 | 1 |
| 1 | 0 | 0 | 1 |
| 1 | 0 | 1 | 1 |
| 1 | 1 | 0 | 1 |
| 1 | 1 | 1 | 1 |

Since all outputs are 1:

### ✔ The circuit is a TAUTOLOGY.

---

# 🏗 Code Architecture

Main components:

- Variable extraction module
- Stack-based Boolean evaluator
- Truth table generator
- Logical analyzer
- Simplification engine
- Equivalence checker

Techniques used:

- Recursion
- Bitwise operations
- Stack data structure
- 2D vectors
- Binary manipulation

---

# ▶ How to Compile & Run

### Compile:
g++ logic_analyzer.cpp -o logic

### Run:
./logic

---

# 📚 Learning Outcomes

Through this project, I gained strong understanding of:

- Boolean algebra laws
- Digital circuit analysis
- Logical equivalence
- Algorithmic simplification
- Translating mathematical logic into C++ code
- Structured program design

---

# 🚀 Future Improvements

- Full Quine–McCluskey with essential prime implicants
- Karnaugh Map visualization
- Object-Oriented refactoring
- GUI version
- Performance optimization
- Unit testing support

---

# 👨‍💻 Author

Hassan Ebrahim  
Engineering Student  
Digital Logic & Discrete Mathematics  

---

# 📌 Academic Context

Developed for:
PHM311s – Discrete Mathematics  
Topic: Digital Logic Circuit Simplification



