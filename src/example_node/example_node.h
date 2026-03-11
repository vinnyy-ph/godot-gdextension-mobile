#ifndef EXAMPLE_NODE_H
#define EXAMPLE_NODE_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>

namespace godot {

/// ExampleNode — a minimal GDExtension custom Node.
/// Rename / replace this with your actual game nodes.
class ExampleNode : public Node {
    GDCLASS(ExampleNode, Node)

private:
    double time_passed = 0.0;

public:
    ExampleNode() = default;
    ~ExampleNode() = default;

    void _process(double delta) override;

    // Exposed to GDScript
    double get_time_passed() const { return time_passed; }

protected:
    static void _bind_methods();
};

} // namespace godot

#endif // EXAMPLE_NODE_H
