#include <QFileInfo>
#include <cmath>

#include "intel.hpp"

Intel::Intel() : brightness_attribute(this->PATH)
{
    this->brightness_attribute.open(QIODevice::WriteOnly);
}

Intel::~Intel()
{
    if (this->brightness_attribute.isOpen())
        this->brightness_attribute.close();
}

bool Intel::supported()
{
    return QFileInfo(this->brightness_attribute).isWritable();
}

uint8_t Intel::priority()
{
    return 4;
}

void Intel::set(int brightness)
{
    brightness = round( (brightness - 75) / (255.0f - 75) * 100 );

    if (this->brightness_attribute.isOpen()) {
        this->brightness_attribute.reset();
        this->brightness_attribute.write(std::to_string(brightness).c_str());
        this->brightness_attribute.flush();
    }
}
