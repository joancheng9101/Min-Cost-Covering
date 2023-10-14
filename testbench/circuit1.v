module circuit1 (input a1, a2, b1, c1, c2, d1, d2, e1, e2, output OUT);

wire a, b, c, d, e, f, g, h, i, j, k, l;

NAND A(a, a1, a2);
NOT B(b, b1);
NAND C(c, c1, c2);
NAND D(d, d1, d2);
NAND E(e, e1, e2);
NAND F(f, a, b);
NOT G(g, f);
NAND H(h, g, c);
NOT I(i, h);
NAND J(j, d, e);
NOT K(k, j);
NAND L(l, i, k);
NOT M(OUT, l);


endmodule
