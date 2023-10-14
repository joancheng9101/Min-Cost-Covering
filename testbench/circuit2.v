module circuit2(input a1, a2, b1, b2, c1, c2, e1, output OUT);

wire a, b, c, d, e, f, g, h;

NAND A(a, a1, a2);
NAND B(b, b1, b2);
NAND C(c, c1, c2);
NAND D(d, a, b);
NOT E(e, e1);
NOT F(f, c);
NOT G(g, d);
NAND H(h, e, f);
NAND I(OUT, g, h);


endmodule
