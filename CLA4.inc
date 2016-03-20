declare CLA4{
	input	a[4];
	input	b[4];
	
	// キャリーなしの出力
	output	c0;
	output	r0[4];
	// キャリーありの出力
	output	c1;
	output	r1[4];

	func_in	exe(a,b);
}
