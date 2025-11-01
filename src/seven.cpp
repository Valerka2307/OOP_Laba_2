#include <../include/seven.hpp>


Seven::Seven()
    : size_(0),
      number_(nullptr) {};

Seven::Seven(const std::string& str) {
    if (str.empty()) {
        throw std::invalid_argument("Empty string");
    }

    size_ = str.size();
    number_ = new unsigned char[size_];
    for (size_t i = 0; i < size_; ++i) {
        if (str[i] < '0' || str[i] > '6') {
            delete[] number_;
            size_ = 0;
            throw std::invalid_argument("Invalid value");
        }
        number_[i] = static_cast<unsigned char>(str[size_ - 1 - i]);
    }
}

Seven::Seven(const std::initializer_list<unsigned char>& lst) {
    number_ = new unsigned char[lst.size()];
    if (number_ == nullptr) {
        throw std::runtime_error("Failed to allocate memory");
    }

    size_t pos_idx = 0;
    for (auto it = lst.end() - 1; it >= lst.begin(); --it) {
        if (*it < '0' || *it > '6') {
            delete[] number_;
            size_ = 0;
            throw std::invalid_argument("Invalid value");
        }
        number_[pos_idx++] = *it;
    }
    size_ = lst.size();
};

size_t Seven::Size() const{
    return size_;
}

Seven::Seven(const Seven& other) {
    number_ = new unsigned char[other.size_];
    if (number_ == nullptr) {
        throw std::runtime_error("Failed to allocate memory");
    }

    for (int i = 0; i < other.size_; ++i) {
        number_[i] = other.number_[i];
    }
    size_ = other.size_;
};

Seven::Seven(Seven&& other) noexcept
    : size_(other.size_)
    , number_(other.number_) {

    other.size_ = 0; 
    other.number_ = nullptr;
};

Seven& Seven::operator=(const Seven& other) {
    Seven copy = other;
    Swap(copy);
    return *this;
};

Seven& Seven::operator=(Seven&& other) noexcept {
    Seven copy = std::move(other);
    Swap(copy);
    return *this;
};

unsigned char* Seven::Number() const{
    return number_;
};

bool operator<(const Seven& left, const Seven& right) {
    if (left.Size() != right.Size())
        return left.Size() < right.Size();

    for (int i = left.Size() - 1; i >= 0; --i) {
        if (left.Number()[i] != right.Number()[i])
            return left.Number()[i] < right.Number()[i];
    }
    return false;
}

bool operator>(const Seven& left, const Seven& right) {
    if (left.Size() != right.Size())
        return left.Size() > right.Size();

    for (int i = left.Size() - 1; i >= 0; --i) {
        if (left.Number()[i] != right.Number()[i])
            return left.Number()[i] > right.Number()[i];
    }
    return false;
}

bool operator<=(const Seven& left, const Seven& right) {
     return (left < right) || !(left > right);
};

bool operator>=(const Seven& left, const Seven& right) {
    return (left > right) || !(left < right);
};

bool operator==(const Seven& left, const Seven& right) {
    return !(left < right) && !(left > right);
};

bool operator!=(const Seven& left, const Seven& right) {
    return (left < right) || (left > right);
};

void Seven::Swap(Seven& other) {
    std::swap(number_, other.number_);
    std::swap(size_, other.size_);
};

Seven& Seven::operator+=(const Seven& other) {
    Seven copy = other;
    if (*this < other) {
        Swap(copy);
    }

    int to_next_digit = 0;
    for (int i = 0; i < size_; ++i) {

        int val_1 = static_cast<int>(number_[i] - '0');
        int val_2 = (i < other.size_) ? static_cast<int>(other.number_[i] - '0') : 0;
        val_1 += val_2;

        int cur_digit = (val_1 + to_next_digit) % 7;
        number_[i] = static_cast<unsigned char>('0' + cur_digit);
        to_next_digit = (val_1 + to_next_digit) / 7;
    }

    if (to_next_digit > 0) {
        unsigned char* new_number = new unsigned char[size_ + 1];

        if (new_number == nullptr) {
            delete[] number_;
            size_ = 0;
            throw std::runtime_error("Failed to allocate memory");
        }

        for (int i = 0; i < size_; ++i) {
            new_number[i] = number_[i];
        }

        new_number[size_] = static_cast<unsigned char>('0' + to_next_digit);
        delete[] number_;
        number_ = new_number;
        ++size_;
    }

    return *this;
};

Seven& Seven::operator-=(const Seven& other) {
    if (*this < other)
        throw std::underflow_error("Subtraction from a lesser to a greater for unsinged type");

    Seven copy = other;

    int to_next_digit = 0;

    for (int i = 0; i < size_; ++i) {
        int val_1 = static_cast<int>(number_[i] - '0') - to_next_digit;
        int val_2 = (i < other.size_) ? static_cast<int>(other.number_[i] - '0') : 0;

        if (val_1 < val_2) {
            val_1 += 7;
            to_next_digit = 1;
        } else {
            to_next_digit = 0;
        }

        number_[i] = static_cast<unsigned char>('0' + (val_1 - val_2));
    }

    while (size_ > 1 && number_[size_ - 1] == '0') {
        --size_;
    }

    return *this;
};

Seven operator+(const Seven& left, const Seven& right){
    Seven copy = left;
    copy += right;
    return copy;
};

Seven operator-(const Seven& left, const Seven& right) {
    Seven copy = left;
    copy -= right;
    return copy;
};

Seven& Seven::operator++() {
    Seven one = Seven("1");
    *this += one;
    return *this;
};

Seven Seven::operator++(int) {
    Seven copy = *this;
    Seven one = Seven("1");
    *this += one;
    return copy;
};

Seven& Seven::operator--() {
    Seven one = Seven("1");
    *this -= one;
    return *this;
};

Seven Seven::operator--(int) {
    Seven copy = *this;
    Seven one = Seven("1");
    *this -= one;
    return copy;
};

std::ostream& operator<<(std::ostream& output, const Seven& num) {
    for (int i = num.size_ - 1; i >= 0; --i) {
        output << num.number_[i];
    }
    return output;
};

Seven::~Seven() {
    delete[] number_;
    size_ = 0;
};
