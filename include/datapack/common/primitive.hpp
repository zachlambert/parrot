#pragma once

#include "datapack/reader.hpp"
#include "datapack/writer.hpp"


namespace datapack {

inline void read(Reader& reader, std::int32_t& value) {
    reader.value_i32(value);
}

inline void read(Reader& reader, std::int64_t& value) {
    reader.value_i64(value);
}

inline void read(Reader& reader, std::uint32_t& value) {
    reader.value_u32(value);
}

inline void read(Reader& reader, std::uint64_t& value) {
    reader.value_u64(value);
}

inline void read(Reader& reader, float& value) {
    reader.value_f32(value);
}

inline void read(Reader& reader, double& value) {
    reader.value_f64(value);
}

inline void read(Reader& reader, std::string& value) {
    reader.value_string(value);
}

inline void read(Reader& reader, bool& value) {
    reader.value_bool(value);
}

inline void write(Writer& writer, std::int32_t value) {
    writer.value_i32(value);
}

inline void write(Writer& writer, std::int64_t value) {
    writer.value_i64(value);
}

inline void write(Writer& writer, std::uint32_t value) {
    writer.value_u32(value);
}

inline void write(Writer& writer, std::uint64_t value) {
    writer.value_u64(value);
}

inline void write(Writer& writer, float value) {
    writer.value_f32(value);
}

inline void write(Writer& writer, double value) {
    writer.value_f64(value);
}

inline void write(Writer& writer, std::string value) {
    writer.value_string(value);
}

inline void write(Writer& writer, bool value) {
    writer.value_bool(value);
}

} // namespace datapack
