# 🌿 Mini MATLAB Compiler

A lightweight, educational compiler that walks through **all five classical compilation stages** —
from raw expression input to **optimized intermediate code**.
It’s written in Python, clean, procedural (non-OOP), and designed for clarity and learning.

---

## 🧩 Overview

This project simulates the main phases of a **compiler** using a small, MATLAB-like language syntax.
Each expression you type passes through:

1. **Lexical Analysis (Lexer)** — breaks input into tokens.
2. **Syntax Analysis (Parser)** — checks the structure and builds a parse tree.
3. **Semantic Analysis** — ensures type correctness and data flow.
4. **Intermediate Code Generation** — translates logic into temporary variable code.
5. **Optimization** — simplifies redundant operations (like `x * 1`, `+ 0`, or constant folding).

---

## ⚙️ Project Structure

```
mini_matlab/
│
├── src/
│   ├── main.py            # Main entry point
│   ├── lexer.py           # Lexical analyzer
│   ├── parser.py          # Syntax analyzer
│   ├── semantic.py        # Semantic analyzer
│   ├── intermediate.py    # Intermediate code generator
│   └── optimizer.py       # Optimizer
│
├── tests/
│   ├── test_lexer.py
│   ├── test_parser.py
│   ├── test_semantic.py
│   ├── test_intermediate.py
│   └── test_optimizer.py
│
└── README.md
```

---

## 🚀 How to Run

### 🧠 1. Run from Command Line

To execute the full compilation pipeline:

```bash
python src/main.py
```

Then type any mathematical expression, for example:

```
(3 + 4) * 2
```

The program will sequentially perform all 5 stages and display results of each.

---

## 🧮 Example Output

```
Input:
Area := Pos + Rate * 50
```

```
[LEXICAL ANALYSIS]
id1 = id2 + id3 * 50
```

```
[SYNTAX ANALYSIS]
           (+)
          /   \
       id2     (*)
              /   \
            id3    50
```

```
[SEMANTIC ANALYSIS]
           (+)
          /   \
       id2     (*)
              /   \
            id3    IntoReal(50)
```

```
[INTERMEDIATE CODE]
t1 = IntoReal 50
t2 = id3 * t1
t3 = id2 + t2
id1 = t3
```

```
[OPTIMIZED CODE]
t2 = id3 * 50.0
id1 = id2 + t2
```
---

## 🧭 Philosophy

> “A compiler is not just a translator,
> it’s a storyteller that turns logic into order.”

This project isn’t about parsing massive programs —
it’s about **understanding the transformation of thought into computation**.

---

## 🧪 Tests

To run the test suite:

```bash
python -m pytest tests/
```

or run an individual test:

```bash
python -m tests.test_optimizer
```

---

## 💡 Future Ideas

* Add support for `^` (power), `√` (square root), `/` (division), and `-` (subtraction).
* Visual parse tree rendering.
* A REPL mode for continuous input.
* Logging and configuration file (`config.py`).

---

## Author

**Shakiba and Mitra** — students.

---
