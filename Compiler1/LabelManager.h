#pragma once
#include<string>
#include<vector>
#include<any>
#include<iostream>
#include<stdexcept>
#include"ParseTreeComponents.h"

class LabelManager {
private:
    class Labl {
    private:
        std::string name_;
        size_t index_;
    public:
        Labl(std::string const &, size_t);
        Labl(psc::Label const &, size_t ind);
        Labl(Labl const &) = default;
        Labl(Labl &&) noexcept;
        bool name_is_equals(std::string const &) const;
        size_t get_labl_index() const;
    };
private:
    std::vector<Labl> labls_;
public:
    LabelManager() = default;
    void insert(psc::Label const &, size_t);
    bool has_labl(std::string const &) const;
    size_t get_labl_index(std::string const &) const;
};