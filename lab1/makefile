.PHONY:test,clean,work,expr,gcc,fibonacci,suffix
test:
	arm-linux-gnueabihf-gcc factorial.S -o example.out
	qemu-arm -L /usr/arm-linux-gnueabihf ./example.out
clean:
	rm -fr example.out
	rm compute_expr
	rm y.tab.c

work:
	qemu-arm -L /usr/arm-linux-gnueabihf ./example.out

expr:
	yacc expr.y
	gcc y.tab.c -o compute_expr
	./compute_expr

suffix:
	yacc expr1.y
	gcc y.tab.c -o compute_expr
	./compute_expr

symbol:
	yacc expr2.y
	gcc y.tab.c -o compute_expr
	./compute_expr

fibonacci:
	arm-linux-gnueabihf-gcc fibonacci.S -o example.out
	qemu-arm -L /usr/arm-linux-gnueabihf ./example.out
