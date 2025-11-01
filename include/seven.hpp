#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <exception>

class Seven {
  public:  
    Seven();
    Seven(const std::string& str);
    Seven(const std::initializer_list<unsigned char>& lst);
    Seven(const Seven& other);
    Seven(Seven&& other) noexcept;
    virtual ~Seven() noexcept;

    Seven& operator=(const Seven& other);
    Seven& operator=(Seven&& other) noexcept;
    Seven& operator+=(const Seven& other);
    Seven& operator-=(const Seven& other);

    Seven& operator++();
    Seven operator++(int);
    Seven& operator--();
    Seven operator--(int);

    friend std::ostream& operator<<(std::ostream& output, const Seven& num);

    size_t Size() const;
    unsigned char* Number() const;
    void Swap(Seven& other);

  private:
    unsigned char* number_;
    size_t size_;
};

bool operator<(const Seven& left, const Seven& right);
bool operator>(const Seven& left, const Seven& right);
bool operator<=(const Seven& left, const Seven& right);
bool operator>=(const Seven& left, const Seven& right);
bool operator==(const Seven& left, const Seven& right);
bool operator!=(const Seven& left, const Seven& right);

Seven operator+(const Seven& left, const Seven& right);
Seven operator-(const Seven& left, const Seven& right);
