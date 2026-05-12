# ExtendedConvexHull

The ExtendedConvexHull package is written in [Maple](https://www.maplesoft.com/) and is designed to compute the extended convex hull of a given polyhedral set.

---

## 📂 Directory Structure

```
ExtendedConvexHull/
│── ECH.mw                          # Maple worksheet containing the ECH implementation and examples
│── master.mla                      # Compiled Maple library archive
```

---

## 🔧 Installation Guide

This package can be installed as follows:

1. Clone or Download this repository (i.e. `git clone https://github.com/MarcMorenoMaza/PolyhedralSets.git`)
2. Navigate to the repository folder (i.e. `cd PolyhedralSets/ExtendedConvexHull`)
3. Copy the full path of `master.mla` by running `pwd`
4. Edit your Maple initialization file `~/.mapleinit` using `libname := "<path>", libname:`

After successful installation `master.mla` will be integrated into your Maple environment.  
Note that `<path>` should be replaced with the full path to where `master.mla` is located.

---

## 💻 Code Demo

The Maple worksheet [ECH.mw](https://github.com/MarcMorenoMaza/PolyhedralSets/blob/main/ExtendedConvexHull/ECH.mw) is a demo of this package.

In addition to installing the package, you also need to have Maple installed to view the demo. You can download Maple from their [official website](https://www.maplesoft.com/).

---

## 📖 Usage and Documentation

This package can be loaded in Maple by using `with(IntegralPolyhedra);`. This command also displays all available functions.

Our main command is `ExtendedConvexHull([P1, ..., Pn])`, which takes a list of polyhedral sets `P1, ..., Pn` and returns two outputs:

- **Plot** — a visual animation wrapping one facet after another, illustrating the construction of the extended convex hull step by step
- **ECH** — the extended convex hull itself, represented as a polyhedral set
