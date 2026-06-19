# Engineering calculator

[Русская версия](README.ru.md)

A desktop application for evaluating mathematical expressions and plotting functions, built with **C++ and Qt Widgets**. The lexer and recursive-descent parser are written from scratch — no third-party math libraries used.

**Demo:**

https://github.com/user-attachments/assets/aee98f97-b4c2-4092-8a55-64f9c78875ae

---

## Features

- Arithmetic expression evaluation with correct operator precedence
- Scientific functions: `sin`, `cos`, `tan`, `log`, `ln`, `sqrt`, `!`
- Detects the variable `x` and automatically renders the function graph
- History of evaluated expressions accessible from the menu bar

---

## Lexer & Parser

The expression string is processed in two stages.

**Lexer** scans the input and produces a flat sequence of typed tokens — numbers, operators, function names, parentheses, and the variable `x`.

**Parser** consumes the token stream using a recursive-descent algorithm where each grammar rule maps to a dedicated function:

```
expression  →  term  (('+' | '-')  term)*
term        →  factor  (('*' | '/')  factor)*
factor      →  number | variable | '(' expression ')' | func '(' expression ')' | '-' factor | factor '!'
```

---

## Stack

- **C++17**
- **Qt 6**
- **QCustomPlot** — graph rendering
- **qmake**

MVC pattern: `MainWindow` — view, `Controller` — expression routing, `Core` + `ParserMath` — model.

---

## Build

```bash
git clone https://github.com/Pavel-Sedlovec/engineering-calculator.git
cd engineering-calculator
qmake calculator.pro
make -j$(nproc)
./calculator
```

## License

Application source — MIT. QCustomPlot — GNU LGPL v2.1.
