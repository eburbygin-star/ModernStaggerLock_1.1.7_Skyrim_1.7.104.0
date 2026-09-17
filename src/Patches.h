#pragma once
#include "DKUtil/Hook.hpp"

namespace ModernStaggerLock
{
	using namespace DKUtil::Alias;

	class StaggeredStateCheckPatch
	{
		static constexpr OpCode NOP = 0x90;
		static constexpr OpCode StaggeredCheckNop[6]{ NOP, NOP, NOP, NOP, NOP, NOP };

		// 1.5.97: 1405FA1B0 (+0x55), 1.7.104.0: 14069FC00 (+0x54)
	public:
		static void Install()
		{
			const auto funcAddr = RELOCATION_ID(36700, 37710).address();
			const auto offset = REL::Module::IsAE() ? 0x54 : 0x55;
			DKUtil::Hook::WriteData(funcAddr + offset, &StaggeredCheckNop, sizeof(StaggeredCheckNop), false);
			INFO("{} Done!", __FUNCTION__);
		}

	private:
		StaggeredStateCheckPatch() = delete;
		~StaggeredStateCheckPatch() = delete;
	};
}