


Testfiles for Lua-Intf
===================


master
========
Nothing is const, run's fine:

``
Start
A:debug "Foo"
Creating B
B:debug
A:debug "Foo"
End
``

non-const
========
version where class B as a const correct class to Base
Compiles fine but generates:

``
Start
A:debug "Foo"
Creating B
simple.lua:7: unknown class (null metatable)
Press <RETURN> to close this window...
``
