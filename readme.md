Testfiles for Lua-Intf
===================


master
========
Nothing is const, run's fine:

```
Start
A:debug "Foo"
Creating B
B:debug
A:debug "Foo"
End
```

non-const
========
version where class B as a const correct class to Base
Compiles fine but generates:

```
Start
A:debug "Foo"
Creating B
simple.lua:7: unknown class (null metatable)
Press <RETURN> to close this window...
```

return-non-const
========

Version where a function tries to return a shared_ptr<const > type
This compiles with the error

```
/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ -c -mmacosx-version-min=10.7 -std=gnu0x -stdlib=libc++ -std=c++11 -g -gdwarf-2 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.8.sdk -std=c++11 -stdlib=libc++ -mmacosx-version-min=10.7 -Wall -W -fPIE -DQT_QML_DEBUG -DQT_DECLARATIVE_DEBUG -DQT_CORE_LIB -I../../Qt5.2.1/5.2.1/clang_64/mkspecs/macx-clang -I. -I../../local/include -I../../Qt5.2.1/5.2.1/clang_64/lib/QtCore.framework/Versions/5/Headers -I. -F/opt/Qt5.2.1/5.2.1/clang_64/lib -o main.o main.cpp
main.cpp:62:14: warning: unused parameter 'argc' [-Wunused-parameter]
int main(int argc, char *argv[])
             ^
main.cpp:62:26: warning: unused parameter 'argv' [-Wunused-parameter]
int main(int argc, char *argv[])
                         ^
In file included from main.cpp:13:
In file included from ./LuaIntf.h:1:
In file included from ./lua-intf/LuaIntf/LuaIntf.h:41:
./lua-intf/LuaIntf/impl/CppObject.h:284:11: error: no matching constructor for initialization of 'LuaIntf::CppObject'
        : CppObject(&*sp)
          ^         ~~~~
./lua-intf/LuaIntf/impl/CppObject.h:319:19: note: in instantiation of member function 'LuaIntf::CppObjectSharedPtr<std::__1::shared_ptr<const A>, const A>::CppObjectSharedPtr' requested here
        new (mem) CppObjectSharedPtr<SP, T>(sp);
                  ^
./lua-intf/LuaIntf/impl/CppObject.h:421:40: note: in instantiation of member function 'LuaIntf::CppObjectSharedPtr<std::__1::shared_ptr<const A>, const A>::pushToStack' requested here
            CppObjectSharedPtr<SP, T>::pushToStack(L, sp, is_const);
                                       ^
./lua-intf/LuaIntf/impl/CppObject.h:453:62: note: in instantiation of member function 'LuaIntf::LuaCppObjectFactory<std::__1::shared_ptr<const A>, const A, true, true>::push' requested here
        LuaCppObjectFactory<T, ObjectType, IsShared, IsRef>::push(L, t, IsConst);
                                                             ^
./lua-intf/LuaIntf/impl/CppInvoke.h:50:21: note: in instantiation of member function 'LuaIntf::LuaCppObject<std::__1::shared_ptr<const A>, false, false>::push' requested here
        LuaType<R>::push(L, call(func, args));
                    ^
./lua-intf/LuaIntf/impl/CppBindModule.h:96:79: note: in instantiation of member function 'LuaIntf::CppInvokeMethod<std::__1::shared_ptr<const A> (*)(), std::__1::shared_ptr<const A>>::push' requested here
            int n = CppInvokeMethod<FN, R, typename CppArg<P>::ValueType...>::push(L, fn, args);
                                                                              ^
./lua-intf/LuaIntf/impl/CppBindModule.h:318:77: note: in instantiation of member function 'LuaIntf::CppBindMethodBase<std::__1::shared_ptr<const A> (*)(), 1, std::__1::shared_ptr<const A>>::call' requested here
        m_meta.rawset(name, LuaRef::createFunction(L(), &CppBindMethod<FN>::call, proc));
                                                                            ^
main.cpp:80:6: note: in instantiation of function template specialization 'LuaIntf::CppBindModule::addFunction<std::__1::shared_ptr<const A> (*)()>' requested here
    .addFunction("getA", &lua_getA);
     ^
./lua-intf/LuaIntf/impl/CppObject.h:117:14: note: candidate constructor not viable: no known conversion from 'const A *' to 'void *' for 1st argument
    explicit CppObject(void* ptr)
             ^
./lua-intf/LuaIntf/impl/CppObject.h:142:5: note: candidate constructor not viable: no known conversion from 'const A *' to 'const LuaIntf::CppObject' for 1st argument
    CppObject(const CppObject&) = delete;
    ^
2 warnings and 1 error generated.
make: *** [main.o] Error 1
15:47:31: The process "/usr/bin/make" exited with code 2.
Error while building/deploying project luaIntfTest (kit: Desktop Qt 5.2.1 clang 64bit2)
When executing step 'Make'
15:47:31: Elapsed time: 00:01.
```
