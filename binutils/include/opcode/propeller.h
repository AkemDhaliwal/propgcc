/* Parallax Propeller opcde list.
   Copyright 2011 Parallax Inc.

   This file is part of GDB and GAS.

   GDB and GAS are free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   GDB and GAS are distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GDB or GAS; see the file COPYING3.  If not, write to
   the Free Software Foundation, 51 Franklin Street - Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* List of possible hardware types, including any pseudo-types like
 * LMM on Propeller-1, */
#define PROP_1 0
#define PROP_2 1
#define PROP_1_LMM 2

/* List of instruction formats */
#define PROPELLER_OPERAND_NO_OPS      0
#define PROPELLER_OPERAND_SOURCE_ONLY 1
#define PROPELLER_OPERAND_DEST_ONLY   2
#define PROPELLER_OPERAND_TWO_OPS     3
#define PROPELLER_OPERAND_CALL        4
#define PROPELLER_OPERAND_IGNORE      5
#define PROPELLER_OPERAND_JMP         6
#define PROPELLER_OPERAND_JMPRET      7
#define PROPELLER_OPERAND_MOVA        8
#define PROPELLER_OPERAND_LDI         9
#define PROPELLER_OPERAND_BRW         10
#define PROPELLER_OPERAND_BRS         11
#define PROPELLER_OPERAND_XMMIO       12
#define PROPELLER_OPERAND_FCACHE      13
#define PROPELLER_OPERAND_MVI         14
#define PROPELLER_OPERAND_LCALL       15
#define PROPELLER_OPERAND_MACRO_8     16
#define PROPELLER_OPERAND_MACRO_0     17

/* types of compressed instructions available */
/* normally instructions take 32 bits each; however, we provide
 * a compressed mode wherein they take fewer bits
 * types of compressed formats available:
 *
 * macro: instruction with no register arguments (like NOP, BREAKPOINT)
 * call:  a subroutine call
 * mov:   a move instruction; we have various optimizations for this
 * add:   an add instruction; ditto
 * cmps:  a signed compare instruction
 * brs:   a relative branch
 * brl:   a long branch
 * reg_or_imm: a generic instruction (not one of those above) which has
 *         a compressed form
 *
 * there are many potential optimizations for mov, based on the immediate
 * value (e.g. mov rN, #0 can be optimized to "clr r0")
 *
 */

/* instruction cannot be compressed */
#define NO_COMPRESSED (0)
/* instruction can be compressed to a macro */
#define COMPRESS_MACRO  (1)
/* instruction can be compressed to a 2 or 3 byte extended operation */
#define COMPRESS_XOP   (2)
/* instruction can be compressed to a conditional branch */
#define COMPRESS_BRL (3)
/* instruction can be compressed to a mvi */
#define COMPRESS_MVI (4)
/* instruction can be compressed to a mviw */
#define COMPRESS_MVIW (5)

/* instruction prefixes */
#define PREFIX_MACRO    (0x00)
#define PREFIX_REGREG   (0x10)
#define PREFIX_REGIMM4  (0x20)
#define PREFIX_REGIMM12 (0x30)
#define PREFIX_BRW      (0x40)
#define PREFIX_MVI      (0x50)
#define PREFIX_MVIW     (0x60)
#define PREFIX_BRS      (0x70)
#define PREFIX_SKIP2    (0x80)
#define PREFIX_SKIP3    (0x90)
#define PREFIX_PACK_NATIVE (0xF0)

/* extended operations */
#define XOP_MOV 0x0
#define XOP_ADD 0x1
#define XOP_SUB 0x2
#define XOP_CMPS 0x3
#define XOP_AND 0x4
#define XOP_ANDN 0x5
#define XOP_NEG 0x6
#define XOP_OR  0x7
#define XOP_XOR 0x8
#define XOP_SHL 0x9
#define XOP_SHR 0xa
#define XOP_SAR 0xb
#define XOP_RDB 0xc
#define XOP_RDL 0xd
#define XOP_WRB 0xe
#define XOP_WRL 0xf

/* "macro" instructions (which need no destination register) */
#define MACRO_NOP    0x00
#define MACRO_BREAK  0x01
#define MACRO_RET    0x02
#define MACRO_PUSHM  0x03
#define MACRO_POPM   0x04
#define MACRO_LCALL  0x05
#define MACRO_MUL    0x06
#define MACRO_UDIV   0x07
#define MACRO_DIV    0x08
#define MACRO_FCACHE 0x0e
#define MACRO_NATIVE 0x0f

/* opcode structure */
struct propeller_opcode
{
  const char *name;
  int opcode;
  int mask;
  int format;
  int result;
  int hardware;
  int can_compress;
  int copc;  /* compressed opcode */
};

struct propeller_condition
{
  const char *name;
  int value;
  int tabs;
};

struct propeller_effect
{
  const char *name;
  int or;
  int and;
};


int print_insn_propeller (bfd_vma memaddr, struct disassemble_info *info);
extern const struct propeller_opcode propeller_opcodes[];
extern const int propeller_num_opcodes;
extern const struct propeller_condition propeller_conditions[];
extern const int propeller_num_conditions;
extern const struct propeller_effect propeller_effects[];
extern const int propeller_num_effects;
