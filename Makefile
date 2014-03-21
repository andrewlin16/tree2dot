EXAMPLES = examples/ling_simple examples/test examples/trivb_tree

tree2dot:
	gcc -o tree2dot tree2dot.c

%.dot: tree2dot
	./tree2dot < $(addsuffix .txt, $(basename $@)) > $@

%.svg: tree2dot
	./tree2dot < $(addsuffix .txt, $(basename $@)) | dot -Tsvg > $@

examples: $(addsuffix .svg, $(EXAMPLES))

examples-dot: $(addsuffix .dot, $(EXAMPLES))

examples-all: examples examples-dot

.PHONY: clean

clean:
	rm -f tree2dot

clean-examples:
	rm -f examples/*.dot examples/*.svg

clean-all: clean clean-examples
