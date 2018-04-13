#ifndef GEOMETRIES_H
#define GEOMETRIES_H

#include <string>
#include <vector>

#include "config.hpp"
#include "geometry_traits.hpp"

namespace binpack2d {

template<class RawShape>
class _Transformation {
    TTransformation<RawShape> tr_;

public:

    _Transformation(TTransformation<RawShape>&& tr): tr_(std::move(tr)) {}

    TCoord<RawShape>& get(unsigned long row, unsigned long col) {
        return TransformationLike::get(tr_, row, col);
    }
};

template<class RawShape>
class _Shape {
    RawShape sh_;
public:

//    Shape(const RawShape& sh): sh_(sh) {}

//    template<class...Args>
//    _Shape(Args...args): sh_(args...) {}

    _Shape(RawShape&& sh): sh_(std::move(sh)) {}

    std::string toString() const { return ShapeLike::toString(sh_); }

    TVertexIterator<RawShape> begin() {
        return ShapeLike::begin(sh_);
    }

    TVertexConstIterator<RawShape> cbegin() const {
        return ShapeLike::cbegin(sh_);
    }

    TVertexIterator<RawShape> end() {
        return ShapeLike::end(sh_);
    }

    TVertexConstIterator<RawShape> cend() const {
        return ShapeLike::cend(sh_);
    }

    TPoint<RawShape> vertex(unsigned long idx) const {
        return ShapeLike::point(sh_, idx);
    }

    _Shape& transform(const TTransformation<RawShape>& tr) {
        return _Shape(ShapeLike::transform(sh_, tr));
    }

    double area() const {
        return ShapeLike::area(sh_);
    }

    _Shape noFitPolygon() const { return _Shape(); }

    unsigned long vertexCount() const BP2D_NOEXCEPT {
        return cend() - cbegin();
    }

};

template<class RawShape>
class _Rectangle: public _Shape<RawShape> {
    RawShape sh_;
public:

    using Unit = typename TCoord<RawShape>;

    _Rectangle(Unit width, Unit height):
        _Shape<RawShape>( ShapeLike::create<RawShape>( {{0, 0},
                                             {0, height},
                                             {width, height},
                                             {width, 0}} ))
    {
    }
};


}

#endif // GEOMETRIES_H
