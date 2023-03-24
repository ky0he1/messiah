#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "emulator.h"
#include "emulator_function.h"
#include "instruction.h"

#include "modrm.h"

// x86命令の配列
// opecode番目の関数がx86のopecodeに対応した命令となっている
instruction_func_t* instructions[256];

// 32ビットのメモリまたはレジスタから、即値を減算
static void sub_rm32_imm8(Emulator* emu, ModRM* modrm) {
    // 減算される数値
    uint32_t rm32 = get_rm32(emu, modrm);
    // 減算する数値
    uint32_t imm8 = (int32_t)get_sign_code8(emu, 0);
    // プログラムを進める
    emu->eip += 1;

    // 減算の結果をレジスタまたはメモリに格納
    set_rm32(emu, modrm, rm32 - imm8);
}

static void inc_rm32(Emulator* emu, ModRM* modrm) {
    uint32_t value = get_rm32(emu, modrm);
    set_rm32(emu, modrm, value + 1);
}

static void add_rm32_r32(Emulator* emu) {
    emu->eip += 1;
    ModRM modrm;
    parse_modrm(emu, &modrm);
    uint32_t r32 = get_r32(emu, &modrm);
    uint32_t rm32 = get_rm32(emu, &modrm);
    set_rm32(emu, &modrm, rm32 + r32);
}

static void code_83(Emulator* emu) {
    emu->eip += 1;
    ModRM modrm;
    parse_modrm(emu, &modrm);

    switch (modrm.opecode) {
    case 5:
        sub_rm32_imm8(emu, &modrm);
        break;
    default:
        printf("not implemented: 83 /%d\n", modrm.opecode);
        exit(1);
    }
}

static void mov_rm32_r32(Emulator* emu) {
    emu->eip += 1;
    ModRM modrm;
    parse_modrm(emu, &modrm);
    uint32_t r32 = get_r32(emu, &modrm);
    set_rm32(emu, &modrm, r32);
}

static void mov_r32_rm32(Emulator* emu) {
    emu->eip += 1;
    ModRM modrm;
    parse_modrm(emu, &modrm);
    uint32_t rm32 = get_rm32(emu, &modrm);
    set_r32(emu, &modrm, rm32);
}

static void mov_r32_imm32(Emulator* emu) {
    uint8_t reg = get_code8(emu, 0) - 0xB8;
    uint32_t value = get_code32(emu, 1);
    set_register32(emu, reg, value);
    emu->eip += 5;
}

static void mov_rm32_imm32(Emulator* emu) {
    emu->eip += 1;
    ModRM modrm;
    parse_modrm(emu, &modrm);
    uint32_t value = get_code32(emu, 0);
    emu->eip += 4;
    set_rm32(emu, &modrm, value);
}

void near_jump(Emulator* emu) {
    int32_t diff = get_sign_code32(emu, 1);
    emu->eip += (diff + 5);
}

void short_jump(Emulator* emu) {
    int8_t diff = get_sign_code8(emu, 1);
    emu->eip += (diff + 2);
}

static void code_ff(Emulator* emu) {
    emu->eip += 1;
    ModRM modrm;
    parse_modrm(emu, &modrm);

    switch (modrm.opecode) {
    case 0:
        inc_rm32(emu, &modrm);
        break;
    default:
        printf("not implemented: FF /%d\n", modrm.opecode);
        exit(1);
    }
}

void init_instructions(void) {
    int i;
    memset(instructions, 0, sizeof(instructions));
    instructions[0x01] = add_rm32_r32;
    instructions[0x83] = code_83;
    instructions[0x89] = mov_rm32_r32;
    instructions[0x8B] = mov_r32_rm32;
    for (i = 0; i < 8; i++) {
        instructions[0xB8 + i] = mov_r32_imm32;
    }
    instructions[0xC7] = mov_rm32_imm32;
    instructions[0xE9] = near_jump;
    instructions[0xEB] = short_jump;
    instructions[0xFF] = code_ff;
}