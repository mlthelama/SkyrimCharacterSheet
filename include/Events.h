#include "RE/Skyrim.h"

namespace Events
{
	class KeyManager : public RE::BSTEventSink<RE::InputEvent*>
	{
	public:
		using EventResult = RE::BSEventNotifyControl;

		static KeyManager* GetSingleton();

		auto ProcessEvent(RE::InputEvent* const* p_event, RE::BSTEventSource<RE::InputEvent*>* p_eventSource) -> EventResult;

		bool Save(const SKSE::SerializationInterface* p_int, uint32_t p_typeCode, uint32_t p_version);
		bool Load(const SKSE::SerializationInterface* p_int);

		void Clear();
		uint32_t GetKey() const;
		void SetKey(uint32_t p_key);
	private:
		using Lock = std::recursive_mutex;
		using Locker = std::lock_guard<Lock>;

		enum : uint32_t
		{
			kInvalid = static_cast<uint32_t>(-1),
			//maybe remove
			kKeyboardOffset = 0
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

	//maybe add event sing when player char changes values we care about
	void SinkEventHandlers();
}