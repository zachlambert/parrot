#pragma once

#include "datapack/packer.hpp"
#include "datapack/primitive.hpp"
#include "datapack/constraint.hpp"
#include "datapack/reader.hpp"
#include "datapack/writer.hpp"
#include <micro_types/string.hpp>


namespace datapack {

DATAPACK_INLINE(std::int32_t, packer, value) {
    packer.primitive(I32, &value);
}

DATAPACK_INLINE(std::int64_t, packer, value) {
    packer.primitive(I64, &value);
}

DATAPACK_INLINE(std::uint32_t, packer, value) {
    packer.primitive(U32, &value);
}

DATAPACK_INLINE(std::uint64_t, packer, value) {
    packer.primitive(U64, &value);
}

DATAPACK_INLINE(float, packer, value) {
    packer.primitive(F32, &value);
}

DATAPACK_INLINE(double, packer, value) {
    packer.primitive(F64, &value);
}

DATAPACK_INLINE(std::string, packer, value) {
    if constexpr(Mode == MODE_READ) {
        if (const char* value_cstr = packer.string()) {
            value = value_cstr;
        } else {
            value.clear();
        }
    }
    if constexpr(Mode == MODE_WRITE) {
        packer.string(value.c_str());
    }
}

DATAPACK_INLINE(mct::string, packer, value) {
    if constexpr(Mode == MODE_READ) {
        if (const char* value_cstr = packer.string()) {
            value = value_cstr;
        } else {
            value.clear();
        }
    }
    if constexpr(Mode == MODE_WRITE) {
        packer.string(value.c_str());
    }
}

DATAPACK_INLINE(bool, packer, value) {
    packer.boolean(value);
}

inline bool validate(const std::int32_t& value, const RangeConstraint& c) {
    return c.validate(value);
}

inline bool validate(const std::int64_t& value, const RangeConstraint& c) {
    return c.validate(value);
}

inline bool validate(const std::uint32_t& value, const RangeConstraint& c) {
    return c.validate(value);
}

inline bool validate(const std::uint64_t& value, const RangeConstraint& c) {
    return c.validate(value);
}

inline bool validate(const float& value, const RangeConstraint& c) {
    return c.validate(value);
}

inline bool validate(const double& value, const RangeConstraint& c) {
    return c.validate(value);
}

} // namespace datapack
