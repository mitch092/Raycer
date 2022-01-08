module;
#include <SDL.h>
#include <assert.h>
export module types;

export using u8 = Uint8;
export using u16 = Uint16;
export using u32 = Uint32;
export using u64 = Uint64;
export using i8 = Sint8;
export using i16 = Sint16;
export using i32 = Sint32;
export using i64 = Sint64;

export void asrt(int expr) {
    assert(expr);
}
