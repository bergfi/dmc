/*
 * DMC - DMC Model Checker is a modular, multi-core model checker
 * Copyright © 2021 Freark van der Berg
 *
 * This file is part of DMC.
 *
 * DMC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * DMC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DMC.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <string>
#include <vector>
#include <ostream>

namespace llmc { namespace statespace {

class Type {
public:
    virtual void print(std::ostream& os) const = 0;
    friend std::ostream& operator<<(std::ostream& os, Type const& type) {
        type.print(os);
        return os;
    }
};

class SingleType: public Type {
public:
    SingleType(const std::string& name) : name(name) {}
    virtual void print(std::ostream& os) const override {
        os << name;
    }
private:
    std::string name;
};

class StructType: public Type {
public:

    StructType& addField(std::string name, Type* type) {
        fieldNames.push_back(name);
        fieldTypes.push_back(type);
        return *this;
    }

    const std::vector<std::string>& getFieldNames() const {
        return fieldNames;
    }

    const std::vector<Type*>& getFieldTypes() const {
        return fieldTypes;
    }

    virtual void print(std::ostream& os) const override {
        os << "{ ";
        for(size_t i = 0; i < fieldNames.size(); ++i) {
            if(i!=0) os << ", ";
            os << fieldNames[i];
            os << ": ";
            os << *fieldTypes[i];
        }
        os << " }";
    }
private:
    std::vector<std::string> fieldNames;
    std::vector<Type*> fieldTypes;
};

class ArrayType: public Type {
public:
    ArrayType(Type* elementType, size_t elements) : _elementType(elementType), _elements(elements) {}

    Type* getElementType() const {
        return _elementType;
    }

    size_t getNumberOfElements() const {
        return _elements;
    }

    virtual void print(std::ostream& os) const override {
        _elementType->print(os);
        os << "[" << _elements << "]";
    }

    bool hasVariableLength() const {
        return _variableLength;
    }

private:
    Type* _elementType;
    size_t _elements;
    bool _variableLength;
};

} }