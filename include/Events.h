#pragma once

namespace Events
{
	class KeyManager : public RE::BSTEventSink<RE::InputEvent*> {
	public:
		using EventResult = RE::BSEventNotifyControl;

		static KeyManager* GetSingleton();

		auto ProcessEvent(RE::InputEvent* const* p_event, RE::BSTEventSource<RE::InputEvent*>* p_eventSource) -> EventResult;

		bool Save(const SKSE::SerializationInterface* p_int, uint32_t p_typeCode, uint32_t p_version);
		bool Load(const SKSE::SerializationInterface* p_int);

		void Clear();
		uint32_t GetKey() const;
		void SetKey(uint32_t p_key);

		static void Sink();
	private:

		uint32_t GetGamepadIndex(RE::BSWin32GamepadDevice::Key a_key);

		using Lock = recursive_mutex;
		using Locker = lock_guard<Lock>;

		enum : uint32_t
		{
			kInvalid = static_cast<uint32_t>(-1),
			kKeyboardOffset = 0,
			kMouseOffset = 256,
			kGamepadOffset = 266
		};
		KeyManager();
		KeyManager(const KeyManager&) = delete;
		KeyManager(KeyManager&&) = delete;
		virtual ~KeyManager() = default;

		KeyManager& operator=(const KeyManager&) = delete;
		KeyManager& operator=(KeyManager&&) = delete;

		mutable Lock _lock;
		uint32_t _key;

	};

	class MenuHandler : public RE::BSTEventSink<RE::MenuOpenCloseEvent> {
	public:
		using EventResult = RE::BSEventNotifyControl;

		static MenuHandler* GetSingleton();

		static void Sink();

		auto ProcessEvent(RE::MenuOpenCloseEvent const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) -> EventResult;

		MenuHandler();
		MenuHandler(const MenuHandler&) = delete;
		MenuHandler(MenuHandler&&) = delete;
		virtual ~MenuHandler() = default;

		MenuHandler& operator=(const MenuHandler&) = delete;
		MenuHandler& operator=(MenuHandler&&) = delete;
	};

	//maybe add event sing when player char changes values we care about
	void SinkEventHandlers();
}