# Heap

A C++ console application implementing a dynamic **max/min heap** data structure for string values, with support for switching between heap modes at runtime.

## Tech Stack

- **Language:** C++
- **Standard Library:** `<iostream>`, `<string>`
- **Build System:** Microsoft Visual Studio (`.sln` / `.vcxproj` project files)
- **Platform:** Windows (Visual Studio solution), but the source is portable C++

## Architecture

The project consists of a single source file (`Heap.cpp`) with the following components:

| Component | Description |
|---|---|
| `StrGt(l, r)` | String comparator — compares strings first by length, then lexicographically |
| `Swap(arr, i1, i2)` | Swaps two elements in the array |
| `MaxHeapify` / `MinHeapify` | Recursive heapify procedures that restore the heap property downwards |
| `MaxHeap` / `MinHeap` | Build a full max or min heap from an unsorted array (bottom-up) |
| `CreateHeap` | Dispatcher that calls `MaxHeap` or `MinHeap` based on the current `HeapMode` |
| `ExpandArray` | Dynamically grows the heap array by one element |
| `DelFirst` | Removes the root (max or min) and shrinks the array |
| `PrintArray` | Prints all heap elements in their internal array order |
| `main` | REPL loop — reads single-character commands and dispatches to the functions above |

The heap is stored as a **flat dynamic array** (`string*`) and rebuilt from scratch after every insertion, deletion, or mode switch. The ordering key is string length (longer = greater), with lexicographic tiebreaking.

## Ordering Rule

Strings are compared by **length first**:
- Longer string → greater
- Equal length → standard lexicographic comparison (character by character)
- If both children have equal values, the **left child** (lower index) is swapped with the parent.

## How to Use

### Build

Open `Heap.sln` in **Visual Studio** and build the project (`Ctrl+Shift+B`), or compile from the command line:

```sh
cl Heap.cpp /EHsc /Fe:heap.exe
```

### Run

```sh
heap.exe
```

The program reads commands from standard input until `q` is entered.

### Commands

| Command | Description |
|---|---|
| `+ v` | Add string `v` to the heap |
| `-` | Remove and print the root element (max in MAX mode, min in MIN mode) |
| `p` | Print all heap elements in their internal array order |
| `r n v1 v2 … vn` | Reset the heap with `n` new elements `v1 … vn` |
| `s` | Toggle heap mode between MAX and MIN (rebuilds the heap) |
| `q` | Quit the program |

> **Note:** `r` is not equivalent to a sequence of `+` operations — it resets the heap entirely before inserting the new elements.

### Example Session

**Input:**
```
+ 1
+ 2
+ 3
p
-
s
p
q
```

**Output:**
```
3 2 1 
3
1 2 
```

A full worked example with 8 elements is provided in [`Heap.txt`](Heap.txt).
