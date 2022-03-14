/*
 * Copyright 2021 Google LLC.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "src/sksl/SkSLCompiler.h"
#include "src/sksl/SkSLContext.h"

namespace SkSL {

class Poison : public Expression {
public:
    inline static constexpr Kind kExpressionKind = Kind::kPoison;

    static std::unique_ptr<Expression> Make(Position pos, const Context& context) {
        return std::make_unique<Poison>(pos, context.fTypes.fPoison.get());
    }

    Poison(Position pos, const Type* type)
        : INHERITED(pos, kExpressionKind, type) {}

    bool hasProperty(Property property) const override {
        return false;
    }

    std::unique_ptr<Expression> clone() const override {
        return std::make_unique<Poison>(fPosition, &this->type());
    }

    std::string description() const override {
        return Compiler::POISON_TAG;
    }

private:
    using INHERITED = Expression;
};

} // namespace SkSL
