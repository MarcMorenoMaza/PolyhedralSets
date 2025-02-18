# QuantifierEliminationOverTheIntegers

The QuantifierEliminationOverTheIntegers package is written in [Maple](https://www.maplesoft.com/) and is designed to determine whether a given formula is satisfiable. If the formula contains free variables, the package identifies the constraints under which the formula remains satisfiable.

## Installation Guide
This package can be installed as follows:
1. Clone or Download this repository (i.e. `git clone https://github.com/MarcMorenoMaza/PolyhedralSets.git`)
2. Navigate to the repository folder (i.e. `cd .PolyhedralSets/QuantifierEliminationOverTheIntegers`)
3. Copy the full path of `master.mla` by running `pwd`
4. Edit your Maple initialization file `~/.mapleinit` using `libname :=  "<path>", libname:`

After successful installation `master.mla` will be integrated into your Maple environment. 
Note that `<path>` should be replaced with the full path to where `master.mla` is located.

## Code Demo
The Maple worksheet [QuantifierEliminationOverZ.mw](https://github.com/MarcMorenoMaza/PolyhedralSets/blob/main/QuantifierEliminationOverTheIntegers/QuantifierEliminationOverZ.mw) is a demo of this package.

In addition to installing the package, you also need to have Maple installed to view the demo. You can download Maple from their [official website](https://www.maplesoft.com/).

## Usage and Documentation
This package can be loaded in Maple by using `with(QuantifierEliminationOverZ);`. This command also displays all available functions.

Our main command is `QEoverZ(<formula>)`, which takes in a (parametric) quantified formula, applies *integer projection* to eliminate quantifiers. The output is either `true`, `false` or quantifier free formula in terms of the free variables, which makes the input formula true.

We provide two *integer projection* methods: `integerpointdecomposition` (default) and `numberofintegerpoints` and and two quantifier elimination modes: `onequantifieratatime` (default) and `byblockofquantifiers`. You can specify them as follows `QEoverZ(<formula>, method = <method name>, mode = <mode name>)`. 

If no options are provided, the function runs with `method = integerpointdecomposition, mode = onequantifieratatime`.

For detailed examples and demonstrations, check the [QuantifierEliminationOverZ.mw](https://github.com/MarcMorenoMaza/PolyhedralSets/blob/main/QuantifierEliminationOverTheIntegers/QuantifierEliminationOverZ.mw) worksheet.
