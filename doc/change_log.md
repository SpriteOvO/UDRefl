# Change Log

[TOC]

## 0.8

- 0.8.1
  - support
    - pointer, array
    - string: `std::string`, `std::string_view`, `const char*` 
  - operations: advance, distance, next, prev
  - `IsCompatible` support pointer and array (e.g. `const char[5]->const char*`)
- :star: 0.8.0 [refactoring] : simplification, improve performance
  - remove `ConstObjectPtr` and `SharedConstObject` 
  - `TypeID` -> `Type`, `StrID` -> `Name` 
  - simplify API
    - `IsInvocable`, ...
    - move APIs with `Type` to corresponding APIs with `ObjectView` 
    - use flag (`FieldFlag`, `MethodFlag`)
  - remove `[aligned]malloc` and `[aligned]free` 
  - fully support every type in C++ (reference, constant)

## 0.7

- 0.7.3
  - support `std::pair` (first, second)
  - support `std::tuple` 
  - `IDRegistry` name require ending with `'\0'` 
- 0.7.2
  - add algorithm `Contains*` 
  - `GetTemporaryResource` for user arguments buffer
  - fix bugs for `NewArgsGuard` 
  - `ArgsBuffer` -> `ArgPtrBuffer` 
- 0.7.1
  - cast APIs with `ConstObjectPtr` support reference
  - improve `ObjectPtrBase::operator bool` (as a meta function)
  - **refactoring compatible, invokable and invoke** 
  - add `IsNonArgCopyConstructible` 
  - add more type computations
    - `AddLValueReference` 
    - `AddRValueReference` 
  - fix bugs
    - `TypeID_of<Args>...` -> `TypeID_of<decltype(args)>...` 
    - `AInvoke`: `ObjectPtr `-> `&{T}` 
- 0.7.0
  - use C++20
  - use `std::span` 
  - rename `RegisterTypeAuto` to `RegisterType` 
  - auto register type's inner type (e.g. `value_type`, `key_type`, `mapped_type`, `iterator`, ...) 
  - remove `RegisterType` in `ReflMngr::GenerateParamList` and `ReflMngr::GenerateResultDesc` 
  - delete target `pch` 

## 0.6

- 0.6.1
  - `RWVar` support non-constant reference object.
  - improve `MethodPtr` 
  - improve `TypeIDRegistry::Register/RegisterUnmanaged`  
  - simplify `ObjectPtr` and `SharedObj`'s `operator x=` (`x` is `+,-,*,/,...`)
  - `ReflMngr` add algorithms for owned
- 0.6.0
  - copy argument for `T <- T&/const T&/const T&&` when invoking.
  - use perfect forwarding for invoke.
  - refactoring `ParamList ` 
    - `ParamList::IsCompatible` -> `ReflMngr::IsCompatible` 
    - `ParamList` -> `std::vector<TypeID>` 
  - `ReflMngr::RVar` support reference object.
  - `args_buffer`'s type : `void*` -> `ArgsBuffer` (= `void* const*`).
  - improve test
  - `TypeIDRegistry` add functions
    - `RegisterAddRValueReference` 
    - `RegisterAddLValueReference` 
    - `RegisterAddConstRValueReference` 
  - `ReflMngr` add functions
    - `MNew` 
    - `MDelete` 

