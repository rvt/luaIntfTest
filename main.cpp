extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}


#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "LuaIntf.h"


namespace LuaIntf {
LUA_USING_SHARED_PTR_TYPE(std::shared_ptr)
}

using namespace LuaIntf;
QString* gOut;

class Base {
public:
    virtual void debug() const = 0;
};

class A : public Base {
public:
    A(const QString & v) : Base() , _value(v){

    }
    virtual void debug() const {
        qDebug() << "A:debug" << _value;
    }

private:
    QString _value;
};

class B : public Base {
public:
    B(std::shared_ptr< Base> in) : Base() , _value(in){

    }
    virtual void debug() const {
        qDebug() << "B:debug";
        _value->debug();
    }

private:
    std::shared_ptr< Base> _value;
};

int main(int argc, char *argv[])
{
    lua_State* L = luaL_newstate();

    LuaBinding(L)
    .beginClass <Base> ("Base")
    .endClass()

    .beginExtendClass <A, Base> ("A")
    .addConstructor(LUA_SP(std::shared_ptr< A>), LUA_ARGS( QString & v))
    .addFunction("debug", &A::debug)
    .endClass()

    .beginExtendClass <B, Base> ("B")
    .addConstructor(LUA_SP(std::shared_ptr< B>), LUA_ARGS(std::shared_ptr< Base> in))
    .addFunction("debug", &B::debug)
    .endClass();

    luaL_openlibs(L);
    int s =luaL_dofile(L, "simple.lua");

    QString out;
    if (s != 0) {
        out.append(lua_tostring(L, -1));
        lua_pop(L, 1);
    }
    QTextStream(stdout) << out << endl;
    lua_close(L);
    return s;
}
