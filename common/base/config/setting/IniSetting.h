#pragma once

#include "SettingAbstract.h"
#include "../parser/IniParser.h"

class IniSetting : public virtual SettingAbstract {
protected:
	friend class IniParser;
};
