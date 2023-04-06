#ifndef EMULATOR_FUNCTION_H_
#define EMULATOR_FUNCTION_H_

#include <stdint.h>

#include "emulator.h"

// EFLAGのビットフラグ
#define CARRY_FLAG (1)
#define ZERO_FLAG (1 << 6)
#define SIGN_FLAG (1 << 7)
#define OVERFLOW_FLAG (1 << 11)

// プログラムカウンタから相対位置にある符号無し8bit値を取得
uint32_t get_code8(Emulator* emu, int index);

// プログラムカウンタから相対位置にある符号付き8bit値を取得
int32_t get_sign_code8(Emulator* emu, int index);

// プログラムカウンタから相対位置にある符号無し32bit値を取得
uint32_t get_code32(Emulator* emu, int index);

// プログラムカウンタから相対位置にある符号付き32bit値を取得
int32_t get_sign_code32(Emulator* emu, int index);

// index番目の8bit汎用レジスタの値を取得する
uint32_t get_register8(Emulator* emu, int index);

// index番目の32bit汎用レジスタの値を取得する
uint32_t get_register32(Emulator* emu, int index);

// index番目の8bit汎用レジスタの値を設定する
void set_register8(Emulator* emu, int index, uint32_t value);

// index番目の32bit汎用レジスタの値を設定する
void set_register32(Emulator* emu, int index, uint32_t value);

// メモリのindex番地の8bit値を取得する
uint32_t get_memory8(Emulator* emu, uint32_t address);

// メモリのindex番地の32bit値を取得する
uint32_t get_memory32(Emulator* emu, uint32_t address);

// メモリのindex番地に8bit値を設定する
void set_memory8(Emulator* emu, uint32_t address, uint32_t value);

// メモリのindex番地に32bit値を設定する
void set_memory32(Emulator* emu, uint32_t address, uint32_t value);

// スタックに32bitの値を積む
void push32(Emulator* emu, uint32_t value);

// スタックから32bitの値を取り出す
uint32_t pop32(Emulator* emu);

// EFLAGの各フラグの設定
void set_carry(Emulator* emu, int is_carry);
void set_zero(Emulator* emu, int is_carry);
void set_sign(Emulator* emu, int is_carry);
void set_overflow(Emulator* emu, int is_carry);

// EFLAGの各フラグの取得
int is_carry(Emulator* emu);
int is_zero(Emulator* emu);
int is_sign(Emulator* emu);
int is_overflow(Emulator* emu);

// 減算によるEFLAGの更新
void update_eflags_sub(Emulator* emu, uint32_t v1, uint32_t v2,
                       uint64_t result);

#endif
