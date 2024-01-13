input [3:0] numeral_bit;

output a;
output b;
output c;
output d;
output e;
output f;
output g;


wire not_numeral_bit_3;
wire not_numeral_bit_2;
wire not_numeral_bit_1;
wire not_numeral_bit_0;

wire n3n2;
wire y3n2;
wire n3y2;
wire n1n0;
wire n1y0;
wire y1n0;
wire y1y0;

wire zeroone;
wire zerotwo;
wire zerofour;
wire twothree;
wire threefour;
wire threefive;
wire fourfive;
wire fourseven;
wire fivesix;
wire sixseven;
wire sixeight;
wire seveneight;
wire eightnine;
wire temp0123;
wire temp0134;
wire temp0235;
wire temp0456;
wire temp2345;
wire temp4789;
wire temp5678;
wire temp6789;
wire temp689;
wire temp01345678;

wire minterm_00;
wire minterm_01;
wire minterm_02;
wire minterm_03;
wire minterm_04;
wire minterm_05;
wire minterm_06;
wire minterm_07;
wire minterm_08;
wire minterm_09;


assign not_numeral_bit_3 = ~numeral_bit[3];
assign not_numeral_bit_2 = ~numeral_bit[2];
assign not_numeral_bit_1 = ~numeral_bit[1];
assign not_numeral_bit_0 = ~numeral_bit[0];

assign n3n2 = not_numeral_bit_3 & not_numeral_bit_2;
assign n3y2 = not_numeral_bit_3 & numeral_bit[2];
assign y3n2 = numeral_bit[3] & not_numeral_bit_2;
assign n1n0 = not_numeral_bit_1 & not_numeral_bit_0;
assign n1y0 = not_numeral_bit_1 & numeral_bit[0];
assign y1n0 = numeral_bit[1] & not_numeral_bit_0;
assign y1y0 = numeral_bit[1] & numeral_bit[0];

assign minterm_00 = n3n2 & n1n0;
assign minterm_01 = n3n2 & n1y0;
assign minterm_02 = n3n2 & y1n0;
assign minterm_03 = n3n2 & y1y0;
assign minterm_04 = n3y2 & n1n0;
assign minterm_05 = n3y2 & n1y0;
assign minterm_06 = n3y2 & y1n0;
assign minterm_07 = n3y2 & y1y0;
assign minterm_08 = y3n2 & n1n0;
assign minterm_09 = y3n2 & n1y0;

assign zeroone = minterm_00 | minterm_01;
assign zerotwo = minterm_00 | minterm_02;
assign zerofour = minterm_00 | minterm_04;
assign twothree = minterm_02 | minterm_03;
assign threefour = minterm_03 | minterm_04;
assign threefive = minterm_03 | minterm_05;
assign fourfive = minterm_04 | minterm_05;
assign fourseven = minterm_04 | minterm_07;
assign fivesix = minterm_05 | minterm_06;
assign sixseven = minterm_06 | minterm_07;
assign sixeight = minterm_06 | minterm_08;
assign seveneight = minterm_07 | minterm_08;
assign eightnine = minterm_08 | minterm_09;

assign temp0123 = zeroone | twothree;
assign temp0134 = zeroone | threefour;
assign temp0235 = zerotwo | threefive;
assign temp0456 = zerofour | fivesix;
assign temp2345 = twothree | fourfive;
assign temp4789 = fourseven | eightnine;
assign temp5678 = fivesix | seveneight;
assign temp6789 = sixseven | eightnine;
assign temp689 = sixeight | minterm_09;
assign temp01345678 = temp0134 | temp5678;

assign a = temp0235 | temp6789;
assign b = temp0123 | temp4789;
assign c = temp01345678 | minterm_09;
assign d = temp0235 | sixeight;
assign e = zerotwo | sixeight;
assign f = temp0456 | eightnine;
assign g = temp2345 | temp689;