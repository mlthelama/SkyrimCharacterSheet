#pragma once
namespace Scaleform
{
	template <class T>
	class Logger : public RE::GFxLog
	{
	public:
		virtual void LogMessageVarg([[maybe_unused]] LogMessageType a_messageType, const char* a_fmt, std::va_list a_argList) override
		{
			std::string fmt(a_fmt ? a_fmt : "");
			while (!fmt.empty() && fmt.back() == '\n') {
				fmt.pop_back();
			}

			std::va_list args;
			va_copy(args, a_argList);
			std::vector<char> buf(std::vsnprintf(0, 0, fmt.c_str(), a_argList) + 1);
			std::vsnprintf(buf.data(), buf.size(), fmt.c_str(), args);
			va_end(args);

			logger::info("{}: {}"sv, T::Name().data(), buf.data());
		}
	};

	void Register();
}