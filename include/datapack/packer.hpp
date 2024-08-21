#pragma once

#include <concepts>

namespace datapack {

template <int Mode>
class Packer;

static constexpr int MODE_WRITE = 0;
static constexpr int MODE_READ = 1;
static constexpr int MODE_EDIT = 2;

template <typename T, int Mode>
using packref = std::conditional_t<Mode==0, const T&, T&>;

template <typename T, int Mode>
concept packable = requires(packref<T, Mode> value, Packer<Mode>& packer) {
    { pack(value, packer) };
};

using Writer = Packer<MODE_WRITE>;
template <typename T>
concept writeable = packable<T, MODE_WRITE>;

using Reader = Packer<MODE_READ>;
template <typename T>
concept readable = packable<T, MODE_READ>;

using Editor = Packer<MODE_EDIT>;
template <typename T>
concept editable = packable<T, MODE_EDIT>;

#define DATAPACK(T) \
template <int Mode> \
void pack(packref<T, Mode> value, Packer<Mode>& packer)

#define DATAPACK_IMPL(T, value_name, packer_name) \
template void pack(packref<T, MODE_WRITE>, Packer<MODE_WRITE>&); \
template void pack(packref<T, MODE_READ>, Packer<MODE_READ>&); \
template <int Mode> \
void pack(packref<T, Mode> value_name, Packer<Mode>& packer_name)

#define DATAPACK_INLINE(T, value_name, packer_name) \
template <int Mode> \
void pack(packref<T, Mode> value_name, Packer<Mode>& packer_name)

// template void pack(packref<T, MODE_EDIT>, Packer<MODE_EDIT>&); \

} // namespace datapack
