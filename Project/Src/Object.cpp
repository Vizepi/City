#include <Object.h>

Object::Object(const std::string & filename)
    : m_obj(filename.c_str(), std::ios::out)
{

}

Object::~Object()
{
    m_obj.close();
}