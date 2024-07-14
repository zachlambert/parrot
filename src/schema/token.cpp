#include "datapack/schema/token.hpp"
#include "datapack/common.hpp"

namespace datapack {

template <typename Visitor>
void visit(Visitor& visitor, token::Enumerate& value) {
    visitor.object_begin();
    visitor.value("labels", value.labels);
    visitor.object_end();
}
DATAPACK_IMPL(token::Enumerate)

template <typename Visitor>
void visit(Visitor& visitor, token::VariantBegin& value) {
    visitor.object_begin();
    visitor.value("labels", value.labels);
    visitor.object_end();
}
DATAPACK_IMPL(token::VariantBegin)

template <typename Visitor>
void visit(Visitor& visitor, token::VariantNext& value) {
    visitor.object_begin();
    visitor.value("type", value.type);
    visitor.object_end();
}
DATAPACK_IMPL(token::VariantNext)

template <typename Visitor>
void visit(Visitor& visitor, datapack::token::ObjectNext& value) {
    visitor.object_begin();
    visitor.value("key", value.key);
    visitor.object_end();
}
DATAPACK_IMPL(token::ObjectNext)

template <typename Visitor>
void visit(Visitor& visitor, datapack::token::TrivialBegin& value) {
    visitor.object_begin();
    visitor.value("size", value.size);
    visitor.object_end();
}
DATAPACK_IMPL(token::TrivialBegin)

template <typename Visitor>
void visit(Visitor& visitor, datapack::token::TrivialEnd& value) {
    visitor.object_begin();
    visitor.value("size", value.size);
    visitor.object_end();
}
DATAPACK_IMPL(token::TrivialEnd)

std::vector<const char*> variant_labels<Token>::value = {
    "i32", "i64", "u32", "u64", "f32", "f64",
    "string", "boolean",
    "optional", "enumerate",
    "variant_begin", "variant_end", "variant_next",
    "binary_data", "trivial_begin", "trivial_end",
    "object_begin", "object_end", "object_next",
    "tuple_begin", "tuple_end", "tuple_next",
    "list"
};

bool operator==(const Token& lhs, const Token& rhs) {
    if (lhs.index() != rhs.index()) return false;

    if (auto lhs_value = std::get_if<token::Enumerate>(&lhs)) {
        auto rhs_value = std::get_if<token::Enumerate>(&rhs);
        return lhs_value->labels == rhs_value->labels;
    }
    if (auto lhs_value = std::get_if<token::VariantBegin>(&lhs)) {
        auto rhs_value = std::get_if<token::VariantBegin>(&rhs);
        return lhs_value->labels == rhs_value->labels;
    }
    if (auto lhs_value = std::get_if<token::VariantNext>(&lhs)) {
        auto rhs_value = std::get_if<token::VariantNext>(&rhs);
        return lhs_value->type == rhs_value->type;
    }
    if (auto lhs_value = std::get_if<token::ObjectNext>(&lhs)) {
        auto rhs_value = std::get_if<token::ObjectNext>(&rhs);
        return lhs_value->key == rhs_value->key;
    }
    if (auto lhs_value = std::get_if<token::TrivialBegin>(&lhs)) {
        auto rhs_value = std::get_if<token::TrivialBegin>(&rhs);
        return lhs_value->size == rhs_value->size;
    }
    if (auto lhs_value = std::get_if<token::TrivialEnd>(&lhs)) {
        auto rhs_value = std::get_if<token::TrivialEnd>(&rhs);
        return lhs_value->size == rhs_value->size;
    }

    return true;
}

} // namespace datapack
