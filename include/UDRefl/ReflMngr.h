#pragma once

#include "Registry.h"
#include "TypeInfo.h"
#include "EnumInfo.h"

#include <functional>

namespace Ubpa::UDRefl {
	class ReflMngr {
	public:
		static ReflMngr& Instance() noexcept {
			static ReflMngr instance;
			return instance;
		}

		//
		// Data
		/////////

		NameRegistry nregistry;
		TypeRegistry tregistry;
		std::unordered_map<TypeID, TypeInfo> typeinfos;
		std::unordered_map<TypeID, EnumInfo> enuminfos;

		//
		// Cast
		/////////

		ObjectPtr StaticCast_DerivedToBase (ObjectPtr obj, TypeID typeID) const noexcept;
		ObjectPtr StaticCast_BaseToDerived (ObjectPtr obj, TypeID typeID) const noexcept;
		ObjectPtr DynamicCast_BaseToDerived(ObjectPtr obj, TypeID typeID) const noexcept;
		ObjectPtr StaticCast               (ObjectPtr obj, TypeID typeID) const noexcept;
		ObjectPtr DynamicCast              (ObjectPtr obj, TypeID typeID) const noexcept;
		
		ConstObjectPtr StaticCast_DerivedToBase (ConstObjectPtr obj, TypeID typeID) const noexcept
		{ return StaticCast_DerivedToBase (reinterpret_cast<ObjectPtr&>(obj), typeID); }

		ConstObjectPtr StaticCast_BaseToDerived (ConstObjectPtr obj, TypeID typeID) const noexcept
		{ return StaticCast_BaseToDerived (reinterpret_cast<ObjectPtr&>(obj), typeID); }

		ConstObjectPtr DynamicCast_BaseToDerived(ConstObjectPtr obj, TypeID typeID) const noexcept
		{ return DynamicCast_BaseToDerived(reinterpret_cast<ObjectPtr&>(obj), typeID); }

		ConstObjectPtr StaticCast               (ConstObjectPtr obj, TypeID typeID) const noexcept
		{ return StaticCast               (reinterpret_cast<ObjectPtr&>(obj), typeID); }

		ConstObjectPtr DynamicCast              (ConstObjectPtr obj, TypeID typeID) const noexcept
		{ return DynamicCast              (reinterpret_cast<ObjectPtr&>(obj), typeID); }

		//
		// Field
		//////////

		// read/write field, non-const
		ObjectPtr RWVar(ObjectPtr obj, NameID fieldID) const noexcept;
		// read field, non-const + const
		ConstObjectPtr RVar(ConstObjectPtr obj, NameID fieldID) const noexcept;

		//
		// Invoke
		///////////

		bool IsStaticInvocable(TypeID typeID, NameID methodID, Span<TypeID> argTypeIDs = {}) const noexcept;
		bool IsConstInvocable(TypeID typeID, NameID methodID, Span<TypeID> argTypeIDs = {}) const noexcept;
		bool IsInvocable(TypeID typeID, NameID methodID, Span<TypeID> argTypeIDs = {}) const noexcept;

		InvokeResult Invoke(TypeID typeID, NameID methodID, Span<TypeID> argTypeIDs = {}, void* args_buffer = nullptr, void* result_buffer = nullptr) const;
		InvokeResult Invoke(ConstObjectPtr obj, NameID methodID, Span<TypeID> argTypeIDs = {}, void* args_buffer = nullptr, void* result_buffer = nullptr) const;
		InvokeResult Invoke(ObjectPtr obj, NameID methodID, Span<TypeID> argTypeIDs = {}, void* args_buffer = nullptr, void* result_buffer = nullptr) const;

		template<typename T>
		T Invoke(TypeID typeID, NameID methodID, Span<TypeID> argTypeIDs = {}, void* args_buffer = nullptr) const;
		template<typename T>
		T Invoke(ConstObjectPtr obj, NameID methodID, Span<TypeID> argTypeIDs = {}, void* args_buffer = nullptr) const;
		template<typename T>
		T Invoke(ObjectPtr obj, NameID methodID, Span<TypeID> argTypeIDs = {}, void* args_buffer = nullptr) const;

		//
		// Meta
		/////////

		bool IsInvocable(NameID methodID, Span<TypeID> argTypeIDs = {}) const noexcept
		{ return IsInvocable(tregistry.GetID(TypeRegistry::Meta::global), methodID, argTypeIDs); }

		InvokeResult Invoke(NameID methodID, Span<TypeID> argTypeIDs = {}, void* args_buffer = nullptr, void* result_buffer = nullptr) const
		{ return Invoke(tregistry.GetID(TypeRegistry::Meta::global), methodID, argTypeIDs, args_buffer, result_buffer); }

		bool IsConstructible(TypeID typeID, Span<TypeID> argTypeIDs = {}) const noexcept;
		bool IsDestructible(TypeID typeID) const noexcept;

		bool Construct(ObjectPtr obj, Span<TypeID> argTypeIDs = {}, void* args_buffer = nullptr) const;
		bool Destruct(ConstObjectPtr obj) const;

		void* Malloc(uint64_t size) const;
		bool  Free(void* ptr) const;

		void* AlignedMalloc(uint64_t size, uint64_t alignment) const;
		bool  AlignedFree(void* ptr) const;

		ObjectPtr New(TypeID typeID, Span<TypeID> argTypeIDs = {}, void* args_buffer = nullptr) const;
		bool      Delete(ConstObjectPtr obj) const;

		//
		// Algorithm
		//////////////

		// self typeID and all bases' typeID
		void ForEachTypeID(
			TypeID typeID,
			const std::function<void(TypeID)>& func) const;

		// self type and all bases' type
		void ForEachType(
			TypeID typeID,
			const std::function<void(Type)>& func) const;

		// self fields and all bases' fields
		void ForEachField(
			TypeID typeID,
			const std::function<void(Type, Field)>& func) const;

		// self methods and all bases' methods
		void ForEachMethod(
			TypeID typeID,
			const std::function<void(Type, Method)>& func) const;

		// self [r/w] vars and all bases' [r/w] vars
		void ForEachRWVar(
			ObjectPtr obj,
			const std::function<void(Type, Field, ObjectPtr)>& func) const;

		// self [r] vars and all bases' [r] vars
		void ForEachRVar(
			ConstObjectPtr obj,
			const std::function<void(Type, Field, ConstObjectPtr)>& func) const;

	private:
		ReflMngr();
	};
}

#include "details/ReflMngr.inl"