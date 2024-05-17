#include "example.hpp"

#include <cstring>
#include <cmath>
#include <datapack/common.hpp>


template <typename V>
void visit(V& visitor, Circle& value) {
    visitor.object_begin();
    visitor.value("radius", value.radius);
    visitor.object_end();
}
DATAPACK_VISITOR_FUNCS_IMPL(Circle)

template <typename V>
void visit(V& visitor, Rect& value) {
    visitor.object_begin();
    visitor.value("width", value.width);
    visitor.value("height", value.height);
    visitor.object_end();
}
DATAPACK_VISITOR_FUNCS_IMPL(Rect)

std::vector<const char*> datapack::enum_details<Physics>::labels = {
    "dynamic", "kinematic", "static"
};

const char* datapack::enum_details<Physics>::to_label(const Physics& value) {
    switch (value){
        case Physics::Dynamic:
            return "dynamic";
        case Physics::Kinematic:
            return "kinematic";
        case Physics::Static:
            return "static";
    }
    return "";
}

Physics datapack::enum_details<Physics>::from_label(const char* label) {
    if (std::strcmp(label, "dynamic") == 0) {
        return Physics::Dynamic;
    }
    if (std::strcmp(label, "kinematic") == 0) {
        return Physics::Kinematic;
    }
    if (std::strcmp(label, "static") == 0) {
        return Physics::Static;
    }
    throw std::runtime_error("Invalid label");
    return Physics::Dynamic;
}

std::vector<const char*> datapack::variant_details<Shape>::labels = {
    "circle", "rect"
};

const char* datapack::variant_details<Shape>::to_label(const Shape& value) {
    if (std::get_if<Circle>(&value)) {
        return "circle";
    }
    if (std::get_if<Rect>(&value)) {
        return "rect";
    }
    return "";
}

Shape datapack::variant_details<Shape>::from_label(const char* label) {
    if (std::strcmp(label, "circle") == 0) {
        return Circle();
    }
    if (std::strcmp(label, "rect") == 0) {
        return Rect();
    }
    throw std::runtime_error("Invalid label");
    return Circle();
}

template <typename V>
void visit(V& visitor, Pose& value) {
    visitor.object_begin();
    visitor.value("x", value.x);
    visitor.value("y", value.y);
    visitor.value("angle", value.angle);
    visitor.object_end();
}
DATAPACK_VISITOR_FUNCS_IMPL(Pose)

template <typename V>
void visit(V& visitor, Item& value) {
    visitor.object_begin();
    visitor.value("count", value.count);
    visitor.value("name", value.name);
    visitor.object_end();
}
DATAPACK_VISITOR_FUNCS_IMPL(Item)

template <typename V>
void visit(V& visitor, Sprite& value) {
    visitor.object_begin();
    visitor.value("width", value.width);
    visitor.value("height", value.height);
    if constexpr(std::is_same_v<V, datapack::Reader>) {
        visitor.value_binary("data", value.data, value.width * value.height);
    }
    if constexpr(std::is_same_v<V, datapack::Writer>) {
        visitor.value_binary("data", value.data);
    }
    if constexpr(std::is_same_v<V, datapack::Definer>) {
        visitor.object_next("data");
        visitor.binary();
        visitor.object_begin();
        visitor.value("x", 0.0);
        visitor.value("y", 0.0);
        visitor.value("z", 0.0);
        visitor.object_end();
    }
    visitor.object_end();
}
DATAPACK_VISITOR_FUNCS_IMPL(Sprite)

template <typename V>
void Entity::visit(V& visitor) {
    visitor.object_begin();
    visitor.value("index", index);
    visitor.value("name", name);
    visitor.value("enabled", enabled);
    visitor.value("pose", pose);
    visitor.value("physics", physics);
    visitor.value("hitbox", hitbox);
    visitor.value("sprite", sprite);
    visitor.value("items", items);
    visitor.value("assigned_items", assigned_items);
    visitor.value("properties", properties);
    visitor.value("flags", flags);
    visitor.object_end();
}
DATAPACK_VISITOR_METHODS_IMPL(Entity)

Entity Entity::example() {
    Entity result;
    result.index = 5;
    result.name = "player";
    result.enabled = true;
    result.pose = { 1.0, 2.0, M_PI/2 };
    result.physics = Physics::Kinematic;
    result.hitbox = Circle { 1.0 };
    result.sprite = [](){
        Sprite sprite;
        sprite.width = 20;
        sprite.height = 20;
        sprite.data.resize(sprite.height * sprite.width);
        for (int i = 0; i < sprite.height; i++) {
            for (int j = 0; j < sprite.width; j++) {
                auto& pixel = sprite.data[i*sprite.width + j];
                pixel.r = ((double)i + 0.5) / sprite.height;
                pixel.g = ((double)j + 0.5) / sprite.width;
                pixel.b = 0;
            }
        }
        return sprite;
    }();
    result.items = []() {
        std::vector<Item> items;
        items.push_back(Item { 5, "hp_potion" });
        items.push_back(Item { 1, "sword" });
        items.push_back(Item { 1, "map" });
        items.push_back(Item { 120, "gold" });
        return items;
    }();
    result.assigned_items = { 1, 2, -1 };
    result.properties = []() {
        std::unordered_map<std::string, double> properties;
        properties["strength"] = 10.5;
        properties["agility"] = 5.0;
        return properties;
    }();
    result.flags = []() {
        std::unordered_map<int, bool> flags;
        flags[0] = true;
        flags[1] = false;
        flags[2] = true;
        return flags;
    }();
    return result;
}