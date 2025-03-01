# Benchmarking for Quantifier Elimination over the Integers

This directory contains benchmarking scripts and input files designed to assess the performance of quantifier elimination methods implemented within the **PolyhedralSets** library.

---

## 📂 Directory Structure
```
Benchmarks/
│── Input/                      # Directory containing input test cases
│── benchmarking.tst            # Maple script utilized for executing tests
│── test-harness.tst            # Tests in Maple format
│── Makefile                    # Automation script for executing benchmarks
│── results_*.output            # Files containing raw execution results
│── BENCHMARKING_results_*.output  # Files containing filtered benchmark-specific results
│── crash_log.txt               # Log file capturing errors encountered during execution
```
---

## 🔍 Methods and Modes
The benchmarking process evaluates two quantifier elimination methods:
- **numberofintegerpoints (NIP)**
- **integerpointdecomposition (IPD)**

Each method operates in two distinct modes:
- `onequantifieratatime` → Processes each quantifier individually.
- `byblockofquantifiers` → Processes quantifiers in grouped blocks.

---

## 🚀 Executing Benchmarks
The benchmarking process is automated using the provided `Makefile` and **Maple**. 

To execute all benchmarks, run:
```sh
make all
```
Alternatively, specific tests can be executed as follows:
```sh
make test_NIP_one      # Executes NIP method with onequantifieratatime mode
make test_NIP_block    # Executes NIP method with byblockofquantifiers mode
make test_IPD_one      # Executes IPD method with onequantifieratatime mode
make test_IPD_block    # Executes IPD method with byblockofquantifiers mode
```

---

## 📊 Output Files
Results from the benchmarking process are stored in the following files:

### 📝 Raw Execution Results
- `results_NIP_one.output` → **NIP (onequantifieratatime)**
- `results_NIP_block.output` → **NIP (byblockofquantifiers)**
- `results_IPD_one.output` → **IPD (onequantifieratatime)**
- `results_IPD_block.output` → **IPD (byblockofquantifiers)**

### 📈 Filtered Benchmark Results
- `BENCHMARKING_results_NIP_one.output`
- `BENCHMARKING_results_NIP_block.output`
- `BENCHMARKING_results_IPD_one.output`
- `BENCHMARKING_results_IPD_block.output`

---

## ⚠️ Error Handling
If errors occur during execution, they will be logged in `crash_log.txt`, including:
- The input file that triggered the error
- The method and mode used during execution
- The corresponding error message from Maple

---

## 🛠 Cleanup Procedure
To remove all generated output files and logs, execute:
```sh
make clean
```