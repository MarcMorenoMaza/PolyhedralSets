# Benchmarking for PIP to QE

This directory contains benchmarking scripts and input files designed to assess the performance of our **PIP (Parametric Integer Programming)** approach implemented within the **PolyhedralSets** library.

---

## 📂 Directory Structure

```
PIP_to_QE/
│── SamplePoint/                    # Maple scripts for the sample point variant
│── Locus/                          # Maple scripts for the locus variant
│── Makefile                        # Automation script for executing benchmarks
```

---

## 🔍 Methods and Modes

The benchmarking process evaluates two external quantifier elimination methods alongside our approach:

- **Feautrier** — Feautrier's parametric integer programming method
- **Barvinok** — Barvinok's rational generating function approach

Our approach operates in two variants:

- `SamplePoint` → Returns concrete sample points that achieve the optimum
- `Locus` → Returns the parametric conditions (in terms of free parameters) under which the optimum exists, along with the optimal value

---

## 🚀 Executing Benchmarks

To execute all benchmarks, run:

```sh
make samplePoint
make locus
```

---

## 📊 Results

Timings are reported in **seconds**.

Special values:
- `error` — the method encountered an internal error on this instance
- `Not supported` — the method does not handle this class of problem
- `> 30 mins` — computation exceeded the 30-minute time limit
- `NA (QE)` — instance requires quantifier elimination outside the method's scope
- `(ILP)` — instance was solved via an ILP sub-procedure

| Objective Function | Feautrier | Barvinok      | Our Code (Sample Point) | Our Code (Locus) |
|--------------------|-----------|---------------|-------------------------|------------------|
| boulet             | 0.032     | 0.021         | 2.514                   | 2.493            |
| bouleti            | 0.039     | error         | 13.069                  | 12.795           |
| cg1                | 0.024     | 0.027         | 1.205                   | 1.167            |
| cnt_sum2           | 1.114     | Not supported | > 30 mins               | > 30 mins        |
| difficult          | 0.079     | 0.555         | 1136.988                | 1133.288         |
| esced              | 0.051     | 0.026         | 394.609                 | 390.996          |
| ex                 | 0.027     | 0.030         | 0.900                   | 0.900            |
| ex2                | 0.027     | 0.030         | 0.907                   | 0.900            |
| fimmel             | 0.038     | 0.038         | 0.644                   | 0.640            |
| jcomplex           | 583.280   | Not supported | > 30 mins               | > 30 mins        |
| max                | 0.026     | 0.030         | 1.437                   | 1.397            |
| negative           | 0.021     | 0.028         | 0.521                   | 0.521            |
| phideo             | 0.764     | > 30 mins     | > 30 mins               | > 30 mins        |
| seghir-e1          | 0.068     | error         | 1278.216                | 1265.387         |
| seghir-e3          | 0.031     | 0.067         | 73.585                  | 73.353           |
| seghir-e4          | 0.045     | 11.675        | > 30 mins               | > 30 mins        |
| seghir-e5          | 0.147     | 2.533         | > 30 mins               | > 30 mins        |
| seghir-e6          | 0.045     | 0.366         | 447.975                 | 445.734          |
| seghir-e7          | 0.029     | 0.111         | 55.668                  | 55.795           |
| seghir-e8          | 0.031     | 0.075         | 925.595                 | 903.961          |
| seghir-e9          | 0.332     | > 30 mins     | > 30 mins               | > 30 mins        |
| small              | 0.018     | 0.026         | 1.209 (ILP)             | 1.200 (ILP)      |
| sor1d              | 0.024     | 0.022         | 0.455                   | 0.453            |
| square             | 0.027     | 0.029         | 0.916                   | 0.958            |
| sven               | 0.024     | 0.019         | 0.228                   | 0.278            |
| tobi               | 0.026     | 0.025         | 45.504                  | 45.355           |
