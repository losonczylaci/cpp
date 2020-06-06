#include <integer.hpp>

Int::operator std::string() const { return std::to_string(_value); }

Int operator+(const Int& lhs, const Int& rhs) {
    return lhs.getValue() + rhs.getValue();
}

Int operator-(const Int& lhs, const Int& rhs) {
    return lhs.getValue() - rhs.getValue();
}

Int operator*(const Int& lhs, const Int& rhs) {
    return lhs.getValue() * rhs.getValue();
}

Int operator/(const Int& lhs, const Int& rhs) {
    if (rhs.getValue() == 0) {
        throw std::runtime_error("Division by zero exception");
    }
    return lhs.getValue() / rhs.getValue();
}

bool operator==(const Int& lhs, const Int& rhs) {
    return lhs.getValue() == rhs.getValue();
}

bool operator!=(const Int& lhs, const Int& rhs) {
    return lhs.getValue() != rhs.getValue();
}

std::ostream& operator<<(std::ostream& o, const Int& rhs) {
    return o << rhs.getValue();
}

int Int::operator()(int nr) const { return this->_value * nr; }

Int& Int::operator++() {
    ++_value;
    return *this;
}

Int Int::operator++(int) {
    Int copy = *this;
    ++_value;
    return copy;
}
