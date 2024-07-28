#include "typesdao.h"

namespace DAO
{
namespace Types
{

const uint8_t* IFigure::getRawData(const Figure* figure) const
{
    const flatbuffers::String* payload = figure->payload();
    const uint8_t* payload_data = reinterpret_cast<const uint8_t*>(payload->data());
    return payload_data;
}

Rect::Rect(const Figure* figure)
{
    auto rawData = IFigure::getRawData(figure);
    const RectData* rectData = flatbuffers::GetRoot<RectData>(rawData);
    x = rectData->x();
    y = rectData->y();
    width = rectData->width();
    height = rectData->height();
    color_hex = rectData->color_hex()->str();
}

std::string Rect::getType() const
{
    return "Rect";
}

std::string Rect::getPosition() const
{
    std::string str = std::to_string(x) + "px, " + std::to_string(y) + "px";
    return str;
}

std::string Rect::getRegion() const
{
    std::string str = std::to_string(width) + "px, " + std::to_string(height) + "px";
    return str;
}

int Rect::getX() const
{
    return x;
}

int Rect::getY() const {
    return y;
}

int Rect::getWidth() const {
    return width;
}

int Rect::getHeight() const {
    return height;
}

std::string Rect::getColorHex() const {
    return color_hex;
}

Ellipse::Ellipse(const Figure* figure)
{
    auto rawData = IFigure::getRawData(figure);
    const EllipseData* ellipseData = flatbuffers::GetRoot<EllipseData>(rawData);
    x = ellipseData->x();
    y = ellipseData->y();
    r1 = ellipseData->r1();
    r2 = ellipseData->r2();
    color_hex = ellipseData->color_hex()->str();
}

std::string Ellipse::getType() const
{
    return "Ellipse";
}

std::string Ellipse::getPosition() const
{
    return std::to_string(x) + "px, " + std::to_string(y) + "px";
}

std::string Ellipse::getRegion() const
{
    return std::to_string(r1) + "px " + std::to_string(r2) + "px at " + std::to_string(x) + "px " + std::to_string(y) + "px";
}

int Ellipse::getX() const
{
    return x;
}

int Ellipse::getY() const
{
    return y;
}

int Ellipse::getR1() const
{
    return r1;
}

int Ellipse::getR2() const
{
    return r2;
}

std::string Ellipse::getColorHex() const
{
    return color_hex;
}

Triangle::Triangle(const Figure* figure)
{
    auto rawData = IFigure::getRawData(figure);
    const TriangleData* triangleData = flatbuffers::GetRoot<TriangleData>(rawData);
    x1 = triangleData->x1();
    y1 = triangleData->y1();
    x2 = triangleData->x2();
    y2 = triangleData->y2();
    x3 = triangleData->x3();
    y3 = triangleData->y3();
    color_hex = triangleData->color_hex()->str();
}

std::string Triangle::getType() const
{
    return "Triangle";
}

std::string Triangle::getPosition() const
{
    return std::to_string(x1) + "px, " + std::to_string(y1) + "px";
}

std::string Triangle::getRegion() const
{
    return std::to_string(x1) + "px " + std::to_string(y1) + "px, " + std::to_string(x2) + "px " + std::to_string(y2) + "px, " + std::to_string(x3) + "px " + std::to_string(y3) + "px";
}

int Triangle::getX1() const
{
    return x1;
}

int Triangle::getY1() const
{
    return y1;
}

int Triangle::getX2() const
{
    return x2;
}

int Triangle::getY2() const
{
    return y2;
}

int Triangle::getX3() const
{
    return x3;
}

int Triangle::getY3() const
{
    return y3;
}

std::string Triangle::getColorHex() const
{
    return color_hex;
}

Line::Line(const Figure* figure)
{
    auto rawData = IFigure::getRawData(figure);
    const LineData* lineData = flatbuffers::GetRoot<LineData>(rawData);
    x1 = lineData->x1();
    y1 = lineData->y1();
    x2 = lineData->x2();
    y2 = lineData->y2();
    color_hex = lineData->color_hex()->str();
}

std::string Line::getType() const
{
    return "Line";
}

std::string Line::getPosition() const
{
    return std::to_string(x1) + "px, " + std::to_string(y1) + "px";
}

std::string Line::getRegion() const
{
    return std::to_string(x1) + "px " + std::to_string(y1) + "px, " + std::to_string(x2) + "px " + std::to_string(y2) + "px";
}

int Line::getX1() const
{
    return x1;
}

int Line::getY1() const
{
    return y1;
}

int Line::getX2() const
{
    return x2;
}

int Line::getY2() const
{
    return y2;
}

std::string Line::getColorHex() const
{
    return color_hex;
}

} // namespace Types
} // namespace DAO
