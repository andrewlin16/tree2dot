tree2dot
========

tree2dot is a simple command-line utility to generate a DOT graph file from a
tree expressed in a Lisp-like syntax.

Usage
-----

tree2dot reads input from stdin and outputs the resulting DOT file to stdout.

Example usage: `tree2dot < examples/test.txt > examples/test.dot`

This will take the tree in examples/test.txt and output a DOT file to
examples/test.dot.

The output of tree2dot can also be piped directly into graphviz.

Example usage: `tree2dot < examples/test.txt | dot -Tsvg > examples/test.svg`

This will take the tree in examples/test.txt, pipe the resulting DOT to the dot
program, and output a SVG file to examples/test.svg.

License
-------

tree2dot is licensed under the MIT license. See LICENSE.txt.
