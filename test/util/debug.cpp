#include <gtest/gtest.h>
#include <datapack/util/debug.hpp>
#include <datapack/examples/entity.hpp>
#include <sstream>

static std::vector<std::string> get_lines(const std::string& text) {
    std::vector<std::string> lines;
    std::size_t prev = 0;
    std::size_t pos = std::min(text.find('\n', 0), text.size());
    while (pos != text.size()) {
        lines.push_back(text.substr(prev, pos - prev));
        prev = pos + 1;
        pos = std::min(text.find('\n', prev), text.size());
    }
    return lines;
}

TEST(Util, Debug) {
    const std::string expected = R"((object) {
    index: 5,
    name: player,
    enabled: true,
    pose: (object, trivial size = 24) {
        x: 1,
        y: 2,
        angle: 3,
    },
    physics: (enum, kinematic),
    hitbox: (optional, has_value) {
        (variant, circle) {
            (object, trivial size = 8) {
                radius: 1,
            },
        },
    },
    sprite: (object) {
        width: 2,
        height: 2,
        data: (list, trivial) {
            (object, trivial size = 24) {
                r: 0.25,
                g: 0.25,
                b: 0,
            },
            (object, trivial size = 24) {
                r: 0.25,
                g: 0.75,
                b: 0,
            },
            (object, trivial size = 24) {
                r: 0.75,
                g: 0.25,
                b: 0,
            },
            (object, trivial size = 24) {
                r: 0.75,
                g: 0.75,
                b: 0,
            },
        },
    },
    items: (list) {
        (object) {
            count: 5,
            name: hp_potion,
        },
        (object) {
            count: 1,
            name: sword,
        },
        (object) {
            count: 1,
            name: map,
        },
        (object) {
            count: 120,
            name: gold,
        },
    },
    assigned_items: (tuple, trivial size = 12) {
        1,
        2,
        -1,
    },
    properties: (list) {
        (tuple) {
            agility,
            5,
        },
        (tuple) {
            strength,
            10.5,
        },
    },
    flags: (list) {
        (tuple) {
            2,
            true,
        },
        (tuple) {
            1,
            false,
        },
        (tuple) {
            0,
            true,
        },
    },
},
)";

    std::stringstream ss;
    datapack::DebugWriter(ss).value(Entity::example());
    const std::string output = ss.str();
    std::cerr << datapack::debug(Entity::example()) << std::endl;

    auto expected_lines = get_lines(expected);
    auto output_lines = get_lines(output);
    ASSERT_EQ(expected_lines.size(), output_lines.size());
    for (std::size_t i = 0; i < expected_lines.size(); i++) {
        EXPECT_EQ(expected_lines[i], output_lines[i]);
    }
}
