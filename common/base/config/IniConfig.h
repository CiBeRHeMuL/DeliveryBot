#pragma once

#include "ConfigAbstract.h"
#include "parser/IniParser.h"

class IniConfig : public virtual ConfigAbstract {
public:
	IniConfig() : ConfigAbstract() {
		m_parser = new IniParser();
	}
};
