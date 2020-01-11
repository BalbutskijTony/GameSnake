#pragma once
class Map
{
	public:
    // Размеры карты в ячейках
    Map(const size_t width, const size_t height) : _width(width), _height(height) {};
    ~Map() = default;
    
    const size_t getWidth() const;
    const size_t getHeight() const;

    void setWidth(const size_t width);
    void setHeight(const size_t height);
private:
    size_t _width;
    size_t _height;
};

