#include <gtest/gtest.h>
#include "datapath/hazard_detection.h"
#include "instructions.h"
#include "datapath/IF.h"

TEST(HDU, branch_previousRinstruct) {
	IFID ifid;
	IDEX idex;
	EXMEM exmem = {};
	MEMWB memwb = {};
	HDU hdu;
	Memory mem;
	IF if_block;
	IFControls ifcontrols;
	bool stall;

	if_block.set_pc(0x1234);

	ifid.instruction = inst::beq(reg::t0, reg::t1, 0x01);

	idex.mem_controls.mem_read = 0;
	idex.write_reg = reg::t0;

	

	hdu.signals_in(ifid, idex, exmem, memwb);
	hdu.tick();
	hdu.tock();
	stall = hdu.signals_out();

	if_block.signals_in(0x0000, ifcontrols, stall);
	if_block.tick(mem);
	if_block.tock(mem);
	ifid = if_block.signals_out();



	//check that stall was passed out of HDU
	EXPECT_EQ(1, stall);
	//check that PC was not changed
	EXPECT_EQ(0x1234, if_block.get_pc());

}

TEST(HDU, branch_previousload) {
	IFID ifid;
	IDEX idex;
	EXMEM exmem = {};
	MEMWB memwb = {};
	HDU hdu;
	Memory mem;
	IF if_block;
	IFControls ifcontrols;
	bool stall;

	if_block.set_pc(0x1234);

	ifid.instruction = inst::beq(reg::t0, reg::t1, 0x01);

	idex.mem_controls.mem_read = 1;
	idex.write_reg = reg::t0;

	hdu.signals_in(ifid, idex, exmem, memwb);
	hdu.tick();
	hdu.tock();
	stall = hdu.signals_out();

	if_block.signals_in(0x0000, ifcontrols, stall);
	if_block.tick(mem);
	if_block.tock(mem);
	ifid = if_block.signals_out();



	//check that stall was passed out of HDU
	EXPECT_EQ(1, stall);
	//check that PC was not changed
	EXPECT_EQ(0x1234, if_block.get_pc());

}

TEST(HDU, branch_2_previousload) {
	IFID ifid;
	IDEX idex;
	EXMEM exmem;
	MEMWB memwb = {};
	HDU hdu;
	Memory mem;
	IF if_block;
	IFControls ifcontrols;
	bool stall;

	if_block.set_pc(0x1234);

	ifid.instruction = inst::beq(reg::t0, reg::t1, 0x01);

	idex.mem_controls.mem_read = 0;
	idex.write_reg = reg::t3;

	exmem.mem_controls.mem_read = 1;
	exmem.write_reg = reg::t0;


	hdu.signals_in(ifid, idex, exmem, memwb);
	hdu.tick();
	hdu.tock();
	stall = hdu.signals_out();

	if_block.signals_in(0x0000, ifcontrols, stall);
	if_block.tick(mem);
	if_block.tock(mem);
	ifid = if_block.signals_out();



	//check that stall was passed out of HDU
	EXPECT_EQ(1, stall);
	//check that PC was not changed
	EXPECT_EQ(0x1234, if_block.get_pc());

}

/*	rs  c  rt
lw $t3, 0($t1)
	rd	  rs   rt
add $t0, $t1, $t0*/

TEST(HDU, loaduse_rt_rs) {
	IFID ifid;
	IDEX idex;
	EXMEM exmem = {};
	MEMWB memwb = {};
	HDU hdu;
	Memory mem;
	IF if_block;
	IFControls ifcontrols;
	bool stall;

	if_block.set_pc(0x1234);

	ifid.instruction = inst::add(reg::t0, reg::t1, reg::t0);

	idex.mem_controls.mem_read = 1;
	idex.write_reg = reg::t1;



	hdu.signals_in(ifid, idex, exmem, memwb);
	hdu.tick();
	hdu.tock();
	stall = hdu.signals_out();

	if_block.signals_in(0x0000, ifcontrols, stall);
	if_block.tick(mem);
	if_block.tock(mem);
	ifid = if_block.signals_out();



	//check that stall was passed out of HDU
	EXPECT_EQ(1, stall);
	//check that PC was not changed
	EXPECT_EQ(0x1234, if_block.get_pc());

}


/*	rs  c  rt
lw $t3, 0($t1)
	rd	  rs   rt
add $t0, $t0, $t1*/
TEST(HDU, loaduse_rt_rt) {
	IFID ifid;
	IDEX idex;
	EXMEM exmem = {};
	MEMWB memwb = {};
	HDU hdu;
	Memory mem;
	IF if_block;
	IFControls ifcontrols;
	bool stall;

	if_block.set_pc(0x1234);

	ifid.instruction = inst::add(reg::t0, reg::t0, reg::t1);

	idex.mem_controls.mem_read = 1;
	idex.write_reg = reg::t1;



	hdu.signals_in(ifid, idex, exmem, memwb);
	hdu.tick();
	hdu.tock();
	stall = hdu.signals_out();

	if_block.signals_in(0x0000, ifcontrols, stall);
	if_block.tick(mem);
	if_block.tock(mem);
	ifid = if_block.signals_out();



	//check that stall was passed out of HDU
	EXPECT_EQ(1, stall);
	//check that PC was not changed
	EXPECT_EQ(0x1234, if_block.get_pc());

}