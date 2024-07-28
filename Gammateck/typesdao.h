#ifndef TYPESDAO_H
#define TYPESDAO_H

#include "api_generated.h"
#include <string>

namespace DAO
{
namespace Types
{

class IFigure
{
public:
    virtual ~IFigure() = default;
    const uint8_t* getRawData(const Figure* figure) const;
    virtual std::string getType() const = 0;
    virtual std::string getPosition() const = 0;
    virtual std::string getRegion() const = 0;
};

class Rect : public IFigure
{
public:
    Rect(const Figure* figure);
    std::string getType() const override;
    std::string getPosition() const override;
    std::string getRegion() const override;
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    std::string getColorHex() const;


private:
    int x;
    int y;
    int width;
    int height;
    std::string color_hex;
};

class Ellipse : public IFigure
{
public:
    Ellipse(const Figure* figure);
    std::string getType() const override;
    std::string getPosition() const override;
    std::string getRegion() const override;
    int getX() const;
    int getY() const;
    int getR1() const;
    int getR2() const;
    std::string getColorHex() const;

private:
    int x;
    int y;
    int r1;
    int r2;
    std::string color_hex;
};

class Triangle : public IFigure
{
public:
    Triangle(const Figure* figure);
    std::string getType() const override;
    std::string getPosition() const override;
    std::string getRegion() const override;
    int getX1() const;
    int getY1() const;
    int getX2() const;
    int getY2() const;
    int getX3() const;
    int getY3() const;
    std::string getColorHex() const;

private:
    int x1;
    int y1;
    int x2;
    int y2;
    int x3;
    int y3;
    std::string color_hex;
};

class Line : public IFigure
{
public:
    Line(const Figure* figure);
    std::string getType() const override;
    std::string getPosition() const override;
    std::string getRegion() const override;
    int getX1() const;
    int getY1() const;
    int getX2() const;
    int getY2() const;
    std::string getColorHex() const;

private:
    int x1;
    int y1;
    int x2;
    int y2;
    std::string color_hex;
};

} // namespace Types
} // namespace DAO

#endif // TYPESDAO_H
